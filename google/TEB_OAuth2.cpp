/*
  MIT License

  Copyright (c) 2021 TinyElectronicBlog

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

  This class is based on the guide https://developers.google.com/identity/protocols/oauth2/limited-input-device.
*/

#include "TEB_OAuth2.h"

const char TEB_OAuth2::oauth2_api_key[] PROGMEM = TEB_OAuth2_API_KEY;
const char TEB_OAuth2::oauth2_client_id[] PROGMEM = TEB_OAuth2_CLIENT_ID;
const char TEB_OAuth2::oauth2_client_secret[] PROGMEM = TEB_OAuth2_CLIENT_SECRET;
const uint16_t TEB_OAuth2::oauth2_server_port = 443;
const char TEB_OAuth2::oauth2_root_ca[] PROGMEM = TEB_OAuth2_ROOT_CA;

const char* TEB_OAuth2::temp_p = NULL;
char* TEB_OAuth2::imported_array = NULL;
TEB_Splittable_Array* TEB_OAuth2::splittable_buffer = NULL;

const char TEB_OAuth2::str1[] PROGMEM = "client_id=";
const char TEB_OAuth2::str2[] PROGMEM = "_secret=";
const char TEB_OAuth2::str3[] PROGMEM = "&scope=";
const char TEB_OAuth2::str4[] PROGMEM = "interval";
const char TEB_OAuth2::str5[] PROGMEM = "user_";
const char TEB_OAuth2::str6[] PROGMEM = "verification_url";
const char TEB_OAuth2::str7[] PROGMEM = "code";
const char TEB_OAuth2::str8[] PROGMEM = "device";
const char TEB_OAuth2::str9[] PROGMEM = "urn:ietf:params:oauth:";
const char TEB_OAuth2::str10[] PROGMEM = "/revoke";
const char TEB_OAuth2::str11[] PROGMEM = "type=";
const char TEB_OAuth2::str12[] PROGMEM = "token";
const char TEB_OAuth2::str13[] PROGMEM = "access_";
const char TEB_OAuth2::str14[] PROGMEM = "refresh_";
const char TEB_OAuth2::str15[] PROGMEM = "POST ";
const char TEB_OAuth2::str16[] PROGMEM = " HTTP/1.1\r\nHost: ";
const char TEB_OAuth2::str17[] PROGMEM = "oauth2.googleapis.com";
const char TEB_OAuth2::str18[] PROGMEM = "\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: ";
const char TEB_OAuth2::str19[] PROGMEM = "grant";
const char TEB_OAuth2::str20[] PROGMEM = "From another device open the link ";
const char TEB_OAuth2::str21[] PROGMEM = " and enter the ";
const char TEB_OAuth2::str22[] PROGMEM = "error";
const char TEB_OAuth2::str23[] PROGMEM = "https://";
#ifdef TEB_DB_DEBUG
const char TEB_OAuth2::debug1[] PROGMEM = "TEB_OAuth2::login_ returned -";
const char TEB_OAuth2::debug2[] PROGMEM = "TEB_OAuth2::relogin_ returned -";
const char TEB_OAuth2::debug3[] PROGMEM = "TEB_OAuth2::logout_ returned -";
#endif

void TEB_OAuth2::initialize_http_request (TEB_DevelopmentBoard::TEB_HTTP::request& http_request) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_OAuth2::initialize_http_request (TEB_DevelopmentBoard::TEB_HTTP::request& http_request)"));
#endif
  //Load on the left all the values except requestText.
  splittable_buffer->addSX_P(str23);
  splittable_buffer->addSX_P(str17, strlen_P(str17) + 1);
  http_request.serverAddress = (const char*)splittable_buffer->splitSX();
  splittable_buffer->addSX_P(oauth2_root_ca, strlen_P(oauth2_root_ca) + 1);
  http_request.rootCA = (const char*)splittable_buffer->splitSX();
  http_request.serverPort = oauth2_server_port;
  http_request.connectionTimeout = TEB_OAUTH2_HTTP_REQUEST_CONNECTION_TIMEOUT;
  http_request.responseDelay = 10000;
}

void TEB_OAuth2::generate_step1_request_text () {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_OAuth2::generate_step1_request_text ()"));
#endif
  splittable_buffer->addDXreverse(temp_p, strlen(temp_p));
  splittable_buffer->addDXreverse_P(str3);
  splittable_buffer->addDXreverse_P(oauth2_client_id);
  splittable_buffer->addDXreverse_P(str1);
}

void TEB_OAuth2::generate_step4_request_text () {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_OAuth2::generate_step4_request_text ()"));
#endif
  splittable_buffer->addDXreverse_P(str7);
  splittable_buffer->addDXreverse("_", 1);
  splittable_buffer->addDXreverse_P(str8);
  splittable_buffer->addDXreverse(":", 1);
  splittable_buffer->addDXreverse_P(str11, 4);
  splittable_buffer->addDXreverse("-", 1);
  splittable_buffer->addDXreverse_P(str19);
  splittable_buffer->addDXreverse_P(str9);
  splittable_buffer->addDXreverse_P(str11);
  splittable_buffer->addDXreverse("_", 1);
  splittable_buffer->addDXreverse_P(str19);
  splittable_buffer->addDXreverse("&", 1);
  splittable_buffer->addDXreverse(temp_p, strlen(temp_p));
  splittable_buffer->addDXreverse("=", 1);
  splittable_buffer->addDXreverse_P(str7);
  splittable_buffer->addDXreverse("_", 1);
  splittable_buffer->addDXreverse_P(str8);
  splittable_buffer->addDXreverse("&", 1);
  splittable_buffer->addDXreverse_P(oauth2_client_secret);
  splittable_buffer->addDXreverse_P(str2);
  splittable_buffer->addDXreverse_P(str1, 6);
  splittable_buffer->addDXreverse("&", 1);
  splittable_buffer->addDXreverse_P(oauth2_client_id);
  splittable_buffer->addDXreverse_P(str1);
}

