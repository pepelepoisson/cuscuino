#include <Arduino.h>
// Information about hardware connections, functions and definitions
#include "Definitions.h"

// Program tunables to be edited by user
long waiting_time=600000;  // Minimum sitting time to win game, in milliseconds 
long call_time=5000;  // Maximum duration of waiting time before recall alarm, in milliseconds
long game_over_time=30000; // Maximum duration of recall alarm before game over, in milliseconds 
long trigger_time=3000;  // Count starts if button is pressed at least for this duration

// Initialisation of program variables
long start_time=0;
long elapsed_time=0;
long pause_start_time=0;
long time_correction=0;
int game_over=0;

// Required for FrenchCanCan music from
// Rob Faludi
// http://www.faludi.com
// Additions by Christopher Stevens
// http://www.christopherstevens.cc
//referenced from http://www.phy.mtu.edu/~suits/notefreqs.html
//starting with F noteFreqArr[1]
int noteFreqArr[] = {
49.4, 52.3, 55.4, 58.7, 62.2, 65.9, 69.9, 74, 78.4, 83.1, 88, 93.2,
98.8, 105, 111, 117, 124, 132, 140, 148, 157, 166, 176, 186,
198, 209, 222, 235, 249, 264, 279, 296, 314, 332, 352, 373,
395, 419, 444, 470, 498, 527, 559, 592, 627, 665, 704, 746,
790, 837, 887, 940, 996, 1050, 1110, 1180, 1250, 1320, 1400, 1490,
1580, 1670, 1770, 1870, 1990, 2100};
long mode = 0;

void setup () {
  HardwareSetup ();
}

void CliLed1 (byte pp) {
  // Function to blink Led1
  static byte cntLed1;
  if (cntLed1++ > pp) {
    cntLed1 = 0;
    Led1Toggle;
  }
}

void CliLed2 (byte pp) {
  // Function to blink Led2
  static byte cntLed2;
  if (cntLed2++ > pp) {
    cntLed2 = 0;
    Led2Toggle;
  }
}

void CliLed3 (byte pp) {
  // Function to blink Led3
  static byte cntLed3;
  if (cntLed3++ > pp) {
    cntLed3 = 0;
    Led3Toggle;
  }
}

void Beep (long loud_duration, long loud_frequency, long silent_duration)  {   
  // Function to beep piezo - Used as recall alarm
  // All durations in milliseconds, frequency in Hz
  long nb_half_periods=loud_duration*2*loud_frequency/1000;
  long loud_half_period=1000000/(2*loud_frequency);  // microseconds
  for (int i; i<nb_half_periods; i++) { 
       HPToggle;
       delayMicroseconds (loud_half_period); // microseconds
     }
     delay (silent_duration);  // milliseconds
}

