#ifndef MUSIC_PLAYER_h
#define MUSIC_PLAYER_h

#include <Arduino.h>

enum SharpFlat {
  flat = -1,
  natural = 0,
  sharp = 1
};

enum Articulation {
  staccato = 50,
  unaccented = 95,
  tied = 100
};

typedef void (*NotePlaybackCallback)(boolean);

class MusicPlayer {
  public:
    MusicPlayer(unsigned int buzzerPin, NotePlaybackCallback callback);

    double getDuration(char indicator, unsigned int quarterNote);

    void playSong(const char* song, unsigned int tempo);

    void playRest();
    void playNote(char note);

  private:
    static const char NOTES[];
    static const int STEPS_FROM_A[];

    unsigned int buzzerPin;
    NotePlaybackCallback callback;

    unsigned int currentOctave = 4;
    unsigned int currentDuration = 0;
    SharpFlat isSharpFlat = natural;
    Articulation currentArticulation = unaccented;

    double getFrequency(unsigned int octave, char note, SharpFlat sharpFlat);
};

#endif

