#ifndef MD_PLC_H
#define MD_PLC_H

#include <QObject>
#include"modbustcp.h"
#include"spdlog/spdlog.h"
#include"spdlog/fmt/bin_to_hex.h"
#include<QTime>
#include<mutex>
#include<QMutex>
class MD_PLC : public modbusTCP
{
  Q_OBJECT
  //正负限位
  Q_PROPERTY(bool sidenegativelimit READ sidenegativelimit WRITE setSidenegativelimit NOTIFY sidenegativelimitChanged)
  Q_PROPERTY(bool sideforwardlimit READ sideforwardlimit WRITE setSideforwardlimit NOTIFY sideforwardlimitChanged)
  Q_PROPERTY(bool axisnegativelimit READ axisnegativelimit WRITE setAxisnegativelimit NOTIFY axisnegativelimitChanged)
  Q_PROPERTY(bool axisforwardlimit READ axisforwardlimit WRITE setAxisforwardlimit NOTIFY axisforwardlimitChanged)
  Q_PROPERTY(bool stepforwardlimit READ stepforwardlimit WRITE setStepforwardlimit NOTIFY stepforwardlimitChanged)
  Q_PROPERTY(bool stepnegativelimit READ stepnegativelimit WRITE setStepnegativelimit NOTIFY stepnegativelimitChanged)
  //驱动器故障
  Q_PROPERTY(bool axisservobreakdown READ axisservobreakdown WRITE setAxisservobreakdown NOTIFY axisservobreakdownChanged)
  Q_PROPERTY(bool sideservobreakdown READ sideservobreakdown WRITE setSideservobreakdown NOTIFY sideservobreakdownChanged)
  //相序保护
  Q_PROPERTY(bool phaseorderprotection READ phaseorderprotection WRITE setPhaseorderprotection NOTIFY phaseorderprotectionChanged)
  //紧急急停按钮
  Q_PROPERTY(bool emergencyStop READ emergencyStop WRITE setEmergencyStop NOTIFY emergencyStopChanged)
  //伺服使能
  Q_PROPERTY(bool axisservoenable READ axisservoenable WRITE setAxisservoenable NOTIFY axisservoenableChanged)
  Q_PROPERTY(bool sideservoenable READ sideservoenable WRITE setSideservoenable NOTIFY sideservoenableChanged)
  //伺服运行状态
  Q_PROPERTY(int axisRunstatus READ axisRunstatus WRITE setAxisRunstatus NOTIFY axisRunstatusChanged)
  Q_PROPERTY(int sideRunstatus READ sideRunstatus WRITE setSideRunstatus NOTIFY sideRunstatusChanged)
  //伺服运行方向 1正转 0反转
  Q_PROPERTY(bool axis_run_direction READ axis_run_direction WRITE setAxis_run_direction NOTIFY axis_run_directionChanged)
  Q_PROPERTY(bool side_run_direction READ side_run_direction WRITE setSide_run_direction NOTIFY side_run_directionChanged)
  //传感器加载力
  Q_PROPERTY(qreal axisforce READ axisforce WRITE setAxisforce NOTIFY axisforceChanged)
  Q_PROPERTY(qreal sideforce READ sideforce WRITE setSideforce NOTIFY sideforceChanged)
  //温度 S1 S2 K3
  Q_PROPERTY(qreal temperatureS1 READ temperatureS1 WRITE setTemperatureS1 NOTIFY temperatureS1Changed)
  Q_PROPERTY(qreal temperatureS2 READ temperatureS2 WRITE setTemperatureS2 NOTIFY temperatureS2Changed)
  Q_PROPERTY(qreal temperatureK3 READ temperatureK3 WRITE setTemperatureK3 NOTIFY temperatureK3Changed)
  //剩余循环次数
  Q_PROPERTY(QVector<int> residualCycletimes READ residualCycletimes WRITE setResidualCycletimes NOTIFY residualCycletimesChanged)
  //电磁阀 调功器 制冷机 机械泵 循环泵
  Q_PROPERTY(bool electromagnetic_valve_s READ electromagnetic_valve_s WRITE setElectromagnetic_valve_s NOTIFY electromagnetic_valve_sChanged)
  Q_PROPERTY(bool power_regulator_s READ power_regulator_s WRITE setPower_regulator_s NOTIFY power_regulator_sChanged)
  Q_PROPERTY(bool refrigerator_s READ refrigerator_s WRITE setRefrigerator_s NOTIFY refrigerator_sChanged)
  Q_PROPERTY(bool mechanical_pump_s READ mechanical_pump_s WRITE setMechanical_pump_s NOTIFY mechanical_pump_sChanged)
  Q_PROPERTY(bool cycle_pump_s READ cycle_pump_s WRITE setCycle_pump_s NOTIFY cycle_pump_sChanged)
 public:
  MD_PLC();
  ~MD_PLC();
  void asyncGetdata();//异步获取数据
  void Getdata();
  ///剩余循环次数
  QList<int> residualCycletimes() const;
  public Q_SLOTS:
  void setEmergencyStop(bool newEmergencyStop);
  void setResidualCycletimes(QList<int> newResidualCycletimes);
  void setTemperatureK3(qreal newTemperatureK3);
  void setTemperatureS2(qreal newTemperatureS2);
  void setTemperatureS1(qreal newTemperatureS1);
  void setStepnegativelimit(bool newStepnegativelimit);
  void setStepforwardlimit(bool newStepforwardlimit);
  void setAxisforwardlimit(bool newAxisforwardlimit);
  void setAxisnegativelimit(bool newAxisnegativelimit);
  void setSideforwardlimit(bool newSideforwardlimit);
  void setSidenegativelimit(bool newSidenegativelimit);
  void setSideforce(qreal newSideforce);
  void setAxisforce(qreal newAxisforce);
  void setAxisservoenable(bool newAxisservoenable);
  void setSideservoenable(bool newSideservoenable);
  void setAxisRunstatus(int newAxisRunstatus);
  void setSideRunstatus(int newSideRunstatus);
  void setPhaseorderprotection(bool newPhaseorderprotection);
  void setAxisservobreakdown(bool newAxisservobreakdown);
  void setSideservobreakdown(bool newSideservobreakdown);
  void setCycle_pump_s(bool newCycle_pump_s);
  void setMechanical_pump_s(bool newMechanical_pump_s);
  void setRefrigerator_s(bool newRefrigerator_s);
  void setPower_regulator_s(bool newPower_regulator_s);
  void setElectromagnetic_valve_s(bool newElectromagnetic_valve_s);
  void setSide_run_direction(bool newSide_run_direction);
  void setAxis_run_direction(bool newAxis_run_direction);
 signals:
  void emergencyStopChanged();
  void residualCycletimesChanged();
  void sidenegativelimitChanged();
  void sideforwardlimitChanged();
  void axisnegativelimitChanged();
  void axisforwardlimitChanged();
  void stepforwardlimitChanged();
  void stepnegativelimitChanged();
  void temperatureS1Changed();
  void temperatureS2Changed();
  void temperatureK3Changed();
  void axisforceChanged();
  void sideforceChanged();
  void axisservoenableChanged();
  void sideservoenableChanged();
  void axisRunstatusChanged();
  void sideRunstatusChanged();
  void sideservobreakdownChanged();
  void axisservobreakdownChanged();
  void phaseorderprotectionChanged();
  void electromagnetic_valve_sChanged();
  void power_regulator_sChanged();
  void refrigerator_sChanged();
  void mechanical_pump_sChanged();
  void cycle_pump_sChanged();
  void axis_run_directionChanged();
  void side_run_directionChanged();

