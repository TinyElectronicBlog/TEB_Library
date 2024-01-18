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

#include "TEB_RemoteControlInterface.h"
#include "TEB_GDrive.h"
#include "../buffer/TEB_SplittableArray.h"
#include "../String/TEB_String.h"
#include "../Number/TEB_Number.h"
#include "TEB_OAuth2.h"

static const TEB_char TEB_RemoteControlInterface_str1[] = TEB_RemoteControlInterface_TINY_ELECTRONIC_BLOG_FOLDER_NAME;
static const TEB_char TEB_RemoteControlInterface_str2[] = "trashed%20%3D%20false%20and%20mimeType%20%3D%20%27application%2Fvnd.google-apps.folder%27%20and%20name%20%3D%20%27";  //"trashed = false and mimeType = 'application/vnd.google-apps.folder' and name = '";
static const TEB_char TEB_RemoteControlInterface_str3[] = "root";
static const TEB_char TEB_RemoteControlInterface_str4[] = "%27%20and%20%27";                           //"' and '";
static const TEB_char TEB_RemoteControlInterface_str5[] = "%27%20in%20parents";                        //"' in parents";
static const TEB_char TEB_RemoteControlInterface_str6[] = "text%2Fplain%27%20and%20name%20%3D%20%27";  //"text/plain' and name = '";
static const TEB_char TEB_RemoteControlInterface_str7[] = "File%20of%20device%20";                     //"File of device ";
static const TEB_char TEB_RemoteControlInterface_str8[] = "From%20dev.%20";                            //"From dev. ";
static const TEB_char TEB_RemoteControlInterface_str9[] = "%20ACK%20";                                 //" ACK ";
static const TEB_char TEB_RemoteControlInterface_str10[] = "files(id)";
static const TEB_char TEB_RemoteControlInterface_str11[] = "contains%20%27";                //"contains '";
static const TEB_char TEB_RemoteControlInterface_str12[] = "and%20not%20name%20";           //"and not name ";
static const TEB_char TEB_RemoteControlInterface_str13[] = "command%20Cus.%20value%20%27";  //"command Cus. value '";
static const TEB_char TEB_RemoteControlInterface_str14[] = "createdTime";
static const TEB_char TEB_RemoteControlInterface_str15[] = "To%20dev.%20";  //"To dev. ";
static const TEB_char TEB_RemoteControlInterface_str16[] = "To dev. ";
static const TEB_char TEB_RemoteControlInterface_str17[] = " command Cus. value ";
static const TEB_char TEB_RemoteControlInterface_str18[] = "File of device ";
static const TEB_char TEB_RemoteControlInterface_str19[] = "text/plain";
static const TEB_char TEB_RemoteControlInterface_str20[] = "From dev. ";
static const TEB_char TEB_RemoteControlInterface_str21[] = " ACK ";

