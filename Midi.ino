#define C 0
#define C_SHARP 1
#define D 2
#define D_SHARP 3
#define E 4
#define F 5
#define F_SHARP 6
#define G 7
#define G_SHARP 8
#define A 9
#define A_SHARP 10
#define B 11

int octave = 5;
int baseNote = 0;

int note = 60;

int getNote() {
    note = (octave * 12) + baseNote;

    if (note > 127) {
        note = 127
    }

    return note;
}

void setBaseNote(note) {
    baseNote = note;

    if (baseNote > 11) baseNote = 11;
    if (baseNote < 0) baseNote = 0;

    getNote();
}

void setOctave(inputOctave) {
    octave = inputOctave;

    if (octave > 10) octave = 10;
    if (octave < 0) octave = 0;

    getNote();
}
