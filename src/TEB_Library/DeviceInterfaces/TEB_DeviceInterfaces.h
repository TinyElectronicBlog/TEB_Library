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

#ifndef TEB_DeviceInterfaces_h
#define TEB_DeviceInterfaces_h

#include "../../TEB_LibrarySettings.h"



#if TEB_LibrarySettings_SELECTED_DEVICE_ID == 1 //WINDOWS PC (test device, most functions are not defined)***********************************************************************************************************************************************************************************************************

//CUSTOMIZABLE PREPROCESSOR DIRECTIVES OF THE SELECTED DEVICE*********************************************************************************************************************************************************************************************************************************************************************************************************************************

//EXTERNAL DEPENDENCIES*********************************************************************************************************************************************************************************************************************************************************************************************************************************
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//TYPES OF DATA USED IN THIS LIBRARY OUTSIDE OF THE TEB_Device_Interfaces.h AND TEB_Device_Interfaces.c FILES.

typedef bool TEB_bool;  //At least one bit, 0 = false. Define "typedef enum {false, true} bool;" if bool definition is missing in the device library.

typedef char TEB_char;             //At least 8 bit.
typedef unsigned char TEB_u_char;  //At least 8 bit.

typedef short TEB_small_int;    //At least 8 bits, for signed integers.
typedef int TEB_medium_int;     //At least 16 bits, for signed integers.
typedef long long TEB_big_int;  //At least 32 bits, for signed integers.

typedef unsigned short TEB_small_u_int;    //At least 8 bits, for unsigned integers.
typedef unsigned int TEB_medium_u_int;     //At least 16 bits, for unsigned integers.
typedef unsigned long long TEB_big_u_int;  //At least 32 bits, for unsigned integers.

typedef size_t TEB_size_t;  //If size_t is not defined in the device library, set TEB_big_u_int.

typedef TEB_big_u_int TEB_time_t;  //Change the data type based on the one used in TEB_s_elapsed().

typedef unsigned char TEB_data_type_to_copy_buffer;  //Set the data type used in the device memcpy function to copy array elements.

//DEFINITION OF CONSTANTS

#define TEB_MILLISECONDS_ELAPSED_SINCE_START_MAX_VALUE 9223372036854775 /*Maximum value returned by TEB_ms_elapsed() before restarting from 0. In this case 9223372036854775807 / 1000 */

#define TEB_NULL_CHAR '\0'  //The null-terminated string character.

#define TEB_NULL_POINTER NULL  //The null pointer value.

#define TEB_MAX_NUMBER_OF_ALLOCABLE_SPLITTABLE_ARRAYS 100  //Maximum number of allocable splittable arrays. Set the smallest value possible.

#endif





#if TEB_LibrarySettings_SELECTED_DEVICE_ID == 2 && TEB_LibrarySettings_SELECTED_PROGRAMMING_LANGUAGE == 2 //ESP32 with C++*******************************************************************************************************************************************************************************************************************************************************************************

//CUSTOMIZABLE PREPROCESSOR DIRECTIVES OF THE SELECTED DEVICE*********************************************************************************************************************************************************************************************************************************************************************************************************************************
#define TEB_ESP32_BAUD_RATE 115200
#define TEB_ESP32_ONBOARD_LED_ID 1
#define TEB_ESP32_ONBOARD_LED_PIN 2

//EXTERNAL DEPENDENCIES*********************************************************************************************************************************************************************************************************************************************************************************************************************************
#include <Arduino.h>
#include "OakOLED.h"  //https://github.com/netguy204/OakOLED
#include "EEPROM.h"
#include <WiFiClientSecure.h>

//TYPES OF DATA USED IN THIS LIBRARY OUTSIDE OF THE TEB_Device_Interfaces.h AND TEB_Device_Interfaces.c FILES.

typedef bool TEB_bool;  //At least one bit, 0 = false. Define "typedef enum {false, true} bool;" if bool definition is missing in the device library.

typedef char TEB_char;             //At least 8 bit.
typedef unsigned char TEB_u_char;  //At least 8 bit.

