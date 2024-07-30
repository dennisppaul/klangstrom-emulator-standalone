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
    audioinfo.device_type = AUDIO_DEVICE_KLST_PANDA_AUDIO_CODEC;
    audiocodec.init(&audioinfo);
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
    if (audio_block->device_id == 0) {
        for (int i = 0; i < audio_block->block_size; ++i) {
            float mSample = oscillator.process();
            for (int j = 0; j < audio_block->output_channels; ++j) {
                audio_block->output[j][i] = mSample;
            }
        }
    }
}