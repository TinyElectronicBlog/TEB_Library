/*
  MIT License

  Copyright (c) 2022 TinyElectronicBlog

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

#ifndef TEB_Strings_h
#define TEB_Strings_h

#include "../development_board/TEB_Debug.h"
#ifdef TEB_DB_DEBUG
#include "../TEB_Some_global_values.h"
#endif

/**
    \class TEB_Strings
    \brief This class contains various methods for handling strings.
*/
class TEB_Strings {

  public:

    /**
          \brief Looks for the str2 (inclusive) - to2 (excluded) delimited string in the char array delimited by str1 (included) - to1 (excluded) from left to right. Returns a pointer to the str2-to2 string within the char array str1-to1 or -1 if not found.
          \param [in] str1 Initial delimiter of the string in which to look for.
          \param [in] to1  Final delimiter of the string in which to look for.
          \param [in] str2 Initial delimiter of the string to search for.
          \param [in] to2  Final delimiter of the string to search for.
          \return A pointer to the str2-to2 string within the char array str1-to1 or 0 if not found.
    */
    static const char* indexOf (const char* str1, const char* to1, const char* str2, const char* to2);

    /**
          \brief Looks for the str2 string (must ends with \0) in the char array delimited by str1 (included) - to1 (excluded) from left to right. Returns a pointer to the str2 string within the char array str1-to1 or -1 if not found.
          \param [in] str1 Initial delimiter of the string in which to look for.
          \param [in] to1  Final delimiter of the string in which to look for.
          \param [in] str2 Initial delimiter of the string to search for.
          \return A pointer to the str2 string within the char array str1-to1 or 0 if not found.
    */
    static const char* indexOf (const char* str1, const char* to1, const char* str2);

    /**
          \brief Looks for the str2 string (must ends with \0) in the char array str1 (must ends with \0) from left to right. Returns a pointer to str2 string within str1 or -1 if not found.
          \param [in] str1 Initial delimiter of the string in which to look for.
          \param [in] str2 Initial delimiter of the string to search for.
          \return A pointer to the str2 string within the char array str1 or 0 if not found.
    */
    static const char* indexOf (const char* str1, const char* str2);

    /**
          \brief Like the indexOf method but the search is done from right to left.
          \param [in] str1 Initial delimiter of the string in which to look for.
          \param [in] to1  Final delimiter of the string in which to look for.
          \param [in] str2 Initial delimiter of the string to search for.
          \param [in] to2  Final delimiter of the string to search for.
          \return A pointer to the str2-to2 string within the char array str1-to1 or 0 if not found.
    */
    static const char* lastIndexOf (const char* str1, const char* to1, const char* str2, const char* to2);

    /**
        \brief Like the indexOf method but the search is done from right to left.
        \param [in] str1 Initial delimiter of the string in which to look for.
        \param [in] to1  Final delimiter of the string in which to look for.
        \param [in] str2 Initial delimiter of the string to search for.
        \return A pointer to the str2 string within the char array str1-to1 or 0 if not found.
    */
    static const char* lastIndexOf (const char* str1, const char* to1, const char* str2);

    /**
          \brief Like the index_of method but the search is done from right to left.
          \param [in] str1 Initial delimiter of the string in which to look for.
          \param [in] str2 Initial delimiter of the string to search for.
          \return A pointer to the str2 string within the char array str1 or 0 if not found.
    */
    static const char* lastIndexOf (const char* str1, const char* str2);

    /**
       \brief Add source in destination. The string to copy is delimited by source (inclusive) and to (excluded). destination ends with \0. Returns a pointer to the \0 of destination.
       \param [in] destination Buffer where to copy source.
       \param [in] source      Initial delimiter of the string to be copied.
       \param [in] to          Final delimiter of the string to be copied.
       \return A pointer to the \0 of destination.
       \details destination must be large enough to contain source.
    */
    static char* append (char* destination, const char* source, const char* to);

