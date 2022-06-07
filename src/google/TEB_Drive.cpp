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

  This class is based on the guide https://developers.google.com/drive/api/v3/reference.
*/

#include "../development_board/TEB_Debug.h"
#include "../TEB_External_dependencies.h"
#include "../development_board/TEB_Display.h"
#include "../development_board/TEB_WiFi.h"
#include "TEB_Drive.h"

uint16_t TEB_Drive::temp_i1 = 0;
uint8_t TEB_Drive::temp_i2 = 0;
const char* TEB_Drive::temp_p1 = NULL;
const char* TEB_Drive::temp_p2 = NULL;
const char* TEB_Drive::temp_p3 = NULL;
const char* TEB_Drive::temp_p4 = NULL;
const char* TEB_Drive::temp_p5 = NULL;

const char TEB_Drive::str1[] PROGMEM = "https://www.googleapis.com";
const char TEB_Drive::str2[] PROGMEM = "drive/v3/files";
const char TEB_Drive::str3[] PROGMEM = "?key=";
const char TEB_Drive::str4[] PROGMEM = " HTTP/1.1\r\nAuthorization:Bearer ";
const char TEB_Drive::str5[] PROGMEM = "&orderBy=";
const char TEB_Drive::str6[] PROGMEM = "&pageSize=";
const char TEB_Drive::str7[] PROGMEM = "&pageToken=";
const char TEB_Drive::str8[] PROGMEM = "&q=";
const char TEB_Drive::str9[] PROGMEM = "&fields=";
const char TEB_Drive::str10[] PROGMEM = "Parents=";
const char TEB_Drive::str11[] PROGMEM = "&remove";
const char TEB_Drive::str12[] PROGMEM = "&uploadType";
const char TEB_Drive::str13[] PROGMEM = "=media";
const char TEB_Drive::str14[] PROGMEM = "\r\nAccept:";
const char TEB_Drive::str15[] PROGMEM = "Content-Type:";
const char TEB_Drive::str16[] PROGMEM = "Length:";
const char TEB_Drive::str17[] PROGMEM = "\"name\":\"";
const char TEB_Drive::str18[] PROGMEM = "\"parents\":[\"";
const char TEB_Drive::str19[] PROGMEM = "mimeType\":\"";
const char TEB_Drive::str20[] PROGMEM = "application/json";
#ifdef TEB_DB_DEBUG
const char TEB_Drive::debug1[] PROGMEM = "TEB_Drive::execute_http_request returned -";
#endif

/*
  temp_i1    page_size2
  temp_p1   order_by2         remove_parents3   parent1
  temp_p2   page_token2     add_parents3          mime_type1        file_data4
  temp_p3   q2                      file_name1_3 1      mime_type4      mime_type7
  temp_p4   fields2                   file_id3_4_5_6_7
  temp_p5     access_token      access_token          access_token          access_token    access_token
*/

void TEB_Drive::initialize_http_request (TEB_HTTP::request& http_request) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Drive::initialize_http_request (TEB_HTTP::request& http_request)"));
#endif
  //Load on the left all values except requestText.
  TEB_OAuth2::splittable_buffer->addSX("https://www.googleapis.com", 35);
  http_request.serverAddress = (const char*)TEB_OAuth2::splittable_buffer->splitSX();
  TEB_OAuth2::splittable_buffer->addSX_P(TEB_OAuth2::oauth2_root_ca, strlen_P(TEB_OAuth2::oauth2_root_ca) + 1);
  http_request.rootCA = (const char*)TEB_OAuth2::splittable_buffer->splitSX();
  http_request.serverPort = TEB_OAuth2::oauth2_server_port;
  http_request.connectionTimeout = TEB_OAUTH2_HTTP_REQUEST_CONNECTION_TIMEOUT;
  http_request.responseDelay = 10000;
}

