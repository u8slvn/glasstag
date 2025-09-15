#include "RFIDReader.h"

/**
 * @brief Constructor - initializes RFID reader with predefined pins
 */
RFIDReader::RFIDReader() : rfid(SS_PIN, RST_PIN) {
}

/**
 * @brief Initialize the RFID reader
 */
void RFIDReader::initialize() {
  SPI.begin();
  rfid.PCD_Init();
}

/**
 * @brief Check if a new RFID card is present and readable
 * @return true if card is present and can be read, false otherwise
 */
bool RFIDReader::isCardPresent() {
  return rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial();
}

/**
 * @brief Read the UID from the detected RFID card
 * @param uid Pointer to 4-byte array to store the card UID
 */
void RFIDReader::readCardUID(byte* uid) {
  for (byte i = 0; i < 4; i++) {
    uid[i] = rfid.uid.uidByte[i];
  }
}

/**
 * @brief Finalize RFID communication and prepare for next read
 */
void RFIDReader::finalize() {
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

/**
 * @brief Print card UID to Serial for debugging
 * @param uid Pointer to 4-byte card UID array
 */
void RFIDReader::printCardUID(byte* uid) {
  Serial.println("RFID tag detected");
  Serial.println("UUID:");
  for (byte i = 0; i < 4; i++) {
    Serial.print(uid[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}
