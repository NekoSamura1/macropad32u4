# macropad32u4
Arduino Leonardo / Pro micro / ATMega 32u4 macro pad

CHECK Scheme.png

Macro description
  1) LBM spam
  2) RBM spam
  3) LBM spam toggle
  4) RBM spam toggle
  5) LBM hold toggle
  6) RBM hold toggle
  7) W hold toggle
  8) Space spam toggle
  9) GI artifact upgrade (depends on your system mouse sensivity settings)
  10) - 
  11) -
  12) -
  13) -
  14) -
  15) Open Powershell
  16) Turn off all macros


There is ability to print some strings from EEPROM (could be used as small cript or password manager with hotkeys), that could be activated be shorting to GND A3 pin.</br>
Strings MUST be writed to EEPROM by another program looking like:
  
  char writedString[] = "suprGigaString";</br>
  uint16_t memAddres = 0;</br>
  EEPROM.update(memAddres++, sizeof(writedString) - 1);</br>
  for (uint8_t i = 0; i < sizeof(writedString) - 1; i++)</br>
    EEPROM.update(memAddres++, writedString0[i]);</br>
  

Used Libs:</br>
  Adafruit_GFX https://github.com/adafruit/Adafruit-GFX-Library</br>
  Arduino_ST7789_Fast https://github.com/cbm80amiga/Arduino_ST7789_Fast </br>
  Keyboard</br>
  Mouse</br>
  EEPROM
  
It's easy to add tabs of 15 macro, but i do not need so much of them
