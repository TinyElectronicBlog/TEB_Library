/*
  MIT License

  Copyright (c) 2024 TinyElectronicBlog

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

#ifndef TEB_OAuth2_h
#define TEB_OAuth2_h

#include "../../TEB_LibrarySettings.h"
#include "../DeviceInterfaces/TEB_DeviceInterfaces.h"

/**
    \brief The functions in this file allow to perform OAuth 2.0 authentication to access Google APIs, as explained in the guide https://developers.google.com/identity/protocols/oauth2/limited-input-device.
*/

/**
    \brief Struc used to handle Google server http responses.
*/
struct TEB_OAuth2_http_response_property {
  TEB_char* property;
  TEB_size_t property_length;
  TEB_medium_u_int status_code;
};

/**
        \brief Performs steps 1 - 6 to obtain an access token. See https://developers.google.com/identity/protocols/oauth2/limited-input-device for more information.
        \param [in] access_token_buffer Buffer in which to save the access token.
	\param [in] refresh_token_buffer Buffer in which to save the refresh token.
	\param [in] scope Scope for which permission is requested.		
	\param [in] function_buffer Buffer needed by the function to execute its instructions. It must be at least TEB_OAuth2_SPLITTABLE_BUFFER_SIZE_FOR_LOGIN (see TEB_LibrarySettings.h) elements long. If the value NULL is set, the function dynamically allocates a temporary buffer.  
	\param oauth2_step3_display_user_code Function to display the user code of step 3. 
        \return 1 on success, 2 if permission is denied by the user, a negative value in case of an error.
    */
TEB_small_int TEB_OAuth2_login (TEB_char* access_token_buffer,
                               TEB_char* refresh_token_buffer,
                               const TEB_char* scope,
                               TEB_char* function_buffer,
                               TEB_small_int (*oauth2_step3_display_user_code)(const TEB_char* text));

/**
         \brief Performs "Refreshing an access token" step to obtain an access token. See https://developers.google.com/identity/protocols/oauth2/limited-input-device#offline for more information.
         \param [in] refresh_token The refresh token to be used for step 7. Must end with \0.
	 \param [in] access_token_buffer Buffer in which to save the access token.
         \param [in] function_buffer Buffer needed by the function to execute its instructions. It must be at least TEB_OAuth2_SPLITTABLE_BUFFER_SIZE_FOR_RELOGIN (see TEB_LibrarySettings.h) elements long. If the value NULL is set, the function dynamically allocates a temporary buffer. 
         \return 1 on success, a negative value in case of an error.
    */
TEB_small_int TEB_OAuth2_relogin (const TEB_char* refresh_token,
                                 TEB_char* access_token_buffer,
                                 TEB_char* function_buffer);

/**
        \brief Performs "Revoking a token" step to revoke an access token. See https://developers.google.com/identity/protocols/oauth2/limited-input-device#tokenrevoke for more information.
        \param [in] token A refresh token or an access token.
	\param [in] function_buffer Buffer needed by the function to execute its instructions. It must be at least TEB_OAuth2_SPLITTABLE_BUFFER_SIZE_FOR_LOGOUT (see TEB_LibrarySettings.h) elements long. If the value NULL is set, the function dynamically allocates a temporary buffer. 
        \return 1 on success, a negative value in case of an error.
    */
TEB_small_int TEB_OAuth2_logout (const TEB_char* token, TEB_char* function_buffer);

/**
       \brief Algorithm for receiving an HTTP response used in TEB_OAuth2.
    */
TEB_char* TEB_OAuth2_response_reception_algorithm (TEB_char* response_buffer,
                                                  TEB_size_t response_buffer_length,
                                                  TEB_time_t response_delay_in_ms,
                                                  void* additional_parameters,
												  TEB_medium_u_int mode);

/**
       \brief Algorithm for processing an HTTP response used in TEB_OAuth2.
    */
TEB_small_int TEB_OAuth2_handle_server_response (struct TEB_http_response* http_response,
                                                struct TEB_OAuth2_http_response_property* http_response_property,
                                                TEB_char* function_buffer);

/**
        \brief Standard function to display the user code of step 3. 
	\param [in] text Text to display.
        \return 1 on success, a negative value in case of an error.
    */
TEB_small_int TEB_OAuth2_standard_oauth2_step3_display_user_code (const TEB_char* text);

#ifdef TEB_LibrarySettings_DEBUG_MODE
TEB_small_int TEB_OAuth2_test1 (TEB_char* access_token_buffer);
TEB_small_int TEB_OAuth2_test2 (const TEB_char* access_token);
#endif

struct TEB_OAuth2_rename_f {
  TEB_small_int (*login)(TEB_char*, TEB_char*, const TEB_char*, TEB_char*, TEB_small_int (*oauth2_step3_display_user_code)(const TEB_char*));
  TEB_small_int (*relogin)(const TEB_char*, TEB_char*, TEB_char*);
  TEB_small_int (*logout)(const TEB_char*, TEB_char*);
  TEB_char* (*responseReceptionAlgorithm)(TEB_char*, TEB_size_t, TEB_time_t, void*, TEB_medium_u_int);
  TEB_small_int (*handleServerResponse)(struct TEB_http_response*, struct TEB_OAuth2_http_response_property*, TEB_char*);
  TEB_small_int (*standardStep3ShowUserCode)(const TEB_char*);
};

#endif