TEB_small_int TEB_RemoteControlInterface_get_workspace_folder_id (const TEB_char* access_token,
                                                                 const TEB_char* workspace_folder_name,
                                                                 TEB_char* workspace_folder_id_buffer,
                                                                 TEB_char* function_buffer) {
  TEB_debug_function_start("TEB_RemoteControlInterface_get_workspace_folder_id");
  if (access_token == TEB_NULL_POINTER) TEB_fatal_error(128, "access_token cannot be NULL.", 2);
  if (workspace_folder_name == TEB_NULL_POINTER) TEB_fatal_error(129, "workspace_folder_name cannot be NULL.", 2);
  if (workspace_folder_id_buffer == TEB_NULL_POINTER) TEB_fatal_error(130, "workspace_folder_id_buffer cannot be NULL.", 2);
  TEB_char fields[TEB_String_strlen(TEB_RemoteControlInterface_str10) + 1];
  TEB_String_append2(fields, TEB_RemoteControlInterface_str10);
  TEB_char q[200];
  //recover the Tiny Electronic Blog folder 
  TEB_String_append2(TEB_String_append2(TEB_String_append2(TEB_String_append2(TEB_String_append2(q, TEB_RemoteControlInterface_str2), TEB_RemoteControlInterface_str1), TEB_RemoteControlInterface_str4), TEB_RemoteControlInterface_str3), TEB_RemoteControlInterface_str5);
  TEB_small_int r = TEB_GDrive_search_file(access_token, q, TEB_NULL_POINTER, fields, 2, TEB_NULL_POINTER, q, function_buffer);
  if (r != 1) return TEB_debug_function_end(-1);
  if (TEB_String_index_of2(q, ",") != TEB_NULL_POINTER) return TEB_debug_function_end(-2);  //there can be only one Tiny Electronic Blog folder
  const TEB_char* p = TEB_String_index_of2(q, "id");
  if (p == TEB_NULL_POINTER) return TEB_debug_function_end(1);
  p = p + 4;
  while (*p != '"') p = p + 1;
  p = p + 1;
  const TEB_char* p2 = TEB_String_index_of2(p, "\"");
  if (p2 == TEB_NULL_POINTER) return TEB_debug_function_end(-3);
  TEB_String_append(workspace_folder_id_buffer, p, p2);
  TEB_debug_print("\nDetected Tiny Electronic Blog folder id \"");
  TEB_debug_print(workspace_folder_id_buffer);
  TEB_debug_print("\".\n");
  //now workspace_folder_id_buffer is the Tiny Electronic Blog folder ID
  //recover the workspace folder ID
  TEB_String_append2(TEB_String_append2(TEB_String_append2(TEB_String_append2(TEB_String_append2(q, TEB_RemoteControlInterface_str2), workspace_folder_name), TEB_RemoteControlInterface_str4), workspace_folder_id_buffer), TEB_RemoteControlInterface_str5);
  r = TEB_GDrive_search_file(access_token, q, TEB_NULL_POINTER, fields, 2, TEB_NULL_POINTER, q, function_buffer);
  if (r != 1) return TEB_debug_function_end(-4);
  if (TEB_String_index_of2(q, ",") != TEB_NULL_POINTER) return TEB_debug_function_end(-5);  //there can be only one workspace folder
  p = TEB_String_index_of2(q, "id");
  if (p == TEB_NULL_POINTER) return TEB_debug_function_end(2);
  p = p + 4;
  while (*p != '"') p = p + 1;
  p = p + 1;
  p2 = TEB_String_index_of2(p, "\"");
  if (p2 == TEB_NULL_POINTER) return TEB_debug_function_end(-6);
  TEB_String_append(workspace_folder_id_buffer, p, p2);
  TEB_debug_print("\nDetected workspace folder id \"");
  TEB_debug_print(workspace_folder_id_buffer);
  TEB_debug_print("\".\n");
  return TEB_debug_function_end(0);
}

TEB_small_int TEB_RemoteControlInterface_new_device_file (const TEB_char* access_token,
                                                         const TEB_char* device_id,
                                                         const TEB_char* workspace_folder_id,
                                                         TEB_char* device_file_id_buffer,
                                                         TEB_char* function_buffer) {
  TEB_debug_function_start("TEB_RemoteControlInterface_new_device_file");
  if (access_token == TEB_NULL_POINTER) TEB_fatal_error(131, "access_token cannot be NULL.", 2);
  if (device_id == TEB_NULL_POINTER) TEB_fatal_error(132, "device_id cannot be NULL.", 2);
  if (workspace_folder_id == TEB_NULL_POINTER) TEB_fatal_error(133, "workspace_folder_id cannot be NULL.", 2);
  if (device_file_id_buffer == TEB_NULL_POINTER) TEB_fatal_error(134, "device_file_id_buffer cannot be NULL.", 2);
  TEB_char name[TEB_String_strlen(TEB_RemoteControlInterface_str18) + TEB_String_strlen(device_id) * 5 / 2 + 1];
  TEB_String_url_encoding2(name, device_id);
  TEB_small_int r = TEB_RemoteControlInterface_get_device_file_id(access_token, name, workspace_folder_id, device_file_id_buffer, function_buffer);
  switch (r) {
    case 0:
      return TEB_debug_function_end(1);
    case 1:
      break;
	case -2:
	  return TEB_debug_function_end(-2);
    default:
      return TEB_debug_function_end(-1);
  }
  TEB_char mime_type[TEB_String_strlen(TEB_RemoteControlInterface_str19) + 1];
  TEB_String_append2(TEB_String_append2(name, TEB_RemoteControlInterface_str18), device_id);
  TEB_String_append2(mime_type, TEB_RemoteControlInterface_str19);
  r = TEB_GDrive_create_metadata_only_file(access_token, name, workspace_folder_id, mime_type, device_file_id_buffer, function_buffer);
  if (r == 1) return TEB_debug_function_end(0);
  else return TEB_debug_function_end(-3);
}