 private:
  static const  int errtimes=5;
  static const  int num_servo=2;
  std::atomic_bool getdata_   =true;//控制读取数据循环的锁
  std::atomic_bool loopRun_ato[num_servo]={true,true};
  std::atomic_int  single_loop[num_servo]={0,0};//同时只能一个电机循环
  std::atomic<int> faulttimes[num_servo]={errtimes,errtimes};//各五次错误机会
  std::atomic_bool threshold[num_servo]={false,false};//轴向 侧向阈值触发
  std::mutex mtx;//互斥锁 防止modbus 命令同时发 导致出错
  public:
  ///两个缸 0:轴向 1：侧向
  enum kServoFunc{
    SERVO1=0,//轴向
    SERVO2=1 //侧向
  };
  Q_ENUM(kServoFunc);
   ///连接tcp
  Q_INVOKABLE void connectTcp(QString IP,int port);
  ///伺服使能
  Q_INVOKABLE void servoEnable(MD_PLC::kServoFunc /*电机1or电机2*/num,bool enable);

  Q_INVOKABLE void asyncServoRun(MD_PLC::kServoFunc num,qreal force,int /*ms 单位*/timeout=60*1000);
  ///点动
  Q_INVOKABLE void inchingRun(MD_PLC::kServoFunc num,bool forward);
  ///点动停止
  Q_INVOKABLE void stopinchingRun(MD_PLC::kServoFunc num,bool forward);
  ///电机 停止运动 退出目标电机的所有循环 并停止运动
  Q_INVOKABLE bool  stop(MD_PLC::kServoFunc    /*电机1or电机2*/num);
  /// 五个继电器 开关
  /// 0.电磁阀PLCaddress:65
  /// 1.调功器PLCaddress:66
  /// 2.制冷机PLCaddress:67
  /// 3.机械泵PLCaddress:68
  /// 4.循环泵PLCaddress:69
  Q_INVOKABLE  void  relaySwitch(int index,int/*1run 0stop*/ run);
  Q_INVOKABLE  void  loopRun(MD_PLC::kServoFunc num,qreal force,int looptimes,int /*ms 单位*/timeout=60*1000);
  ///参数配置
  Q_INVOKABLE  void  parameter_configur(int num,float R_speed,float AC_T,float DC_T,float I_speed,float I_increment);
  ///故障复位
  Q_INVOKABLE  void  error_reset(MD_PLC::kServoFunc num);
  qreal axisforce()        const;
  qreal sideforce()        const;
  bool axisservoenable()   const;
  bool sideservoenable()   const;
  int  axisRunstatus()     const;
  int  sideRunstatus()     const;
  bool sideservobreakdown() const;
  bool axisservobreakdown() const;
  bool phaseorderprotection() const;
  bool electromagnetic_valve_s() const;
  bool power_regulator_s()  const;
  bool refrigerator_s()     const;
  bool mechanical_pump_s()  const;
  bool cycle_pump_s()       const;
  bool axis_run_direction() const;
  bool side_run_direction() const;
  bool emergencyStop()      const;
  bool sidenegativelimit()  const;
  bool sideforwardlimit()   const;
  bool axisnegativelimit()  const;
  bool axisforwardlimit()   const;
  bool stepforwardlimit()   const;
  bool stepnegativelimit()  const;
  qreal temperatureS1()     const;
  qreal temperatureS2()     const;
  qreal temperatureK3()     const;
 private:
           ///电机往目标方向和力运动运动
  void servoRun(MD_PLC::kServoFunc num,qreal force,int /*ms 单位*/timeout=60*1000);