typedef short TEB_small_int;    //At least 8 bits, for signed integers.
typedef int TEB_medium_int;     //At least 16 bits, for signed integers.
typedef long long TEB_big_int;  //At least 32 bits, for signed integers.

typedef unsigned short TEB_small_u_int;    //At least 8 bits, for unsigned integers.
typedef unsigned int TEB_medium_u_int;     //At least 16 bits, for unsigned integers.
typedef unsigned long long TEB_big_u_int;  //At least 32 bits, for unsigned integers.

typedef size_t TEB_size_t;  //If size_t is not defined in the device library, set TEB_big_u_int.

typedef int64_t TEB_time_t;  //Change the data type based on the one used in TEB_s_elapsed().

typedef unsigned char TEB_data_type_to_copy_buffer;  //Set the data type used in the device memcpy function to copy array elements.

//DEFINITION OF CONSTANTS

#define TEB_MILLISECONDS_ELAPSED_SINCE_START_MAX_VALUE 9223372036854775 /*Maximum value returned by TEB_ms_elapsed() before restarting from 0. In this case 9223372036854775807 / 1000 */

#define TEB_NULL_CHAR '\0'  //The null-terminated string character.

#define TEB_NULL_POINTER NULL  //The null pointer value.

#define TEB_MAX_NUMBER_OF_ALLOCABLE_SPLITTABLE_ARRAYS 100  //Maximum number of allocable splittable arrays. Set the smallest value possible.

#endif



























//WARNING, FROM THIS LINE ONWARD DO NOT TOUCH ANYTHING!***************************************************************************************************************************************************************************************************************************************************************************************************

//DEBUG FUNCTIONS

/**
       \brief Prints a message on the debug monitor when TEB_LibrarySettings_DEBUG_MODE is 1 or 3. 
       \param [in] str The message to print.       
    */
void TEB_debug_print (const TEB_char* str);

/**
       \brief Prints a character on the debug monitor when TEB_LibrarySettings_DEBUG_MODE is 1 or 3.
       \param [in] c The character to print.       
    */
void TEB_debug_print_char (const TEB_char c);

/**
       \brief Prints a number on the debug monitor when TEB_LibrarySettings_DEBUG_MODE is 1 or 3.
       \param [in] n The number to print.       
    */
void TEB_debug_print_int (TEB_big_u_int n);

/**
       \brief TEB_debug_function_start should be inserted at the beginning of the body of each function for which you want to keep track of the order of execution. It works when TEB_LibrarySettings_DEBUG_MODE is 2 or 3.
       \param [in] function_name The name of the function.      
    */
void TEB_debug_function_start (const TEB_char* function_name);

/**
       \brief TEB_debug_function_end should be inserted at the end of the body of each function for which you want to keep track of the order of execution. It works when TEB_LibrarySettings_DEBUG_MODE is 2 or 3.
       \param [in] r The value to return.   
    */
TEB_small_int TEB_debug_function_end (TEB_small_int r);

/**
       \brief TEB_debug_undefined_function should be inserted in the body of an undefined function. If executed when TEB_LibrarySettings_DEBUG_MODE is 2 or 3, it prints "Warning: executed undefined function with name function_name." on the debug monitor.
       \param [in] function_name The name of the function.       
    */
void TEB_debug_undefined_function (const TEB_char* function_name);





//FUNCTIONS TO DISPLAY INFORMATION AND REPORT ERRORS

/**
       \brief Prints a message. Beware, when TEB_LibrarySettings_DEBUG_MODE is uncommented, incorrect parameter values result in an error being printed on the debug monitor and the program execution being blocked. 
       \param [in] str The message to print. 
	   \param [in] mode The execution mode. Default value 1.
	   \return 1 if all ok.
    */
TEB_small_int TEB_print (const TEB_char* str, TEB_medium_u_int mode);

