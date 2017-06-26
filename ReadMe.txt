========================================
---------------LASER HARP---------------
========================================

This laser harp is set to work with 6 lasers and light sensors.

It can be used as MIDI controller but we need to set a kind of bridge between USB and MIDI :
1. (first time only) Install "loopMIDI" from "utils/loopMIDISetup.exe"
2. Open a virtual MIDI port by launching "loopMIDI"
3. Plug the Arduino in and upload the code inside
4. Launch "Serial_Midi_Converter_V2D.exe". Be sure to use a 64-bits computer.
5. Use this configuration for "Serial_Midi_Converter_V2D" :
	- Serial Port : COM3 or 4
	- Serial Baud Rate : 115200 bps
	- MIDI Input port : loopMIDI Port
	- MIDI Output port : loopMIDI Port
6. Open your favorite music software and use your harp. The corresponding midi channel is "loopMIDI Port"

========================================
Wires :
+  : orange ----
-  : copper
A0 : brown ----
A1 : brown - - - -
A2 : green ----
A3 : green - - - -
A4 : blue ----
A5 : blue - - - -

========================================
Nice laser harp sound : 
Using "TAL-NoiseMaker", preset "229 - LD We Felt Digital TUC"