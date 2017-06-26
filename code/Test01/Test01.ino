#define THRESHOLD 600
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
int sensorValueA0;
int sensorValueA1;
int sensorValueA2;
int sensorValueA3;
int sensorValueA4;
int sensorValueA5;
boolean on0 = false;
boolean on1 = false;
boolean on2 = false;
boolean on3 = false;
boolean on4 = false;
boolean on5 = false;


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
  sensorValueA0 = analogRead(A0);
  sensorValueA1 = analogRead(A1);
  sensorValueA2 = analogRead(A2);
  sensorValueA3 = analogRead(A3);
  sensorValueA4 = analogRead(A4);
  sensorValueA5 = analogRead(A5);
  Serial.println(sensorValueA0);
  if (sensorValueA0 < THRESHOLD && !on0){
    noteOn(MIDI_CHANNEL, NOTE_C3,0x7F);  
    on0 = true;
  }
  else if(sensorValueA0 >= THRESHOLD && on0){
    noteOff(MIDI_CHANNEL, NOTE_C3);
    on0 = false;
  }
  Serial.println(sensorValueA1);
  if (sensorValueA1 < THRESHOLD && !on1){
    noteOn(MIDI_CHANNEL+1, NOTE_E3,0x7F);  
    on1 = true;
  }
  else if(sensorValueA1 >= THRESHOLD && on1){
    noteOff(MIDI_CHANNEL+1, NOTE_E3);
    on1 = false;
  }
  Serial.println(sensorValueA2);
  if (sensorValueA2 < THRESHOLD && !on2){
    noteOn(MIDI_CHANNEL+2, NOTE_G3,0x7F);  
    on2 = true;
  }
  else if(sensorValueA2 >= THRESHOLD && on2){
    noteOff(MIDI_CHANNEL+2, NOTE_G3);
    on2 = false;
  }
  Serial.println(sensorValueA3);
  if (sensorValueA3 < THRESHOLD && !on3){
    noteOn(MIDI_CHANNEL+3, NOTE_C4,0x7F);  
    on3 = true;
  }
  else if(sensorValueA3 >= THRESHOLD && on3){
    noteOff(MIDI_CHANNEL+3, NOTE_C4);
    on3 = false;
  }
    Serial.println(sensorValueA4);
  if (sensorValueA4 < THRESHOLD && !on4){
    noteOn(MIDI_CHANNEL+4, NOTE_E4,0x7F);  
    on4 = true;
  }
  else if(sensorValueA4 >= THRESHOLD && on4){
    noteOff(MIDI_CHANNEL+4, NOTE_E4);
    on4 = false;
  }
  Serial.println(sensorValueA5);
  if (sensorValueA5 < THRESHOLD && !on5){
    noteOn(MIDI_CHANNEL+5, NOTE_G4,0x7F);  
    on5 = true;
  }
  else if(sensorValueA5 >= THRESHOLD && on5){
    noteOff(MIDI_CHANNEL+5, NOTE_G4);
    on5 = false;
  }
}

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
