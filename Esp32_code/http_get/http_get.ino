
  #include <WiFi.h>
  #include <HTTPClient.h>


// Replace with your network credentials
const char* ssid     = "kassu2.4GHZ";
const char* password = "omaverkko";

// REPLACE with your Domain name and URL path or IP address with path
const char* serverName = "http://192.168.0.101/esp-data.php";

// Keep this API Key value to be compatible with the PHP code provided in the project page. 
// If you change the apiKeyValue value, the PHP file /post-esp-data.php also needs to have the same key 
String apiKeyValue = "tPmAT5Ab3j7F9";

String sensorName = "ESP8266";
String sensorLocation = "Home at bdr";
String tester = "A3647B40 \n";
String huuhaa = "A3647B40";

void setup()
{
  Serial.begin(115200);
  //dht.begin();                    //Start the dht sensor
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  
  while(WiFi.status() != WL_CONNECTED)
  { 
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  //.println(WiFi.localIP());
}

void loop() {
  //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;Serial;
    
    // Your Domain name with URL path or IP address with path
    http.begin(serverName);
    
    int httpCode = http.GET(); //Send the request
      Serial.print("Get command: ");
      Serial.println(serverName);
 
      if (httpCode > 0) { //Check the returning code
        String payload = http.getString();   //Get the request response payload
        Serial.println("payload: " + payload);                     //Print the response payload
        String sendpayload = String(payload);
        DoStuff(sendpayload);        
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
  delay(25000);
}

void DoStuff(String payload){
  Serial.println(payload);
  if(payload == tester)
  {
    Serial.println("faohgowhgoahgojaoehgjeojgioqehgoiaehgohaoghagiojheg");
  }
  else
  {
    Serial.println("Ei toimi");
  }


  if(huuhaa == tester)
  {
    Serial.println("testerertiettieyeadiet");
  }
  else
  {
    Serial.println("Ei toimi TESTERIIIIII");
  }
}