const char* TEB_Drive::generate_http_request_text (uint8_t type) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Drive::generate_http_request_text (uint8_t type)"));
#endif
  const char* t = "\r\n";
  size_t free_space;
  TEB_OAuth2::splittable_buffer->addDXreverse("", 1);
  if (type == 4) {
    free_space = TEB_OAuth2::splittable_buffer->freeSpace();
    TEB_OAuth2::splittable_buffer->addDXreverse(temp_p2, strlen(temp_p2));
  }
  if (type == 1 || type == 3) {
    free_space = TEB_OAuth2::splittable_buffer->freeSpace();
    TEB_OAuth2::splittable_buffer->addDXreverse("}", 1);
    if (type == 1) {
      if (temp_p2 != NULL) {
        TEB_OAuth2::splittable_buffer->addDXreverse("\"", 1);
        TEB_OAuth2::splittable_buffer->addDXreverse(temp_p2, strlen(temp_p2));
        TEB_OAuth2::splittable_buffer->addDXreverse_P(str19);
        TEB_OAuth2::splittable_buffer->addDXreverse("\"", 1);
      }
      if (temp_p1 != NULL) {
        if (temp_p2 != NULL) TEB_OAuth2::splittable_buffer->addDXreverse(",", 1);
        TEB_OAuth2::splittable_buffer->addDXreverse("\"]", 2);
        TEB_OAuth2::splittable_buffer->addDXreverse(temp_p1, strlen(temp_p1));
        TEB_OAuth2::splittable_buffer->addDXreverse_P(str18);
      }
    }
    if (temp_p3 != NULL) {
      if ((temp_p2 != NULL || temp_p1 != NULL) && type == 1) TEB_OAuth2::splittable_buffer->addDXreverse(",", 1);
      TEB_OAuth2::splittable_buffer->addDXreverse("\"", 1);
      TEB_OAuth2::splittable_buffer->addDXreverse(temp_p3, strlen(temp_p3));
      TEB_OAuth2::splittable_buffer->addDXreverse_P(str17);
    }
    TEB_OAuth2::splittable_buffer->addDXreverse("{", 1);
  }
  TEB_OAuth2::splittable_buffer->addDXreverse(t, 2);
  TEB_OAuth2::splittable_buffer->addDXreverse(t, 2);
  if (type == 1 || type == 3 || type == 4) {
    TEB_Strings::intChar(free_space - TEB_OAuth2::splittable_buffer->freeSpace() - 4, (char*)TEB_OAuth2::splittable_buffer->SX());
    TEB_OAuth2::splittable_buffer->addDXreverse((const char*)TEB_OAuth2::splittable_buffer->SX(), strlen((const char*)TEB_OAuth2::splittable_buffer->SX()));
    TEB_OAuth2::splittable_buffer->addDXreverse_P(str16);
    TEB_OAuth2::splittable_buffer->addDXreverse_P(str15, 8);
    TEB_OAuth2::splittable_buffer->addDXreverse(t, 2);
    if (type == 4) TEB_OAuth2::splittable_buffer->addDXreverse(temp_p3, strlen(temp_p3));
    else TEB_OAuth2::splittable_buffer->addDXreverse_P(str20);
    TEB_OAuth2::splittable_buffer->addDXreverse_P(str15);
    TEB_OAuth2::splittable_buffer->addDXreverse(t, 2);
  }
  TEB_OAuth2::splittable_buffer->addDXreverse_P(str20);
  TEB_OAuth2::splittable_buffer->addDXreverse_P(str14);
  TEB_OAuth2::splittable_buffer->addDXreverse(temp_p5, strlen(temp_p5));
  TEB_OAuth2::splittable_buffer->addDXreverse_P(str4);
  switch (type) {
    case 2:
      if (temp_p4 != NULL) {
        TEB_OAuth2::splittable_buffer->addDXreverse(temp_p4, strlen(temp_p4));
        TEB_OAuth2::splittable_buffer->addDXreverse_P(str9);
      }
      if (temp_p3 != NULL) {
        TEB_OAuth2::splittable_buffer->addDXreverse(temp_p3, strlen(temp_p3));
        TEB_OAuth2::splittable_buffer->addDXreverse_P(str8);
      }
      if (temp_p2 != NULL) {
        TEB_OAuth2::splittable_buffer->addDXreverse(temp_p2, strlen(temp_p2));
        TEB_OAuth2::splittable_buffer->addDXreverse_P(str7);
      }
      if (temp_i1 != 0) {
        TEB_Strings::intChar(temp_i1, (char*)TEB_OAuth2::splittable_buffer->SX());
        TEB_OAuth2::splittable_buffer->addDXreverse((const char*)TEB_OAuth2::splittable_buffer->SX(), strlen((const char*)TEB_OAuth2::splittable_buffer->SX()));
        TEB_OAuth2::splittable_buffer->addDXreverse_P(str6);
      }
      if (temp_p1 != NULL) {
        TEB_OAuth2::splittable_buffer->addDXreverse(temp_p1, strlen(temp_p1));
        TEB_OAuth2::splittable_buffer->addDXreverse_P(str5);
      }
      break;
    case 3:
      if (temp_p1 != NULL) {
        TEB_OAuth2::splittable_buffer->addDXreverse(temp_p1, strlen(temp_p1));
        TEB_OAuth2::splittable_buffer->addDXreverse_P(str10);
        TEB_OAuth2::splittable_buffer->addDXreverse_P(str11);
      }
      if (temp_p2 != NULL) {
        TEB_OAuth2::splittable_buffer->addDXreverse(temp_p2, strlen(temp_p2));
        TEB_OAuth2::splittable_buffer->addDXreverse_P(str10);
        TEB_OAuth2::splittable_buffer->addDXreverse("&add", 4);
      }
      break;
    case 4:
      TEB_OAuth2::splittable_buffer->addDXreverse_P(str13);
      TEB_OAuth2::splittable_buffer->addDXreverse_P(str12);
      break;
    case 5:
      TEB_OAuth2::splittable_buffer->addDXreverse_P(str13);
      TEB_OAuth2::splittable_buffer->addDXreverse("&alt", 4);
      break;
    case 7:
      TEB_OAuth2::splittable_buffer->addDXreverse(temp_p3, strlen(temp_p3));
      TEB_OAuth2::splittable_buffer->addDXreverse("=", 1);
      TEB_OAuth2::splittable_buffer->addDXreverse_P(str19, 8);
      TEB_OAuth2::splittable_buffer->addDXreverse("&", 1);
      break;
  }
  TEB_OAuth2::splittable_buffer->addDXreverse_P(TEB_OAuth2::oauth2_api_key);
  TEB_OAuth2::splittable_buffer->addDXreverse_P(str3);
  if (type == 7) TEB_OAuth2::splittable_buffer->addDXreverse("/export", 7);
  if (type == 3 || type == 4 || type == 5 || type == 6 || type == 7) {
    TEB_OAuth2::splittable_buffer->addDXreverse(temp_p4, strlen(temp_p4));
    TEB_OAuth2::splittable_buffer->addDXreverse("/", 1);
  }
  TEB_OAuth2::splittable_buffer->addDXreverse_P(str2);
  if (type == 4) TEB_OAuth2::splittable_buffer->addDXreverse("upload/", 7);
  TEB_OAuth2::splittable_buffer->addDXreverse("/", 1);
  TEB_OAuth2::splittable_buffer->addDXreverse_P(str1);
  TEB_OAuth2::splittable_buffer->addDXreverse(" ", 1);
  if (type == 4) type = 3;
  if (type == 5 || type == 7) type = 2;
  switch (type) {
    case 1:
      TEB_OAuth2::splittable_buffer->addDXreverse("POST", 4);
      break;
    case 2:
      TEB_OAuth2::splittable_buffer->addDXreverse("GET", 3);
      break;
    case 3:
      TEB_OAuth2::splittable_buffer->addDXreverse("PATCH", 5);
      break;
    case 6:
      TEB_OAuth2::splittable_buffer->addDXreverse("DELETE", 6);
      break;
  }
  t = (const char*)TEB_OAuth2::splittable_buffer->splitDXreverse();
  TEB_OAuth2::splittable_buffer->resetSX();
  TEB_OAuth2::splittable_buffer->resetDX();
  return t;
}

