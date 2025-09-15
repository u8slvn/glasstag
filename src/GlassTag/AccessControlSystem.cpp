#include "AccessControlSystem.h"
#include "images.h"
#include <Arduino.h>

/**
 * @brief Constructor - initializes system in waiting state
 */
AccessControlSystem::AccessControlSystem() : timer(0), currentState(WAITING) {
}

/**
 * @brief Initialize all system components
 * @return true if all components initialized successfully, false otherwise
 */
bool AccessControlSystem::initialize() {
  Serial.begin(9600);
  
  audio.initialize();
  
  if (!screen.initialize()) {
    return false;
  }
  
  rfidReader.initialize();
  reset();
  audio.playIntro();
  return true;
}

/**
 * @brief Reset system to waiting state with lock screen
 */
void AccessControlSystem::reset() {
  currentState = WAITING;
  timer = 0;
  screen.displayLock();
}

/**
 * @brief Update the display timeout timer
 */
void AccessControlSystem::updateTimer() {
  if (currentState == DISPLAYING) {
    timer += TICK_MS;
  }
  
  if (timer >= MAX_TIMER_VALUE) {
    reset();
  }
}

/**
 * @brief Find a person in the database by their RFID code
 */
Person* AccessControlSystem::findPersonByRFID(byte* rfidCode) {
  for (int i = 0; i < PEOPLE_COUNT; i++) {
    if (compareRFIDCodes(rfidCode, people[i].rfidUuid)) {
      return &people[i];
    }
  }
  return nullptr;
}

/**
 * @brief Compare two RFID codes for equality
 */
bool AccessControlSystem::compareRFIDCodes(byte* code1, byte* code2) {
  for (int i = 0; i < 4; i++) {
    if (code1[i] != code2[i]) {
      return false;
    }
  }
  return true;
}

/**
 * @brief Handle successful person recognition
 */
void AccessControlSystem::handlePersonFound(Person* person) {
  currentState = DISPLAYING;
  screen.displayPerson(person);
  audio.playSuccess();
}

/**
 * @brief Handle unknown/unauthorized card detection
 */
void AccessControlSystem::handleUnknownCard() {
  audio.playFailure();
}

/**
 * @brief Process a detected RFID card
 */
void AccessControlSystem::processRFIDCard() {
  byte cardUID[4];
  rfidReader.readCardUID(cardUID);
  rfidReader.printCardUID(cardUID);
  
  Person* foundPerson = findPersonByRFID(cardUID);
  
  if (foundPerson != nullptr) {
    handlePersonFound(foundPerson);
  } else {
    handleUnknownCard();
  }
  
  rfidReader.finalize();
}

/**
 * @brief Main system update loop
 */
void AccessControlSystem::update() {
  updateTimer();
  
  if (rfidReader.isCardPresent()) {
    processRFIDCard();
  }
}
