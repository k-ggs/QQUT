#include "md_plc.h"

MD_PLC::MD_PLC()
{
  getdata_=true;
}
MD_PLC::~MD_PLC()
{
  getdata_=false;
}
bool MD_PLC::emergencyStop() const
{
  return m_emergencyStop;
}
void MD_PLC::setEmergencyStop(bool newEmergencyStop)
{
  if (m_emergencyStop == newEmergencyStop)
    return;
      m_emergencyStop = newEmergencyStop;
      emit emergencyStopChanged();
}

void MD_PLC::servoEnable(kServoFunc num,bool enable)
{ // mtx.lock();
  if(num==0){
    hold2coils(8,enable?1:0);
  }else{
    hold2coils(0,enable?1:0);
   }
 //  mtx.unlock();

}

bool MD_PLC::Run(kServoFunc num, qreal force)
{
  /*
   * 1 判断趋势 checktendency 给定机会 默认五次 
   * 2 判断限位 checklimit
   * 3 判断目标力阈值 checkthreshold 80%
   * 4.判断是否超出目标值 是返回false 否返回true 继续
   */
  

if(!checkRunstatus(num))    {return false;}
bool forward=force>0;
if(!checklimit(num,forward)){return false;}

static qreal oldfc=0;
static qreal newfc=0;
oldfc=num==0?axisforce():sideforce();

std::this_thread::sleep_for(std::chrono::milliseconds(20));

newfc=num==0?axisforce():sideforce();
if(!checktendency(num,forward,oldfc,newfc))
{

if(faulttimes[num]<=0)
{

  faulttimes[num]=errtimes;
  return  false;
}else{
  faulttimes[num]--;
}
}
if(!threshold[num]){
  if(checkthreshold(num,force,newfc)){threshold[num]=true;}
}

if(!checktgetarget(num,force,newfc)){return false;}
  return true;
}

///获取电机的运动状态 停止false 运动true
bool MD_PLC::checkRunstatus(kServoFunc num)
{
  int runstatus=num==0?axisRunstatus():sideRunstatus();
   if(runstatus!=1){setErrorString(QString("电机%1没有处于运动状态").arg(num)); return false;}
  return true;
}

bool MD_PLC::checktendency(kServoFunc num,bool forward, qreal oldforce, qreal getforce)
{
  if(!checkRunstatus(num)){return false;}
  static int edge=100;//范围值 可能运动中存在波动


  if(forward){
    if(getforce-oldforce<-100)//正向运动 得出值应该>0 如果得值<负值说明与运动方向相反  需要停止运动
    setErrorString(QString("电机%1 运动趋势反向与设定正向相反 ").arg(num));
      return false;
  }
  else{
    if(getforce-oldforce>100)//负向运动 得出值应该<0 如果得值>0说明与运动方向相反  需要停止运动
     setErrorString(QString("电机%1 运动趋势正向与设定方向相反 ").arg(num));
      return false;

  }
  return true;
}

bool MD_PLC::checklimit(kServoFunc num, bool forwardrun)
{

  if(!checkRunstatus(num)){return false;}

  bool forwardlimit =num==0? axisforwardlimit():sideforwardlimit();
  bool nagativelimit=num==0? axisnegativelimit():sidenegativelimit();
   if(forwardrun&&forwardlimit)  {setErrorString(QString("电机%1 正限位触发 不能正向运动").arg(num));stop(num);return false;}
   if(!forwardrun&&nagativelimit){setErrorString(QString("电机%1 负限位触发 不能负向运动").arg(num));stop(num);return false;}
   return true;
}

bool MD_PLC::checkthreshold(kServoFunc num, qreal dstforce, qreal getforce)
{ if(!checkRunstatus(num)){return false;}

  if(dstforce==0)         {return false;}
  bool forward=dstforce>0;
  qreal th_force=dstforce*forcethreshold_;
  if(forward){
    
    if(getforce>=th_force)//正向运动 当力达到阈值区域时 减速运动至目标
    setspeed(num,lowspeed_,defaultactime,defaultdctime);

   spdlog::info("电机 {0} 正向运动记载力:{1} KG 触发低速阈值 开始低速运动:{2} mm/s",(int)num,th_force,lowspeed_);
    return true;
  }
  else{
    if(getforce<=th_force)//负向运动 当力达到阈值区域时 减速运动至目标
      setspeed(num,lowspeed_,defaultactime,defaultdctime);
      

    spdlog::info("电机 {0} 负向运动记载力:{1} KG 触发低速阈值 开始低速运动:{2} mm/s",(int)num,th_force,lowspeed_);
      return true;

  }
  return false;
}
 
