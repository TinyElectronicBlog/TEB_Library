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

#include "../strings_and_numbers/TEB_Strings.h"
#include "TEB_Drive_Remote_Control_Interface.h"

const char TEB_Drive_Remote_Control_Interface::str1[] PROGMEM = TEB_Drive_Remote_Control_Interface_TINY_ELECTRONIC_BLOG_FOLDER_NAME;
const char TEB_Drive_Remote_Control_Interface::str2[] PROGMEM = "trashed%20%3D%20false%20and%20mimeType%20%3D%20%27application%2Fvnd.google-apps.folder%27%20and%20name%20%3D%20%27";//"trashed = false and mimeType = 'application/vnd.google-apps.folder' and name = '";
const char TEB_Drive_Remote_Control_Interface::str3[] = "root";
const char TEB_Drive_Remote_Control_Interface::str4[] PROGMEM = "%27%20and%20%27";//"' and '";
const char TEB_Drive_Remote_Control_Interface::str5[] PROGMEM = "%27%20in%20parents";//"' in parents";
const char TEB_Drive_Remote_Control_Interface::str6[] PROGMEM = "text%2Fplain%27%20and%20name%20%3D%20%27";//"text/plain' and name = '";
const char TEB_Drive_Remote_Control_Interface::str7[] PROGMEM = "File%20of%20device%20";//"File of device ";
const char TEB_Drive_Remote_Control_Interface::str8[] PROGMEM = "From%20dev.%20";//"From dev. ";
const char TEB_Drive_Remote_Control_Interface::str9[] PROGMEM = "%20ACK%20";//" ACK ";
const char TEB_Drive_Remote_Control_Interface::str10[] PROGMEM = "files(id)";
const char TEB_Drive_Remote_Control_Interface::str11[] PROGMEM = "contains%20%27";//"contains '";
const char TEB_Drive_Remote_Control_Interface::str12[] PROGMEM = "and%20not%20name%20";//"and not name ";
const char TEB_Drive_Remote_Control_Interface::str13[] PROGMEM = "command%20Cus.%20value%20%27";//"command Cus. value '";
const char TEB_Drive_Remote_Control_Interface::str14[] PROGMEM = "createdTime";
const char TEB_Drive_Remote_Control_Interface::str15[] PROGMEM = "To%20dev.%20";//"To dev. ";
const char TEB_Drive_Remote_Control_Interface::str16[] PROGMEM = "To dev. ";
const char TEB_Drive_Remote_Control_Interface::str17[] PROGMEM = " command Cus. value ";
const char TEB_Drive_Remote_Control_Interface::str18[] PROGMEM = "File of device ";
const char TEB_Drive_Remote_Control_Interface::str19[] PROGMEM = "text/plain";
const char TEB_Drive_Remote_Control_Interface::str20[] PROGMEM = "From dev. ";
const char TEB_Drive_Remote_Control_Interface::str21[] PROGMEM = " ACK ";