TEB_small_int TEB_RemoteControlInterface_get_device_file_id (const TEB_char* access_token,
                                                            const TEB_char* device_id,
                                                            const TEB_char* workspace_folder_id,
                                                            TEB_char* device_file_id_buffer,
                                                            TEB_char* function_buffer) {
  TEB_debug_function_start("TEB_RemoteControlInterface_get_device_file_id");
  if (access_token == TEB_NULL_POINTER) TEB_fatal_error(135, "access_token cannot be NULL.", 2);
  if (device_id == TEB_NULL_POINTER) TEB_fatal_error(136, "device_id cannot be NULL.", 2);
  if (workspace_folder_id == TEB_NULL_POINTER) TEB_fatal_error(137, "workspace_folder_id cannot be NULL.", 2);
  if (device_file_id_buffer == TEB_NULL_POINTER) TEB_fatal_error(138, "device_file_id_buffer cannot be NULL.", 2);
  TEB_char fields[TEB_String_strlen(TEB_RemoteControlInterface_str10) + 1];
  TEB_String_append2(fields, TEB_RemoteControlInterface_str10);
  TEB_char q[200];
  //recover the device file ID
  TEB_String_append2(TEB_String_append2(TEB_String_append2(TEB_String_append2(TEB_String_append2(TEB_String_append2(TEB_String_append(q, TEB_RemoteControlInterface_str2, TEB_RemoteControlInterface_str2 + 50), TEB_RemoteControlInterface_str6), TEB_RemoteControlInterface_str7), device_id), TEB_RemoteControlInterface_str4), workspace_folder_id), TEB_RemoteControlInterface_str5);
  TEB_small_int r = TEB_GDrive_search_file(access_token, q, TEB_NULL_POINTER, fields, 2, TEB_NULL_POINTER, q, function_buffer);
  if (r != 1) return TEB_debug_function_end(-1);
  const TEB_char* p = TEB_String_index_of2(q, "id");
  if (p == TEB_NULL_POINTER) return TEB_debug_function_end(1);  
  TEB_bool multiple_id_files = 0;
  if (TEB_String_index_of2(q, ",") != TEB_NULL_POINTER) multiple_id_files = 1; //error, found multiple files id
  p = p + 4;
  while (*p != '"') p = p + 1;
  p = p + 1;
  const TEB_char* p2 = TEB_String_index_of2(p, "\"");
  if (p2 == TEB_NULL_POINTER) return TEB_debug_function_end(-3);
  TEB_String_append(device_file_id_buffer, p, p2);
  TEB_debug_print("\nDetected device file id \"");
  TEB_debug_print(device_file_id_buffer);
  TEB_debug_print("\".\n");
  if (multiple_id_files == 0) return TEB_debug_function_end(0);
  else return TEB_debug_function_end(-2); //there can be only one device file  
}

TEB_small_int TEB_RemoteControlInterface_get_device_file_text (const TEB_char* access_token,
                                                              const TEB_char* device_file_id,
                                                              TEB_char* text_buffer,
                                                              TEB_char* function_buffer) {
  TEB_debug_function_start("TEB_RemoteControlInterface_get_device_file_text");
  if (access_token == TEB_NULL_POINTER) TEB_fatal_error(139, "access_token cannot be NULL.", 2);
  if (device_file_id == TEB_NULL_POINTER) TEB_fatal_error(140, "device_file_id cannot be NULL.", 2);
  if (text_buffer == TEB_NULL_POINTER) TEB_fatal_error(141, "text_buffer cannot be NULL.", 2);
  TEB_small_int r = TEB_GDrive_get_file_content(access_token, device_file_id, text_buffer, function_buffer);
  return TEB_debug_function_end(r);
}

TEB_small_int TEB_RemoteControlInterface_update_device_file_text (const TEB_char* access_token,
                                                                 const TEB_char* device_file_id,
                                                                 const TEB_char* text,
                                                                 TEB_char* function_buffer) {
  TEB_debug_function_start("TEB_RemoteControlInterface_update_device_file_text");
  if (access_token == TEB_NULL_POINTER) TEB_fatal_error(142, "access_token cannot be NULL.", 2);
  if (device_file_id == TEB_NULL_POINTER) TEB_fatal_error(143, "device_file_id cannot be NULL.", 2);
  if (text == TEB_NULL_POINTER) TEB_fatal_error(144, "text cannot be NULL.", 2);
  TEB_char mime_type[TEB_String_strlen(TEB_RemoteControlInterface_str19) + 1];
  TEB_String_append2(mime_type, TEB_RemoteControlInterface_str19);
  TEB_small_int r = TEB_GDrive_update_file_content(access_token, device_file_id, text, mime_type, function_buffer);
  return TEB_debug_function_end(r);
}

TEB_small_int TEB_RemoteControlInterface_delete_device_file (const TEB_char* access_token,
                                                            const TEB_char* device_file_id,
                                                            TEB_char* function_buffer) {
  TEB_debug_function_start("TEB_RemoteControlInterface_delete_device_file");
  if (access_token == TEB_NULL_POINTER) TEB_fatal_error(145, "access_token cannot be NULL.", 2);
  if (device_file_id == TEB_NULL_POINTER) TEB_fatal_error(146, "device_file_id cannot be NULL.", 2);
  TEB_small_int r = TEB_GDrive_delete_file(access_token, device_file_id, function_buffer);
  return TEB_debug_function_end(r);
}

