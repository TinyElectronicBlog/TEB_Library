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

#ifndef TEB_String_h
#define TEB_String_h

#include "../../TEB_LibrarySettings.h"
#include "../DeviceInterfaces/TEB_DeviceInterfaces.h"

/**
    \brief This class contains various methods for handling strings.
*/

/**
        \param [in] str Must end with \0.
        \return Returns the length of str without including \0.
    */
	
	/**
	    pointer: pointer to the memory location of the associated array;
	   sizeof_one_element: size of an array element (e.g. sizeof(int) for an array of int);
	   length: number of array elements;
	   allocation_mode: 1 if a new dynamically allocated array is associated, 2 one already instantiated, another value if nothing is associated.
    */
TEB_size_t TEB_String_strlen (const TEB_char* str);

/**
          \brief Compare two strings.
          \param [in] str1 Initial delimiter of the first string (inclusive).
          \param [in] to1 Final delimiter of the first string (excluded).
          \param [in] str2 Initial delimiter of the second string (inclusive).
          \param [in] to2 Final delimiter of the second string (excluded).
          \return 1 if str1 and str2 are equal (the \0 is neglected), 0 otherwise.
    */
TEB_small_int TEB_String_equals (const TEB_char* str1,
                                const TEB_char* to1,
                                const TEB_char* str2,
                                const TEB_char* to2);

/**
          \brief Compare two strings.
          \param [in] str1 Must end with \0..
          \param [in] str2 Must end with \0.
          \return 1 if str1 and str2 are equal (the \0 is neglected), 0 otherwise.
    */
TEB_small_int TEB_String_equals2 (const TEB_char* str1,
                                 const TEB_char* str2);

/**
          \brief Compare two strings.
           \param [in] str1 Initial delimiter of the first string (inclusive).
          \param [in] to1 Final delimiter of the first string (excluded).
          \param [in] str2 Must end with \0.
          \return 1 if str1 and str2 are equal (the \0 is neglected), 0 otherwise.
    */
TEB_small_int TEB_String_equals3 (const TEB_char* str1,
                                 const TEB_char* to1,
                                 const TEB_char* str2);

/**
          \brief Looks for the str2 (inclusive) - to2 (excluded) delimited string in the char array delimited by str1 (included) - to1 (excluded) from left to right. Returns a pointer to the str2-to2 string within the char array str1-to1 or NULL if not found.
          \param [in] str1 Initial delimiter of the string in which to look for.
          \param [in] to1  Final delimiter of the string in which to look for.
          \param [in] str2 Initial delimiter of the string to search for.
          \param [in] to2  Final delimiter of the string to search for.
          \return A pointer to the str2-to2 string within the char array str1-to1 or NULL if not found.
    */
const TEB_char* TEB_String_index_of (const TEB_char* str1,
                                    const TEB_char* to1,
                                    const TEB_char* str2,
                                    const TEB_char* to2);

/**
          \brief Looks for the str2 string (must ends with \0) in the char array str1 (must ends with \0) from left to right. Returns a pointer to str2 string within str1 or NULL if not found.
          \param [in] str1 Initial delimiter of the string in which to look for.
          \param [in] str2 Initial delimiter of the string to search for.
          \return A pointer to the str2 string within the char array str1 or NULL if not found.
    */
const TEB_char* TEB_String_index_of2 (const TEB_char* str1, const TEB_char* str2);

/**
          \brief Looks for the str2 string (must ends with \0) in the char array delimited by str1 (included) - to1 (excluded) from left to right. Returns a pointer to the str2 string within the char array str1-to1 or NULL if not found.
          \param [in] str1 Initial delimiter of the string in which to look for.
          \param [in] to1  Final delimiter of the string in which to look for.
          \param [in] str2 Initial delimiter of the string to search for.
          \return A pointer to the str2 string within the char array str1-to1 or NULL if not found.
    */
const TEB_char* TEB_String_index_of3 (const TEB_char* str1, const TEB_char* to1, const TEB_char* str2);

/**
          \brief Like the indexOf method but the search is done from right to left.
          \param [in] str1 Initial delimiter of the string in which to look for.
          \param [in] to1  Final delimiter of the string in which to look for.
          \param [in] str2 Initial delimiter of the string to search for.
          \param [in] to2  Final delimiter of the string to search for.
          \return A pointer to the str2-to2 string within the char array str1-to1 or NULL if not found.
    */