int8_t TEB_Drive_Remote_Control_Interface::getWorkspaceFolderID (const char* workspaceFolderName, char* workspaceFolderIDBuffer) {
#ifdef TEB_DB_DEBUG
  TEB_Debug(F("TEB_Drive_Remote_Control_Interface::getWorkspaceFolderID (const char* workspaceFolderName, char* workspaceFolderIDBuffer)"));
#endif
  char fields[strlen_P(str10) + 1];
  TEB_Strings::append_P(fields, str10);
  char q[200];
  //recover the Tiny Electronic Blog folder ID
  TEB_Strings::append_P(TEB_Strings::append(TEB_Strings::append_P(TEB_Strings::append_P(TEB_Strings::append_P(q, str2), str1), str4), str3), str5);
  int8_t r = TEB_Drive::searchFile(q, NULL, fields, 2, NULL, q);
  if (r != 1) return -1;
  if (TEB_Strings::indexOf(q, ",") != 0) return -2; //there can be only one Tiny Electronic Blog folder
  const char* p = TEB_Strings::indexOf(q, "id");
  if (p == 0) return 1;
  p = p + 3;
  while (*p != '"') p++;
  p++;
  const char* p2 = TEB_Strings::indexOf(p, "\"");
  if (p2 == 0) return -3;
  TEB_Strings::append(workspaceFolderIDBuffer, p, p2);
  //now workspaceFolderIDBuffer is the Tiny Electronic Blog folder ID
  //recover the workspace folder ID
  TEB_Strings::append_P(TEB_Strings::append(TEB_Strings::append_P(TEB_Strings::append(TEB_Strings::append_P(q, str2), workspaceFolderName), str4), workspaceFolderIDBuffer), str5);
  r = TEB_Drive::searchFile(q, NULL, fields, 2, NULL, q);
  if (r != 1) return -4;
  if (TEB_Strings::indexOf(q, ",") != 0) return -5; //there can be only one workspace folder
  p = TEB_Strings::indexOf(q, "id");
  if (p == 0) return 2;
  p = p + 3;
  while (*p != '"') p++;
  p++;
  p2 = TEB_Strings::indexOf(p, "\"");
  if (p2 == 0) return -6;
  TEB_Strings::append(workspaceFolderIDBuffer, p, p2);
  return 0;
}

int8_t TEB_Drive_Remote_Control_Interface::newDeviceFile (const char* deviceID, const char* workspaceFolderID, char* deviceFileIDBuffer) {
#ifdef TEB_DB_DEBUG
  TEB_Debug(F("TEB_Drive_Remote_Control_Interface::newDeviceFile (const char* deviceID, const char* workspaceFolderID, char* deviceFileIDBuffer)"));
#endif
  char name[strlen_P(str18) + strlen(deviceID) * 5 / 2 + 1];
  TEB_Strings::percentEncoding(name, deviceID);
  int8_t r = TEB_Drive_Remote_Control_Interface::getDeviceFileID(name, workspaceFolderID, deviceFileIDBuffer);
  switch (r) {
    case 0:
      return 1;
    case 1:
      break;
    default:
      return -1;
  }
  char mimeType[strlen_P(str19) + 1];
  TEB_Strings::append(TEB_Strings::append_P(name, str18), deviceID);
  TEB_Strings::append_P(mimeType, str19);
  r = TEB_Drive::createMetadataOnlyFile(name, workspaceFolderID, mimeType, deviceFileIDBuffer);
  if (r == 1) return 0;
  else return -2;
}

int8_t TEB_Drive_Remote_Control_Interface::getDeviceFileID (const char* deviceID, const char* workspaceFolderID, char* deviceFileIDBuffer) {
#ifdef TEB_DB_DEBUG
  TEB_Debug(F("TEB_Drive_Remote_Control_Interface::getDeviceFileID (const char* deviceID, const char* workspaceFolderID, char* deviceFileIDBuffer)"));
#endif
  char fields[strlen_P(str10) + 1];
  TEB_Strings::append_P(fields, str10);
  char q[200];
  //recover the device file ID
  TEB_Strings::append_P(TEB_Strings::append(TEB_Strings::append_P(TEB_Strings::append(TEB_Strings::append_P(TEB_Strings::append_P(TEB_Strings::append_P(q, str2, 51), str6), str7), deviceID), str4), workspaceFolderID), str5);
  int8_t r = TEB_Drive::searchFile(q, NULL, fields, 2, NULL, q);
  if (r != 1) return -1;
  if (TEB_Strings::indexOf(q, ",") != 0) return -2; //there can be only one device file
  const char* p = TEB_Strings::indexOf(q, "id");
  if (p == 0) return 1;
  p = p + 3;
  while (*p != '"') p++;
  p++;
  const char* p2 = TEB_Strings::indexOf(p, "\"");
  if (p2 == 0) return -4;
  TEB_Strings::append(deviceFileIDBuffer, p, p2);
  return 0;
}

int8_t TEB_Drive_Remote_Control_Interface::getDeviceFileText (const char* deviceFileID, char* textBuffer) {
#ifdef TEB_DB_DEBUG
  TEB_Debug(F("TEB_Drive_Remote_Control_Interface::getDeviceFileText (const char* deviceFileID, char* textBuffer)"));
#endif
  return TEB_Drive::getFileContent(deviceFileID, textBuffer);
}

