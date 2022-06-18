#include <mbed.h>
#include <rtos.h>
#include <Arduino.h>

using namespace mbed;
using namespace events;
using namespace rtos;
using namespace std::literals::chrono_literals;

SPI fff(PC_3,PC_2,PI_1,PI_0);
int16_t raw [8];
int16_t data[8];
uint8_t j;
DigitalOut CONVST(PC_15);
Thread thread(osPriorityRealtime);



void getADC(){
      //Serial.begin(9600);
       while(1){
     
      //ThisThread::sleep_for(std::chrono::milliseconds(100) ); 
      //ThisThread::sleep_for(500us); 
      wait_us(1);
      CONVST=1;
      wait_us(3);
      //j=0;
      for(int ii=0;ii<8;ii++){
         raw [ii]=fff.write((int) 0x00);
        
      }        
      CONVST=!CONVST;
   }
}


void setup() {
   Serial.begin(9600);   
   fff.frequency(25600000);
   fff.format(16,0);
   CONVST=1;   
   thread.start(getADC); 
   
}

void loop() 
{
   ThisThread::sleep_for(std::chrono::seconds(1) ); 
   
}