void TEB_OAuth2::generate_step7_request_text () {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_OAuth2::generate_step7_request_text ()"));
  TEB_DevelopmentBoard::TEB_Debug::print(F("The refresh token saved in the EEPROM is "));
  TEB_DevelopmentBoard::TEB_Debug::print(temp_p);
  TEB_DevelopmentBoard::TEB_Debug::print(F("\n"));
#endif
  splittable_buffer->addDXreverse_P(str12);
  splittable_buffer->addDXreverse_P(str14);
  splittable_buffer->addDXreverse_P(str11);
  splittable_buffer->addDXreverse("_", 1);
  splittable_buffer->addDXreverse_P(str19);
  splittable_buffer->addDXreverse("&", 1);
  splittable_buffer->addDXreverse(temp_p, strlen(temp_p));
  splittable_buffer->addDXreverse("=", 1);
  splittable_buffer->addDXreverse_P(str12);
  splittable_buffer->addDXreverse_P(str14);
  splittable_buffer->addDXreverse("&", 1);
  splittable_buffer->addDXreverse_P(oauth2_client_secret);
  splittable_buffer->addDXreverse_P(str2);
  splittable_buffer->addDXreverse_P(str1, 6);
  splittable_buffer->addDXreverse("&", 1);
  splittable_buffer->addDXreverse_P(oauth2_client_id);
  splittable_buffer->addDXreverse_P(str1);
}

void TEB_OAuth2::generate_step8_request_text () {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_OAuth2::generate_step8_request_text ()"));
#endif
  splittable_buffer->addDXreverse(temp_p, strlen(temp_p));
  splittable_buffer->addDXreverse("=", 1);
  splittable_buffer->addDXreverse_P(str12);
}

//Generates the text of the http request, saves it in the right buffer and returns the pointer to it. It also executes resetSX.
const char* TEB_OAuth2::generate_http_request_text (uint8_t step_number) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_OAuth2::generate_http_request_text (uint8_t step_number)"));
#endif
  const char* t = "\r\n";
  size_t free_space = splittable_buffer->freeSpace();
  splittable_buffer->addDXreverse("", 1);
  switch (step_number) {
    case 1:
      generate_step1_request_text();
      break;
    case 4:
      generate_step4_request_text();
      break;
    case 7:
      generate_step7_request_text();
      break;
    case 8:
      generate_step8_request_text();
      break;
  }
  splittable_buffer->addDXreverse(t, 2);
  splittable_buffer->addDXreverse(t, 2);
  TEB_Strings::intChar(free_space - splittable_buffer->freeSpace() - 5, (char*)splittable_buffer->SX());
  splittable_buffer->addDXreverse((const char*)splittable_buffer->SX(), strlen((const char*)splittable_buffer->SX()));
  splittable_buffer->addDXreverse_P(str18);
  splittable_buffer->addDXreverse_P(str17);
  splittable_buffer->addDXreverse_P(str16);
  if (step_number == 7) step_number = 4;
  switch (step_number) {
    case 1:
      splittable_buffer->addDXreverse_P(str7);
      splittable_buffer->addDXreverse("/", 1);
      splittable_buffer->addDXreverse_P(str8);
      splittable_buffer->addDXreverse("/", 1);
      break;
    case 4:
      splittable_buffer->addDXreverse_P(str12);
      splittable_buffer->addDXreverse("/", 1);
      break;
    case 8:
      splittable_buffer->addDXreverse_P(str10);
      break;
  }
  splittable_buffer->addDXreverse_P(str15);
  t = (const char*)splittable_buffer->splitDXreverse();
  splittable_buffer->resetSX();
  splittable_buffer->freeDX(strlen(t) + 1);
  return t;
}

int8_t TEB_OAuth2::step1_2_3_4_5 (TEB_DevelopmentBoard::TEB_HTTP::request& http_request, TEB_DevelopmentBoard::TEB_HTTP::response& http_response, void (*step3_display_user_code) (const char* text)) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_OAuth2::step1_2_3_4_5 (TEB_DevelopmentBoard::TEB_HTTP::request& http_request, TEB_DevelopmentBoard::TEB_HTTP::response& http_response, void (*step3_display_user_code) (const char* text))"));
#endif
  initialize_http_request(http_request);
  http_request.requestText = generate_http_request_text(1);
  int8_t r = TEB_DevelopmentBoard::TEB_HTTP::sendRequest(http_request, http_response, (char*)splittable_buffer->SX(), splittable_buffer->freeSpace(), response_reception_algorithm);
  if (r != 1) {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::error(22, F("TEB_OAuth2::step1_2_3_4_5 returned -1."));
#endif
    return -1;
  }
  //Now in splittable_buffer->SX() there is only the http response saved temporarily.
  http_response_property http_response_property;
  splittable_buffer->addDXreverse_P(str4, strlen_P(str4) + 1);
  http_response_property.property = (char*)splittable_buffer->splitDXreverse();
  r = handle_server_response(http_response, http_response_property);
  splittable_buffer->resetDX();
  if (r != 1) {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::error(23, F("TEB_OAuth2::step1_2_3_4_5 returned -2."));
#endif
    return -2;
  }
  uint8_t interval = TEB_Numbers::charInt(http_response_property.property, http_response_property.property + http_response_property.property_length);
  splittable_buffer->addDXreverse_P(str7, strlen_P(str7) + 1);
  splittable_buffer->addDXreverse("_", 1);
  splittable_buffer->addDXreverse_P(str8);
  http_response_property.property = (char*)splittable_buffer->splitDXreverse();
  r = handle_server_response(http_response, http_response_property);
  splittable_buffer->resetDX();
  if (r != 1) {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::error(24, F("TEB_OAuth2::step1_2_3_4_5 returned -3."));
#endif
    return -3;
  }
  splittable_buffer->addDXreverse("", 1);
  splittable_buffer->addDXreverse(http_response_property.property, http_response_property.property_length);
  char* device_code = (char*)splittable_buffer->splitDXreverse();
  splittable_buffer->addDXreverse_P(str7, strlen_P(str7) + 1);
  splittable_buffer->addDXreverse_P(str5);
  http_response_property.property = (char*)splittable_buffer->splitDXreverse();
  http_request.rootCA = http_response_property.property;//temp
  r = handle_server_response(http_response, http_response_property);
  splittable_buffer->freeDX(strlen(http_request.rootCA) + 1);
  if (r != 1) {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::error(25, F("TEB_OAuth2::step1_2_3_4_5 returned -4."));
#endif
    return -4;
  }
  splittable_buffer->addDXreverse(".", 2);
  splittable_buffer->addDXreverse(http_response_property.property, http_response_property.property_length);
  splittable_buffer->addDXreverse(" ", 1);
  splittable_buffer->addDXreverse_P(str7);
  splittable_buffer->addDXreverse_P(str21);
  splittable_buffer->splitDXreverse();
  splittable_buffer->addDXreverse_P(str6, strlen_P(str6) + 1);
  http_response_property.property = (char*)splittable_buffer->splitDXreverse();
  http_request.rootCA = http_response_property.property;//temp
  r = handle_server_response(http_response, http_response_property);
  splittable_buffer->freeDX(strlen(http_request.rootCA) + 1);
  if (r != 1) {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::error(26, F("TEB_OAuth2::step1_2_3_4_5 returned -5."));
#endif
    return -5;
  }
  splittable_buffer->addDXreverse(http_response_property.property, http_response_property.property_length);
  splittable_buffer->addDXreverse_P(str20);
  char* text = (char*) splittable_buffer->splitDXreverse();
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug::print(text);
  TEB_DevelopmentBoard::TEB_Debug::print(F("\nThe other values read are device_code = "));
  TEB_DevelopmentBoard::TEB_Debug::print(device_code);
  TEB_DevelopmentBoard::TEB_Debug::print(F(" and interval = "));
  TEB_DevelopmentBoard::TEB_Debug::print(interval);
  TEB_DevelopmentBoard::TEB_Debug::print(F(".\n"));
