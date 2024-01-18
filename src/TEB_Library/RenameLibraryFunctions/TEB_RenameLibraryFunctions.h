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

#ifndef TEB_RenameLibraryFunctions_h
#define TEB_RenameLibraryFunctions_h

#include "../../TEB_LibrarySettings.h"
#include "../DeviceInterfaces/TEB_DeviceInterfaces.h"
#include "../String/TEB_String.h"
#include "../Number/TEB_Number.h"
#include "../Time/TEB_TimeManagement.h"
#include "../Time/TEB_Clock.h"
#include "../Time/TEB_TimeZoneDST.h"
#include "../Buffer/TEB_AbstractArray.h"
#include "../Buffer/TEB_SplittableArray.h"
#include "../Google/TEB_OAuth2.h"
#include "../Google/TEB_GDrive.h"
#include "../Google/TEB_RemoteControlInterface.h"

/**
    \brief Library functions are renamed in this file.
*/

struct TEB_RenameLibraryFunctions_time_rename_f {
  const struct TEB_TimeManagement_rename_f manage;
  const struct TEB_Clock_rename_f clock;
  const struct TEB_TimeZoneDST_rename_f tz;
};

struct TEB_RenameLibraryFunctions_buffer_rename_f {
  const struct TEB_AbstractArray_rename_f abstract;
  const struct TEB_SplittableArray_rename_f splittable;
};

struct TEB_RenameLibraryFunctions_google_rename_f {
  const struct TEB_OAuth2_rename_f oauth2;
  const struct TEB_GDrive_rename_f drive;
  const struct TEB_RemoteControlInterface_rename_f rci;
};

struct TEB_RenameLibraryFunctions {
  const struct TEB_String_rename_f string;
  const struct TEB_Number_rename_f number;
  const struct TEB_RenameLibraryFunctions_time_rename_f time;
  const struct TEB_RenameLibraryFunctions_buffer_rename_f buffer;
  const struct TEB_RenameLibraryFunctions_google_rename_f google;
  const struct TEB_rename_f device;
#ifdef TEB_LibrarySettings_DEBUG_MODE
  TEB_small_int (*generalTest) (void*, const TEB_char*, const TEB_char*, TEB_medium_u_int);
#endif
};

extern const struct TEB_RenameLibraryFunctions teb;

typedef struct TEB_AbstractArray_struct TEB_abstractArray;
typedef struct TEB_http_request TEB_httpRequest;
typedef struct TEB_http_response TEB_httpResponse;
typedef struct TEB_OAuth2_http_response_property TEB_oauth2Property;
typedef struct TEB_Clock_struct TEB_clock;
typedef struct TEB_TimeManagement_struct TEB_timeManagement;
typedef struct TEB_TimeZoneDST_struct TEB_timeZoneDst;

#ifdef TEB_LibrarySettings_DEBUG_MODE
TEB_small_int TEB_RenameLibraryFunctions_test (void* TEB_device_initialization_parameter, const TEB_char* wifi_ssid, const TEB_char* wifi_password, TEB_medium_u_int mode);
#endif

#endif