const TEB_char* TEB_String_last_index_of (const TEB_char* str1, 
								          const TEB_char* to1, 
										  const TEB_char* str2, 
										  const TEB_char* to2);

  /**
          \brief Like the index_of method but the search is done from right to left.
          \param [in] str1 Initial delimiter of the string in which to look for.
          \param [in] str2 Initial delimiter of the string to search for.
          \return A pointer to the str2 string within the char array str1 or NULL if not found.
    */
  const TEB_char* TEB_String_last_index_of2 (const TEB_char* str1, const TEB_char* str2);

/**
        \brief Like the indexOf method but the search is done from right to left.
        \param [in] str1 Initial delimiter of the string in which to look for.
        \param [in] to1  Final delimiter of the string in which to look for.
        \param [in] str2 Initial delimiter of the string to search for.
        \return A pointer to the str2 string within the char array str1-to1 or NULL if not found.
    */
const TEB_char* TEB_String_last_index_of3 (const TEB_char* str1,
										   const TEB_char* to1, 
										   const TEB_char* str2);

/**
       \brief Add source in destination. The string to copy is delimited by source (inclusive) and to (excluded). destination ends with \0. Returns a pointer to the \0 of destination.
       \param [in] destination Buffer where to copy source.
       \param [in] source      Initial delimiter of the string to be copied.
       \param [in] to          Final delimiter of the string to be copied.
       \return A pointer to the \0 of destination.
       \details destination must be large enough to contain source.
    */
TEB_char* TEB_String_append (TEB_char* destination, const TEB_char* source, const TEB_char* to);

/**
        \brief Add source in destination. source must end with \0. destination ends with \0. Returns a pointer to the \0 of destination.
        \param [in] destination Buffer where to copy source.
        \param [in] source      String to copy. 
        \return A pointer to the \0 of destination.
        \details destination must be large enough to contain source.
    */
TEB_char* TEB_String_append2 (TEB_char* destination, const TEB_char* source);

/**
       \brief Like TEB_String_append, however source is saved at the end of the buffer.
       \param [in] last_element_of_the_destination_buffer The last element of the buffer where to copy source.
       \param [in] source      Initial delimiter of the string to be copied (inclusive).
       \param [in] to          Final delimiter of the string to be copied (excluded).
	   \param [in] ends_with_null_character          1 to end the copied string with \0, otherwise 0.	   
       \return The initial element of source copied into the buffer.
       \details The buffer must be large enough to contain source.
    */
TEB_char* TEB_String_append_end (TEB_char* last_element_of_the_destination_buffer,
								 const TEB_char* source,
								 const TEB_char* to, 
								 TEB_bool ends_with_null_character);

/**
       \brief Like TEB_String_append, however source is saved at the end of the buffer.
       \param [in] last_element_of_the_destination_buffer The last element of the buffer where to copy source.
       \param [in] source      String to copy. Must end with \0.
	   \param [in] ends_with_null_character          1 to end the copied string with \0, otherwise 0.	   
       \return The initial element of source copied into the buffer.
       \details The buffer must be large enough to contain source.
    */
TEB_char* TEB_String_append_end2 (TEB_char* last_element_of_the_destination_buffer,
							      const TEB_char* source,
								  TEB_bool ends_with_null_character);

/**
        \brief In input must be entered an integer value between 0 and 9 included; returns it in output converted into char.
        \param [in] number Digit to convert.
        \return The converted digit otherwise 0 if number does not contain a digit between 0 and 9.
    */
TEB_char TEB_String_int_char (TEB_small_u_int digit);

/**
        \brief number must be an integer value >= 0. number is converted into char array and saved in buffer (must be large enough). buffer[0] is msb. The converted value ends with \0. The method returns a pointer to \0 of buffer.
        \param [in] number Number to convert.
        \param [in] buffer Buffer in which to save the converted number.
        \return Pointer to \0 of buffer.
    */
TEB_char* TEB_String_int_str (TEB_big_u_int number, TEB_char* buffer);

/**
        \brief Like the intChar method but the number is saved backwards.
        \param [in] number   Number to convert.
        \param [in] buffer Buffer in which to save the converted number.
        \return Pointer to \0 of buffer.
    */