void Imperial_March(){
    // Function to play imperial march on piezo - Used as a game win signal
    //tone(pin, note, duration)
    tone(bHP,LA3,Q); 
    delay(1+Q); //delay duration should always be 1 ms more than the note in order to separate them.
    tone(bHP,LA3,Q);
    delay(1+Q);
    tone(bHP,LA3,Q);
    delay(1+Q);
    tone(bHP,F3,E+S);
    delay(1+E+S);
    tone(bHP,C4,S);
    delay(1+S);
    
    tone(bHP,LA3,Q);
    delay(1+Q);
    tone(bHP,F3,E+S);
    delay(1+E+S);
    tone(bHP,C4,S);
    delay(1+S);
    tone(bHP,LA3,H);
    delay(1+H);
    
    tone(bHP,E4,Q); 
    delay(1+Q); 
    tone(bHP,E4,Q);
    delay(1+Q);
    tone(bHP,E4,Q);
    delay(1+Q);
    tone(bHP,F4,E+S);
    delay(1+E+S);
    tone(bHP,C4,S);
    delay(1+S);
    
    tone(bHP,Ab3,Q);
    delay(1+Q);
    tone(bHP,F3,E+S);
    delay(1+E+S);
    tone(bHP,C4,S);
    delay(1+S);
    tone(bHP,LA3,H);
    delay(1+H);
    
    tone(bHP,LA4,Q);
    delay(1+Q);
    tone(bHP,LA3,E+S);
    delay(1+E+S);
    tone(bHP,LA3,S);
    delay(1+S);
    tone(bHP,LA4,Q);
    delay(1+Q);
    tone(bHP,Ab4,E+S);
    delay(1+E+S);
    tone(bHP,G4,S);
    delay(1+S);
    
    tone(bHP,Gb4,S);
    delay(1+S);
    tone(bHP,E4,S);
    delay(1+S);
    tone(bHP,F4,E);
    delay(1+E);
    delay(1+E);//PAUSE
    tone(bHP,Bb3,E);
    delay(1+E);
    tone(bHP,Eb4,Q);
    delay(1+Q);
    tone(bHP,D4,E+S);
    delay(1+E+S);
    tone(bHP,Db4,S);
    delay(1+S);
    
    tone(bHP,C4,S);
    delay(1+S);
    tone(bHP,B3,S);
    delay(1+S);
    tone(bHP,C4,E);
    delay(1+E);
    delay(1+E);//PAUSE QUASI FINE RIGA
    tone(bHP,F3,E);
    delay(1+E);
    tone(bHP,Ab3,Q);
    delay(1+Q);
    tone(bHP,F3,E+S);
    delay(1+E+S);
    tone(bHP,LA3,S);
    delay(1+S);
    
    tone(bHP,C4,Q);
    delay(1+Q);
     tone(bHP,LA3,E+S);
    delay(1+E+S);
    tone(bHP,C4,S);
    delay(1+S);
    tone(bHP,E4,H);
    delay(1+H);
    
     tone(bHP,LA4,Q);
    delay(1+Q);
    tone(bHP,LA3,E+S);
    delay(1+E+S);
    tone(bHP,LA3,S);
    delay(1+S);
    tone(bHP,LA4,Q);
    delay(1+Q);
    tone(bHP,Ab4,E+S);
    delay(1+E+S);
    tone(bHP,G4,S);
    delay(1+S);
    
    tone(bHP,Gb4,S);
    delay(1+S);
    tone(bHP,E4,S);
    delay(1+S);
    tone(bHP,F4,E);
    delay(1+E);
    delay(1+E);//PAUSE
    tone(bHP,Bb3,E);
    delay(1+E);
    tone(bHP,Eb4,Q);
    delay(1+Q);
    tone(bHP,D4,E+S);
    delay(1+E+S);
    tone(bHP,Db4,S);
    delay(1+S);
    
    tone(bHP,C4,S);
    delay(1+S);
    tone(bHP,B3,S);
    delay(1+S);
    tone(bHP,C4,E);
    delay(1+E);
    delay(1+E);//PAUSE QUASI FINE RIGA
    tone(bHP,F3,E);
    delay(1+E);
    tone(bHP,Ab3,Q);
    delay(1+Q);
    tone(bHP,F3,E+S);
    delay(1+E+S);
    tone(bHP,C4,S);
    delay(1+S);
    
    tone(bHP,LA3,Q);
    delay(1+Q);
     tone(bHP,F3,E+S);
    delay(1+E+S);
    tone(bHP,C4,S);
    delay(1+S);
    tone(bHP,LA3,H);
    delay(1+H);
    
    delay(2*H);
}

void playNote(long noteInt, long length, long mode, long breath = 25) {
  length = length - breath;
 
  long noteInt2 = noteInt + 12; //1 octave up
  long noteInt3 = noteInt + 24; //2 octaves up
  long noteInt4 = noteInt + 36; //3 octaves up
 
  long playLoop = length / 100; //divide length by 4, for use in play sequence
 
  if(mode == 0) { //mode 0 sequence
    for (long i=0; i < playLoop; i++){
      buzz(bHP, noteFreqArr[noteInt], 20);
      delay(5);
      buzz(bHP, noteFreqArr[noteInt2], 20);
      delay(5);
      buzz(bHP, noteFreqArr[noteInt3], 20);
      delay(5);
      buzz(bHP, noteFreqArr[noteInt4], 20);
      delay(5);
    }
  } else if(mode == 1) { //mode 1 sequence
    for (long i=0; i < playLoop; i++){
      buzz(bHP, noteFreqArr[noteInt3], 20);
      delay(5);
      buzz(bHP, noteFreqArr[noteInt4], 20);
      delay(5);
      buzz(bHP, noteFreqArr[noteInt3], 20);
      delay(5);
      buzz(bHP, noteFreqArr[noteInt4], 20);
      delay(5);
    }
  } else if(mode == 2) { //mode 2 sequence
    for (long i=0; i < playLoop; i++){
      buzz(bHP, noteFreqArr[noteInt3], 20);
      delay(5);
      buzz(bHP, noteFreqArr[noteInt3], 20);
      delay(5);
      buzz(bHP, noteFreqArr[noteInt3], 20);
      delay(5);
      buzz(bHP, noteFreqArr[noteInt2], 20);
      delay(5);
    }
  } else if(mode == 3) { //mode 3 sequence
    for (long i=0; i < playLoop; i++){
      buzz(bHP, noteFreqArr[noteInt4], 40);
      delay(5);
      buzz(bHP, noteFreqArr[noteInt2], 40);
      delay(5);
    }
  }
  if(breath > 0) { //take a short pause or 'breath' if specified
    delay(breath);
  }
}

