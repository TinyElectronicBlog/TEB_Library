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

#include "TEB_DeviceInterfaces.h"
#include "../String/TEB_String.h"
#include "../number/TEB_Number.h"



#if TEB_LibrarySettings_SELECTED_DEVICE_ID == 1  //WINDOWS PC*******************************************************************************************************************************************************************************************************************************************************************************

void TEB_debug_print(const TEB_char* str) {
#if TEB_LibrarySettings_DEBUG_MODE == 1 || TEB_LibrarySettings_DEBUG_MODE == 3
  TEB_print(str, 1);
#endif
}

void TEB_debug_print_char(const TEB_char c) {
#if TEB_LibrarySettings_DEBUG_MODE == 1 || TEB_LibrarySettings_DEBUG_MODE == 3
  TEB_print_char(c, 1);
#endif
}

void TEB_debug_print_int(TEB_big_u_int n) {
#if TEB_LibrarySettings_DEBUG_MODE == 1 || TEB_LibrarySettings_DEBUG_MODE == 3
  TEB_print_int(n, 1);
#endif
}

void TEB_debug_function_start(const TEB_char* function_name) {
}

TEB_small_int TEB_debug_function_end(TEB_small_int r) {
  return r;
}

void TEB_debug_undefined_function(const TEB_char* function_name) {
#if TEB_LibrarySettings_DEBUG_MODE == 2 || TEB_LibrarySettings_DEBUG_MODE == 3
  TEB_print("\n\n   Warning: executed undefined function with name \"", 1);
  TEB_print(function_name, 1);
  TEB_print("\".\n\n", 1);
#endif
}

TEB_small_int TEB_print(const TEB_char* str, TEB_medium_u_int mode) {
  return 1;
}

TEB_small_int TEB_print_char(const TEB_char c, TEB_medium_u_int mode) {
  return 1;
}

TEB_small_int TEB_print_int(TEB_big_u_int n, TEB_medium_u_int mode) {
  return 1;
}

TEB_small_int TEB_error(TEB_big_u_int number,
                        const TEB_char* text,
                        TEB_time_t duration_in_ms,
                        TEB_medium_u_int mode) {
  return 1;
}

void TEB_fatal_error(TEB_big_u_int number,
                     const TEB_char* text,
                     TEB_medium_u_int mode) {
}

TEB_small_int TEB_device_init(void* parameters, TEB_medium_u_int mode) {
  return 1;
}

TEB_time_t TEB_ms_elapsed() {
  return 0;
}

TEB_bool TEB_is_delay_over(TEB_time_t initial_instant_returned_by_TEB_ms_elapsed,
                           TEB_time_t interval_duration_in_milliseconds,
                           TEB_medium_u_int mode) {
  return 1;
}

TEB_small_int TEB_delay(TEB_time_t milliseconds_waiting_time, TEB_medium_u_int mode) {
  return 1;
}

void TEB_reboot_device(TEB_medium_u_int mode) {
}

TEB_size_t TEB_free_heap() {
  return 1;
}

TEB_size_t TEB_largest_heap_free_block() {
  return 1;
}

TEB_small_int TEB_led_on(TEB_medium_u_int led_id, TEB_medium_u_int mode) {
  return 1;
}

TEB_small_int TEB_led_off(TEB_medium_u_int led_id, TEB_medium_u_int mode) {
  return 1;
}

TEB_small_int TEB_led_blink(TEB_medium_u_int led_id,
                            TEB_time_t on_ms,
                            TEB_time_t off_ms,
                            TEB_medium_u_int mode) {
  return 1;
}

TEB_small_int TEB_wifi_connect(TEB_small_u_int wifi_interface_id,
                               const TEB_char* ssid,
                               const TEB_char* password,
                               TEB_medium_u_int timeout_in_ms,
                               TEB_medium_u_int mode) {
  return 1;
}

TEB_small_int TEB_wifi_disconnect(TEB_small_u_int wifi_interface_id, TEB_medium_u_int mode) {
  return 1;
}

TEB_small_int TEB_wifi_check(TEB_small_u_int wifi_interface_id, TEB_medium_u_int mode) {
  return 1;
}

TEB_small_int TEB_display_print(TEB_small_u_int display_id,
                                const TEB_char* text,
                                TEB_medium_u_int text_size,
                                TEB_medium_u_int mode) {
  return 1;
}

TEB_small_int TEB_memory_write(TEB_medium_u_int memory_id,
                               void* elements_to_write,
                               TEB_size_t number_of_elements_to_write,
                               TEB_size_t sizeof_one_element,
                               TEB_medium_u_int mode) {
  return 1;
}

TEB_small_int TEB_memory_read(TEB_medium_u_int memory_id,
                              void* elements_to_read_buffer,
                              TEB_size_t number_of_elements_to_read,
                              TEB_size_t sizeof_one_element,
                              TEB_medium_u_int mode) {
  return 1;
}

TEB_small_int TEB_http_connect(const TEB_char* server_address,
                               TEB_medium_u_int server_port,
                               TEB_bool use_ssl,
                               const TEB_char* root_ca,
                               TEB_time_t connection_timeout_in_ms,
                               TEB_medium_u_int mode) {
}

TEB_small_int TEB_http_send(const TEB_char* request_text,
                            TEB_size_t request_text_length,
                            TEB_medium_u_int mode) {
  return 1;
}

TEB_big_int TEB_http_receive(TEB_char* response_buffer,
                             TEB_big_int response_buffer_length,
                             TEB_medium_u_int mode) {
  return 1;
}

TEB_small_int TEB_http_stop(TEB_medium_u_int mode) {
  return 1;
}

TEB_small_int TEB_http_send_request(struct TEB_http_request* http_request,
                                    struct TEB_http_response* http_response,
                                    TEB_char* response_buffer,
                                    TEB_size_t response_buffer_length,
                                    TEB_char* (*http_response_reception_algorithm)(TEB_char* response_buffer, TEB_size_t response_buffer_length, TEB_time_t response_delay_in_ms, void* additional_parameters, TEB_medium_u_int mode),
                                    void* additional_parameters_of_http_response_reception_algorithm,
                                    TEB_medium_u_int mode) {
  return 1;
}

TEB_small_int TEB_http_standard_send_request(struct TEB_http_request* http_request,
                                             struct TEB_http_response* http_response,
                                             TEB_char* response_buffer,
                                             TEB_size_t response_buffer_length,
                                             TEB_medium_u_int mode) {
  return 1;
}

TEB_char* TEB_http_standard_response_reception_algorithm(TEB_char* response_buffer,
                                                         TEB_size_t response_buffer_length,
                                                         TEB_time_t response_delay_in_ms,
                                                         void* additional_parameters,
                                                         TEB_medium_u_int mode) {
  return TEB_NULL_POINTER;
}

TEB_small_int TEB_custom_command (TEB_medium_u_int command_id,
                                 const void* optional_parameters,
                                 void* optional_buffer,
                                 TEB_size_t optional_buffer_length) {
}

#ifdef TEB_LibrarySettings_DEBUG_MODE
TEB_small_int TEB_DeviceInterfaces_test1(const TEB_char* wifi_ssid, const TEB_char* wifi_password) {
  return 1;
}

TEB_small_int TEB_DeviceInterfaces_test2 () {
  return 1;
}
#endif

#endif





#if TEB_LibrarySettings_SELECTED_DEVICE_ID == 2 && TEB_LibrarySettings_SELECTED_PROGRAMMING_LANGUAGE == 2 //ESP32 with C++*******************************************************************************************************************************************************************************************************************************************************************************

