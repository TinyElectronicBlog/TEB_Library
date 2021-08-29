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
*/

#include "TEB_DevelopmentBoard.h"
#include <WiFiClientSecure.h>
#include "../strings_and_numbers/TEB_Strings.h"

WiFiClientSecure TEB_DevelopmentBoard_TEB_HTTP_client;

uint8_t TEB_DevelopmentBoard_TEB_HTTP_connection_mode = 0;

char* TEB_DevelopmentBoard_TEB_HTTP_standard_response_reception_algorithm (void* client, char* response_buffer, size_t response_buffer_size, uint16_t response_delay) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_DevelopmentBoard_TEB_HTTP_standard_response_reception_algorithm (void* client, char* response_buffer, size_t response_buffer_size, uint16_t response_delay)"));
#endif
  uint32_t m = millis();
  uint16_t nbit = 256; //nbit > 0 && <= response_buffer_size
  int n;
  while (true) {
    if (response_buffer_size < nbit) nbit = response_buffer_size;
    n = ((WiFiClientSecure*)client)->read((uint8_t*)response_buffer, nbit);
    if (n != -1 && n != 0) {
      response_buffer = response_buffer + n;
      response_buffer_size = response_buffer_size - n;
      if (response_buffer_size == 0) break;
      m = millis();
    }
    else if (m + response_delay < millis()) break;
  }
  return response_buffer;
}

int8_t TEB_DevelopmentBoard::TEB_HTTP::sendRequest (request& httpRequest, response& httpResponse, char* responseBuffer, size_t responseBufferSize) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_DevelopmentBoard::TEB_HTTP::sendRequest (request& httpRequest, response& httpResponse, char* responseBuffer, size_t responseBufferSize)"));
#endif
  return sendRequest(httpRequest, httpResponse, responseBuffer, responseBufferSize, TEB_DevelopmentBoard_TEB_HTTP_standard_response_reception_algorithm);
}

int8_t TEB_DevelopmentBoard::TEB_HTTP::sendRequest (request& httpRequest, response& httpResponse, char* responseBuffer, size_t responseBufferSize, char* (*responseReceptionAlgorithm) (void* client, char* responseBuffer, size_t responseBufferSize, uint16_t responseDelay)) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_DevelopmentBoard::TEB_HTTP::sendRequest (request& httpRequest, response& httpResponse, char* responseBuffer, size_t responseBufferSize, char* (*responseReceptionAlgorithm) (void* client, char* responseBuffer, size_t responseBufferSize, uint16_t responseDelay))"));
  if (httpRequest.requestText == NULL) TEB_DevelopmentBoard::TEB_Debug::fatalError(141, F("httpRequest.requestText cannot be NULL."));
  if (httpRequest.serverAddress == NULL) TEB_DevelopmentBoard::TEB_Debug::fatalError(142, F("httpRequest.serverAddress cannot be NULL."));
  if (responseBuffer == NULL) TEB_DevelopmentBoard::TEB_Debug::fatalError(143, F("responseBuffer cannot be NULL."));
  if (responseBufferSize == 0) TEB_DevelopmentBoard::TEB_Debug::fatalError(144, F("responseBufferSize must be >= 1."));
  if (responseReceptionAlgorithm == NULL) TEB_DevelopmentBoard::TEB_Debug::fatalError(145, F("responseReceptionAlgorithm cannot be NULL."));
  TEB_DevelopmentBoard::TEB_Debug::print(F("\nTry to connect to "));
  TEB_DevelopmentBoard::TEB_Debug::print(httpRequest.serverAddress);
  TEB_DevelopmentBoard::TEB_Debug::print(F(" and send the request:\n"));
  const char* b1 = httpRequest.requestText;
  while (*b1 != '\0') {
    if (*b1 == '\r') TEB_DevelopmentBoard::TEB_Debug::print(F("\\r"));
    else if (*b1 == '\n') TEB_DevelopmentBoard::TEB_Debug::print(F("\\n\n"));
    else {
      TEB_DevelopmentBoard::TEB_Debug::print(*b1);
    }
    b1++;
  }
  TEB_DevelopmentBoard::TEB_Debug::print(F("\n- END REQUEST -\n"));
