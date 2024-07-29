//#define KLANG_SAMPLES_PER_AUDIO_BLOCK 2048
//#define KLANG_SAMPLE_RATE             48000

#include "Arduino.h"
#include "Klangstrom.h"
#include "KlangstromAudioCodec.h"
#include "KlangstromSerialDebug.h"
#include "KlangstromLEDs.h"
#include "Wavetable.h"

Klangstrom  klangstrom;
SerialDebug console;
AudioInfo   audioinfo;
AudioCodec  audiocodec;
LEDs        leds;
uint8_t     fLEDIntensity = 0;

float                  wavetable[512];
klangwellen::Wavetable oscillator{wavetable, 512, audioinfo.sample_rate};

void setup() {
    /* init section */
    klangstrom.init();
    console.init();
    console.info();
    console.timestamp();
    console.println("starting init");
    audiocodec.init(&audioinfo);
    //    audiocodec.init(48000, 2, 1, 128, 16);
    //    audiocodec.init(sample_rate, output_channels, input_channels, block_size, bit_depth);
    leds.init(); // TODO interferes with audiocodec

    console.timestamp();
    console.println("finished init");

    /* setup section */
    console.timestamp();
    console.println("starting setup");
    klangstrom.setup();

    klangwellen::Wavetable::fill(wavetable, 512, klangwellen::KlangWellen::WAVEFORM_SINE);

    console.timestamp();
    console.println("finished setup");
    console.println("---------------------------------------------------------");

    audiocodec.start();
}

void loop() {
    fLEDIntensity += 10;
    leds.set(0, (float) fLEDIntensity / 255.0f);
    leds.toggle(1);
    // console.println("LED 0 : %f", leds.get(0));
    // console.println("LED 1 : %f", leds.get(1));
    oscillator.set_frequency((float) random(1, 4) * 55);

    klangstrom.loop();
    delay(1000);
}

void audioblock(AudioBlock* audio_block) {
    for (int i = 0; i < audio_block->block_size; ++i) {
        audio_block->output[0][i] = oscillator.process();
        audio_block->output[1][i] = audio_block->output[0][i];
    }
}