void TEB_debug_print (const TEB_char* str) {
#if TEB_LibrarySettings_DEBUG_MODE == 1 || TEB_LibrarySettings_DEBUG_MODE == 3
  TEB_print(str, 1);
#endif
}

void TEB_debug_print_char (const TEB_char c) {
#if TEB_LibrarySettings_DEBUG_MODE == 1 || TEB_LibrarySettings_DEBUG_MODE == 3
  TEB_print_char(c, 1);
#endif
}

void TEB_debug_print_int (TEB_big_u_int n) {
#if TEB_LibrarySettings_DEBUG_MODE == 1 || TEB_LibrarySettings_DEBUG_MODE == 3
  TEB_print_int(n, 1);
#endif
}

#if TEB_LibrarySettings_DEBUG_MODE == 2 || TEB_LibrarySettings_DEBUG_MODE == 3
static TEB_big_u_int TEB_debug_level = 0;
#endif
void TEB_debug_function_start (const TEB_char* function_name) {
#if TEB_LibrarySettings_DEBUG_MODE == 2 || TEB_LibrarySettings_DEBUG_MODE == 3
  TEB_print("\n\n", 1);
  for (TEB_big_u_int i = 0; i < TEB_debug_level; i = i + 1) {
    TEB_print_char('\t', 1);
  }
  TEB_print_char('L', 1);
  TEB_print_int(TEB_debug_level, 1);
  TEB_print(" - Executing ", 1);
  TEB_print(function_name, 1);
  TEB_print(".\n\n", 1);
  TEB_debug_level = TEB_debug_level + 1;
#endif
}

TEB_small_int TEB_debug_function_end (TEB_small_int r) {
#if TEB_LibrarySettings_DEBUG_MODE == 2 || TEB_LibrarySettings_DEBUG_MODE == 3
  TEB_print("\n\n", 1);
  TEB_debug_level = TEB_debug_level - 1;
  for (TEB_big_u_int i = 0; i < TEB_debug_level; i = i + 1) {
    TEB_print_char('\t', 1);
  }
  TEB_print_char('L', 1);
  TEB_print_int(TEB_debug_level, 1);
  TEB_print(" - End.\n\n", 1);
#endif
  return r;
}

void TEB_debug_undefined_function (const TEB_char* function_name) {
#if TEB_LibrarySettings_DEBUG_MODE == 2 || TEB_LibrarySettings_DEBUG_MODE == 3
  TEB_print("\n\n   Warning: executed undefined function with name \"", 1);
  TEB_print(function_name, 1);
  TEB_print("\".\n\n", 1);
#endif
}

TEB_small_int TEB_print (const TEB_char* str, TEB_medium_u_int mode) {
#ifdef TEB_LibrarySettings_DEBUG_MODE
  if (str == TEB_NULL_POINTER) {
    Serial.println("Error: unable to execute TEB_print with parameter str null. Program execution stopped.");
    while (1)
      ;
  } else
#endif
    if (mode == 1)
    Serial.print(str);
#ifdef TEB_LibrarySettings_DEBUG_MODE
  else {
    Serial.println("Error: executed TEB_print with an unallowed value for the mode parameter. Program execution stopped.");
    while (1)
      ;
  }
#endif
  return 1;
}

TEB_small_int TEB_print_char (const TEB_char c, TEB_medium_u_int mode) {
  if (mode == 1) Serial.print(c);
#ifdef TEB_LibrarySettings_DEBUG_MODE
  else {
    Serial.println("Error: executed TEB_print_char with an unallowed value for the mode parameter. Program execution stopped.");
    while (1)
      ;
  }
#endif
  return 1;
}

TEB_small_int TEB_print_int (TEB_big_u_int n, TEB_medium_u_int mode) {
  if (mode == 1) Serial.print(n);
#ifdef TEB_LibrarySettings_DEBUG_MODE
  else {
    Serial.println("Error: executed TEB_print_char with an unallowed value for the mode parameter. Program execution stopped.");
    while (1)
      ;
  }
#endif
  return 1;
}

TEB_small_int TEB_error (TEB_big_u_int number,
					     const TEB_char* text, 
						 TEB_time_t duration_in_ms, 
						 TEB_medium_u_int mode) {
  TEB_debug_function_start("TEB_error");
  if (text == TEB_NULL_POINTER) TEB_fatal_error(26, "text cannot be NULL.", 2);
  if (mode != 1 && mode != 2 && mode != 0) TEB_fatal_error(27, "Value not allowed for mode.", 2);
  if (duration_in_ms < 0 || duration_in_ms > TEB_MILLISECONDS_ELAPSED_SINCE_START_MAX_VALUE) TEB_fatal_error(28, "Value not allowed for duration_in_ms.", 2);
  TEB_debug_print("\n\n**********\nERROR ");
  TEB_debug_print_int(number);
  TEB_debug_print(": ");
  TEB_debug_print(text);
  TEB_debug_print("\n----------");
#ifdef TEB_LibrarySettings_ENABLE_ERRORS
  if (mode == 1) {
    TEB_char t[TEB_String_strlen(TEB_error_str0) + TEB_String_strlen(TEB_error_str1) + TEB_String_strlen(text) + TEB_Number_number_of_digits(number) + 1];
    TEB_String_append2(TEB_String_append2(TEB_String_int_str(number, TEB_String_append2(t, TEB_error_str0)), TEB_error_str1), text);
    TEB_display_print(1, t, 1, 1);
    TEB_time_t now = TEB_ms_elapsed();
    while (TEB_is_delay_over(now, duration_in_ms, 1) == 0) {
      TEB_led_blink(TEB_ESP32_ONBOARD_LED_ID, 300, 300, 1);
    }
  }
#endif
  return TEB_debug_function_end(1);
}

