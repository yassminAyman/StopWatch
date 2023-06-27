# StopWatch
Implementation of a StopWatch using Atmega32 Microcontroller
The specifications:
1. Microcontroller frequency 1Mhz.
2. Timer1 with CTC mode.
3. six Common Anode 7-segments using the multiplexed technique.
4. 7447 decoder 4-pins is connected to the first 4-pins in PORTC.
5. first 6-pins in PORTA is used as the enable/disable pins for the six 7-segments.
6. External Interrupt INT0 is configured with falling edge. Connect a push button with the internal pull-up resistor.
    If a falling edge detected the Stop Watch time should be reset.
7. External Interrupt INT1 is configured with raising edge. Connect a push button with the 
    external pull-down resistor. If a raising edge detected the Stop Watch time should be paused.
8.External Interrupt INT2 is configured with falling edge. Connect a push button with the 
    internal pull-up resistor. If a falling edge detected the Stop Watch time should be resumed.
