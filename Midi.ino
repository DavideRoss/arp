#define NOTE_C 0
#define NOTE_C_SHARP 1
#define NOTE_D 2
#define NOTE_D_SHARP 3
#define NOTE_E 4
#define NOTE_F 5
#define NOTE_F_SHARP 6
#define NOTE_G 7
#define NOTE_G_SHARP 8
#define NOTE_A 9
#define NOTE_A_SHARP 10
#define NOTE_B 11

#define LED 14

String notes[] = {
    "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"
};

String scaleNames[] = {
    "Ionian",
    "Dorian",
    "Phrygi.",
    "Lydian",
    "Mixoly.",
    "Aeolian",
    "Locrian",
    "Melodic",
    "Harmon."
};

int scales[9][7] = {
    { 0, 2, 4, 5, 7, 9, 11 }, // ionian
    { 0, 2, 3, 5, 7, 9, 10 }, // dorian
    { 0, 1, 3, 5, 7, 8, 10 }, // phrygian
    { 0, 2, 4, 6, 7, 9, 11 }, // lydian
    { 0, 2, 4, 5, 7, 9, 10 }, // mixolydian
    { 0, 2, 3, 5, 7, 8, 10 }, // aeolian
    { 0, 1, 3, 5, 6, 8, 10 }, // locrian
    { 0, 2, 3, 5, 7, 9, 11 }, // melodic
    { 0, 2, 3, 5, 7, 8, 11 } // harmonic
};

int scale = 0;
int scaleLen = sizeof(scales[scale]) / sizeof(int);

int currentNote = 60;
int start = 60;
int counter = 0;
int incIndex = 0;
int inc = 1;
int steps = 4;

float gate = 0.5f;
int ms = 0;
int gateMs = 0;
int bpm = 130;

unsigned long lastTime = 0;
unsigned long lastGateTime = 0;

unsigned long dbgCounter = 0;

bool waitForGate = false;

void midi_setup() {
    calculate_ms();

    pinMode(LED, OUTPUT);
}

void midi_loop() {
    int curr = millis();

    if (curr - lastTime > ms) {
        lastTime = curr;
        lastGateTime = curr;

        Serial.print("Tick - ");
        Serial.println(dbgCounter);

        digitalWrite(LED, HIGH);

        waitForGate = true;
    }

    if (waitForGate) {
        if (curr - lastGateTime > gateMs) {
            Serial.print("Gate - ");
            Serial.println(dbgCounter);

            digitalWrite(LED, LOW);

            waitForGate = false;
            dbgCounter++;
        }
    }
}

void send_midi() {
    int noteIndex = currentNote % 12;
    int octave = (currentNote / 12) - 1;

    Serial.print(notes[noteIndex]);
    Serial.print(octave);
    Serial.print(' - ');
    Serial.println(currentNote);
}

void calculate_next() {
    counter++;
    incIndex += inc;

    if (counter == steps) {
        counter = 0;
        incIndex = 0;
        currentNote = start;
    }

    int trueInc = scales[scale][incIndex % scaleLen];
    currentNote += trueInc;
}

void calculate_ms() {
    ms = 60000 / bpm;
    gateMs = ms * gate;
}