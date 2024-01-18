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

#include "TEB_RenameLibraryFunctions.h"

const struct TEB_RenameLibraryFunctions teb = {

  .string = {
    .strlen = TEB_String_strlen,
    .equals = TEB_String_equals,
    .equals2 = TEB_String_equals2,
    .equals3 = TEB_String_equals3,
    .indexOf = TEB_String_index_of,
    .indexOf2 = TEB_String_index_of2,
    .indexOf3 = TEB_String_index_of3,
    .lastIndexOf = TEB_String_last_index_of,
    .lastIndexOf2 = TEB_String_last_index_of2,
    .lastIndexOf3 = TEB_String_last_index_of3,
    .append = TEB_String_append,
    .append2 = TEB_String_append2,
    .appendEnd = TEB_String_append_end,
    .appendEnd2 = TEB_String_append_end2,
    .intChar = TEB_String_int_char,
    .intStr = TEB_String_int_str,
    .invIntStr = TEB_String_inv_int_str,
    .urlEncodingChar = TEB_String_url_encoding_char,
    .urlEncoding = TEB_String_url_encoding,
    .urlEncoding2 = TEB_String_url_encoding2 
  },
  .number = {
    .numberOfDigits = TEB_Number_number_of_digits,
    .isInt = TEB_Number_is_int,
    .isInt2 = TEB_Number_is_int2,
    .exp10 = TEB_Number_exp10,
    .charDigit = TEB_Number_char_digit,
    .strInt = TEB_Number_str_int,
    .strInt2 = TEB_Number_str_int2,
  },
  .time = { 
	.manage = {
              .firstWeekdayYear = TEB_TimeManagement_first_weekday_year,
              .isLeapYear = TEB_TimeManagement_is_leap_year,
              .daysOfMonth = TEB_TimeManagement_days_of_month,
              .timeToEpoch = TEB_TimeManagement_time_to_epoch,
              .epochToTime = TEB_TimeManagement_epoch_to_time,
              .weekdayFromEpoch = TEB_TimeManagement_weekday_from_epoch,
              .weekdayFromDate = TEB_TimeManagement_weekday_from_date,
              .isTimePassed = TEB_TimeManagement_is_time_passed,
              .isDstTime = TEB_TimeManagement_is_dst_time,
              .isDstEpoch = TEB_TimeManagement_is_dst_epoch,
              .getDstEpoch = TEB_TimeManagement_get_dst_epoch,
              .utcToLocalEpoch = TEB_TimeManagement_utc_to_local_epoch,
              .localToUtcEpoch = TEB_TimeManagement_local_to_utc_epoch,
              .strDate = TEB_TimeManagement_str_date,
              .strTime = TEB_TimeManagement_str_time,
              .strIntY = TEB_TimeManagement_str_int_y,
              .strIntMon = TEB_TimeManagement_str_int_mon,
              .strIntD = TEB_TimeManagement_str_int_d,
              .strIntH = TEB_TimeManagement_str_int_h,
              .strIntMin = TEB_TimeManagement_str_int_min,
              .strIntS = TEB_TimeManagement_str_int_s,
              .httpDateToEpoch = TEB_TimeManagement_http_date_to_epoch,
    },
	.clock = {
		.defaultInit = TEB_Clock_struct_default_init,
		.setDefaultInitialYearEpoch = TEB_Clock_set_default_initial_year_epoch,
		.setInitialYearEpoch = TEB_Clock_set_initial_year_epoch,
		.setEpoch = TEB_Clock_set_epoch,
		.setTime = TEB_Clock_set_time,
		.setAutomaticUpdate = TEB_Clock_set_automatic_update,
		.epoch = TEB_Clock_get_epoch,
		.time = TEB_Clock_get_time,
		.initialYearEpoch = TEB_Clock_get_initial_year_epoch,
		.initialWeekdayEpoch = TEB_Clock_get_initial_weekday_epoch,
		.s = TEB_Clock_get_s,
		.min = TEB_Clock_get_min,
		.h = TEB_Clock_get_h,
		.d = TEB_Clock_get_d,
		.mon = TEB_Clock_get_mon,
		.y = TEB_Clock_get_y,
		.w = TEB_Clock_get_weekday,
		.isEpochSet = TEB_Clock_is_epoch_set,
		.automaticUpdate = TEB_Clock_get_automatic_update,
		.adjust = TEB_Clock_adjust
	},
    .tz = {
		.init = TEB_TimeZoneDST_struct_init,
		.setEpoch = TEB_TimeZoneDST_set_epoch,
		.setTime = TEB_TimeZoneDST_set_time,
		.epoch = TEB_TimeZoneDST_get_epoch,
		.time = TEB_TimeZoneDST_get_time,
		.s = TEB_TimeZoneDST_get_s,
		.min = TEB_TimeZoneDST_get_min,
		.h = TEB_TimeZoneDST_get_h,
		.d = TEB_TimeZoneDST_get_d,
		.mon = TEB_TimeZoneDST_get_mon,
		.y = TEB_TimeZoneDST_get_y,
		.w = TEB_TimeZoneDST_get_weekday 
	}
  },
  .buffer = { 
     .abstract = { 
	    .newArray = TEB_AbstractArray_new_array,
		.deleteArray = TEB_AbstractArray_delete_array,
		.pointer = TEB_AbstractArray_get_pointer,
		.sizeofOneElement = TEB_AbstractArray_get_sizeof_one_element,
		.length = TEB_AbstractArray_get_length,
		.allocationMode = TEB_AbstractArray_get_allocation_mode
	 },
     .splittable = { 
	    .newArray = TEB_SplittableArray_new_array,
		.deleteLastArray = TEB_SplittableArray_delete_last_array,
		.add = TEB_SplittableArray_add_elements,
		.addEnd = TEB_SplittableArray_add_elements_end,
		.split = TEB_SplittableArray_split_array,
		.lastElement = TEB_SplittableArray_last_element_pointer,
		.release = TEB_SplittableArray_release_elements,
		.reset = TEB_SplittableArray_reset_array,
		.freeElements = TEB_SplittableArray_number_of_free_elements,
		.occupiedElements = TEB_SplittableArray_number_of_occupied_elements,
		.numberOfAllocatedArrays = TEB_SplittableArray_number_of_allocated_arrays
	 } 
  },
  .google = { 
     .oauth2 = { 
	    .login = TEB_OAuth2_login,
		.relogin = TEB_OAuth2_relogin,
		.logout = TEB_OAuth2_logout,
		.responseReceptionAlgorithm = TEB_OAuth2_response_reception_algorithm,
		.handleServerResponse = TEB_OAuth2_handle_server_response,
		.standardStep3ShowUserCode = TEB_OAuth2_standard_oauth2_step3_display_user_code
		},
     .drive = { 
	    .createMetadataOnlyFile = TEB_GDrive_create_metadata_only_file,
	    .updateFileMetadata = TEB_GDrive_update_file_metadata,
		.updateFileContent = TEB_GDrive_update_file_content,
		.searchFile = TEB_GDrive_search_file,
		.getFileContent = TEB_GDrive_get_file_content,
		.deleteFile = TEB_GDrive_delete_file,
		.exportGoogleDocument = TEB_GDrive_export_google_document,
		.responseReceptionAlgorithm = TEB_GDrive_response_reception_algorithm 
	 },
     .rci = {
		 .getWorkspaceFolderID = TEB_RemoteControlInterface_get_workspace_folder_id,
		 .newDeviceFile = TEB_RemoteControlInterface_new_device_file,
		 .getDeviceFileID = TEB_RemoteControlInterface_get_device_file_id,
		 .getDeviceFileText = TEB_RemoteControlInterface_get_device_file_text,
		 .updateDeviceFileText = TEB_RemoteControlInterface_update_device_file_text,
		 .deleteDeviceFile = TEB_RemoteControlInterface_delete_device_file,
		 .isThereACK = TEB_RemoteControlInterface_is_there_ack,
		 .getCommand = TEB_RemoteControlInterface_get_command,
		 .sendCommandACK = TEB_RemoteControlInterface_send_command_ack,
		 .getCustomCommand = TEB_RemoteControlInterface_get_custom_command,
		 .deleteCustomCommand = TEB_RemoteControlInterface_delete_custom_command 
	} 
  },
  .device = { 
     .debugPrint = TEB_debug_print,
	 .debugPrintChar = TEB_debug_print_char,
	 .debugPrintInt = TEB_debug_print_int,
	 .debugFunctionStart = TEB_debug_function_start,
	 .debugFunctionEnd = TEB_debug_function_end,
	 .debugUndefinedFunction = TEB_debug_undefined_function,
	 .print = TEB_print,
	 .printChar = TEB_print_char,
	 .printInt = TEB_print_int,
	 .error = TEB_error,
	 .fatalError = TEB_fatal_error,
	 .init = TEB_device_init,
	 .millis = TEB_ms_elapsed,
	 .isDelayOver = TEB_is_delay_over,
	 .delay = TEB_delay,
	 .reboot = TEB_reboot_device,
	 .freeHeap = TEB_free_heap,
	 .largestHeapFreeBlock = TEB_largest_heap_free_block,
	 .ledOn = TEB_led_on,
	 .ledOff = TEB_led_off,
	 .ledBlink = TEB_led_blink,
	 .wifiConnect = TEB_wifi_connect,
	 .wifiDisconnect = TEB_wifi_disconnect,
	 .wifiCheck = TEB_wifi_check,
	 .displayPrint = TEB_display_print,
	 .memoryWrite = TEB_memory_write,
	 .memoryRead = TEB_memory_read,
	 .httpConnect = TEB_http_connect,
	 .httpSend = TEB_http_send,
	 .httpReceive = TEB_http_receive,
	 .httpStop = TEB_http_stop,
	 .httpSendRequest = TEB_http_send_request,
	 .httpStandardSendRequest = TEB_http_standard_send_request,
	 .httpStandardResponseReceptionAlgorithm = TEB_http_standard_response_reception_algorithm,
	 .customCommand = TEB_custom_command
  }
#ifdef TEB_LibrarySettings_DEBUG_MODE
  ,
  .generalTest = TEB_RenameLibraryFunctions_test
#endif

};