/**
       \brief Prints a character. Beware, when TEB_LibrarySettings_DEBUG_MODE is uncommented, incorrect parameter values result in an error being printed on the debug monitor and the program execution being blocked. 
       \param [in] c The character to print. 
	   \param [in] mode The execution mode. Default value 1.
	   \return 1 if all ok.
    */
TEB_small_int TEB_print_char (const TEB_char c, TEB_medium_u_int mode);

/**
       \brief Prints a number. Beware, when TEB_LibrarySettings_DEBUG_MODE is uncommented, incorrect parameter values result in an error being printed on the debug monitor and the program execution being blocked. 
       \param [in] n The number to print. 
	   \param [in] mode The execution mode. Default value 1.
	   \return 1 if all ok.
    */
TEB_small_int TEB_print_int (TEB_big_u_int n, TEB_medium_u_int mode);

/**
       \brief Reports an error when TEB_LibrarySettings_ENABLE_ERRORS is uncommented. If TEB_LibrarySettings_DEBUG_MODE is 1 or 3 the error is printed on the debug monitor.
       \param [in] number The error number.
	   \param [in] text The error text.
	   \param [in] duration_in_ms Duration of error reporting in milliseconds.
	   \param [in] mode The execution mode. Default value 1. If 2 the error is reported only on the debug monitor.
	   \return 1 if all ok.
    */
TEB_small_int TEB_error (TEB_big_u_int number,
					     const TEB_char* text, 
						 TEB_time_t duration_in_ms, 
						 TEB_medium_u_int mode);

/**
       \brief Reports a fatal error when TEB_LibrarySettings_ENABLE_FATAL_ERRORS is uncommented; if TEB_LibrarySettings_DEBUG_MODE is 1 or 3 the error is printed on the debug monitor. Fatal errors with number other than 0 block the execution of the program, requiring a device reboot.
       \param [in] number The error number.
	   \param [in] text The error text.
	   \param [in] mode The execution mode. Default value 1. If 2 the error is reported only on the debug monitor.
	   \return 1 if all ok.
    */
void TEB_fatal_error (TEB_big_u_int number, 
					  const TEB_char* text, 
					  TEB_medium_u_int mode);





//VARIOUS FUNCTIONS

/**
       \brief All instructions to be executed when starting the device should be placed in the body of this function; TEB_device_init should be executed before any other function.
	   \param [in] parameters Additional parameters, if necessary.
	   \param [in] mode The execution mode. Default value 1.
	   \return 1 if all ok.
    */
TEB_small_int TEB_device_init (void* parameters, TEB_medium_u_int mode);

/**
	   \return The milliseconds elapsed since the device started up. TEB_MILLISECONDS_ELAPSED_SINCE_START_MAX_VALUE is the last value returned before restarting the count from 0.
    */
TEB_time_t TEB_ms_elapsed ();

/**
	 \brief Evaluates if a time interval has elapsed. This function works even if the variable used to measure time goes into overflow.
	   \param [in] initial_instant_returned_by_TEB_ms_elapsed The initial time instant to be considered. It must have been returned by TEB_ms_elapsed.
	   \param [in] interval_duration_in_milliseconds. Interval duration in milliseconds.
	   	   \param [in] mode The execution mode. Default value 1.
	   \return Returns 1 if at least interval_duration_in_milliseconds ms have elapsed since the initial_instant_returned_by_TEB_ms_elapsed, otherwise 0.
    */
TEB_bool TEB_is_delay_over (TEB_time_t initial_instant_returned_by_TEB_ms_elapsed,
						         TEB_time_t interval_duration_in_milliseconds,
								 TEB_medium_u_int mode);

/**
       \brief Pauses program execution for the desired time interval.
	   \param [in] milliseconds_waiting_time The millisecond wait times.
	   \param [in] mode The execution mode. Default value 1.
	   \return 1 if all ok.
    */
TEB_small_int TEB_delay (TEB_time_t milliseconds_waiting_time, TEB_medium_u_int mode);

/**
       \brief Restart the device.
	   \param [in] mode The execution mode. Default value 1.
    */
void TEB_reboot_device (TEB_medium_u_int mode);

