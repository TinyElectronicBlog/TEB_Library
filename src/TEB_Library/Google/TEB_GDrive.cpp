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

#include "TEB_GDrive.h"
#include "../Buffer/TEB_SplittableArray.h"
#include "../String/TEB_String.h"
#include "../Number/TEB_Number.h"
#include "TEB_OAuth2.h"

static const TEB_char TEB_GDrive_str1[] = "https://www.googleapis.com";
static const TEB_char TEB_GDrive_str2[] = "drive/v3/files";
static const TEB_char TEB_GDrive_str3[] = "?key=";
static const TEB_char TEB_GDrive_str4[] = " HTTP/1.1\r\nAuthorization:Bearer ";
static const TEB_char TEB_GDrive_str5[] = "&orderBy=";
static const TEB_char TEB_GDrive_str6[] = "&pageSize=";
static const TEB_char TEB_GDrive_str7[] = "&pageToken=";
static const TEB_char TEB_GDrive_str8[] = "&q=";
static const TEB_char TEB_GDrive_str9[] = "&fields=";
static const TEB_char TEB_GDrive_str10[] = "Parents=";
static const TEB_char TEB_GDrive_str11[] = "&remove";
static const TEB_char TEB_GDrive_str12[] = "&uploadType";
static const TEB_char TEB_GDrive_str13[] = "=media";
static const TEB_char TEB_GDrive_str14[] = "\r\nAccept:";
static const TEB_char TEB_GDrive_str15[] = "Content-Type:";
static const TEB_char TEB_GDrive_str16[] = "Length:";
static const TEB_char TEB_GDrive_str17[] = "\"name\":\"";
static const TEB_char TEB_GDrive_str18[] = "\"parents\":[\"";
static const TEB_char TEB_GDrive_str19[] = "mimeType\":\"";
static const TEB_char TEB_GDrive_str20[] = "application/json";

static TEB_small_int TEB_GDrive_initialize_http_request (struct TEB_http_request* http_request, TEB_size_t splittable_array_index) {
  TEB_debug_function_start("TEB_GDrive_initialize_http_request");
  //load at the beginning of the buffer all the values except request_text.
  if (TEB_SplittableArray_add_elements(splittable_array_index, TEB_OAuth2_SERVER_ADDRESS, TEB_String_strlen(TEB_OAuth2_SERVER_ADDRESS) + 1) != 1) return TEB_debug_function_end(-2);
  http_request->server_address = (const TEB_char*)TEB_SplittableArray_split_array(splittable_array_index);
  if (TEB_SplittableArray_add_elements(splittable_array_index, TEB_OAuth2_ROOT_CA, TEB_String_strlen(TEB_OAuth2_ROOT_CA) + 1) != 1) return TEB_debug_function_end(-1);
  http_request->root_ca = (const TEB_char*)TEB_SplittableArray_split_array(splittable_array_index);
  http_request->server_port = TEB_OAuth2_SERVER_PORT;
  http_request->connection_timeout_in_ms = TEB_GDrive_HTTP_REQUEST_CONNECTION_TIMEOUT_IN_MS;
  http_request->response_delay_in_ms = TEB_GDrive_HTTP_REQUEST_RESPONSE_DELAY_IN_MS;
  http_request->use_ssl = 1;
  return TEB_debug_function_end(1);
}

