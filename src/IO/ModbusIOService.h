#ifndef ModbusIOService_H
#define ModbusIOService_H

#include<QObject>
#include<modbus.h>
#include<thread>
#include"spdlog/spdlog.h"
class ModbusIOService:public QObject{

  Q_OBJECT
  Q_PROPERTY(bool connected READ connected WRITE setConnected NOTIFY connectedChanged)
  Q_PROPERTY(QString errorString READ errorString WRITE setErrorString NOTIFY errorStringChanged)



 public:
 ModbusIOService();
 void MD_init(modbus_t* mod=nullptr);
 virtual ~ModbusIOService();//基类虚函数 基类引用派生类对象 销毁时 析构虚表指向派生类类型 派生类析构->基类析构
 Q_INVOKABLE  bool mD_connect();
 Q_INVOKABLE  void mD_close();
 ///发生错误 断开重连  所有情况
 Q_INVOKABLE  void mD_reconnect();
 Q_INVOKABLE  int mD_read_bits(int slave, int addr, int nb, uint8_t *dest);
 Q_INVOKABLE  int mD_read_input_bits(int slave, int addr, int nb, uint8_t *dest);
 Q_INVOKABLE  int mD_read_registers(int slave, int addr, int nb, uint16_t *dest);
 Q_INVOKABLE  int mD_read_input_registers(int slave, int addr, int nb, uint16_t *dest);

 Q_INVOKABLE  int    mD_debug(bool dbg);
 ///modbus.c 188 if ((errno == EBADF || errno == ECONNRESET || errno == EPIPE))
 /// linmodbus EBADF ECONNRESET EPIPE 三种情况  0 2 4
 Q_INVOKABLE  int    mD_recover_mod(modbus_error_recovery_mode recovermod);
 Q_INVOKABLE  int    mD_write_bit(int slave, int addr, int status);
 Q_INVOKABLE  int    mD_write_bits(int slave, int addr, int nb, const uint8_t *src);
 Q_INVOKABLE  int    mD_write_register(int slave, int addr, const uint16_t value);
 Q_INVOKABLE  int    mD_write_registers(int slave, int addr, int nb, const uint16_t *src);

 ///获取错误信息 和 (recovery mod)未知错误重连
 Q_INVOKABLE  QString  mD_error_print( int errnum);


 Q_INVOKABLE   bool   mD_set_response_timeout(int ms);
 Q_INVOKABLE   bool   mD_set_byte_timeout(int ms);
 Q_INVOKABLE   bool   mD_set_indication_timeout(int ms);
private:

 ///一些额外的错误 输出
 modbus_t * modbus=nullptr;

 int response_timeout_=150;
 int byte_timeout_=0;
 int indication_timeout_=0;


 bool m_connected=false;
 QString m_errorString;

signals:
 void connectedChanged();
 void errorStringChanged();

public Q_SLOTS:
 void setConnected(bool newConnected);
 void setErrorString(const QString &newErrorString);
public:
 bool connected() const;
 const QString &errorString() const;

};

#endif // ModbusIOService_H