/**
       \brief The free heap.
    */
TEB_size_t TEB_free_heap ();

/**
       \brief The size of the largest block of free heap.
    */
TEB_size_t TEB_largest_heap_free_block ();





//FUNCTIONS TO MANAGE LEDS CONNECTED TO THE DEVICE

/**
       \brief Turns on a led.
	   \param [in] led_id ID of the led to manage. Default value 1.
	   \param [in] mode The execution mode. Default value 1.
	   \return 1 if all ok.
    */
TEB_small_int TEB_led_on (TEB_medium_u_int led_id, TEB_medium_u_int mode);

/**
       \brief Turns off a led.
	   \param [in] led_id ID of the led to manage. Default value 1.
	   \param [in] mode The execution mode. Default value 1.
	   \return 1 if all ok.
    */
TEB_small_int TEB_led_off (TEB_medium_u_int led_id, TEB_medium_u_int mode);

/**
       \brief Turns a led on and off.
	   \param [in] led_id ID of the led to manage. Default value 1.
	   \param [in] on_ms Power-on milliseconds.
	   \param [in] off_ms Power-off milliseconds.
	   \param [in] mode The execution mode. Default value 1.
	   \return 1 if all ok.
    */
TEB_small_int TEB_led_blink (TEB_medium_u_int led_id,
					         TEB_time_t on_ms, 
							 TEB_time_t off_ms, 
							 TEB_medium_u_int mode);





//FUNCTIONS TO MANAGE THE CONNECTION TO WIFI NETWORKS

/**
          \brief Connects to a WiFi network.
	   \param [in] wifi_interface_id ID of the wifi interface. Default value 1.
          \param [in] ssid Name of WiFi network.
          \param [in] password Password of WiFi network.
          \param [in] timeout_in_ms Maximum time in milliseconds to make the connection.
		  	   \param [in] mode The execution mode. Default value 1.
          \return 1 if the Internet connection succeeds within timeout_in_s s.
    */
TEB_small_int TEB_wifi_connect (TEB_small_u_int wifi_interface_id,
								const TEB_char* ssid,
								const TEB_char* password,
								TEB_medium_u_int timeout_in_ms,
								TEB_medium_u_int mode);

/**
          \brief Disconnect from WiFi network.
	   \param [in] wifi_interface_id ID of the wifi interface. Default value 1.
		  	   \param [in] mode The execution mode. Default value 1.
          \return 1 if all ok.
    */
TEB_small_int TEB_wifi_disconnect (TEB_small_u_int wifi_interface_id, TEB_medium_u_int mode);

/**
	   \param [in] wifi_interface_id ID of the wifi interface.
		  	   \param [in] mode The execution mode. Default value 1.
          \return 1 if the device is connected to a WiFi network, otherwise 0. Return a negative value in case of error.
*/
TEB_small_int TEB_wifi_check (TEB_small_u_int wifi_interface_id, TEB_medium_u_int mode);





//FUNCTIONS TO MANAGE DISPLAYS CONNECTED TO THE DEVICE

/**
          \brief Print a message on a display.
	   \param [in] display_id ID of the display. Default value 1.
          \param [in] text Text to print.
          \param [in] text_size Text size. Must be > 0.
		  	   \param [in] mode The execution mode. Default value 1.
          \return 1 if all ok.
    */
TEB_small_int TEB_display_print (TEB_small_u_int display_id, 
							     const TEB_char* text, 
								 TEB_medium_u_int text_size, 
								 TEB_medium_u_int mode);





//FUNCTIONS TO MANAGE MEMORIES CONNECTED TO THE DEVICE

/**
          \brief Saves data in a memory. 
	   \param [in] memory_id ID of the memory. Default value 1.
          \param [in] elements_to_write Elements to be saved.
          \param [in] number_of_elements_to_write Number of elements to be saved.
          \param [in] sizeof_one_element Size of one element to be saved.
		  	   \param [in] mode The execution mode. Default value 1.
          \return 1 if all ok.
    */
