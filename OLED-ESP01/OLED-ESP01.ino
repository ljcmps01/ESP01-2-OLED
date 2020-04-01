//
// Small Simple OLED library demo
//
// Demonstrates how to initialize and use a few functions of the ss_oled library
// If your MCU has enough RAM, enable the backbuffer to see a demonstration
// of the speed difference between drawing directly on the display versus
// deferred rendering, followed by a "dump" of the memory to the display
//
#include <ss_oled.h>
#include "ESPHelper.h"
// if your system doesn't have enough RAM for a back buffer, comment out
// this line (e.g. ATtiny85)
#define USE_BACKBUFFER

#ifdef USE_BACKBUFFER
static uint8_t ucBackBuffer[1024];
#else
static uint8_t *ucBackBuffer = NULL;
#endif

netInfo homeNet = {  .mqttHost = "",     //can be blank if not using MQTT
          .mqttUser = "",   //can be blank
          .mqttPass = "",   //can be blank
          .mqttPort = 1883,         //default port for MQTT is 1883 - only chance if needed.
          .ssid = "Campos", 
          .pass = "perico15"};

ESPHelper myESP(&homeNet);

void setup() {
int rc;
// The I2C SDA/SCL pins set to -1 means to use the default Wire library
// If pins were specified, they would be bit-banged in software
// This isn't inferior to hw I2C and in fact allows you to go faster on certain CPUs
// The reset pin is optional and I've only seen it needed on larger OLEDs (2.4")
//    that can be configured as either SPI or I2C
//
// oledInit(type, rotate180, invert, SDA_PIN, SCL_PIN, RESET_PIN, speed)

rc = oledInit(OLED_128x64, 0, 0, 0, 2, -1, 400000L); // use standard I2C bus at 400Khz
  if (rc != OLED_NOT_FOUND)
  {
    char *msgs[] = {(char *)"SSD1306 @ 0x3C", (char *)"SSD1306 @ 0x3D",(char *)"SH1106 @ 0x3C",(char *)"SH1106 @ 0x3D"};
    oledFill(0, 1);
    oledWriteString(0,0,0,msgs[rc], FONT_NORMAL, 0, 1);
    oledSetBackBuffer(ucBackBuffer);
    delay(2000);
  }
  oledFill(0,1);
  oledWriteString(0,0,0,(char *)"Setting up OTA", FONT_NORMAL,1,1);
myESP.OTA_enable();
myESP.OTA_setPassword("123");
myESP.OTA_setHostname("ESP01-A");
myESP.begin();
  oledWriteString(0,0,2,(char *)"OTA ready!!", FONT_LARGE,0,1);
  oledSetBackBuffer(ucBackBuffer);
  oledFill(0x0, 1);
  delay(1000);

} /* setup() */

void loop() {
  myESP.loop();  //run the loop() method as often as possible - this keeps the network services running
  // put your main code here, to run repeatedly:
int i, x, y;
String mensaje="Prueba Alejo";
String msg= "Hola probando las string en arduino";
int caracteres=msg.length(), Div=caracteres/21,rde=3-Div/2;
String renglon[8];
  myESP.loop();
for(int i=0;i<=Div;i++){
  renglon[i]=msg.substring(21*i,21+21*i);
  myESP.loop();
}
unsigned long ms;
  myESP.loop();
  
  oledWriteString(0,16,0,(char *)"ss_oled Demo", FONT_NORMAL, 0, 1);
  oledWriteString(0,0,1,(char *)mensaje.c_str(), FONT_SMALL, 1, 1);
  oledWriteString(0,0,5,(char *)"1237890", FONT_SMALL, 0, 1);
  oledWriteString(0,0,6,(char *)"11111111111111111111", FONT_SMALL, 0, 1);
  oledWriteString(0,0,7,(char *)"place", FONT_SMALL, 0, 1);
  oledWriteString(0,32,7,(char *)"place", FONT_SMALL, 0, 1);
  oledWriteString(0,99,7,(char *)"place", FONT_SMALL, 0, 1);
  
  delay(1000);
  oledSetBackBuffer(ucBackBuffer);
  oledFill(0x0,1);
  myESP.loop();  //run the loop() method as often as possible - this keeps the network services running
  delay(1000);
  for(int i=0;i<=Div;i++){
  myESP.loop();
  oledWriteString(0,0,rde+i,(char *)renglon[i].c_str(), FONT_SMALL, 0, 1);
  delay(750);
  }
  delay(2000);
  oledFill(0x0,1);
  myESP.loop();
  delay(1000);
  
  yield();

} /* loop() */