void TEB_fatal_error (TEB_big_u_int number, 
					  const TEB_char* text, 
					  TEB_medium_u_int mode) {
  TEB_debug_function_start("TEB_fatal_error");
  TEB_bool block = 0;
  if (mode != 1 && mode != 2) {
    TEB_debug_print("\n\n**********\nFATAL ERROR 2: Value not allowed for mode.");
    TEB_debug_print("\n----------");
    TEB_debug_print("\n\nPROGRAM EXECUTION IS NOW INTERRUPTED. FIX YOUR CODE AND RUN IT AGAIN!\n");
#if TEB_LibrarySettings_DEBUG_MODE == 1 || TEB_LibrarySettings_DEBUG_MODE == 3
    block = 1;
#endif
#ifdef TEB_LibrarySettings_ENABLE_FATAL_ERRORS
    TEB_char t[TEB_String_strlen(TEB_fatal_error_str0) + TEB_String_strlen(TEB_fatal_error_str1) + TEB_String_strlen(TEB_fatal_error_str2) + TEB_String_strlen(TEB_fatal_error_str4) + 2];
    TEB_String_append2(TEB_String_append2(TEB_String_append2(TEB_String_append2(TEB_String_append2(t, TEB_fatal_error_str0), "2"), TEB_fatal_error_str1), TEB_fatal_error_str4), TEB_fatal_error_str2);
    TEB_display_print(1, t, 1, 1);
    block = 1;
#endif
  } else if (text == TEB_NULL_POINTER) {
    TEB_debug_print("\n\n**********\nFATAL ERROR 1: text cannot be NULL.");
    TEB_debug_print("\n----------");
    TEB_debug_print("\n\nPROGRAM EXECUTION IS NOW INTERRUPTED. FIX YOUR CODE AND RUN IT AGAIN!\n");
#if TEB_LibrarySettings_DEBUG_MODE == 1 || TEB_LibrarySettings_DEBUG_MODE == 3
    block = 1;
#endif
#ifdef TEB_LibrarySettings_ENABLE_FATAL_ERRORS
    TEB_char t[TEB_String_strlen(TEB_fatal_error_str0) + TEB_String_strlen(TEB_fatal_error_str1) + TEB_String_strlen(TEB_fatal_error_str2) + TEB_String_strlen(TEB_fatal_error_str3) + 2];
    TEB_String_append2(TEB_String_append2(TEB_String_append2(TEB_String_append2(TEB_String_append2(t, TEB_fatal_error_str0), "1"), TEB_fatal_error_str1), TEB_fatal_error_str3), TEB_fatal_error_str2);
    TEB_display_print(1, t, 1, 1);
    block = 1;
#endif
  } else {
    TEB_debug_print("\n\n**********\nFATAL ERROR ");
    TEB_debug_print_int(number);
    TEB_debug_print(": ");
    TEB_debug_print(text);
    TEB_debug_print("\n----------");
    TEB_debug_print("\n\nPROGRAM EXECUTION IS NOW INTERRUPTED. FIX YOUR CODE AND RUN IT AGAIN!\n");
#if TEB_LibrarySettings_DEBUG_MODE == 1 || TEB_LibrarySettings_DEBUG_MODE == 3
    block = 1;
#endif
#ifdef TEB_LibrarySettings_ENABLE_FATAL_ERRORS
    if (mode == 1) {
      TEB_char t[TEB_String_strlen(TEB_fatal_error_str0) + TEB_String_strlen(TEB_fatal_error_str1) + TEB_String_strlen(TEB_fatal_error_str2) + TEB_String_strlen(text) + TEB_Number_number_of_digits(number) + 1];
      TEB_String_append2(TEB_String_append2(TEB_String_append2(TEB_String_int_str(number, TEB_String_append2(t, TEB_fatal_error_str0)), TEB_fatal_error_str1), text), TEB_fatal_error_str2);
      TEB_display_print(1, t, 1, 1);
      block = 1;
    }
#endif
  }
  if (block != 0 && number != 0) {
    while (1)
      ;
  }
  TEB_debug_function_end(0);
}

static TEB_bool TEB_device_initialized = 0;
TEB_small_int TEB_device_init (void* parameters, TEB_medium_u_int mode) {
  if (mode == 1) {
    if (TEB_device_initialized == 0) {
      Serial.begin(TEB_ESP32_BAUD_RATE);
      while (!Serial)
        ;
      TEB_delay(300, 1);
      //Serial must be initialized before using Serial.print
      TEB_debug_function_start("TEB_device_init");
      pinMode(TEB_ESP32_ONBOARD_LED_PIN, OUTPUT);
      TEB_device_initialized = 1;
      return TEB_debug_function_end(1);
    } else {
      TEB_debug_function_start("TEB_device_init");
      return TEB_debug_function_end(1);
    }
  }
#ifdef TEB_LibrarySettings_DEBUG_MODE
  else {
    Serial.println("Error: executed TEB_device_init with an unallowed value for the mode parameter. Program execution stopped.");
    while (1)
      ;
  }
#endif
  return -1;
}

TEB_time_t TEB_ms_elapsed () {
  TEB_debug_function_start("TEB_ms_elapsed");
  TEB_time_t r = esp_timer_get_time() / 1000;  //esp_timer_get_time() returns the value in micros
  TEB_debug_function_end(0);
  return r;
}

TEB_bool TEB_is_delay_over (TEB_time_t initial_instant_returned_by_TEB_ms_elapsed,
						         TEB_time_t interval_duration_in_milliseconds,
								 TEB_medium_u_int mode) {
  TEB_debug_function_start("TEB_is_delay_over");
  if (initial_instant_returned_by_TEB_ms_elapsed < 0 || initial_instant_returned_by_TEB_ms_elapsed > TEB_MILLISECONDS_ELAPSED_SINCE_START_MAX_VALUE) TEB_fatal_error(30, "Value not allowed for initial_instant_returned_by_TEB_ms_elapsed.", 2);
  if (interval_duration_in_milliseconds < 0 || interval_duration_in_milliseconds > TEB_MILLISECONDS_ELAPSED_SINCE_START_MAX_VALUE) TEB_fatal_error(31, "Value not allowed for interval_duration_in_milliseconds.", 2);
  if (mode != 1) TEB_fatal_error(32, "Value not allowed for mode.", 2);
  TEB_time_t now = TEB_ms_elapsed();
  if (now >= initial_instant_returned_by_TEB_ms_elapsed) {
    if (now - initial_instant_returned_by_TEB_ms_elapsed >= interval_duration_in_milliseconds) return TEB_debug_function_end(1);
    else return TEB_debug_function_end(0);
  } else {  //If the variable for measuring time has been reset
    if ((TEB_MILLISECONDS_ELAPSED_SINCE_START_MAX_VALUE - initial_instant_returned_by_TEB_ms_elapsed) + now + 1 >= interval_duration_in_milliseconds) return TEB_debug_function_end(1);
    else return TEB_debug_function_end(0);
  }
}

TEB_small_int TEB_delay (TEB_time_t milliseconds_waiting_time, TEB_medium_u_int mode) {
  TEB_debug_function_start("TEB_delay");
  if (mode != 1) TEB_fatal_error(33, "Value not allowed for mode.", 2);
  if (milliseconds_waiting_time < 0 || milliseconds_waiting_time > TEB_MILLISECONDS_ELAPSED_SINCE_START_MAX_VALUE) TEB_fatal_error(34, "Value not allowed for milliseconds_waiting_time.", 2);
  TEB_time_t now = TEB_ms_elapsed();
  while (TEB_is_delay_over(now, milliseconds_waiting_time, 1) == 0) ;
  return TEB_debug_function_end(1);
}

void TEB_reboot_device (TEB_medium_u_int mode) {
  TEB_debug_function_start("TEB_reboot_device");
  if (mode != 1) TEB_fatal_error(35, "Value not allowed for mode.", 2);
  ESP.restart();
  TEB_debug_function_end(0);
}

TEB_size_t TEB_free_heap () {
  TEB_debug_function_start("TEB_free_heap");
  TEB_size_t r = heap_caps_get_free_size(MALLOC_CAP_8BIT);
  TEB_debug_function_end(0);
  return r;
}

TEB_size_t TEB_largest_heap_free_block () {
  TEB_debug_function_start("TEB_largest_heap_free_block");
  TEB_size_t r = heap_caps_get_largest_free_block(MALLOC_CAP_8BIT);
  TEB_debug_function_end(0);
  return r;
}

TEB_small_int TEB_led_on (TEB_medium_u_int led_id, TEB_medium_u_int mode) {
  TEB_debug_function_start("TEB_led_on");
  if (mode != 1) TEB_fatal_error(36, "Value not allowed for mode.", 2);
  switch (led_id) {
    case TEB_ESP32_ONBOARD_LED_ID:
      digitalWrite(TEB_ESP32_ONBOARD_LED_PIN, HIGH);
      return TEB_debug_function_end(1);
  }
  TEB_fatal_error(37, "Wrong led id.", 2);
  return TEB_debug_function_end(-1);
}

