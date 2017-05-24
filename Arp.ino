void setup() {
    controls_setup();
    screen_setup();
    midi_setup();
}

void loop() {
    controls_loop();
    screen_loop();
    midi_loop();
}

/*
    base
    steps
    step size
    gate
    speed
    scale
    arp mode (up/down/up-down/up-down bounce/random)
    ??

    TODO:

    - MIDI controls
    -

*/