int8_t TEB_Drive_Remote_Control_Interface::updateDeviceFileText (const char* deviceFileID, const char* text) {
#ifdef TEB_DB_DEBUG
  TEB_Debug(F("TEB_Drive_Remote_Control_Interface::updateDeviceFileText (const char* deviceFileID, const char* text)"));
#endif
  char mimeType[strlen(str19) + 1];
  TEB_Strings::append_P(mimeType, str19);
  return TEB_Drive::updateFileContent(deviceFileID, text, mimeType);
}

int8_t TEB_Drive_Remote_Control_Interface::deleteDeviceFile (const char* deviceFileID) {
#ifdef TEB_DB_DEBUG
  TEB_Debug(F("TEB_Drive_Remote_Control_Interface::deleteDeviceFile (const char* deviceFileID)"));
#endif
  return TEB_Drive::deleteFile(deviceFileID);
}

int8_t TEB_Drive_Remote_Control_Interface::isThereACK (const char* deviceID, const char* workspaceFolderID) {
#ifdef TEB_DB_DEBUG
  TEB_Debug(F("TEB_Drive_Remote_Control_Interface::isThereACK (const char* deviceID, const char* workspaceFolderID)"));
#endif
  char fields[strlen_P(str10) + 1];
  TEB_Strings::append_P(fields, str10);
  char q[88 + strlen_P(str11) + strlen_P(str8) + strlen(deviceID) + strlen_P(str9) + strlen_P(str4) + strlen(workspaceFolderID) + strlen_P(str5)];
  TEB_Strings::append_P(TEB_Strings::append(TEB_Strings::append_P(TEB_Strings::append_P(TEB_Strings::append(TEB_Strings::append_P(TEB_Strings::append_P(TEB_Strings::append_P(TEB_Strings::append_P(q, str2, 51), str6, 32), str11), str8), deviceID), str9), str4), workspaceFolderID), str5);
  int8_t r = TEB_Drive::searchFile(q, NULL, fields, 1, NULL, q);
  if (r != 1) return -1;
  if (TEB_Strings::indexOf(q, "id") == 0) return 1;
  else return 0;
}

int8_t TEB_Drive_Remote_Control_Interface::getCommand (const char* deviceID, const char* workspaceFolderID, char* commandNameBuffer) {
#ifdef TEB_DB_DEBUG
  TEB_Debug(F("TEB_Drive_Remote_Control_Interface::getCommand (const char* deviceID, const char* workspaceFolderID, char* commandNameBuffer)"));
#endif
  char fields[strlen_P(str10) + 3];
  TEB_Strings::append_P(fields, str10, 7);
  fields[6] = 'n';
  fields[7] = 'a';
  fields[8] = 'm';
  fields[9] = 'e';
  fields[10] = ')';
  fields[11] = '\0';
  char orderBy[strlen_P(str14) + 1];
  TEB_Strings::append_P(orderBy, str14);
  char q[104 + strlen_P(str12) + strlen_P(str13) + 2 * strlen_P(str11) + strlen_P(str15) + strlen(deviceID) * 3 + strlen_P(str4) + strlen(workspaceFolderID) + strlen_P(str5)];
  TEB_Strings::append_P(TEB_Strings::append_P(TEB_Strings::append_P(TEB_Strings::append(TEB_Strings::append_P(TEB_Strings::append(TEB_Strings::append_P(TEB_Strings::append_P(TEB_Strings::append(TEB_Strings::percentEncoding(TEB_Strings::append_P(TEB_Strings::append_P(TEB_Strings::append_P(TEB_Strings::append_P(q, str2, 51), str6, 32), str11), str15), deviceID), "%20"), str13, 11), str4), workspaceFolderID), str5), "%20"), str12), str11), str13);
  int8_t r = TEB_Drive::searchFile(q, orderBy, fields, 1, NULL, q);
  if (r != 1) return -1;
  const char* p = TEB_Strings::indexOf(q, "name");
  if (p == 0) return 1;
  p = p + 5;
  while (*p != '"') p++;
  p = p + strlen_P(str16) + strlen(deviceID) + 10;
  const char* p2 = TEB_Strings::indexOf(p, "\"");
  if (p2 == 0) return -2;
  TEB_Strings::append(commandNameBuffer, p, p2);
  return 0;
}

