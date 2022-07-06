#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

#define CH1_PIN A1
#define CH2_PIN A0
#define CH3_PIN A2
#define CH4_PIN A3

const int ch1_limit[2] = {500,2500};
const int ch2_limit[2] = {500,2500};
const int ch3_limit[2] = {500,2500};
const int ch4_limit[2] = {500,2500};

const int pipe = 9876;
const int mid_ang = 1500;

RF24 radio(9,10);

struct Data{
  short ch1;
  short ch2;
  short ch3;
  short ch4;
};

Data data;

int format(int val, int min_v, int max_v,bool reverse){
  int result = map(val,0,1023,min_v,max_v);
  if(reverse){
    if(result < mid_ang){
      return mid_ang + (mid_ang - result);
    }
    else{
      return mid_ang - (result - mid_ang);
    }
  }
  return result;
}

void get_input(){
  data.ch1 = format(analogRead(CH1_PIN),ch1_limit[0],ch1_limit[1],true);
  data.ch2 = format(analogRead(CH2_PIN),ch2_limit[0],ch2_limit[1],true);
  data.ch3 = format(analogRead(CH3_PIN),ch3_limit[0], ch3_limit[1],false);
  data.ch4 = format(analogRead(CH4_PIN),ch4_limit[0],ch4_limit[1],false);
}

void setup(){
  radio.begin();
  radio.openWritingPipe(pipe);
}

void loop(){
  get_input();
  radio.write(&data,sizeof(data));
}
