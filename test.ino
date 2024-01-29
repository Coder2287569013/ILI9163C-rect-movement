// #include <SPI.h>
// #include <Adafruit_GFX.h>
// #include <TFT_ILI9163C.h>


// // Color definitions
// #define	BLACK   0x0000
// #define	BLUE    0x001F
// #define	RED     0xF800
// #define	GREEN   0x07E0
// #define CYAN    0x07FF
// #define MAGENTA 0xF81F
// #define YELLOW  0xFFE0  
// #define WHITE   0xFFFF

// /*
// Teensy3.x and Arduino's
// You are using 4 wire SPI here, so:
//  MOSI:  11//Teensy3.x/Arduino UNO (for MEGA/DUE refere to arduino site)
//  MISO:  12//Teensy3.x/Arduino UNO (for MEGA/DUE refere to arduino site)
//  SCK:   13//Teensy3.x/Arduino UNO (for MEGA/DUE refere to arduino site)
//  the rest of pin below:
//  */
// #define __CS 10
// #define __DC 9
// /*
// Teensy 3.x can use: 2,6,9,10,15,20,21,22,23
// Arduino's 8 bit: any
// DUE: check arduino site
// If you do not use reset, tie it to +3V3
// */


// TFT_ILI9163C tft = TFT_ILI9163C(__CS,8, __DC);
// class Rect {
//   public:
//     int16_t x;
//     int16_t y;
//     int16_t w;
//     int16_t h;
//     uint16_t color;
//     Rect(int16_t xCor, int16_t yCor, int16_t wRect, int16_t hRect, uint16_t colorRect) {
//       x = xCor;
//       y = yCor;
//       w = wRect;
//       h = hRect;
//       color = colorRect;
//     };
//     void moveRight(uint16_t speed) {
//       int buttonState = digitalRead(2);
//       if (buttonState == HIGH) {
//         Serial.println(digitalRead(2));
//         x += speed;
//       }
//     }
//     void moveLeft(uint16_t speed) {
//       int buttonState = digitalRead(3);
//       if (buttonState == HIGH) {
//         Serial.println(digitalRead(3));
//         x -= speed;
//       }
//     }
//     void moveDown(uint16_t speed) {
//       int buttonState = digitalRead(4);
//       if (buttonState == HIGH) {
//         Serial.println(digitalRead(4));
//         y += speed;
//       }
//     }
//     void moveUp(uint16_t speed) {
//       int buttonState = digitalRead(5);
//       if (buttonState == HIGH) {
//         Serial.println(digitalRead(5));
//         y -= speed;
//       }
//     }
//     void drawRect() {
//       tft.fillRect(x,y,w,h,color);
//     }
// };
// Rect rect(25,25,25,70,RED);
// void setup() {
//   SPI.begin();
//   SPI.setClockDivider(SPI_CLOCK_DIV4); // This sets the SPI clock to its highest speed
//   tft.begin(); 
//   pinMode(2,INPUT);
//   pinMode(3,INPUT);
//   pinMode(4,INPUT);
//   pinMode(5,INPUT);
//   Serial.begin(9600);
// }

// void loop(){
//   tft.fillScreen(BLACK);
//   rect.moveRight(2);
//   rect.moveLeft(3);
//   rect.moveDown(4);
//   rect.moveUp(5);
//   rect.drawRect();
//   delay(16)
// }

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <TFT_ILI9163C.h>

#define BLACK   0x0000
#define RED     0xF800

#define __CS    10
#define __DC    9

TFT_ILI9163C tft = TFT_ILI9163C(__CS, 8, __DC);

class Rect {
public:
    int16_t x, y, w, h;
    uint16_t color;
    Rect(int16_t xCor, int16_t yCor, int16_t wRect, int16_t hRect, uint16_t colorRect)
        : x(xCor), y(yCor), w(wRect), h(hRect), color(colorRect) {}

    void updatePosition(int16_t dx, int16_t dy) {
        if (dx != 0 || dy != 0) {
            tft.fillRect(x, y, w, h, BLACK);

            // Update position
            x += dx;
            y += dy;

            // Draw new rectangle
            tft.fillRect(x, y, w, h, color);
        }
    }
};

Rect rect(25, 25, 15, 30, RED);

void setup() {
    tft.begin();
    tft.fillScreen(BLACK);
    pinMode(2, INPUT_PULLUP);
    pinMode(3, INPUT_PULLUP);
    pinMode(4, INPUT_PULLUP);
    pinMode(5, INPUT_PULLUP);
    Serial.begin(9600);
    tft.fillRect(rect.x, rect.y, rect.w, rect.h, rect.color);
}

void loop() {
    int dx = 0, dy = 0;

    if (digitalRead(2) == LOW && rect.x+rect.w < 127) dx += 2; // Move right
    if (digitalRead(3) == LOW && rect.x > 1) dx -= 2; // Move left
    if (digitalRead(4) == LOW && rect.y+rect.h < 127) dy += 2; // Move down
    if (digitalRead(5) == LOW && rect.y > 1) dy -= 2; // Move up

    rect.updatePosition(dx, dy);

}