int8_t TEB_Drive::execute_http_request (uint8_t type, char* buffer1) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Drive::execute_http_request (uint8_t type, char* buffer1)"));
#endif
  int8_t r;
  TEB_HTTP::request http_request;
  TEB_HTTP::response http_response;
  TEB_Splittable_Array s_b;
  TEB_OAuth2::splittable_buffer = &s_b;
  size_t size;
  switch (type) {
    case 1:
      size = TEB_OAUTH2_SPLITTABLE_BUFFER_SIZE_FOR_CREATE_METADATA_ONLY_FILE;
      break;
    case 2:
      size = TEB_OAUTH2_SPLITTABLE_BUFFER_SIZE_FOR_SEARCH_FILE;
      break;
    case 3:
      size = TEB_OAUTH2_SPLITTABLE_BUFFER_SIZE_FOR_UPDATE_FILE_METADATA;
      break;
    case 4:
      size = TEB_OAUTH2_SPLITTABLE_BUFFER_SIZE_FOR_UPDATE_FILE_CONTENT;
      break;
    case 5:
      size = TEB_OAUTH2_SPLITTABLE_BUFFER_SIZE_FOR_GET_FILE_CONTENT;
      break;
    case 6:
      size = TEB_OAUTH2_SPLITTABLE_BUFFER_SIZE_FOR_DELETE_FILE;
      break;
    case 7:
      size = TEB_OAUTH2_SPLITTABLE_BUFFER_SIZE_FOR_EXPORT_GOOGLE_DOC_CONTENT;
      break;
  }
  if (TEB_OAuth2::allocate_splittable_buffer(size) != 1) {
#ifdef TEB_DB_DEBUG
    TEB_Debug::fatalError(155, F("Allocation of TEB_OAuth2::splittable_buffer failed in TEB_Drive::execute_http_request."));
#endif
    return -1;
  }
  initialize_http_request(http_request);
  http_request.requestText = generate_http_request_text(type);
  r = TEB_HTTP::sendRequest(http_request, http_response, (char*)TEB_OAuth2::splittable_buffer->SX(), TEB_OAuth2::splittable_buffer->freeSpace(), response_reception_algorithm);
  if (r == 1) {
    TEB_OAuth2::http_response_property http_response_property;
    if (type == 1) http_response_property.property = "id";
    else http_response_property.property = NULL;
    r = TEB_OAuth2::handle_server_response(http_response, http_response_property);
    if (type == 1) {
      if (r == 1) {
        if (http_response_property.status_code == 200) {
#ifndef TEB_DB_DEBUG
          TEB_Strings::append(buffer1, http_response_property.property, http_response_property.property + http_response_property.property_length);
#endif
#ifdef TEB_DB_DEBUG
          if (http_response_property.property_length == 0) *buffer1 = '\0';
          else TEB_Strings::append(buffer1, http_response_property.property, http_response_property.property + http_response_property.property_length);
#endif
          r = 1;
        }
        else r = -7; //Wrong response_code.
      }
      else r = -6;
    }
    else {
      if (r == 2) {
        if (type == 6) {
          if (http_response_property.status_code == 204) r = 1;
          else r = -4;
        }
        else {
          if (http_response_property.status_code == 200) {
            if (type == 5) {
#ifndef TEB_DB_DEBUG
              TEB_Strings::append(buffer1, http_response.payload, http_response.payload + http_response.payloadLength);
#endif
#ifdef TEB_DB_DEBUG
	      if (http_response.payloadLength == 0) *buffer1 = '\0';
              else TEB_Strings::append(buffer1, http_response.payload, http_response.payload + http_response.payloadLength);
#endif
            }
            else if (type == 7 || type == 2) {
              while (*http_response.payload != '\n') {
                http_response.payload++;
                http_response.payloadLength--;
              }
              http_response.payload++;
              http_response.payloadLength--;
              if (type == 2) http_response.payloadLength--;
#ifndef TEB_DB_DEBUG
              TEB_Strings::append(buffer1, http_response.payload, http_response.payload + http_response.payloadLength - 7);
#endif
#ifdef TEB_DB_DEBUG
	      if (http_response.payloadLength - 7 == 0) *buffer1 = '\0';
              else TEB_Strings::append(buffer1, http_response.payload, http_response.payload + http_response.payloadLength - 7);
#endif
            }
            r = 1;
          }
          else r = -5;
        }
      }
      else r = -3;
    }
  }
  else r = -2;
  if (TEB_OAuth2::deallocate_splittable_buffer() != 1) {
#ifdef TEB_DB_DEBUG
    TEB_Debug::fatalError(16, F("Buffer deallocation failed."));
#endif
    r = r - 10;
  }
  TEB_OAuth2::splittable_buffer = NULL;
