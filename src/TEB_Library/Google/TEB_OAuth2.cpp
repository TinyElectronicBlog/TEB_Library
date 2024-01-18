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

#include "TEB_OAuth2.h"
#include "../buffer/TEB_SplittableArray.h"
#include "../String/TEB_String.h"
#include "../Number/TEB_Number.h"

static const TEB_char TEB_OAuth2_str1[] = "client_id=";
static const TEB_char TEB_OAuth2_str2[] = "_secret=";
static const TEB_char TEB_OAuth2_str3[] = "&scope=";
static const TEB_char TEB_OAuth2_str4[] = "interval";
static const TEB_char TEB_OAuth2_str5[] = "user_";
static const TEB_char TEB_OAuth2_str6[] = "verification_url";
static const TEB_char TEB_OAuth2_str7[] = "code";
static const TEB_char TEB_OAuth2_str8[] = "device";
static const TEB_char TEB_OAuth2_str9[] = "urn:ietf:params:oauth:";
static const TEB_char TEB_OAuth2_str10[] = "/revoke";
static const TEB_char TEB_OAuth2_str11[] = "type=";
static const TEB_char TEB_OAuth2_str12[] = "token";
static const TEB_char TEB_OAuth2_str13[] = "access_";
static const TEB_char TEB_OAuth2_str14[] = "refresh_";
static const TEB_char TEB_OAuth2_str15[] = "POST ";
static const TEB_char TEB_OAuth2_str16[] = " HTTP/1.1\r\nHost: ";
static const TEB_char TEB_OAuth2_str17[] = "oauth2.googleapis.com";
static const TEB_char TEB_OAuth2_str18[] = "\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: ";
static const TEB_char TEB_OAuth2_str19[] = "grant";
static const TEB_char TEB_OAuth2_str20[] = "From another device open the link ";
static const TEB_char TEB_OAuth2_str21[] = " and enter the ";
static const TEB_char TEB_OAuth2_str22[] = "error";

static TEB_small_int TEB_OAuth2_initialize_http_request (struct TEB_http_request* http_request, TEB_size_t splittable_array_index) {
  TEB_debug_function_start("TEB_OAuth2_initialize_http_request");
  //load at the beginning of the buffer all the values except request_text.
  if (TEB_SplittableArray_add_elements(splittable_array_index, TEB_OAuth2_SERVER_ADDRESS, TEB_String_strlen(TEB_OAuth2_SERVER_ADDRESS) + 1) != 1) return TEB_debug_function_end(-1);
  http_request->server_address = (const TEB_char*)TEB_SplittableArray_split_array(splittable_array_index);
  if (TEB_SplittableArray_add_elements(splittable_array_index, TEB_OAuth2_ROOT_CA, TEB_String_strlen(TEB_OAuth2_ROOT_CA) + 1) != 1) return TEB_debug_function_end(-2);
  http_request->root_ca = (const TEB_char*)TEB_SplittableArray_split_array(splittable_array_index);
  http_request->server_port = TEB_OAuth2_SERVER_PORT;
  http_request->connection_timeout_in_ms = TEB_OAuth2_HTTP_REQUEST_CONNECTION_TIMEOUT_IN_MS;
  http_request->response_delay_in_ms = TEB_OAuth2_HTTP_REQUEST_RESPONSE_DELAY_IN_MS;
  http_request->use_ssl = 1;
  return TEB_debug_function_end(1);
}

static TEB_char* TEB_OAuth2_generate_step1_request_text (const TEB_char* scope,
                                                        TEB_char* inv_p) {
  TEB_debug_function_start("TEB_OAuth2_generate_step1_request_text");
  inv_p = TEB_String_append_end2(inv_p, scope, 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, TEB_OAuth2_str3, 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, TEB_OAuth2_CLIENT_ID, 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, TEB_OAuth2_str1, 0) - 1;
  TEB_debug_function_end(0);
  return inv_p;
}

static TEB_char* TEB_OAuth2_generate_step4_request_text (const TEB_char* device_code,
                                                        TEB_char* inv_p) {
  TEB_debug_function_start("TEB_OAuth2_generate_step4_request_text");
  inv_p = TEB_String_append_end2(inv_p, TEB_OAuth2_str7, 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, "_", 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, TEB_OAuth2_str8, 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, ":", 0) - 1;
  inv_p = TEB_String_append_end(inv_p, TEB_OAuth2_str11, TEB_OAuth2_str11 + 4, 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, "-", 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, TEB_OAuth2_str19, 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, TEB_OAuth2_str9, 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, TEB_OAuth2_str11, 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, "_", 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, TEB_OAuth2_str19, 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, "&", 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, device_code, 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, "=", 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, TEB_OAuth2_str7, 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, "_", 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, TEB_OAuth2_str8, 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, "&", 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, TEB_OAuth2_CLIENT_SECRET, 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, TEB_OAuth2_str2, 0) - 1;
  inv_p = TEB_String_append_end(inv_p, TEB_OAuth2_str1, TEB_OAuth2_str1 + 6, 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, "&", 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, TEB_OAuth2_CLIENT_ID, 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, TEB_OAuth2_str1, 0) - 1;
  TEB_debug_function_end(0);
  return inv_p;
}