TEB_small_int TEB_led_off (TEB_medium_u_int led_id, TEB_medium_u_int mode) {
  TEB_debug_function_start("TEB_led_off");
  if (mode != 1) TEB_fatal_error(38, "Value not allowed for mode.", 2);
  switch (TEB_ESP32_ONBOARD_LED_ID) {
    case 1:
      digitalWrite(TEB_ESP32_ONBOARD_LED_PIN, LOW);
      return TEB_debug_function_end(1);
  }
  TEB_fatal_error(39, "Wrong led id.", 2);
  return TEB_debug_function_end(-1);
}

TEB_small_int TEB_led_blink (TEB_medium_u_int led_id,
					         TEB_time_t on_ms, 
							 TEB_time_t off_ms, 
							 TEB_medium_u_int mode) {
  TEB_debug_function_start("TEB_led_blink");
  if (on_ms < 0 || on_ms > TEB_MILLISECONDS_ELAPSED_SINCE_START_MAX_VALUE) TEB_fatal_error(40, "Value not allowed for on_ms.", 2);
  if (off_ms < 0 || off_ms > TEB_MILLISECONDS_ELAPSED_SINCE_START_MAX_VALUE) TEB_fatal_error(41, "Value not allowed for off_ms.", 2);
  if (mode != 1) TEB_fatal_error(42, "Value not allowed for mode.", 2);
  TEB_small_int r = 1;
  if (TEB_led_on(led_id, 1) != 1) r = -1;
  if (TEB_delay(on_ms, 1) != 1) r = -2;
  if (TEB_led_off(led_id, 1) != 1) r = -3;
  if (TEB_delay(off_ms, 1) != 1) r = r - 4;
  return TEB_debug_function_end(r);
}

TEB_small_int TEB_wifi_connect (TEB_small_u_int wifi_interface_id,
								const TEB_char* ssid,
								const TEB_char* password,
								TEB_medium_u_int timeout_in_ms,
								TEB_medium_u_int mode) {
  TEB_debug_function_start("TEB_wifi_connect");
  if (mode != 1) TEB_fatal_error(43, "Value not allowed for mode.", 2);
  if (timeout_in_ms < 0 || timeout_in_ms > TEB_MILLISECONDS_ELAPSED_SINCE_START_MAX_VALUE) TEB_fatal_error(44, "Value not allowed for timeout_in_ms.", 2);
  if (ssid == TEB_NULL_POINTER) TEB_fatal_error(45, "ssid cannot be NULL.", 2);
  if (password == TEB_NULL_POINTER) TEB_fatal_error(46, "password cannot be NULL.", 2);
  if (wifi_interface_id == 1) {
    TEB_time_t now = TEB_ms_elapsed();
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      if (TEB_is_delay_over(now, timeout_in_ms, 1) != 0) {
        TEB_debug_print("WiFi connection failed within timeout_in_ms s.");
        return TEB_debug_function_end(-1);
      }
    }
    TEB_debug_print("\nSuccessful WiFI connection with IP address ");
    TEB_debug_print_int(WiFi.localIP()[0]);
    TEB_debug_print(".");
    TEB_debug_print_int(WiFi.localIP()[1]);
    TEB_debug_print(".");
    TEB_debug_print_int(WiFi.localIP()[2]);
    TEB_debug_print(".");
    TEB_debug_print_int(WiFi.localIP()[3]);
    TEB_debug_print(".\n");
    return TEB_debug_function_end(1);
  }
  TEB_fatal_error(47, "Wrong WiFi interface id.", 2);
  return TEB_debug_function_end(-2);
}

TEB_small_int TEB_wifi_disconnect (TEB_small_u_int wifi_interface_id, TEB_medium_u_int mode) {
  TEB_debug_function_start("TEB_wifi_disconnect");
  if (mode != 1) TEB_fatal_error(48, "Value not allowed for mode.", 2);
  switch (wifi_interface_id) {
    case 1:
      WiFi.disconnect();
      return TEB_debug_function_end(1);
  }
  TEB_fatal_error(49, "Wrong WiFi interface id.", 2);
  return TEB_debug_function_end(-1);
}

TEB_small_int TEB_wifi_check (TEB_small_u_int wifi_interface_id, TEB_medium_u_int mode) {
  TEB_debug_function_start("TEB_wifi_check");
  if (mode != 1) TEB_fatal_error(50, "Value not allowed for mode.", 2);
  switch (wifi_interface_id) {
    case 1:
      if (WiFi.status() == WL_CONNECTED) {
        TEB_debug_print("\nThe device is connected to the Internet.\n");
        return TEB_debug_function_end(1);
      } else {
        TEB_debug_print("\nThe device is not connected to the Internet.\n");
        return TEB_debug_function_end(0);
      }
  }
  TEB_fatal_error(51, "Wrong WiFi interface id.", 2);
  return TEB_debug_function_end(-1);
}

static OakOLED TEB_display_id1;
static TEB_bool TEB_display_id1_not_initialized = 1;
static void TEB_display_id1_initialize () {
  if (TEB_display_id1_not_initialized != 0) {
    TEB_display_id1.begin();
    TEB_delay(50, 1);
    TEB_display_id1_not_initialized = 0;
  }
}

TEB_small_int TEB_display_print (TEB_small_u_int display_id, 
							     const TEB_char* text, 
								 TEB_medium_u_int text_size, 
								 TEB_medium_u_int mode) {
  TEB_debug_function_start("TEB_display_print");
  if (text == TEB_NULL_POINTER) TEB_fatal_error(52, "text cannot be NULL.", 2);
  if (mode != 1) TEB_fatal_error(53, "Value not allowed for mode.", 2);
  if (text_size == 0) TEB_fatal_error(54, "Value not allowed for text_size.", 2);
  switch (display_id) {
    case 1:
      TEB_display_id1_initialize();
      TEB_display_id1.clearDisplay();
      TEB_display_id1.setTextSize(text_size);
      TEB_display_id1.setCursor(0, 0);
      TEB_display_id1.print(text);
      TEB_display_id1.display();
      TEB_debug_print("\nShown on the display \"");
      TEB_debug_print(text);
      TEB_debug_print("\".\n");
      return TEB_debug_function_end(1);
  }
  TEB_fatal_error(55, "Wrong display id.", 2);
  return TEB_debug_function_end(-1);
}

TEB_small_int TEB_memory_write (TEB_medium_u_int memory_id,
                               void* elements_to_write,
                               TEB_size_t number_of_elements_to_write,
                               TEB_size_t sizeof_one_element,
                               TEB_medium_u_int mode) {
  TEB_debug_function_start("TEB_memory_write");
  if (elements_to_write == TEB_NULL_POINTER) TEB_fatal_error(56, "elements_to_write cannot be NULL.", 2);
  if (mode != 1) TEB_fatal_error(57, "Value not allowed for mode.", 2);
  if (number_of_elements_to_write == 0) TEB_fatal_error(58, "Value not allowed for number_of_elements_to_write.", 2);
  if (sizeof_one_element == 0) TEB_fatal_error(59, "Value not allowed for sizeof_one_element.", 2);
  switch (memory_id) {
    case 1:  //INTERNAL EEPROM OF ESP32
      if (number_of_elements_to_write * sizeof_one_element > 512) {
        TEB_fatal_error(60, "It is not possible to write more than 512 bytes into the EEPROM of ESP32.", 2);
        return TEB_debug_function_end(-1);
      }
      if (!EEPROM.begin(512)) {
        TEB_debug_print("Failed to initialize EEPROM");
        return TEB_debug_function_end(-2);
      }
      TEB_data_type_to_copy_buffer i = 0, l = (TEB_data_type_to_copy_buffer)number_of_elements_to_write * sizeof_one_element;
      TEB_data_type_to_copy_buffer* value = (TEB_data_type_to_copy_buffer*)elements_to_write;
      TEB_bool w = 0, ok = 0;
      while (i < l) {
        if (EEPROM.read(i) != *value) {
          EEPROM.write(i, *value);
          w = 1;
        }
        value = value + 1;
        i = i + 1;
      }
      if (w != 0) ok = EEPROM.commit();
      if (w == 0 || ok != 0) {
        TEB_debug_print("\nWritten ");
        TEB_debug_print_int(l);
        TEB_debug_print(" bytes in the EEPROM.\n");
        EEPROM.end();
        return TEB_debug_function_end(1);
      } else {
        EEPROM.end();
        TEB_debug_print("Error while writing EEPROM.");
        return TEB_debug_function_end(-3);
      }
      break;
  }
  TEB_fatal_error(61, "Wrong memory id.", 2);
  return TEB_debug_function_end(-4);
}