TEB_small_int TEB_RemoteControlInterface_is_there_ack (const TEB_char* access_token,
                                                      const TEB_char* device_id,
                                                      const TEB_char* workspace_folder_id,
                                                      TEB_char* function_buffer) {
  TEB_debug_function_start("TEB_RemoteControlInterface_is_there_ack");
  if (access_token == TEB_NULL_POINTER) TEB_fatal_error(147, "access_token cannot be NULL.", 2);
  if (device_id == TEB_NULL_POINTER) TEB_fatal_error(148, "device_id cannot be NULL.", 2);
  if (workspace_folder_id == TEB_NULL_POINTER) TEB_fatal_error(149, "workspace_folder_id cannot be NULL.", 2);
  TEB_char fields[TEB_String_strlen(TEB_RemoteControlInterface_str10) + 1];
  TEB_String_append2(fields, TEB_RemoteControlInterface_str10);
  TEB_char q[88 + TEB_String_strlen(TEB_RemoteControlInterface_str11) + TEB_String_strlen(TEB_RemoteControlInterface_str8) + TEB_String_strlen(device_id) + TEB_String_strlen(TEB_RemoteControlInterface_str9) + TEB_String_strlen(TEB_RemoteControlInterface_str4) + TEB_String_strlen(workspace_folder_id) + TEB_String_strlen(TEB_RemoteControlInterface_str5)];
  TEB_String_append2(TEB_String_append2(TEB_String_append2(TEB_String_append2(TEB_String_append2(TEB_String_append2(TEB_String_append2(TEB_String_append(TEB_String_append(q, TEB_RemoteControlInterface_str2, TEB_RemoteControlInterface_str2 + 50), TEB_RemoteControlInterface_str6, TEB_RemoteControlInterface_str6 + 31), TEB_RemoteControlInterface_str11), TEB_RemoteControlInterface_str8), device_id), TEB_RemoteControlInterface_str9), TEB_RemoteControlInterface_str4), workspace_folder_id), TEB_RemoteControlInterface_str5);
  TEB_small_int r = TEB_GDrive_search_file(access_token, q, TEB_NULL_POINTER, fields, 1, TEB_NULL_POINTER, q, function_buffer);
  if (r != 1) return TEB_debug_function_end(-1);
  if (TEB_String_index_of2(q, "id") == TEB_NULL_POINTER) return TEB_debug_function_end(1);
  else return TEB_debug_function_end(0);
}

TEB_small_int TEB_RemoteControlInterface_get_command (const TEB_char* access_token,
                                                     const TEB_char* device_id,
                                                     const TEB_char* workspace_folder_id,
                                                     TEB_char* command_name_buffer,
                                                     TEB_char* function_buffer) {
  TEB_debug_function_start("TEB_RemoteControlInterface_get_command");
  if (access_token == TEB_NULL_POINTER) TEB_fatal_error(150, "access_token cannot be NULL.", 2);
  if (device_id == TEB_NULL_POINTER) TEB_fatal_error(151, "device_id cannot be NULL.", 2);
  if (workspace_folder_id == TEB_NULL_POINTER) TEB_fatal_error(152, "workspace_folder_id cannot be NULL.", 2);
  if (command_name_buffer == TEB_NULL_POINTER) TEB_fatal_error(153, "command_name_buffer cannot be NULL.", 2);
  TEB_char fields[TEB_String_strlen(TEB_RemoteControlInterface_str10) + 3];
  TEB_String_append(fields, TEB_RemoteControlInterface_str10, TEB_RemoteControlInterface_str10 + 7);
  fields[6] = 'n';
  fields[7] = 'a';
  fields[8] = 'm';
  fields[9] = 'e';
  fields[10] = ')';
  fields[11] = '\0';
  TEB_char order_by[TEB_String_strlen(TEB_RemoteControlInterface_str14) + 1];
  TEB_String_append2(order_by, TEB_RemoteControlInterface_str14);
  TEB_char q[104 + TEB_String_strlen(TEB_RemoteControlInterface_str12) + TEB_String_strlen(TEB_RemoteControlInterface_str13) + 2 * TEB_String_strlen(TEB_RemoteControlInterface_str11) + TEB_String_strlen(TEB_RemoteControlInterface_str15) + TEB_String_strlen(device_id) * 3 + TEB_String_strlen(TEB_RemoteControlInterface_str4) + TEB_String_strlen(workspace_folder_id) + TEB_String_strlen(TEB_RemoteControlInterface_str5)];
  TEB_String_append2(TEB_String_append2(TEB_String_append2(TEB_String_append2(TEB_String_append2(TEB_String_append2(TEB_String_append2(TEB_String_append(TEB_String_append2(TEB_String_url_encoding2(TEB_String_append2(TEB_String_append2(TEB_String_append(TEB_String_append(q, TEB_RemoteControlInterface_str2, TEB_RemoteControlInterface_str2 + 50), TEB_RemoteControlInterface_str6, TEB_RemoteControlInterface_str6 + 31), TEB_RemoteControlInterface_str11), TEB_RemoteControlInterface_str15), device_id), "%20"), TEB_RemoteControlInterface_str13, TEB_RemoteControlInterface_str13 + 11), TEB_RemoteControlInterface_str4), workspace_folder_id), TEB_RemoteControlInterface_str5), "%20"), TEB_RemoteControlInterface_str12), TEB_RemoteControlInterface_str11), TEB_RemoteControlInterface_str13);
  TEB_small_int r = TEB_GDrive_search_file(access_token, q, order_by, fields, 1, TEB_NULL_POINTER, q, function_buffer);
  if (r != 1) return TEB_debug_function_end(-1);
  const TEB_char* p = TEB_String_index_of2(q, "name");
  if (p == TEB_NULL_POINTER) return TEB_debug_function_end(1);
  p = p + 6;
  while (*p != '"') p = p + 1;
  p = p + TEB_String_strlen(TEB_RemoteControlInterface_str16) + TEB_String_strlen(device_id) + 10;
  const TEB_char* p2 = TEB_String_index_of2(p, "\"");
  if (p2 == TEB_NULL_POINTER) return TEB_debug_function_end(-2);
  TEB_String_append(command_name_buffer, p, p2);
  TEB_debug_print("\nReceived command \"");
  TEB_debug_print(command_name_buffer);
  TEB_debug_print("\".\n");
  return TEB_debug_function_end(0);
}