/*
  temp_i1   page_size2
  temp_p1   order_by2        remove_parents3      parent1
  temp_p2   page_token2      add_parents3         mime_type1        file_data4
  temp_p3   q2               file_name1_3 1       mime_type4        mime_type7
  temp_p4   fields2          file_id3_4_5_6_7
  temp_p5   access_token     access_token         access_token      access_token    access_token
*/
static const TEB_char* TEB_GDrive_generate_http_request_text (TEB_small_u_int type,
                                                             const TEB_char* access_token,
                                                             const TEB_char* temp_p1,
                                                             const TEB_char* temp_p2,
                                                             const TEB_char* temp_p3,
                                                             const TEB_char* temp_p4,
                                                             TEB_medium_u_int temp_i1,
                                                             TEB_size_t splittable_array_index) {
  TEB_debug_function_start("TEB_GDrive_generate_http_request_text");
  const TEB_char* t = "\r\n";
  TEB_char* p = (TEB_char*)TEB_SplittableArray_last_element_pointer(splittable_array_index);
  TEB_char* p_e = p;
  *p = TEB_NULL_CHAR;
  p = p - 1;
  if (type == 4) {
    p = TEB_String_append_end2(p, temp_p2, 0) - 1;
  }
  if (type == 1 || type == 3) {
    *p = '}';
    p = p - 1;
    if (type == 1) {
      if (temp_p2 != TEB_NULL_POINTER) {
        *p = '\"';
        p = p - 1;
        p = TEB_String_append_end2(p, temp_p2, 0) - 1;
        p = TEB_String_append_end2(p, TEB_GDrive_str19, 0) - 1;
        *p = '\"';
        p = p - 1;
      }
      if (temp_p1 != TEB_NULL_POINTER) {
        if (temp_p2 != TEB_NULL_POINTER) {
          *p = ',';
          p = p - 1;
        }
        *p = ']';
        p = p - 1;
        *p = '\"';
        p = p - 1;
        p = TEB_String_append_end2(p, temp_p1, 0) - 1;
        p = TEB_String_append_end2(p, TEB_GDrive_str18, 0) - 1;
      }
    }
    if (temp_p3 != TEB_NULL_POINTER) {
      if ((temp_p2 != TEB_NULL_POINTER || temp_p1 != TEB_NULL_POINTER) && type == 1) {
        *p = ',';
        p = p - 1;
      }
      *p = '\"';
      p = p - 1;
      p = TEB_String_append_end2(p, temp_p3, 0) - 1;
      p = TEB_String_append_end2(p, TEB_GDrive_str17, 0) - 1;
    }
    *p = '{';
    p = p - 1;
  }
  p = TEB_String_append_end2(p, t, 0) - 1;
  p = TEB_String_append_end2(p, t, 0) - 1;
  if (type == 1 || type == 3 || type == 4) {
    TEB_String_int_str((p_e - p) - 5, (TEB_char*)TEB_SplittableArray_split_array(splittable_array_index));  //temporary buffer to convert number to string
    p = TEB_String_append_end2(p, (TEB_char*)TEB_SplittableArray_split_array(splittable_array_index), 0) - 1;
    p = TEB_String_append_end2(p, TEB_GDrive_str16, 0) - 1;
    p = TEB_String_append_end(p, TEB_GDrive_str15, TEB_GDrive_str15 + 8, 0) - 1;
    p = TEB_String_append_end2(p, t, 0) - 1;
    if (type == 4) p = TEB_String_append_end2(p, temp_p3, 0) - 1;
    else p = TEB_String_append_end2(p, TEB_GDrive_str20, 0) - 1;
    p = TEB_String_append_end2(p, TEB_GDrive_str15, 0) - 1;
    p = TEB_String_append_end2(p, t, 0) - 1;
  }
  p = TEB_String_append_end2(p, TEB_GDrive_str20, 0) - 1;
  p = TEB_String_append_end2(p, TEB_GDrive_str14, 0) - 1;
  p = TEB_String_append_end2(p, access_token, 0) - 1;
  p = TEB_String_append_end2(p, TEB_GDrive_str4, 0) - 1;
  switch (type) {
    case 2:
      if (temp_p4 != TEB_NULL_POINTER) {
        p = TEB_String_append_end2(p, temp_p4, 0) - 1;
        p = TEB_String_append_end2(p, TEB_GDrive_str9, 0) - 1;
      }
      if (temp_p3 != TEB_NULL_POINTER) {
        p = TEB_String_append_end2(p, temp_p3, 0) - 1;
        p = TEB_String_append_end2(p, TEB_GDrive_str8, 0) - 1;
      }
      if (temp_p2 != TEB_NULL_POINTER) {
        p = TEB_String_append_end2(p, temp_p2, 0) - 1;
        p = TEB_String_append_end2(p, TEB_GDrive_str7, 0) - 1;
      }
      if (temp_i1 != 0) {
        TEB_String_int_str(temp_i1, (TEB_char*)TEB_SplittableArray_split_array(splittable_array_index));  //temporary buffer to convert number to string
        p = TEB_String_append_end2(p, (TEB_char*)TEB_SplittableArray_split_array(splittable_array_index), 0) - 1;
        p = TEB_String_append_end2(p, TEB_GDrive_str6, 0) - 1;
      }
      if (temp_p1 != TEB_NULL_POINTER) {
        p = TEB_String_append_end2(p, temp_p1, 0) - 1;
        p = TEB_String_append_end2(p, TEB_GDrive_str5, 0) - 1;
      }
      break;
    case 3:
      if (temp_p1 != TEB_NULL_POINTER) {
        p = TEB_String_append_end2(p, temp_p1, 0) - 1;
        p = TEB_String_append_end2(p, TEB_GDrive_str10, 0) - 1;
        p = TEB_String_append_end2(p, TEB_GDrive_str11, 0) - 1;
      }
      if (temp_p2 != TEB_NULL_POINTER) {
        p = TEB_String_append_end2(p, temp_p2, 0) - 1;
        p = TEB_String_append_end2(p, TEB_GDrive_str10, 0) - 1;
        p = TEB_String_append_end2(p, "&add", 0) - 1;
      }
      break;
    case 4:
      p = TEB_String_append_end2(p, TEB_GDrive_str13, 0) - 1;
      p = TEB_String_append_end2(p, TEB_GDrive_str12, 0) - 1;
      break;
    case 5:
      p = TEB_String_append_end2(p, TEB_GDrive_str13, 0) - 1;
      p = TEB_String_append_end2(p, "&alt", 0) - 1;
      break;
    case 7:
      p = TEB_String_append_end2(p, temp_p3, 0) - 1;
      *p = '=';
      p = p - 1;
      p = TEB_String_append_end(p, TEB_GDrive_str19, TEB_GDrive_str19 + 8, 0) - 1;
      *p = '&';
      p = p - 1;
      break;
  }
  p = TEB_String_append_end2(p, TEB_OAuth2_API_KEY, 0) - 1;
  p = TEB_String_append_end2(p, TEB_GDrive_str3, 0) - 1;
  if (type == 7) p = TEB_String_append_end2(p, "/export", 0) - 1;
  if (type == 3 || type == 4 || type == 5 || type == 6 || type == 7) {
    p = TEB_String_append_end2(p, temp_p4, 0) - 1;
    *p = '/';
    p = p - 1;
  }
  p = TEB_String_append_end2(p, TEB_GDrive_str2, 0) - 1;
  if (type == 4) p = TEB_String_append_end2(p, "upload/", 0) - 1;
  *p = '/';
  p = p - 1;
  p = TEB_String_append_end2(p, TEB_GDrive_str1, 0) - 1;
  *p = ' ';
  p = p - 1;
  if (type == 4) type = 3;
  if (type == 5 || type == 7) type = 2;
  switch (type) {
    case 1:
      p = TEB_String_append_end2(p, "POST", 0);
      break;
    case 2:
      p = TEB_String_append_end2(p, "GET", 0);
      break;
    case 3:
      p = TEB_String_append_end2(p, "PATCH", 0);
      break;
    case 6:
      p = TEB_String_append_end2(p, "DELETE", 0);
      break;
  }
  TEB_SplittableArray_reset_array(splittable_array_index);
  TEB_debug_function_end(0);
  return (const TEB_char*)p;
}