#endif
  temp_p = device_code; //temp variable for device code
  while (true) {
    (*step3_display_user_code)(text);
    //Create a new request for login credentials and it must be redone every time because buffer is recycled to parse response. Currently are saved on right device_code and text.
    initialize_http_request(http_request);
    http_request.requestText = generate_http_request_text(4); //Ends with \0.
    delay(interval * 1000);
    r = TEB_DevelopmentBoard::TEB_HTTP::sendRequest(http_request, http_response, (char*)splittable_buffer->SX(), splittable_buffer->freeSpace(), response_reception_algorithm);
    if (r == 1) {
      //Now I have to analyze the answer.
      http_response_property.property = NULL;
      r = handle_server_response(http_response, http_response_property);
      if (r == 2) {
        //Now I have to see what is the status code of the response.
        if (http_response_property.status_code == 400 || http_response_property.status_code == 401) {//error
#ifdef TEB_DB_DEBUG
          TEB_DevelopmentBoard::TEB_Debug::error(27, F("TEB_OAuth2::step1_2_3_4_5 returned -6."));
#endif
          return -6;
        }
        else if (http_response_property.status_code == 403) {
          splittable_buffer->addDXreverse_P(str22, strlen_P(str2) + 1);
          http_response_property.property = (char*)splittable_buffer->splitDXreverse();
          http_request.rootCA = http_response_property.property;//temp
          if (handle_server_response(http_response, http_response_property) == 1) {
            if (*http_response_property.property == 'a' && *(http_response_property.property + 1) == 'c' &&  *(http_response_property.property + 2) == 'c' && *(http_response_property.property + 3) == 'e' && *(http_response_property.property + 4) == 's' && *(http_response_property.property + 5) == 's' && *(http_response_property.property + 6) == '_' && *(http_response_property.property + 7) == 'd' && *(http_response_property.property + 8) == 'e' && *(http_response_property.property + 9) == 'n' && *(http_response_property.property + 10) == 'i' && *(http_response_property.property + 11) == 'e' && *(http_response_property.property + 12) == 'd') {
              return 2; //Everything ok, but access has been denied.
            }
            if (*http_response_property.property == 's' && *(http_response_property.property + 1) == 'l' &&  *(http_response_property.property + 2) == 'o' && *(http_response_property.property + 3) == 'w' && *(http_response_property.property + 4) == '_' && *(http_response_property.property + 5) == 'd' && *(http_response_property.property + 6) == 'o' && *(http_response_property.property + 7) == 'w' && *(http_response_property.property + 8) == 'n') {
              delay(1000);
              splittable_buffer->freeDX(strlen(http_request.rootCA) + 1);
              continue;
            }
          }
          else {
#ifdef TEB_DB_DEBUG
            TEB_DevelopmentBoard::TEB_Debug::error(28, F("TEB_OAuth2::step1_2_3_4_5 returned -7."));
#endif
            return -7;
          }
        }
        else if (http_response_property.status_code == 428) { //Pending Authorization.
          continue;
        }
        else if (http_response_property.status_code == 200) {
          splittable_buffer->resetDX();
          //The http response is in the buffer on the left.
          return 1;
        }
        else {//Unknown status code.
#ifdef TEB_DB_DEBUG
          TEB_DevelopmentBoard::TEB_Debug::error(29, F("TEB_OAuth2::step1_2_3_4_5 returned -8."));
#endif
          return -8;
        }
      }
      else {
#ifdef TEB_DB_DEBUG
        TEB_DevelopmentBoard::TEB_Debug::error(30, F("TEB_OAuth2::step1_2_3_4_5 returned -9."));
#endif
        return -9;
      }
    }
    else {
#ifdef TEB_DB_DEBUG
      TEB_DevelopmentBoard::TEB_Debug::error(31, F("TEB_OAuth2::step1_2_3_4_5 returned -10."));
#endif
      return -10;
    }
  }
}

