#define ENC1 2
#define ENC2 3

#define SHIFT 16

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastEncoderValue = 0;

int shiftState = LOW;
int lastShiftState = LOW;

void controls_setup() {
    pinMode(ENC1, INPUT);
    pinMode(ENC2, INPUT);
    pinMode(SHIFT, INPUT_PULLUP);

    digitalWrite(ENC1, HIGH);
    digitalWrite(ENC2, HIGH);

    attachInterrupt(0, updateEncoder, CHANGE);
    attachInterrupt(1, updateEncoder, CHANGE);
}

void controls_loop() {
    lastShiftState = shiftState;
    shiftState = !digitalRead(SHIFT);
}

void updateEncoder() {
    int MSB = digitalRead(ENC1);
    int LSB = digitalRead(ENC2);

    int encoded = (MSB << 1) | LSB;
    int sum = (lastEncoded << 2) | encoded;

    if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
    if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;
 
    lastEncoded = encoded;
}
