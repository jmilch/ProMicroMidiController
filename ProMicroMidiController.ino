#include <MIDIUSB.h>
#include <Bounce2.h>

#define BUTTON_PIN_0 2
#define BUTTON_PIN_1 3
#define BUTTON_PIN_2 4
#define BUTTON_PIN_3 5

// the MIDI channel number to send messages
const int channel = 1;

Bounce debouncer0 = Bounce(); 
Bounce debouncer1 = Bounce(); 
Bounce debouncer2 = Bounce(); 
Bounce debouncer3 = Bounce(); 

int const numDigPinsCC = 4; // number of digital pins to send CC
int currentDigcc[numDigPinsCC];
int digitalpincc[] = {BUTTON_PIN_0, BUTTON_PIN_1, BUTTON_PIN_2, BUTTON_PIN_3};
int digInputcc[numDigPinsCC];
int value[] = {0, 0, 0, 0};

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}


void setup() {
    for (int i = 0; i < numDigPinsCC; i++) {
    pinMode(digitalpincc[i], INPUT_PULLUP);
   }
  debouncer0.attach(BUTTON_PIN_0);
  debouncer0.interval(5); // interval in ms
  debouncer1.attach(BUTTON_PIN_1);
  debouncer1.interval(5); // interval in ms
  debouncer2.attach(BUTTON_PIN_2);
  debouncer2.interval(5); // interval in ms
  debouncer3.attach(BUTTON_PIN_3);
  debouncer3.interval(5); // interval in ms


}

void loop() {
  // put your main code here, to run repeatedly:
  // Update the Bounce instances :
  debouncer0.update();
  debouncer1.update();
  debouncer2.update();
  debouncer3.update();

  // Get the updated value :
  value[0] = debouncer0.read();
  value[1] = debouncer1.read();
  value[2] = debouncer2.read();
  value[3] = debouncer3.read();
   
   
   // digital pins sending CC

  for (int i = 0; i < numDigPinsCC; i++) {
    if (value[i] == 1 && currentDigcc[i] == 0) {
  //    midi.sendControlChange(i+50, 127, channel); 
controlChange(channel, i, 127);
      currentDigcc[i] = 1;
    }  
    if (value[i] == 0  && currentDigcc[i] == 1) {
//      midi.sendControlChange(i+50, 0, channel);
controlChange(channel, i, 0);
      currentDigcc[i] = 0;
    }  
MidiUSB.flush();
  }
 
}