int8_t TEB_OAuth2::step6 (TEB_DevelopmentBoard::TEB_HTTP::response& http_response, char* access_token_buffer, char* refresh_token_buffer, bool save_refresh_token) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_OAuth2::step6 (TEB_DevelopmentBoard::TEB_HTTP::response& http_response, char* access_token_buffer, char* refresh_token_buffer, bool save_refresh_token)"));
#endif
  http_response_property http_response_property;
  splittable_buffer->addDXreverse_P(str12, strlen_P(str12) + 1);
  splittable_buffer->addDXreverse_P(str13);
  http_response_property.property = (char*)splittable_buffer->splitDXreverse();
  if (handle_server_response(http_response, http_response_property) == 1) {
    splittable_buffer->resetDX();
    TEB_Strings::append(access_token_buffer, http_response_property.property, http_response_property.property + http_response_property.property_length);
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::print(F("\nThe access token read is "));
    TEB_DevelopmentBoard::TEB_Debug::print(access_token_buffer);
    TEB_DevelopmentBoard::TEB_Debug::print(F(".\n"));
#endif
  }
  else {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::error(32, F("TEB_OAuth2::step6 returned -1."));
#endif
    return -1;
  }
  if (refresh_token_buffer != NULL || save_refresh_token) {
    splittable_buffer->addDXreverse_P(str12, strlen_P(str12) + 1);
    splittable_buffer->addDXreverse_P(str14);
    http_response_property.property = (char*)splittable_buffer->splitDXreverse();
    if (handle_server_response(http_response, http_response_property) == 1) {
      *(http_response_property.property + http_response_property.property_length) = '\0';
      if (refresh_token_buffer != NULL) {
        TEB_Strings::append(refresh_token_buffer, http_response_property.property);
#ifdef TEB_DB_DEBUG
        TEB_DevelopmentBoard::TEB_Debug::print(F("\nThe refresh token read is "));
        TEB_DevelopmentBoard::TEB_Debug::print(refresh_token_buffer);
        TEB_DevelopmentBoard::TEB_Debug::print(F(".\n"));
#endif
      }
      if (save_refresh_token) {
        if (set_refresh_token_eeprom(http_response_property.property) != 1) {
#ifdef TEB_DB_DEBUG
          TEB_DevelopmentBoard::TEB_Debug::error(33, F("TEB_OAuth2::step6 returned -2."));
#endif
          return -2;
        }
#ifdef TEB_DB_DEBUG
        TEB_DevelopmentBoard::TEB_Debug::print(F("\nThe refresh token has been saved in the EEPROM.\n"));
#endif
      }
    }
    else {
#ifdef TEB_DB_DEBUG
      TEB_DevelopmentBoard::TEB_Debug::error(34, F("TEB_OAuth2::step6 returned -3."));
#endif
      return -3;
    }
  }
  return 1;
}

int8_t TEB_OAuth2::refresh_access_token (TEB_DevelopmentBoard::TEB_HTTP::request& http_request, TEB_DevelopmentBoard::TEB_HTTP::response& http_response) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_OAuth2::refresh_access_token (TEB_DevelopmentBoard::TEB_HTTP::request& http_request, TEB_DevelopmentBoard::TEB_HTTP::response& http_response)"));
#endif
  initialize_http_request(http_request);
  if (temp_p == NULL) { //I need to read refresh token from eeprom.
    temp_p = (const char*)splittable_buffer->SX();
    if (get_refresh_token_eeprom((char*)temp_p) != 1) {
#ifdef TEB_DB_DEBUG
      TEB_DevelopmentBoard::TEB_Debug::error(35, F("TEB_OAuth2::refresh_access_token returned -1."));
#endif
      return -1;
    }
    splittable_buffer->splitSX(temp_p + strlen(temp_p) + 1); //Is released in generate_step7_request_text.
    temp_p = temp_p + 2;
  }
  else {
    if (http_response.headerLength == 1) { //I want to save the refresh token in the eeprom.
      if (set_refresh_token_eeprom(temp_p) != 1) {
#ifdef TEB_DB_DEBUG
        TEB_DevelopmentBoard::TEB_Debug::error(36, F("TEB_OAuth2::refresh_access_token returned -2."));
#endif
        return -2;
      }
#ifdef TEB_DB_DEBUG
      TEB_DevelopmentBoard::TEB_Debug::print(F("\nThe refresh token has been saved in the EEPROM.\n"));
#endif
    }
  }
  http_request.requestText = generate_http_request_text(7);  //Ends with \0.
  temp_p = http_response.header; //Contains accessTokenBuffer  .
  int8_t r = TEB_DevelopmentBoard::TEB_HTTP::sendRequest(http_request, http_response, (char*)splittable_buffer->SX(), splittable_buffer->freeSpace(), response_reception_algorithm);
  if (r != 1) {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::error(37, F("TEB_OAuth2::refresh_access_token returned -3."));
#endif
    return -3;
  }
  http_response_property http_response_property;
  splittable_buffer->addDXreverse_P(str12, strlen_P(str12) + 1);
  splittable_buffer->addDXreverse_P(str13);
  http_response_property.property = (char*)splittable_buffer->splitDXreverse();
  r = handle_server_response(http_response, http_response_property);
  if (r == 1 && http_response_property.status_code == 200) {
    TEB_Strings::append((char*)temp_p, http_response_property.property, http_response_property.property + http_response_property.property_length);
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::print(F("\nThe access token read is "));
    TEB_DevelopmentBoard::TEB_Debug::print(temp_p);
    TEB_DevelopmentBoard::TEB_Debug::print(F(".\n"));
#endif
    return 1;
  }
  else {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::error(38, F("TEB_OAuth2::refresh_access_token returned -4."));
#endif
    return -4;
  }
}

