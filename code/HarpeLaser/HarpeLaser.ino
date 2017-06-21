#define THRESHOLD 800
#define MIDI_CHANNEL 1
#define NOTE_C2 0x18 //Decimal : 24
#define NOTE_C#2 0x19
#define NOTE_D2 0x1A
#define NOTE_D#2 0x1B
#define NOTE_E2 0x1C
#define NOTE_F2 0x1D
#define NOTE_F#2 0x1E
#define NOTE_G2 0x1F
#define NOTE_G#2 0x20
#define NOTE_A2 0x21
#define NOTE_A#2 0x22
#define NOTE_B2 0x23
#define NOTE_C3 0x24 //Decimal : 36
#define NOTE_C#2 0x25
#define NOTE_D3 0x26
#define NOTE_D#3 0x27
#define NOTE_E3 0x28
#define NOTE_F3 0x29
#define NOTE_F#3 0x2A
#define NOTE_G3 0x2B
#define NOTE_G#3 0x2C
#define NOTE_A3 0x2D
#define NOTE_A#3 0x2E
#define NOTE_B3 0x2F
#define NOTE_C4 0x30 //Decimal : 48
#define NOTE_C#4 0x31
#define NOTE_D4 0x32
#define NOTE_D#4 0x33
#define NOTE_E4 0x34
#define NOTE_F4 0x35
#define NOTE_F#4 0x36
#define NOTE_G4 0x37
#define NOTE_G#4 0x38
#define NOTE_A4 0x39
#define NOTE_A#4 0x3A
#define NOTE_B4 0x3B
#define NOTE_C5 0x3C //Decimal : 60
#define NOTE_C#5 0x3D
#define NOTE_D5 0x3E
#define NOTE_D#5 0x3F
#define NOTE_E5 0x40
#define NOTE_F5 0x41
#define NOTE_F#5 0x42
#define NOTE_G5 0x43
#define NOTE_G#5 0x44
#define NOTE_A5 0x45
#define NOTE_A#5 0x46
#define NOTE_B5 0x47
#define NOTE_C6 0x48 //Decimal : 72

#define VELOCITY 0x7F

/**
 * Could be modified depending on sensors !
 */
int numberOfSensors = 5;
int sensorValues[5] = {0,0,0,0,0};
boolean on[] = {false, false, false, false, false};
int sensor[] = {A0,A1,A2,A3,A4};
int notes[] = {NOTE_C3, NOTE_E3, NOTE_G3, NOTE_A3, NOTE_B3};


/**==========================================
 * Needed fonctions
 */
void setup() {
  Serial.begin(115200);
}

void loop() {
  //BUTTONVERSION
  /*
  sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  if (sensorValue >= 100 && !on){
    noteOn(MIDI_CHANNEL, NOTE_C3,0x7F);  
    on = true;
  }
  else if(sensorValue < 100 && on){
    noteOff(MIDI_CHANNEL, NOTE_C3);
    on = false;
  }
  */

  //LIGHT SENSOR VERSION
  for(int i=0; i<numberOfSensors; i++){  
    sensorValues[i] = analogRead(sensor[i]);
    Serial.println(sensorValues[i]);
    if (sensorValues[i] < THRESHOLD && !on[i]){
      noteOn(MIDI_CHANNEL + i, notes[i],0x7F);  
      on[i] = true;
    }
    else if(sensorValues[i] >= THRESHOLD && on[i]){
      noteOff(MIDI_CHANNEL + i, notes[i]);
      on[i] = false;
    }
  }
}

/**=============================================
 *   other functions
 */
void noteOn(byte channel, byte pitch, byte velocity)
{
  // 0x90 is the first of 16 note on channels. Subtract one to go from MIDI's 1-16 channels to 0-15
  channel += 0x90 - 1;
  
  // Ensure we're between channels 1 and 16 for a note on message
  if (channel >= 0x90 && channel <= 0x9F)
  {
    #ifdef DEBUG
      //Serial.print("Button pressed: ");
      //Serial.println(pitch);
    #elif defined(TEENSY_PLUS_PLUS) || defined(TEENSY_2) || defined(TEENSY_PLUS_PLUS_2)
      usbMIDI.sendNoteOn(pitch, velocity, channel);
    #else
      Serial.write(channel);
      Serial.write(pitch);
      Serial.write(velocity);
    #endif
  }
}

void noteOff(byte channel, byte pitch)
{
  // 0x80 is the first of 16 note off channels. Subtract one to go from MIDI's 1-16 channels to 0-15
  channel += 0x80 - 1;
  
  // Ensure we're between channels 1 and 16 for a note off message
  if (channel >= 0x80 && channel <= 0x8F)
  {
    #ifdef DEBUG
      Serial.print("Button released: ");
      Serial.println(pitch);
    #elif defined(TEENSY_PLUS_PLUS) || defined(TEENSY_2) || defined(TEENSY_PLUS_PLUS_2)
      usbMIDI.sendNoteOff(pitch, 0x00, channel);
    #else 
      Serial.write(channel);
      Serial.write(pitch);
      Serial.write((byte)0x00);
    #endif
  }
}
