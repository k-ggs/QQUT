#include "serial.h"

Serial::Serial(int _baudrate,int _bits,int _parity,int _stopbits )

{
  setBaudrate(_baudrate);
  setBits(_bits);
  setParity(_parity);
  setStopbits(_stopbits);
  refreshPorts();
}

Serial::~Serial()
{
  sp_close(port);
 sp_free_port(port);
  delete readbits;
 }


int Serial::check(enum sp_return result)
{
  /* For this example we'll just exit on any error by calling abort(). */
  char *error_message;

  switch (result) {
    case SP_ERR_ARG:
      spdlog::info("Error: Invalid argument.");

    case SP_ERR_FAIL:
      error_message = sp_last_error_message();
      spdlog::info("Error: Failed: {0:s}", error_message);
      sp_free_error_message(error_message);

    case SP_ERR_SUPP:
      spdlog::info("Error: Not supported.");

    case SP_ERR_MEM:
      spdlog::info("Error: Couldn't allocate memory.");

    case SP_OK:
    default:
      return result;
  }
}

QStringList Serial::refreshPorts()
{
  sp_port **ports;
  int erro_=sp_list_ports(&ports);
  QStringList list;
  if(erro_!=0)
  { spdlog::error("获取端口数错误： %d",erro_);return list;}
        /* Iterate through the ports. When port_list[i] is NULL
         * this indicates the end of the list. */
        int i;
        for (i = 0; ports[i] != NULL; i++) {
                struct sp_port *port = ports[i];

                /* Get the name of the port. */
                char *port_name = sp_get_port_name(port);
                list<<port_name;
                spdlog::info("Found port: {0:s}", port_name);
        }

        spdlog::info("Found {0:d} ports.", i);

        spdlog::info("Freeing port list.");

        /* Free the array created by sp_list_ports(). */
        sp_free_port_list(ports);

        /* Note that this will also free all the sp_port structures
         * it points to. If you want to keep one of them (e.g. to
         * use that port in the rest of your program), take a copy
         * of it first using sp_copy_port(). */
        return list;
 }

bool Serial::serial_open(QString portName)
{
   sp_get_port_by_name(portName.toStdString().data(),&port);
  /* Display some basic information about the port. */
   spdlog::info("Port name: {:s}", sp_get_port_name(port));
   spdlog::info("Description:{:s}", sp_get_port_description(port));

  /* The port must be open to access its configuration. */
  spdlog::info("Opening port.");
   bool opened= check(sp_open(port, SP_MODE_READ_WRITE)) ==0;
  setConnected(opened);
   if(opened){
    check(sp_set_baudrate(port, baudrate()));
    check(sp_set_bits(port, bits()));
    check(sp_set_parity(port, sp_parity(parity())));
    check(sp_set_stopbits(port, stopbits()));
    check(sp_set_flowcontrol(port, SP_FLOWCONTROL_NONE));
    }
return opened;
}

bool Serial::serial_close()
{
  bool closed= check( sp_close(port))==0;
  setConnected(!closed);
  return closed;
}

int Serial::serial_write(const QByteArray bits,int timeout)
{
 return check( sp_blocking_write(port,bits.data(),bits.size(),timeout));
}

QByteArray Serial::serial_read(const QByteArray bits,size_t size,int timeout)
{
  if(bits.size()>1){serial_write(bits,timeout);}
  if(readbits!=nullptr){free(readbits);}
  readbits =(char*)malloc(sizeof(char)*size);
  size_t readsize;


  if(timeout>0){
  readsize=  check( sp_blocking_read(port,readbits,size,timeout));
  }else{

  readsize=   check( sp_blocking_read_next(port,readbits,size,200));
  }
//  char * dread=(char*)malloc(sizeof(char)*readsize);
//  memcpy(dread,readbits,readsize);
 // QByteArray read(dread);//深拷贝
 // free(dread);
 // free(readbits);

   QByteArray read(readbits,readsize);
   spdlog::info("{0:p}",readbits);

   return read;
}





bool Serial::connected() const
{
  return m_connected;
}

void Serial::setConnected(bool newConnected)
{
  if (m_connected == newConnected)
    return;
  m_connected = newConnected;
  emit connectedChanged();
}

const QStringList &Serial::portNames() const
{
  return m_portNames;
}

void Serial::setPortNames(const QStringList &newPortNames)
{
  if (m_portNames == newPortNames)
    return;
  m_portNames = newPortNames;
  emit portNamesChanged();
}

int Serial::baudrate() const
{
  return m_baudrate;
}

void Serial::setBaudrate(int newBaudrate)
{
  if (m_baudrate == newBaudrate)
    return;
  m_baudrate = newBaudrate;
  emit baudrateChanged();
}

int Serial::bits() const
{
  return m_bits;
}

void Serial::setBits(int newBits)
{
  if (m_bits == newBits)
    return;
  m_bits = newBits;
  emit bitsChanged();
}

int Serial::parity() const
{
  return m_parity;
}

void Serial::setParity(int newParity)
{
  if (m_parity == newParity)
    return;
  m_parity = newParity;
  emit parityChanged();
}

int Serial::stopbits() const
{
  return m_stopbits;
}

void Serial::setStopbits(int newStopbits)
{
  if (m_stopbits == newStopbits)
    return;
  m_stopbits = newStopbits;
  emit stopbitsChanged();
}
