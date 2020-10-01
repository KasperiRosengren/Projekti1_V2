#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
String myCard = "";

void dump_byte_array(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
        myCard += buffer[i];
    }
}


void RfidMain() {
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
