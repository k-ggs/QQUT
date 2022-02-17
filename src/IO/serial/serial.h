#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include<spdlog/spdlog.h>
#include"libserialport.h"
#include<QDebug>
class Serial : public QObject
{
  Q_OBJECT

  Q_PROPERTY(bool connected READ connected WRITE setConnected NOTIFY connectedChanged)
      Q_PROPERTY(QStringList portNames READ portNames WRITE setPortNames NOTIFY portNamesChanged)


      Q_PROPERTY(int baudrate READ baudrate WRITE setBaudrate NOTIFY baudrateChanged)
      Q_PROPERTY(int bits READ bits WRITE setBits NOTIFY bitsChanged)
      Q_PROPERTY(int parity READ parity WRITE setParity NOTIFY parityChanged)
      Q_PROPERTY(int stopbits READ stopbits WRITE setStopbits NOTIFY stopbitsChanged)

      public:
        Serial(int _baudrate=9600,int _bits=8,int _parity=0,int _stopbits=1  );
       ~Serial();

      ///获取端口列表
  Q_INVOKABLE QStringList refreshPorts();
  Q_INVOKABLE bool serial_open(QString portName);
  Q_INVOKABLE bool serial_close();
  Q_INVOKABLE int  serial_write(const QByteArray bits,int timeout);

  /**
   * @brief serial_read 1.读到立即返回 maxsize 2.一直达到指定size
   * @param bits          1.写入  size>0  写读  否则 只读
   * @param size
   * @param timeout
   * @return
   */
  Q_INVOKABLE QByteArray serial_read(const QByteArray bits,size_t size,int timeout);





  bool connected() const;


  const QStringList &portNames() const;

  /* Helper function for error handling. */
  int check(enum sp_return result);
  int baudrate() const;


  int bits() const;


  int parity() const;


  int stopbits() const;


 public Q_SLOTS:

  void setPortNames(const QStringList &newPortNames);
  void setConnected(bool newConnected);
  void setBaudrate(int newBaudrate);
  void setBits(int newBits);
  void setParity(int newParity);
  void setStopbits(int newStopbits);
 Q_SIGNALS:

  void connectedChanged();

  void portNamesChanged();

  void baudrateChanged();

  void bitsChanged();

  void parityChanged();

  void stopbitsChanged();

 private:

  sp_port *port;//串口号等
 // sp_port_config *sp_port_config;//波特率...


  QString m_portName="COM1";
  bool m_connected=false;
  QStringList m_portNames;
  int m_baudrate=9600;
  int m_bits=8;
  int m_parity=0;
  int m_stopbits=1;
 private:
  char  *readbits=nullptr;

};

#endif // SERIAL_H