int8_t TEB_OAuth2::revoke_token (TEB_DevelopmentBoard::TEB_HTTP::request& http_request, TEB_DevelopmentBoard::TEB_HTTP::response& http_response) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_OAuth2::revoke_token (TEB_DevelopmentBoard::TEB_HTTP::request& http_request, TEB_DevelopmentBoard::TEB_HTTP::response& http_response)"));
#endif
  initialize_http_request(http_request);
  http_request.requestText = generate_http_request_text(8); //Ends with \0.
  int8_t r = TEB_DevelopmentBoard::TEB_HTTP::sendRequest(http_request, http_response, (char*)splittable_buffer->SX(), splittable_buffer->freeSpace(), response_reception_algorithm);
  if (r != 1) {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::error(39, F("TEB_OAuth2::revoke_token returned -1."));
#endif
    return -1;
  }
  http_response_property http_response_property;
  http_response_property.property = 0;
  r = handle_server_response(http_response, http_response_property);
  if (r == 2 && http_response_property.status_code == 200) {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::print(F("\nLogged out with access token "));
    TEB_DevelopmentBoard::TEB_Debug::print(temp_p);
    TEB_DevelopmentBoard::TEB_Debug::print(F(".\n"));
#endif
    return 1;
  }
  else {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::error(40, F("TEB_OAuth2::revoke_token returned -2."));
#endif
    return -2;
  }
}

int8_t TEB_OAuth2::handle_server_response (TEB_DevelopmentBoard::TEB_HTTP::response& http_response, http_response_property& http_response_property) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_OAuth2::handle_server_response (TEB_DevelopmentBoard::TEB_HTTP::response& http_response, http_response_property& http_response_property)"));
#endif
  char* t1 = (char*)splittable_buffer->DX() - strlen_P(str16);
  TEB_Strings::append_P(t1, str16);
  const char* t2 = TEB_Strings::indexOf(http_response.header, http_response.header + http_response.headerLength, t1 + 1, t1 + 9);
  if (t2 == 0) {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::error(41, F("TEB_OAuth2::handle_server_response returned -1."));
#endif
    return -1;
  }
  t1 = (char*) t2 + 9;
  uint16_t code;
  if (TEB_Numbers::isInt(t1, t1 + 3)) {
    code = TEB_Numbers::charInt(t1, t1 + 3);
  }
  else {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::error(42, F("TEB_OAuth2::handle_server_response returned -2."));
#endif
    return -2;
  }
  http_response_property.status_code = code;
  if (http_response_property.property == NULL) return 2;
  http_response_property.property_length = strlen(http_response_property.property);
  t1 = (char*) TEB_Strings::indexOf(http_response.payload, http_response.payload + http_response.payloadLength, http_response_property.property, http_response_property.property + http_response_property.property_length);
  if (t1 == 0) {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::error(43, F("TEB_OAuth2::handle_server_response returned -3."));
#endif
    return -3;
  }
  if (*(t1 - 1) != '"' || *(t1 + http_response_property.property_length) != '"' || *(t1 + http_response_property.property_length + 1) != ':') {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::error(44, F("TEB_OAuth2::handle_server_response returned -4."));
#endif
    return -4;
  }
  t1 = t1 + http_response_property.property_length + 3;
  if (*t1 == '"') t1++;
  t2 = TEB_Strings::indexOf(t1 + 1, "\n");
  if (t2 == 0) {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::error(45, F("TEB_OAuth2::handle_server_response returned -5."));
#endif
    return -5;
  }
  t2--;
  if (*t2 == ',') t2--;
  if (*t2 == '"') t2--;
  http_response_property.property = t1;
  http_response_property.property_length = t2 - t1 + 1;
  return 1;
}

char* TEB_OAuth2::response_reception_algorithm (void* client, char* response_buffer, size_t response_buffer_size, uint16_t response_delay) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_OAuth2::response_reception_algorithm (void* client, char* response_buffer, size_t response_buffer_size, uint16_t response_delay)"));
#endif
  uint32_t m = millis();
  uint16_t nbit = 256; //nbit > 0 and <= response_buffer_size.
  int n;
  char* b = response_buffer;
  while (true) {
    if (response_buffer_size < nbit) nbit = response_buffer_size;
    n = ((WiFiClientSecure*)client)->read((uint8_t*)response_buffer, nbit);
    if (n != -1 && n != 0) {
      response_buffer = response_buffer + n;
      response_buffer_size = response_buffer_size - n;
      if (response_buffer - b >= 7) {
        b = (char*)TEB_Strings::lastIndexOf(b, response_buffer, "\r\n0\r\n\r\n");
        if (b != 0) {
          response_buffer = b + 7;
#ifdef TEB_DB_DEBUG
          TEB_DevelopmentBoard::TEB_Debug::print(F("\nTEB_OAuth2::response_reception_algorithm has correctly detected the final string of the http response.\n"));
#endif
          break;
        }
        else {
          b = response_buffer - 6;
        }
      }
      if (response_buffer_size == 0) {
#ifdef TEB_DB_DEBUG
        TEB_DevelopmentBoard::TEB_Debug::error(46, F("TEB_OAuth2::response_reception_algorithm did not find at the end \r\n0\r\n\r\n. Maybe response_buffer is too short."));
#endif
        break;
      }
      m = millis();
    }
    else if (m + response_delay < millis()) {
#ifdef TEB_DB_DEBUG
      TEB_DevelopmentBoard::TEB_Debug::error(47, F("TEB_OAuth2::response_reception_algorithm did not find at the end \r\n0\r\n\r\n. There may be problems with the Internet connection."));
#endif
      break;
    }
  }
  return response_buffer;
}

int8_t TEB_OAuth2::allocate_splittable_buffer (size_t size) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_OAuth2::allocate_splittable_buffer (size_t size)"));
  if (splittable_buffer == NULL) {
    TEB_DevelopmentBoard::TEB_Debug::fatalError(171, F("splittable_buffer cannot be NULL."));
  }
#endif
  if (imported_array == NULL) { //I use dynamic buffer.
    if (splittable_buffer->dynamicAllocation(size) != 1) {
#ifdef TEB_DB_DEBUG
      TEB_DevelopmentBoard::TEB_Debug::fatalError(172, F("Dinamic allocation of splittable_buffer failed."));
#endif
      return -1;
    }
  }
  else {
    if (splittable_buffer->arrayImport(imported_array, size) != 1) {
#ifdef TEB_DB_DEBUG
      TEB_DevelopmentBoard::TEB_Debug::fatalError(173, F("Static allocation of splittable_buffer failed."));
#endif
      return -2;
    }
  }
  return 1;
}