static TEB_char* TEB_OAuth2_generate_step7_request_text (const TEB_char* refresh_token,
                                                        TEB_char* inv_p) {
  TEB_debug_function_start("TEB_OAuth2_generate_step7_request_text");
  inv_p = TEB_String_append_end2(inv_p, TEB_OAuth2_str12, 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, TEB_OAuth2_str14, 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, TEB_OAuth2_str11, 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, "_", 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, TEB_OAuth2_str19, 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, "&", 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, refresh_token, 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, "=", 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, TEB_OAuth2_str12, 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, TEB_OAuth2_str14, 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, "&", 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, TEB_OAuth2_CLIENT_SECRET, 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, TEB_OAuth2_str2, 0) - 1;
  inv_p = TEB_String_append_end(inv_p, TEB_OAuth2_str1, TEB_OAuth2_str1 + 6, 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, "&", 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, TEB_OAuth2_CLIENT_ID, 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, TEB_OAuth2_str1, 0) - 1;
  TEB_debug_function_end(0);
  return inv_p;
}

static TEB_char* TEB_OAuth2_generate_step8_request_text (const TEB_char* oauth2_token, TEB_char* inv_p) {
  TEB_debug_function_start("TEB_OAuth2_generate_step8_request_text");
  inv_p = TEB_String_append_end2(inv_p, oauth2_token, 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, "=", 0) - 1;
  inv_p = TEB_String_append_end2(inv_p, TEB_OAuth2_str12, 0) - 1;
  TEB_debug_function_end(0);
  return inv_p;
}

static TEB_char* TEB_OAuth2_generate_http_request_text (TEB_small_u_int oauth2_step_number,
                                                       const TEB_char* scope_1_function_buffer_4,
                                                       const TEB_char* device_code_4,
                                                       const TEB_char* refresh_token_7,
                                                       const TEB_char* oauth2_token_8,
                                                       TEB_size_t splittable_array_index,
                                                       TEB_char* function_buffer) {
  TEB_debug_function_start("TEB_OAuth2_generate_http_request_text");
  const TEB_char* t = "\r\n";
  TEB_char* p = function_buffer;
  TEB_char* p_e = p;
  *p = TEB_NULL_CHAR;
  p = p - 1;
  switch (oauth2_step_number) {
    case 1:
      p = TEB_OAuth2_generate_step1_request_text(scope_1_function_buffer_4, p);
      break;
    case 4:
      p = TEB_OAuth2_generate_step4_request_text(device_code_4, p);
      break;
    case 7:
      p = TEB_OAuth2_generate_step7_request_text(refresh_token_7, p);
      break;
    case 8:
      p = TEB_OAuth2_generate_step8_request_text(oauth2_token_8, p);
      break;
  }
  p = TEB_String_append_end2(p, "\r\n\r\n", 0) - 1;
  TEB_String_int_str((p_e - p) - 5, (TEB_char*)TEB_SplittableArray_split_array(splittable_array_index));  //temporary buffer to convert number to string
  p = TEB_String_append_end2(p, (TEB_char*)TEB_SplittableArray_split_array(splittable_array_index), 0) - 1;
  p = TEB_String_append_end2(p, TEB_OAuth2_str18, 0) - 1;
  p = TEB_String_append_end2(p, TEB_OAuth2_str17, 0) - 1;
  p = TEB_String_append_end2(p, TEB_OAuth2_str16, 0) - 1;
  if (oauth2_step_number == 7) oauth2_step_number = 4;
  switch (oauth2_step_number) {
    case 1:
      p = TEB_String_append_end2(p, TEB_OAuth2_str7, 0) - 1;
      p = TEB_String_append_end2(p, "/", 0) - 1;
      p = TEB_String_append_end2(p, TEB_OAuth2_str8, 0) - 1;
      p = TEB_String_append_end2(p, "/", 0) - 1;
      break;
    case 4:
      p = TEB_String_append_end2(p, TEB_OAuth2_str12, 0) - 1;
      p = TEB_String_append_end2(p, "/", 0) - 1;
      break;
    case 8:
      p = TEB_String_append_end2(p, TEB_OAuth2_str10, 0) - 1;
      break;
  }
  p = TEB_String_append_end2(p, TEB_OAuth2_str15, 0);
  TEB_SplittableArray_reset_array(splittable_array_index);
  TEB_debug_function_end(0);
  return p;
}

