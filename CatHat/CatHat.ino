#include "src/MusicPlayer.h";

// Settings
int buzzerPin = 2;
int ledPins[] = { A5, A4 };

unsigned int currentLedIndex = 0;
unsigned int pinCount = sizeof(ledPins) / sizeof(int);

void handleNoteChange(boolean isOn) {
  int pin = ledPins[currentLedIndex];
  
  if (isOn) {
    analogWrite(pin, 255);
  } else {
    analogWrite(pin, 0);
    currentLedIndex = (currentLedIndex + 1) % pinCount;
  }
}

MusicPlayer player(buzzerPin, handleNoteChange);

void setup() {
  for (int i = 0; i < pinCount; i++) {
    int pin = ledPins[i];
    pinMode(pin, OUTPUT);
    analogWrite(pin, 0);
  }
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(57600);
  Serial.println("OK.  Here we go!");
}

// Tells the program which song is chosen.
void loop() {
  Serial.println("Gonna start playing");
  char warEagle[] = "W_c! | Hag | Qf Hf Qd | H.c Qr | Qe He Qf | Hgc | Qf Hf Qg | H.a Qr | W_c! | Hag"
                    "Qf Hf Qd | H.c Qr | Qe H-e! Qe | Qfe Hd | Qgr > H^c | cc! | H.c < Q-b! | Hag | Qf Hf Qg | H.a Qr"
                    ">Qdd Hc | Qdd Hc< | Q-b Hb! Qa | Qgr > ^c <! Qr | W_c! | Hag | fg | a > d | Qc < Hb > Qc <"
                    "Hag | W_f | Qfr Hr";
  player.playSong(warEagle, 290);
  noTone(buzzerPin);  
  delay(5000);
}
