#include <cvzone.h>

// Define RGB LED pins
const int RED_PIN = 2;    // Red LED cathode
const int GREEN_PIN = 3; // Green LED cathode
const int BLUE_PIN = 4;  // Blue LED cathode (not used)

// Define Buzzer pin
const int buzzer = 8;

// Note frequency definitions
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62

#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123

#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247

#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494

#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988

#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976

#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951

// -----------------------------
// Section 1: Opening Riff
// -----------------------------
int melody1[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0, 0,
  NOTE_G6, 0, 0, 0
};

int durations1[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12
};

// -----------------------------
// Section 2: Middle Part
// -----------------------------
int melody2[] = {
  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0
};

int durations2[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12
};

// -----------------------------
// Section 3: Final Part
// -----------------------------
int melody3[] = {
  NOTE_G6, NOTE_E7, NOTE_G7, NOTE_A7,
  0, NOTE_F7, NOTE_G7, 0,
  NOTE_E7, 0, NOTE_C7, NOTE_D7,
  NOTE_B6, 0, 0, 0
};

int durations3[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12
};

// -----------------------------
// Helper function to play a melody array
// -----------------------------
void playMelody(int melody[], int durations[], int length) {
  for (int i = 0; i < length; i++) {
    int noteDuration = 1000 / durations[i]; // duration in ms
    if (melody[i] == 0) {
      // 0 means rest
      delay(noteDuration);
    } else {
      tone(buzzer, melody[i], noteDuration);
      // Brief pause between notes for clarity
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(buzzer);
    }
  }
}

/*
  Disappointing Trumpet Alarm – Intensified Version
  -------------------------------------------------
  This sketch simulates a more disappointing and “louder” trumpet-like alarm.
  It uses an extended descending glissando and longer staccato hits with
  reduced silent gaps.

  Wiring:
    - Connect the buzzer's VCC to 5V (or the appropriate voltage)
    - Connect the buzzer's GND to Arduino GND
    - Connect the buzzer's Signal pin to digital pin 8
*/

// Function to perform a descending glissando (smooth slide)
void descendingGlissando(int startFreq, int endFreq, int duration, int steps) {
  for (int i = 0; i <= steps; i++) {
    // Linear interpolation between start and end frequency:
    int currentFreq = startFreq + ((endFreq - startFreq) * i) / steps;
    tone(buzzer, currentFreq);
    delay(duration / steps);
  }
  noTone(buzzer);
}

// Function to play a single note (or rest if frequency is 0)
void playNote(int frequency, int duration) {
  if (frequency == 0) {
    delay(duration);
  } else {
    tone(buzzer, frequency, duration);
    delay(duration * 1.1);  // slightly reduced pause for a more continuous sound
    noTone(buzzer);
  }
}

void playDisappointingSound() {
  // Part 1: Descending glissando for a deflating trumpet effect
  // Slide from 1000 Hz down to 300 Hz over 700 ms (using 30 steps)
  descendingGlissando(1000, 300, 700, 30);
  
  // Very short pause between segments
  delay(50);
  
  // Part 2: A longer, forceful staccato note to simulate a muted, disappointing trumpet hit
  playNote(500, 200);
  
  // Reduced pause between cycles for a more aggressive alarm rhythm
  delay(150);
}

void playMarioTheme() {
  int len1 = sizeof(melody1) / sizeof(melody1[0]);

  // Play Section 1 (Opening Riff)
  playMelody(melody1, durations1, len1);
}


// -------------------------------------------------------------------------------------------------------


int played = false;
bool red_on = false;
bool green_on = true;

SerialData serialData(1, 1);
int valsRec[1];

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(buzzer, OUTPUT);

  // Start with the LED set to green
  analogWrite(RED_PIN, 0);     // Red OFF
  analogWrite(GREEN_PIN, 255); // Green ON
  analogWrite(BLUE_PIN, 0);    // Blue OFF
  digitalWrite(13, 0);

  serialData.begin();
}

void loop() {
  if (green_on && (!played)) {
    playMarioTheme();
    played = true;
  } else if (red_on) {
    playDisappointingSound();
    played = false;
  }

  serialData.Get(valsRec);

  if (valsRec[0]) {
    analogWrite(RED_PIN, 255);
    analogWrite(GREEN_PIN, 0);
    red_on = true;
    green_on = false;
  } else {
    analogWrite(GREEN_PIN, 255);
    analogWrite(RED_PIN, 0);
    green_on = true;
    red_on = false;
  }
}