bool MD_PLC::checktgetarget(kServoFunc num, qreal force, qreal getforce)
{
if(!checkRunstatus(num)){return false;}

  if(force==0)          {return false;}
  bool forward=force>0;
  if(forward){

    if(getforce>force)  {return false;}
  }
  else{

    if(getforce<force)  {return false;}
  }
  return true;
}

void MD_PLC::hold2coils( int index, int data)
{
  mtx.lock();
  mD_read_registers(servoaddres.slave_adr,1-1,1,&H16coils);
  QString bin=QString("%1").arg(H16coils,16,2,QLatin1Char('0'));
  //spdlog::info("bin40001-16{}",bin.toStdString());
  bin[index]=QString::number(data)[0];
  bool ok=false;
  H16coils=bin.toUInt(&ok,2);
  //spdlog::info("bin40001-16Later{}:{}",bin.toStdString(),ok);
  mD_write_register(servoaddres.slave_adr,1-1,H16coils);
  mtx.unlock();
}
void MD_PLC::gethold16()
{
 mD_read_registers(servoaddres.slave_adr,1-1,1,&H16coils);
 //QString bin=  QByteArray::number(H16coils, 2);
 QString bin=QString("%1").arg(H16coils,16,2,QLatin1Char('0'));
 ///侧向伺服正转点动
  side_servo_forward_inching_s =bin[2]=='1';
 ///侧向伺服反转点动
  side_servo_negative_inching_s=bin[3]=='1';
 ///侧向伺服方向切换
  setSide_run_direction(bin[4]=='1');
  ///伺服使能
  setAxisservoenable(bin[8]=='1');
  setSideservoenable(bin[0]=='1');
  //spdlog::info("bin:{} Axisservoenable:{} Sideservoenable:{}",bin.toStdString(),axisservoenable(),sideservoenable());
 ///轴向伺服正转点动
  axis_servo_forward_inching_s =bin[10]=='1';
 ///轴向伺服反转点动
  axis_servo_negative_inching_s=bin[11]=='1';
 ///轴向伺服方向切换
  setAxis_run_direction(bin[12]=='1');
}
void MD_PLC::setspeed(kServoFunc num,qreal speed,float /*加速时间ms*/act,float /*减速时间ms*/dct){
   /*
   plc set speed
   */
   uint16_t utspeed[2]={0};
   uint16_t utact[2]={0};
   uint16_t utdct[2]={0};
   modbus_set_float_abcd(speed,&utspeed[0]);
   modbus_set_float_abcd(act,&utact[0]);
   modbus_set_float_abcd(dct,&utdct[0]);
   mD_write_registers(servoaddres.slave_adr,num==0?servoaddres.axis_setspeed:servoaddres.side_setspeed,2,utspeed);
   mD_write_registers(servoaddres.slave_adr,num==0?servoaddres.axis_ACtime:servoaddres.side_ACtime,2,utact);
   mD_write_registers(servoaddres.slave_adr,num==0?servoaddres.axis_DCtime:servoaddres.side_DCtime,2,utdct);
   mD_write_registers(servoaddres.slave_adr,num==0?servoaddres.axis_servo_speed_configure_ensure:servoaddres.side_servo_speed_configure_ensure,2,utdct);
 }
void MD_PLC::servoRun(MD_PLC::kServoFunc num,qreal force, int timeout)
{/*
   1. 放置定时器超时则停止并退出
   2. 循环检测当前力是否达到目标值
      *力是否趋于目标值 是继续运动 否则停止运动
      *加入错误退出标志 限位等 未知错误
      *当距离目标值一定阈值时 降低速度抵达目标值
      *>=目标值则停止运动 并退出
   */
if(checkRunstatus(num)){stop(num);setErrorString(QString("电机:%1 已停止正在运行的电机!").arg(num)); return;};
//loopRun_ato[num]=true;
faulttimes[num]=errtimes;
QTime startT=QTime::currentTime();
mtx.lock();
if(mD_write_bit(servoaddres.slave_adr,num==0? servoaddres.axis_servo_RunStop:servoaddres.side_servo_RunStop,1)==-1) {loopRun_ato[num]=false;return ;} //运行电机
mtx.unlock();
while(loopRun_ato[num]){
QTime endT=QTime::currentTime();
if(startT.msecsTo(endT)>=timeout){
  stop(num);//超时停止电机
  //loopRun_ato[num]=false;
  return ;
}
if(!Run(num,force)){
  stop(num);//满足条件停止电机
  //loopRun_ato[num]=false;
  return;
}
}
}
void MD_PLC::asyncServoRun(MD_PLC::kServoFunc num,qreal force, int timeout){   
 static MD_PLC::kServoFunc num_= num;static std::atomic<double> force_[2]={0};static std::atomic<int> timeout_[2]={0};
 num_ = num;
 force_[num_]   = force;
 timeout_[num_] = timeout;
 std::thread td([&]()
                { 
                //spdlog::info("num:{0:d}, force:{1:f}, timeout:{2:d}",static_cast<int>(num_),force_[num_],timeout_[num_]);
                  loopRun_ato[num_]=true;
                  servoRun(num_, force_[num_], timeout_[num_]);
                  });
 td.detach();
}