#ifdef TEB_DB_DEBUG
  if (r < 0) {
    char t2[strlen_P(debug1) + 4];
    TEB_Strings::append(TEB_Strings::intChar(r * -1, TEB_Strings::append_P(t2, debug1)), ".");
    TEB_Debug::error(17, t2);
  }
#endif
  return r;
}

char* TEB_Drive::response_reception_algorithm (void* client, char* response_buffer, size_t response_buffer_size, uint16_t response_delay) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Drive::response_reception_algorithm (void* client, char* response_buffer, size_t response_buffer_size, uint16_t response_delay)"));
#endif
  uint32_t m = millis();
  uint16_t nbit = 256;
  int n;
  char* b = response_buffer;
  char* b2 = response_buffer;
  uint8_t brackets = 0;
  uint32_t len = 0;
  while (true) {
    if (response_buffer_size < nbit) nbit = response_buffer_size;
    n = ((WiFiClientSecure*)client)->read((uint8_t*)response_buffer, nbit);
    if (n != -1 && n != 0) {
      if (temp_i2 == 4) {
        for (int i = 0; i < n; i++) {
          switch (*(response_buffer + i)) {
            case '{':
              brackets++;
              break;
            case '}':
              brackets--;
              break;
          }
        }
      }
      response_buffer = response_buffer + n;
      response_buffer_size = response_buffer_size - n;
      if (temp_i2 == 2 || temp_i2 == 3 || temp_i2 == 7) temp_i2 = 1;
      if (temp_i2 == 1) {
        if (response_buffer - b >= 7) {
          b = (char*)TEB_Strings::lastIndexOf(b, response_buffer, "\r\n0\r\n\r\n");
          if (b != 0) {
            response_buffer = b + 7;
#ifdef TEB_DB_DEBUG
            TEB_Debug::print(F("\nTEB_Drive::response_reception_algorithm has correctly detected the final string of the http response.\n"));
#endif
            break;
          }
          else {
            b = response_buffer - 6;
          }
        }
      }
      else if (temp_i2 == 4) {
        if (response_buffer - b >= 2 && brackets == 0) {
          b = (char*)TEB_Strings::lastIndexOf(b, response_buffer, "}\n");
          if (b != 0) {
            response_buffer = b + 2;
#ifdef TEB_DB_DEBUG
            TEB_Debug::print(F("\nTEB_Drive::response_reception_algorithm has correctly detected the final string of the http response.\n"));
#endif
            break;
          }
          else {
            b = response_buffer - 1;
          }
        }
      }
      else if (temp_i2 == 6) {
        if (response_buffer - b >= 10) {
          b = (char*)TEB_Strings::lastIndexOf(b, response_buffer, "No Content");
          if (b != 0) {
            *b = '\r'; b++;
            *b = '\n'; b++;
            *b = '\r'; b++;
            *b = '\n'; b++;
            response_buffer = b;
#ifdef TEB_DB_DEBUG
            TEB_Debug::print(F("\nTEB_Drive::response_reception_algorithm has correctly detected the final string of the http response.\n"));
#endif
            break;
          }
          else {
            b = response_buffer - 9;
          }
        }
      }
      else if (temp_i2 == 5) {
        if (brackets == 0) {
          if (response_buffer - b >= 4) {
            b = (char*)TEB_Strings::lastIndexOf(b, response_buffer, "\r\n\r\n");
            if (b != 0) {
              b2 = (char*)TEB_Strings::lastIndexOf(b2, response_buffer, "-Length: ");
              if (b2 != 0) {
                int i2 = 9;
                while (TEB_Numbers::charInt(*(b2 + i2)) != -1) i2++;
                if (i2 != 9) {
                  len = TEB_Numbers::charInt(b2 + 9, b2 + i2);
                  brackets = 1;
                  b = b + 4;
                }
                else {
#ifdef TEB_DB_DEBUG
                  TEB_Debug::error(18, F("TEB_Drive::response_reception_algorithm did not find the length of the payload. There may be problems with the Internet connection."));
#endif
                  response_buffer = b; //So sendRequest will return 2.
                  break;
                }
              }
              else {
#ifdef TEB_DB_DEBUG
                TEB_Debug::error(19, F("TEB_Drive::response_reception_algorithm did not find the length of the payload. There may be problems with the Internet connection."));
#endif
                response_buffer = b; //So sendRequest will return 2.
                break;
              }
            }
            else {
              b = response_buffer - 3;
            }
          }
        }
        if (brackets == 1) {
          if (response_buffer - b >= len) {
            if (response_buffer - b > len) response_buffer = b + len;
#ifdef TEB_DB_DEBUG
            TEB_Debug::print(F("\nTEB_Drive::response_reception_algorithm has correctly detected the final string of the http response.\n"));
#endif
            break;
          }
        }
      }
      if (response_buffer_size == 0) {
        if (temp_i2 == 5) response_buffer = b - 4; //So sendRequest will return 2.
#ifdef TEB_DB_DEBUG
        TEB_Debug::error(20, F("TEB_OAuth2::response_reception_algorithm finished earlier than expected. Maybe response_buffer is too short."));
#endif
        break;
      }
      m = millis();
    }
    else if (m + response_delay < millis()) {
      if (temp_i2 == 5) response_buffer = b - 4; //So sendRequest will return 2.
#ifdef TEB_DB_DEBUG
      TEB_Debug::error(21, F("TEB_Drive::response_reception_algorithm ended due to timeout. There may be problems with the Internet connection."));
#endif
      break;
    }
  }
  return response_buffer;
}