static TEB_small_int TEB_OAuth2_step1_2_3_4_5 (struct TEB_http_request* http_request,
                                              struct TEB_http_response* http_response,
                                              TEB_char* access_token_buffer,
                                              TEB_char* refresh_token_buffer,
                                              const TEB_char* scope,
                                              TEB_size_t splittable_array_index,
                                              TEB_small_int (*oauth2_step3_display_user_code)(const TEB_char* text)) {
  TEB_debug_function_start("TEB_OAuth2_step1_2_3_4_5");
  if (TEB_OAuth2_initialize_http_request(http_request, splittable_array_index) != 1) {
    return TEB_debug_function_end(-13);
  }
  http_request->request_text = TEB_OAuth2_generate_http_request_text(1, scope, TEB_NULL_POINTER,
                                                                     TEB_NULL_POINTER, TEB_NULL_POINTER,
                                                                     splittable_array_index, (TEB_char*)TEB_SplittableArray_last_element_pointer(splittable_array_index));
  TEB_small_int r = TEB_http_send_request(http_request, http_response,
                                          (TEB_char*)TEB_SplittableArray_split_array(splittable_array_index),
                                          TEB_SplittableArray_number_of_free_elements(splittable_array_index), TEB_OAuth2_response_reception_algorithm,
                                          TEB_NULL_POINTER, 1);
  if (r != 1) {
    return TEB_debug_function_end(-1);
  }
  //Now in splittable_buffer there is only the http response saved temporarily.
  struct TEB_OAuth2_http_response_property http_response_property;
  TEB_char* p = (TEB_char*)TEB_SplittableArray_last_element_pointer(splittable_array_index);
  http_response_property.property = TEB_String_append_end2(p, TEB_OAuth2_str4, 1);
  r = TEB_OAuth2_handle_server_response(http_response, &http_response_property, http_response_property.property - 1);
  if (r != 1) {
    return TEB_debug_function_end(-2);
  }
  TEB_small_u_int interval = TEB_Number_str_int2(http_response_property.property, http_response_property.property + http_response_property.property_length);
  p = TEB_String_append_end2(p, TEB_OAuth2_str7, 1) - 1;
  *p = '_';
  p = p - 1;
  http_response_property.property = TEB_String_append_end2(p, TEB_OAuth2_str8, 0);
  r = TEB_OAuth2_handle_server_response(http_response, &http_response_property, http_response_property.property - 1);
  if (r != 1) {
    return TEB_debug_function_end(-3);
  }
  p = (TEB_char*)TEB_SplittableArray_last_element_pointer(splittable_array_index);
  TEB_char* device_code = TEB_String_append_end(p, http_response_property.property, http_response_property.property + http_response_property.property_length, 1);
  p = TEB_String_append_end2(device_code - 1, TEB_OAuth2_str7, 1) - 1;
  http_response_property.property = TEB_String_append_end2(p, TEB_OAuth2_str5, 0);
  r = TEB_OAuth2_handle_server_response(http_response, &http_response_property, http_response_property.property - 1);
  if (r != 1) {
    return TEB_debug_function_end(-4);
  }
  p = TEB_String_append_end2(device_code - 1, ".", 1) - 1;
  p = TEB_String_append_end(p, http_response_property.property, http_response_property.property + http_response_property.property_length, 0) - 1;
  p = TEB_String_append_end2(p, " ", 0) - 1;
  p = TEB_String_append_end2(p, TEB_OAuth2_str7, 0) - 1;
  p = TEB_String_append_end2(p, TEB_OAuth2_str21, 0) - 1;
  http_response_property.property = TEB_String_append_end2(p, TEB_OAuth2_str6, 1);
  r = TEB_OAuth2_handle_server_response(http_response, &http_response_property, http_response_property.property - 1);
  if (r != 1) {
    return TEB_debug_function_end(-5);
  }
  p = TEB_String_append_end(p, http_response_property.property, http_response_property.property + http_response_property.property_length, 0) - 1;
  TEB_char* text = TEB_String_append_end2(p, TEB_OAuth2_str20, 0);
  while (1) {
    TEB_debug_print(text);
    TEB_debug_print("\nThe other values read are device_code = ");
    TEB_debug_print(device_code);
    TEB_debug_print(" and interval = ");
    TEB_debug_print_int(interval);
    TEB_debug_print(".\n");
    if (oauth2_step3_display_user_code != TEB_NULL_POINTER) (*oauth2_step3_display_user_code)(text);
    //Create a new request for login credentials and it must be redone every time because buffer is recycled to parse response. Currently device_code and text are saved at the end of the buffer.
    if (TEB_OAuth2_initialize_http_request(http_request, splittable_array_index) != 1) {
      return TEB_debug_function_end(-12);
    }
    http_request->request_text = TEB_OAuth2_generate_http_request_text(4, TEB_NULL_POINTER, device_code, TEB_NULL_POINTER,
                                                                       TEB_NULL_POINTER, splittable_array_index, text - 1);  //Ends with \0.
    TEB_delay(interval * 1000, 1);
    p = ((TEB_char*)TEB_SplittableArray_last_element_pointer(splittable_array_index)) - TEB_String_strlen(text) - TEB_String_strlen(device_code) - 10;
    r = TEB_http_send_request(http_request, http_response,
                              (TEB_char*)TEB_SplittableArray_split_array(splittable_array_index),
                              (TEB_size_t)(p - (TEB_char*)TEB_SplittableArray_split_array(splittable_array_index)),
                              TEB_OAuth2_response_reception_algorithm,
                              TEB_NULL_POINTER, 1);
    if (r == 1) {
      //Now I have to analyze the answer.
      http_response_property.property = TEB_NULL_POINTER;
      r = TEB_OAuth2_handle_server_response(http_response, &http_response_property, p);
      if (r == 2) {
        //Now I have to see what is the status code of the response.
        if (http_response_property.status_code == 400 || http_response_property.status_code == 401) {  //error
          return TEB_debug_function_end(-6);
        } else if (http_response_property.status_code == 403) {
          http_response_property.property = TEB_String_append_end2(p - 1, TEB_OAuth2_str22, 1);
          if (TEB_OAuth2_handle_server_response(http_response, &http_response_property, http_response_property.property - 1) == 1) {
            if (*http_response_property.property == 'a' && *(http_response_property.property + 1) == 'c' && *(http_response_property.property + 2) == 'c' && *(http_response_property.property + 3) == 'e' && *(http_response_property.property + 4) == 's' && *(http_response_property.property + 5) == 's' && *(http_response_property.property + 6) == '_' && *(http_response_property.property + 7) == 'd' && *(http_response_property.property + 8) == 'e' && *(http_response_property.property + 9) == 'n' && *(http_response_property.property + 10) == 'i' && *(http_response_property.property + 11) == 'e' && *(http_response_property.property + 12) == 'd') {
              return TEB_debug_function_end(2);
              ;  //Everything ok, but access has been denied.
            }
            if (*http_response_property.property == 's' && *(http_response_property.property + 1) == 'l' && *(http_response_property.property + 2) == 'o' && *(http_response_property.property + 3) == 'w' && *(http_response_property.property + 4) == '_' && *(http_response_property.property + 5) == 'd' && *(http_response_property.property + 6) == 'o' && *(http_response_property.property + 7) == 'w' && *(http_response_property.property + 8) == 'n') {
              TEB_delay(1000, 1);
              continue;
            }
            if (*http_response_property.property == 'o' && *(http_response_property.property + 1) == 'r' && *(http_response_property.property + 2) == 'g' && *(http_response_property.property + 3) == '_' && *(http_response_property.property + 4) == 'i' && *(http_response_property.property + 5) == 'n' && *(http_response_property.property + 6) == 't' && *(http_response_property.property + 7) == 'e' && *(http_response_property.property + 8) == 'r' && *(http_response_property.property + 9) == 'n' && *(http_response_property.property + 10) == 'a' && *(http_response_property.property + 11) == 'l') {
              return TEB_debug_function_end(-11);
            }
          } else {
            return TEB_debug_function_end(-7);
          }
        } else if (http_response_property.status_code == 428) {  //Pending Authorization.
          continue;
        } else if (http_response_property.status_code == 200) {
          //the http response is at the beginning of the buffer
          return TEB_debug_function_end(1);
        } else {  //Unknown status code.
          return TEB_debug_function_end(-8);
        }
      } else {
        return TEB_debug_function_end(-9);
      }
    } else {
      return TEB_debug_function_end(-10);
    }
  }
}

