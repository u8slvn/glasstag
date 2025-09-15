/**
 * @file GlassTag.ino
 * @brief GlassTag - Smart Drink Glass Identification System
 * @author u8slvn
 * @version 1.0.0
 * 
 * GlassTag is an Arduino-based RFID system that automatically identifies drink glasses at parties. 
 * Each glass has a permanent RFID tag attached underneath. When placed near the scanner, the system 
 * instantly displays the owner's name and avatar on an OLED screen, eliminating mix-ups and making 
 * it easy to identify whose drink is whose.
 * 
 * Hardware requirements:
 * - Arduino (Uno/Nano/ESP32)
 * - MFRC522 RFID reader
 * - SSD1306 OLED display (128x64)
 * - Passive buzzer
 * - RFID tags (attached to glasses)
 */

#include "AccessControlSystem.h"
#include "Person.h"
#include "images.h"

// ========== TIMING CONSTANTS ==========
#define TICK_MS 100

// ========== GLASS OWNERS DATABASE ==========

/**
 * @brief Array of glass owners with their RFID tag credentials and avatars
 * 
 * To add a new glass owner:
 * 1. Add their RFID tag UUID (scan tag attached to glass and check Serial output)
 * 2. Add their display name
 * 3. Create their avatar image in images.h
 * 4. Add entry to this array
 */
Person people[] = {
  {"Alice",    {0x04, 0x53, 0x8A, 0x52}, &ALICE_IMG},
  {"Bob",      {0x04, 0xEA, 0xA3, 0x79}, &BOB_IMG},
  // Add more people here...
};

int PEOPLE_COUNT = sizeof(people) / sizeof(people[0]); ///< Number of glass owners

// ========== GLOBAL SYSTEM INSTANCE ==========
AccessControlSystem accessSystem; ///< Main automatic glass identification controller

// ========== ARDUINO FUNCTIONS ==========

/**
 * @brief Arduino setup function - runs once at startup
 * 
 * Initializes the GlassTag automatic glass identification system and provides feedback
 * about initialization success or failure.
 */
void setup() {
  if (!accessSystem.initialize()) {
    Serial.println("System initialization failed!");
    for(;;); // Stop execution if initialization fails
  }
  Serial.println("GlassTag Automatic Glass Identification System initialized successfully!");
}

/**
 * @brief Arduino main loop function - runs continuously
 * 
 * Updates the automatic glass identification system and manages timing
 * for glass owner recognition and display.
 */
void loop() {
  accessSystem.update();
  delay(TICK_MS);
}
