#include "Arduino.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#define LED_BUILTIN 22
Adafruit_ST7735 tft = Adafruit_ST7735(16, 17, 23, 5, 9); // CS,A0,SDA,SCK,RESET
float r, x1, ya, z1, x2, y2, z2, x3, y3, z3;             //
int f[8][2], x, y;                                       // Draw box, x, y center
int c[8][3] = {                                          // Cube
    {-20, -20, 20},
    {20, -20, 20},
    {20, 20, 20},
    {-20, 20, 20},
    {-20, -20, -20},
    {20, -20, -20},
    {20, 20, -20},
    {-20, 20, -20}};

float p = 3.1415926;

void testlines(uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0, 0, x, tft.height()-1, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0, 0, tft.width()-1, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1, 0, x, tft.height()-1, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1, 0, 0, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0, tft.height()-1, x, 0, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0, tft.height()-1, tft.width()-1, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1, tft.height()-1, x, 0, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1, tft.height()-1, 0, y, color);
    delay(0);
  }
}

void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void testfastlines(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t y=0; y < tft.height(); y+=5) {
    tft.drawFastHLine(0, y, tft.width(), color1);
  }
  for (int16_t x=0; x < tft.width(); x+=5) {
    tft.drawFastVLine(x, 0, tft.height(), color2);
  }
}

void testdrawrects(uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color);
  }
}

void testfillrects(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=tft.width()-1; x > 6; x-=6) {
    tft.fillRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color1);
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color2);
  }
}

void testfillcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=radius; x < tft.width(); x+=radius*2) {
    for (int16_t y=radius; y < tft.height(); y+=radius*2) {
      tft.fillCircle(x, y, radius, color);
    }
  }
}

void testdrawcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=0; x < tft.width()+radius; x+=radius*2) {
    for (int16_t y=0; y < tft.height()+radius; y+=radius*2) {
      tft.drawCircle(x, y, radius, color);
    }
  }
}

void testtriangles() {
  tft.fillScreen(ST77XX_BLACK);
  int color = 0xF800;
  int t;
  int w = tft.width()/2;
  int x = tft.height()-1;
  int y = 0;
  int z = tft.width();
  for(t = 0 ; t <= 15; t++) {
    tft.drawTriangle(w, y, y, x, z, x, color);
    x-=4;
    y+=4;
    z-=4;
    color+=100;
  }
}

void testroundrects() {
  tft.fillScreen(ST77XX_BLACK);
  int color = 100;
  int i;
  int t;
  for(t = 0 ; t <= 4; t+=1) {
    int x = 0;
    int y = 0;
    int w = tft.width()-2;
    int h = tft.height()-2;
    for(i = 0 ; i <= 16; i+=1) {
      tft.drawRoundRect(x, y, w, h, 5, color);
      x+=2;
      y+=3;
      w-=4;
      h-=6;
      color+=1100;
    }
    color+=100;
  }
}

void tftPrintTest() {
  tft.setTextWrap(false);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 30);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(3);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_BLUE);
  tft.setTextSize(4);
  tft.print(1234.567);
  delay(1500);
  tft.setCursor(0, 0);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(0);
  tft.println("Hello World!");
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_GREEN);
  tft.print(p, 6);
  tft.println(" Want pi?");
  tft.println(" ");
  tft.print(8675309, HEX); // print 8,675,309 out in HEX!
  tft.println(" Print HEX!");
  tft.println(" ");
  tft.setTextColor(ST77XX_WHITE);
  tft.println("Sketch has been");
  tft.println("running for: ");
  tft.setTextColor(ST77XX_MAGENTA);
  tft.print(millis() / 1000);
  tft.setTextColor(ST77XX_WHITE);
  tft.print(" seconds.");
}

void mediabuttons() {
  // play
  tft.fillScreen(ST77XX_BLACK);
  tft.fillRoundRect(25, 10, 78, 60, 8, ST77XX_WHITE);
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_RED);
  delay(500);
  // pause
  tft.fillRoundRect(25, 90, 78, 60, 8, ST77XX_WHITE);
  tft.fillRoundRect(39, 98, 20, 45, 5, ST77XX_GREEN);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST77XX_GREEN);
  delay(500);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_BLUE);
  delay(50);
  // pause color
  tft.fillRoundRect(39, 98, 20, 45, 5, ST77XX_RED);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST77XX_RED);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_GREEN);
}

void setup(void)
{
  pinMode(27, INPUT);           //Backlight:27
  digitalWrite(27, HIGH);       //New version added to backlight control
  tft.initR(INITR_18GREENTAB);  // 1.44 v2.1
  tft.fillScreen(ST7735_BLACK); // CLEAR
  tft.setTextColor(0x5FCC);     // GREEN
  tft.setRotation(1);           //
  x = tft.width() / 2;
  x = x + 14;           // x Center Calculat
  y = tft.height() / 2; // y Center Calculate
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.println(F("Initialized"));

  uint16_t time = millis();
  tft.fillScreen(ST77XX_BLACK);
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);

  // large block of text
  tft.fillScreen(ST77XX_BLACK);
  testdrawtext("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere. ", ST77XX_WHITE);
  delay(1000);

  // tft print function!
  tftPrintTest();
  delay(4000);

  // a single pixel
  tft.drawPixel(tft.width()/2, tft.height()/2, ST77XX_GREEN);
  delay(500);

  // line draw test
  testlines(ST77XX_YELLOW);
  delay(500);

  // optimized lines
  testfastlines(ST77XX_RED, ST77XX_BLUE);
  delay(500);

  testdrawrects(ST77XX_GREEN);
  delay(500);

  testfillrects(ST77XX_YELLOW, ST77XX_MAGENTA);
  delay(500);

  tft.fillScreen(ST77XX_BLACK);
  testfillcircles(10, ST77XX_BLUE);
  testdrawcircles(10, ST77XX_WHITE);
  delay(500);

  testroundrects();
  delay(500);

  testtriangles();
  delay(500);

  mediabuttons();
  delay(500);

  Serial.println("done");
  delay(1000);
}