static TEB_small_int TEB_GDrive_execute_http_request (TEB_small_u_int type,
                                                     const TEB_char* access_token,
                                                     const TEB_char* temp_p1,
                                                     const TEB_char* temp_p2,
                                                     const TEB_char* temp_p3,
                                                     const TEB_char* temp_p4,
                                                     TEB_medium_u_int temp_i1,
                                                     TEB_char* response_buffer,
                                                     TEB_char* function_buffer) {
  TEB_debug_function_start("TEB_GDrive_execute_http_request");
  TEB_size_t size;
  switch (type) {
    case 1:
      size = TEB_GDrive_SPLITTABLE_BUFFER_SIZE_FOR_FOR_CREATE_METADATA_ONLY_FILE;
      break;
    case 2:
      size = TEB_GDrive_SPLITTABLE_BUFFER_SIZE_FOR_FOR_SEARCH_FILE;
      break;
    case 3:
      size = TEB_GDrive_SPLITTABLE_BUFFER_SIZE_FOR_FOR_UPDATE_FILE_METADATA;
      break;
    case 4:
      size = TEB_GDrive_SPLITTABLE_BUFFER_SIZE_FOR_FOR_UPDATE_FILE_CONTENT;
      break;
    case 5:
      size = TEB_GDrive_SPLITTABLE_BUFFER_SIZE_FOR_FOR_GET_FILE_CONTENT;
      break;
    case 6:
      size = TEB_GDrive_SPLITTABLE_BUFFER_SIZE_FOR_FOR_DELETE_FILE;
      break;
    case 7:
      size = TEB_GDrive_SPLITTABLE_BUFFER_SIZE_FOR_FOR_EXPORT_GOOGLE_DOC_CONTENT;
      break;
  }
  TEB_size_t splittable_array_index;
  if (function_buffer == TEB_NULL_POINTER) splittable_array_index = TEB_SplittableArray_new_array(sizeof(TEB_char), size, TEB_NULL_POINTER);
  else splittable_array_index = TEB_SplittableArray_new_array(sizeof(TEB_char), size, function_buffer);
  if (splittable_array_index == 0) return TEB_debug_function_end(-1);
  struct TEB_http_request http_request;
  struct TEB_http_response http_response;
  TEB_GDrive_initialize_http_request(&http_request, splittable_array_index);
  http_request.request_text = TEB_GDrive_generate_http_request_text(type, access_token, temp_p1, temp_p2, temp_p3, temp_p4, temp_i1, splittable_array_index);
  TEB_small_u_int par[1];
  par[0] = type;
  TEB_small_int r = TEB_http_send_request(&http_request, &http_response,
                                          (TEB_char*)TEB_SplittableArray_split_array(splittable_array_index),
                                          TEB_SplittableArray_number_of_free_elements(splittable_array_index), TEB_GDrive_response_reception_algorithm, par, 1);
  if (r != 1) {
    r = -2;
  } else {
    //Now in splittable_buffer there is only the http response saved temporarily.
    struct TEB_OAuth2_http_response_property http_response_property;
	char idb[3];
	idb[0] = 'i'; idb[1] = 'd'; idb[2] = TEB_NULL_CHAR; 
    if (type == 1) http_response_property.property = idb;
    else http_response_property.property = TEB_NULL_POINTER;
    r = TEB_OAuth2_handle_server_response(&http_response, &http_response_property, (TEB_char*)TEB_SplittableArray_last_element_pointer(splittable_array_index));
    //The following function code should be updated each time the Google server changes the way it responds.
    if (type == 1) {
      if (r == 1) {
        if (http_response_property.status_code == 200) {
#ifndef TEB_LibrarySettings_DEBUG_MODE
          TEB_String_append(response_buffer, http_response_property.property, http_response_property.property + http_response_property.property_length);
#endif
#ifdef TEB_LibrarySettings_DEBUG_MODE
          if (http_response_property.property_length == 0) *response_buffer = TEB_NULL_CHAR;
          else TEB_String_append(response_buffer, http_response_property.property, http_response_property.property + http_response_property.property_length);
#endif
          r = 1;
        } else r = -7;  //Wrong response_code.
      } else r = -6;
    } else {
      if (r == 2) {
        if (type == 6) {
          if (http_response_property.status_code == 204) r = 1;
          else r = -4;
        } else {
          if (http_response_property.status_code == 200) {
            if (type == 5) {
#ifndef TEB_LibrarySettings_DEBUG_MODE
              TEB_String_append(response_buffer, http_response.payload, http_response.payload + http_response.payload_length);
#endif
#ifdef TEB_LibrarySettings_DEBUG_MODE
              if (http_response.payload_length == 0) *response_buffer = TEB_NULL_CHAR;
              else TEB_String_append(response_buffer, http_response.payload, http_response.payload + http_response.payload_length);
#endif
            } else if (type == 2) {
              while (*http_response.payload != '\n') {
                http_response.payload = http_response.payload + 1;
                http_response.payload_length = http_response.payload_length - 1;
              }
              http_response.payload = http_response.payload + 1;
              http_response.payload_length = http_response.payload_length - 2;
#ifndef TEB_LibrarySettings_DEBUG_MODE
              TEB_String_append(response_buffer, http_response.payload, http_response.payload + http_response.payload_length - 7);
#endif
#ifdef TEB_LibrarySettings_DEBUG_MODE
              if (http_response.payload_length - 7 == 0) *response_buffer = TEB_NULL_CHAR;
              else TEB_String_append(response_buffer, http_response.payload, http_response.payload + http_response.payload_length - 7);
#endif
            } else if (type == 7) {
              http_response.payload = http_response.payload + 3;
              http_response.payload_length = http_response.payload_length - 3;
#ifndef TEB_LibrarySettings_DEBUG_MODE
              TEB_String_append(response_buffer, http_response.payload, http_response.payload + http_response.payload_length);
#endif
#ifdef TEB_LibrarySettings_DEBUG_MODE
              if (http_response.payload_length == 0) *response_buffer = TEB_NULL_CHAR;
              else TEB_String_append(response_buffer, http_response.payload, http_response.payload + http_response.payload_length);
#endif
            }
            r = 1;
          } else r = -5;
        }
      } else r = -3;
    }
  }
  if (TEB_SplittableArray_delete_last_array() != 1) {
    TEB_fatal_error(97, "Buffer deallocation failed.", 2);
    r = r - 10;
  }
  return TEB_debug_function_end(r);
}