  ///加载力1的范围
  int force1_[2]={-2000,2000};//KG
  ///加载力2的范围
  int force2_[2]={-600,600};  //KG
  ///疲劳测试的循环次数
  int looptimes_=0;
  ///速度范围 0.1-16.6 mm/s
  float speedlimit[2]={0.1,16.6};
  uint16_t H16coils=0;
  ///运动目标阈值 >=force*forcethreshold_ 时减速至低速防止 冲过
  float forcethreshold_=0.8; //
  float lowspeed_      =0.05;// mm/s
  float defaultactime=1;
  float defaultdctime=1;
  int Sthermocouple[2]={0,1600};//s型热电偶
  int Kthermocouple[2]={-200,1300};//K型热电偶
 typedef struct PlcAddress
{
   int   slave_adr;
   int   start_adr;
//  1x  input status
   uchar axis_forward_limit;  //轴向正限位           1：限位触发
   uchar axis_negative_limit; //轴向负限位           1：限位触发
   uchar side_forward_limit;  //侧向正限位           1：限位触发
   uchar side_negative_limit; //侧向负限位           1：限位触发
   uchar step_forward_limit;  //步进正限位           1：限位触发
   uchar step_negative_limit; //步进负限位           1：限位触发
   uchar  axis_servo_error;   //轴向伺服驱动器故障    1：正常，0：故障
   uchar  side_servo_error;   //侧向伺服驱动器故障    1：正常，0：故障
   uchar  phase_order_protection;//相序保护          1：正常，0：相序故障
   uchar  emergency_stop;    //紧急急停按钮          1:正常,0：故障
//  3x  input   register
   uchar   axis_force;        //轴向拉压力
   uchar   side_force;        //侧向扭力
   uchar   S_Temperature1;    //温度1（S型热电偶）
   uchar   S_Temperature2;    //温度2（S型热电偶）
   uchar   S_Temperature3;    //温度3（K型热电偶）
//  4x  holding register
    uchar  side_servo_enable;                      //侧向伺服使能 1：使能
    uchar  side_servo_RunStop;                     //侧向伺服启停 1：启动，0：停止
    uchar  side_servo_forward_point_run;           //侧向伺服正转点动
    uchar  side_servo_negative_point_run;          //侧向伺服反转点动
    uchar  side_servo_switch_direction;            //侧向伺服方向切换
    uchar  side_servo_speed_configure_ensure;      //侧向伺服速度配置确认
    uchar  side_servo_inching_configure_ensure;    //侧向伺服点动配置确认
    uchar  side_servo_error_resert_ensure;         //侧向伺服故障复位按键
    uchar  axis_servo_enable;                      //轴向伺服使能 1：使能
    uchar  axis_servo_RunStop;                     //轴向伺服启停 1：启动，0：停止
    uchar  axis_servo_forward_point_run;           //轴向伺服正转点动
    uchar  axis_servo_negative_point_run;          //轴向伺服反转点动
    uchar  axis_servo_switch_direction;            //轴向伺服方向切换
    uchar  axis_servo_speed_configure_ensure;      //轴向伺服速度配置确认
    uchar  axis_servo_inching_configure_ensure;    //轴向伺服点动配置确认
    uchar  axis_servo_error_resert_ensure;         //轴向伺服故障复位按键
    //0x  coil status
     uchar  electromagnetic_valve;//电磁阀
     uchar  power_regulator;//电磁阀
     uchar  refrigerating_machine ;//电磁阀
     uchar  mechanical_pump ;//电磁阀
     uchar  cycle_pump;//电磁阀
     //4x
     uchar axis_setspeed;//轴速度设置    范围：0.1--16.6mm/s
     uchar axis_ACtime;  //轴加速时间设置 ms
     uchar axis_DCtime;  //轴减速速时间设置 ms
     uchar side_setspeed;//侧向速度设置    范围：0.1--16.6mm/s
     uchar side_ACtime;  //侧向加速时间设置 ms
     uchar side_DCtime;  //侧向减速速时间设置 ms
     uchar axis_inchingspeed;    //轴点动速度
     uchar axis_inchingincrement;//轴点动增量
     uchar side_inchingspeed;    //侧点动速度
     uchar side_inchingincrement;//侧点动增量
     uchar step_setspeed;         //步进速度设置
     uchar power_regulator_output;//调功器输出给定
     PlcAddress(){
       slave_adr=1;
       start_adr=0;
       axis_forward_limit=1-1;
       axis_negative_limit=2-1;
       side_forward_limit=3-1;
       side_negative_limit=4-1;
       step_forward_limit=5-1;
       step_negative_limit=6-1;
       axis_servo_error=7-1;
       side_servo_error=8-1;
       phase_order_protection=9-1;
       emergency_stop=10-1;
      //  3x  input   register
       axis_force=17-1;
       side_force=18-1;
       S_Temperature1=25-1;
       S_Temperature2=26-1;
       S_Temperature3=27-1;
      //  4x  holding register
       side_servo_enable=0;
       side_servo_RunStop=1;
       side_servo_forward_point_run=2;
       side_servo_negative_point_run=3;
       side_servo_switch_direction=4;
       side_servo_speed_configure_ensure=5;
       side_servo_inching_configure_ensure=6;
       side_servo_error_resert_ensure=7;
       axis_servo_enable=8;
       axis_servo_RunStop=9;
       axis_servo_forward_point_run=10;
       axis_servo_negative_point_run=11;
       axis_servo_switch_direction=12;
       axis_servo_speed_configure_ensure=13;
       axis_servo_inching_configure_ensure=14;
       axis_servo_error_resert_ensure=15;
      //0x  coil status
       electromagnetic_valve=65-1;//电磁阀
       power_regulator=66-1;//电磁阀
       refrigerating_machine =67-1;//电磁阀
       mechanical_pump =68-1;//电磁阀
       cycle_pump=69-1;//电磁阀
       //4x
       axis_setspeed=3-1;//轴速度设置    范围：0.1--16.6mm/s
       axis_ACtime=5-1;  //轴加速时间设置 ms
       axis_DCtime=7-1;  //轴减速速时间设置 ms
       side_setspeed=11-1;//侧向速度设置    范围：0.1--16.6mm/s
       side_ACtime=13-1;  //侧向加速时间设置 ms
       side_DCtime=15-1;  //侧向减速速时间设置 ms
       axis_inchingspeed=19-1;    //轴点动速度
       axis_inchingincrement=21-1;//轴点动增量
       side_inchingspeed=23-1;    //侧点动速度
       side_inchingincrement=25-1;//侧点动增量
       step_setspeed=27-1;         //步进速度设置
       power_regulator_output=29-1;//调功器输出给定
    }
 } PLCADDRES;