#endif
  if (strlen(httpRequest.rootCA) != 0) {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::print(F("\nSet the rootCA:\n"));
    TEB_DevelopmentBoard::TEB_Debug::print(httpRequest.rootCA);
    TEB_DevelopmentBoard::TEB_Debug::print(F("- END ROOTCA -\n"));
#endif
    TEB_DevelopmentBoard_TEB_HTTP_client.setCACert(httpRequest.rootCA);
  }
  else {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::print(F("\nrootCA not set."));
#endif
    TEB_DevelopmentBoard_TEB_HTTP_client.setInsecure();//skip verification
  }
  if (WiFi.status() != WL_CONNECTED) {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::error(6, F("Sending HTTP request failed due to no Internet connection."));
#endif
    TEB_DevelopmentBoard_TEB_HTTP_client.stop();
    return -1;
  }
  if (!TEB_DevelopmentBoard_TEB_HTTP_client.connect(httpRequest.serverAddress, httpRequest.serverPort, httpRequest.connectionTimeout)) {
    TEB_DevelopmentBoard_TEB_HTTP_client.stop();
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::error(7, F("Sending HTTP request failed. Unable to connect to the server."));
#endif
    return -2;
  }
  TEB_DevelopmentBoard_TEB_HTTP_client.print(httpRequest.requestText);
  httpResponse.header = responseBuffer;
  responseBuffer = (*responseReceptionAlgorithm)(&TEB_DevelopmentBoard_TEB_HTTP_client, httpResponse.header, responseBufferSize, httpRequest.responseDelay);
  httpResponse.payload = (char*)TEB_Strings::indexOf(httpResponse.header, responseBuffer, "\r\n\r\n");
  size_t i3;
  if (httpResponse.payload == 0) {
    httpResponse.headerLength = responseBuffer - httpResponse.header;
    httpResponse.payload = 0;
    httpResponse.payloadLength = 0;
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::print(F("\n\\r\\n\\r\\n was not found at the end of the header. The entire HTTP response was saved in httpResponse.header.\nThe response received ("));
    TEB_DevelopmentBoard::TEB_Debug::print(httpResponse.headerLength);
    TEB_DevelopmentBoard::TEB_Debug::print(F(" bytes long) is:\n"));
    i3 = 0;
    while (i3 < httpResponse.headerLength) {
      if (httpResponse.header[i3] == '\r') TEB_DevelopmentBoard::TEB_Debug::print(F("\\r"));
      else if (httpResponse.header[i3] == '\n') TEB_DevelopmentBoard::TEB_Debug::print(F("\\n\n"));
      else {
        TEB_DevelopmentBoard::TEB_Debug::print(httpResponse.header[i3]);
      }
      i3++;
    }
    TEB_DevelopmentBoard::TEB_Debug::print(F("\n- RESPONSE END -\n"));
#endif
    TEB_DevelopmentBoard_TEB_HTTP_client.stop();
    return 2;
  }
  httpResponse.headerLength = httpResponse.payload - httpResponse.header;
  httpResponse.payload = httpResponse.payload + 4;
  httpResponse.payloadLength = responseBuffer - httpResponse.payload;
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug::print(F("\nThe response header detected ("));
  TEB_DevelopmentBoard::TEB_Debug::print(httpResponse.headerLength);
  TEB_DevelopmentBoard::TEB_Debug::print(F(" bytes long) is:\n"));
  i3 = 0;
  while (i3 < httpResponse.headerLength) {
    if (httpResponse.header[i3] == '\r') TEB_DevelopmentBoard::TEB_Debug::print(F("\\r"));
    else if (httpResponse.header[i3] == '\n') TEB_DevelopmentBoard::TEB_Debug::print(F("\\n\n"));
    else {
      TEB_DevelopmentBoard::TEB_Debug::print(httpResponse.header[i3]);
    }
    i3++;
  }
  TEB_DevelopmentBoard::TEB_Debug::print(F("\n- HEADER END -\n"));
  if (httpResponse.payloadLength == 0) TEB_DevelopmentBoard::TEB_Debug::print(F("\nNo response payload detected.\n"));
  else {
    TEB_DevelopmentBoard::TEB_Debug::print(F("\nThe response payload detected ("));
    TEB_DevelopmentBoard::TEB_Debug::print(httpResponse.payloadLength);
    TEB_DevelopmentBoard::TEB_Debug::print(F(" bytes long) is:\n"));
    i3 = 0;
    while (i3 < httpResponse.payloadLength) {
      if (httpResponse.payload[i3] == '\r') TEB_DevelopmentBoard::TEB_Debug::print(F("\\r"));
      else if (httpResponse.payload[i3] == '\n') TEB_DevelopmentBoard::TEB_Debug::print(F("\\n\n"));
      else {
        TEB_DevelopmentBoard::TEB_Debug::print(httpResponse.payload[i3]);
      }
      i3++;
    }
    TEB_DevelopmentBoard::TEB_Debug::print(F("\n- PAYLOAD END -\n"));
  }