#ifdef TEB_LibrarySettings_DEBUG_MODE
static TEB_small_int TEB_RenameLibraryFunctions_test_print(const TEB_char* function_name, TEB_small_int result) {
  const char* s1 = " concluded ";
  const char* s2 = "successfully.";
  const char* s3 = "with errors.";
  TEB_char d[TEB_String_strlen(s1) + TEB_String_strlen(s2) + TEB_String_strlen(s3) + TEB_String_strlen(function_name) + 1];
  TEB_debug_print("\n\n");
  TEB_debug_print(function_name);
  TEB_debug_print(" concluded ");
  if (result == 1) {
    TEB_debug_print("without errors.\n");
    TEB_String_append2(TEB_String_append2(TEB_String_append2(d, function_name), s1), s2);
    TEB_display_print(1, d, 1, 1);
    TEB_delay(5000, 1);
    return result;
  }
  TEB_debug_print("with error ");
  if (result < 0) {
    TEB_debug_print("-");
    result = result * -1;
    TEB_debug_print_int(result);
    result = result * -1;
  } else TEB_debug_print_int(result);
  TEB_debug_print(".");
  TEB_String_append2(TEB_String_append2(TEB_String_append2(d, function_name), s1), s3);
  TEB_display_print(1, d, 1, 1);
  TEB_delay(5000, 1);
  return result;
}