///设置点动速度和增量 开始点动
void MD_PLC::inchingRun(kServoFunc num, bool forward)
{
  if(num==0)
  {
  hold2coils(forward?servoaddres.axis_servo_forward_point_run:servoaddres.axis_servo_negative_point_run,1);
  }
  else
  {
   hold2coils(forward?servoaddres.side_servo_forward_point_run:servoaddres.side_servo_negative_point_run,1);
  }
}
void MD_PLC::stopinchingRun(kServoFunc num, bool forward)
{
  if(num==0)
  {
    hold2coils(forward?servoaddres.axis_servo_forward_point_run:servoaddres.axis_servo_negative_point_run,0);
  }else{
    hold2coils(forward?servoaddres.side_servo_forward_point_run:servoaddres.side_servo_negative_point_run,0);
  }
}
void MD_PLC::loopRun(MD_PLC::kServoFunc num,qreal force,int looptimes,int /*ms 单位*/timeout){ 
  if(single_loop[num]>0){
  setErrorString(QString("servo(%1)已经运行 #loops(%2)").arg(num,single_loop[num])); 
  return ;
  }
 static MD_PLC::kServoFunc  num_= num;
 static std::atomic<double> force_[2]    ={0};
 static std::atomic<int>    timeout_[2]  ={0};
 static std::atomic<int>    looptimes_[2]={0};
 num_=num;
 force_[num_]=force;
 timeout_[num_]=timeout;
 looptimes_[num_]=looptimes;

std::thread td([&](){
 loopRun_ato[num_]=true;
 single_loop[num_]++;
for(int i=looptimes;i>0&&loopRun_ato[num_];i--){
 servoRun(num_,force_[num_],timeout_[num_]);
 servoRun(num_,0,timeout_[num_]);
 m_residualCycletimes[num_]=i;
 setResidualCycletimes(m_residualCycletimes);//更新循环次数
}
single_loop[num]--;

});
 td.detach();
}
void MD_PLC::parameter_configur(int num,float R_speed, float AC_T, float DC_T, float I_speed, float I_increment)
{ //轴向速度设置
  uint16_t rspeed[2]={0};
  uint16_t ac_t[2]={0};
  uint16_t dc_t[2]={0};
  uint16_t i_speed[2]={0};
  uint16_t i_increment[2]={0};
  modbus_set_float_dcba(R_speed,&rspeed[0]);  /*abcd  先转网络 小端->大端->小端*/
  modbus_set_float_dcba(AC_T,&ac_t[0]);
  modbus_set_float_dcba(DC_T,&dc_t[0]);
  modbus_set_float_dcba(I_speed,&i_speed[0]);
  modbus_set_float_dcba(I_increment,&i_increment[0]);
  //速度设置
  mtx.lock();
  mD_write_registers(servoaddres.slave_adr,num==0?servoaddres.axis_setspeed:servoaddres.side_setspeed,2,&rspeed[0]);
  mD_write_registers(servoaddres.slave_adr,num==0?servoaddres.axis_ACtime:servoaddres.side_ACtime,2,&ac_t[0]);
  mD_write_registers(servoaddres.slave_adr,num==0?servoaddres.axis_DCtime:servoaddres.side_DCtime,2,&dc_t[0]);
  mD_write_registers(servoaddres.slave_adr,num==0?servoaddres.axis_inchingspeed:servoaddres.side_inchingspeed,2,&i_speed[0]);
  mD_write_registers(servoaddres.slave_adr,num==0?servoaddres.axis_inchingincrement:servoaddres.side_inchingincrement,2,&i_increment[0]);
  //参数配置确认
  mD_read_registers(servoaddres.slave_adr,/*4001*/1-1,1,&H16coils);
  QString bin=QString("%1").arg(H16coils,16,2,QLatin1Char('0'));
  //spdlog::info("bin40001-16{}",bin.toStdString());
  if(num==1){
  bin[5] =QString::number(1)[0];//侧向伺服速度配置确认
  bin[6] =QString::number(1)[0];//侧向伺服点动配置确认
  }else{
  bin[13]=QString::number(1)[0];//轴向伺服速度配置确认
  bin[14]=QString::number(1)[0];//轴向伺服点动配置确认
  }
  bool ok=false;
  H16coils=bin.toUInt(&ok,2);
  //spdlog::info("bin40001-16Later{}:{}",bin.toStdString(),ok);
  mD_write_register(servoaddres.slave_adr,1-1,H16coils);
  mtx.unlock();
}
void MD_PLC::error_reset(kServoFunc num)
{
  hold2coils(15,1);
}

