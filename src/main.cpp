#include <mbed.h>
#include <rtos.h>
#include <Arduino.h>

using namespace mbed;
using namespace events;
using namespace rtos;
using namespace std::literals::chrono_literals;

SPI fff(PC_3,PC_2,PI_1,PI_0);
int16_t raw [8];
DigitalOut CONVST(PC_15);
Thread thread(osPriorityRealtime);



void getADC(){
   while(1){
      //ThisThread::sleep_for(std::chrono::milliseconds(100) ); 
      //ThisThread::sleep_for(500us); 
      wait_us(1);
      CONVST=1;
      wait_us(3);
      for(int ii=0;ii<8;ii++){
         raw[ii]=fff.write((int) 0x00);
         //Serial.print(raw[ii]);
         //Serial.print(",");
      }   
      //Serial.print(" \n");
      CONVST=!CONVST;
   }
}

int data;
void setup() {
   Serial.begin(9600);  
   fff.frequency(36000000);
   fff.format(16,0);
   CONVST=1;
   //osPriority DC=realtime;
   //thread.set_priority(osPriorityHigh);
   thread.start(getADC);
   
}

void loop() 
{
   ThisThread::sleep_for(std::chrono::hours(1) ); 
   //ThisThread::sleep_for(forever ); 
  /* CONVST=1;
   wait_us(5);
   for(int ii=0;ii<8;ii++){
      raw[ii]=fff.write((int) 0x00);
      //Serial.print(raw[ii]);
      //Serial.print(",");
   }   
   //Serial.print(" \n");
   CONVST=!CONVST;
   */
} 