int8_t TEB_OAuth2::deallocate_splittable_buffer () {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_OAuth2::deallocate_splittable_buffer ()"));
  if (splittable_buffer == NULL) {
    TEB_DevelopmentBoard::TEB_Debug::fatalError(174, F("splittable_buffer cannot be NULL."));
  }
#endif
  int8_t r = splittable_buffer->deallocate();
  if (r != 1) {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::fatalError(175, F("Deallocation of splittable_buffer failed."));
#endif
    return -1;
  }
  return 1;
}

int16_t TEB_OAuth2::refresh_token_eeprom_length () {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_OAuth2::refresh_token_eeprom_length ()"));
#endif
  uint8_t ee[2];
  if (TEB_DevelopmentBoard::TEB_EEPROM::read(ee, 2) != 1) {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::fatalError(176, F("EEPROM reading error."));
#endif
    return -1;
  }
  return (uint16_t)ee[0] + (uint16_t)ee[1];
}

int8_t TEB_OAuth2::get_refresh_token_eeprom (char* refresh_token_buffer) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_OAuth2::get_refresh_token_eeprom (char* refresh_token_buffer)"));
#endif
  int16_t t = refresh_token_eeprom_length();
  if (t == -1) return -1;
  if (TEB_DevelopmentBoard::TEB_EEPROM::read((uint8_t*)refresh_token_buffer, t + 2) != 1) {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::fatalError(177, F("EEPROM reading error."));
#endif
    return -2;
  }
  *(refresh_token_buffer + t + 2) = '\0';
  return 1;
}

int8_t TEB_OAuth2::set_refresh_token_eeprom (const char* refresh_token) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_OAuth2::set_refresh_token_eeprom (const char* refresh_token)"));
#endif
  uint16_t l = strlen(refresh_token);
  uint8_t t[l + 2];
  if (l > 255) {
    t[0] = 255;
    t[1] = l - 255;
  }
  else {
    t[0] = l;
    t[1] = 0;
  }
  TEB_Strings::append((char*)(t + 2), refresh_token, refresh_token + l);
  if (TEB_DevelopmentBoard::TEB_EEPROM::write(t, l + 2) != 1) {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::fatalError(178, F("EEPROM writing error."));
#endif
    return -1;
  }
  return 1;
}

int8_t TEB_OAuth2::login_ (const char* scope, char* access_token_buffer, char* refresh_token_buffer, bool save_refresh_token, void (*step3_display_user_code) (const char* text)) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_OAuth2::login_ (const char* scope, char* access_token_buffer, char* refresh_token_buffer, bool save_refresh_token, void (*step3_display_user_code) (const char* text))"));
#endif
  int8_t r;
  TEB_DevelopmentBoard::TEB_HTTP::request http_request;
  TEB_DevelopmentBoard::TEB_HTTP::response http_response;
  TEB_Splittable_Array s_b;
  splittable_buffer = &s_b;
  temp_p = scope; //temp
  if (allocate_splittable_buffer(TEB_OAUTH2_SPLITTABLE_BUFFER_SIZE_FOR_LOGIN) != 1) {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::fatalError(179, F("Allocation of splittable_buffer failed in TEB_OAuth2::login_."));
#endif
    return -1;
  }
  r = step1_2_3_4_5(http_request, http_response, step3_display_user_code);
  if (r == 1) {
    if (step6(http_response, access_token_buffer, refresh_token_buffer, save_refresh_token) != 1) r = -2;
  }
  else if (r != 2) r = -3; //If r=2 permission not granted.
  if (deallocate_splittable_buffer() != 1) {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::fatalError(180, F("Buffer deallocation failed."));
#endif
    r = r - 10;
  }
  splittable_buffer = NULL;
#ifdef TEB_DB_DEBUG
  if (r < 0) {
    char t2[strlen_P(debug1) + 4];
    TEB_Strings::append(TEB_Strings::intChar(r * -1, TEB_Strings::append_P(t2, debug1)), ".");
    TEB_DevelopmentBoard::TEB_Debug::error(48, t2);
  }
#endif
  return r;
}

int8_t TEB_OAuth2::relogin_ (char* access_token_buffer, const char* refresh_token, bool save_refresh_token) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_OAuth2::relogin_ (char* access_token_buffer, const char* refresh_token, bool save_refresh_token)"));
#endif
  int8_t r = 1;
  TEB_DevelopmentBoard::TEB_HTTP::request http_request;
  TEB_DevelopmentBoard::TEB_HTTP::response http_response;
  if (refresh_token != NULL) temp_p = (char*)refresh_token;
  else {
#ifdef TEB_DB_DEBUG
    if (refresh_token_eeprom_length() == 0) {
      TEB_DevelopmentBoard::TEB_Debug::fatalError(181, F("It is not possible to execute this function without a refresh token passed as an input parameter or saved in the EEPROM."));
    }
    if (save_refresh_token) {
      TEB_DevelopmentBoard::TEB_Debug::fatalError(182, F("save_refresh_token cannot be true when the refresh token saved in the EEPROM is used."));
    }
#endif
    temp_p = NULL;
  }
  TEB_Splittable_Array s_b;
  splittable_buffer = &s_b;
  http_response.header = access_token_buffer; //temp
  if (save_refresh_token) http_response.headerLength = 1; //temp
  else http_response.headerLength = 0;
  if (allocate_splittable_buffer(TEB_OAUTH2_SPLITTABLE_BUFFER_SIZE_FOR_RELOGIN) != 1) {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::fatalError(183, F("Allocation of splittable_buffer failed in TEB_OAuth2::relogin_."));
#endif
    return -1;
  }
  if (refresh_access_token(http_request, http_response) != 1) r = -2;
  if (deallocate_splittable_buffer() != 1) {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::fatalError(184, F("Buffer deallocation failed."));
#endif
    r = r - 10;
  }
  splittable_buffer = NULL;
#ifdef TEB_DB_DEBUG
  if (r < 0) {
    char t2[strlen_P(debug2) + 4];
    TEB_Strings::append(TEB_Strings::intChar(r * -1, TEB_Strings::append_P(t2, debug2)), ".");
    TEB_DevelopmentBoard::TEB_Debug::error(49, t2);
  }