static TEB_small_int TEB_OAuth2_step6 (struct TEB_http_response* http_response,
                                      TEB_char* access_token_buffer,
                                      TEB_char* refresh_token_buffer,
                                      TEB_size_t splittable_array_index) {
  TEB_debug_function_start("TEB_OAuth2_step6");
  struct TEB_OAuth2_http_response_property http_response_property;
  TEB_char* p = (TEB_char*)TEB_SplittableArray_last_element_pointer(splittable_array_index);
  p = TEB_String_append_end2(p, TEB_OAuth2_str12, 1) - 1;
  http_response_property.property = TEB_String_append_end2(p, TEB_OAuth2_str13, 0);
  if (TEB_OAuth2_handle_server_response(http_response, &http_response_property, http_response_property.property - 1) == 1) {
    TEB_String_append(access_token_buffer, http_response_property.property, http_response_property.property + http_response_property.property_length);
    TEB_debug_print("\nThe access token read is ");
    TEB_debug_print(access_token_buffer);
    TEB_debug_print(".\n");
  } else {
    return TEB_debug_function_end(-1);
  }
  p = (TEB_char*)TEB_SplittableArray_last_element_pointer(splittable_array_index);
  p = TEB_String_append_end2(p, TEB_OAuth2_str12, 1) - 1;
  http_response_property.property = TEB_String_append_end2(p, TEB_OAuth2_str14, 0);
  if (TEB_OAuth2_handle_server_response(http_response, &http_response_property, http_response_property.property - 1) == 1) {
    TEB_String_append(refresh_token_buffer, http_response_property.property, http_response_property.property + http_response_property.property_length);
    TEB_debug_print("\nThe refresh token read is ");
    TEB_debug_print(refresh_token_buffer);
    TEB_debug_print(".\n");
  } else {
    return TEB_debug_function_end(-2);
  }
  return TEB_debug_function_end(1);
}

