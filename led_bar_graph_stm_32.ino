//two 74HC595 shift registers LED RPM Bar Graph example using SPI
//based on the stm32duino "using_SPI_ports" Example
//by Mike Kushnerik

//circuit settings:
// SER >> PB15 (MOSI)
// LATCH >> PB12 (CS)
// CLK >> PB13 (SCK)


#include <SPI.h> //SPI Library for STM32

#define latchPin PB12 //Chip Select Pin, feel free to change to any GPIO pin

SPIClass SPI_2(2); //Create an instance of the SPI Class called SPI_2 that uses the 2nd SPI Port (SPI2)

int tim1 = 100; //integer that determines the delay between leds in the sweep, in milliseconds

void setup() 
{
  SPI_2.begin();
  SPI_2.setBitOrder(LSBFIRST);
  SPI_2.setDataMode(SPI_MODE0);
  SPI_2.setClockDivider(SPI_CLOCK_DIV16); //SPI Speed  = 72 MHz / 16 = 4.5 MHz
  
  //NOTE: Clock Frequency -> As this example uses the 74HC595 shift register, the maximum clock speed, according to the TI Datasheet, is around 5 MHz at 3.3V VCC
  //Decreasing the above prescaler will cause the shift register to become unstable, and is not recommended without increaseing VCC, which is not shown in this example
  
  pinMode(latchPin, OUTPUT);
}
void loop() 
{
  for(int16_t i=0; i<=15000; i+=1000) //loop to gradually increase the RPM value to 15,000
    {
      ledBarGraph(i, 15000); //function call to send data to the shift registers over SPI
      delay(tim1); 
    }
    delay(tim1);
    for(int16_t j=15000;j>=0;j-=1000) //loop to gradually decrease the RPM value back to 0
    {
      ledBarGraph(j, 15000); //function call to send data to the shift registers over SPI
      delay(tim1);
    }
    delay(tim1);
}
void ledBarGraph(uint16_t inputRPM, uint16_t maxRPM) //function to send data over SPI to the shift registers, creating a left -> right sweeping 15 led bar graph
{
  uint8_t num = (inputRPM*15)/maxRPM; //scaling the input RPM from 0 -> 15,000 to 0 -> 15, which is the number of leds in our bar
  uint16_t ledData = 0; //setting the initial number of LEDs to be turned on to zero           
  for(int i=15;i>15-num; i--) //loop to set the correct number of bits inside the ledData based on our input rpm value
  {
    ledData |= 1<<i; //or bitwise operation to set the current bit masked by 1<<i
  }
  digitalWrite(latchPin, LOW); //clear the CS pin to begin communication with the shift register
  SPI_2.write16(ledData); //send 16 bits of data to the shift registers (MSB first)
  digitalWrite(latchPin, HIGH); //set the CS pin to end communication with the shift register                  
}
