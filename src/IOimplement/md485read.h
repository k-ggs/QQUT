#ifndef MD485READ_H
#define MD485READ_H

#include<QObject>
#include"modbusrtu.h"
#include<atomic>
#include<thread>
#include "Singleton.h"
class MD485Read : public modbusRTU
{
  Q_OBJECT
  Q_PROPERTY(qreal vacuumdata READ vacuumdata WRITE setVacuumdata NOTIFY vacuumdataChanged)
  Q_PROPERTY(qreal infraredTEMPdata READ infraredTEMPdata WRITE setInfraredTEMPdata NOTIFY infraredTEMPdataChanged)

  public:
   MD485Read(QString port);
   ~MD485Read();

  ///获取真空计值 单位pa
  Q_INVOKABLE qreal getvacuumdata(const char *cmd,size_t t);

  ///获取红外温度值 单位摄氏度
  Q_INVOKABLE qreal getinfraredTEMPdata(const char *cmd,size_t t);


  qreal infraredTEMPdata() const;

  qreal vacuumdata() const;


 public Q_SLOTS:

  void setInfraredTEMPdata(qreal newInfraredTEMPdata);
  void setVacuumdata(qreal newVacuumdata);
 signals:

  void infraredTEMPdataChanged();

  void vacuumdataChanged();

 private:

  qreal m_infraredTEMPdata=0;
  qreal m_vacuumdata=0;
  std::atomic_bool getdata=true;
 private:
  const char  vacuumdata_cmd_[6]  ={22,33,44,55,66,77};
  const char  infraredTEMPdata_cmd_[6]={12,13,14,15,16,17};
  void asyncGetdata();
};

#endif // MD485READ_H
