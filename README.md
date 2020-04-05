# ledBarGraph
A example program for using two 74HC595 Shift Registers via SPI for stm32duino. Based on the stm32duino "using_SPI_ports" Example.

circuit settings:
SER >> PB15 (MOSI)
LATCH >> PB12 (CS)
CLK >> PB13 (SCK)

See comments inside program for Additional Information.

Note: This program uses hardware SPI for communication with the two 74HC595 shift registers. This is significantly more efficient than using bit banging as it utilizes the STM32's hardware SPI peripheral for sending data to the two registers rather than the main processor.
