/*
  MIT License

  Copyright (c) 2022 TinyElectronicBlog

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include "../TEB_External_dependencies.h"
#include "../TEB_Some_global_values.h"
#include "TEB_Debug.h"
#include "TEB_EEPROM.h"

#ifdef TEB_DB_DEBUG
const char TEB_EEPROM_debug1[] PROGMEM = "Failed to initialize EEPROM";
#endif

int8_t TEB_EEPROM::write (const uint8_t* value, uintDataType valueLength) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_EEPROM::write (const uint8_t* value, uintDataType valueLength)"));
  if (value == NULL) TEB_Debug::fatalError(134, F("value cannot be NULL."));
  if (valueLength == 0 || valueLength > 512) TEB_Debug::fatalError(135, F("valueLength must be > 0 and <= 512."));
#endif
  if (!EEPROM.begin(512)) {
#ifdef TEB_DB_DEBUG
    TEB_Debug::fatalError(136, TEB_EEPROM_debug1);
#endif
    return -1;
  }
  uintDataType i = 0;
  while (i < valueLength) {
    if (EEPROM.read(i) != *value) EEPROM.write(i, *value);
    value++;
    i++;
  }
  if (EEPROM.commit()) {
#ifdef TEB_DB_DEBUG
    TEB_Debug::print(F("\nWritten "));
    TEB_Debug::print(valueLength);
    TEB_Debug::print(F(" bytes in the EEPROM.\n"));
#endif
    EEPROM.end();
    return 1;
  }
  else {
#ifdef TEB_DB_DEBUG
    TEB_Debug::fatalError(137, F("Error while writing EEPROM."));
#endif
    EEPROM.end();
    return -2;
  }
}

int8_t TEB_EEPROM::read (uint8_t* buffer, uintDataType bufferSize) {
#ifdef TEB_DB_DBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_EEPROM::read (uint8_t* buffer, uintDataType bufferSize)"));
  if (buffer == NULL) TEB_Debug::fatalError(138, F("buffer cannot be NULL."));
  if (bufferSize == 0 || bufferSize > 512) TEB_Debug::fatalError(139, F("bufferSize must be > 0 and <= 512."));
#endif
  if (!EEPROM.begin(512)) {
#ifdef TEB_DB_DEBUG
    TEB_Debug::fatalError(140, TEB_EEPROM_debug1);
#endif
    return -1;
  }
  uintDataType i = 0;
  while (i < bufferSize) {
    *buffer = EEPROM.read(i);
    buffer++;
    i++;
  }
#ifdef TEB_DB_DEBUG
  TEB_Debug::print(F("\nRead "));
  TEB_Debug::print(bufferSize);
  TEB_Debug::print(F(" bytes from the EEPROM.\n"));
#endif
  EEPROM.end();
  return 1;
}

#ifdef TEB_DB_DEBUG
void TEB_EEPROM::test () {
  TEB_Debug tebdb = TEB_Debug(F("TEB_EEPROM::test ()"));
  TEB_Debug::print(TEB_Library_global_string_for_debugging1);
  TEB_Debug::print(F("TEB_EEPROM"));
  TEB_Debug::print(TEB_Library_global_string_for_debugging2);
  char str[7];
  TEB_EEPROM::write((uint8_t*)"Hello!", 7);
  TEB_EEPROM::read((uint8_t*)str, 7);
  TEB_Debug::print(F("\n\""));
  TEB_Debug::print(str);
  TEB_Debug::print(F("\" is stored in the EEPROM.\n"));
  TEB_Debug::print(TEB_Library_global_string_for_debugging3);
}
#endif