static TEB_small_int TEB_OAuth2_refresh_access_token (const TEB_char* refresh_token,
                                                     TEB_char* access_token_buffer,
                                                     TEB_size_t splittable_array_index) {
  TEB_debug_function_start("TEB_OAuth2_refresh_access_token");
  struct TEB_http_request http_request;
  struct TEB_http_response http_response;
  if (TEB_OAuth2_initialize_http_request(&http_request, splittable_array_index) != 1) {
    return TEB_debug_function_end(-1);
  }
  TEB_char* p = (TEB_char*)TEB_SplittableArray_last_element_pointer(splittable_array_index);
  http_request.request_text = TEB_OAuth2_generate_http_request_text(7,
                                                                    TEB_NULL_POINTER,
                                                                    TEB_NULL_POINTER,
                                                                    refresh_token,
                                                                    TEB_NULL_POINTER,
                                                                    splittable_array_index,
                                                                    p);
  TEB_small_int r = TEB_http_send_request(&http_request, &http_response,
                                          (TEB_char*)TEB_SplittableArray_split_array(splittable_array_index),
                                          TEB_SplittableArray_number_of_free_elements(splittable_array_index),
                                          TEB_OAuth2_response_reception_algorithm,
                                          TEB_NULL_POINTER, 1);
  if (r != 1) {
    return TEB_debug_function_end(-3);
  }
  struct TEB_OAuth2_http_response_property http_response_property;
  p = TEB_String_append_end2(p, TEB_OAuth2_str12, 1) - 1;
  http_response_property.property = TEB_String_append_end2(p, TEB_OAuth2_str13, 0);
  r = TEB_OAuth2_handle_server_response(&http_response, &http_response_property, http_response_property.property - 1);
  if (r == 1 && http_response_property.status_code == 200) {
    TEB_String_append(access_token_buffer, http_response_property.property, http_response_property.property + http_response_property.property_length);
    TEB_debug_print("\nThe access token read is ");
    TEB_debug_print(access_token_buffer);
    TEB_debug_print(".\n");
    return TEB_debug_function_end(1);
  } else {
    return TEB_debug_function_end(-2);
  }
}

