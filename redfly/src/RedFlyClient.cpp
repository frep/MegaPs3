#ifdef __cplusplus
extern "C" {
#endif
  #include <inttypes.h>
  #include <avr/pgmspace.h>
#ifdef __cplusplus
}
#endif
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "RedFly.h"
#include "RedFlyServer.h"
#include "RedFlyClient.h"


#define MAX_ERRORS (10)


//-------------------- Constructor --------------------


RedFlyClient::RedFlyClient(void) : c_lport(0), c_socket(INVALID_SOCKET)
{
  return;
}


RedFlyClient::RedFlyClient(uint8_t socket) : c_lport(0), c_socket(socket)
{
  return;
}


RedFlyClient::RedFlyClient(uint8_t *ip, uint16_t port)
{
  c_ip[0]  = ip[0];
  c_ip[1]  = ip[1];
  c_ip[2]  = ip[2];
  c_ip[3]  = ip[3];
  c_port   = port;
  c_socket = INVALID_SOCKET;

  return;
}


RedFlyClient::RedFlyClient(uint8_t *ip, uint16_t port, uint16_t lport)
{
  c_ip[0]  = ip[0];
  c_ip[1]  = ip[1];
  c_ip[2]  = ip[2];
  c_ip[3]  = ip[3];
  c_port   = port;
  c_lport  = lport;
  c_socket = INVALID_SOCKET;

  return;
}


//-------------------- Public --------------------


void RedFlyClient::begin(void)
{
  connect();

  return;
}


int RedFlyClient::connect(void)
{
  if(c_socket != INVALID_SOCKET)
  {
    return 0;
  }

  if(c_lport)
  {
    c_socket = RedFly.socketConnect(PROTO_TCP, c_ip, c_port, c_lport);
  }
  else
  {
    c_socket = RedFly.socketConnect(PROTO_TCP, c_ip, c_port);
  }

  if(c_socket == INVALID_SOCKET)
  {
    return 0;
  }

  error = 0;

  return 1;
}


int RedFlyClient::connect(uint8_t *ip, uint16_t port)
{
  c_ip[0] = ip[0];
  c_ip[1] = ip[1];
  c_ip[2] = ip[2];
  c_ip[3] = ip[3];
  c_port  = port;

  return connect();
}


int RedFlyClient::connect(uint8_t *ip, uint16_t port, uint16_t lport)
{
  c_ip[0] = ip[0];
  c_ip[1] = ip[1];
  c_ip[2] = ip[2];
  c_ip[3] = ip[3];
  c_port  = port;
  c_lport = lport;

  return connect();
}


int RedFlyClient::connect(char *host, uint16_t port)
{
  if(RedFly.getip(host, c_ip) == 0)
  {
    c_port  = port;
    return connect();
  }

  return 0;
}


uint8_t RedFlyClient::connected(void)
{
  if(c_socket == INVALID_SOCKET)
  {
    return 0;
  }

  if(RedFly.socketClosed(c_socket)) //socket closed?
  {
    c_socket = INVALID_SOCKET;
    return 0;
  }

  if(error >= MAX_ERRORS)
  {
    RedFly.socketClose(c_socket);
    c_socket = INVALID_SOCKET;
    return 0;
  }

  return 1;
}


void RedFlyClient::stop(void)
{
  if(c_socket == INVALID_SOCKET)
  {
    return;
  }

  flush(); //clear buffer

  RedFly.socketClose(c_socket);
  c_socket = INVALID_SOCKET;
  error    = 0;

  return;
}


uint8_t RedFlyClient::status(void)
{
  if(c_socket == INVALID_SOCKET)
  {
    return 1;
  }

  if(RedFly.socketStatus(c_socket)) //socket closed?
  {
    c_socket = INVALID_SOCKET;
    return 1;
  }

  return 0;
}


uint8_t RedFlyClient::getSocket(void)
{
  return c_socket;
}


int RedFlyClient::available(void)
{
  uint8_t socket=c_socket;
  uint16_t len=0;

  if(socket != INVALID_SOCKET)
  {
    RedFly.socketRead(&socket, &len, 0, 0);
  }

  return (int)len;
}


int RedFlyClient::read(void)
{
  uint8_t b;
  uint8_t socket=c_socket;
  uint16_t len, read;

  if(socket == INVALID_SOCKET)
  {
    return -1;
  }

  read = RedFly.socketRead(&socket, &len, &b, 1);

  if(read == 0)
  {
    return -1;
  }
  if(read == 0xFFFF) //socket closed?
  {
    c_socket = INVALID_SOCKET;
    return -1;
  }
 
  return b;
}


int RedFlyClient::read(uint8_t *s, size_t size)
{
  uint8_t socket=c_socket;
  uint16_t len, read;

  if(socket == INVALID_SOCKET)
  {
    return 0;
  }

  read = RedFly.socketRead(&socket, &len, s, size);
  if(read == 0xFFFF) //socket closed?
  {
    c_socket = INVALID_SOCKET;
    read = 0;
  }

  return read;
}


void RedFlyClient::flush(void)
{
  uint16_t len = available();

  while(len)
  {
    read();
    len--;
  }

  return;
}


size_t RedFlyClient::write(uint8_t b)
{
  if(c_socket != INVALID_SOCKET)
  {
    if(RedFly.socketSend(c_socket, (uint8_t*)&b, 1))
    {
      if(++error >= MAX_ERRORS)
      {
        RedFly.socketClose(c_socket);
        c_socket = INVALID_SOCKET;
      }
    }
    else
    {
      error = 0;
      return 1;
    }
  }

  return 0;
}


size_t RedFlyClient::write(const char *s)
{
  if(c_socket != INVALID_SOCKET)
  {
    if(RedFly.socketSend(c_socket, (char*)s))
    {
      if(++error >= MAX_ERRORS)
      {
        RedFly.socketClose(c_socket);
        c_socket = INVALID_SOCKET;
      }
    }
    else
    {
      error = 0;
      return strlen(s);
    }
  }

  return 0;
}


size_t RedFlyClient::write(const uint8_t *s, size_t size)
{
  if(c_socket != INVALID_SOCKET)
  {
    if(RedFly.socketSend(c_socket, (uint8_t*)s, size))
    {
      if(++error >= MAX_ERRORS)
      {
        RedFly.socketClose(c_socket);
        c_socket = INVALID_SOCKET;
      }
    }
    else
    {
      error = 0;
      return size;
    }
  }

  return 0;
}


size_t RedFlyClient::print_P(PGM_P s)
{
  if(c_socket != INVALID_SOCKET)
  {
    if(RedFly.socketSendPGM(c_socket, s))
    {
      if(++error >= MAX_ERRORS)
      {
        RedFly.socketClose(c_socket);
        c_socket = INVALID_SOCKET;
      }
    }
    else
    {
      error = 0;
      return strlen_P(s);
    }
  }

  return 0;
}


size_t RedFlyClient::println_P(PGM_P s)
{
  if(c_socket != INVALID_SOCKET)
  {
    if(RedFly.socketSendPGM(c_socket, s))
    {
      if(++error >= MAX_ERRORS)
      {
        RedFly.socketClose(c_socket);
        c_socket = INVALID_SOCKET;
      }
    }
    else
    {
      RedFly.socketSendPGM(c_socket, PSTR("\r\n"));
      error = 0;
      return strlen_P(s) + 2;
    }
  }

  return 0;
}


//the next function allows us to use the client returned by
//RedFlyServer::available() as the condition in an if-statement.
RedFlyClient::operator bool()
{
  return c_socket != INVALID_SOCKET;
}