TEB_small_int TEB_GDrive_create_metadata_only_file (const TEB_char* access_token,
                                                   const TEB_char* name,
                                                   const TEB_char* parents,
                                                   const TEB_char* mime_type,
                                                   TEB_char* file_id_buffer,
                                                   TEB_char* function_buffer) {
  TEB_debug_function_start("TEB_GDrive_create_metadata_only_file");
  if (access_token == TEB_NULL_POINTER) TEB_fatal_error(98, "access_token cannot be NULL.", 2);
  if (name == TEB_NULL_POINTER) TEB_fatal_error(99, "name cannot be NULL.", 2);
  if (file_id_buffer == TEB_NULL_POINTER) TEB_fatal_error(100, "file_id_buffer cannot be NULL.", 2);
  TEB_small_int r = TEB_GDrive_execute_http_request(1, access_token, parents, mime_type, name, TEB_NULL_POINTER, 0, file_id_buffer, function_buffer);
  return TEB_debug_function_end(r);
}

TEB_small_int TEB_GDrive_update_file_metadata (const TEB_char* access_token,
                                              const TEB_char* file_id,
                                              const TEB_char* file_name,
                                              const TEB_char* add_parents,
                                              const TEB_char* remove_parents,
                                              TEB_char* function_buffer) {
  TEB_debug_function_start("TEB_GDrive_update_file_metadata");
  if (access_token == TEB_NULL_POINTER) TEB_fatal_error(103, "access_token cannot be NULL.", 2);
  if (file_id == TEB_NULL_POINTER) TEB_fatal_error(104, "file_id cannot be NULL.", 2);
  TEB_small_int r = TEB_GDrive_execute_http_request(3, access_token, remove_parents, add_parents, file_name, file_id, 0, TEB_NULL_POINTER, function_buffer);
  return TEB_debug_function_end(r);
}

