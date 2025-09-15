#include "ScreenManager.h"
#include "images.h"
#include <Arduino.h>

struct Person;

/**
 * @brief Constructor - initializes display with default parameters
 */
ScreenManager::ScreenManager() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {
}

/**
 * @brief Initialize the OLED display
 * @return true if initialization successful, false otherwise
 */
bool ScreenManager::initialize() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    return false;
  }
  display.setTextColor(WHITE);
  delay(2000);
  return true;
}

/**
 * @brief Display the lock icon (waiting state)
 */
void ScreenManager::displayLock() {
  display.clearDisplay();
  display.drawBitmap(52, 10, LOCK_IMG.data, LOCK_IMG.width, LOCK_IMG.height, WHITE);
  display.display();
}

/**
 * @brief Display person's information (name and image)
 * @param person Pointer to Person struct containing display data
 */
void ScreenManager::displayPerson(Person* person) {
  display.clearDisplay();
  display.setTextSize(2);
  int textPosition = (SCREEN_WIDTH - (strlen(person->displayName) * 11)) / 2;
  display.setCursor(textPosition, 0);
  display.print(person->displayName);
  display.drawBitmap(44, 24, person->image->data, person->image->width, person->image->height, WHITE);
  display.display();
}

/**
 * @brief Clear the display
 */
void ScreenManager::clear() {
  display.clearDisplay();
  display.display();
}
