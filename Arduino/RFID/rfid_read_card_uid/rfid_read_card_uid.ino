#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
String myCard = "";

void setup() {
    Serial.begin(9600);         // Initialize serial communications with the PC
    while (!Serial);            // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
    SPI.begin();                // Init SPI bus
    mfrc522.PCD_Init();         // Init MFRC522 card
    Serial.println(F("Try the most used default keys to print block 0 of a MIFARE PICC."));
}

void dump_byte_array(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
        myCard += buffer[i];
    }
}


void loop() {
    // Pysyy tässä kunnes lukee kortin
    if ( ! mfrc522.PICC_IsNewCardPresent())
        return;

    // Kun huomaa kortin, lukee sen tiedot
    if ( ! mfrc522.PICC_ReadCardSerial())
        return;

    Serial.print(F("Kortin UID:"));
    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);

    Serial.println("");
    if(myCard == "1072133734")
    {
      Serial.println("Terve! Oikea kortti.");
      //Aliohjelma joka lähettää dataa tietokantaan
    }
    else
    {
      Serial.println("Väärä kortti!");
    }
    Serial.println("########################");
    myCard = "";
}
