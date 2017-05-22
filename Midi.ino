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

String notes[] = {
    "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"
};

int scales[1][7] = {
    { 0, 2, 3, 5, 7, 8, 10 } // aeolian
};

int scale = 0;
int scaleLen = sizeof(scales[scale]) / sizeof(int);

int currentNote = 60;
int start = 60;
int counter = 0;
int incIndex = 0;
int inc = 1;
int steps = 4;

void midi_setup() {

}

void midi_loop() {
    send_midi();
    calculate_next();

    delay(200);
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
