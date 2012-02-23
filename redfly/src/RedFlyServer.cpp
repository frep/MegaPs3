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
#include "RedFlyClient.h"
#include "RedFlyServer.h"


#define MAX_ERRORS (10)


//-------------------- Constructor --------------------


RedFlyServer::RedFlyServer(void) : s_port(80)
{
  return;
}



RedFlyServer::RedFlyServer(uint16_t port) : s_port(port), s_socket(INVALID_SOCKET)
{
  return;
}


//-------------------- Public --------------------


void RedFlyServer::begin(void)
{
  connect();

  return;
}


int RedFlyServer::connect(void)
{
  if(s_socket != INVALID_SOCKET)
  {
    return 0;
  }

  s_socket = RedFly.socketListen(PROTO_TCP, s_port);

  if(s_socket == INVALID_SOCKET)
  {
    return 0;
  }

  error = 0;

  return 1;
}


uint8_t RedFlyServer::connected(void)
{
  if(s_socket == INVALID_SOCKET)
  {
    return 0;
  }

  if(RedFly.socketClosed(s_socket)) //socket closed?
  {
    s_socket = INVALID_SOCKET;
    return 0;
  }

  if(error >= MAX_ERRORS)
  {
    RedFly.socketClose(s_socket);
    s_socket = INVALID_SOCKET;
    return 0;
  }

  return 1;
}


void RedFlyServer::stop(void)
{
  if(s_socket == INVALID_SOCKET)
  {
    return;
  }

  flush(); //clear buffer

  RedFly.socketClose(s_socket);
  s_socket = INVALID_SOCKET;
  error    = 0;

  return;
}


uint8_t RedFlyServer::status(void)
{
  if(s_socket == INVALID_SOCKET)
  {
    return 1;
  }

  if(RedFly.socketStatus(s_socket)) //socket closed?
  {
    s_socket = INVALID_SOCKET;
    return 1;
  }

  return 0;
}


uint8_t RedFlyServer::getSocket(void)
{
  return s_socket;
}


int RedFlyServer::available(void)
{
  uint8_t socket=s_socket;
  uint16_t len=0;

  if(socket != INVALID_SOCKET)
  {
    RedFly.socketRead(&socket, &len, 0, 0);
  }

  return (int)len;
}


int RedFlyServer::read(void)
{
  uint8_t b;
  uint8_t socket=s_socket;
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
    s_socket = INVALID_SOCKET;
    return -1;
  }

  return b;
}


int RedFlyServer::read(uint8_t *s, size_t size)
{
  uint8_t socket=s_socket;
  uint16_t len, read;

  if(socket == INVALID_SOCKET)
  {
    return 0;
  }

  read = RedFly.socketRead(&socket, &len, s, size);
  if(read == 0xFFFF) //socket closed?
  {
    s_socket = INVALID_SOCKET;
    read = 0;
  }

  return read;
}


void RedFlyServer::flush(void)
{
  uint16_t len = available();

  while(len)
  {
    read();
    len--;
  }

  return;
}


size_t RedFlyServer::write(uint8_t b) 
{
  if(s_socket != INVALID_SOCKET)
  {
    if(RedFly.socketSend(s_socket, (uint8_t*)&b, 1))
    {
      if(++error >= MAX_ERRORS)
      {
        RedFly.socketClose(s_socket);
        s_socket = INVALID_SOCKET;
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


size_t RedFlyServer::write(const char *s) 
{
  if(s_socket != INVALID_SOCKET)
  {
    if(RedFly.socketSend(s_socket, (char*)s))
    {
      if(++error >= MAX_ERRORS)
      {
        RedFly.socketClose(s_socket);
        s_socket = INVALID_SOCKET;
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


size_t RedFlyServer::write(const uint8_t *s, size_t size) 
{
  if(s_socket != INVALID_SOCKET)
  {
    if(RedFly.socketSend(s_socket, (uint8_t*)s, size))
    {
      if(++error >= MAX_ERRORS)
      {
        RedFly.socketClose(s_socket);
        s_socket = INVALID_SOCKET;
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


size_t RedFlyServer::print_P(PGM_P s)
{
  if(s_socket != INVALID_SOCKET)
  {
    if(RedFly.socketSendPGM(s_socket, s))
    {
      if(++error >= MAX_ERRORS)
      {
        RedFly.socketClose(s_socket);
        s_socket = INVALID_SOCKET;
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


size_t RedFlyServer::println_P(PGM_P s)
{
  if(s_socket != INVALID_SOCKET)
  {
    if(RedFly.socketSendPGM(s_socket, s))
    {
      if(++error >= MAX_ERRORS)
      {
        RedFly.socketClose(s_socket);
        s_socket = INVALID_SOCKET;
      }
    }
    else
    {
      RedFly.socketSendPGM(s_socket, PSTR("\r\n"));
      error = 0;
      return strlen_P(s) + 2;
    }
  }

  return 0;
}


//the next function allows us to use the client returned by
//RedFlyServer::available() as the condition in an if-statement.
RedFlyServer::operator bool()
{
  return s_socket != INVALID_SOCKET;
}
