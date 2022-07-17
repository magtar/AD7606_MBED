# include "mbed/mbed.h"


using namespace mbed;
using namespace events;
using namespace rtos;
using namespace std::literals::chrono_literals;

//EventQueue queue(32 * EVENTS_EVENT_SIZE);
EventQueue queue;
DigitalOut CONVST(PC_15);
int16_t raw [8];  
SPI fff(PC_3,PC_2,PI_1,PI_0);

void getADC(){        
      CONVST=1;
      wait_us(3);
      for(int ii=0;ii<8;ii++){
         raw [ii]=fff.write((int) 0x00);            
      CONVST=!CONVST;
      }
}

int main(){   
   fff.frequency(25600000);
   fff.format(16,0);    
   Thread thread(osPriorityRealtime);
   thread.start(callback(&queue, &EventQueue::dispatch_forever));
   Ticker t;  
   t.attach(queue.event(&getADC),1000us);
   while(1)
   {
      ThisThread::sleep_for(std::chrono::hours::max()); 
   }
   
}
