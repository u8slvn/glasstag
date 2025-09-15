#include "AudioManager.h"

// ========== STATIC MELODY DEFINITIONS ==========

// Startup melody
int AudioManager::introMelody[] = {
  NOTE_C5, 16, NOTE_C6, 16, NOTE_C7, 8,
};
int AudioManager::introNotes = sizeof(AudioManager::introMelody) / sizeof(AudioManager::introMelody[0]) / 2;

// Success melody (when person is recognized)
int AudioManager::successMelody[] = {
  NOTE_G6, 14, NOTE_FS6, 14, NOTE_DS6, 14, NOTE_A5, 14,
  NOTE_GS5, 14, NOTE_E6, 14, NOTE_GS6, 14, NOTE_C7, 8,
};
int AudioManager::successNotes = sizeof(AudioManager::successMelody) / sizeof(AudioManager::successMelody[0]) / 2;

// Failure melody (when card is not recognized)
int AudioManager::failMelody[] = {
  NOTE_C6, 16, NOTE_C5, 16, NOTE_C4, 8,
};
int AudioManager::failNotes = sizeof(AudioManager::failMelody) / sizeof(AudioManager::failMelody[0]) / 2;

// ========== PUBLIC METHODS IMPLEMENTATION ==========

/**
 * @brief Initialize the buzzer pin
 */
void AudioManager::initialize() {
  pinMode(BUZZERPIN, OUTPUT);
}

/**
 * @brief Play the system startup melody
 */
void AudioManager::playIntro() {
  playMelody(introMelody, introNotes);
}

/**
 * @brief Play success melody when authorized person is detected
 */
void AudioManager::playSuccess() {
  playMelody(successMelody, successNotes);
}

/**
 * @brief Play failure melody when unauthorized card is detected
 */
void AudioManager::playFailure() {
  playMelody(failMelody, failNotes);
}

// ========== PRIVATE METHODS IMPLEMENTATION ==========

/**
 * @brief Play a melody on the buzzer
 * @param melody Array containing note frequencies and durations
 * @param notes Number of notes in the melody
 */
void AudioManager::playMelody(int melody[], int notes) {
  int tempo = 144; 
  int divider = 0, noteDuration = 0;
  int wholenote = (60000 * 4) / tempo;
  
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    divider = melody[thisNote + 1];
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // Dotted notes
    }
    tone(BUZZERPIN, melody[thisNote], noteDuration * 0.9);
    delay(noteDuration);
    noTone(BUZZERPIN);
  }
}
