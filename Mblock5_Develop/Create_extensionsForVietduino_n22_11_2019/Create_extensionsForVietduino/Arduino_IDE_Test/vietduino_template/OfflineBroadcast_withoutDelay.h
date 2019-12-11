#ifndef OfflineBoardcast_withoutDelay_H
#define OfflineBoardcast_withoutDelay_H
// #include "MeSerial.h"
#include <Arduino.h>

#define BROADCAST_ID_ 70
#define GET 1

class OfflineBroadcast_withoutDelay
{
public:
	OfflineBroadcast_withoutDelay(void);
	void loop();
	String broadcastMsg = "";
	String broadcastValue = "";
	void broadcast(String msg,String value);
  void broadcast(String msg);
  void callOK();
  void on(String msg,void(*callback)(void));
  bool checkMessage(String msg);
  String getMessageValue(String msg);
private:
  bool isAvailable,isStart;
  char serialRead;
  char buffer[52];

  struct Listener
  {
      String msg;
      void (*callback)(void);
      bool flag_called;//kxn
      String value;
  };

  struct Listener listenList[16]; //20
  int listenerP=0;

  char _receiveStr[20] = {};
  uint8_t _receiveUint8[16] = {};

  void readSensor(int device);
  unsigned char readBuffer(int index);
  void writeBuffer(int index,unsigned char c);
  void parseData();
  void writeEnd();
  void writeSerial(unsigned char c);
  void readSerial();
  String readString(int idx,int len);
  void writeHead();
};
#endif
