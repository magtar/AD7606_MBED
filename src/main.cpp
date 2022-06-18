
#include "mbed/mbed.h"
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

Ticker t;

void getADC(){
      while(1){
      wait_us(1);
      CONVST=1;
      wait_us(3);
      for(int ii=0;ii<8;ii++){
         raw [ii]=fff.write((int) 0x00);        
      }        
      CONVST=!CONVST;
   }
}

int main(){  
   
   fff.frequency(25600000);
   fff.format(16,0);  
   CONVST=1;   
   thread.start(getADC); 
  /*t.attach(&getADC,1.0); 
  while (1) {
        
        ThisThread::sleep_for(200.0);
    }
*/
return 0;
}
