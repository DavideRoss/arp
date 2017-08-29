#include <Encoder.h>

#define DIVIDER 4
#define SHIFT 4

long realValue = -999;
long encValue = -999;

bool shift = LOW;
bool lastShift = LOW;
bool lastRead = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

Encoder enc(5, 6);

void controls_setup() {
    pinMode(SHIFT, INPUT);
}

void controls_loop() {
    read_encoder();
    read_shift();
}

void read_encoder() {
    long newVal = enc.read();

    if (newVal != realValue) {
        realValue = newVal;
        encValue = realValue / DIVIDER;
    }
}

void read_shift() {
    // int read = digitalRead(SHIFT);

    // if (read != lastRead) {
    //     lastDebounceTime = millis();
    // }

    // if ((millis() - lastDebounceTime) > debounceDelay) {
    //     if (read != shift) {
    //         shift = read;
    //     }
    // }
    
    // lastRead = read;

    lastShift = shift;
    shift = digitalRead(SHIFT);
}