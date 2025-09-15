#ifndef RFID_READER_H
#define RFID_READER_H

#include <MFRC522.h>
#include <SPI.h>

// Pin constants for this module
#define SS_PIN    10
#define RST_PIN   9

/**
 * @class RFIDReader
 * @brief Manages RFID tag reading for automatic glass identification
 * 
 * This class encapsulates all RFID-related functionality for the GlassTag system,
 * detecting permanent RFID tags attached to glasses when placed near the scanner.
 */
class RFIDReader {
private:
  MFRC522 rfid; ///< MFRC522 RFID reader instance
  
public:
  /**
   * @brief Constructor - initializes RFID reader with predefined pins
   */
  RFIDReader();
  
  /**
   * @brief Initialize the RFID reader
   */
  void initialize();
  
  /**
   * @brief Check if a new RFID card is present and readable
   * @return true if card is present and can be read, false otherwise
   */
  bool isCardPresent();
  
  /**
   * @brief Read the UID from the detected RFID card
   * @param uid Pointer to 4-byte array to store the card UID
   */
  void readCardUID(byte* uid);
  
  /**
   * @brief Finalize RFID communication and prepare for next read
   */
  void finalize();
  
  /**
   * @brief Print card UID to Serial for debugging
   * @param uid Pointer to 4-byte card UID array
   */
  void printCardUID(byte* uid);
};

#endif // RFID_READER_H
