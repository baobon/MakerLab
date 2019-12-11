#include "Vietduino_Ultrasonic.h"
//#include "SimpleKalmanFilter.h"

//SimpleKalmanFilter kalman(2, 2, 0.1);

/*
   Port 12  --->  trigPin = 12 , echo = 13 -->
   Port 11  --->  trigPin = 11 , echo = 12
   Port 2   --->  trigPin = 2 , echo = 3
   Normal port 2;
*/

// Vietduino_Ultrasonic::Vietduino_Ultrasonic(unsigned int b_port, unsigned long b_maxdistance) {
//   port = b_port;
//   maxDisTance = b_maxdistance;
//   pinMode(port, OUTPUT); // trig
//   pinMode(port + 1, INPUT); // echo
//   kalman = new SimpleKalmanFilter(2, 2, 0.1);
//   this->intervalTime = 100;
//   this->lastTimeRead = millis();
// }

Vietduino_Ultrasonic::Vietduino_Ultrasonic(unsigned int b_port){
  // Vietduino_Ultrasonic(b_port, b_port + 1);

  trig_pin = b_port;
  echo_pin = b_port + 1;
  setMaxDistance(100);
  pinMode(trig_pin, OUTPUT); // trig
  pinMode(echo_pin, INPUT); // echo
  if(!kalman) kalman = new SimpleKalmanFilter(2, 2, 0.1);   //kxn
  this->intervalTime = 100;
  this->lastTimeRead = millis();
}

Vietduino_Ultrasonic::Vietduino_Ultrasonic(unsigned int _trig_pin_, unsigned int _echo_pin_) {
  trig_pin = _trig_pin_;
  echo_pin = _echo_pin_;
  setMaxDistance(100);
  pinMode(trig_pin, OUTPUT); // trig
  pinMode(echo_pin, INPUT); // echo
  if(!kalman) kalman = new SimpleKalmanFilter(2, 2, 0.1);   //kxn
  this->intervalTime = 100;
  this->lastTimeRead = millis();
}

void Vietduino_Ultrasonic::setMaxDistance(uint16_t _maxDistanceValue_){
  maxDisTance = _maxDistanceValue_;
  timeOutPulIn = ((maxDisTance * 10 / 0.1715) + 0.5);
}

bool Vietduino_Ultrasonic::begin() {
  return true;
}

bool Vietduino_Ultrasonic::stop() {
  return false;
}

float Vietduino_Ultrasonic::getMeasure() {
  unsigned long tempCurrenttime = millis();
  if(tempCurrenttime - this->lastTimeRead >= this->intervalTime){
    this->lastTimeRead = tempCurrenttime;
    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin, LOW);
    Time = pulseIn(echo_pin, HIGH, timeOutPulIn);
    //  Measurement = Time * 0.1715;
    Measurement = Time * 0.1715 ;

    if (Measurement == 0) {
      Measurement = maxDisTance * 10;
    } else {
      Measurement = this -> kalman -> updateEstimate(Measurement);

    }
  }
   return Measurement / 10;
}
