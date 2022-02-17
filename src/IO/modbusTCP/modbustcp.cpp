#include "modbustcp.h"

modbusTCP::modbusTCP()

{

}

modbusTCP::~modbusTCP()
{

}
///初始化tcp连接
void modbusTCP::mdbustcpinit(QString ipaddress, int port)
{
  if(tcp==nullptr){
    tcp=modbus_new_tcp(ipaddress.toStdString().data(),port);
    MD_init(tcp);
  }else{

    modbus_close(tcp);
    modbus_free(tcp);
    tcp=modbus_new_tcp(ipaddress.toStdString().data(),port);
    MD_init(tcp);
  }
  modbus_set_error_recovery(tcp,modbus_error_recovery_mode::MODBUS_ERROR_RECOVERY_PROTOCOL);
   modbus_set_debug(tcp,0);
  setIpaddress(ipaddress);
  setPort(port);
}


int modbusTCP::port() const
{
  return m_port;
}

void modbusTCP::setPort(int newPort)
{
  if (m_port == newPort)
    return;
  m_port = newPort;
  emit portChanged();
}

const QString &modbusTCP::ipaddress() const
{
  return m_ipaddress;
}

void modbusTCP::setIpaddress(const QString &newIpaddress)
{
  if (m_ipaddress == newIpaddress)
    return;
  m_ipaddress = newIpaddress;
  emit ipaddressChanged();
}