TEB_small_int TEB_memory_read (TEB_medium_u_int memory_id,
                              void* elements_to_read_buffer,
                              TEB_size_t number_of_elements_to_read,
                              TEB_size_t sizeof_one_element,
                              TEB_medium_u_int mode) {
  TEB_debug_function_start("TEB_memory_read");
  if (elements_to_read_buffer == TEB_NULL_POINTER) TEB_fatal_error(62, "elements_to_read_buffer cannot be NULL.", 2);
  if (mode != 1) TEB_fatal_error(63, "Value not allowed for mode.", 2);
  if (number_of_elements_to_read == 0) TEB_fatal_error(64, "Value not allowed for number_of_elements_to_read.", 2);
  if (sizeof_one_element == 0) TEB_fatal_error(65, "Value not allowed for sizeof_one_element.", 2);
  switch (memory_id) {
    case 1:  //INTERNAL EEPROM OF ESP32
      if (number_of_elements_to_read * sizeof_one_element > 512) {
        TEB_fatal_error(66, "It is not possible to read more than 512 bytes into the EEPROM of ESP32.", 2);
        return TEB_debug_function_end(-1);
      }
      if (!EEPROM.begin(512)) {
        TEB_debug_print("Failed to initialize EEPROM");
        return TEB_debug_function_end(-2);
      }
      TEB_data_type_to_copy_buffer i = 0, l = (TEB_data_type_to_copy_buffer)number_of_elements_to_read * sizeof_one_element;
      TEB_data_type_to_copy_buffer* buffer = (TEB_data_type_to_copy_buffer*)elements_to_read_buffer;
      while (i < l) {
        *buffer = EEPROM.read(i);
        buffer = buffer + 1;
        i = i + 1;
      }
      TEB_debug_print("\nRead ");
      TEB_debug_print_int(l);
      TEB_debug_print(" bytes in the EEPROM.\n");
      EEPROM.end();
      return TEB_debug_function_end(1);
  }
  TEB_fatal_error(67, "Wrong memory id.", 2);
  return TEB_debug_function_end(-3);
}

static TEB_small_int TEB_http_connection_mode = 0;
static TEB_bool TEB_http_use_ssl = 0;
static WiFiClientSecure TEB_http_ssl_client;
static WiFiClient TEB_http_client;

TEB_small_int TEB_http_connect (const TEB_char* server_address,
                               TEB_medium_u_int server_port,
                               TEB_bool use_ssl,
                               const TEB_char* root_ca,
                               TEB_time_t connection_timeout_in_ms,
                               TEB_medium_u_int mode) {
  TEB_debug_function_start("TEB_http_connect");
  if (server_address == TEB_NULL_POINTER) TEB_fatal_error(68, "server_address cannot be NULL.", 2);
  if (connection_timeout_in_ms < 0 || connection_timeout_in_ms > TEB_MILLISECONDS_ELAPSED_SINCE_START_MAX_VALUE) TEB_fatal_error(69, "Value not allowed for connection_timeout_in_ms.", 2);
  if (root_ca == TEB_NULL_POINTER) TEB_fatal_error(70, "root_ca cannot be NULL.", 2);
  if (mode != 1) TEB_fatal_error(71, "Value not allowed for mode.", 2);
  if (TEB_http_connection_mode != 0) {
    TEB_fatal_error(72, "You need to run TEB_http_connect before you can reuse this function.", 2);
    return TEB_debug_function_end(-1);
  }
  TEB_small_int r;
  if (use_ssl != 0) {
    if (TEB_String_strlen(root_ca) != 0) {
      TEB_debug_print("\nSet the root_ca:\n");
      TEB_debug_print(root_ca);
      TEB_debug_print("- END ROOT_CA -\n");
      TEB_http_ssl_client.setCACert(root_ca);
    } else {
      TEB_debug_print("\nroot_ca not set.");
      TEB_http_ssl_client.setInsecure();  //skip verification of rootCA
    }
  }
  if (WiFi.status() != WL_CONNECTED) {
    TEB_debug_print("Connection to server failed due to no Internet connection.");
    if (use_ssl != 0) TEB_http_ssl_client.stop();
    else TEB_http_client.stop();
    return TEB_debug_function_end(-2);
  }
  if (use_ssl != 0) r = TEB_http_ssl_client.connect(server_address, server_port, connection_timeout_in_ms);
  else r = TEB_http_client.connect(server_address, server_port, connection_timeout_in_ms);
  if (!r) {
    if (use_ssl != 0) TEB_http_ssl_client.stop();
    else TEB_http_client.stop();
    TEB_debug_print("Connection to server failed.");
    return TEB_debug_function_end(-3);
  }
  TEB_debug_print("\nConnected to ");
  TEB_debug_print(server_address);
  TEB_debug_print(" via port ");
  TEB_debug_print_int(server_port);
  TEB_debug_print(".\n");
  TEB_http_connection_mode = 1;
  TEB_http_use_ssl = use_ssl;
  return TEB_debug_function_end(1);
}

TEB_small_int TEB_http_send (const TEB_char* request_text,
						     TEB_size_t request_text_length, 
							 TEB_medium_u_int mode) {
  TEB_debug_function_start("TEB_http_send");
  if (request_text == TEB_NULL_POINTER) TEB_fatal_error(73, "request_text cannot be NULL.", 2);
  if (request_text_length == 0) TEB_fatal_error(74, "Value not allowed for request_text_length.", 2);
  if (mode != 1) TEB_fatal_error(75, "Value not allowed for mode.", 2);
  if (TEB_http_connection_mode != 1 && TEB_http_connection_mode != 2) {
    TEB_fatal_error(76, "Before using this function you need to connect to a server using TEB_http_send.", 2);
    return TEB_debug_function_end(-1);
  }
  TEB_small_u_int err;
  TEB_size_t res;
  TEB_debug_print("\nSending: ");
  while (1) {
    if (TEB_http_use_ssl != 0) res = TEB_http_ssl_client.write((const uint8_t*)request_text, request_text_length);
    else res = TEB_http_client.write((const uint8_t*)request_text, request_text_length);
#ifdef TEB_LibrarySettings_DEBUG_MODE
    TEB_size_t i = 0;
    while (i < res) {
      if (request_text[i] == '\n') TEB_debug_print("\\n");
      else if (request_text[i] == '\r') TEB_debug_print("\\r");
      else {
        TEB_debug_print_char(request_text[i]);
      }
      i = i + 1;
    }
    TEB_debug_print("\n");
#endif
    if (res == request_text_length) break;
    if (res == 0) {
      err = err + 1;
      if (err == 5) {
        if (TEB_http_use_ssl != 0) TEB_http_ssl_client.stop();
        else TEB_http_client.stop();
        TEB_http_connection_mode = 0;
        TEB_debug_print("HTTP request sending failed. The server has been disconnected.");
        return TEB_debug_function_end(-2);
      }
    } else {
      request_text = request_text + res;
      request_text_length = request_text_length - res;
      err = 0;
    }
    TEB_fatal_error(77, "Unexpected fatal error.", 2);
  }
  TEB_http_connection_mode = 2;
  return TEB_debug_function_end(1);
}

