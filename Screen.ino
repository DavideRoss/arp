#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16

byte mode = 0;
String modes[6] = {
    "Base",
    "Steps",
    "Scale",
    "BPM",
    "Rate",
    "Gate"
};

long lastEnc = 0;

void screen_setup() {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void screen_loop() {
    if (shift == LOW && lastShift == HIGH) {
        mode++;
        if (mode > 5) mode = 0;
    }

    handleEncoder();

    display.clearDisplay();
    drawTemplate();
    display.display();
}

void handleEncoder() {
    long encDelta = encValue - lastEnc;
    lastEnc = encValue;

    if (encDelta == 0) return;

    if (mode == 0) {
        start += encDelta;

        if (start < 0) start = 0;
        if (start > 127) start = 127;
    } else if (mode == 1) {
        steps += encDelta;

        if (steps < 1) steps = 1;
        if (steps > 8) steps = 8;
    } else if (mode == 2) {
        scale += encDelta;

        if (scale < 0) scale = 0;
        if (scale > 8) scale = 8;
    } else if (mode == 3) {
        bpm += encDelta;

        if (bpm < 60) bpm = 60;
        if (bpm > 240) bpm = 240;
    } else if (mode == 4) {
        rate += encDelta;
        if (rate < 0) rate = 0;
        if (rate > 7) rate = 7;
    } else {
        gate += float(encDelta) * .01f;

        if (gate < .01f) gate = .01f;
        if (gate > .99f) gate = .99f;
    }
}

void drawTemplate() {
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println(modes[mode]);

    display.setCursor(0, 24);
    display.setTextSize(4);
    
    if (mode == 0) {
        int noteIndex = start % 12;
        int octave = (start / 12) - 1;

        display.println(notes[noteIndex] + String(octave));
    } else if (mode == 1) {
        display.println(steps);
    } else if (mode == 2) {
        display.println(scaleNames[scale]);
    } else if (mode == 3) {
        display.println(bpm);
    } else if (mode == 4) {
        display.println(rateNames[rate]);
    } else {
        display.println(String(int(gate * 100)) + "%");
    }
}