void TEB_Drive::useDynamicBuffer () {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Drive::useDynamicBuffer ()"));
#endif
  TEB_OAuth2::useDynamicBuffer();
}

void TEB_Drive::useImportedBuffer (char* buffer) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Drive::useImportedBuffer (char* buffer)"));
#endif
  TEB_OAuth2::useImportedBuffer(buffer);
}

void TEB_Drive::setAccessToken (const char* accessToken) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Drive::setAccessToken (const char* accessToken)"));
  if (accessToken == NULL) {
    TEB_Debug::fatalError(156, F("accessToken cannot be NULL."));
  }
#endif
  temp_p5 = accessToken;
}

int8_t TEB_Drive::createMetadataOnlyFile (const char* name, const char* parents, const char* mimeType, char* responseBuffer) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Drive::createMetadataOnlyFile (const char* name, const char* parents, const char* mimeType, char* responseBuffer)"));
  if (name == NULL) {
    TEB_Debug::fatalError(157,  F("name cannot be NULL."));
  }
  if (responseBuffer == NULL) {
    TEB_Debug::fatalError(158,  F("responseBuffer cannot be NULL."));
  }
  if (temp_p5 == NULL) {
    TEB_Debug::fatalError(276,  F("Set the accessToken before using this function."));
  }
#endif
  temp_i2 = 1;
  temp_p3 = name;
  temp_p1 = parents;
  temp_p2 = mimeType;
  return execute_http_request(1, responseBuffer);
}