TEB_small_int TEB_GDrive_update_file_content (const TEB_char* access_token,
                                             const TEB_char* file_id,
                                             const TEB_char* file_content,
                                             const TEB_char* mime_type,
                                             TEB_char* function_buffer) {
  TEB_debug_function_start("TEB_GDrive_update_file_content");
  if (access_token == TEB_NULL_POINTER) TEB_fatal_error(105, "access_token cannot be NULL.", 2);
  if (file_content == TEB_NULL_POINTER) TEB_fatal_error(106, "file_content cannot be NULL.", 2);
  if (mime_type == TEB_NULL_POINTER) TEB_fatal_error(107, "mime_type cannot be NULL.", 2);
  if (file_id == TEB_NULL_POINTER) TEB_fatal_error(108, "file_id cannot be NULL.", 2);
  TEB_small_int r = TEB_GDrive_execute_http_request(4, access_token, TEB_NULL_POINTER, file_content, mime_type, file_id, 0, TEB_NULL_POINTER, function_buffer);
  return TEB_debug_function_end(r);
}

TEB_small_int TEB_GDrive_search_file (const TEB_char* access_token,
                                     const TEB_char* q,
                                     const TEB_char* order_by,
                                     const TEB_char* fields,
                                     TEB_medium_u_int page_size,
                                     const TEB_char* page_token,
                                     TEB_char* response_buffer,
                                     TEB_char* function_buffer) {
  TEB_debug_function_start("TEB_GDrive_search_file");
  if (access_token == TEB_NULL_POINTER) TEB_fatal_error(101, "access_token cannot be NULL.", 2);
  if (response_buffer == TEB_NULL_POINTER) TEB_fatal_error(102, "response_buffer cannot be NULL.", 2);
  TEB_small_int r = TEB_GDrive_execute_http_request(2, access_token, order_by, page_token, q, fields, page_size, response_buffer, function_buffer);
  return TEB_debug_function_end(r);
}

TEB_small_int TEB_GDrive_get_file_content (const TEB_char* access_token,
                                          const TEB_char* file_id,
                                          TEB_char* response_buffer,
                                          TEB_char* function_buffer) {
  TEB_debug_function_start("TEB_GDrive_get_file_content");
  if (access_token == TEB_NULL_POINTER) TEB_fatal_error(109, "access_token cannot be NULL.", 2);
  if (response_buffer == TEB_NULL_POINTER) TEB_fatal_error(110, "response_buffer cannot be NULL.", 2);
  if (file_id == TEB_NULL_POINTER) TEB_fatal_error(111, "file_id cannot be NULL.", 2);
  TEB_small_int r = TEB_GDrive_execute_http_request(5, access_token, TEB_NULL_POINTER, TEB_NULL_POINTER, TEB_NULL_POINTER, file_id, 0, response_buffer, function_buffer);
  return TEB_debug_function_end(r);
}

