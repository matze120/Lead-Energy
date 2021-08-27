/*
* The circuit:
*  - pushbutton attached to pin 2 from +5V
*  - 10K resistor attached to pin 2 from ground
*
* created 2021
* by matze120
* GitHub: <https://github.com/matze120/Lead-Energy>
*
*/

#include "LeadDynamic.h"

// Constants for WiFi
const char* ssid     = "yourSSID"; //Change this value for your network
const char* password = "yourPassword"; //Change this value for your network
bool connected = false;

// Constants for IO-Pins
const int buttonPin = 2;     // the number of the pushbutton pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
bool LampOn = false;

// Forward Declaration
void ConnectWiFi(void);
void WiFiEvent(WiFiEvent_t event);
void callback();

// Create object of LeadDynamic
LeadDynamic wohnzimmer("192.168.0.44");


void setup() {
  // Initialize Serial port to get some debug messanges
  Serial.begin(115200);

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  // Init WiFi  
  ConnectWiFi();
}

void loop()
{
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH)
  {
    // turn Lamp "wohnzimmer" on:
    LampState = !LampState;
  }
  // Send the command to the Lamp
  wohnzimmer.OnOffState(LampState);

  // Wait a second for the Lamp to react and to get rid of a bouncing pushbutton
  delay(1000);
}



// Functions needed for WiFi
void ConnectWiFi(void)
{
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  WiFi.disconnect(true);
  WiFi.onEvent(WiFiEvent);
  WiFi.begin(ssid, password);
    // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if(connected){
      digitalWrite(LED_BUILTIN, LOW); //Turn on LED on the Board
    }
    else
    {
      digitalWrite(LED_BUILTIN, HIGH); //Turn off LED on the Board
      setup();
    }
}

void WiFiEvent(WiFiEvent_t event) {
    //Serial.printf("[WiFi-event] event: %d\n", event);  

    switch(event) {
    case 0:
        Serial.println("WL_IDLE_STATUS");
        break;
    case 1:
        Serial.println("WL_NO_SSID_AVAIL");
        break;      
    case 3:
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
        connected = true;
        break;
    case 4:   
        Serial.println("WL_CONNECT_FAILED");
        break;
    case 6:
        Serial.println("WiFi lost connection");
        connected = false;
        break;
    default:
        Serial.print("unhandeled WiFi event: ");
        Serial.println(event);
        break;        
    }

    // 0 : WL_IDLE_STATUS when Wi-Fi is in process of changing between statuses
    // 1 : WL_NO_SSID_AVAILin case configured SSID cannot be reached
    // 3 : WL_CONNECTED after successful connection is established
    // 4 : WL_CONNECT_FAILED if password is incorrect
    // 6 : WL_DISCONNECTED if module is not configured in station mode

}

void callback(){
  //placeholder callback function
}