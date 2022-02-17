#include "modbusrtu.h"


modbusRTU::modbusRTU(QString port,int _baudrate,int _bits,QChar _parity,int _stopbits){
  portname_=port;
  setBaudrate(_baudrate);
  setBits(_bits);
  setParity(_parity);
  setStopbits(_stopbits);
  rtu=modbus_new_rtu(portname_.toStdString().data(),baudrate(),parity().toLatin1(),bits(),stopbits());
  MD_init(rtu);
}
modbusRTU::~modbusRTU()
{
}
const QStringList &modbusRTU::portNames() const
{
  return m_portNames;
}
void modbusRTU::setPortNames(const QStringList &newPortNames)
{
  if (m_portNames == newPortNames)
    return;
  m_portNames = newPortNames;
  emit portNamesChanged();
}
int modbusRTU::baudrate() const
{
  return m_baudrate;
}
void modbusRTU::setBaudrate(int newBaudrate)
{
  if (m_baudrate == newBaudrate)
    return;
  m_baudrate = newBaudrate;
  emit baudrateChanged();
}
int modbusRTU::bits() const
{
  return m_bits;
}
void modbusRTU::setBits(int newBits)
{
  if (m_bits == newBits)
    return;
  m_bits = newBits;
  emit bitsChanged();
}
int modbusRTU::stopbits() const
{
  return m_stopbits;
}
void modbusRTU::setStopbits(int newStopbits)
{
  if (m_stopbits == newStopbits)
    return;
  m_stopbits = newStopbits;
  emit stopbitsChanged();
}
const QChar &modbusRTU::parity() const
{
    return m_parity;
}
void modbusRTU::setParity(const QChar &newParity)
{
  if (m_parity == newParity)
        return;
    m_parity = newParity;
    emit parityChanged();
}
