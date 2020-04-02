/*Testeo de control de OLED con ESP01 basico (NoWiFi)
  7-     8-VCC
  5-SDA  6-Rst (VCC)
  3-SCL  4-CE(VCC)
  1-GND  2-
*/
#include <ss_oled.h>

// if your system doesn't have enough RAM for a back buffer, comment out
// this line (e.g. ATtiny85)
#define USE_BACKBUFFER

#ifdef USE_BACKBUFFER
static uint8_t ucBackBuffer[1024];
#else
static uint8_t *ucBackBuffer = NULL;
#endif

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
} /* setup() */

void loop() {
  // put your main code here, to run repeatedly:
int i, x, y;
char szTemp[32];
unsigned long ms;

  oledFill(0x0, 1);
  oledWriteString(0,16,0,(char *)"ss_oled Demo", FONT_NORMAL, 0, 1);
  oledWriteString(0,0,1,(char *)"Written by Larry Bank", FONT_SMALL, 1, 1);
  oledWriteString(0,0,3,(char *)"**Demo**", FONT_LARGE, 0, 1);
  delay(2000);
  
 // Pixel and line functions won't work without a back buffer
#ifdef USE_BACKBUFFER
  oledFill(0, 1);
  oledWriteString(0,0,0,(char *)"Backbuffer Test", FONT_NORMAL,0,1);
  oledWriteString(0,0,1,(char *)"3000 Random dots", FONT_NORMAL,0,1);
  delay(2000);
  oledFill(0,1);
  ms = millis();
  for (i=0; i<3000; i++)
  {
    x = random(128);
    y = random(64);
    oledSetPixel(x, y, 1, 1);
  }
  ms = millis() - ms;
  sprintf(szTemp, "%dms", (int)ms);
  oledWriteString(0,0,0,szTemp, FONT_NORMAL, 0, 1);
  oledWriteString(0,0,1,(char *)"Without backbuffer", FONT_SMALL,0,1);
  delay(2000);
  oledFill(0,1);
  ms = millis();
  for (i=0; i<3000; i++)
  {
    x = random(128);
    y = random(64);
    oledSetPixel(x, y, 1, 0);
  }
  oledDumpBuffer(NULL);
  ms = millis() - ms;
  sprintf(szTemp, "%dms", (int)ms);
  oledWriteString(0,0,0,szTemp, FONT_NORMAL, 0, 1);
  oledWriteString(0,0,1,(char *)"With backbuffer", FONT_SMALL,0,1);
  delay(2000);
  oledFill(0, 1);
  oledWriteString(0,0,0,(char *)"Backbuffer Test", FONT_NORMAL,0,1);
  oledWriteString(0,0,1,(char *)"96 lines", FONT_NORMAL,0,1);
  delay(2000);
  ms = millis();
  for (x=0; x<127; x+=2)
  {
    oledDrawLine(x, 0, 127-x, 63, 1);
  }
  for (y=0; y<63; y+=2)
  {
    oledDrawLine(127,y, 0,63-y, 1);
  }
  ms = millis() - ms;
  sprintf(szTemp, "%dms", (int)ms);
  oledWriteString(0,0,0,szTemp, FONT_NORMAL, 0, 1);
  oledWriteString(0,0,1,(char *)"Without backbuffer", FONT_SMALL,0,1);
  delay(2000);
  oledFill(0,1);
  ms = millis();
  for (x=0; x<127; x+=2)
  {
    oledDrawLine(x, 0, 127-x, 63, 0);
  }
  for (y=0; y<63; y+=2)
  {
    oledDrawLine(127,y, 0,63-y, 0);
  }
  oledDumpBuffer(ucBackBuffer);
  ms = millis() - ms;
  sprintf(szTemp, "%dms", (int)ms);
  oledWriteString(0,0,0,szTemp, FONT_NORMAL, 0, 1);
  oledWriteString(0,0,1,(char *)"With backbuffer", FONT_SMALL,0,1);
  delay(2000);
#endif
} /* loop() */