  ///达到设定的加载力 停止运动  @target 设置超时 超时未达到则自动停止
  bool Run(MD_PLC::kServoFunc     /*电机1or电机2*/num,qreal  force);
  void setspeed(kServoFunc num,qreal speed,float /*加速时间ms*/act,float /*减速时间ms*/dct);
  bool checkRunstatus(kServoFunc num);
  bool checktendency(kServoFunc num,bool forward, qreal oldforce, qreal getforce);
  bool checklimit(kServoFunc num, bool forwardrun);
  bool checkthreshold(kServoFunc num, qreal dstforce, qreal getforce);
  bool checktgetarget(kServoFunc num, qreal force, qreal getforce);
  //40001-40002 存储在16位寄存器
  void hold2coils(int index,int/*1 or 0*/ data);
  void gethold16();
  PLCADDRES servoaddres;
  bool m_sidenegativelimit=false;
  bool m_sideforwardlimit=false;
  bool m_axisnegativelimit=false;
  bool m_axisforwardlimit=false;
  bool m_stepforwardlimit=false;
  bool m_stepnegativelimit=false;
  qreal m_temperatureS1=0;
  qreal m_temperatureS2=0;
  qreal m_temperatureK3=0;
  bool m_emergencyStop=false;
  QVector<int>  m_residualCycletimes={0,0};
  qreal m_axisforce=0;
  qreal m_sideforce=0;
  bool m_axisservoenable=false;
  bool m_sideservoenable=false;
  int m_axisRunstatus=0;
  int m_sideRunstatus=0;
  bool m_sideservobreakdown=false;
  bool m_axisservobreakdown=false;
  bool m_phaseorderprotection=false;
  ///侧向伺服正转点动
  bool side_servo_forward_inching_s=false;
  ///侧向伺服反转点动
  bool side_servo_negative_inching_s=false;
  ///侧向伺服方向切换
  bool m_side_run_direction=false;
  ///轴向伺服正转点动
  bool axis_servo_forward_inching_s=false;
  ///轴向伺服反转点动
  bool axis_servo_negative_inching_s=false;
  ///轴向伺服方向切换
  bool m_axis_run_direction=false;
  bool m_electromagnetic_valve_s=false;
  bool m_power_regulator_s=false;
  bool m_refrigerator_s=false;
  bool m_mechanical_pump_s=false;
  bool m_cycle_pump_s=false;
};

#endif // MD_PLC_H
