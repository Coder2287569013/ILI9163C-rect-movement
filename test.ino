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

    if (digitalRead(2) == LOW && rect.x > 1) dx -= 1; 
    if (digitalRead(3) == LOW && rect.y+rect.h < 127) dy += 1; 
    if (digitalRead(4) == LOW && rect.y > 1) dy -= 1; 
    if (digitalRead(5) == LOW && rect.x+rect.w < 127) dx += 1; 

    rect.updatePosition(dx, dy);

}
