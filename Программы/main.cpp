#include "rccregisters.hpp"
#include "gpioaregisters.hpp"
#include "gpiocregisters.hpp"
#include "tim2registers.hpp"

extern "C"
{
  int __low_level_init (void)
  {
    RCC::CR::HSEON::Enable::Set();
    while (!RCC::CR::HSERDY::Enable::IsSet());
    {
    };
    
    RCC::CFGR::SW::Hse::Set();
    while (!RCC::CFGR::SWS::Hse::IsSet());
    {
    };
    RCC::CFGR::RTCPRE::Set(16);
    RCC::AHB1ENR::GPIOCEN::Enable::Set(); //podkluchaem porti C
    RCC::AHB1ENR::GPIOAEN::Enable::Set(); //podkluchaem porti A
    GPIOA::MODER::MODER5::Output::Set(); //Podkluchaem port kak vihod
    GPIOC::MODER::MODER5::Output::Set(); //Podkluchaem port kak vihod
    GPIOC::MODER::MODER8::Output::Set(); //Podkluchaem port kak vihod
    GPIOC::MODER::MODER9::Output::Set(); //Podkluchaem port kak vihod
    GPIOC::MODER::MODER13::Input::Set(); //Podkluchaem port kak vhod
    
    RCC::APB1ENR::TIM2EN::Enable::Set(); //Podkluchaem TIM2EN
    TIM2::CR1::URS::Value1::Set(); //Vkluchaem ursu
    return 0;
  }
}

void Delay(std::uint32_t delay) //Zadershka v razvitii programmi
{
  TIM2::ARR::Write(delay * 8'000 );
  TIM2::SR::UIF::NoUpdate::Set();
  TIM2::CNT::Write(0);
  TIM2::CR1::CEN::Enable::Set();
  while (TIM2::SR::UIF::UpdatePending::IsSet())
  {
  };
}
struct Button
{
  static bool IsPressed()
  {
    bool result = false;
    if (GPIOC::IDR::IDR13::Off::IsSet())
    {
      while(GPIOC::IDR::IDR13::Off::IsSet())
      {
      };
      result = true;
    }
    return result;
  }
};

template <typename Port, std::uint32_t pinNum>
struct Led
{
  static void Toggle()
  {
    Port::ODR::Toggle(1 << pinNum);
  }
};

using Led1 = Led<GPIOC, 5>;
using Led2 = Led<GPIOC, 8>;
using Led3 = Led<GPIOC, 9>;
using Led4 = Led<GPIOA, 5>;

int main()
{
bool flag = false;
for (; ;)
{

if(GPIOC::IDR::IDR13::Off::IsSet()) //kn vkl
{
while(GPIOC::IDR::IDR13::Off::IsSet())
{
} ;

if(flag)
{
GPIOA::ODR::ODR5::High::Set ();
GPIOC::ODR::ODR5::High::Set ();
GPIOC::ODR::ODR8::High::Set ();
GPIOC::ODR::ODR9::High::Set ();
flag = false ;
}
else
{
GPIOA::ODR::ODR5::Low::Set ();
GPIOC::ODR::ODR5::Low::Set ();
GPIOC::ODR::ODR8::Low::Set ();
GPIOC::ODR::ODR9::Low::Set ();
flag = true ;
}
}
}
return 0;
}
