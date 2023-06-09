#include <WiFi.h>       // standard library
#include <WebServer.h>  // standard library
#include <Wire.h>       // standard libary
#include "Website.h"    // .h file that stores your html page code

// replace this with your homes intranet connect parameters
#define LOCAL_SSID "your_home_ssid"
#define LOCAL_PASS "your_home_password"

// start your defines for pins for sensors, outputs etc.
#define PIN_LED 2     // on board LED

// variables to store LED states and sensors
bool LED0 = false;
char redData = 0;
char greenData = 0;
char blueData = 0;

// the XML array size needs to be bigger that your maximum expected size. For mine 128 is good.
char XML[128];

// just some buffer holder for char operations
char buf[32];

// variable for the IP reported when you connect to your homes intranet (during debug mode)
IPAddress Actual_IP;

// definitions of your desired intranet created by the ESP32
IPAddress ip;

// server
WebServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);

  // turn off led
  LED0 = false;
  digitalWrite(PIN_LED, LED0);

  // Pmod COLOR setup
  Wire.setClock(3400000);
  Wire.begin();
  Wire.beginTransmission(0x29);
  Wire.write(0x80);
  Wire.write(0x01);
  delay(3);
  Wire.endTransmission();
  Wire.beginTransmission(0x29);
  Wire.write(0x80);
  Wire.write(0x03);
  Wire.endTransmission();
  delay(5);

  // if your web page or XML are large, you may not get a call back from the web page
  // and the ESP will think something has locked up and reboot the ESP
  disableCore0WDT();
  disableCore1WDT();

  Serial.println("Starting server");

  // connect to home network
  WiFi.begin(LOCAL_SSID, LOCAL_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("IP address: "); Serial.println(WiFi.localIP());
  Actual_IP = WiFi.localIP();

  printWifiStatus();

  // these calls will handle data coming back from your web page
  // this one is a page request, upon ESP getting / string the web page will be sent
  server.on("/", SendWebsite);

  // upon esp getting /XML string, ESP will build and send the XML, this is how we refresh
  // just parts of the web page
  server.on("/xml", SendXML);

  // code for controlling onboard LED on esp32
  server.on("/BUTTON_0", ProcessButton_0);

  server.begin();
}

void loop() {
  Wire.beginTransmission(0x29);
  Wire.write(0xB6);
  Wire.endTransmission();
  int temp = 0;
  Wire.requestFrom(0x29, 6);
  while(!Wire.available());
  temp = Wire.read();
  while(!Wire.available());
  temp += Wire.read() << 8;
  temp /= 256;
  redData = (char)temp;
  while(!Wire.available());
  temp = Wire.read();
  while(!Wire.available());
  temp += Wire.read() << 8;
  temp /= 256;
  greenData = (char)temp;
  while(!Wire.available());
  temp = Wire.read();
  while(!Wire.available());
  temp += Wire.read() << 8;
  temp /= 256;
  blueData = (char)temp;
  // no matter what you must call this handleClient repeatidly--otherwise the web page
  // will not get instructions to do something
  server.handleClient();
}

// code to send the main web page
// PAGE_MAIN is a large char defined in Website.h
void SendWebsite() {
  Serial.println("Sending web page");
  // you may have to play with this value, big pages need more porcessing time, and hence
  // a longer timeout that 200 ms
  server.send(200, "text/html", PAGE_MAIN);
}

// now process button_0 press from the web site to switch onboard LED
void ProcessButton_0() {
  LED0 = !LED0;
  digitalWrite(PIN_LED, LED0);
  Serial.print("Button 0: "); Serial.println(LED0);
  // send something back since it is expected
  server.send(200, "text/plain", ""); //Send web page
}

// code to send the main web page
void SendXML() {
  Serial.println("Sending xml");
  strcpy(XML, "<?xml version = '1.0'?>\n<Data>\n");
  // send test
  sprintf(buf, "<B0>%d</B0>\n", redData);
  strcat(XML, buf);
  sprintf(buf, "<B1>%d</B1>\n", greenData);
  strcat(XML, buf);
  sprintf(buf, "<B2>%d</B2>\n", blueData);
  strcat(XML, buf);

  strcat(XML, "</Data>\n");
  Serial.println(XML);
  server.send(400, "text/xml", XML);
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("Open http://");
  Serial.println(ip);
}