TEB_small_int TEB_memory_write (TEB_medium_u_int memory_id,
                               void* elements_to_write,
                               TEB_size_t number_of_elements_to_write,
                               TEB_size_t sizeof_one_element,
                               TEB_medium_u_int mode);

/**
          \brief Read data from a memory. 
	   \param [in] memory_id ID of the memory. Default value 1.
          \param [in] elements_to_read_buffer Buffer in which to save the data.
          \param [in] number_of_elements_to_read Number of elements to read.
          \param [in] sizeof_one_element Size of one element to read.
		  	   \param [in] mode The execution mode. Default value 1.
          \return 1 if all ok.
    */
TEB_small_int TEB_memory_read (TEB_medium_u_int memory_id,
                              void* elements_to_read_buffer,
                              TEB_size_t number_of_elements_to_read,
                              TEB_size_t sizeof_one_element,
                              TEB_medium_u_int mode);





//FUNCTIONS TO MANAGE HTTP/HTTPS REQUESTS

/**
       \brief Connect to a server.
       \param [in] server_address Server Address.
       \param [in] server_port Server port.
	     \param [in] use_ssl true to use an encrypted connection.
       \param [in] root_ca SSL root certificate of the server address; if rootCA = "" the certificate is not verified.
       \param [in] connection_timeout_in_ms ms within which the connection must take place. 
  	   \param [in] mode The execution mode. Default value 1.
       \return 1 if ok.
       \details TEB_http_connect can only be re-executed after the stop function or after a connect, send or receive failure. 
    */
TEB_small_int TEB_http_connect (const TEB_char* server_address,
                               TEB_medium_u_int server_port,
                               TEB_bool use_ssl,
                               const TEB_char* root_ca,
                               TEB_time_t connection_timeout_in_ms,
                               TEB_medium_u_int mode);

/**
       \brief Sends an HTTP request.
       \param [in] request_text The request text.
	     \param [in] request_text_length Length of the request text.
  	   \param [in] mode The execution mode. Default value 1.
       \return 1 if ok.
       \details If the send fails you must start over with connect. It can be executed after connect or another send.
    */
TEB_small_int TEB_http_send (const TEB_char* request_text,
						     TEB_size_t request_text_length, 
							 TEB_medium_u_int mode);

/**
       \brief Receive an HTTP response.
       \param [in] response_buffer Buffer in which to save the response.
       \param [in] response_buffer_length Length of buffer.
       \param [in] mode The execution mode. Default value 1.
       \return The number of characters saved in response_buffer, otherwise a negative value.
       \details If it doesn't read anything return 0 (in this case it is recommended to repeat the reading several times to be sure to have received all the data). It can be executed after connect, send or another receive.
    */
TEB_big_int TEB_http_receive (TEB_char* response_buffer,
							  TEB_big_int response_buffer_length, 
							  TEB_medium_u_int mode);

/**
       \brief Closes the connection with a server.
       \details It can be executed after connect, send or receive.
	   \param [in] mode The execution mode. Default value 1.
       \return The number of characters saved in response_buffer, otherwise a negative value.
    */
TEB_small_int TEB_http_stop (TEB_medium_u_int mode);

/**
       \brief HTTP request data type used in TEB_http_send_request.\n
	   request_text: HTTP request message;\n
	   server_address: Server Address.\n
       server_port: Server port.\n
	   use_ssl: true to use encrypted connections;\n
	   root_ca: SSL root certificate of the server address; if root_ca = "" the certificate is not verified.\n
	   connection_timeout_in_ms: maximum time in milliseconds to connect to the server;\n 
	   response_delay_in_ms: if more than response_delay_in_ms milliseconds elapse since the last data received from the server, the development board closes the connection.  
    */
struct TEB_http_request {
  const TEB_char* request_text;
  const TEB_char* server_address;
  TEB_medium_u_int server_port;
  TEB_bool use_ssl;
  const TEB_char* root_ca;
  TEB_time_t connection_timeout_in_ms;
  TEB_time_t response_delay_in_ms;
};

