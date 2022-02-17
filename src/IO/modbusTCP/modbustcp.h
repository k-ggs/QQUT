#ifndef MODBUSTCP_H
#define MODBUSTCP_H

#include <QObject>
#include<spdlog/spdlog.h>
#include"modbus-tcp.h"
#include"ModbusIOService.h"
class modbusTCP : public ModbusIOService
{
  Q_OBJECT
  Q_PROPERTY(QString ipaddress READ ipaddress WRITE setIpaddress NOTIFY ipaddressChanged)
  Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)
  public:
  modbusTCP();
  virtual ~modbusTCP();
  Q_INVOKABLE  void  mdbustcpinit(QString ipaddress="127.0.0.1",int port=502);
  int port() const;
  const QString &ipaddress() const;

 public Q_SLOTS:
  void setIpaddress(const QString &newIpaddress);
  void setPort(int newPort);

 Q_SIGNALS:
  void portChanged();
  void ipaddressChanged();

private:
  modbus_t *tcp=nullptr;
  int m_port=502;
  QString m_ipaddress="127.0.0.1";
};

#endif // MODBUSTCP_H
