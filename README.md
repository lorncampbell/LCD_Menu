# LCD_Menu
LCD menu structure and servo control box
Arduino_multiple_screens3_Github3 is the main file.
The other files are IDE "Tab" function files that are commented out in the program and have now been included in main file.

The project requires 3x momentary buttons and a potentiometer [10K linear]
I used a combined potentiometer and momentary button.   These are hard to find - I used this one: RS Components Stock no:729-3555
[http://uk.rs-online.com].

The Arduino used was an UNO but any compatible would work.
Any low voltage power regulator should work - I used this here:LM2596 DC to DC Buck Converter 3.0-40V to 1.5-35V Power Supply Step Down Module.

The voltage sensors are these here: Max 25V Voltage Detector Range 3 Terminal Sensor Module for Arduino.

The LCD 4x20 screen is a LCD-BLUE-12C and see this excellent wiki here: https://arduino-info.wikispaces.com/LCD-Blue-I2C

The menu structure is based on Nicolas Jarpa ideas here: http://www.instructables.com/id/Arduino-LCD-16x2-Turn-Single-Screen-Into-Multiple-/