int8_t TEB_Drive::searchFile (const char* q, const char* orderBy, const char* fields, uint16_t pageSize, const char* pageToken, char* responseBuffer) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Drive::searchFile (const char* q, const char* orderBy, const char* fields, uint16_t pageSize, const char* pageToken, char* responseBuffer)"));
  if (responseBuffer == NULL) {
    TEB_Debug::fatalError(159,  F("responseBuffer cannot be NULL."));
  }
  if (temp_p5 == NULL) {
    TEB_Debug::fatalError(279,  F("Set the accessToken before using this function."));
  }
#endif
  temp_i1 = pageSize;
  temp_i2 = 2;
  temp_p1 = orderBy;
  temp_p2 = pageToken;
  temp_p3 = q;
  temp_p4 = fields;
  return execute_http_request(2, responseBuffer);
}

int8_t TEB_Drive::updateFileMetadata (const char* fileID, const char* fileName, const char* addParents, const char* removeParents) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Drive::updateFileMetadata (const char* fileID, const char* fileName, const char* addParents, const char* removeParents)"));
  if (fileID == NULL) {
    TEB_Debug::fatalError(160,  F("fileID cannot be NULL."));
  }
  if (temp_p5 == NULL) {
    TEB_Debug::fatalError(277,  F("Set the accessToken before using this function."));
  }
