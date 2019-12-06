#include <cstdint>
#include <cstddef>
#include <iostream>
#include "rccregisters.hpp"
#include "gpiocregisters.hpp"
using namespace std;

extern "C" 
{
  int __low_level_init(void)
  {
    
    RCC::CR::HSION::Value1::Set();
    while ( !RCC::CR::HSIRDY::Value1::IsSet( ) )
    {
    };
    RCC::CFGR::SW::Hsi::Set();
    while ( !RCC::CFGR::SWS::Hsi::IsSet( ) )
    {
    };
    RCC::CFGR::HPRE::Value2::Set()
 
    constexpr size_t GpiocAddr = 0x40020800;
    constexpr size_t ModerOffset = 0x00; 
    constexpr size_t OdrOffset = 0x14; 
    constexpr size_t ModerAddr = GpiocAddr + ModerOffset; 
    constexpr size_t OdrAddr = GpiocAddr + OdrOffset; 
  }
}
void delay(uint32_t delay)
 {
   for (int i=0; i<delay; i++)
   {
   }
 }

int main() 
{
RCC::AHB1ENR::GPIOCEN::Enable::Set() ;

  volatile uint32_t *ModerPointer = reinterpret_cast<volatile uint32_t*>(ModerAddr); 
  volatile uint32_t *OdrPointer = reinterpret_cast<volatile uint32_t*>(OdrAddr ) ; 
  for(;;) 
   {
      *ModerPointer |= ((1 << 10 )|(1<<16)|(1<<18));   
      *ModerPointer &= ~ ((1 << 11 )|(1<<17)|(1<<19)); 
      *OdrPointer |= ((1 << 5 )|(1<<8)|(1<<9)); 
      delay (1'000'000);
      *OdrPointer &= ~ ((1 << 5 )|(1<<8)|(1<<9)); 
   }
  bool flag = false;
  for (; ;)
  {

    if(GPIOC::IDR::IDR13::Value0::IsSet()) //kn vkl
    {
      while(GPIOC::IDR::IDR13::Value0::IsSet())
      {
      } ;

      if(flag)
      {
        GPIOC::ODR::ODR5::Enable::Set ();
        GPIOC::ODR::ODR8::Enable::Set ();
        GPIOC::ODR::ODR9::Enable::Set ();
        flag = false ;
      }
      else
      {
        GPIOA::ODR::ODR5::Disable::Set ();
        GPIOC::ODR::ODR5::Disable::Set ();
        GPIOC::ODR::ODR8::Disable::Set ();
        GPIOC::ODR::ODR9::Disable::Set ();
        flag = true ;
      }
    }
  }
  return 0 ;
}