static TEB_small_int TEB_OAuth2_logout_ (const TEB_char* token,
                                        TEB_size_t splittable_array_index) {
  TEB_debug_function_start("TEB_OAuth2_logout_");
  struct TEB_http_request http_request;
  struct TEB_http_response http_response;
  if (TEB_OAuth2_initialize_http_request(&http_request, splittable_array_index) != 1) {
    return TEB_debug_function_end(-1);
  }
  TEB_char* p = (TEB_char*)TEB_SplittableArray_last_element_pointer(splittable_array_index);
  http_request.request_text = TEB_OAuth2_generate_http_request_text(8,
                                                                    TEB_NULL_POINTER,
                                                                    TEB_NULL_POINTER,
                                                                    TEB_NULL_POINTER,
                                                                    token,
                                                                    splittable_array_index,
                                                                    p);
  TEB_small_int r = TEB_http_send_request(&http_request, &http_response,
                                          (TEB_char*)TEB_SplittableArray_split_array(splittable_array_index),
                                          TEB_SplittableArray_number_of_free_elements(splittable_array_index),
                                          TEB_OAuth2_response_reception_algorithm,
                                          TEB_NULL_POINTER, 1);
  if (r != 1) {
    return TEB_debug_function_end(-3);
  }
  struct TEB_OAuth2_http_response_property http_response_property;
  http_response_property.property = TEB_NULL_POINTER;
  r = TEB_OAuth2_handle_server_response(&http_response, &http_response_property, p);
  if (r == 2 && http_response_property.status_code == 200) {
    TEB_debug_print("\nLogged out with access token ");
    TEB_debug_print(token);
    TEB_debug_print(".\n");
    return TEB_debug_function_end(1);
  } else {
    return TEB_debug_function_end(-2);
  }
}

TEB_small_int TEB_OAuth2_login (TEB_char* access_token_buffer,
                               TEB_char* refresh_token_buffer,
                               const TEB_char* scope,
                               TEB_char* function_buffer,
                               TEB_small_int (*oauth2_step3_display_user_code)(const TEB_char* text)) {
  TEB_debug_function_start("TEB_OAuth2_login");
  if (access_token_buffer == TEB_NULL_POINTER) TEB_fatal_error(118, "access_token_buffer cannot be NULL.", 2);
  if (refresh_token_buffer == TEB_NULL_POINTER) TEB_fatal_error(119, "refresh_token_buffer cannot be NULL.", 2);
  if (scope == TEB_NULL_POINTER) TEB_fatal_error(120, "scope cannot be NULL.", 2);
  if (oauth2_step3_display_user_code == TEB_NULL_POINTER) TEB_fatal_error(121, "oauth2_step3_display_user_code cannot be NULL.", 2);
  TEB_size_t splittable_array_index;
  if (function_buffer == TEB_NULL_POINTER) splittable_array_index = TEB_SplittableArray_new_array(sizeof(TEB_char), TEB_OAuth2_SPLITTABLE_BUFFER_SIZE_FOR_LOGIN, TEB_NULL_POINTER);
  else splittable_array_index = TEB_SplittableArray_new_array(sizeof(TEB_char), TEB_OAuth2_SPLITTABLE_BUFFER_SIZE_FOR_LOGIN, function_buffer);
  if (splittable_array_index == 0) return TEB_debug_function_end(-1);
  struct TEB_http_request http_request;
  struct TEB_http_response http_response;
  TEB_small_int r = TEB_OAuth2_step1_2_3_4_5(&http_request, &http_response, access_token_buffer, refresh_token_buffer, scope, splittable_array_index, oauth2_step3_display_user_code);
  if (r == 1) {
    if (TEB_OAuth2_step6(&http_response, access_token_buffer, refresh_token_buffer, splittable_array_index) != 1) r = -2;
  } else if (r != 2) r = -3;  //If r=2 permission not granted.
  if (TEB_SplittableArray_delete_last_array() != 1) {
    TEB_fatal_error(122, "Buffer deallocation failed.", 2);
    r = r - 10;
  }
  return TEB_debug_function_end(r);
}

TEB_small_int TEB_OAuth2_relogin (const TEB_char* refresh_token,
                                 TEB_char* access_token_buffer,
                                 TEB_char* function_buffer) {
  TEB_debug_function_start("TEB_OAuth2_relogin");
  if (refresh_token == TEB_NULL_POINTER) TEB_fatal_error(123, "refresh_token cannot be NULL.", 2);
  if (access_token_buffer == TEB_NULL_POINTER) TEB_fatal_error(124, "access_token_buffer cannot be NULL.", 2);
  TEB_size_t splittable_array_index;
  if (function_buffer == TEB_NULL_POINTER) splittable_array_index = TEB_SplittableArray_new_array(sizeof(TEB_char), TEB_OAuth2_SPLITTABLE_BUFFER_SIZE_FOR_RELOGIN, TEB_NULL_POINTER);
  else splittable_array_index = TEB_SplittableArray_new_array(sizeof(TEB_char), TEB_OAuth2_SPLITTABLE_BUFFER_SIZE_FOR_RELOGIN, function_buffer);
  if (splittable_array_index == 0) return TEB_debug_function_end(-1);
  TEB_small_int r = TEB_OAuth2_refresh_access_token(refresh_token, access_token_buffer, splittable_array_index);
  if (TEB_SplittableArray_delete_last_array() != 1) {
    TEB_fatal_error(125, "Buffer deallocation failed.", 2);
    r = r - 10;
  }
  return TEB_debug_function_end(r);
}