TEB_small_int TEB_RemoteControlInterface_send_command_ack (const TEB_char* access_token,
                                                          const TEB_char* device_id,
                                                          const TEB_char* command_name,
                                                          const TEB_char* workspace_folder_id,
                                                          TEB_char* function_buffer) {
  TEB_debug_function_start("TEB_RemoteControlInterface_send_command_ack");
  if (access_token == TEB_NULL_POINTER) TEB_fatal_error(154, "access_token cannot be NULL.", 2);
  if (device_id == TEB_NULL_POINTER) TEB_fatal_error(155, "device_id cannot be NULL.", 2);
  if (command_name == TEB_NULL_POINTER) TEB_fatal_error(156, "command_name cannot be NULL.", 2);
  if (workspace_folder_id == TEB_NULL_POINTER) TEB_fatal_error(157, "workspace_folder_id cannot be NULL.", 2);
  TEB_char buffer[TEB_String_strlen(TEB_RemoteControlInterface_str20) + TEB_String_strlen(device_id) + TEB_String_strlen(TEB_RemoteControlInterface_str21) + TEB_String_strlen(command_name) + TEB_String_strlen(workspace_folder_id)];
  TEB_char* name = buffer;
  TEB_char* mime_type = TEB_String_append2(TEB_String_append2(TEB_String_append2(TEB_String_append2(name, TEB_RemoteControlInterface_str20), device_id), TEB_RemoteControlInterface_str21), command_name) + 1;
  TEB_String_append2(mime_type, TEB_RemoteControlInterface_str19);
  TEB_small_int r = TEB_GDrive_create_metadata_only_file(access_token, name, workspace_folder_id, mime_type, buffer, function_buffer);
  return TEB_debug_function_end(r);
}