bool MD_PLC::stop(kServoFunc num)
{
 loopRun_ato[num]=false;
 if(mD_write_bit(servoaddres.slave_adr,num==0? servoaddres.axis_servo_RunStop:servoaddres.side_servo_RunStop,0)) {return false;}
 return true;
}
void MD_PLC::relaySwitch(int index, int run)
{mtx.lock();
  mD_write_bit(servoaddres.slave_adr,index,run);
 mtx.unlock();
}
void MD_PLC::asyncGetdata()
{
  std::thread td([&](){

    Getdata();
  });

  td.detach();
}
void MD_PLC::Getdata()
{
    while(getdata_){
    QTime s=QTime::currentTime();
    uint8_t dest[10]={0};
    //16bits
    mtx.lock();
    gethold16();
    //状态信息
    if(mD_read_input_bits(servoaddres.slave_adr,servoaddres.axis_forward_limit,10,dest)!=-1) {
      setAxisforwardlimit(dest[0]==1) ;
      setAxisnegativelimit(dest[1]==1);
      setSideforwardlimit(dest[2]==1);
      setSidenegativelimit(dest[3]==1);
      setStepforwardlimit(dest[4]==1);
      setStepnegativelimit(dest[5]==1);
      setAxisservobreakdown(dest[6]==1);
      setSideservobreakdown(dest[7]==1);
      setPhaseorderprotection(dest[8]==1);
      setEmergencyStop(dest[9]==1);
    }
    uint8_t dest5[5]={0};
    //5个继电器
    if(mD_read_bits(servoaddres.slave_adr,servoaddres.electromagnetic_valve,5,dest5)!=-1){
    setElectromagnetic_valve_s(dest5[0]==1);
    setPower_regulator_s(dest5[1]==1);
    setRefrigerator_s(dest5[2]==1);
    setMechanical_pump_s(dest5[3]==1);
    setCycle_pump_s(dest5[4]==1);
    }
    //5个寄存器
    uint16_t Iputdest5[11]={0};
    if(mD_read_input_registers(servoaddres.slave_adr,servoaddres.axis_force,11,Iputdest5)!=-1){
    setAxisforce(Iputdest5[0]);
    setSideforce(Iputdest5[1]);
    setTemperatureS1(Iputdest5[8]);
    setTemperatureS2(Iputdest5[9]);
    setTemperatureK3(Iputdest5[10]);
    }
    mtx.unlock();

    if(axisforwardlimit()){
      if(axis_servo_forward_inching_s){
        hold2coils(10,0);
      }
    }
    if(axisnegativelimit()){
      if(axis_servo_negative_inching_s){
        hold2coils(11,0);
      }
    }
    if(sideforwardlimit()){
      if(side_servo_forward_inching_s){
        hold2coils(2,0);
      }
    }
    if(sideforwardlimit()){
      if(side_servo_negative_inching_s){
        hold2coils(3,0);
      }
    }
    if(axisservobreakdown()){
      hold2coils(15,1);
    }
    if(sideservobreakdown()){
       hold2coils(7,1);
       }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    QTime e=QTime::currentTime();
    int ct=s.msecsTo(e);
    //spdlog::info("time: {}ms timetotal:{}ms",ct-10,ct);
  }
}
QVector<int> MD_PLC::residualCycletimes() const
{
  return m_residualCycletimes;
}

