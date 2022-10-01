# atmega328-blink-isr

This is a simple Microchip (Atmel) Studio project written in C that blinks the Built in LED on an Arduino UNO board. The code uses the TIMER1 on the ATMega328P processor, and the LED toggling is performed by a handler for the timer's Interrupt Service Request (ISR).

### Note
A guide on setting up Atmel Studio so that it can upload firmware to an Arduino board can be found in this [article](https://medium.com/jungletronics/how-to-load-programs-to-an-arduino-uno-from-atmel-studio-7-83c8dd8d175d).
