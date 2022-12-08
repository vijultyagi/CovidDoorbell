/*************************************************** 
Covid Doorbell (Open Source)
****************************************************/
 
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <TM1637Display.h>
#include "SoftwareSerial.h"

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

// Mp3 player
SoftwareSerial mySerial(10, 11); 

#define CLK 12 
#define DIO 9  
#define buttonPin 3
#define buzzerPin 4

# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x00 
# define ACTIVATED LOW

int checkTemperature=0;
int buttonValue=0;

// adjust sensor 
int adjustTemp=3;

// Creates display object  
TM1637Display display(CLK, DIO);

// All - in display
const uint8_t SEG_START[] = {
          SEG_G,            // -
           SEG_G, // -
          SEG_G,   // -
          SEG_G  // -
          };

void setup() {

// Sensor is always on in this case as we removed the button
  Serial.begin(9600);


  Serial.println("Covid doorbell");  

   // mp3 player

    mySerial.begin(9600);        

    // nothing being played, just init        

    playFirst();  

    display.setBrightness(0x0f);

   display.setSegments(SEG_START);

   mlx.begin();    

   delay(1000);

}

void loop() {

  beep();    
  //Reads the temperature of surrounding
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC());
  //Reads the temperature of object near the sensor
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");

  checkTemperature=mlx.readObjectTempC();

  checkTemperature=checkTemperature+adjustTemp;

  display.showNumberDec(checkTemperature, false,4);

  execute_CMD(0x0F,0x01,0x01);
//threshold for fever
  if (checkTemperature>35) {

      Serial.println("Risk Detected: High fever");    

      execute_CMD(0x0F,0x01,0x02);      

    }

  Serial.println();

  delay(5000);

   display.setSegments(SEG_START);
}


//code for doorbell and buzzer - not in demo
void beep(){
  tone(buzzerPin, 2000);  
  delay(100);         
  noTone(buzzerPin);         
  }

  void playFirst()
{
  execute_CMD(0x3F, 0, 0); // query device
  delay(500);
  setVolume(25);
  delay(500);

}

void pause()
{
  execute_CMD(0x0E,0,0);
  delay(500);
}

void play()
{
  execute_CMD(0x0D,0,1); 
  delay(500);
}

void playNext()
{
  execute_CMD(0x01,0,1);
  delay(500);
}

void playPrevious()
{
  execute_CMD(0x02,0,1);
  delay(500);
}

void setVolume(int volume)
{
  execute_CMD(0x06, 0, volume); 
  delay(2000);
}

void execute_CMD(byte CMD, byte Par1, byte Par2)
// Excecute the command and parameters
{
// Calculate the checksum (2 bytes)
word checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);

byte Command_line[10] = { Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge,
Par1, Par2, highByte(checksum), lowByte(checksum), End_Byte};
//Send the command
for (byte k=0; k<10; k++)
{
mySerial.write( Command_line[k]);
}
}