TEB_big_int TEB_http_receive (TEB_char* response_buffer,
							  TEB_big_int response_buffer_length, 
							  TEB_medium_u_int mode) {
  TEB_debug_function_start("TEB_http_receive");
  if (response_buffer == TEB_NULL_POINTER) TEB_fatal_error(78, "response_buffer cannot be NULL.", 2);
  if (response_buffer_length == 0) TEB_fatal_error(79, "Value not allowed for response_buffer_length.", 2);
  if (mode != 1) TEB_fatal_error(80, "Value not allowed for mode.", 2);
  TEB_big_int r;
  if (TEB_http_connection_mode != 1 && TEB_http_connection_mode != 2) {
    TEB_fatal_error(81, "Before using this function you must at least connect to a server TEB_http_connect.", 2);
    return TEB_debug_function_end(-1);
  } else {
    if (TEB_http_use_ssl != 0) r = TEB_http_ssl_client.read((uint8_t*)response_buffer, response_buffer_length);
    else r = TEB_http_client.read((uint8_t*)response_buffer, response_buffer_length);
    if (r == -1) {
      return TEB_debug_function_end(0);
    } else {
#ifdef TEB_LibrarySettings_DEBUG_MODE
      TEB_debug_print("\nReceived: ");
      TEB_big_int i = 0;
      while (i < r) {
        if (response_buffer[i] == '\r') TEB_debug_print("\\r");
        else if (response_buffer[i] == '\n') TEB_debug_print("\\n");
        else {
          TEB_debug_print_char(response_buffer[i]);
        }
        i = i + 1;
      }
      TEB_debug_print("\n");
#endif
      TEB_debug_function_end(0);
      return r;
    }
  }
}

TEB_small_int TEB_http_stop (TEB_medium_u_int mode) {
  TEB_debug_function_start("TEB_http_stop");
  if (mode != 1) TEB_fatal_error(82, "Value not allowed for mode.", 2);
  if (TEB_http_connection_mode != 1 && TEB_http_connection_mode != 2) {
    TEB_fatal_error(83, "Before using this function you need to execute TEB_http_connect, send, TEB_http_send and/or TEB_http_receive.", 2);
    return TEB_debug_function_end(-1);
  }
  if (TEB_http_use_ssl != 0) TEB_http_ssl_client.stop();
  else TEB_http_client.stop();
  TEB_http_connection_mode = 0;
  TEB_debug_print("\nConnection with server closed.\n");
  return TEB_debug_function_end(1);
}

TEB_small_int TEB_http_send_request (struct TEB_http_request* http_request,
                                    struct TEB_http_response* http_response,
                                    TEB_char* response_buffer,
                                    TEB_size_t response_buffer_length,
                                    TEB_char* (*http_response_reception_algorithm)(TEB_char* response_buffer, TEB_size_t response_buffer_length, TEB_time_t response_delay_in_ms, void* additional_parameters, TEB_medium_u_int mode),
                                    void* additional_parameters_of_http_response_reception_algorithm,
                                    TEB_medium_u_int mode) {
  TEB_debug_function_start("TEB_http_send_request");
  if (http_request == TEB_NULL_POINTER) TEB_fatal_error(84, "http_request cannot be NULL.", 2);
  if (http_response == TEB_NULL_POINTER) TEB_fatal_error(85, "http_response cannot be NULL.", 2);
  if (response_buffer == TEB_NULL_POINTER) TEB_fatal_error(86, "response_buffer cannot be NULL.", 2);
  if (response_buffer_length == 0) TEB_fatal_error(87, "response_buffer_length must be >= 1.", 2);
  if (http_response_reception_algorithm == TEB_NULL_POINTER) TEB_fatal_error(88, "http_response_reception_algorithm cannot be NULL.", 2);
  if (mode != 1) TEB_fatal_error(89, "Value not allowed for mode.", 2);
  if (http_request->connection_timeout_in_ms < 0 || http_request->connection_timeout_in_ms > TEB_MILLISECONDS_ELAPSED_SINCE_START_MAX_VALUE) TEB_fatal_error(90, "Value not allowed for http_request->connection_timeout_in_ms.", 2);
  if (http_request->response_delay_in_ms < 0 || http_request->response_delay_in_ms > TEB_MILLISECONDS_ELAPSED_SINCE_START_MAX_VALUE) TEB_fatal_error(91, "Value not allowed for http_request->response_delay_in_ms.", 2);
  if (http_request->request_text == TEB_NULL_POINTER) TEB_fatal_error(92, "http_request->request_text cannot be NULL.", 2);
  if (http_request->server_address == TEB_NULL_POINTER) TEB_fatal_error(93, "http_request->server_address cannot be NULL.", 2);
  if (http_request->root_ca == TEB_NULL_POINTER) TEB_fatal_error(94, "http_request->root_ca cannot be NULL.", 2);
  TEB_debug_print("\nTry to connect to ");
  TEB_debug_print(http_request->server_address);
  TEB_debug_print(" and send the request:\n");
#ifdef TEB_LibrarySettings_DEBUG_MODE
  const TEB_char* b1 = http_request->request_text;
  while (*b1 != '\0') {
    if (*b1 == '\r') TEB_debug_print("\\r");
    else if (*b1 == '\n') TEB_debug_print("\\n\n");
    else {
      TEB_debug_print_char(*b1);
    }
    b1 = b1 + 1;
  }
  TEB_debug_print("\n- END REQUEST -\n");
#endif
  if (TEB_http_connection_mode != 0) {
    TEB_fatal_error(95, "You need to run TEB_http_stop before you can use TEB_http_request.", 2);
    return TEB_debug_function_end(-4);
  }
  if (WiFi.status() != WL_CONNECTED) {
    TEB_debug_print("Sending HTTP request failed due to no Internet connection.");
    return TEB_debug_function_end(-1);
  }
  TEB_small_int r = TEB_http_connect(http_request->server_address,
                                     http_request->server_port,
                                     http_request->use_ssl,
                                     http_request->root_ca,
                                     http_request->connection_timeout_in_ms, mode);
  if (r != 1) {
    TEB_debug_print("Sending HTTP request failed. Unable to connect to the server.");
    return TEB_debug_function_end(-2);
  }
  r = TEB_http_send(http_request->request_text, TEB_String_strlen(http_request->request_text), mode);
  if (r != 1) {
    TEB_http_stop(mode);
    TEB_debug_print("Sending HTTP request failed. Unable to send the http request.");
    return TEB_debug_function_end(-5);
  }
  http_response->header = response_buffer;
  response_buffer = (*http_response_reception_algorithm)(http_response->header, response_buffer_length, http_request->response_delay_in_ms, additional_parameters_of_http_response_reception_algorithm, mode);
  //http_response->header beginning of the answer, response_buffer end of the answer
  if (http_response->header == response_buffer) {
    http_response->header = 0;
    http_response->header_length = 0;
    http_response->payload = 0;
    http_response->payload_length = 0;
    TEB_debug_print("\nNo response detected.");
    TEB_http_stop(mode);
    return TEB_debug_function_end(2);
  } else {
#ifdef TEB_LibrarySettings_DEBUG_MODE
    TEB_size_t i3;
#endif
    http_response->payload = (TEB_char*)TEB_String_index_of3(http_response->header, response_buffer, "\r\n\r\n");
    if (http_response->payload == TEB_NULL_POINTER) {
      http_response->header_length = response_buffer - http_response->header;
      http_response->payload_length = 0;
#ifdef TEB_LibrarySettings_DEBUG_MODE
      TEB_debug_print("\n\\r\\n\\r\\n was not found at the end of the header. The entire HTTP response was saved in http_response->header.\nThe response received (");
      TEB_debug_print_int(http_response->header_length);
      TEB_debug_print(" long) is:\n");
      i3 = 0;
      while (i3 < http_response->header_length) {
        if (http_response->header[i3] == '\r') TEB_debug_print("\\r");
        else if (http_response->header[i3] == '\n') TEB_debug_print("\\n\n");
        else TEB_debug_print_char(http_response->header[i3]);
        i3 = i3 + 1;
      }
      TEB_debug_print("\n- RESPONSE END -\n");
#endif
      TEB_http_stop(mode);
      return TEB_debug_function_end(2);
    } else {
      http_response->header_length = http_response->payload - http_response->header;
      http_response->payload_length = response_buffer - http_response->payload - 4;
      if (http_response->payload_length == 0) http_response->payload = 0;
      else http_response->payload = http_response->payload + 4;
#ifdef TEB_LibrarySettings_DEBUG_MODE
      TEB_debug_print("\nThe response header detected (");
      TEB_debug_print_int(http_response->header_length);
      TEB_debug_print(" long) is:\n");
      i3 = 0;
      while (i3 < http_response->header_length) {
        if (http_response->header[i3] == '\r') TEB_debug_print("\\r");
        else if (http_response->header[i3] == '\n') TEB_debug_print("\\n\n");
        else TEB_debug_print_char(http_response->header[i3]);
        i3 = i3 + 1;
      }
      TEB_debug_print("\n- HEADER END -\n");
      TEB_debug_print("\nThe response payload detected (");
      TEB_debug_print_int(http_response->payload_length);
      TEB_debug_print(" long) is:\n");
      i3 = 0;
      while (i3 < http_response->payload_length) {
        if (http_response->payload[i3] == '\r') TEB_debug_print("\\r");
        else if (http_response->payload[i3] == '\n') TEB_debug_print("\\n\n");
        else TEB_debug_print_char(http_response->payload[i3]);
        i3 = i3 + 1;
      }
      TEB_debug_print("\n- PAYLOAD END -\n");
#endif
      TEB_http_stop(mode);
      return TEB_debug_function_end(1);
    }
  }
  TEB_fatal_error(96, "This instruction should not be executed. Recheck the previous code.", 2);
  return TEB_debug_function_end(-3);
}