void loop()
{
    tft.invertDisplay(true);
  delay(500);
  tft.invertDisplay(false);
  delay(500);
  // for (int a = 0; a <= 360; a = a + 2)
  // { // 0 to 360 degree
  //   tft.drawLine(f[0][0], f[0][1], f[1][0], f[1][1], ST7735_BLACK);
  //   tft.drawLine(f[1][0], f[1][1], f[2][0], f[2][1], ST7735_BLACK);
  //   tft.drawLine(f[2][0], f[2][1], f[3][0], f[3][1], ST7735_BLACK);
  //   tft.drawLine(f[3][0], f[3][1], f[0][0], f[0][1], ST7735_BLACK);
  //   tft.drawLine(f[4][0], f[4][1], f[5][0], f[5][1], ST7735_BLACK);
  //   tft.drawLine(f[5][0], f[5][1], f[6][0], f[6][1], ST7735_BLACK);
  //   tft.drawLine(f[6][0], f[6][1], f[7][0], f[7][1], ST7735_BLACK);
  //   tft.drawLine(f[7][0], f[7][1], f[4][0], f[4][1], ST7735_BLACK);
  //   tft.drawLine(f[0][0], f[0][1], f[4][0], f[4][1], ST7735_BLACK);
  //   tft.drawLine(f[1][0], f[1][1], f[5][0], f[5][1], ST7735_BLACK);
  //   tft.drawLine(f[2][0], f[2][1], f[6][0], f[6][1], ST7735_BLACK);
  //   tft.drawLine(f[3][0], f[3][1], f[7][0], f[7][1], ST7735_BLACK);
  //   tft.drawLine(f[1][0], f[1][1], f[3][0], f[3][1], ST7735_BLACK); // cross
  //   tft.drawLine(f[0][0], f[0][1], f[2][0], f[2][1], ST7735_BLACK); // cross
  //   for (int i = 0; i < 8; i++)
  //   {                                           //
  //     r = a * 0.0174532;                        // 1 degree
  //     x1 = c[i][2] * sin(r) + c[i][0] * cos(r); // rotate Y
  //     ya = c[i][1];                             //
  //     z1 = c[i][2] * cos(r) - c[i][0] * sin(r); //
  //     x2 = x1;                                  //
  //     y2 = ya * cos(r) - z1 * sin(r);           // rotate X
  //     z2 = ya * sin(r) + z1 * cos(r);           //
  //     x3 = x2 * cos(r) - y2 * sin(r);           // rotate Z
  //     y3 = x2 * sin(r) + y2 * cos(r);           //
  //     z3 = z2;
  //     x3 = x3 + x;
  //     y3 = y3 + y; //
  //     f[i][0] = x3;
  //     f[i][1] = y3;
  //     f[i][2] = z3; // store new values
  //   }
  //   //  tft.fillScreen(ST7735_BLACK);
  //   tft.drawLine(f[0][0], f[0][1], f[1][0], f[1][1], ST7735_WHITE);
  //   tft.drawLine(f[1][0], f[1][1], f[2][0], f[2][1], ST7735_WHITE);
  //   tft.drawLine(f[2][0], f[2][1], f[3][0], f[3][1], ST7735_WHITE);
  //   tft.drawLine(f[3][0], f[3][1], f[0][0], f[0][1], ST7735_WHITE);
  //   tft.drawLine(f[4][0], f[4][1], f[5][0], f[5][1], ST7735_WHITE);
  //   tft.drawLine(f[5][0], f[5][1], f[6][0], f[6][1], ST7735_WHITE);
  //   tft.drawLine(f[6][0], f[6][1], f[7][0], f[7][1], ST7735_WHITE);
  //   tft.drawLine(f[7][0], f[7][1], f[4][0], f[4][1], ST7735_WHITE);
  //   tft.drawLine(f[0][0], f[0][1], f[4][0], f[4][1], ST7735_WHITE);
  //   tft.drawLine(f[1][0], f[1][1], f[5][0], f[5][1], ST7735_WHITE);
  //   tft.drawLine(f[2][0], f[2][1], f[6][0], f[6][1], ST7735_WHITE);
  //   tft.drawLine(f[3][0], f[3][1], f[7][0], f[7][1], ST7735_WHITE);
  //   tft.drawLine(f[1][0], f[1][1], f[3][0], f[3][1], ST7735_WHITE); // cross
  //   tft.drawLine(f[0][0], f[0][1], f[2][0], f[2][1], ST7735_WHITE); // cross
  // }
  // digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  // delay(1000);                       // wait for a second
  // digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  // delay(1000);                       // wait for a second
}
