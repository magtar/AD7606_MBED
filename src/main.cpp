#include <mbed.h>
#include <rtos.h>
#include <Arduino.h>

using namespace mbed;
using namespace events;
using namespace rtos;

SPI fff(PC_3,PC_2,PI_1,PI_0);
int16_t raw [8];
DigitalOut CONVST(PC_15);


void getADC(){

}

int data;
void setup() {
   Serial.begin(9600);  
   fff.frequency(20000000);
   fff.format(16,0);
   CONVST=1;
   
}

void loop() {
   ThisThread::sleep_for(std::chrono::milliseconds(100) ); 
   CONVST=1;
   wait_us(5);
   for(int ii=0;ii<8;ii++){
      raw[ii]=fff.write((int) 0x00);
      //Serial.print(raw[ii]);
      //Serial.print(",");
   }   
   //Serial.print(" \n");
   CONVST=!CONVST;
}