TEB_small_int TEB_OAuth2_logout (const TEB_char* token, TEB_char* function_buffer) {
  TEB_debug_function_start("TEB_OAuth2_logout");
  if (token == TEB_NULL_POINTER) TEB_fatal_error(126, "token cannot be NULL.", 2);
  TEB_size_t splittable_array_index;
  if (function_buffer == TEB_NULL_POINTER) splittable_array_index = TEB_SplittableArray_new_array(sizeof(TEB_char), TEB_OAuth2_SPLITTABLE_BUFFER_SIZE_FOR_LOGOUT, TEB_NULL_POINTER);
  else splittable_array_index = TEB_SplittableArray_new_array(sizeof(TEB_char), TEB_OAuth2_SPLITTABLE_BUFFER_SIZE_FOR_LOGOUT, function_buffer);
  if (splittable_array_index == 0) return TEB_debug_function_end(-1);
  TEB_small_int r = TEB_OAuth2_logout_(token, splittable_array_index);
  if (TEB_SplittableArray_delete_last_array() != 1) {
    TEB_fatal_error(127, "Buffer deallocation failed.", 2);
    r = r - 10;
  }
  return TEB_debug_function_end(r);
}

TEB_char* TEB_OAuth2_response_reception_algorithm (TEB_char* response_buffer,
                                                  TEB_size_t response_buffer_length,
                                                  TEB_time_t response_delay_in_ms,
                                                  void* additional_parameters,
												  TEB_medium_u_int mode) {
  TEB_debug_function_start("TEB_OAuth2_response_reception_algorithm");
  TEB_time_t m = TEB_ms_elapsed();
  TEB_big_int nbit = 256;  //nbit > 0 and <= response_buffer_length.
  TEB_big_int n;
  TEB_char* b = response_buffer;
  while (1) {
    if (response_buffer_length < nbit) nbit = response_buffer_length;
    n = TEB_http_receive(response_buffer, nbit, mode);
    if (n != -1 && n != 0) {
      response_buffer = response_buffer + n;
      response_buffer_length = response_buffer_length - n;
      if (response_buffer - b >= 7) {
        b = (TEB_char*)TEB_String_last_index_of3(b, response_buffer, "\r\n0\r\n\r\n");
        if (b != 0) {
          response_buffer = b + 7;
          TEB_debug_print("\nTEB_OAuth2_response_reception_algorithm has correctly detected the final string of the http response.\n");
          break;
        } else {
          b = response_buffer - 6;
        }
      }
      if (response_buffer_length == 0) {
        TEB_debug_print("\nTEB_OAuth2_response_reception_algorithm did not find at the end \r\n0\r\n\r\n. Maybe response_buffer is too short.");
        break;
      }
      m = TEB_ms_elapsed();
    } else if (TEB_is_delay_over(m, response_delay_in_ms, 1) == 1) {
      TEB_debug_print("\nTEB_OAuth2_response_reception_algorithm did not find at the end \r\n0\r\n\r\n. There may be problems with the Internet connection.");
      break;
    }
  }
  TEB_debug_function_end(0);
  return response_buffer;
}

