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

#ifndef TEB_OAuth2_h
#define TEB_OAuth2_h

#include "../strings_and_numbers/TEB_Numbers.h"

/**
    \class TEB_OAuth2
    \brief This class allows to perform OAuth 2.0 authentication to access Google APIs, as explained in the guide https://developers.google.com/identity/protocols/oauth2/limited-input-device.
*/
class TEB_OAuth2
{
  private:

    friend class TEB_Drive;

    struct http_response_property {
      char* property;
      size_t property_length;
      uint16_t status_code;
    };

    static const char oauth2_api_key[];
    static const char oauth2_client_id[];
    static const char oauth2_client_secret[];
    static const uint16_t oauth2_server_port;
    static const char oauth2_root_ca[];

    static const char* temp_p;
    static char* imported_array;
    static TEB_Splittable_Array* splittable_buffer;

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
    static const char str21[];
    static const char str22[];
    static const char str23[];
#ifdef TEB_DB_DEBUG
    static const char debug1[];
    static const char debug2[];
    static const char debug3[];
#endif

    static void initialize_http_request (TEB_DevelopmentBoard::TEB_HTTP::request& http_request);
    static void generate_step1_request_text ();
    static void generate_step4_request_text ();
    static void generate_step7_request_text ();
    static void generate_step8_request_text ();

    static const char* generate_http_request_text (uint8_t step_number);

    static int8_t step1_2_3_4_5 (TEB_DevelopmentBoard::TEB_HTTP::request& http_request, TEB_DevelopmentBoard::TEB_HTTP::response& http_response, void (*step3_display_user_code) (const char* text));
    static int8_t step6 (TEB_DevelopmentBoard::TEB_HTTP::response& http_response, char* access_token_buffer, char* refresh_token_buffer, bool save_refresh_token);
    static int8_t refresh_access_token (TEB_DevelopmentBoard::TEB_HTTP::request& http_request, TEB_DevelopmentBoard::TEB_HTTP::response& http_response);
    static int8_t revoke_token (TEB_DevelopmentBoard::TEB_HTTP::request& http_request, TEB_DevelopmentBoard::TEB_HTTP::response& http_response);

    static int8_t handle_server_response (TEB_DevelopmentBoard::TEB_HTTP::response& http_response, http_response_property& http_response_property);
    static char* response_reception_algorithm (void* client, char* response_buffer, size_t response_buffer_size, uint16_t response_delay);

    static int8_t allocate_splittable_buffer (size_t size);
    static int8_t deallocate_splittable_buffer ();

    static int16_t refresh_token_eeprom_length ();
    static int8_t get_refresh_token_eeprom (char* refresh_token_buffer);
    static int8_t set_refresh_token_eeprom (const char* refresh_token);

    static int8_t login_ (const char* scope, char* access_token_buffer, char* refresh_token_buffer, bool save_refresh_token, void (*step3_display_user_code) (const char* text));
    static int8_t relogin_ (char* access_token_buffer, const char* refresh_token, bool save_refresh_token);
    static int8_t logout_ ();

  public:

    /**
       \brief Indicate to TEB_OAuth2 to use a dynamically allocated buffer. Is the deafult buffer.
    */
    static void useDynamicBuffer ();

    /**
       \brief Indicates to TEB_OAuth2 to use a buffer external to the class.
       \param [in] buffer Buffer to use.
       \details See the minimum buffer sizes in the TEB_Library.h file.
    */
    static void useImportedBuffer (char* buffer);

    /**
        \brief Performs steps 1 - 6 to obtain an access token. See https://developers.google.com/identity/protocols/oauth2/limited-input-device for more information.
        \param [in] scope Scope for which permission is requested.
        \param [in] accessTokenBuffer Buffer in which to save the access token.
        \param [in] saveRefreshToken If true the refresh token is saved in EEPROM.
        \param [in] step3DisplayUserCode Function to display information about step 3.
        \return 1 on success, 2 if permission is denied by the user, a negative value in case of an error.
    */
    static int8_t login (const char* scope, char* accessTokenBuffer, bool saveRefreshToken, void (*step3DisplayUserCode) (const char* text));

    /**
        \brief Performs steps 1 - 6 to obtain an access token. See https://developers.google.com/identity/protocols/oauth2/limited-input-device for more information.
        \param [in] scope Scope for which permission is requested.
        \param [in] accessTokenBuffer Buffer in which to save the access token.
        \param [in] refreshTokenBuffer Buffer in which to save the refresh token.
        \param [in] saveRefreshToken If true the refresh token is saved in EEPROM.
        \param [in] step3DisplayUserCode Function to display information about step 3.
        \return 1 on success, 2 if permission is denied by the user, a negative value in case of an error.
    */
    static int8_t login (const char* scope, char* accessTokenBuffer, char* refreshTokenBuffer, bool saveRefreshToken, void (*step3DisplayUserCode) (const char* text));

    /**
         \brief Performs step 7 to obtain an access token with the refresh token saved in EEPROM. See https://developers.google.com/identity/protocols/oauth2/limited-input-device for more information.
         \param [in] accessTokenBuffer Buffer in which to save the access token.
         \return 1 on success, a negative value in case of an error.
    */
    static int8_t relogin (char* accessTokenBuffer);

    /**
         \brief Performs "Refreshing an access token" step to obtain an access token. See https://developers.google.com/identity/protocols/oauth2/limited-input-device#offline for more information.
         \param [in] accessTokenBuffer Buffer in which to save the access token.
         \param [in] refreshToken The refresh token to be used for step 7. Must end with \0.
         \param [in] saveRefreshToken If true the refresh token is saved in EEPROM.
         \return 1 on success, a negative value in case of an error.
    */
    static int8_t relogin (char* accessTokenBuffer, const char* refreshToken, bool saveRefreshToken);

    /**
        \brief Performs "Revoking a token" step to obtain an access token. See https://developers.google.com/identity/protocols/oauth2/limited-input-device#tokenrevoke for more information.
        \param [in] token A refresh token or an access token.
        \return 1 on success, a negative value in case of an error.
    */
    static int8_t logout (const char* token);

    /**
       \return true if a refresh token is stored in EEPROM.
    */
    static bool refreshTokenEEPROM ();

    /**
       \brief Saves the refresh token contained in EEPROM in refreshTokenBuffer. The token ends with \0 and the sum of the first two bytes is equal to its length.
       \param [in] refreshTokenBuffer The buffer in which to save the refresh token.
       \return A pointer to refreshTokenBuffer without the initial 2 bytes, otherwise NULL if the refresh token is not present in EEPROM.
    */
    static char* getRefreshTokenEEPROM (char* refreshTokenBuffer);

    /**
       \brief Removes the refresh token from the EEPROM.
       \return 1 on success, a negative value in case of an error.
    */
    static int8_t deleteRefreshTokenEEPROM ();

#ifdef TEB_DB_DEBUG
  public:
    static void s3PrintText (const char* t);
      
    static void test (const char* ssid, const char* password, uint32_t timeOut);
#endif

};

#endif