#endif
  return r;
}

int8_t TEB_OAuth2::logout_ () {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_OAuth2::logout_ ()"));
#endif
  int8_t r = 1;
  TEB_DevelopmentBoard::TEB_HTTP::request http_request;
  TEB_DevelopmentBoard::TEB_HTTP::response http_response;
  TEB_Splittable_Array s_b;
  splittable_buffer = &s_b;
  if (allocate_splittable_buffer(TEB_OAUTH2_SPLITTABLE_BUFFER_SIZE_FOR_LOGOUT) != 1) {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::fatalError(185, F("Allocation of splittable_buffer failed in TEB_OAuth2::logout_."));
#endif
    return -1;
  }
  if (revoke_token(http_request, http_response) != 1) r = -2;
  if (deallocate_splittable_buffer() != 1) {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::fatalError(186, F("Buffer deallocation failed."));
#endif
    r = r - 10;
  }
  splittable_buffer = NULL;
#ifdef TEB_DB_DEBUG
  if (r < 0) {
    char t2[strlen_P(debug3) + 4];
    TEB_Strings::append(TEB_Strings::intChar(r * -1, TEB_Strings::append_P(t2, debug3)), ".");
    TEB_DevelopmentBoard::TEB_Debug::error(50, t2);
  }
#endif
  return r;
}

void TEB_OAuth2::useDynamicBuffer () {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_OAuth2::useDynamicBuffer"));
#endif
  imported_array = NULL;
}

void TEB_OAuth2::useImportedBuffer (char* buffer) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_OAuth2::useImportedBuffer (char* buffer)"));
  if (buffer == NULL) {
    TEB_DevelopmentBoard::TEB_Debug::fatalError(187, F("buffer cannot be NULL."));
  }
#endif
  imported_array = buffer;
}

int8_t TEB_OAuth2::login (const char* scope, char* accessTokenBuffer, bool saveRefreshToken, void (*step3DisplayUserCode) (const char* text)) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_OAuth2::login (const char* scope, char* accessTokenBuffer, bool saveRefreshToken, void (*step3DisplayUserCode) (const char* text))"));
  if (scope == NULL) {
    TEB_DevelopmentBoard::TEB_Debug::fatalError(188, F("scope cannot be NULL."));
  }
  if (accessTokenBuffer == NULL) {
    TEB_DevelopmentBoard::TEB_Debug::fatalError(189,  F("accessTokenBuffer cannot be NULL."));
  }
  if (step3DisplayUserCode == NULL) {
    TEB_DevelopmentBoard::TEB_Debug::fatalError(190, F("step3DisplayUserCode cannot be NULL."));
  }
#endif
  return login_(scope, accessTokenBuffer, NULL, saveRefreshToken, step3DisplayUserCode);
}

int8_t TEB_OAuth2::login (const char* scope, char* accessTokenBuffer, char* refreshTokenBuffer, bool saveRefreshToken, void (*step3DisplayUserCode) (const char* text)) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_OAuth2::login (const char* scope, char* accessTokenBuffer, char* refreshTokenBuffer, bool saveRefreshToken, void (*step3DisplayUserCode) (const char* text))"));
  if (scope == NULL) {
    TEB_DevelopmentBoard::TEB_Debug::fatalError(191, F("scope cannot be NULL."));
  }
  if (accessTokenBuffer == NULL) {
    TEB_DevelopmentBoard::TEB_Debug::fatalError(192,  F("accessTokenBuffer cannot be NULL."));
  }
  if (refreshTokenBuffer == NULL) {
    TEB_DevelopmentBoard::TEB_Debug::fatalError(193,  F("refreshTokenBuffer cannot be NULL."));
  }
  if (step3DisplayUserCode == NULL) {
    TEB_DevelopmentBoard::TEB_Debug::fatalError(194, F("step3DisplayUserCode cannot be NULL."));
  }
#endif
  return login_(scope, accessTokenBuffer, refreshTokenBuffer, saveRefreshToken, step3DisplayUserCode);
}

int8_t TEB_OAuth2::relogin (char* accessTokenBuffer) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_OAuth2::relogin (char* accessTokenBuffer)"));
  if (accessTokenBuffer == NULL) {
    TEB_DevelopmentBoard::TEB_Debug::fatalError(195, F("accessTokenBuffer cannot be NULL."));
  }
#endif
  return relogin_(accessTokenBuffer, NULL, false);
}

int8_t TEB_OAuth2::relogin (char* accessTokenBuffer, const char* refreshToken, bool saveRefreshToken) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_OAuth2::relogin (char* accessTokenBuffer, const char* refreshToken, bool saveRefreshToken)"));
  if (refreshToken == NULL) {
    TEB_DevelopmentBoard::TEB_Debug::fatalError(196, F("refreshToken cannot be NULL."));
  }
  if (accessTokenBuffer == NULL) {
    TEB_DevelopmentBoard::TEB_Debug::fatalError(197, F("accessTokenBuffer cannot be NULL."));
  }
#endif
  return relogin_(accessTokenBuffer, refreshToken, saveRefreshToken);
}

int8_t TEB_OAuth2::logout (const char* token) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_OAuth2::logout (const char* token)"));
  if (token == NULL) {
    TEB_DevelopmentBoard::TEB_Debug::fatalError(198, F("token cannot be NULL."));
  }
#endif
  temp_p = token;
  return logout_();
}

bool TEB_OAuth2::refreshTokenEEPROM () {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_OAuth2::refreshTokenEEPROM ()"));
#endif
  int16_t r = refresh_token_eeprom_length();
  if (r == 0 || r == -1) return false;
  else return true;
}

char* TEB_OAuth2::getRefreshTokenEEPROM (char* refreshTokenBuffer) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_OAuth2::getRefreshTokenEEPROM (char* refreshTokenBuffer)"));
  if (refreshTokenBuffer == NULL) {
    TEB_DevelopmentBoard::TEB_Debug::fatalError(199, F("refreshTokenBuffer cannot be NULL."));
  }
