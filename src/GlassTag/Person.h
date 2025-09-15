#ifndef PERSON_H
#define PERSON_H

#include "images.h"

/**
 * @struct Person
 * @brief Represents a person in the automatic glass identification system
 * 
 * Contains all information needed to identify a person and display
 * their information when their glass (with permanent RFID tag) is placed near the scanner.
 */
struct Person {
  const char* displayName;  ///< Name to display on screen
  byte rfidUuid[4];        ///< 4-byte RFID card UUID
  const Image* image;      ///< Pointer to person's image data
};

#endif // PERSON_H