#endif
  temp_i2 = 3;
  temp_p1 = removeParents;
  temp_p2 = addParents;
  temp_p3 = fileName;
  temp_p4 = fileID;
  return execute_http_request(3, NULL);
}

int8_t TEB_Drive::updateFileContent (const char* fileID, const char* fileContent, const char* mimeType) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Drive::updateFileContent (const char* fileID, const char* fileContent, const char* mimeType)"));
  if (fileID == NULL) {
    TEB_Debug::fatalError(162,  F("fileID cannot be NULL."));
  }
  if (fileContent == NULL) {
    TEB_Debug::fatalError(163,  F("fileContent cannot be NULL."));
  }
  if (mimeType == NULL) {
    TEB_Debug::fatalError(164,  F("mimeType cannot be NULL."));
  }
  if (temp_p5 == NULL) {
    TEB_Debug::fatalError(278,  F("Set the accessToken before using this function."));
  }
#endif
  temp_i2 = 4;
  temp_p2 = fileContent;
  temp_p3 = mimeType;
  temp_p4 = fileID;
  return execute_http_request(4, NULL);
}

int8_t TEB_Drive::getFileContent (const char* fileID, char* responseBuffer) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Drive::getFileContent (const char* fileID, char* responseBuffer)"));
  if (fileID == NULL) {
    TEB_Debug::fatalError(165,  F("fileID cannot be NULL."));
  }
  if (responseBuffer == NULL) {
    TEB_Debug::fatalError(166,  F("responseBuffer cannot be NULL."));
  }
  if (temp_p5 == NULL) {
    TEB_Debug::fatalError(280,  F("Set the accessToken before using this function."));
  }
#endif
  temp_i2 = 5;
  temp_p4 = fileID;
  return execute_http_request(5, responseBuffer);
}

int8_t TEB_Drive::deleteFile (const char* fileID) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Drive::deleteFile (const char* fileID)"));
  if (fileID == NULL) {
    TEB_Debug::fatalError(167,  F("fileID cannot be NULL."));
  }
  if (temp_p5 == NULL) {
    TEB_Debug::fatalError(281,  F("Set the accessToken before using this function."));
  }
#endif
  temp_i2 = 6;
  temp_p4 = fileID;
  return execute_http_request(6, NULL);
}

int8_t TEB_Drive::exportGoogleDocContent (const char* fileID, char* mimeType, char* responseBuffer) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Drive::exportGoogleDocContent (const char* fileID, char* mimeType, char* responseBuffer)"));
  if (fileID == NULL) {
    TEB_Debug::fatalError(168,  F("fileID cannot be NULL."));
  }
  if (mimeType == NULL) {
    TEB_Debug::fatalError(169,  F("mimeType cannot be NULL."));
  }
  if (responseBuffer == NULL) {
    TEB_Debug::fatalError(170,  F("responseBuffer cannot be NULL."));
  }
  if (temp_p5 == NULL) {
    TEB_Debug::fatalError(282,  F("Set the accessToken before using this function."));
  }
#endif
  temp_i2 = 7;
  temp_p3 = mimeType;
  temp_p4 = fileID;
  return execute_http_request(7, responseBuffer);
}

