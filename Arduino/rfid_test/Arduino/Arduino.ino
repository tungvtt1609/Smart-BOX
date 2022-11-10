#include <SPI.h>
#include <RFID.h>
#include <string.h>

/* Ket noi chan (Arduino Mega)
 *  Reset     5
 *  SPI SDA   53
 *  SPI MOSI  51
 *  SPI MISO  50
 *  SPI SCK   52
 */

#define SDA_DIO 53
#define RESET_DIO 5

RFID RC522(SDA_DIO, RESET_DIO);

String id = "rfid:";
String idx = "set:";
String idx2 = "get:";
String p_check = "p:";

bool check = false;

void setup()
{ 
  Serial.begin(9600);
  /* Enable the SPI interface */
  SPI.begin(); 
  /* Initialise the RFID reader */
  RC522.init();
}

void loop()
{
  String b = "";
  String mode = "1";
  /* Has a card been detected? */
  if (RC522.isCard())
  {
//    /* If so then get its serial number */
    RC522.readCardSerial();
    for(int i=0;i<5;i++)
    {
      b = b + String(RC522.serNum[i]);
    }

    Serial.println(b);
//      
//     if (!check){
//      b = p_check + "1"; 
//      check = !check;
//     }else {
//      b = p_check + "0"; 
//      check = !check;
//     }

  }
  delay(1000);
}
