#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> 
#include <Keypad.h>
/*
 * Digitaali pinnit varattu: 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
 */
void setup()
{
  Serial.begin(9600);         // Initialize serial communications with the PC
  //while (!Serial);            // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  //SPI.begin();                // Init SPI bus
  //mfrc522.PCD_Init();         // Init MFRC522 card
  //Serial.println(F("Try the most used default keys to print block 0 of a MIFARE PICC."));
}