#endif
  if (get_refresh_token_eeprom(refreshTokenBuffer) != 1) {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::fatalError(200, F("TEB_OAuth2::getRefreshTokenEEPROM returned NULL."));
#endif
    return NULL;
  }
  return refreshTokenBuffer + 2;
}

int8_t TEB_OAuth2::deleteRefreshTokenEEPROM () {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_OAuth2::deleteRefreshTokenEEPROM ()"));
  if (!refreshTokenEEPROM()) TEB_DevelopmentBoard::TEB_Debug::fatalError(201, F("You cannot use this function if there is no refresh token in the EEPROM."));
#endif
  uint8_t rf[2];
  rf[0] = 0;
  rf[1] = 0;
  if (TEB_DevelopmentBoard::TEB_EEPROM::write(rf, 2) != 1) {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::fatalError(202, F("TEB_OAuth2::deleteRefreshTokenEEPROM returned -1."));
#endif
    return -1;
  }
  return 1;
}

#ifdef TEB_DB_DEBUG
void TEB_OAuth2::s3PrintText (const char* t) {
  TEB_DevelopmentBoard::TEB_Display::print(t, 1);
}
void TEB_OAuth2::test (const char* ssid, const char* password, uint32_t timeOut) {
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_OAuth2::test (const char* ssid, const char* password, uint32_t timeOut)"));
  TEB_DevelopmentBoard::TEB_Debug::print(TEB_Library_global_string_for_debugging1);
  TEB_DevelopmentBoard::TEB_Debug::print(F("TEB_OAuth2"));
  TEB_DevelopmentBoard::TEB_Debug::print(TEB_Library_global_string_for_debugging2);
  TEB_DevelopmentBoard::TEB_Debug::print(F("\n"));
  char accessTokenBuffer[250], refreshTokenBuffer[250];
  if (TEB_DevelopmentBoard::TEB_WiFi::check() != 1) {
    if (TEB_DevelopmentBoard::TEB_WiFi::connect(ssid, password, timeOut) != 1) {
      TEB_DevelopmentBoard::TEB_Debug::print(F("\nCannot connect to the Internet. End of the test.\n"));
      return;
    }
  }
  TEB_DevelopmentBoard::TEB_Debug::print(F("\nLogin test 1\n"));
  if (login("https://www.googleapis.com/auth/drive.file", accessTokenBuffer, false, s3PrintText) != 1 ) {
    TEB_DevelopmentBoard::TEB_Debug::print(F("\nLogin test 1 failed. End of the test.\n"));
    return;
  }
  TEB_DevelopmentBoard::TEB_Debug::print(F("\nThe access token is "));
  TEB_DevelopmentBoard::TEB_Debug::print(accessTokenBuffer);
  TEB_DevelopmentBoard::TEB_Debug::print(F(".\n\nTest login 2\n"));
  if (login("https://www.googleapis.com/auth/drive.file", accessTokenBuffer, refreshTokenBuffer, true, s3PrintText) != 1 ) {
    TEB_DevelopmentBoard::TEB_Debug::print(F("\nLogin test 2 failed. End of the test.\n"));
    return;
  }
  TEB_DevelopmentBoard::TEB_Debug::print(F("\nThe access token is "));
  TEB_DevelopmentBoard::TEB_Debug::print(accessTokenBuffer);
  TEB_DevelopmentBoard::TEB_Debug::print(F("\n and the refresh token is "));
  TEB_DevelopmentBoard::TEB_Debug::print(refreshTokenBuffer);
  TEB_DevelopmentBoard::TEB_Debug::print(F(".\n\nTest relogin 1\n"));
  if (relogin(accessTokenBuffer, refreshTokenBuffer, true) != 1 ) {
    TEB_DevelopmentBoard::TEB_Debug::print(F("\nRelogin test 1 failed. End of the test.\n"));
    return;
  }
  TEB_DevelopmentBoard::TEB_Debug::print(F("\nThe access token is "));
  TEB_DevelopmentBoard::TEB_Debug::print(accessTokenBuffer);
  TEB_DevelopmentBoard::TEB_Debug::print(F("\n and the refresh token is "));
  TEB_DevelopmentBoard::TEB_Debug::print(refreshTokenBuffer);
  TEB_DevelopmentBoard::TEB_Debug::print(F(".\n\nTest relogin 2\n"));
  if (relogin(accessTokenBuffer) != 1 ) {
    TEB_DevelopmentBoard::TEB_Debug::print(F("\nRelogin test 2 failed. End of the test.\n"));
    return;
  }
  TEB_DevelopmentBoard::TEB_Debug::print(F("\nThe access token is "));
  TEB_DevelopmentBoard::TEB_Debug::print(accessTokenBuffer);
  TEB_DevelopmentBoard::TEB_Debug::print(F(".\n\nTest logout\n"));
  if (logout(accessTokenBuffer) != 1 ) {
    TEB_DevelopmentBoard::TEB_Debug::print(F("\nLogout test failed. End of the test.\n"));
    return;
  }
  getRefreshTokenEEPROM(refreshTokenBuffer);
  if (refreshTokenBuffer == NULL) {
    TEB_DevelopmentBoard::TEB_Debug::print(F("\ngetRefreshTokenEEPROM(). End of the test.\n"));
    return;
  }
  TEB_DevelopmentBoard::TEB_Debug::print(F("\nThe refresh token saved in the EEPROM is "));
  TEB_DevelopmentBoard::TEB_Debug::print(refreshTokenBuffer + 2);
  TEB_DevelopmentBoard::TEB_Debug::print(F(".\n"));
  if (deleteRefreshTokenEEPROM() != 1) {
    TEB_DevelopmentBoard::TEB_Debug::print(F("\ndeleteRefreshTokenEEPROM test failed. End of the test.\n"));
    return;
  }
  TEB_DevelopmentBoard::TEB_Debug::print(F("\nThe refresh token has been cleared from the EEPROM.\n"));
  TEB_DevelopmentBoard::TEB_Debug::print(TEB_Library_global_string_for_debugging3);
}
#endif