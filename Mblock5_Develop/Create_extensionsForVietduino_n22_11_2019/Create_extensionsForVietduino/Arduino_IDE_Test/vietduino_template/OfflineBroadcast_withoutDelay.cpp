#include "OfflineBroadcast_withoutDelay.h"
unsigned char prevc_withoutDelay;
byte index_withoutDelay = 0;
byte dataLen_withoutDelay;
// bool isAvailable,isStart;
uint8_t command_index_withoutDelay = 0;
// char serialRead;
// char buffer[52];
#define MAX_LISTENER 15

// struct Listener
// {
//     String msg;
//     void (*callback)(void);
// };

// struct Listener listenList[20];
// int listenerP=0;
OfflineBroadcast_withoutDelay::OfflineBroadcast_withoutDelay(void)
{}
void OfflineBroadcast_withoutDelay::readSerial(){
  isAvailable = false;
  if(Serial.available()>0){
    isAvailable = true;
    serialRead = Serial.read();
  }
}
unsigned char OfflineBroadcast_withoutDelay::readBuffer(int index){
 return buffer[index]; 
}
void OfflineBroadcast_withoutDelay::loop()
{
	readSerial();
  if(isAvailable){
	unsigned char c = serialRead&0xff;
	if(c==0x55&&isStart==false){
	 if(prevc_withoutDelay==0xff){
	  index_withoutDelay=1;
	  isStart = true;
	 }
	}else{
	  prevc_withoutDelay = c;
	  if(isStart){
		if(index_withoutDelay==2){
		 dataLen_withoutDelay = c; 
		}else if(index_withoutDelay>2){
		  dataLen_withoutDelay--;
		}
		writeBuffer(index_withoutDelay,c);
	  }
	}
	 index_withoutDelay++;
	 if(index_withoutDelay>51){
	  index_withoutDelay=0; 
	  isStart=false;
	 }
	 if(isStart&&dataLen_withoutDelay==0&&index_withoutDelay>3){ 
		isStart = false;
		parseData(); 
		index_withoutDelay=0;
	 }
  }
}
void OfflineBroadcast_withoutDelay::broadcast( String msg){
  uint8_t arr[50]={0,0,1,0x46,1,1};
  int len = msg.length();
  int size = 6;
  if(len==0){
    return;
  }
  arr[5] = len;
	for(int i=0;i<len;i++){
    	arr[size] = uint8_t(msg[i]);
    	size++;
  }
  arr[0] = size-1;
  writeHead();
  for(int i=0;i<size;i++)
  {
    writeSerial(arr[i]);
  }
  writeEnd();
  // delay(100);
}
void OfflineBroadcast_withoutDelay::broadcast(String msg,String value){
  uint8_t arr[50]={0,0,1,0x46,2,1};
  int len = msg.length();
  if(len==0){
    return;
  }
  int len2 = value.length();
  int size = 6;
  arr[5] = len;
  for(int i=0;i<len;i++){
      arr[size] = uint8_t(msg[i]);
      size++;
  }
  arr[size++] = len2;
  for(int i=0;i<len2;i++){
      arr[size++] = uint8_t(value[i]);
  }
  arr[0] = size-1;
  writeHead();
  for(int i=0;i<size;i++)
  {
    writeSerial(arr[i]);
  }
  writeEnd();
  // delay(100);
}

void OfflineBroadcast_withoutDelay::readSensor(int device){
   /**************************************************
      ff    55      len idx action device type len name  
      0     1       2   3   4      5      6    7    8
      0xff  0x55   0x4 0x3 0x1    0x46    0x1  0x2  48 69
      -----------------------------------------------
      ff    55      len idx action device type len name len message
      0   1   2 3 4   5   6 7 8 9 10
  ***************************************************/
  int type;
  switch(device){
    case  BROADCAST_ID_:{
      type = readBuffer(6);
      // 无附加值
      if(type==1){
        int len = readBuffer(7);
        broadcastMsg = readString(8,len); 
        broadcastValue = "";
      }
      // 有附加值
      else if(type==2){
        int nlen = readBuffer(7);
        broadcastMsg = readString(8,nlen);
        int vlen = readBuffer(7+nlen+1);
        broadcastValue = readString(7+nlen+2,vlen);
      }
      bool hasCallback = false;
      for(int i=0;i<MAX_LISTENER;i++){
        if(broadcastMsg.equals(listenList[i].msg)){
          if(listenList[i].callback) listenList[i].callback();
          listenList[i].flag_called = true;
          listenList[i].value = broadcastValue;
          hasCallback = true;
        }
      } 
      if(!hasCallback){
        callOK();
      }
    }
    break;
  }
}
void OfflineBroadcast_withoutDelay::parseData(){
  isStart = false;
  int idx = readBuffer(3);
  command_index_withoutDelay = (uint8_t)idx;
  int action = readBuffer(4);
  int device = readBuffer(5);
  switch(action){
    case GET:{
        readSensor(device);
     }
     break;
  }
}

void OfflineBroadcast_withoutDelay::writeBuffer(int index,unsigned char c){
  buffer[index]=c;
}
void OfflineBroadcast_withoutDelay::writeHead(){
  writeSerial(0xff);
  writeSerial(0x55);
}
void OfflineBroadcast_withoutDelay::writeEnd(){
 Serial.println(); 
}
void OfflineBroadcast_withoutDelay::writeSerial(unsigned char c){
 Serial.write(c);
}
// char _receiveStr[20] = {};
// uint8_t _receiveUint8[16] = {};
String OfflineBroadcast_withoutDelay::readString(int idx,int len){
  char p[50];
  for(int i=0;i<len;i++){
    p[i]=readBuffer(idx+i);
  }
  p[len] = ' ';
  return String(p);
}
void OfflineBroadcast_withoutDelay::callOK(){
    uint8_t arr[5]={4,0,1,0x46,3};
    writeHead();
    for(int i=0;i<5;i++)
    {
      writeSerial(arr[i]);
    }
    writeEnd();
}
void OfflineBroadcast_withoutDelay::on(String msg,void(*callback)(void)){
  struct Listener listener;
  listener.msg = msg;
  listener.callback = callback;
  if(listenerP<MAX_LISTENER){
    listenList[listenerP++] = listener;
  }
}

bool OfflineBroadcast_withoutDelay::checkMessage(String msg){
  for(int i=0;i<MAX_LISTENER;i++){
    if(msg.equals(listenList[i].msg)){
      bool temFlag = listenList[i].flag_called;
      if(temFlag)
      listenList[i].flag_called = false;
      return temFlag;
    }
  }
  return false;
}

String OfflineBroadcast_withoutDelay::getMessageValue(String msg){
  for(int i=0;i<MAX_LISTENER;i++){
    if(msg.equals(listenList[i].msg)){
      String tempValue = listenList[i].value;
      listenList[i].value = "";
      return tempValue;
    }
  }
  return "";
}