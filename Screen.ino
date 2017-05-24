#include <LiquidCrystal.h>

#define RS 9
#define ENABLE 8

#define DB7 4
#define DB6 5
#define DB5 6
#define DB4 7

#define HALF 8

LiquidCrystal lcd(RS, ENABLE, DB4, DB5, DB6, DB7);

// NOTE+OCT     STEPS
// SCALE        SPEED
byte mode = 0;

void screen_setup() {
    lcd.begin(16, 2);
    lcd.print(">BASE   -STEPS  ");
}   

void screen_loop() {
    if (lastShiftState == LOW && shiftState == HIGH) {
        mode++;
        if (mode >= 4) mode = 0;
    }

    lcd.setCursor(0, 0);
    lcd.print(get_line());

    lcd.setCursor(0, 1);
    
    if (mode < 2) {
        lcd.print(pad_left(String(currentNote)));
        lcd.setCursor(8, 1);
        lcd.print(pad_left(String(steps)));
    } else {
        lcd.print(pad_left("Aeolian"));
        lcd.setCursor(8, 1);
        lcd.print(pad_left("130"));
    }
}

String pad_right(int val) {
    char buff[HALF];
    sprintf(buff, "%4d", val);
    return String(buff);
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
    } else {
        s += mode == 2? ">" : "-";
        s += "SCALE  ";
        s += mode == 3? ">" : "-";
        s += "SPEED  ";
    }

    return s;
}
