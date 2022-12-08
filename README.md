# CoronavirusDoorbell

Arduino Doorbell with hidden IR temperature sensor to detect high fever

Works similar to the IR temperature used at airports, scan the visitors body temperature as soon as they ring the bell using IR remote temperature. If body temperature is normal ring the bell, otherwise an alarm will appear.

The objective of this project is to measure the temperature of a person before entering the house, to warn that the visitor may be potentially infected with Covid. The process begins with a doorbell, which consists of a hidden IR thermometer and activates when a person comes in close proximity to the sensor. This infrared thermometer determines the body temperature by calculating the difference between the IR of the surrounding and that coming from the person. The recorded temperature is displayed on the screen, which is then compared to the standard fever temperatures. If the temperature of a person lies within the fever bracket, an alarm will be triggered, thereby giving warning about a potentially infected visitor, else it will ring a normal doorbell without triggering any alarm. Additionally, we will need to develop an algorithm  to  compare  the  recorded  temperature,  conditionally  trigger  the  alarm  and send temperature digits to the display.


Development Environments:

Hardware - Arduino Nano R3, LED Display, IR Temperature sensor, MP3 decoder, speaker, breadboard.
IDE - Arduino IDE 2.0.3
Language - Arduino programming language

Youtube Video Link : https://www.youtube.com/watch?v=zm7D8iYt6jo&t=7s&ab_channel=Vijul

Group 11
Vishal Singh - 1001949135
Vijul Tyagi - 1001947373