TEB_char* TEB_String_inv_int_str (TEB_big_u_int number, TEB_char* buffer);

/**
        \brief If c contains one of the following characters:\n ':'  '/' '?' '#' '[' ']' '@' '!' '$' '&' "'" '(' ')' '*' '+' ',' ';' '=' '%' ' '\n the relative value among the following is returned\n %3A %2F %3F  %23 %5B %5D %40 %21 %24 %26 %27 %28 %29 %2A %2B %2C %3B %3D %25 %20.
        \param [in] c Value to convert.
        \return The converted character or 0.
    */
TEB_small_u_int TEB_String_url_encoding_char (TEB_char c);

/**
          \brief Copies source (included) - to (excluded) in destination. destination ends with \0 and a pointer to the latter \0 is returned. If the following characters are present in source:\n ':' '/' '?' '#' '[' ']' '@' '!' '$' '&' "'" '(' ')' '*' '+' ',' ';' '=' '%' ' '\n are replaced with the following relative values:\n %3A  %2F %3F %23 %5B %5D %40 %21 %24 %26 %27 %28 %29 %2A %2B %2C %3B %3D %25 %20.
          \param [in] destination Buffer where to copy source.
          \param [in] source      Initial delimiter of the string to be copied.
          \param [in] to          Final delimiter of the string to be copied.
          \return Pointer to \0 of destination.
    */
TEB_char* TEB_String_url_encoding (TEB_char* destination, const TEB_char* source, const TEB_char* to);

/**
          \brief Copies source (must end with \0) in destination. destination ends with \0 and a pointer to the latter \0 is returned. If the following characters are present in source:\n ':' '/' '?' '#' '[' ']' '@' '!' '$' '&' "'" '(' ')' '*' '+' ',' ';' '=' '%' ' '\n are replaced with the following relative values:\n %3A  %2F %3F %23 %5B %5D %40 %21 %24 %26 %27 %28 %29 %2A %2B %2C %3B %3D %25 %20.
          \param [in] destination Buffer where to copy source.
          \param [in] source    String to copy that must end with \0.
          \return Pointer to \0 of destination.
    */
TEB_char* TEB_String_url_encoding2 (TEB_char* destination, const TEB_char* source);

#ifdef TEB_LibrarySettings_DEBUG_MODE
TEB_small_int TEB_String_test ();
#endif

struct TEB_String_rename_f {
  TEB_size_t (*strlen)(const TEB_char*);
  TEB_small_int (*equals)(const TEB_char*, const TEB_char*, const TEB_char*, const TEB_char*);
  TEB_small_int (*equals2)(const TEB_char*, const TEB_char*);
  TEB_small_int (*equals3)(const TEB_char*, const TEB_char*, const TEB_char*);
  const TEB_char* (*indexOf)(const TEB_char*, const TEB_char*, const TEB_char*, const TEB_char*);
  const TEB_char* (*indexOf2)(const TEB_char*, const TEB_char*);
  const TEB_char* (*indexOf3)(const TEB_char*, const TEB_char*, const TEB_char*);
  const TEB_char* (*lastIndexOf)(const TEB_char*, const TEB_char*, const TEB_char*, const TEB_char*);
  const TEB_char* (*lastIndexOf2)(const TEB_char*, const TEB_char*);
  const TEB_char* (*lastIndexOf3)(const TEB_char*, const TEB_char*, const TEB_char*);
  TEB_char* (*append)(TEB_char*, const TEB_char*, const TEB_char*);
  TEB_char* (*append2)(TEB_char*, const TEB_char*);
  TEB_char* (*appendEnd)(TEB_char*, const TEB_char*, const TEB_char*, TEB_bool);
  TEB_char* (*appendEnd2)(TEB_char*, const TEB_char*, TEB_bool);
  TEB_char (*intChar)(TEB_small_u_int);
  TEB_char* (*intStr)(TEB_big_u_int, TEB_char*);
  TEB_char* (*invIntStr)(TEB_big_u_int, TEB_char*);
  TEB_small_u_int (*urlEncodingChar)(TEB_char);
  TEB_char* (*urlEncoding)(TEB_char*, const TEB_char*, const TEB_char*);
  TEB_char* (*urlEncoding2)(TEB_char*, const TEB_char*);
};

#endif