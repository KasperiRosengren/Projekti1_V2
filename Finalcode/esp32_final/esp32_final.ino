#include <SPI.h>        // RC522 Module uses SPI protocol
#include <MFRC522.h>  // Library for Mifare RC522 Devices
#include <HTTPClient.h>
#include <WiFi.h>
#include <ESP32Servo.h>


#define redLed 13    // Set Led Pins
#define greenLed 12
#define blueLed 14


TaskHandle_t Task1;
TaskHandle_t Task2;

// wifi
const char* ssid = "kassu2.4GHZ";
const char* password = "omaverkko";


// REPLACE with your Domain name and URL path or IP address with path
const char* serverName = "http://192.168.0.101/post-esp-data.php";
const char* serverName2 = "http://192.168.0.101/esp-data.php";


// Keep this API Key value to be compatible with the PHP code provided in the project page.
// If you change the apiKeyValue value, the PHP file /post-esp-data.php also needs to have the same key
String apiKeyValue = "tPmAT5Ab3j7F9";


String deviceID = "1";


Servo myservo;  // create servo object to control a servo


int pos = 0;    // variable to store the servo position
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33
int servoPin = 33;


// Create MFRC522 instance.
#define SS_PIN 5
#define RST_PIN 22
MFRC522 mfrc522(SS_PIN, RST_PIN);


char piccUID[32];
char received[32];


void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(115200);  // Initialize serial communications with PC
  SPI.begin();           // MFRC522 Hardware uses SPI protocol
  mfrc522.PCD_Init();    // Initialize MFRC522 Hardware
  
  //Arduino Pin Configuration
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  digitalWrite(redLed, LOW);  // Make sure led is off
  digitalWrite(greenLed, LOW);  // Make sure led is off
  digitalWrite(blueLed, LOW); // Make sure led is off
  
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(servoPin, 500, 2400); // attaches the servo on pin 33 to the servo object
  
  //If you set Antenna Gain to Max it will increase reading distance
  //mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_max);

  Serial.print("connecting to ");
  Serial.print(ssid);

  //connect to wifi
  WiFi.begin(ssid, password);

  //wait until connection has been confirmed
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  //debugging - output the ip address of the esp
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

   //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
    Task1code,   /* Task function. */
    "Task1",     /* name of task. */
    10000,       /* Stack size of task */
    NULL,        /* parameter of the task */
    1,           /* priority of the task */
    &Task1,      /* Task handle to keep track of created task */
    0);          /* pin task to core 0 */
  delay(500);

  //create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
  xTaskCreatePinnedToCore(
    Task2code,   /* Task function. */
    "Task2",     /* name of task. */
    10000,       /* Stack size of task */
    NULL,        /* parameter of the task */
    1,           /* priority of the task */
    &Task2,      /* Task handle to keep track of created task */
    1);          /* pin task to core 1 */
  delay(500);


  Serial.println(F("Access Control Example v0.1"));   // For debugging purposes
  ShowReaderDetails();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println("Present PICC");
}


//Task1code: 
void Task1code( void * pvParameters ) {
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());

  for (;;) 
  {
    digitalWrite(greenLed, HIGH);
    delay(300);
    digitalWrite(greenLed, LOW);
    delay(300); 
    getID(piccUID);
  }
}

//Task2code: 
void Task2code( void * pvParameters ) 
{
  Serial.print("Task2 running on core ");
  Serial.println(xPortGetCoreID());

  for (;;) 
  {
    digitalWrite(blueLed, HIGH);
    delay(300);
    digitalWrite(blueLed, LOW);
    delay(300);
    getData(received);
  }  
}

void loop() 
{
  
}

/////////////////////////////////print RFID readers details///////////////////////////
void ShowReaderDetails()
{
  // Get the MFRC522 software version
  byte v = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);
  Serial.print(F("MFRC522 Software Version: 0x"));
  Serial.print(v, HEX);
  if (v == 0x91)
    Serial.print(F(" = v1.0"));
  else if (v == 0x92)
    Serial.print(F(" = v2.0"));
  else
    Serial.print(F(" (unknown),probably a chinese clone?"));
  Serial.println("");
  // When 0x00 or 0xFF is returned, communication probably failed
  if ((v == 0x00) || (v == 0xFF)) {
    Serial.println(F("WARNING: Communication failure, is the MFRC522 properly connected?"));
    Serial.println(F("SYSTEM HALTED: Check connections."));
    // Visualize system is halted
    digitalWrite(greenLed, LOW);  // Make sure green LED is off
    digitalWrite(blueLed, LOW);   // Make sure blue LED is off
    digitalWrite(redLed, HIGH);   // Turn on red LED
    while (true); // do not go further
  }
}

