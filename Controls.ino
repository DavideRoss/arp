#define POT_1 18
#define POT_2 19
#define POT_3 20
#define POT_4 21

#define SHIFT 10

int pots[] = {0, 0, 0, 0};
int shiftState = LOW;

void controls_setup() {
    pinMode(POT_1, INPUT);
    pinMode(POT_2, INPUT);
    pinMode(POT_3, INPUT);
    pinMode(POT_4, INPUT);

    pinMode(SHIFT, INPUT);
}

void controls_loop() {
    pots[0] = analogRead(POT_1);
    pots[1] = analogRead(POT_2);
    pots[2] = analogRead(POT_3);
    pots[3] = analogRead(POT_4);

    shiftState = digitalRead(SHIFT);
}