#endif
  TEB_DevelopmentBoard_TEB_HTTP_client.stop();
  return 1;
}

int8_t TEB_DevelopmentBoard::TEB_HTTP::connect (const char* serverAddress, uint16_t serverPort, const char* rootCA, uint16_t connectionTimeout) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_DevelopmentBoard::TEB_HTTP::connect (const char* serverAddress, uint16_t serverPort, const char* rootCA, uint16_t connectionTimeout)"));
  if (serverAddress == NULL) TEB_DevelopmentBoard::TEB_Debug::fatalError(146, F("serverAddress cannot be NULL."));
#endif
  if (TEB_DevelopmentBoard_TEB_HTTP_connection_mode != 0) {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::error(8, "Before you can reuse this function you need to run TEB_HTTP::stop.");
#endif
    return -1;
  }
  if (strlen(rootCA) != 0) {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::print(F("\nSet the rootCA:\n"));
    TEB_DevelopmentBoard::TEB_Debug::print(rootCA);
    TEB_DevelopmentBoard::TEB_Debug::print(F("- END ROOTCA -\n"));
#endif
    TEB_DevelopmentBoard_TEB_HTTP_client.setCACert(rootCA);
  }
  else {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::print(F("\nrootCA not set."));
#endif
    TEB_DevelopmentBoard_TEB_HTTP_client.setInsecure();//skip verification
  }
  if (WiFi.status() != WL_CONNECTED) {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::error(9, F("Connection to server failed due to no Internet connection."));
#endif
    TEB_DevelopmentBoard_TEB_HTTP_client.stop();
    return -2;
  }
  if (!TEB_DevelopmentBoard_TEB_HTTP_client.connect(serverAddress, serverPort, connectionTimeout)) {
    TEB_DevelopmentBoard_TEB_HTTP_client.stop();
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::error(10, F("Connection to server failed."));
#endif
    return -3;
  }
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug::print(F("\nConnected to "));
  TEB_DevelopmentBoard::TEB_Debug::print(serverAddress);
  TEB_DevelopmentBoard::TEB_Debug::print(F(" via port "));
  TEB_DevelopmentBoard::TEB_Debug::print(serverPort);
  TEB_DevelopmentBoard::TEB_Debug::print(F(".\n"));
#endif
  TEB_DevelopmentBoard_TEB_HTTP_connection_mode = 1;
  return 1;
}

int8_t TEB_DevelopmentBoard::TEB_HTTP::send (const char* requestText, size_t requestTextLength) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_DevelopmentBoard::TEB_HTTP::send (const char* requestText, size_t requestTextLength)"));
  if (requestText == NULL) TEB_DevelopmentBoard::TEB_Debug::fatalError(147, F("requestText cannot be NULL."));
  if (requestTextLength == 0) TEB_DevelopmentBoard::TEB_Debug::fatalError(148, F("requestTextLength cannot be 0."));