TEB_small_int TEB_RemoteControlInterface_get_custom_command (const TEB_char* access_token,
                                                            const TEB_char* device_id,
                                                            const TEB_char* workspace_folder_id,
                                                            TEB_char* command_name_buffer,
                                                            TEB_char* function_buffer) {
  TEB_debug_function_start("TEB_RemoteControlInterface_get_custom_command");
  if (access_token == TEB_NULL_POINTER) TEB_fatal_error(158, "access_token cannot be NULL.", 2);
  if (device_id == TEB_NULL_POINTER) TEB_fatal_error(159, "device_id cannot be NULL.", 2);
  if (command_name_buffer == TEB_NULL_POINTER) TEB_fatal_error(160, "command_name_buffer cannot be NULL.", 2);
  if (workspace_folder_id == TEB_NULL_POINTER) TEB_fatal_error(161, "workspace_folder_id cannot be NULL.", 2);
  TEB_char fields[TEB_String_strlen(TEB_RemoteControlInterface_str10) + 3];
  TEB_String_append(fields, TEB_RemoteControlInterface_str10, TEB_RemoteControlInterface_str10 + 7);
  fields[6] = 'n';
  fields[7] = 'a';
  fields[8] = 'm';
  fields[9] = 'e';
  fields[10] = ')';
  fields[11] = '\0';
  TEB_char order_by[TEB_String_strlen(TEB_RemoteControlInterface_str14) + 1];
  TEB_String_append2(order_by, TEB_RemoteControlInterface_str14);
  TEB_char q[93 + TEB_String_strlen(TEB_RemoteControlInterface_str13) + TEB_String_strlen(TEB_RemoteControlInterface_str11) + TEB_String_strlen(TEB_RemoteControlInterface_str15) + TEB_String_strlen(device_id) * 3 + TEB_String_strlen(TEB_RemoteControlInterface_str4) + TEB_String_strlen(workspace_folder_id) + TEB_String_strlen(TEB_RemoteControlInterface_str5)];
  TEB_String_append2(TEB_String_append2(TEB_String_append2(TEB_String_append(TEB_String_append2(TEB_String_url_encoding2(TEB_String_append2(TEB_String_append2(TEB_String_append(TEB_String_append(q, TEB_RemoteControlInterface_str2, TEB_RemoteControlInterface_str2 + 50), TEB_RemoteControlInterface_str6, TEB_RemoteControlInterface_str6 + 31), TEB_RemoteControlInterface_str11), TEB_RemoteControlInterface_str15), device_id), "%20"), TEB_RemoteControlInterface_str13, TEB_RemoteControlInterface_str13 + 26), TEB_RemoteControlInterface_str4), workspace_folder_id), TEB_RemoteControlInterface_str5);
  TEB_small_int r = TEB_GDrive_search_file(access_token, q, order_by, fields, 1, TEB_NULL_POINTER, q, function_buffer);
  if (r != 1) return TEB_debug_function_end(-1);
  const TEB_char* p = TEB_String_index_of2(q, "name");
  if (p == TEB_NULL_POINTER) return TEB_debug_function_end(1);
  p = p + 6;  
  while (*p != '"') p = p + 1;  
  p = p + TEB_String_strlen(TEB_RemoteControlInterface_str16) + TEB_String_strlen(device_id) + TEB_String_strlen(TEB_RemoteControlInterface_str17) + 1;
  const TEB_char* p2 = TEB_String_index_of2(p, "\"");
  if (p2 == TEB_NULL_POINTER) return TEB_debug_function_end(-2);
  TEB_String_append(command_name_buffer, p, p2);
  TEB_debug_print("\nReceived custom command \"");
  TEB_debug_print(command_name_buffer);
  TEB_debug_print("\".\n");
  return TEB_debug_function_end(0);
}

TEB_small_int TEB_RemoteControlInterface_delete_custom_command (const TEB_char* access_token,
                                                               const TEB_char* device_id,
                                                               const TEB_char* command_name,
                                                               const TEB_char* workspace_folder_id,
                                                               TEB_char* function_buffer) {
  TEB_debug_function_start("TEB_RemoteControlInterface_delete_custom_command");
  if (access_token == TEB_NULL_POINTER) TEB_fatal_error(162, "access_token cannot be NULL.", 2);
  if (device_id == TEB_NULL_POINTER) TEB_fatal_error(163, "device_id cannot be NULL.", 2);
  if (command_name == TEB_NULL_POINTER) TEB_fatal_error(164, "command_name cannot be NULL.", 2);
  if (workspace_folder_id == TEB_NULL_POINTER) TEB_fatal_error(165, "workspace_folder_id cannot be NULL.", 2);
  TEB_char fields[TEB_String_strlen(TEB_RemoteControlInterface_str10) + 1];
  TEB_String_append2(fields, TEB_RemoteControlInterface_str10);
  TEB_char order_by[TEB_String_strlen(TEB_RemoteControlInterface_str14) + 1];
  TEB_String_append2(order_by, TEB_RemoteControlInterface_str14);
  TEB_char q[85 + TEB_String_strlen(TEB_RemoteControlInterface_str6) + TEB_String_strlen(TEB_RemoteControlInterface_str15) + TEB_String_strlen(device_id) + TEB_String_strlen(command_name) + TEB_String_strlen(TEB_RemoteControlInterface_str4) + TEB_String_strlen(workspace_folder_id) + TEB_String_strlen(TEB_RemoteControlInterface_str5)];
  TEB_small_int r;
  while (1) {
    TEB_String_append2(TEB_String_append2(TEB_String_append2(TEB_String_append2(TEB_String_append(TEB_String_append2(TEB_String_append2(TEB_String_append2(TEB_String_append2(TEB_String_append(q, TEB_RemoteControlInterface_str2, TEB_RemoteControlInterface_str2 + 50), TEB_RemoteControlInterface_str6), TEB_RemoteControlInterface_str15), device_id), "%20"), TEB_RemoteControlInterface_str13, TEB_RemoteControlInterface_str13 + 25), command_name), TEB_RemoteControlInterface_str4), workspace_folder_id), TEB_RemoteControlInterface_str5);
    r = TEB_GDrive_search_file(access_token, q, order_by, fields, 1, TEB_NULL_POINTER, q, function_buffer);
    if (r != 1) return TEB_debug_function_end(-1);
    const TEB_char* p = TEB_String_index_of2(q, "id");
    if (p == TEB_NULL_POINTER) break;
    p = p + 4;
    while (*p != '"') p = p + 1;
    p = p + 1;
    const TEB_char* p2 = TEB_String_index_of2(p, "\"");
    if (p2 == TEB_NULL_POINTER) return TEB_debug_function_end(-2);
    TEB_String_append(q, p, p2);
    //q now contains the id of the file to be deleted
	TEB_debug_print("\nThe id of the file to be deleted is \"");
	TEB_debug_print(q);
	TEB_debug_print("\".\n");
    if (TEB_GDrive_delete_file(access_token, q, function_buffer) != 1) return TEB_debug_function_end(-3);
  }
  return TEB_debug_function_end(1);
}

