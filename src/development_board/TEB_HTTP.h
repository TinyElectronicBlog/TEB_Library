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

#ifndef TEB_HTTP_h
#define TEB_HTTP_h

#include "../TEB_Configurations.h"
#include <Arduino.h>

/**
   \class TEB_HTTP
   \brief This class contains methods to send request and receive http response. sendRequest is an independent function while connect, send, receive and stop are used together. sendRequest is less efficient but makes it easier to handle long HTTP requests and responses.
*/
class TEB_HTTP {

  public:

    /**
       \brief HTTP request data type used in sendRequest. All fields must be initialized. connectionTimeout and responseDelay are in ms. If rootCA == "" is not evaluated.
    */
    struct request {
      const char* requestText;
      const char* serverAddress;
      uint16_t serverPort;
      const char* rootCA;
      uint16_t connectionTimeout;
      uint16_t responseDelay;
    };

    /**
       \brief HTTP response data type used in sendRequest. The fields do not need to be initialized.
    */
    struct response {
      char* header;
      size_t headerLength;
      char* payload;
      size_t payloadLength;
    };

    /**
       \brief It sends an HTTP request and receives the relative response.
       \param [in] httpRequest The HTTP request.
       \param [in] httpResponse TThe HTTP response.
       \param [in] responseBuffer Buffer in which to save the response.
       \param [in] responseBufferSize Buffer length.
       \return 1 if ok, 2 if "\n\r\n\r" was not found at the end of the HTTP response header.
       \details if return 2 the whole http response is saved in httpResponse.header. All fields of httpRequest must be initialized. If the HTTP response is longer than responseBufferSize it is truncated. If httpRequest.rootCA = "" the rootCA of httpRequest.serverAddress is not considered. The char* fields of httpResponse do not end with \0 while those of httpRequest do. httpResponse contains pointers to responseBuffer.
    */
    static int8_t sendRequest (request& httpRequest, response& httpResponse, char* responseBuffer, size_t responseBufferSize);

    /**
       \brief It sends an HTTP request and receives the relative response.
       \param [in] httpRequest The HTTP request.
       \param [in] httpResponse The HTTP response.
       \param [in] responseBuffer Buffer in which to save the response.
       \param [in] responseBufferSize Buffer length.
       \param [in] responseReceptionAlgorithm Custom algorithm for receiving the HTTP response.
       \return 1 if ok, 2 if "\n\r\n\r" was not found at the end of the HTTP response header.
       \details if return 2 the whole http response is saved in httpResponse.header. All fields of httpRequest must be initialized. If the HTTP response is longer than responseBufferSize it is truncated. If httpRequest.rootCA = "" the rootCA of httpRequest.serverAddress is not considered. The char* fields of httpResponse do not end with \0 while those of httpRequest do. httpResponse contains pointers to responseBuffer.
    */
    static int8_t sendRequest (request& httpRequest, response& httpResponse, char* responseBuffer, size_t responseBufferSize, char* (*responseReceptionAlgorithm) (void* client, char* responseBuffer, size_t responseBufferSize, uint16_t responseDelay));

    /**
       \brief Connect to a server.
       \param [in] serverAddress Server Address.
       \param [in] serverPort Server port.
       \param [in] rootCA If "" the rootCA of serverAddress is not considered.
       \param [in] connectionTimeout ms within which the connection must take place.
       \return 1 if ok.
       \details It can only be re-executed after the stop function or after a connect, send or receive failure.
    */
    static int8_t connect (const char* serverAddress, uint16_t serverPort, const char* rootCA, uint16_t connectionTimeout);

    /**
       \brief Sends an HTTP request.
       \param [in] requestText Request text.
       \param [in] requestTextLength Length of request.
       \return 1 if ok.
       \details If the send fails you must start over with connect. It can be executed after connect or another send.
    */
    static int8_t send (const char* requestText, size_t requestTextLength);

    /**
       \brief Receive an HTTP response.
       \param [in] responseBuffer Buffer in which to save the response.
       \param [in] requestTextLength Length of buffer.
       \return The number of characters saved in responseBuffer, otherwise a negative value.
       \details If it doesn't read anything return 0 (in this case it is recommended to repeat the reading several times to be sure to have received all the data). It can be executed after connect, send or another receive.
    */
    static int receive (const char* responseBuffer, size_t bufferSize);

    /**
       \brief Closes the connection with the server.
       \details It can be executed after connect, send or receive.
    */
    static void stop ();

#ifdef TEB_DB_DEBUG
    static void test (const char* ssid, const char* password, uint32_t timeOut);
#endif

};

#endif