void MD_PLC::setResidualCycletimes(QVector<int> newResidualCycletimes)
{
 // if (m_residualCycletimes == newResidualCycletimes)
 // return;
  m_residualCycletimes = newResidualCycletimes;
  emit residualCycletimesChanged();
}

bool MD_PLC::sidenegativelimit() const
{
  return m_sidenegativelimit;
}

void MD_PLC::setSidenegativelimit(bool newSidenegativelimit)
{
  if (m_sidenegativelimit == newSidenegativelimit)
    return;
  m_sidenegativelimit = newSidenegativelimit;
  emit sidenegativelimitChanged();
}

bool MD_PLC::sideforwardlimit() const
{
  return m_sideforwardlimit;
}

void MD_PLC::setSideforwardlimit(bool newSideforwardlimit)
{
  if (m_sideforwardlimit == newSideforwardlimit)
    return;
  m_sideforwardlimit = newSideforwardlimit;
  emit sideforwardlimitChanged();
}

bool MD_PLC::axisnegativelimit() const
{
  return m_axisnegativelimit;
}

void MD_PLC::setAxisnegativelimit(bool newAxisnegativelimit)
{
  if (m_axisnegativelimit == newAxisnegativelimit)
    return;
  m_axisnegativelimit = newAxisnegativelimit;
  emit axisnegativelimitChanged();
}

bool MD_PLC::axisforwardlimit() const
{
  return m_axisforwardlimit;
}

void MD_PLC::setAxisforwardlimit(bool newAxisforwardlimit)
{
  if (m_axisforwardlimit == newAxisforwardlimit)
    return;
  m_axisforwardlimit = newAxisforwardlimit;

  emit axisforwardlimitChanged();
}

bool MD_PLC::stepforwardlimit() const
{
  return m_stepforwardlimit;
}

void MD_PLC::setStepforwardlimit(bool newStepforwardlimit)
{
  if (m_stepforwardlimit == newStepforwardlimit)
    return;
  m_stepforwardlimit = newStepforwardlimit;
  emit stepforwardlimitChanged();
}

bool MD_PLC::stepnegativelimit() const
{
  return m_stepnegativelimit;
}

void MD_PLC::setStepnegativelimit(bool newStepnegativelimit)
{
  if (m_stepnegativelimit == newStepnegativelimit)
    return;
  m_stepnegativelimit = newStepnegativelimit;
  emit stepnegativelimitChanged();
}

qreal MD_PLC::temperatureS1() const
{
  return m_temperatureS1;
}

void MD_PLC::setTemperatureS1(qreal newTemperatureS1)
{
  if (qFuzzyCompare(m_temperatureS1, newTemperatureS1))
    return;
  m_temperatureS1 = newTemperatureS1;
  emit temperatureS1Changed();
}

qreal MD_PLC::temperatureS2() const
{
  return m_temperatureS2;
}

void MD_PLC::setTemperatureS2(qreal newTemperatureS2)
{
  if (qFuzzyCompare(m_temperatureS2, newTemperatureS2))
    return;
  m_temperatureS2 = newTemperatureS2;
  emit temperatureS2Changed();
}

qreal MD_PLC::temperatureK3() const
{
  return m_temperatureK3;
}

void MD_PLC::setTemperatureK3(qreal newTemperatureK3)
{
  if (qFuzzyCompare(m_temperatureK3, newTemperatureK3))
    return;
  m_temperatureK3 = newTemperatureK3;
  emit temperatureK3Changed();
}

qreal MD_PLC::axisforce() const
{
  return m_axisforce;
}

void MD_PLC::setAxisforce(qreal newAxisforce)
{
  if (qFuzzyCompare(m_axisforce, newAxisforce))
    return;
  m_axisforce = newAxisforce;
  emit axisforceChanged();
}

qreal MD_PLC::sideforce() const
{
  return m_sideforce;
}

void MD_PLC::setSideforce(qreal newSideforce)
{
  if (qFuzzyCompare(m_sideforce, newSideforce))
    return;
  m_sideforce = newSideforce;
  emit sideforceChanged();
}

bool MD_PLC::axisservoenable() const
{
  return m_axisservoenable;
}

void MD_PLC::setAxisservoenable(bool newAxisservoenable)
{
  if (m_axisservoenable == newAxisservoenable)
    return;
  m_axisservoenable = newAxisservoenable;
  emit axisservoenableChanged();
}

bool MD_PLC::sideservoenable() const
{
  return m_sideservoenable;
}

void MD_PLC::setSideservoenable(bool newSideservoenable)
{
  if (m_sideservoenable == newSideservoenable)
    return;
  m_sideservoenable = newSideservoenable;
  emit sideservoenableChanged();
}

