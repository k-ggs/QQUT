#include "md485read.h"



MD485Read::MD485Read(QString port):modbusRTU(port)
{

}

MD485Read::~MD485Read()
{
  getdata=false;
}

qreal MD485Read::getvacuumdata(const char *cmd,size_t t)
{
  return 0.0;
}

qreal MD485Read::getinfraredTEMPdata(const char *cmd,size_t t)
{
return 0.0;
}

qreal MD485Read::infraredTEMPdata() const
{
  return m_infraredTEMPdata;
}

void MD485Read::setInfraredTEMPdata(qreal newInfraredTEMPdata)
{
  if (qFuzzyCompare(m_infraredTEMPdata, newInfraredTEMPdata))
    return;
  m_infraredTEMPdata = newInfraredTEMPdata;
  emit infraredTEMPdataChanged();
}

qreal MD485Read::vacuumdata() const
{
  return m_vacuumdata;
}

void MD485Read::setVacuumdata(qreal newVacuumdata)
{
  if (qFuzzyCompare(m_vacuumdata, newVacuumdata))
    return;
  m_vacuumdata = newVacuumdata;
  emit vacuumdataChanged();
}

void MD485Read::asyncGetdata()
{std::thread td([&](){


    while(getdata){


      if(!connected()){

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        continue;
      }else{

        getvacuumdata(&vacuumdata_cmd_[0],sizeof (vacuumdata_cmd_));
        getinfraredTEMPdata(&infraredTEMPdata_cmd_[0],sizeof (infraredTEMPdata_cmd_));
      }
    }
  });
  td.detach();
}
