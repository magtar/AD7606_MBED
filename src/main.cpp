# include "mbed/mbed.h"


using namespace mbed;
using namespace events;
using namespace rtos;
using namespace std::literals::chrono_literals;


DigitalOut CONVST(PC_15);
int16_t raw [8];  
SPI fff(PC_3,PC_2,PI_1,PI_0);
Thread thread(osPriorityRealtime);
Semaphore ticksema(0);
void getADC();
void isrTick();


int main()
{   
   fff.frequency(56000000);
   fff.format(16,0);      
   thread.start(getADC);

   Ticker t;  
   t.attach(isrTick,30us);
   
   while(1)
   {
      ThisThread::sleep_for(std::chrono::hours::max()); 
   }
   
}

void isrTick()
{
   ticksema.release();
}

void getADC()
{          
   while(1){
   ticksema.acquire();
   CONVST=1;
   wait_us(3);
  
   for(int ii=0;ii<4;ii++)
   {
    raw [ii]=fff.write((int) 0x00);            
   }
   CONVST=!CONVST; 
   }     
}