int MD_PLC::axisRunstatus() const
{
  return m_axisRunstatus;
}

void MD_PLC::setAxisRunstatus(int newAxisRunstatus)
{
  if (m_axisRunstatus == newAxisRunstatus)
    return;
  m_axisRunstatus = newAxisRunstatus;
  emit axisRunstatusChanged();
}

int MD_PLC::sideRunstatus() const
{
  return m_sideRunstatus;
}

void MD_PLC::setSideRunstatus(int newSideRunstatus)
{
  if (m_sideRunstatus == newSideRunstatus)
    return;
  m_sideRunstatus = newSideRunstatus;
  emit sideRunstatusChanged();
}

bool MD_PLC::sideservobreakdown() const
{
  return m_sideservobreakdown;
}

void MD_PLC::setSideservobreakdown(bool newSideservobreakdown)
{
  if (m_sideservobreakdown == newSideservobreakdown)
    return;
  m_sideservobreakdown = newSideservobreakdown;
  emit sideservobreakdownChanged();
}

bool MD_PLC::axisservobreakdown() const
{
  return m_axisservobreakdown;
}

void MD_PLC::setAxisservobreakdown(bool newAxisservobreakdown)
{
  if (m_axisservobreakdown == newAxisservobreakdown)
    return;
  m_axisservobreakdown = newAxisservobreakdown;
  emit axisservobreakdownChanged();
}

bool MD_PLC::phaseorderprotection() const
{
  return m_phaseorderprotection;
}

void MD_PLC::setPhaseorderprotection(bool newPhaseorderprotection)
{
  if (m_phaseorderprotection == newPhaseorderprotection)
    return;
  m_phaseorderprotection = newPhaseorderprotection;
  emit phaseorderprotectionChanged();
}

bool MD_PLC::electromagnetic_valve_s() const
{
  return m_electromagnetic_valve_s;
}

void MD_PLC::setElectromagnetic_valve_s(bool newElectromagnetic_valve_s)
{
  if (m_electromagnetic_valve_s == newElectromagnetic_valve_s)
    return;
  m_electromagnetic_valve_s = newElectromagnetic_valve_s;
  emit electromagnetic_valve_sChanged();
}

void MD_PLC::connectTcp(QString IP, int port)
{
  mdbustcpinit(IP,port);
}

bool MD_PLC::power_regulator_s() const
{
  return m_power_regulator_s;
}

void MD_PLC::setPower_regulator_s(bool newPower_regulator_s)
{
  if (m_power_regulator_s == newPower_regulator_s)
    return;
  m_power_regulator_s = newPower_regulator_s;
  emit power_regulator_sChanged();
}

bool MD_PLC::refrigerator_s() const
{
  return m_refrigerator_s;
}

void MD_PLC::setRefrigerator_s(bool newRefrigerator_s)
{
  if (m_refrigerator_s == newRefrigerator_s)
    return;
  m_refrigerator_s = newRefrigerator_s;
  emit refrigerator_sChanged();
}

bool MD_PLC::mechanical_pump_s() const
{
  return m_mechanical_pump_s;
}

void MD_PLC::setMechanical_pump_s(bool newMechanical_pump_s)
{
  if (m_mechanical_pump_s == newMechanical_pump_s)
    return;
  m_mechanical_pump_s = newMechanical_pump_s;
  emit mechanical_pump_sChanged();
}

bool MD_PLC::cycle_pump_s() const
{
  return m_cycle_pump_s;
}

void MD_PLC::setCycle_pump_s(bool newCycle_pump_s)
{
  if (m_cycle_pump_s == newCycle_pump_s)
    return;
  m_cycle_pump_s = newCycle_pump_s;
  emit cycle_pump_sChanged();
}

bool MD_PLC::axis_run_direction() const
{
  return m_axis_run_direction;
}

void MD_PLC::setAxis_run_direction(bool newAxis_run_direction)
{
  if (m_axis_run_direction == newAxis_run_direction)
    return;
  m_axis_run_direction = newAxis_run_direction;
  emit axis_run_directionChanged();
}

bool MD_PLC::side_run_direction() const
{
  return m_side_run_direction;
}

void MD_PLC::setSide_run_direction(bool newSide_run_direction)
{
  if (m_side_run_direction == newSide_run_direction)
    return;
  m_side_run_direction = newSide_run_direction;
  emit side_run_directionChanged();
}
