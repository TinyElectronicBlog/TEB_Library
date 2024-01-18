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

#ifndef TEB_Library_h
#define TEB_Library_h

#include "TEB_LibrarySettings.h"

#if TEB_LibrarySettings_SELECTED_PROGRAMMING_LANGUAGE == 1  //C

#if TEB_LibrarySettings_SELECT_DEVELOPMENT_ENVIRONMENT == 2
#include "TEB_Library/Buffer/TEB_AbstractArray.c"
#include "TEB_Library/Buffer/TEB_SplittableArray.c"
#include "TEB_Library/DeviceInterfaces/TEB_DeviceInterfaces.c"
#include "TEB_Library/Number/TEB_Number.c"
#include "TEB_Library/String/TEB_String.c"
#include "TEB_Library/Time/TEB_TimeManagement.c"
#include "TEB_Library/Time/TEB_Clock.c"
#include "TEB_Library/Time/TEB_TimeZoneDST.c"
#include "TEB_Library/RenameLibraryFunctions\TEB_RenameLibraryFunctions.c"
#include "TEB_Library/Google\TEB_GDrive.c"
#include "TEB_Library/Google\TEB_OAuth2.c"
#include "TEB_Library/Google\TEB_RemoteControlInterface.c"
#endif
#include "TEB_Library/RenameLibraryFunctions/TEB_RenameLibraryFunctions.h"

#endif

#if TEB_LibrarySettings_SELECTED_PROGRAMMING_LANGUAGE == 2 //C++

#if TEB_LibrarySettings_SELECT_DEVELOPMENT_ENVIRONMENT == 2
#include "TEB_Library/Buffer/TEB_AbstractArray.cpp"
#include "TEB_Library/Buffer/TEB_SplittableArray.cpp"
#include "TEB_Library/DeviceInterfaces/TEB_DeviceInterfaces.cpp"
#include "TEB_Library/Number/TEB_Number.cpp"
#include "TEB_Library/String/TEB_String.cpp"
#include "TEB_Library/Time/TEB_TimeManagement.cpp"
#include "TEB_Library/Time/TEB_Clock.cpp"
#include "TEB_Library/Time/TEB_TimeZoneDST.cpp"
#include "TEB_Library/RenameLibraryFunctions\TEB_RenameLibraryFunctions.cpp"
#include "TEB_Library/Google\TEB_GDrive.cpp"
#include "TEB_Library/Google\TEB_OAuth2.cpp"
#include "TEB_Library/Google\TEB_RemoteControlInterface.cpp"
#endif
#include "TEB_Library/RenameLibraryFunctions/TEB_RenameLibraryFunctions.h"

#endif

#endif