int8_t TEB_Drive_Remote_Control_Interface::sendCommandACK (const char* deviceID, const char* commandName, const char* workspaceFolderID) {
#ifdef TEB_DB_DEBUG
  TEB_Debug(F("TEB_Drive_Remote_Control_Interface::sendCommandACK (const char* deviceID, const char* commandName, const char* workspaceFolderID)"));
#endif
  char buffer[strlen_P(str20) + strlen(deviceID) + strlen_P(str21) + strlen(commandName) + strlen(workspaceFolderID)];
  char* name = buffer;
  char* mimeType = TEB_Strings::append(TEB_Strings::append_P(TEB_Strings::append(TEB_Strings::append_P(name, str20), deviceID), str21), commandName) + 1;
  TEB_Strings::append_P(mimeType, str19);
  return TEB_Drive::createMetadataOnlyFile(name, workspaceFolderID, mimeType, buffer);
}

int8_t TEB_Drive_Remote_Control_Interface::getCustomCommand (const char* deviceID, const char* workspaceFolderID, char* commandNameBuffer) {
#ifdef TEB_DB_DEBUG
  TEB_Debug(F("TEB_Drive_Remote_Control_Interface::getCustomCommand (const char* deviceID, const char* workspaceFolderID, char* commandNameBuffer)"));
#endif
  char fields[strlen_P(str10) + 3];
  TEB_Strings::append_P(fields, str10, 7);
  fields[6] = 'n';
  fields[7] = 'a';
  fields[8] = 'm';
  fields[9] = 'e';
  fields[10] = ')';
  fields[11] = '\0';
  char orderBy[strlen_P(str14) + 1];
  TEB_Strings::append_P(orderBy, str14);
  char q[93 + strlen_P(str13) + strlen_P(str11) + strlen_P(str15) + strlen(deviceID) * 3 + strlen_P(str4) + strlen(workspaceFolderID) + strlen_P(str5)];
  TEB_Strings::append_P(TEB_Strings::append(TEB_Strings::append_P(TEB_Strings::append_P(TEB_Strings::append(TEB_Strings::percentEncoding(TEB_Strings::append_P(TEB_Strings::append_P(TEB_Strings::append_P(TEB_Strings::append_P(q, str2, 51), str6, 32), str11), str15), deviceID), "%20"), str13, 26), str4), workspaceFolderID), str5);
  int8_t r = TEB_Drive::searchFile(q, orderBy, fields, 1, NULL, q);
  if (r != 1) return -1;
  const char* p = TEB_Strings::indexOf(q, "name");
  if (p == 0) return 1;
  p = p + 5;
  while (*p != '"') p++;
  p = p + strlen_P(str16) + strlen(deviceID) + strlen_P(str17) + 1;
  const char* p2 = TEB_Strings::indexOf(p, "\"");
  if (p2 == 0) return -2;
  TEB_Strings::append(commandNameBuffer, p, p2);
  return 0;
}