TEB_small_int TEB_http_standard_send_request (struct TEB_http_request* http_request,
                                             struct TEB_http_response* http_response,
                                             TEB_char* response_buffer,
                                             TEB_size_t response_buffer_length,
                                             TEB_medium_u_int mode) {
  TEB_debug_function_start("TEB_http_standard_send_request");
  TEB_small_int r = TEB_http_send_request(http_request, http_response, response_buffer, response_buffer_length,
                                          TEB_http_standard_response_reception_algorithm, TEB_NULL_POINTER, mode);
  return TEB_debug_function_end(r);
}

TEB_char* TEB_http_standard_response_reception_algorithm (TEB_char* response_buffer,
                                                         TEB_size_t response_buffer_length,
                                                         TEB_time_t response_delay_in_ms,
                                                         void* additional_parameters,
                                                         TEB_medium_u_int mode) {
  TEB_debug_function_start("TEB_http_standard_response_reception_algorithm");
  TEB_time_t m = TEB_ms_elapsed();
  TEB_big_int nbit = 256;  //nbit > 0 && <= response_buffer_length
  TEB_big_int n;
  while (1) {
    if (response_buffer_length < nbit) nbit = response_buffer_length;
    n = TEB_http_receive(response_buffer, nbit, mode);
    if (n != -1 && n != 0) {
      response_buffer = response_buffer + n;
      response_buffer_length = response_buffer_length - n;
      if (response_buffer_length == 0) break;
      m = TEB_ms_elapsed();
    } else if (TEB_is_delay_over(m, response_delay_in_ms, 1) != 0) break;
  }
  TEB_debug_function_end(0);
  return response_buffer;
}

TEB_small_int TEB_custom_command (TEB_medium_u_int command_id,
                                 const void* optional_parameters,
                                 void* optional_buffer,
                                 TEB_size_t optional_buffer_length) {
  TEB_debug_function_start("TEB_custom_command");
  TEB_debug_undefined_function("TEB_custom_command");
  return TEB_debug_function_end(1);
}