TEB_small_int TEB_RenameLibraryFunctions_test (void* TEB_device_initialization_parameter, const TEB_char* wifi_ssid, const TEB_char* wifi_password, TEB_medium_u_int mode) {
  if (TEB_RenameLibraryFunctions_test_print ("TEB_DeviceInterfaces_test1", TEB_DeviceInterfaces_test1(wifi_ssid, wifi_password)) != 1) { return -1; }

  if (TEB_RenameLibraryFunctions_test_print ("TEB_Number_test", TEB_Number_test()) != 1) { return -2; }

  if (TEB_RenameLibraryFunctions_test_print ("TEB_String_test", TEB_String_test()) != 1) { return -3; }

  if (TEB_RenameLibraryFunctions_test_print ("TEB_AbstractArray_test", TEB_AbstractArray_test()) != 1) { return -4; }

  if (TEB_RenameLibraryFunctions_test_print ("TEB_SplittableArray_test", TEB_SplittableArray_test()) != 1) { return -5; }

  if (TEB_RenameLibraryFunctions_test_print ("TEB_TimeManagement_test", TEB_TimeManagement_test()) != 1) { return -6; }

  if (TEB_RenameLibraryFunctions_test_print ("TEB_Clock_test", TEB_Clock_test()) != 1) { return -7; }

  if (TEB_RenameLibraryFunctions_test_print ("TEB_TimeZoneDST_test", TEB_TimeZoneDST_test()) != 1) { return -8; }

  TEB_char access_token_buffer[500];
  if (TEB_RenameLibraryFunctions_test_print ("TEB_OAuth2_test1", TEB_OAuth2_test1(access_token_buffer)) != 1) { return -9; }

  if (TEB_RenameLibraryFunctions_test_print ("TEB_GDrive_test", TEB_GDrive_test(access_token_buffer)) != 1) { return -10; }

  if (TEB_RenameLibraryFunctions_test_print ("TEB_RemoteControlInterface_test", TEB_RemoteControlInterface_test(access_token_buffer)) != 1) { return -11; }

  if (TEB_RenameLibraryFunctions_test_print ("TEB_OAuth2_test2", TEB_OAuth2_test2(access_token_buffer)) != 1) { return -12; }

  if (TEB_RenameLibraryFunctions_test_print ("TEB_DeviceInterfaces_test2", TEB_DeviceInterfaces_test2()) != 1) { return -13; }

  //Error because the device should have rebooted or already returned -13.
  return -14;
}
#endif
