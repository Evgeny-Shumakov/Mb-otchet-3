#include "rccregisters.hpp" //for RCC
#include "gpiocregisters.hpp"
int Delay(void)
{
for(int i=0; i<1000000000; i++)
  {
  }
return 0;
}

int main()
{
  RCC::AHB1ENR::GPIOCEN::Enable::Set();
 for( ; ; )
  { 
    GPIOC::MODER::MODER5::Output::Set();
    GPIOC::MODER::MODER8::Output::Set();
    GPIOC::MODER::MODER9::Output::Set();
    
    GPIOC::ODR::ODR5::Enable::Set();
    GPIOC::ODR::ODR8::Enable::Set();
    GPIOC::ODR::ODR9::Enable::Set();
    
  Delay();  
      
    GPIOC::ODR::ODR5::Disable::Set();
    GPIOC::ODR::ODR8::Disable::Set();
    GPIOC::ODR::ODR9::Disable::Set();
  }
return 0;
}
