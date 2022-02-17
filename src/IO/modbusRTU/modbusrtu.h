#ifndef MODBUSRTU_H
#define MODBUSRTU_H

#include <QObject>
#include<spdlog/spdlog.h>
#include"modbus-rtu.h"
#include"ModbusIOService.h"
class modbusRTU: public ModbusIOService
{  Q_OBJECT
  Q_PROPERTY(QStringList portNames READ portNames WRITE setPortNames NOTIFY portNamesChanged)
  Q_PROPERTY(int baudrate READ baudrate WRITE setBaudrate NOTIFY baudrateChanged)
  Q_PROPERTY(int bits READ bits WRITE setBits NOTIFY bitsChanged)  /* Parity: 'N', 'O', 'E' */
  Q_PROPERTY(QChar parity READ parity WRITE setParity NOTIFY parityChanged)
  Q_PROPERTY(int stopbits READ stopbits WRITE setStopbits NOTIFY stopbitsChanged)
 public:
  modbusRTU(QString port="COM3",int _baudrate=9600,int _bits=8,QChar _parity='N',int _stopbits=1);
  virtual ~ modbusRTU();
  const QStringList &portNames() const;
  void setPortNames(const QStringList &newPortNames);
  int baudrate() const;
  void setBaudrate(int newBaudrate);
  int bits() const;
  void setBits(int newBits);
  int stopbits() const;
  void setStopbits(int newStopbits);
  const QChar &parity() const;
  void setParity(const QChar &newParity);
  public Q_SLOTS:

 Q_SIGNALS:
  void portNamesChanged();
  void baudrateChanged();
  void bitsChanged();
  void stopbitsChanged();
  void parityChanged();
private:
  QStringList m_portNames;
  QString portname_="COM3";
  int m_baudrate;
  int m_bits;
  int m_stopbits;
  modbus_t *rtu;
  // ModbusIOService interface
  QChar m_parity;
};

#endif // MODBUSRTU_H
