#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include "Person.h"

// Screen configuration
#define SCREEN_WIDTH   128
#define SCREEN_HEIGHT  64
#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C

/**
 * @class ScreenManager
 * @brief Manages OLED display for automatic drink glass identification
 * 
 * This class handles all display operations for the GlassTag system,
 * including showing person names, avatars, and default screens when
 * glasses with permanent RFID tags are placed near the scanner.
 */
class ScreenManager {
private:
  Adafruit_SSD1306 display; ///< OLED display instance
  
public:
  /**
   * @brief Constructor - initializes display with default parameters
   */
  ScreenManager();
  
  /**
   * @brief Initialize the OLED display
   * @return true if initialization successful, false otherwise
   */
  bool initialize();
  
  /**
   * @brief Display the lock icon (waiting state)
   */
  void displayLock();
  
  /**
   * @brief Display person's information (name and image)
   * @param person Pointer to Person struct containing display data
   */
  void displayPerson(Person* person);
  
  /**
   * @brief Clear the display
   */
  void clear();
};

#endif // SCREEN_MANAGER_H
