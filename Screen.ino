#include <LiquidCrystal.h>

#define RS 9
#define ENABLE 8

#define DB7 4
#define DB6 5
#define DB5 6
#define DB4 7

#define DIVIDER 4

LiquidCrystal lcd(RS, ENABLE, DB4, DB5, DB6, DB7);

// BASE         STEPS
// SCALE        BPM
// RATE         GATE
byte mode = 0;

int module = 0;
int lastModule = 0;

void screen_setup() {
    lcd.begin(16, 2);
    draw();
}   

void screen_loop() {
    // ============================================================================================
    // ===== MODE CHANGE ==========================================================================
    // ============================================================================================

    if (lastShiftState == LOW && shiftState == HIGH) {
        mode++;
        if (mode >= 6) mode = 0;

        draw();
    }

    // ============================================================================================
    // ===== VALUE CHANGE =========================================================================
    // ============================================================================================

    int module = encoderValue / DIVIDER;
    int encDelta = module - lastModule;
    lastModule = module;

    if (encDelta > 1) encDelta = 1;
    if (encDelta < -1) encDelta = -1;

    if (encDelta != 0) {
        Serial.println(encDelta);
        
        if (mode == 0) {
            // Base note (0-127)
            currentNote += encDelta;

            if (currentNote < 0) currentNote = 0;
            if (currentNote > 127) currentNote = 127;
        } else if (mode == 1) {
            // Steps (1-8)
            steps += encDelta;

            if (steps < 1) steps = 1;
            if (steps > 8) steps = 8;
        } else if (mode == 2) {
            // Scale (see Midi.ino:18)
            scale += encDelta;

            if (scale < 0) scale = 0;
            if (scale > 8) scale = 8;
        } else if (mode == 3) {
            // BPM (60-240)
            bpm += encDelta;

            if (bpm < 60) bpm = 60;
            if (bpm > 240) bpm = 240;

            calculate_ms();
        } else if (mode == 4) {
            // Rate (1/1-1/16)

            rate += encDelta;

            if (rate < 0) rate = 0;
            if (rate > 7) rate = 7;

            calculate_ms();
        } else if (mode == 5) {
            // Gate (0.01 - 0.99)

            gate += float(encDelta) * .01f;

            if (gate < .01f) gate = .01f;
            if (gate > 0.99f) gate = 0.99f;

            calculate_gate();
        }

        draw();
    }
}

void draw() {
    lcd.setCursor(0, 0);
    lcd.print(get_line());
    lcd.setCursor(0, 1);
    
    if (mode < 2) {
        int noteIndex = currentNote % 12;
        int octave = (currentNote / 12) - 1;
        
        lcd.print(pad_left(notes[noteIndex] + String(octave)));
        lcd.setCursor(8, 1);
        lcd.print(pad_left(String(steps)));
    } else if (mode >= 2 && mode < 4) {
        lcd.print(pad_left(scaleNames[scale]));
        lcd.setCursor(8, 1);
        lcd.print(pad_left(String(bpm)));
    } else {
        lcd.print(pad_left(rateNames[rate]));
        lcd.setCursor(8, 1);
        lcd.print(pad_left(String(int(gate * 100)) + "%"));
    }
}

String pad_left(String val) {
    int diff = 8 - val.length() + 1;
    String s = val;

    for(int i = 0; i < diff; i++) {
        s += " ";
    }

    return s;
}

String get_line() {
    String s = "";

    if (mode < 2) {
        s += mode == 0? ">" : "-";
        s += "BASE   ";
        s += mode == 1? ">" : "-";
        s += "STEPS  ";
    } else if (mode >= 2 && mode < 4) {
        s += mode == 2? ">" : "-";
        s += "SCALE  ";
        s += mode == 3? ">" : "-";
        s += "BPM    ";
    } else {
        s += mode == 4? ">" : "-";
        s += "RATE   ";
        s += mode == 5? ">" : "-";
        s += "GATE   ";
    }

    return s;
}