/**
       \brief HTTP response data type used in TEB_http_send_request. The fields do not need to be initialized.
	    header: http response header, does not end with \0;
	   header_length: header length;
	   payload: http response payload, does not end with \0;
	   payload_length: payload length;.  
    */
struct TEB_http_response {
  TEB_char* header;
  TEB_size_t header_length;
  TEB_char* payload;
  TEB_size_t payload_length;
};

/**
       \brief It sends an HTTP request and receives the relative response.
       \param [in] http_request The HTTP request.
       \param [in] http_response The HTTP response.
       \param [in] response_buffer Buffer in which to save the response.
       \param [in] response_buffer_length Response buffer length.
       \param [in] http_response_reception_algorithm Custom algorithm for receiving the HTTP response.
	   \param [in] additional_parameters_of_http_response_reception_algorithm Any additional parameters to pass to http_response_reception_algorithm.
        \param [in] mode The execution mode. Default value 1.
		\return 1 if ok, 2 if "\n\r\n\r" was not found at the end of the HTTP response header.
       \details if return 2 the whole http response is saved in http_response.header. All fields of http_request must be initialized. If the HTTP response is longer than response_buffer_length it is truncated. If http_request.root_ca = "" the rootCA of http_request.server_address is not considered. The TEB_char* fields of http_response do not end with \0 while those of http_request do. http_response contains pointers to response_buffer.
    */
TEB_small_int TEB_http_send_request (struct TEB_http_request* http_request,
                                    struct TEB_http_response* http_response,
                                    TEB_char* response_buffer,
                                    TEB_size_t response_buffer_length,
                                    TEB_char* (*http_response_reception_algorithm)(TEB_char* response_buffer, TEB_size_t response_buffer_length, TEB_time_t response_delay_in_ms, void* additional_parameters, TEB_medium_u_int mode),
                                    void* additional_parameters_of_http_response_reception_algorithm,
                                    TEB_medium_u_int mode);

/**
       \brief It sends an HTTP request and receives the relative response.
       \param [in] http_request The HTTP request.
       \param [in] http_response The HTTP response.
       \param [in] response_buffer Buffer in which to save the response.
       \param [in] response_buffer_length Response buffer length.
        \param [in] mode The execution mode. Default value 1.
		\return 1 if ok, 2 if "\n\r\n\r" was not found at the end of the HTTP response header.
       \details if return 2 the whole http response is saved in http_response.header. All fields of http_request must be initialized. If the HTTP response is longer than response_buffer_length it is truncated. If http_request.root_ca = "" the rootCA of http_request.server_address is not considered. The TEB_char* fields of http_response do not end with \0 while those of http_request do. http_response contains pointers to response_buffer.
    */
TEB_small_int TEB_http_standard_send_request (struct TEB_http_request* http_request,
                                             struct TEB_http_response* http_response,
                                             TEB_char* response_buffer,
                                             TEB_size_t response_buffer_length,
                                             TEB_medium_u_int mode);

/**
       \brief Algorithm for receiving an HTTP response used in TEB_http_standard_send_request. 
    */
TEB_char* TEB_http_standard_response_reception_algorithm (TEB_char* response_buffer,
                                                         TEB_size_t response_buffer_length,
                                                         TEB_time_t response_delay_in_ms,
                                                         void* additional_parameters,
                                                         TEB_medium_u_int mode);





//CUSTOMIZABLE FUNCTION

/**
          \brief Customizable function, if you want to add features not managed by other functions.
	        \param [in] command_id ID of the command.
          \param [in] optional_parameters Undefined.
          \param [in] optional_buffer Undefined.
          \param [in] optional_buffer_length Undefined.
          \return Undefined.
    */
TEB_small_int TEB_custom_command (TEB_medium_u_int command_id,
                                 const void* optional_parameters,
                                 void* optional_buffer,
                                 TEB_size_t optional_buffer_length);





//TEST FUNCTIONS