#endif
  if (TEB_DevelopmentBoard_TEB_HTTP_connection_mode != 1 && TEB_DevelopmentBoard_TEB_HTTP_connection_mode != 2) {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::error(11, F("Before using this function you need to connect to a server using TEB_HTTP::connect."));
#endif
    return -1;
  }
  size_t res;
  uint8_t err = 0;
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug::print(F("\nSending: "));
#endif
  while (true) {
    res = TEB_DevelopmentBoard_TEB_HTTP_client.write((const uint8_t*)requestText, requestTextLength);
#ifdef TEB_DB_DEBUG
    size_t i = 0;
    while (i < res) {
      if (requestText[i] == '\n') TEB_DevelopmentBoard::TEB_Debug::print(F("\\n"));
      else if (requestText[i] == '\r') TEB_DevelopmentBoard::TEB_Debug::print(F("\\r"));
      else {
        TEB_DevelopmentBoard::TEB_Debug::print(requestText[i]);
      }
      i++;
    }
    TEB_DevelopmentBoard::TEB_Debug::print(F("\n"));
#endif
    if (res == requestTextLength) break;
    if (res == 0) {
      err++;
      if (err == 5) {
        TEB_DevelopmentBoard_TEB_HTTP_client.stop();
        TEB_DevelopmentBoard_TEB_HTTP_connection_mode = 0;
#ifdef TEB_DB_DEBUG
        TEB_DevelopmentBoard::TEB_Debug::error(12, F("HTTP request sending failed. The server has been disconnected."));
#endif
        return -2;
      }
    }
    else {
      requestText = requestText + res;
      requestTextLength = requestTextLength - res;
      err = 0;
    }
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::fatalError(149, F("Unexpected fatal error."));
#endif
  }
  TEB_DevelopmentBoard_TEB_HTTP_connection_mode = 2;
  return 1;
}

int TEB_DevelopmentBoard::TEB_HTTP::receive (const char* responseBuffer, size_t bufferSize) {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_DevelopmentBoard::TEB_HTTP::receive (const char* responseBuffer, size_t bufferSize)"));
  if (responseBuffer == NULL) TEB_DevelopmentBoard::TEB_Debug::fatalError(150, F("responseBuffer cannot be NULL."));
  if (bufferSize == 0) TEB_DevelopmentBoard::TEB_Debug::fatalError(151, F("bufferSize cannot be 0."));
#endif
  int r;
  if (TEB_DevelopmentBoard_TEB_HTTP_connection_mode != 1 && TEB_DevelopmentBoard_TEB_HTTP_connection_mode != 2) {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::error(13, F("Before using this function you must at least connect to a server using TEB_HTTP::connect."));
#endif
    return -1;
  }
  else {
    r = TEB_DevelopmentBoard_TEB_HTTP_client.read((uint8_t*)responseBuffer, bufferSize);
    if (r == -1) return 0;
    else {
#ifdef TEB_DB_DEBUG
      TEB_DevelopmentBoard::TEB_Debug::print(F("\nReceived: "));
      int i = 0;
      while (i < r) {
        if (responseBuffer[i] == '\r') TEB_DevelopmentBoard::TEB_Debug::print(F("\\r"));
        else if (responseBuffer[i] == '\n') TEB_DevelopmentBoard::TEB_Debug::print(F("\\n"));
        else {
          TEB_DevelopmentBoard::TEB_Debug::print(responseBuffer[i]);
        }
        i++;
      }
      TEB_DevelopmentBoard::TEB_Debug::print(F("\n"));
#endif
      return r;
    }
  }
}

void TEB_DevelopmentBoard::TEB_HTTP::stop () {
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_DevelopmentBoard::TEB_HTTP::stop ()"));
#endif
  if (TEB_DevelopmentBoard_TEB_HTTP_connection_mode != 1 && TEB_DevelopmentBoard_TEB_HTTP_connection_mode != 2) {
#ifdef TEB_DB_DEBUG
    TEB_DevelopmentBoard::TEB_Debug::error(14, F("Before using this function you need to execute TEB_HTTP::connect, TEB_HTTP::send and/or TEB_HTTP::receive."));
#endif
    return;
  }
  TEB_DevelopmentBoard_TEB_HTTP_client.stop();
  TEB_DevelopmentBoard_TEB_HTTP_connection_mode = 0;
#ifdef TEB_DB_DEBUG
  TEB_DevelopmentBoard::TEB_Debug::print(F("\nConnection with server closed.\n"));
#endif
}