//////////////////////////// Get PICC's UID /////////////////////////////////////////////////////////
char getID(char uid[32])
{
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return 1;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return 1;
  }

  array_to_string(mfrc522.uid.uidByte, 4, uid); //Insert (byte array, length, char array for output)
  Serial.println(uid); //Print the output uid string
  mfrc522.PICC_HaltA();
  SendData(uid);
}

////////////////////Turn Uid into char string///////////////////////////////////////////////////
void array_to_string(byte array[], unsigned int len, char buffer[])
{
  for (unsigned int i = 0; i < len; i++)
  {
    byte nib1 = (array[i] >> 4) & 0x0F;
    byte nib2 = (array[i] >> 0) & 0x0F;
    buffer[i * 2 + 0] = nib1  < 0xA ? '0' + nib1  : 'A' + nib1  - 0xA;
    buffer[i * 2 + 1] = nib2  < 0xA ? '0' + nib2  : 'A' + nib2  - 0xA;
  }
  buffer[len * 2] = '\0';
}

////////////////////Send piccUID to server//////////////////////////////////////////////////////
void SendData(char UID[32])
{
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http; Serial;

    // Your Domain name with URL path or IP address with path
    http.begin(serverName);

    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Prepare your HTTP POST request data
    //int temperature = lueDHTlampo();
    String httpRequestData = "api_key=" + apiKeyValue + "&deviceid=" + deviceID
                             + "&piccuid=" + UID;

    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);


    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);

    if (httpResponseCode > 0)
    {
      //Serial.print("HTTP Response code: ");
      //Serial.println(httpResponseCode);
    }
    else
    {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else
  {
    Serial.println("WiFi Disconnected");
  }
}

//////////////////////////////////////Get data from server///////////////////////////////////
void getData(char getData[32]) {
  //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;Serial;
    
    // Your Domain name with URL path or IP address with path
    http.begin(serverName2);
    
    int httpCode = http.GET(); //Send the request
      Serial.print("Get command: ");
      Serial.println(serverName);
 
      if (httpCode > 0) { //Check the returning code
        String payload = http.getString();   //Get the request response payload
        Serial.println("payload: " + payload);                     //Print the response payload
        payload.toCharArray(getData,32);
        Serial.println(getData);
                
      } else {
        Serial.println("No response");
      }
      Serial.println("http code: " + String(httpCode));
      http.end();   //Close connection
     
    }
  else
  {   
    Serial.println("--> connection failed");
  }
  delay(2000);
}

/////////////////////////////////////////  Access Granted    ///////////////////////////////////
void granted ( uint16_t setDelay) {
  digitalWrite(blueLed, LOW);   // Turn off blue LED
  digitalWrite(redLed, LOW);  // Turn off red LED
  digitalWrite(greenLed, HIGH);   // Turn on green LED
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);    // tell servo to go to position in variable 'pos'
    delay(15);             // waits 15ms for the servo to reach the position
  }
  delay(setDelay);          // Hold door lock open for given seconds
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);    // tell servo to go to position in variable 'pos'
    delay(15);             // waits 15ms for the servo to reach the position
  }
  delay(1000);            // Hold green LED on for a second
}

///////////////////////////////////////// Access Denied  ///////////////////////////////////
void denied() {
  digitalWrite(greenLed, LOW);  // Make sure green LED is off
  digitalWrite(blueLed, LOW);   // Make sure blue LED is off
  digitalWrite(redLed, HIGH);   // Turn on red LED
  delay(1000);
}

//////////////////////////////////////// Normal Mode Led  ///////////////////////////////////
void normalModeOn ()
{
  digitalWrite(blueLed, HIGH);  // Blue LED ON and ready to read card
  digitalWrite(redLed, LOW);  // Make sure Red LED is off
  digitalWrite(greenLed, LOW);  // Make sure Green LED is off
}