#ifdef TEB_LibrarySettings_DEBUG_MODE
TEB_small_int TEB_DeviceInterfaces_test1 (const TEB_char* wifi_ssid, const TEB_char* wifi_password);
TEB_small_int TEB_DeviceInterfaces_test2 ();
#endif

struct TEB_rename_f {
  void (*debugPrint)(const TEB_char*);
  void (*debugPrintChar)(const TEB_char);
  void (*debugPrintInt)(TEB_big_u_int);
  void (*debugFunctionStart)(const TEB_char*);
  TEB_small_int (*debugFunctionEnd)(TEB_small_int);
  void (*debugUndefinedFunction)(const TEB_char*);
  TEB_small_int (*print)(const TEB_char*, TEB_medium_u_int);
  TEB_small_int (*printChar)(const TEB_char, TEB_medium_u_int);
  TEB_small_int (*printInt)(TEB_big_u_int, TEB_medium_u_int);
  TEB_small_int (*error)(TEB_big_u_int, const TEB_char*, TEB_time_t, TEB_medium_u_int);
  void (*fatalError)(TEB_big_u_int, const TEB_char*, TEB_medium_u_int);
  TEB_small_int (*init)(void*, TEB_medium_u_int);
  TEB_time_t (*millis)();
  TEB_bool (*isDelayOver)(TEB_time_t, TEB_time_t, TEB_medium_u_int);
  TEB_small_int (*delay)(TEB_time_t, TEB_medium_u_int);
  void (*reboot)(TEB_medium_u_int);
  TEB_size_t (*freeHeap)();
  TEB_size_t (*largestHeapFreeBlock)();
  TEB_small_int (*ledOn)(TEB_medium_u_int, TEB_medium_u_int);
  TEB_small_int (*ledOff)(TEB_medium_u_int, TEB_medium_u_int);
  TEB_small_int (*ledBlink)(TEB_medium_u_int, TEB_time_t, TEB_time_t, TEB_medium_u_int);
  TEB_small_int (*wifiConnect)(TEB_small_u_int, const TEB_char*, const TEB_char*, TEB_medium_u_int, TEB_medium_u_int);
  TEB_small_int (*wifiDisconnect)(TEB_small_u_int, TEB_medium_u_int);
  TEB_small_int (*wifiCheck)(TEB_small_u_int, TEB_medium_u_int);
  TEB_small_int (*displayPrint)(TEB_small_u_int, const TEB_char*, TEB_medium_u_int, TEB_medium_u_int);
  TEB_small_int (*memoryWrite)(TEB_medium_u_int, void*, TEB_size_t, TEB_size_t, TEB_medium_u_int);
  TEB_small_int (*memoryRead)(TEB_medium_u_int, void*, TEB_size_t, TEB_size_t, TEB_medium_u_int);
  TEB_small_int (*httpConnect)(const TEB_char*, TEB_medium_u_int, TEB_bool, const TEB_char*, TEB_time_t, TEB_medium_u_int);
  TEB_small_int (*httpSend)(const TEB_char*, TEB_size_t, TEB_medium_u_int);
  TEB_big_int (*httpReceive)(TEB_char*, TEB_big_int, TEB_medium_u_int);
  TEB_small_int (*httpStop)(TEB_medium_u_int);
  TEB_small_int (*httpSendRequest)(struct TEB_http_request*, struct TEB_http_response*, TEB_char*, TEB_size_t, TEB_char* (*http_response_reception_algorithm)(TEB_char*, TEB_size_t, TEB_time_t, void*, TEB_medium_u_int), void*, TEB_medium_u_int);
  TEB_small_int (*httpStandardSendRequest)(struct TEB_http_request*, struct TEB_http_response*, TEB_char*, TEB_size_t, TEB_medium_u_int);
  TEB_char* (*httpStandardResponseReceptionAlgorithm)(TEB_char*, TEB_size_t, TEB_time_t, void*, TEB_medium_u_int);
  TEB_small_int (*customCommand)(TEB_medium_u_int, const void*, void*, TEB_size_t);
};

#endif
														 