#include"ModbusIOService.h"

     ModbusIOService::ModbusIOService()
{

}

void ModbusIOService::MD_init(modbus_t *mod)
{
 modbus=mod;
}

ModbusIOService::~ModbusIOService()
{
  if(modbus!=nullptr){

    modbus_close(modbus);
    modbus_free(modbus);
  }
  setConnected(false);
}

bool ModbusIOService::mD_connect()
{

  bool connected= modbus_connect(modbus)==0;

  setConnected(connected);
  return connected;
}

void ModbusIOService::mD_close()
{
  modbus_close(modbus);
  setConnected(false);
}

void ModbusIOService::mD_reconnect()
{
  setConnected(false);
  modbus_close(modbus);
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  if(modbus_connect(modbus)==0) {
    setConnected(true);
  }
}

int  ModbusIOService::mD_read_bits(int slave, int addr, int nb, uint8_t *dest)
{
  int rt =modbus_set_slave(modbus,slave);
  if( rt==-1){
    rt= GetLastError();
    mD_error_print(rt);
    return rt;
  }
  rt=modbus_read_bits(modbus,addr,nb,dest);
  if( rt==-1){
    rt= GetLastError();
    mD_error_print(rt);
  }
  return rt;
}

int  ModbusIOService::mD_read_input_bits(int slave, int addr, int nb, uint8_t *dest)
{
  int rt =modbus_set_slave(modbus,slave);
  if( rt==-1){
    rt= GetLastError();
    mD_error_print(rt);
    return rt;
  }
  rt=modbus_read_input_bits(modbus,addr,nb,dest);
  if( rt==-1){
    rt= GetLastError();
  mD_error_print(rt);
  }
  return rt;
}

int  ModbusIOService::mD_read_registers(int slave, int addr, int nb, uint16_t *dest)
{
  int rt =modbus_set_slave(modbus,slave);
  if( rt==-1){
    rt= GetLastError();
    mD_error_print(rt);
    return rt;
  }
  rt=modbus_read_registers(modbus,addr,nb,dest);
  if( rt==-1){
    rt= GetLastError();
    mD_error_print(rt);
  }
  return rt;
}

int  ModbusIOService::mD_read_input_registers(int slave, int addr, int nb, uint16_t *dest)
{
  int rt =modbus_set_slave(modbus,slave);
  if( rt==-1){
    rt= GetLastError();
    mD_error_print(rt);
    return rt;
  }
  rt=modbus_read_input_registers(modbus,addr,nb,dest);
  if( rt==-1){
    rt= GetLastError();
    mD_error_print(rt);
  }
  return rt;
}

int  ModbusIOService::mD_debug(bool dbg)
{
  int rt =modbus_set_debug(modbus,dbg==true?1:0);
  if( rt==-1){
    rt= GetLastError();


  }
  return rt;
}

int  ModbusIOService::mD_recover_mod(modbus_error_recovery_mode recovermod)
{
  int rt =modbus_set_error_recovery(modbus,recovermod);
  if( rt==-1){
    rt= GetLastError();

  }
  return rt;
}

int  ModbusIOService::mD_write_bit(int slave, int addr, int status)
{
  int rt =modbus_set_slave(modbus,slave);
  if( rt==-1){
    rt= GetLastError();
     mD_error_print(rt);
    return rt;
  } rt=modbus_write_bit(modbus,addr,status);
  if( rt==-1){
    rt= GetLastError();
    mD_error_print(rt);
  }
  return rt;
}

int  ModbusIOService::mD_write_bits(int slave, int addr, int nb, const uint8_t *src)
{
  int rt =modbus_set_slave(modbus,slave);
  if( rt==-1){
    rt= GetLastError();
     mD_error_print(rt);
    return rt;
  } rt=modbus_write_bits(modbus,addr,nb,src);
  if( rt==-1){
    rt= GetLastError();
    mD_error_print(rt);
  }
  return rt;
}

int  ModbusIOService::mD_write_register(int slave, int addr, const uint16_t value)
{
  int rt =modbus_set_slave(modbus,slave);
  if( rt==-1){
    rt= GetLastError();
     mD_error_print(rt);
    return rt;
  } rt=modbus_write_register(modbus,addr,value);
  if( rt==-1){
    rt= GetLastError();
    mD_error_print(rt);
  }
  return rt;
}

int  ModbusIOService::mD_write_registers(int slave, int addr, int nb, const uint16_t *src)
{
  int rt =modbus_set_slave(modbus,slave);
  if( rt==-1){
    rt= GetLastError();
     mD_error_print(rt);
    return rt;
  } rt=modbus_write_registers(modbus,addr,nb,src);
  if( rt==-1){
    rt= GetLastError();
     mD_error_print(rt);
  }
  return rt;
}



QString ModbusIOService::mD_error_print( int errnum)
{
  switch (errnum) {
    case EMBXILFUN:
      setErrorString("Illegal function");
      return "Illegal function";
    case EMBXILADD:
       setErrorString("Illegal data address");
      return "Illegal data address";
    case EMBXILVAL:
       setErrorString("Illegal data value");
      return "Illegal data value";
    case EMBXSFAIL:
       setErrorString("Slave device or server failure");
      return "Slave device or server failure";
    case EMBXACK:
       setErrorString("Acknowledge");
      return "Acknowledge";
    case EMBXSBUSY:
       setErrorString("Slave device or server is busy");
      return "Slave device or server is busy";
    case EMBXNACK:
       setErrorString("Negative acknowledge");
      return "Negative acknowledge";
    case EMBXMEMPAR:
       setErrorString("Memory parity error");
      return "Memory parity error";
    case EMBXGPATH:
       setErrorString("Gateway path unavailable");
      return "Gateway path unavailable";
    case EMBXGTAR:
       setErrorString("Target device failed to respond");
      return "Target device failed to respond";
    case EMBBADCRC:
       setErrorString("Invalid CRC");
      return "Invalid CRC";
    case EMBBADDATA:
       setErrorString("Invalid data");
      return "Invalid data";
    case EMBBADEXC:
       setErrorString("Invalid exception code");
      return "Invalid exception code";
    case EMBMDATA:
       setErrorString("Too many data");
      return "Too many data";
    case EMBBADSLAVE:
       setErrorString("Response not from requested slave");
      return "Response not from requested slave";
    default:
      QString msg=strerror(errnum)+QString("NUM:")+QString::number(errnum);
      setErrorString(msg);
      //mD_reconnect();//其它错误则重连
      return msg;
  }
}

bool ModbusIOService::mD_set_response_timeout(int ms)
{

          response_timeout_=ms;
          return modbus_set_response_timeout(modbus,0,ms*1000)==0;


}

bool ModbusIOService::mD_set_byte_timeout(int ms)
{       response_timeout_=ms;
        return modbus_set_byte_timeout(modbus,0,ms*1000)==0;
}

bool ModbusIOService::mD_set_indication_timeout(int ms)
{        indication_timeout_=ms;
         return modbus_set_indication_timeout(modbus,0,ms*1000)==0;
}
/**
 *property
 * */
////
bool ModbusIOService::connected() const
{
  return m_connected;
}

void ModbusIOService::setConnected(bool newConnected)
{
  if (m_connected == newConnected)
    return;
  m_connected = newConnected;
  emit connectedChanged();
}

const QString &ModbusIOService::errorString() const
{
  return m_errorString;
}
void ModbusIOService::setErrorString(const QString &newErrorString)
{
  if (m_errorString == newErrorString)
    return;
  m_errorString = newErrorString;
  spdlog::info("mdbuserror:{}",m_errorString.toStdString());
  emit errorStringChanged();
}
