#ifndef ACCESS_CONTROL_SYSTEM_H
#define ACCESS_CONTROL_SYSTEM_H

#include "ScreenManager.h"
#include "RFIDReader.h"
#include "AudioManager.h"
#include "Person.h"

// External data from main file
extern Person people[];
extern int PEOPLE_COUNT;

// Timing constants
#define TICK_MS 100
#define DISPLAY_TIMEOUT_SECONDS 20
#define MAX_TIMER_VALUE (DISPLAY_TIMEOUT_SECONDS * 10 * TICK_MS)

/**
 * @class AccessControlSystem
 * @brief Main system controller for automatic drink glass identification
 * 
 * This is the primary class that manages the entire GlassTag drink identification system.
 * It coordinates between the screen, RFID reader, and audio manager to automatically identify 
 * drink glasses with permanent RFID tags when placed near the scanner.
 */
class AccessControlSystem {
private:
  ScreenManager screen;     ///< Display management
  RFIDReader rfidReader;    ///< RFID card reading
  AudioManager audio;       ///< Audio feedback
  int timer;                ///< Display timeout timer
  enum State { WAITING, DISPLAYING } currentState; ///< Current system state
  
public:
  /**
   * @brief Constructor - initializes system in waiting state
   */
  AccessControlSystem();
  
  /**
   * @brief Initialize all system components
   * @return true if all components initialized successfully, false otherwise
   */
  bool initialize();
  
  /**
   * @brief Reset system to waiting state with lock screen
   */
  void reset();
  
  /**
   * @brief Update the display timeout timer
   * 
   * If displaying person info, increment timer and reset to default screen
   * when timeout is reached.
   */
  void updateTimer();
  
  /**
   * @brief Find a person in the database by their RFID tag
   * @param rfidCode Pointer to 4-byte RFID tag code to search for
   * @return Pointer to Person if found, nullptr if not found
   */
  Person* findPersonByRFID(byte* rfidCode);
  
  /**
   * @brief Compare two RFID tag codes for equality
   * @param code1 First 4-byte RFID tag code
   * @param code2 Second 4-byte RFID tag code
   * @return true if codes match, false otherwise
   */
  bool compareRFIDCodes(byte* code1, byte* code2);
  
  /**
   * @brief Handle successful person recognition
   * @param person Pointer to recognized Person
   */
  void handlePersonFound(Person* person);
  
  /**
   * @brief Handle unknown/unregistered tag detection
   */
  void handleUnknownCard();
  
  /**
   * @brief Process a detected RFID tag
   * 
   * Reads the tag UID from glasses placed near the scanner, searches for matching person, 
   * and displays their name and avatar on the identification system.
   */
  void processRFIDCard();
  
  /**
   * @brief Main system update loop
   * 
   * Call this method continuously to check for RFID tags on glasses and
   * manage display timeout for the automatic glass identification.
   */
  void update();
};

#endif // ACCESS_CONTROL_SYSTEM_H
