# ledBarGraph
A example program for using two 74HC595 Shift Registers via SPI for stm32duino. Based on the stm32duino "using_SPI_ports" Example.

circuit settings:
SER >> PB15 (MOSI)
LATCH >> PB12 (CS)
CLK >> PB13 (SCK)

See comments inside program for Additional Information.

Note 1: This program uses hardware SPI for communication with the two 74HC595 shift registers. This is significantly more efficient than using bit banging as it utilizes the STM32's hardware SPI peripheral for sending data to the two registers rather than the main processor.
Note 2: The SPI clock frequency used is based on a 16:1 prescaler from the main sys clock. For the STM32 BluePill boards, this is 72 MHz. So, our resulting SPI clock is 72 MHz / 16 = 4.5 MHz. As this example uses the 74HC595 shift register, the maximum clock speed, according to the TI Datasheet, is around 5 MHz at 3.3V. Decreasing the prescaler below the value given in the example will cause the shift register to become unstable, and is not recommended without increaseing VCC, which is not shown in this example