TEB_small_int TEB_GDrive_delete_file (const TEB_char* access_token,
                                     const TEB_char* file_id,
                                     TEB_char* function_buffer) {
  TEB_debug_function_start("TEB_GDrive_delete_file");
  if (access_token == TEB_NULL_POINTER) TEB_fatal_error(112, "access_token cannot be NULL.", 2);
  if (file_id == TEB_NULL_POINTER) TEB_fatal_error(113, "file_id cannot be NULL.", 2);
  TEB_small_int r = TEB_GDrive_execute_http_request(6, access_token, TEB_NULL_POINTER, TEB_NULL_POINTER, TEB_NULL_POINTER, file_id, 0, TEB_NULL_POINTER, function_buffer);
  return TEB_debug_function_end(r);
}

TEB_small_int TEB_GDrive_export_google_document (const TEB_char* access_token,
                                                const TEB_char* file_id,
                                                const TEB_char* mime_type,
                                                TEB_char* response_buffer,
                                                TEB_char* function_buffer) {
  TEB_debug_function_start("TEB_GDrive_export_google_document");
  if (access_token == TEB_NULL_POINTER) TEB_fatal_error(114, "access_token cannot be NULL.", 2);
  if (file_id == TEB_NULL_POINTER) TEB_fatal_error(115, "file_id cannot be NULL.", 2);
  if (mime_type == TEB_NULL_POINTER) TEB_fatal_error(116, "mime_type cannot be NULL.", 2);
  if (response_buffer == TEB_NULL_POINTER) TEB_fatal_error(117, "response_buffer cannot be NULL.", 2);
  TEB_small_int r = TEB_GDrive_execute_http_request(7, access_token, TEB_NULL_POINTER, TEB_NULL_POINTER, mime_type, file_id, 0, response_buffer, function_buffer);
  return TEB_debug_function_end(r);
}