TEB_small_int TEB_OAuth2_handle_server_response (struct TEB_http_response* http_response,
                                                struct TEB_OAuth2_http_response_property* http_response_property,
                                                TEB_char* function_buffer) {
  TEB_debug_function_start("TEB_OAuth2_handle_server_response");
  function_buffer = TEB_String_append_end2(function_buffer, TEB_OAuth2_str16, 1);
  const TEB_char* t2;
  if (http_response->header_length == 0) t2 = TEB_NULL_POINTER;
  else t2 = TEB_String_index_of(http_response->header, http_response->header + http_response->header_length, function_buffer + 1, function_buffer + 9);
  if (t2 == TEB_NULL_POINTER) {
    TEB_debug_print("TEB_OAuth2_handle_server_response returned -1.");
    return TEB_debug_function_end(-1);
  }
  function_buffer = (TEB_char*)t2 + 9;
  TEB_medium_u_int code;
  if (TEB_Number_is_int2(function_buffer, function_buffer + 3) != 0) {
    code = TEB_Number_str_int2(function_buffer, function_buffer + 3);
  } else {
    TEB_debug_print("TEB_OAuth2_handle_server_response returned -2.");
    return TEB_debug_function_end(-2);
  }
  http_response_property->status_code = code;
  if (http_response_property->property == TEB_NULL_POINTER) return TEB_debug_function_end(2);
  http_response_property->property_length = TEB_String_strlen(http_response_property->property);
  function_buffer = (TEB_char*)TEB_String_index_of(http_response->payload, http_response->payload + http_response->payload_length, http_response_property->property, http_response_property->property + http_response_property->property_length);
  if (function_buffer == TEB_NULL_POINTER) {
    TEB_debug_print("TEB_OAuth2_handle_server_response returned -3.");
    return TEB_debug_function_end(-3);
  }
  if (*(function_buffer - 1) != '"' || *(function_buffer + http_response_property->property_length) != '"' || *(function_buffer + http_response_property->property_length + 1) != ':') {
    TEB_debug_print("TEB_OAuth2_handle_server_response -4.");
    return TEB_debug_function_end(-4);
  }
  function_buffer = function_buffer + http_response_property->property_length + 3;
  if (*function_buffer == '"') function_buffer = function_buffer + 1;
  t2 = TEB_String_index_of2(function_buffer + 1, "\n");
  if (t2 == TEB_NULL_POINTER) {
    TEB_debug_print("TEB_OAuth2_handle_server_response -5.");
    return TEB_debug_function_end(-5);
  }
  t2 = t2 - 1;
  if (*t2 == ',') t2 = t2 - 1;
  if (*t2 == '"') t2 = t2 - 1;
  http_response_property->property = function_buffer;
  http_response_property->property_length = t2 - function_buffer + 1;
  return TEB_debug_function_end(1);
}

TEB_small_int TEB_OAuth2_standard_oauth2_step3_display_user_code (const TEB_char* text) {
  TEB_debug_function_start("TEB_OAuth2_standard_oauth2_step3_display_user_code");
  TEB_small_int r = TEB_display_print(1, text, 1, 1);
  return TEB_debug_function_end(r);
}

#ifdef TEB_LibrarySettings_DEBUG_MODE
static void TEB_OAuth2_function_end (const TEB_char* f_name, TEB_bool ok) {
  if (ok == 0) {
    TEB_debug_print("\n");
    TEB_debug_print(f_name);
    TEB_debug_print(" ko");
  } else {
    TEB_debug_print("\n");
    TEB_debug_print(f_name);
    TEB_debug_print(" ok");
  }
}

TEB_small_int TEB_OAuth2_test1 (TEB_char* access_token_buffer) {
  TEB_debug_function_start("TEB_OAuth2_test1");

  TEB_char refresh_token_buffer[500];

  TEB_small_int r = TEB_OAuth2_login(access_token_buffer, refresh_token_buffer, "https://www.googleapis.com/auth/drive.file", TEB_NULL_POINTER, TEB_OAuth2_standard_oauth2_step3_display_user_code);
  switch (r) {
    case 1:
      TEB_debug_print("\nThe access token is ");
      TEB_debug_print(access_token_buffer);
      TEB_debug_print(" and the refresh token buffer is ");
      TEB_debug_print(refresh_token_buffer);
      TEB_debug_print(".\n");
      break;
    case 2:
      TEB_debug_print("\nError, the user refuses to grant access to the device.\n");
      break;
  }
  if (r == 1) TEB_OAuth2_function_end("TEB_OAuth2_login", 1);
  else {
    TEB_OAuth2_function_end("TEB_OAuth2_login", 0);
    return TEB_debug_function_end(-1);
  }

  if (TEB_OAuth2_relogin(refresh_token_buffer, access_token_buffer, TEB_NULL_POINTER) == 1) TEB_OAuth2_function_end("TEB_OAuth2_relogin", 1);
  else {
    TEB_OAuth2_function_end("TEB_OAuth2_relogin", 0);
    return TEB_debug_function_end(-2);
  }
  TEB_debug_print("\nThe access token is ");
  TEB_debug_print(access_token_buffer);
  TEB_debug_print(".\n");

  return TEB_debug_function_end(1);
}

TEB_small_int TEB_OAuth2_test2 (const TEB_char* access_token) {
  TEB_debug_function_start("TEB_OAuth2_test2");

  if (TEB_OAuth2_logout(access_token, TEB_NULL_POINTER) == 1) TEB_OAuth2_function_end("TEB_OAuth2_logout", 1);
  else {
    TEB_OAuth2_function_end("TEB_OAuth2_logout", 0);
    return TEB_debug_function_end(-1);
  }

  TEB_wifi_disconnect(1, 1);

  return TEB_debug_function_end(1);
}
#endif