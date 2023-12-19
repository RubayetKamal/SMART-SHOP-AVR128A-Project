# SMART-SHOP-AVR128A-Project

A Smart Shop was modelled where it has three states: 1)Opened 2)Closed 3)Warning

In Opened state, the door opens automatically when HCSR04 detects someone in front of it and closes at least 2 seconds after the object is gone. The infrared sensor is diabled in this state. The fire alarm is activated in all states where if fire is detected, the door is opened.

In Closed state, the door won't be opening automatically. The infrared sensor will trigger the alarm if it detects someone inside the shop. As already mentioned, the fire alarm is trigerred in all state, opening the door.

In warning state, a fire has been detected for which the door of the shop remains open. RGB LED will blink red in this state.

The starting state of the shop is opened. 0 can be pressed on the keypad to close the shop. 1 can be pressed to open. If alarm is trigerred, holding A on the keypad can disable the alarm after which pressing 1 or 0 will allow the shop be in it's respective state.

We have I2C OLED Display, which displays three information: The current temperature, humidity and current state of the shop.

Components used:

Flame Sensor Infrared HCSR04 Keypad DHT-11

I2C OLED Servo RGB LED Buzzer

Me and my group have used modules like I/O, ADC, Timer, Interrupts and Communication Protocols like I2C to complete this project.