TEB_char* TEB_GDrive_response_reception_algorithm (TEB_char* response_buffer,
                                                  TEB_size_t response_buffer_length,
                                                  TEB_time_t response_delay_in_ms,
                                                  void* additional_parameters,
												  TEB_medium_u_int mode) {
  TEB_debug_function_start("TEB_GDrive_response_reception_algorithm");
  TEB_time_t m = TEB_ms_elapsed();
  TEB_big_int nbit = 256;  //nbit > 0 and <= response_buffer_length.
  TEB_big_int n;
  TEB_char* b = response_buffer;
  TEB_char* b2 = response_buffer;
  TEB_small_u_int brackets = 0;
  TEB_big_u_int len = 0;
  TEB_small_u_int temp_i2 = *((TEB_small_u_int*)additional_parameters);
  while (1) {
    if (response_buffer_length < nbit) nbit = response_buffer_length;
    n = TEB_http_receive(response_buffer, nbit, mode);
    if (n != -1 && n != 0) {
      if (temp_i2 == 4) {
        for (TEB_big_int i = 0; i < n; i = i + 1) {
          switch (*(response_buffer + i)) {
            case '{':
              brackets = brackets + 1;
              break;
            case '}':
              brackets = brackets - 1;
              break;
          }
        }
      }
      response_buffer = response_buffer + n;
      response_buffer_length = response_buffer_length - n;
      if (temp_i2 == 2 || temp_i2 == 3) temp_i2 = 1;
      else if (temp_i2 == 7) temp_i2 = 5;
      if (temp_i2 == 1) {
        if (response_buffer - b >= 7) {
          b = (TEB_char*)TEB_String_last_index_of3(b, response_buffer, "\r\n0\r\n\r\n");
          if (b != TEB_NULL_POINTER) {
            response_buffer = b + 7;
            TEB_debug_print("\nTEB_GDrive_response_reception_algorithm has correctly detected the final string of the http response.\n");
            break;
          } else {
            b = response_buffer - 6;
          }
        }
      } else if (temp_i2 == 4) {
        if (response_buffer - b >= 2 && brackets == 0) {
          b = (TEB_char*)TEB_String_last_index_of3(b, response_buffer, "}\n");
          if (b != TEB_NULL_POINTER) {
            response_buffer = b + 2;
            TEB_debug_print("\nTEB_GDrive_response_reception_algorithm has correctly detected the final string of the http response.\n");
            break;
          } else {
            b = response_buffer - 1;
          }
        }
      } else if (temp_i2 == 6) {
        if (response_buffer - b >= 10) {
          b = (TEB_char*)TEB_String_last_index_of3(b, response_buffer, "No Content");
          if (b != 0) {
            *b = '\r';
            b = b + 1;
            *b = '\n';
            b = b + 1;
			*b = '\r';
            b = b + 1;
			*b = '\n';
            b = b + 1;
			response_buffer = b;
            TEB_debug_print("\nTEB_GDrive_response_reception_algorithm has correctly detected the final string of the http response.\n");
            break;
          } else {
            b = response_buffer - 9;
          }
        }
      } else if (temp_i2 == 5) {
        if (brackets == 0) {
          if (response_buffer - b >= 4) {
            b = (TEB_char*)TEB_String_last_index_of3(b, response_buffer, "\r\n\r\n");
            if (b != TEB_NULL_POINTER) {
              b2 = (TEB_char*)TEB_String_last_index_of3(b2, response_buffer, "-Length: ");
              if (b2 != TEB_NULL_POINTER) {
                int i2 = 9;
                while (TEB_Number_char_digit(*(b2 + i2)) != -1) i2 = i2 + 1;
                if (i2 != 9) {
                  len = TEB_Number_str_int2(b2 + 9, b2 + i2);
                  brackets = 1;  //temporary variable
                  b = b + 4;
                } else {
                  TEB_debug_print("TEB_GDrive_response_reception_algorithm did not find the length of the payload. There may be problems with the Internet connection.");
                  response_buffer = b;  //So sendRequest will return 2.
                  break;
                }
              } else {
                TEB_debug_print("TEB_GDrive_response_reception_algorithm did not find the length of the payload. There may be problems with the Internet connection.");
                response_buffer = b;  //So sendRequest will return 2.
                break;
              }
            } else {
              b = response_buffer - 3;
            }
          }
        }
        if (brackets == 1) {
          if (response_buffer - b >= len) {
            response_buffer = b + len;
            TEB_debug_print("\nTEB_GDrive_response_reception_algorithm has correctly detected the final string of the http response.\n");
            break;
          }
        }
      }
      if (response_buffer_length == 0) {
        if (temp_i2 == 5) {
          if (brackets == 1) response_buffer = b - 4;
          else response_buffer = b;
          //So sendRequest will return 2.
        }
        TEB_debug_print("TEB_GDrive_response_reception_algorithm finished earlier than expected. Maybe response_buffer is too short.");
        break;
      }
      m = TEB_ms_elapsed();
    } else if (TEB_is_delay_over(m, response_delay_in_ms, 1) == 1) {
      if (temp_i2 == 5) {
        if (brackets == 1) response_buffer = b - 4;
        else response_buffer = b;
        //So sendRequest will return 2.
      }
      TEB_debug_print("TEB_Drive::response_reception_algorithm ended due to timeout. There may be problems with the Internet connection.");
      break;
    }
  }
  TEB_debug_function_end(0);
  return response_buffer;
}

