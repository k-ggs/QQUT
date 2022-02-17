#include "datamap.h"

datamap::datamap(token t)
{
  connect(&Uitimer,&QTimer::timeout,this,&datamap::uiUpdate);
  Uitimer.start(60);
}
datamap::~datamap()
{
}
void datamap::DataSave()
{
 if(side_data_.size()<1){return;}
 QString path= Misc::Utilities::getDir();
 QString PLC_path   =path+"/" +QDateTime::currentDateTime().toString("PLCYYMMDDhhmm")   +".csv";
 QString Serial_path=path+"/" +QDateTime::currentDateTime().toString("SerialYYMMDDhhmm")+".csv";
 //PLC
 QFile Plcfile(PLC_path);
 if(!Plcfile.open(QFile::WriteOnly)){return;}
 QTextStream PLCstream(&Plcfile);
 PLCstream<<QString::fromLocal8Bit("时间(ms)")<<","
          <<QString::fromLocal8Bit("轴向加载力(KG)")<<","
          <<QString::fromLocal8Bit("侧向加载力(KG)")<<","
          <<QString::fromLocal8Bit("温度1S型热电偶(℃)")<<","
          <<QString::fromLocal8Bit("温度2S型热电偶(℃)")<<","
          <<QString::fromLocal8Bit("温度3K型热电偶(℃)")<<"\n";

 for(int i=0;i<side_data_.size();i++){
PLCstream<<QString::number(plct[i])<<","
         <<QString::number(axis_data_[i])<<","
         <<QString::number(side_data_[i])<<","
         <<QString::number(temp1_[i])<<","
         <<QString::number(temp2_[i])<<","
         <<QString::number(temp3_[i])<<"\n";
 }
 Plcfile.close();
 ///串口
 QFile Serialfile(Serial_path);
 if(!Serialfile.open(QFile::WriteOnly)){return;}
 QTextStream Serialstream(&Serialfile);
 Serialstream<<QString::fromLocal8Bit("时间(ms)")<<","
     <<QString::fromLocal8Bit("真空计(℃)")<<","
     <<QString::fromLocal8Bit("红外温度计(℃)")<<"\n";

 for(int i=0;i<side_data_.size();i++){
   Serialstream<<QString::number(serialt[i])<<","
             <<QString::number(vacuum_gauge_data_[i])<<","
             <<QString::number(infrared_temp_data_[i])<<"\n";
 }
 Serialfile.close();
 clearMap();
}


void datamap::plcappend(qreal axisforce,qreal side_force,
                        qreal temp1,qreal temp2,qreal temp3)
{ static QTime startTime=QTime::currentTime();
  static int tm=0;
  if(side_data_.size()<1){startTime= QTime::currentTime();tm=0;}
  QTime endtime=QTime::currentTime();
  int tms=startTime.msecsTo(endtime);//ms间隔
  tm+=tms;//
  plct<<tm;
  startTime=endtime;
  axis_data_<<side_force;
  side_data_<<side_force;
  temp1_<<temp1;
  temp2_<<temp2;
  temp3_<<temp3;
}
void datamap::serialappend(qreal vacuum_gauge,qreal infrared_temp )
{
  static QTime startTime=QTime::currentTime();
  static int tm=0;
  if(side_data_.size()<1){startTime= QTime::currentTime();tm=0;}
  QTime endtime=QTime::currentTime();
  int tms=startTime.msecsTo(endtime);//ms间隔
  tm+=tms;//
  serialt<<tm;
  startTime=endtime;
  vacuum_gauge_data_.insert(tm,vacuum_gauge);
  infrared_temp_data_.insert(tm,infrared_temp);
}
void datamap::clearMap()
{  side_data_.clear();
   axis_data_.clear();
   temp1_.clear();
   temp2_.clear();
   temp3_.clear();
   vacuum_gauge_data_.clear();
   infrared_temp_data_.clear();
   serialt.clear();
   plct.clear();
   emit cleared();
}
void datamap::uiUpdate()
{
  if(side_data_.size()>1){count++;}else{return;}
    QVariantList dat;
    dat<<plct[count];
    dat<<axis_data_[count];
    dat<<side_data_[count];
    dat<<temp1_[count];
    dat<<temp2_[count];
    dat<<temp3_[count];
    if(serialt.size()>1){
      dat<<serialt[count];
    }else{

    }

}


const QVariantList &datamap::plcUidata() const
{
  return m_plcUidata;
}

void datamap::setPlcUidata(const QVariantList &newPlcUidata)
{
  if (m_plcUidata == newPlcUidata)
    return;
  m_plcUidata = newPlcUidata;
  emit plcUidataChanged();
}

const QVariantList &datamap::serialUidata() const
{
  return m_serialUidata;
}

void datamap::setSerialUidata(const QVariantList &newSerialUidata)
{
  if (m_serialUidata == newSerialUidata)
    return;
  m_serialUidata = newSerialUidata;
  emit serialUidataChanged();
}