#ifdef TEB_LibrarySettings_DEBUG_MODE
static void TEB_RemoteControlInterface_function_end (const TEB_char* f_name, TEB_bool ok) {
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

TEB_small_int TEB_RemoteControlInterface_test (const TEB_char* access_token) {

  TEB_debug_function_start("TEB_RemoteControlInterface_test");

  TEB_char workspace_folder_id[50], device_file_id[50], text_buffer[75];
  TEB_char device_id[] = "TEST 1";
  TEB_char device_id_url[] = "TEST%201";

  TEB_small_int r = TEB_RemoteControlInterface_get_workspace_folder_id(access_token, "Workspace%20TEST", workspace_folder_id, TEB_NULL_POINTER);
  switch (r) {
    case 0:
      TEB_debug_print("\nworkspace_folder_id is ");
      TEB_debug_print(workspace_folder_id);
      TEB_debug_print(".\n");
      break;
    case 1:
      TEB_debug_print("\nThe Tiny Electronic Blog folder does not exist.\n");
      break;
    case 2:
      TEB_debug_print("\nThe workspace folder does not exist.\n");
      break;
  }
  if (r == 0) TEB_RemoteControlInterface_function_end("TEB_RemoteControlInterface_get_workspace_folder_id", 1);
  else {
    TEB_RemoteControlInterface_function_end("TEB_RemoteControlInterface_get_workspace_folder_id", 0);
    return TEB_debug_function_end(-1);
  }

  r = TEB_RemoteControlInterface_new_device_file(access_token, device_id, workspace_folder_id, device_file_id, TEB_NULL_POINTER);
  switch (r) {
    case 0:
      TEB_debug_print("\nGenerates a new device file with ID ");
      TEB_debug_print(device_file_id);
      TEB_debug_print(".\n");
      break;
    case 1:
      TEB_debug_print("\nThe device file already exists and has ID ");
      TEB_debug_print(device_file_id);
      TEB_debug_print(".\n");
      break;
  }
  if (r == 0 || r == 1) TEB_RemoteControlInterface_function_end("TEB_RemoteControlInterface_new_device_file", 1);
  else {
    TEB_RemoteControlInterface_function_end("TEB_RemoteControlInterface_new_device_file", 0);
    return TEB_debug_function_end(-2);
  }

  r = TEB_RemoteControlInterface_get_device_file_id(access_token, device_id_url, workspace_folder_id, device_file_id, TEB_NULL_POINTER);
  switch (r) {
    case 0:
      TEB_debug_print("\nThe device file ID is ");
      TEB_debug_print(device_file_id);
      TEB_debug_print(".\n");
      break;
    case 1:
      TEB_debug_print("\nThe device file does not exist.\n");
      break;
  }
  if (r == 0 || r == 1) TEB_RemoteControlInterface_function_end("TEB_RemoteControlInterface_get_device_file_id", 1);
  else {
    TEB_RemoteControlInterface_function_end("TEB_RemoteControlInterface_get_device_file_id", 0);
    return TEB_debug_function_end(-3);
  }

  r = TEB_RemoteControlInterface_update_device_file_text(access_token, device_file_id, "buttons: TEST, customizable value;\nvalues: TEST is X;\nHello!", TEB_NULL_POINTER);
  if (r == 1) TEB_debug_print("\nDevice file text updated.\n");
  if (r == 1) TEB_RemoteControlInterface_function_end("TEB_RemoteControlInterface_update_device_file_text", 1);
  else {
    TEB_RemoteControlInterface_function_end("TEB_RemoteControlInterface_update_device_file_text", 0);
    return TEB_debug_function_end(-4);
  }

  r = TEB_RemoteControlInterface_get_device_file_text(access_token, device_file_id, text_buffer, TEB_NULL_POINTER);
  if (r == 1) {
    TEB_debug_print("\nDevice file text is:\n");
    TEB_debug_print(text_buffer);
    TEB_debug_print("\n");
  }
  if (r == 1) TEB_RemoteControlInterface_function_end("TEB_RemoteControlInterface_get_device_file_text", 1);
  else {
    TEB_RemoteControlInterface_function_end("TEB_RemoteControlInterface_get_device_file_text", 0);
    return TEB_debug_function_end(-5);
  }

  r = TEB_RemoteControlInterface_delete_device_file(access_token, device_file_id, TEB_NULL_POINTER);
  if (r == 1) {
    TEB_debug_print("\nDevice file deleted.\n");
  }
  if (r == 1) TEB_RemoteControlInterface_function_end("TEB_RemoteControlInterface_delete_device_file", 1);
  else {
    TEB_RemoteControlInterface_function_end("TEB_RemoteControlInterface_delete_device_file", 0);
    return TEB_debug_function_end(-6);
  }

  r = TEB_RemoteControlInterface_is_there_ack(access_token, device_id_url, workspace_folder_id, TEB_NULL_POINTER);
  switch (r) {
    case 0:
      TEB_debug_print("\nAt least one ACK detected.\n");
      break;
    case 1:
      TEB_debug_print("\nNo ACK detected.\n");
      break;
  }
  if (r == 0 || r == 1) TEB_RemoteControlInterface_function_end("TEB_RemoteControlInterface_is_there_ack", 1);
  else {
    TEB_RemoteControlInterface_function_end("TEB_RemoteControlInterface_is_there_ack", 0);
    return TEB_debug_function_end(-7);
  }

  r = TEB_RemoteControlInterface_get_command(access_token, device_id, workspace_folder_id, text_buffer, TEB_NULL_POINTER);
  switch (r) {
    case 0:
      TEB_debug_print("\nRecovered the command with name '");
      TEB_debug_print(text_buffer);
      TEB_debug_print("'.\n");
      break;
    case 1:
      TEB_debug_print("\nNo command detected.\n");
      break;
  }
  if (r == 0) {
    if (TEB_RemoteControlInterface_send_command_ack(access_token, device_id, text_buffer, workspace_folder_id, TEB_NULL_POINTER) == 1) {
      TEB_debug_print("\nACK sent.\n'");
      TEB_RemoteControlInterface_function_end("TEB_RemoteControlInterface_send_command_ack", 1);
    } else {
      TEB_debug_print("\nsendCommandACK failed.\n");
      TEB_RemoteControlInterface_function_end("TEB_RemoteControlInterface_send_command_ack", 0);
      return TEB_debug_function_end(-8);
    }
  }
  if (r == 0 || r == 1) TEB_RemoteControlInterface_function_end("TEB_RemoteControlInterface_get_command", 1);
  else {
    TEB_RemoteControlInterface_function_end("TEB_RemoteControlInterface_get_command", 0);
    return TEB_debug_function_end(-9);
  }

  r = TEB_RemoteControlInterface_get_custom_command(access_token, device_id, workspace_folder_id, device_file_id, TEB_NULL_POINTER);
  switch (r) {
    case 0:
      TEB_debug_print("\nRecovered the custom command with name '");
      TEB_debug_print(device_file_id);
      TEB_debug_print("'.\n");
      TEB_String_url_encoding2(text_buffer, device_file_id);
      break;
    case 1:
      TEB_debug_print("\nNo custom command detected.\n");
      break;
  }
  if (r == 0) {
    if (TEB_RemoteControlInterface_delete_custom_command(access_token, device_id_url, text_buffer, workspace_folder_id, TEB_NULL_POINTER) == 1) {
      TEB_debug_print("\nCustom command deleted.\n");
      TEB_RemoteControlInterface_function_end("TEB_RemoteControlInterface_delete_custom_command", 1);
    } else {
      TEB_debug_print("\ndeleteCustomCommand failed.\n");
      TEB_RemoteControlInterface_function_end("TEB_RemoteControlInterface_delete_custom_command", 0);
      return TEB_debug_function_end(-10);
    }
  }
  if (r == 0 || r == 1) TEB_RemoteControlInterface_function_end("TEB_RemoteControlInterface_get_custom_command", 1);
  else {
    TEB_RemoteControlInterface_function_end("TEB_RemoteControlInterface_get_custom_command", 0);
    return TEB_debug_function_end(-11);
  }

  return TEB_debug_function_end(1);
}
#endif