int8_t TEB_Drive_Remote_Control_Interface::deleteCustomCommand (const char* deviceID, const char* commandName, const char* workspaceFolderID) {
#ifdef TEB_DB_DEBUG
  TEB_Debug(F("TEB_Drive_Remote_Control_Interface::deleteCustomCommand (const char* deviceID, const char* commandName, const char* workspaceFolderID)"));
#endif
  char fields[strlen_P(str10) + 1];
  TEB_Strings::append_P(fields, str10);
  char orderBy[strlen_P(str14) + 1];
  TEB_Strings::append_P(orderBy, str14);
  char q[85 + strlen_P(str6) + strlen_P(str15) + strlen(deviceID) + strlen(commandName) + strlen_P(str4) + strlen(workspaceFolderID) + strlen_P(str5)];
  int8_t r;
  while (true) {
    TEB_Strings::append_P(TEB_Strings::append(TEB_Strings::append_P(TEB_Strings::append(TEB_Strings::append_P(TEB_Strings::append(TEB_Strings::append(TEB_Strings::append_P(TEB_Strings::append_P(TEB_Strings::append_P(q, str2, 51), str6), str15), deviceID), "%20"), str13, 26), commandName), str4), workspaceFolderID), str5);
    r = TEB_Drive::searchFile(q, orderBy, fields, 1, NULL, q);
    if (r != 1) return -1;
    const char* p = TEB_Strings::indexOf(q, "id");
    if (p == 0) break;
    p = p + 3;
    while (*p != '"') p++;
    p++;
    const char* p2 = TEB_Strings::indexOf(p, "\"");
    if (p2 == 0) return -2;
    TEB_Strings::append(q, p, p2);
    //q now contains the id of the file to be deleted
    if (TEB_Drive::deleteFile(q) != 1) return -3;
  }
  return 1;
}