#ifdef TEB_DB_DEBUG
void TEB_Drive::test (const char* ssid, const char* password, uint32_t timeOut) {
  TEB_Debug tebdb = TEB_Debug(F("TEB_Drive::test (const char* ssid, const char* password, uint32_t timeOut)"));
  TEB_Debug::print(TEB_Library_global_string_for_debugging1);
  TEB_Debug::print(F("TEB_Drive"));
  TEB_Debug::print(TEB_Library_global_string_for_debugging2);
  TEB_Debug::print(F("\n"));
  char accessTokenBuffer[250];
  if (TEB_WiFi::check() != 1) {
    if (TEB_WiFi::connect(ssid, password, timeOut) != 1) {
      TEB_Debug::print(F("\nCannot connect to the Internet. End of the test.\n"));
      return;
    }
  }
  TEB_Debug::print(F("\nExecute OAuth2 authentication.\n"));
  if (TEB_OAuth2::login("https://www.googleapis.com/auth/drive.file", accessTokenBuffer, true, TEB_OAuth2::s3PrintText) != 1 ) {
    TEB_Debug::print(F("\nLogin failed. End of the test.\n"));
    return;
  }
  TEB_Debug::print(F("\nThe access token is "));
  TEB_Debug::print(accessTokenBuffer);
  char folderID[70], fileID[70], gdocID[70];
  setAccessToken(accessTokenBuffer);
  if (createMetadataOnlyFile("folder", NULL, "application/vnd.google-apps.folder", folderID) != 1 ) {
    TEB_Debug::print(F("\ncreateMetadataOnlyFile failed. End of the test.\n"));
    return;
  }
  TEB_Debug::print(F("\nfolderID is "));
  TEB_Debug::print(folderID);
  TEB_Debug::print(F(".\n"));
  if (createMetadataOnlyFile("file.txt", folderID, NULL, fileID) != 1 ) {
    TEB_Debug::print(F("\ncreateMetadataOnlyFile failed. End of the test.\n"));
    return;
  }
  TEB_Debug::print(F("\nfileID is "));
  TEB_Debug::print(fileID);
  TEB_Debug::print(F(".\n"));
  if (createMetadataOnlyFile("Google Doc", NULL, "application/vnd.google-apps.document", gdocID) != 1 ) {
    TEB_Debug::print(F("\ncreateMetadataOnlyFile failed. End of the test.\n"));
    return;
  }
  TEB_Debug::print(F("\ngdocID is "));
  TEB_Debug::print(fileID);
  TEB_Debug::print(F(".\n"));
  if (updateFileMetadata(gdocID, "folder2", NULL, NULL) != 1 ) {
    TEB_Debug::print(F("\nupdateFileMetadata failed. End of the test.\n"));
    return;
  }
  if (updateFileMetadata(gdocID, "Google Doc 2", folderID, NULL) != 1 ) {
    TEB_Debug::print(F("\nupdateFileMetadata failed. End of the test.\n"));
    return;
  }
  if (updateFileMetadata(fileID, NULL, NULL, folderID) != 1 ) {
    TEB_Debug::print(F("\nupdateFileMetadata failed. End of the test.\n"));
    return;
  }
  if (updateFileContent(fileID, "Hello!", "text/plain") != 1 ) {
    TEB_Debug::print(F("\nupdateFileContent failed. End of the test.\n"));
    return;
  }
  if (updateFileContent(gdocID, "Hello!", "application/vnd.google-apps.document") != 1 ) {
    TEB_Debug::print(F("\nupdateFileContent failed. End of the test.\n"));
    return;
  }
  char responseBuffer[250];
  if (getFileContent(fileID, responseBuffer) != 1 ) {
    TEB_Debug::print(F("\ngetFileContent failed. End of the test.\n"));
    return;
  }
  TEB_Debug::print(F("\nThe text contained in file.txt is: "));
  TEB_Debug::print(responseBuffer);
  TEB_Debug::print(F(".\n"));
  if (exportGoogleDocContent(gdocID, "text/plain", responseBuffer) != 1 ) {
    TEB_Debug::print(F("\nexportGoogleDocContent failed. End of the test.\n"));
    return;
  }
  TEB_Debug::print(F("\nThe text contained in Google Doc 2 is: "));
  TEB_Debug::print(responseBuffer);
  TEB_Debug::print(F(".\n"));
  char t1[200], t2[60];
  TEB_Strings::percentEncoding(t1, "name = 'file.txt' or name = 'Google Doc 2' or name = 'folder2'");
  TEB_Strings::percentEncoding(t2, "files/id,files/name");
  if (searchFile(t1, "name", t2, 3, NULL, responseBuffer) != 1 ) {
    TEB_Debug::print(F("\nsearchFile failed. End of the test.\n"));
    return;
  }
  TEB_Debug::print(F("\nThe files found are:\n"));
  TEB_Debug::print(responseBuffer);
  TEB_Debug::print(F(".\n"));
  if (deleteFile(folderID) != 1 ) {
    TEB_Debug::print(F("\ndeleteFile failed. End of the test.\n"));
    return;
  }
  if (deleteFile(fileID) != 1 ) {
    TEB_Debug::print(F("\ndeleteFile failed. End of the test.\n"));
    return;
  }
  TEB_Debug::print(TEB_Library_global_string_for_debugging3);
  return;
}
#endif
