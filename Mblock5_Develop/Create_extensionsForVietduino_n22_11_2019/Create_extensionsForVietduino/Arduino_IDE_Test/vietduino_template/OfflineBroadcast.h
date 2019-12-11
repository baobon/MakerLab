#ifndef OfflineBoardcast_H
#define OfflineBoardcast_H
// #include "MeSerial.h"
#include <Arduino.h>

#define BROADCAST 70
#define GET 1

class OfflineBroadcast
{
public:
	OfflineBroadcast(void);
	void loop();
	String broadcastMsg = "";
	String broadcastValue = "";
	void broadcast(String msg,String value);
  void broadcast(String msg);
  void callOK();
  void on(String msg,void(*callback)(void));
private:
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