#ifdef TEB_DB_DEBUG
void TEB_DevelopmentBoard::TEB_HTTP::test (const char* ssid, const char* password, uint32_t timeOut) {
  TEB_DevelopmentBoard::TEB_Debug tebdb = TEB_DevelopmentBoard::TEB_Debug(F("TEB_DevelopmentBoard::TEB_HTTP::test (const char* ssid, const char* password, uint32_t timeOut)"));
  TEB_DevelopmentBoard::TEB_Debug::print(TEB_Library_global_string_for_debugging1);
  TEB_DevelopmentBoard::TEB_Debug::print(F("TEB_DevelopmentBoard::TEB_HTTP"));
  TEB_DevelopmentBoard::TEB_Debug::print(TEB_Library_global_string_for_debugging2);
  TEB_DevelopmentBoard::TEB_Debug::print(F("\nFirst method (less efficient but easier to handle long HTTP messages).\n\n"));
  if (TEB_DevelopmentBoard::TEB_WiFi::check() != 1) {
    if (TEB_DevelopmentBoard::TEB_WiFi::connect(ssid, password, timeOut) != 1) {
      TEB_DevelopmentBoard::TEB_Debug::print(F("\nCannot connect to the Internet. End of the test.\n"));
      return;
    }
  }
  TEB_DevelopmentBoard::TEB_HTTP::request httpRequest;
  httpRequest.requestText = "GET https://www.howsmyssl.com/a/check HTTP/1.0\r\nHost: www.howsmyssl.com\r\nConnection: close\r\n\r\n";
  httpRequest.serverAddress = "www.howsmyssl.com";
  httpRequest.serverPort = 443;
  httpRequest.rootCA = "";
  httpRequest.connectionTimeout = 15000;
  httpRequest.responseDelay = 15000;
  TEB_DevelopmentBoard::TEB_HTTP::response httpResponse;
  char responseBuffer[3500];
  if (sendRequest(httpRequest, httpResponse, responseBuffer, 3500) != 1) {
    TEB_DevelopmentBoard::TEB_Debug::print(F("\nProblems with sendRequest. End of the test.\n"));
    return;
  }
  TEB_DevelopmentBoard::TEB_Debug::print(F("\nSecond method (more efficient and more versatile but harder to handle long HTTP messages).\n"));
  if (connect("www.howsmyssl.com", 443, "", 5000) != 1) {
    TEB_DevelopmentBoard::TEB_Debug::print(F("\nProblems with connect. End of the test.\n"));
    return;
  }
  if (send("GET https://www.howsmyssl.com/a/check HTTP/1.0", 46) != 1) {
    TEB_DevelopmentBoard::TEB_Debug::print(F("\nProblems with send. End of the test.\n"));
    return;
  }
  if (send("\r\nHost: www.howsmyssl.com\r\nConnection: close\r\n\r\n", 48) != 1) {
    TEB_DevelopmentBoard::TEB_Debug::print(F("\nProblems with send. End of the test.\n"));
    return;
  }
  char* buf = responseBuffer;
  uint32_t m = millis();
  while (true) {
    int n = receive(buf, 255);
    if (n > 0) {
      buf = buf + n;
      m = millis();
    }
    if (m + 500 < millis()) break;
  }
  *buf = '\0';
  TEB_DevelopmentBoard::TEB_Debug::print(F("\nHTTP response received:\n"));
  TEB_DevelopmentBoard::TEB_Debug::print(responseBuffer);
  TEB_DevelopmentBoard::TEB_Debug::print(F("\n"));
  stop();
  TEB_DevelopmentBoard::TEB_Debug::print(TEB_Library_global_string_for_debugging3);
}
#endif