void FrenchCanCan() {
  //main course
  playNote(12, 500, mode);
 
  playNote(5, 1000, mode);
  playNote(7, 250, mode);
  playNote(10, 250, mode);
  playNote(9, 250, mode);
  playNote(7, 250, mode);
  playNote(12, 500, mode);
  playNote(12, 500, mode);
  playNote(12, 250, mode);
  playNote(14, 250, mode);
  playNote(9, 250, mode);
  playNote(10, 250, mode);
  playNote(7, 500, mode);
  playNote(7, 500, mode);
  playNote(7, 250, mode);
  playNote(10, 250, mode);
  playNote(9, 250, mode);
  playNote(7, 250, mode);
  playNote(5, 250, mode);
  playNote(17, 250, mode);
  playNote(16, 250, mode);
  playNote(14, 250, mode);
  playNote(12, 250, mode);
  playNote(10, 250, mode);
  playNote(9, 250, mode);
  playNote(7, 250, mode);
 
  playNote(5, 1000, mode);
  playNote(7, 250, mode);
  playNote(10, 250, mode);
  playNote(9, 250, mode);
  playNote(7, 250, mode);
  playNote(12, 500, mode);
  playNote(12, 500, mode);
  playNote(12, 250, mode);
  playNote(14, 250, mode);
  playNote(9, 250, mode);
  playNote(10, 250, mode);
  playNote(7, 500, mode);
  playNote(7, 500, mode);
  playNote(7, 250, mode);
  playNote(10, 250, mode);
  playNote(9, 250, mode);
  playNote(7, 250, mode);
  playNote(5, 250, mode);
  playNote(12, 250, mode);
  playNote(7, 250, mode);
  playNote(9, 250, mode);
  playNote(5, 250, mode);
  delay(250);
 
  if(mode == 0) {
    mode = 1;
  } else if(mode == 1) {
    mode = 2;
  } else if(mode == 2) {
    mode = 3;
  } else if(mode == 3) {
    mode = 0;
  }
}

void buzz(int targetPin, long frequency, long length) {
  long delayValue = 1000000/frequency/2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length/ 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
  for (long i=0; i < numCycles; i++){ // for the calculated length of time...
    digitalWrite(targetPin,HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin,LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait againf or the calculated delay value
  }
}

enum {Sleep,Start,Check,Count,Call,Success} condition=Sleep;
void loop () {
  delay (20);
  switch (condition) {
  case Sleep:
    //Initialize variables (required on second run)
    start_time=0;
    elapsed_time=0;
    pause_start_time=0;
    time_correction=0;
    game_over=0;
    Led2Off;
    Led3Off;
    CliLed1(1000/25);
    if (Pous1On) { 
      condition = Start; 
    }
    break;
  case Start:
    start_time=millis();
    //Beep(50,1661,1);
    condition = Count;
    break;
  case Count:
    Led1Off;
    CliLed2(100/25);
    CliLed3(100/25);
    elapsed_time = millis()-start_time-time_correction;
    if (!Pous1On & elapsed_time<trigger_time) { 
      condition = Sleep;
    }
    if (!Pous1On & elapsed_time>=trigger_time) { 
      Led2Off;
      Led3Off;
      condition = Call;
      pause_start_time=millis();
    }
    if (elapsed_time>waiting_time){
      condition=Success;
    }
    break;
  case Call:
    while(!Pous1On){
      if (millis()-pause_start_time>call_time){
        Beep(200,1000,3000);
        if (millis()-pause_start_time>call_time+game_over_time){
          game_over=1;
          for (int i=27;i>=-27;i--){
            Beep(200,int(440.0*pow(2.0,float(i/12.0))),1);
          }
          Beep(3000,int(440.0*pow(2.0,float(-27.0/12.0))),1);
          break;
        }
      }
    }
    if (game_over==1){
      condition=Sleep;
    }
    else {
      condition = Count;
    }
    time_correction=time_correction+millis()-pause_start_time;
    break;
  case Success:
    Led1On;
    Led2On;
    Led3On;
    //Imperial_March();
    FrenchCanCan();
    FrenchCanCan();
    FrenchCanCan();
    FrenchCanCan();
    condition = Sleep;
    break;
  }
}