#ifdef TEB_DB_DEBUG
void TEB_Drive_Remote_Control_Interface::test (const char* ssid, const char* password, uint32_t timeOut) {
  TEB_Debug tebdb = TEB_Debug(F("TEB_Drive_Remote_Control_Interface::test (const char* ssid, const char* password, uint32_t timeOut)"));
  TEB_Debug::print(TEB_Library_global_string_for_debugging1);
  TEB_Debug::print(F("TEB_Drive_Remote_Control_Interface"));
  TEB_Debug::print(TEB_Library_global_string_for_debugging2);
  TEB_Debug::print(F("\n"));
  char accessTokenBuffer[512];
  if (TEB_WiFi::check() != 1) {
    if (TEB_WiFi::connect(ssid, password, timeOut) != 1) {
      TEB_Debug::print(F("\nCannot connect to the Internet. End of the test.\n"));
      return;
    }
  }
  TEB_Debug::print(F("\nExecute OAuth2 authentication.\n"));
  if (TEB_OAuth2::refreshTokenEEPROM()) {
    char* refreshToken = TEB_OAuth2::getRefreshTokenEEPROM(accessTokenBuffer);
    if (TEB_OAuth2::relogin(accessTokenBuffer, refreshToken, false) != 1 ) {
      if (TEB_OAuth2::login("https://www.googleapis.com/auth/drive.file", accessTokenBuffer, true, TEB_OAuth2::s3PrintText) != 1 ) {
        TEB_Debug::print(F("\nLogin failed. End of the test.\n"));
        return;
      }
    }
  }
  else {
    if (TEB_OAuth2::login("https://www.googleapis.com/auth/drive.file", accessTokenBuffer, true, TEB_OAuth2::s3PrintText) != 1 ) {
      TEB_Debug::print(F("\nLogin failed. End of the test.\n"));
      return;
    }
  }
  TEB_Debug::print(F("\nThe access token is "));
  TEB_Debug::print(accessTokenBuffer);
  TEB_Drive::setAccessToken(accessTokenBuffer);
  char workspaceFolderID[50], deviceFileID[50], textBuffer[75];
  char deviceID[] = "TEST 1";
  char deviceIDurl[] = "TEST%201";
  int8_t r = getWorkspaceFolderID("Workspace%20TEST", workspaceFolderID);
  switch (r) {
    case 0:
      TEB_Debug::print(F("\nworkspaceFolderID is "));
      TEB_Debug::print(workspaceFolderID);
      TEB_Debug::print(F(".\n"));
      break;
    case 1:
      TEB_Debug::print(F("\nThe Tiny Electronic Blog folder does not exist. End of the test.\n"));
      return;
    case 2:
      TEB_Debug::print(F("\nThe workspace folder does not exist. End of the test.\n"));
      return;
    default:
      TEB_Debug::print(F("\ngetWorkspaceFolderID failed. End of the test.\n"));
      return;
  }
  r = newDeviceFile(deviceID, workspaceFolderID, deviceFileID);
  switch (r) {
    case 0:
      TEB_Debug::print(F("\nGenerates a new device file with ID "));
      TEB_Debug::print(deviceFileID);
      TEB_Debug::print(F(".\n"));
      break;
    case 1:
      TEB_Debug::print(F("\nThe device file already exists and has ID "));
      TEB_Debug::print(deviceFileID);
      TEB_Debug::print(F(".\n"));
      break;
    default:
      TEB_Debug::print(F("\nnewDeviceFile failed. End of the test.\n"));
      return;
  }
  r = getDeviceFileID(deviceIDurl, workspaceFolderID, deviceFileID);
  switch (r) {
    case 0:
      TEB_Debug::print(F("\nThe device file ID is "));
      TEB_Debug::print(deviceFileID);
      TEB_Debug::print(F(".\n"));
      break;
    case 1:
      TEB_Debug::print(F("\nThe device file does not exist.\n"));
      break;
    default:
      TEB_Debug::print(F("\ngetDeviceFileID failed. End of the test.\n"));
      return;
  }
  if (updateDeviceFileText(deviceFileID, "buttons: TEST, customizable value;\nvalues: TEST is X;\nHello!") != 1) {
    TEB_Debug::print(F("\nupdateDeviceFileText failed. End of the test.\n"));
    return;
  }
  TEB_Debug::print(F("\nDevice file text updated.\n"));
  if (getDeviceFileText(deviceFileID, textBuffer) != 1) {
    TEB_Debug::print(F("\ngetDeviceFileText failed. End of the test.\n"));
    return;
  }
  TEB_Debug::print(F("\nDevice file text is:\n"));
  TEB_Debug::print(textBuffer);
  TEB_Debug::print(F("\n"));
  if (deleteDeviceFile(deviceFileID) != 1) {
    TEB_Debug::print(F("\ndeleteDeviceFile failed. End of the test.\n"));
    return;
  }
  TEB_Debug::print(F("\nDevice file deleted.\n"));
  r = isThereACK(deviceIDurl, workspaceFolderID);
  switch (r) {
    case 0:
      TEB_Debug::print(F("\nAt least one ACK detected.\n"));
      break;
    case 1:
      TEB_Debug::print(F("\nNo ACK detected.\n"));
      break;
    default:
      TEB_Debug::print(F("\nisThereACK failed. End of the test.\n"));
      return;
  }
  r = getCommand(deviceID, workspaceFolderID, textBuffer);
  switch (r) {
    case 0:
      TEB_Debug::print(F("\nRecovered the command with name '"));
      TEB_Debug::print(textBuffer);
      TEB_Debug::print(F("'.\n"));
      if (sendCommandACK(deviceID, textBuffer, workspaceFolderID) != 1) {
        TEB_Debug::print(F("\nsendCommandACK failed. End of the test.\n"));
        return;
      }
      TEB_Debug::print(F("\nACK sent.\n'"));
      break;
    case 1:
      TEB_Debug::print(F("\nNo command detected.\n"));
      break;
    default:
      TEB_Debug::print(F("\ngetCommand failed. End of the test.\n"));
      return;
  }
  r = getCustomCommand(deviceID, workspaceFolderID, deviceFileID);
  switch (r) {
    case 0:
      TEB_Debug::print(F("\nRecovered the custom command with name '"));
      TEB_Debug::print(deviceFileID);
      TEB_Debug::print(F("'.\n"));
      TEB_Strings::percentEncoding(textBuffer, deviceFileID);
      if (deleteCustomCommand(deviceIDurl, textBuffer, workspaceFolderID) != 1) {
        TEB_Debug::print(F("\ndeleteCustomCommand failed. End of the test.\n"));
        return;
      }
      TEB_Debug::print(F("\nCustom command deleted.\n"));
      break;
    case 1:
      TEB_Debug::print(F("\nNo custom command detected.\n"));
      break;
    default:
      TEB_Debug::print(F("\ngetCustomCommand failed. End of the test.\n"));
      return;
  }
  TEB_Debug::print(TEB_Library_global_string_for_debugging3);
  return;
}
#endif