#ifdef TEB_LibrarySettings_DEBUG_MODE
static void TEB_GDrive_function_end (const TEB_char* f_name, TEB_bool ok) {
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

TEB_small_int TEB_GDrive_test (const TEB_char* access_token) {
  TEB_debug_function_start("TEB_GDrive_test");

  char folder_id[70], file_id[70], gdoc_id[70];

  if (TEB_GDrive_create_metadata_only_file(access_token, "folder", NULL, "application/vnd.google-apps.folder", folder_id, NULL) == 1) TEB_GDrive_function_end("TEB_GDrive_create_metadata_only_file1", 1);
  else {
    TEB_GDrive_function_end("TEB_GDrive_create_metadata_only_file1", 0);
    return TEB_debug_function_end(-1);
  }
  TEB_debug_print("\nfolder_id is ");
  TEB_debug_print(folder_id);
  TEB_debug_print(".\n");
  if (TEB_GDrive_create_metadata_only_file(access_token, "file.txt", folder_id, NULL, file_id, NULL) == 1) TEB_GDrive_function_end("TEB_GDrive_create_metadata_only_file2", 1);
  else {
    TEB_GDrive_function_end("TEB_GDrive_create_metadata_only_file2", 0);
    return TEB_debug_function_end(-2);
  }
  TEB_debug_print("\nfile_id is ");
  TEB_debug_print(file_id);
  TEB_debug_print(".\n");
  if (TEB_GDrive_create_metadata_only_file(access_token, "Google Doc", NULL, "application/vnd.google-apps.document", gdoc_id, NULL) == 1) TEB_GDrive_function_end("TEB_GDrive_create_metadata_only_file3", 1);
  else {
    TEB_GDrive_function_end("TEB_GDrive_create_metadata_only_file3", 0);
    return TEB_debug_function_end(-3);
  }
  TEB_debug_print("\ngdoc_id is ");
  TEB_debug_print(gdoc_id);
  TEB_debug_print(".\n");

  if (TEB_GDrive_update_file_metadata(access_token, gdoc_id, "folder2", NULL, NULL, NULL) == 1) TEB_GDrive_function_end("TEB_GDrive_update_file_metadata1", 1);
  else {
    TEB_GDrive_function_end("TEB_GDrive_update_file_metadata1", 0);
    return TEB_debug_function_end(-4);
  }
  if (TEB_GDrive_update_file_metadata(access_token, gdoc_id, "Google Doc 2", folder_id, NULL, NULL) == 1) TEB_GDrive_function_end("TEB_GDrive_update_file_metadata2", 1);
  else {
    TEB_GDrive_function_end("TEB_GDrive_update_file_metadata2", 0);
    return TEB_debug_function_end(-5);
  }
  if (TEB_GDrive_update_file_metadata(access_token, file_id, NULL, NULL, folder_id, NULL) == 1) TEB_GDrive_function_end("TEB_GDrive_update_file_metadata3", 1);
  else {
    TEB_GDrive_function_end("TEB_GDrive_update_file_metadata3", 0);
    return TEB_debug_function_end(-6);
  }

  if (TEB_GDrive_update_file_content(access_token, file_id, "Hello!", "text/plain", NULL) == 1) TEB_GDrive_function_end("TEB_GDrive_update_file_content1", 1);
  else {
    TEB_GDrive_function_end("TEB_GDrive_update_file_content1", 0);
    return TEB_debug_function_end(-7);
  }
  if (TEB_GDrive_update_file_content(access_token, gdoc_id, "Hello!", "application/vnd.google-apps.document", NULL) == 1) TEB_GDrive_function_end("TEB_GDrive_update_file_content2", 1);
  else {
    TEB_GDrive_function_end("TEB_GDrive_update_file_content2", 0);
    return TEB_debug_function_end(-8);
  }

  char response_buffer[500];
  if (TEB_GDrive_get_file_content(access_token, file_id, response_buffer, NULL) == 1) TEB_GDrive_function_end("TEB_GDrive_get_file_content", 1);
  else {
    TEB_GDrive_function_end("TEB_GDrive_get_file_content", 0);
    return TEB_debug_function_end(-9);
  }
  TEB_debug_print("\nThe text contained in file.txt is: ");
  TEB_debug_print(response_buffer);
  TEB_debug_print(".\n");

  if (TEB_GDrive_export_google_document(access_token, gdoc_id, "text/plain", response_buffer, NULL) == 1) TEB_GDrive_function_end("TEB_GDrive_export_google_document", 1);
  else {
    TEB_GDrive_function_end("TEB_GDrive_export_google_document", 0);
    return TEB_debug_function_end(-10);
  }
  TEB_debug_print("\nThe text contained in Google Doc 2 is: ");
  TEB_debug_print(response_buffer);
  TEB_debug_print(".\n");

  char t1[200], t2[60];
  TEB_String_url_encoding2(t1, "name = 'file.txt' or name = 'Google Doc 2' or name = 'folder2'");
  TEB_String_url_encoding2(t2, "files/id,files/name");
  if (TEB_GDrive_search_file(access_token, t1, "name", t2, 3, NULL, response_buffer, NULL) == 1) TEB_GDrive_function_end("TEB_GDrive_search_file", 1);
  else {
    TEB_GDrive_function_end("TEB_GDrive_search_file", 0);
    return TEB_debug_function_end(-11);
  }
  TEB_debug_print("\nThe files found are:\n");
  TEB_debug_print(response_buffer);
  TEB_debug_print(".\n");

  if (TEB_GDrive_delete_file(access_token, folder_id, NULL) == 1) TEB_GDrive_function_end("TEB_GDrive_delete_file1", 1);
  else {
    TEB_GDrive_function_end("TEB_GDrive_delete_file1", 0);
    return TEB_debug_function_end(-12);
  }
  if (TEB_GDrive_delete_file(access_token, file_id, NULL) == 1) TEB_GDrive_function_end("TEB_GDrive_delete_file2", 1);
  else {
    TEB_GDrive_function_end("TEB_GDrive_delete_file2", 0);
    return TEB_debug_function_end(-13);
  }

  return TEB_debug_function_end(1);
}
#endif