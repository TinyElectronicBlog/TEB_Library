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

  This class is based on the guide https://developers.google.com/drive/api/v3/reference.
*/

#ifndef TEB_Drive_h
#define TEB_Drive_h

#include "TEB_OAuth2.h"
#include "../strings_and_numbers/TEB_Strings.h"

/**
    \class TEB_Drive
    \brief This class has methods for basic file management on Google Drive. For more information see https://developers.google.com/drive/api/v3/reference. This class requires an access token which can be obtained with TEB_OAuth2 class. Attention, some input parameters of the functions must be provided URL encoded; to know which ones precisely (the information in this file may be inaccurate), you can help yourself with the "Try this method" function present in the online Google documentation of a method (e.g. https://developers.google.com/drive/api/v3/reference/about/get).
*/
class TEB_Drive
{
  private:

    static uint16_t temp_i1;
    static uint8_t temp_i2;
    static const char* temp_p1;
    static const char* temp_p2;
    static const char* temp_p3;
    static const char* temp_p4;
    static const char* temp_p5;

    static const char str1[];
    static const char str2[];
    static const char str3[];
    static const char str4[];
    static const char str5[];
    static const char str6[];
    static const char str7[];
    static const char str8[];
    static const char str9[];
    static const char str10[];
    static const char str11[];
    static const char str12[];
    static const char str13[];
    static const char str14[];
    static const char str15[];
    static const char str16[];
    static const char str17[];
    static const char str18[];
    static const char str19[];
    static const char str20[];
#ifdef TEB_DB_DEBUG
    static const char debug1[];
#endif

    static void initialize_http_request (TEB_DevelopmentBoard::TEB_HTTP::request& http_request);

    static const char* generate_http_request_text (uint8_t type);

    static int8_t execute_http_request (uint8_t type, char* buffer1);

    static char* response_reception_algorithm (void* client, char* response_buffer, size_t response_buffer_size, uint16_t response_delay);

  public:

    /**
       \brief Indicate to TEB_Drive to use a dynamically allocated buffer. Is the deafult buffer.
    */
    static void useDynamicBuffer ();

    /**
       \brief Indicates to TEB_Drive to use a buffer external to the class.
       \param [in] buffer Buffer to use.
       \details See the minimum buffer sizes in the TEB_Library.h file.
    */
    static void useImportedBuffer (char* buffer);

    /**
       \brief Sets the access token to be used with the methods of this class.
       \param [in] accessToken The access token to use.
    */
    static void setAccessToken (const char* accessToken);

    /**
       \brief Creates a new file.
       \param [in] name File name. It cannot be NULL.
       \param [in] parents The ID of the parent folder (insert one only).
       \param [in] mimeType The MIME type of the file.
       \param [in] responseBuffer Buffer in which the ID of the created file is saved. It cannot be NULL.
       \return 1 on success, otherwise a negative value.
       \details parents and mimeType are optional parameters. For more information see https://developers.google.com/drive/api/v3/reference/files/create.
    */
    static int8_t createMetadataOnlyFile (const char* name, const char* parents, const char* mimeType, char* responseBuffer);

    /**
       \brief Updates a file's metadata to rename or move a file.
       \param [in] fileID It cannot be NULL.
       \param [in] fileName The new file name.
       \param [in] addParents The ID of the new parent folder (insert one only) where to move the file.
       \param [in] removeParents The ID of the old parent folder (insert one only).
       \return 1 on success, otherwise a negative value.
       \details fileName, addParents and removeParents are optional parameters. For more information see https://developers.google.com/drive/api/v3/reference/files/update.
    */
    static int8_t updateFileMetadata (const char* fileID, const char* fileName, const char* addParents, const char* removeParents);

    /**
       \brief Updates a file's content.
       \param [in] fileID It cannot be NULL.
       \param [in] fileContent The new file content. It cannot be NULL.
       \param [in] mimeType The new MIME type of the file. It cannot be NULL.
       \return 1 on success, otherwise a negative value.
       \details For more information see https://developers.google.com/drive/api/v3/reference/files/update.
    */
    static int8_t updateFileContent (const char* fileID, const char* fileContent, const char* mimeType);

    /**
       \brief Searches files.
       \param [in] q A query for filtering the results.
       \param [in] orderBy A list of sort keys.
       \param [in] fields The paths of the fields you want included in the response.
       \param [in] pageSize The maximum number of files to return per page. Enter 0 to set the default value.
       \param [in] pageToken The token for continuing a previous request.
       \param [in] responseBuffer Buffer in which the body of the http response is saved. It cannot be NULL.
       \return 1 on success, otherwise a negative value.
       \details q, orderBy, fields, pageSize and pageToken are optional parameters. For more information see https://developers.google.com/drive/api/v3/reference/files/list.
    */
    static int8_t searchFile (const char* q, const char* orderBy, const char* fields, uint16_t pageSize, const char* pageToken, char* responseBuffer);

    /**
       \brief Gets a file's content.
       \param [in] fileID It cannot be NULL.
       \param [in] responseBuffer Buffer in which the contents of the file is saved. It cannot be NULL.
       \return 1 on success, otherwise a negative value.
       \details For more information see https://developers.google.com/drive/api/v3/reference/files/get.
    */
    static int8_t getFileContent (const char* fileID, char* responseBuffer);

    /**
       \brief Permanently deletes a file.
       \param [in] fileID It cannot be NULL.
       \return 1 on success, otherwise a negative value.
       \details For more information see https://developers.google.com/drive/api/v3/reference/files/delete.
    */
    static int8_t deleteFile (const char* fileID);

    /**
       \brief Exports a Google Doc.
       \param [in] fileID It cannot be NULL.
       \param [in] mimeType MIME type export. It cannot be NULL.
       \param [in] responseBuffer Buffer in which the contents of the file is saved. It cannot be NULL.
       \return 1 on success, otherwise a negative value.
       \details For more information see https:developers.google.com/drive/api/v3/reference/files/export.
    */
    static int8_t exportGoogleDocContent (const char* fileID, char* mimeType, char* responseBuffer);

#ifdef TEB_DB_DEBUG
    static void test (const char* ssid, const char* password, uint32_t timeOut);
#endif

};

#endif
