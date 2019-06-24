#include <string.h>

#include "MusicPlayer.h"
#include "Helpers.h"

const char MusicPlayer::NOTES[] = {'c', 'd', 'e', 'f', 'g', 'a', 'b'};
const int MusicPlayer::STEPS_FROM_A[] = {-9, -7, -5, -4, -2, 0, 2};

MusicPlayer::MusicPlayer(unsigned int buzzerPin, NotePlaybackCallback callback): 
  buzzerPin(buzzerPin),
  callback(callback)
  { };

double MusicPlayer::getDuration(char indicator, unsigned int quarterNote) {
  switch(indicator) {
    case 'W':
      return quarterNote * 4;

    case 'H':
      return quarterNote * 2;

    case 'Q':
      return quarterNote;

    case 'E':
      return quarterNote / 2;

    case 'S':
      return quarterNote / 4;
  }
}

void MusicPlayer::playSong(const char* song, unsigned int tempo) {
  const unsigned int quarterNoteDuration = 60000 / tempo;
  
  currentOctave = 4;
  isSharpFlat = natural;
  currentArticulation = unaccented;

  for (int i = 0; i < strlen(song); ++i) {
    char note = song[i];

    switch (note) {
      case ' ':
      case '|':
        break;

      case '!':
        currentArticulation = unaccented;
        isSharpFlat = natural;
        break;

      case '_':
        currentArticulation = tied;
        break;
      
      case '^':
        currentArticulation = staccato;
        break;

      case '+':
      case '#':
        isSharpFlat = sharp;
        break;

      case '-':
        isSharpFlat = flat;
        break;

      case '<':
        Serial.println("Lower octave");
        --currentOctave;
        break;

      case '>':
        Serial.println("Raise octave");
        ++currentOctave;
        break;

      case 'W':
      case 'H':
      case 'Q':
      case 'E':
      case 'S':
        currentDuration = getDuration(note, quarterNoteDuration);
        break;

      case '.':
        currentDuration *= 1.5;
        break;

      case 'r':
        playRest();
        break;

      case 'a':
      case 'b':
      case 'c':
      case 'd':
      case 'e':
      case 'f':
      case 'g':
        playNote(note);
        break;
    }
  }
}

void MusicPlayer::playRest() {
  delay(currentDuration);
};

void MusicPlayer::playNote(char note) {
  double frequency = getFrequency(currentOctave, note, isSharpFlat);
  unsigned int toneDuration = currentDuration * (currentArticulation / 100.0);

  Serial.print("note: ");
  Serial.print(note);
  Serial.print(" frequency: ");
  Serial.print(frequency);
  Serial.print(" duration: ");
  Serial.println(currentDuration);

  callback(true);
  tone(buzzerPin, frequency, toneDuration);
  delay(toneDuration);
  callback(false);

  delay(currentDuration - toneDuration);
}

double MusicPlayer::getFrequency(unsigned int octave, char note, SharpFlat sharpFlat) {
  double frequency = 440;

  unsigned int noteIndex;
  for (unsigned int i = 0; i < ARRAY_SIZE(NOTES); ++i) {
    if (NOTES[i] == note) {
      noteIndex = i;
      break;
    }
  }

  int halfSteps = STEPS_FROM_A[noteIndex];
  halfSteps += 12 * (octave - 4);
  halfSteps += sharpFlat;

  frequency *= pow(2, halfSteps / 12.0);
  return frequency;
}