#ifdef TEB_LibrarySettings_DEBUG_MODE
static void TEB_DeviceInterfaces_function_end (const TEB_char* f_name, TEB_bool ok) {
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

TEB_small_int TEB_DeviceInterfaces_test1 (const TEB_char* wifi_ssid, const TEB_char* wifi_password) {
  TEB_small_int r = TEB_device_init(TEB_NULL_POINTER, 1);
  TEB_debug_function_start("TEB_DeviceInterfaces_test1");

  if (r == 1) TEB_DeviceInterfaces_function_end("TEB_device_init", 1);
  else {
    TEB_DeviceInterfaces_function_end("TEB_device_init", 0);
    return TEB_debug_function_end(-1);
  }

  if (TEB_print("\nThis is a test string.\n", 1) == 1) TEB_DeviceInterfaces_function_end("TEB_print", 1);
  else {
    TEB_DeviceInterfaces_function_end("TEB_print", 0);
    return TEB_debug_function_end(-2);
  }

  TEB_debug_print("\n");
  if (TEB_print_char('A', 1) == 1) TEB_DeviceInterfaces_function_end("TEB_print_char", 1);
  else {
    TEB_DeviceInterfaces_function_end("TEB_print_char", 0);
    return TEB_debug_function_end(-3);
  }

  TEB_debug_print("\n");
  if (TEB_print_int(1000, 1) == 1) TEB_DeviceInterfaces_function_end("TEB_print_int", 1);
  else {
    TEB_DeviceInterfaces_function_end("TEB_print_int", 0);
    return TEB_debug_function_end(-4);
  }

  if (TEB_error(0, "Test error.", 6000, 0) == 1) TEB_DeviceInterfaces_function_end("TEB_error", 1);
  else {
    TEB_DeviceInterfaces_function_end("TEB_error", 0);
    return TEB_debug_function_end(-5);
  }

  TEB_fatal_error(0, "Test fatal error.\nProgram execution is not interrupted.", 1);
  TEB_debug_print("TEB_fatal_error ok");

  if (TEB_delay(6000, 1) == 1) TEB_DeviceInterfaces_function_end("TEB_delay, TEB_is_delay_over and TEB_ms_elapsed", 1);
  else {
    TEB_DeviceInterfaces_function_end("TEB_delay, TEB_is_delay_over and TEB_ms_elapsed", 0);
    return TEB_debug_function_end(-22);
  }

  TEB_debug_print("\nThe total free heap is ");
  TEB_debug_print_int(TEB_free_heap());
  TEB_debug_print("\nunits long and the largest heap free block is ");
  TEB_debug_print_int(TEB_largest_heap_free_block());
  TEB_debug_print("\nunits long.\n");

  TEB_time_t t = TEB_ms_elapsed();
  TEB_debug_print_int(t);
  TEB_debug_print(" milliseconds have passed since the program started.");

  if (TEB_led_on(TEB_ESP32_ONBOARD_LED_ID, 1) == 1) TEB_DeviceInterfaces_function_end("TEB_led_on", 1);
  else {
    TEB_DeviceInterfaces_function_end("TEB_led_on", 0);
    return TEB_debug_function_end(-6);
  }

  if (TEB_led_off(TEB_ESP32_ONBOARD_LED_ID, 1) == 1) TEB_DeviceInterfaces_function_end("TEB_led_off", 1);
  else {
    TEB_DeviceInterfaces_function_end("TEB_led_off", 0);
    return TEB_debug_function_end(-7);
  }

  if (TEB_led_blink(TEB_ESP32_ONBOARD_LED_ID, 1000, 1000, 1) == 1) TEB_DeviceInterfaces_function_end("TEB_led_blink", 1);
  else {
    TEB_DeviceInterfaces_function_end("TEB_led_blink", 0);
    return TEB_debug_function_end(-8);
  }

  if (TEB_display_print(1, "This is a test string.", 1, 1) == 1) TEB_DeviceInterfaces_function_end("TEB_display_print", 1);
  else {
    TEB_DeviceInterfaces_function_end("TEB_display_print", 0);
    return TEB_debug_function_end(-9);
  }

  byte a[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  byte b[10];
  if (TEB_memory_write(1, a, 10, sizeof(byte), 1) == 1) TEB_DeviceInterfaces_function_end("TEB_memory_write", 1);
  else {
    TEB_DeviceInterfaces_function_end("TEB_memory_write", 0);
    return TEB_debug_function_end(-10);
  }

  if (TEB_memory_read(1, b, 10, sizeof(byte), 1) == 1) TEB_DeviceInterfaces_function_end("TEB_memory_read", 1);
  else {
    TEB_DeviceInterfaces_function_end("TEB_memory_read", 0);
    return TEB_debug_function_end(-11);
  }

  int i = 0;
  while (i < 10) {
    if (a[i] != b[i]) break;
    i = i + 1;
  }
  if (i == 10) TEB_debug_print("\nTEB_memory_read2 ok");
  else TEB_debug_print("\nTEB_memory_read2 ko");

  if (TEB_wifi_connect(1, wifi_ssid, wifi_password, 15000, 1) == 1) TEB_DeviceInterfaces_function_end("TEB_wifi_connect", 1);
  else {
    TEB_DeviceInterfaces_function_end("TEB_wifi_connect", 0);
    return TEB_debug_function_end(-12);
  }

  char* response_buffer = (char*)malloc(4500);
  struct TEB_http_request http_request;
  http_request.request_text = "POST /device/code HTTP/1.1\r\nHost: oauth2.googleapis.com\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: 60\r\n\r\nclient_id=fgdgjkd&scope=https://www.googleapis.com/auth/drive.file";
  http_request.server_address = "oauth2.googleapis.com";
  http_request.server_port = 443;
  http_request.use_ssl = 1;
  http_request.root_ca = "";
  http_request.connection_timeout_in_ms = 15000;
  http_request.response_delay_in_ms = 15000;
  struct TEB_http_response http_response;
  if (TEB_http_send_request(&http_request, &http_response, response_buffer, 3500, TEB_http_standard_response_reception_algorithm, TEB_NULL_POINTER, 1) == 1) TEB_DeviceInterfaces_function_end("TEB_http_send_request", 1);
  else {
    TEB_DeviceInterfaces_function_end("TEB_http_send_request", 0);
    return TEB_debug_function_end(-13);
  }

  if (TEB_http_standard_send_request(&http_request, &http_response, response_buffer, 3500, 1) == 1) TEB_DeviceInterfaces_function_end("TEB_http_standard_send_request", 1);
  else {
    TEB_DeviceInterfaces_function_end("TEB_http_standard_send_request", 0);
    return TEB_debug_function_end(-14);
  }

  if (TEB_http_connect("www.howsmyssl.com", 443, 1, "", 5000, 1) == 1) TEB_DeviceInterfaces_function_end("TEB_http_connect", 1);
  else {
    TEB_DeviceInterfaces_function_end("TEB_http_connect", 0);
    return TEB_debug_function_end(-15);
  }

  if (TEB_http_send("GET https://www.howsmyssl.com/a/check HTTP/1.0", 46, 1) == 1) TEB_DeviceInterfaces_function_end("TEB_http_send", 1);
  else {
    TEB_DeviceInterfaces_function_end("TEB_http_send", 0);
    return TEB_debug_function_end(-16);
  }

  if (TEB_http_send("\r\nHost: www.howsmyssl.com\r\nConnection: close\r\n\r\n", 48, 1) == 1) TEB_DeviceInterfaces_function_end("TEB_http_send2", 1);
  else {
    TEB_DeviceInterfaces_function_end("TEB_http_send2", 0);
    return TEB_debug_function_end(-17);
  }

  TEB_char* buf = response_buffer;
  TEB_time_t m = TEB_ms_elapsed();
  while (1) {
    int n = TEB_http_receive(buf, 255, 1);
    if (n > 0) {
      buf = buf + n;
      m = TEB_ms_elapsed();
    }
    if (TEB_is_delay_over(m, 10, 1) == 1) break;
  }
  *buf = '\0';
  TEB_debug_print("\nHTTP response received:\n");
  TEB_debug_print(response_buffer);
  TEB_debug_print("\n");
  free(response_buffer);

  if (TEB_http_stop(1) == 1) TEB_DeviceInterfaces_function_end("TEB_http_stop", 1);
  else {
    TEB_DeviceInterfaces_function_end("TEB_http_stop", 0);
    return TEB_debug_function_end(-18);
  }

  if (TEB_wifi_check(1, 1) == 1) TEB_DeviceInterfaces_function_end("TEB_wifi_check", 1);
  else {
    TEB_DeviceInterfaces_function_end("TEB_wifi_check", 0);
    return TEB_debug_function_end(-19);
  }

  if (TEB_custom_command(0, TEB_NULL_POINTER, TEB_NULL_POINTER, 0) == 1) TEB_DeviceInterfaces_function_end("TEB_custom_command", 1);
  else {
    TEB_DeviceInterfaces_function_end("TEB_custom_command", 0);
    return TEB_debug_function_end(-21);
  }

  return TEB_debug_function_end(1);
}

TEB_small_int TEB_DeviceInterfaces_test2 () {
  TEB_debug_function_start("TEB_DeviceInterfaces_test2");

  if (TEB_wifi_disconnect(1, 1) == 1) TEB_DeviceInterfaces_function_end("TEB_wifi_disconnect", 1);
  else {
    TEB_DeviceInterfaces_function_end("TEB_wifi_disconnect", 0);
    return TEB_debug_function_end(-20);
  }

  TEB_debug_print("\nIf the device reboots within 15 seconds, it means that all tests have been successfully completed.\n");
  TEB_display_print(1, "If the device reboots within 15 seconds, it means that all tests have been successfully completed.", 1, 1);

  TEB_delay(15000, 1);
  TEB_reboot_device(1);

  TEB_debug_print("\n\nError, the device did not restart.\n");
  return TEB_debug_function_end(-23);
}
#endif

#endif
