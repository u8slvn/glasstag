# GlassTag

GlassTag is an Arduino-based RFID system that automatically identifies drink glasses at parties. Each glass has a permanent RFID tag attached underneath. When placed near the scanner, the system instantly displays the owner's name and avatar on an OLED screen, eliminating mix-ups and making it easy to identify whose drink is whose.

## Wiring Diagram

### MFRC522 RFID Reader
| MFRC522 Pin | Arduino Pin |
|-------------|-------------|
| VCC         | 3.3V        |
| GND         | GND         |
| RST         | Pin 9       |
| IRQ         | Not connected |
| MISO        | Pin 12      |
| MOSI        | Pin 11      |
| SCK         | Pin 13      |
| SDA         | Pin 10      |

### SSD1306 OLED Display (I2C)
| OLED Pin | Arduino Pin |
|----------|-------------|
| VCC      | 5V          |
| GND      | GND         |
| SCL      | A5          |
| SDA      | A4          |

### Buzzer
| Buzzer Pin | Arduino Pin |
|------------|-------------|
| Positive   | Pin 8       |
| Negative   | GND         |

## Software Installation

1. **Install Arduino IDE**

2. **Install Required Libraries:**
   - Adafruit SSD1306
   - Adafruit GFX Library
   - MFRC522

3. **Clone or Download** this project to your Arduino sketchbook folder

4. **Open** `GlassTag.ino` in Arduino IDE

## Project Structure

```
GlassTag/
├── GlassTag.ino              # Main Arduino sketch file
├── AccessControlSystem.h/.cpp # Main system controller
├── ScreenManager.h/.cpp      # OLED display management
├── RFIDReader.h/.cpp         # RFID card reader management
├── AudioManager.h/.cpp       # Audio feedback system
├── Person.h                  # User data structure
├── images.h                  # Bitmap image data
└── README.md                 # This file
```

## Adding New Party Guests

1. **Scan RFID Card:** Upload the code and scan the new guest's card. Check Serial Monitor for the UID.

2. **Create Guest Avatar:** Convert their photo to a 64x64 bitmap array and add it to `images.h`:
   ```cpp
   const unsigned char GUEST_NAME_DATA[] PROGMEM = {
     // Your bitmap data here...
   };
   const Image GUEST_NAME_IMG = {GUEST_NAME_DATA, 64, 64};
   ```

3. **Add Guest to System:** In `GlassTag.ino`, add the new guest to the `people[]` array:
   ```cpp
   Person people[] = {
     {"Alice",    {0x04, 0x53, 0x8A, 0x52}, &ALICE_IMG},
     {"Bob",      {0x04, 0xEA, 0xA3, 0x79}, &BOB_IMG},
     {"NewGuest", {0xXX, 0xXX, 0xXX, 0xXX}, &GUEST_NAME_IMG}, // Add here
   };
   ```

## Configuration

### Display Settings
- **Timeout:** 20 seconds (adjustable in `AccessControlSystem.h`)
- **Resolution:** 128x64 pixels
- **I2C Address:** 0x3C (default for most SSD1306 modules)

### Audio Settings
- **Buzzer Pin:** Pin 3 (adjustable in `AudioManager.h`)
- **Musical Notes:** Customizable melodies for glass tagging events

---

**GlassTag** - Never lose your drink at a party again!
