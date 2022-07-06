#include <RF24.h>
#include <nRF24L01.h>
#include <SPI.h>
#include <Servo.h>

Servo ch1_s;
Servo ch2_s;
Servo ch3_s;
Servo ch4_s;

RF24 radio(9,10);
const int pipe = 9876;

const int mid_ang = 1500;

struct Data{
int ch1;
int ch2;
int ch3;
int ch4;  //throttle
};

Data data;

void reset_data(){
  data.ch1 = mid_ang;
  data.ch2 = mid_ang;
  data.ch3 = mid_ang;
  data.ch4 = 0;  //ch4 is assumpt as throttle variable, motor power zero;
}


void write_servos(){
  ch1_s.writeMicroseconds(data.ch1);
  ch2_s.writeMicroseconds(data.ch2);
  ch3_s.writeMicroseconds(data.ch3);
  ch4_s.writeMicroseconds(data.ch4);
}

void setup() {
  Serial.begin(9600);
  reset_data();

  ch1_s.attach(2);
  ch2_s.attach(3);
  ch3_s.attach(4);
  ch4_s.attach(5);
  
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
}

void loop() {
  while(radio.available()){
    radio.read(&data,sizeof(data));
    write_servos();
   }
}