    /**
        \brief Add source in destination. source must end with \0. destination ends with \0. Returns a pointer to the \0 of destination.
        \param [in] destination Buffer where to copy source.
        \param [in] source      String to copy.
        \return A pointer to the \0 of destination.
        \details destination must be large enough to contain source.
    */
    static char* append (char* destination, const char* source);

    /**
        \brief Like the append method but for PROGMEM strings.
        \param [in] destination Buffer where to copy source.
        \param [in] source PROGMEM string to copy.
        \return A pointer to the \0 of destination.
        \details destination must be large enough to contain source.
    */
    static char* append_P (char* destination, const char* source);

    /**
       \brief Add source in destination. source is a PROGMEM string. Returns a pointer to the \0 of destination.
       \param [in] destination Buffer where to copy source.
       \param [in] source PROGMEM string to be copied.
       \param [in] sourceLength Length of source.
       \return A pointer to the \0 of destination.
       \details destination must be large enough to contain source.
    */
    static char* append_P (char* destination, const char* source, size_t sourceLength);

    /**
        \brief In input must be entered an integer value between 0 and 9 included; returns it in output converted into char.
        \param [in] number Digit to convert.
        \return The converted digit otherwise 0 if number does not contain a digit between 0 and 9.
    */
    static char intChar (uint8_t number);

    /**
        \brief number must be an integer value >= 0. number is converted into char array and saved in buffer (must be large enough). buffer[0] is msb. The converted value ends with \0. The method returns a pointer to \0 of buffer.
        \param [in] number Number to convert.
        \param [in] buffer Buffer in which to save the converted number.
        \return Pointer to \0 of buffer.
    */
    static char* intChar (uint32_t number, char* buffer);

    /**
        \brief Like the intChar method but the number is saved backwards.
        \param [in] number   Number to convert.
        \param [in] buffer Buffer in which to save the converted number.
        \return Pointer to \0 of buffer.
    */
    static char* invIntChar (uint32_t number, char* buffer);

    /**
        \brief If c contains one of the following characters:\n ':'  '/' '?' '#' '[' ']' '@' '!' '$' '&' "'" '(' ')' '*' '+' ',' ';' '=' '%' ' '\n the relative value among the following is returned\n %3A %2F %3F  %23 %5B %5D %40 %21 %24 %26 %27 %28 %29 %2A %2B %2C %3B %3D %25 %20.
        \param [in] c Value to convert.
        \return The converted character or 0.
    */
    static uint8_t percentEncoding (char c);

    /**
          \brief Copies source (included) - to (excluded) in destination. destination ends with \0 and a pointer to the latter \0 is returned. If the following characters are present in source:\n ':' '/' '?' '#' '[' ']' '@' '!' '$' '&' "'" '(' ')' '*' '+' ',' ';' '=' '%' ' '\n are replaced with the following relative values:\n %3A  %2F %3F %23 %5B %5D %40 %21 %24 %26 %27 %28 %29 %2A %2B %2C %3B %3D %25 %20.
          \param [in] destination Buffer where to copy source.
          \param [in] source      Initial delimiter of the string to be copied.
          \param [in] to          Final delimiter of the string to be copied.
          \return Pointer to \0 of destination.
    */
    static char* percentEncoding (char* destination, const char* source, const char* to);

    /**
          \brief Copies source (must end with \0) in destination. destination ends with \0 and a pointer to the latter \0 is returned. If the following characters are present in source:\n ':' '/' '?' '#' '[' ']' '@' '!' '$' '&' "'" '(' ')' '*' '+' ',' ';' '=' '%' ' '\n are replaced with the following relative values:\n %3A  %2F %3F %23 %5B %5D %40 %21 %24 %26 %27 %28 %29 %2A %2B %2C %3B %3D %25 %20.
          \param [in] destination Buffer where to copy source.
          \param [in] source    String to copy that must end with \0.
          \return Pointer to \0 of destination.
    */static char* percentEncoding (char* destination, const char* source);

#ifdef TEB_DB_DEBUG
    static void test ();
#endif

};

#endif