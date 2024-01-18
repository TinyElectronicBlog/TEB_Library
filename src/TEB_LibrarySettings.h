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

#ifndef TEB_LibrarySettings_h
#define TEB_LibrarySettings_h

/**
	\brief Settings file.
*/

#define TEB_LibrarySettings_SELECT_DEVELOPMENT_ENVIRONMENT 1 /*1 Arduino IDE;
															   2 gcc compiler.*/

#define TEB_LibrarySettings_SELECTED_PROGRAMMING_LANGUAGE 2 /*1 for C, 2 for C++.
															  Beware, some devices do not support both languages.
															  If the C language is selected and there are files with the extension ".cpp" in the 
															  TEB_Library folder and its subfolders, the extension must be changed to ".c";
															  If the C++ language is selected and there are files with the extension ".c" in the 
															  TEB_Library folder and its subfolders, the extension must be changed to ".cpp".
															  It is possible to use the python script "Change extension C - C++.py" to
															  change extensions on the fly.*/	

#define TEB_LibrarySettings_SELECTED_DEVICE_ID 2 /*1 windows pc (supports C and C++);
								                   2 eps32 (supports C++).*/

#define TEB_LibrarySettings_DEBUG_MODE 1 //Commented no debug information is displayed;
									     //1 only information displayed through TEB_debug_print (and various versions);
										 //2 only through TEB_debug_undefined_function, TEB_debug_function_start and TEB_debug_function_end;
										 //3 all debug information is displayed.

#define TEB_LibrarySettings_SELECTED_LANGUAGE 1 /*1 English language;
												  2 Italian language.*/

#define TEB_LibrarySettings_ENABLE_ERRORS  //Uncomment to enable error visualization on the display. It does not affect what is shown on the debug monitor.

#define TEB_LibrarySettings_ENABLE_FATAL_ERRORS  //Uncomment to enable fatal error visualization on the display. It does not affect what is shown on the debug monitor.

//Values used in TEB_OAuth2 files.
#define TEB_OAuth2_API_KEY ""
#define TEB_OAuth2_CLIENT_ID ""
#define TEB_OAuth2_CLIENT_SECRET ""
#define TEB_OAuth2_SERVER_ADDRESS "https://www.googleapis.com"
#define TEB_OAuth2_SERVER_PORT 443
#define TEB_OAuth2_ROOT_CA "-----BEGIN CERTIFICATE-----\nMIIDdTCCAl2gAwIBAgILBAAAAAABFUtaw5QwDQYJKoZIhvcNAQEFBQAwVzELMAkG\nA1UEBhMCQkUxGTAXBgNVBAoTEEdsb2JhbFNpZ24gbnYtc2ExEDAOBgNVBAsTB1Jv\nb3QgQ0ExGzAZBgNVBAMTEkdsb2JhbFNpZ24gUm9vdCBDQTAeFw05ODA5MDExMjAw\nMDBaFw0yODAxMjgxMjAwMDBaMFcxCzAJBgNVBAYTAkJFMRkwFwYDVQQKExBHbG9i\nYWxTaWduIG52LXNhMRAwDgYDVQQLEwdSb290IENBMRswGQYDVQQDExJHbG9iYWxT\naWduIFJvb3QgQ0EwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDaDuaZ\njc6j40+Kfvvxi4Mla+pIH/EqsLmVEQS98GPR4mdmzxzdzxtIK+6NiY6arymAZavp\nxy0Sy6scTHAHoT0KMM0VjU/43dSMUBUc71DuxC73/OlS8pF94G3VNTCOXkNz8kHp\n1Wrjsok6Vjk4bwY8iGlbKk3Fp1S4bInMm/k8yuX9ifUSPJJ4ltbcdG6TRGHRjcdG\nsnUOhugZitVtbNV4FpWi6cgKOOvyJBNPc1STE4U6G7weNLWLBYy5d4ux2x8gkasJ\nU26Qzns3dLlwR5EiUWMWea6xrkEmCMgZK9FGqkjWZCrXgzT/LCrBbBlDSgeF59N8\n9iFo7+ryUp9/k5DPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNVHRMBAf8E\nBTADAQH/MB0GA1UdDgQWBBRge2YaRQ2XyolQL30EzTSo//z9SzANBgkqhkiG9w0B\nAQUFAAOCAQEA1nPnfE920I2/7LqivjTFKDK1fPxsnCwrvQmeU79rXqoRSLblCKOz\nyj1hTdNGCbM+w6DjY1Ub8rrvrTnhQ7k4o+YviiY776BQVvnGCv04zcQLcFGUl5gE\n38NflNUVyRRBnMRddWQVDf9VMOyGj/8N7yy5Y0b2qvzfvGn9LhJIZJrglfCm7ymP\nAbEVtQwdpf5pLGkkeB6zpxxxYu7KyJesF12KwvhHhm4qxFYxldBniYUr+WymXUad\nDKqC5JlR3XC321Y9YeRq4VzW9v493kHMB65jUr9TU/Qr6cf9tveCX4XSQRjbgbME\nHMUfpIBvFSDJ3gyICh3WZlXi/EjJKSZp4A==\n-----END CERTIFICATE-----\n"
#define TEB_OAuth2_HTTP_REQUEST_CONNECTION_TIMEOUT_IN_MS 5000
#define TEB_OAuth2_HTTP_REQUEST_RESPONSE_DELAY_IN_MS 10000
#define TEB_OAuth2_SPLITTABLE_BUFFER_SIZE_FOR_LOGIN 2300
#define TEB_OAuth2_SPLITTABLE_BUFFER_SIZE_FOR_RELOGIN 2100
#define TEB_OAuth2_SPLITTABLE_BUFFER_SIZE_FOR_LOGOUT 2000

//Values used in TEB_GDrive files.
#define TEB_GDrive_HTTP_REQUEST_CONNECTION_TIMEOUT_IN_MS 5000
#define TEB_GDrive_HTTP_REQUEST_RESPONSE_DELAY_IN_MS 10000
#define TEB_GDrive_SPLITTABLE_BUFFER_SIZE_FOR_FOR_CREATE_METADATA_ONLY_FILE 2500
#define TEB_GDrive_SPLITTABLE_BUFFER_SIZE_FOR_FOR_SEARCH_FILE 10000
#define TEB_GDrive_SPLITTABLE_BUFFER_SIZE_FOR_FOR_UPDATE_FILE_METADATA 2500
#define TEB_GDrive_SPLITTABLE_BUFFER_SIZE_FOR_FOR_UPDATE_FILE_CONTENT 10000
#define TEB_GDrive_SPLITTABLE_BUFFER_SIZE_FOR_FOR_GET_FILE_CONTENT 10000
#define TEB_GDrive_SPLITTABLE_BUFFER_SIZE_FOR_FOR_DELETE_FILE 2500
#define TEB_GDrive_SPLITTABLE_BUFFER_SIZE_FOR_FOR_EXPORT_GOOGLE_DOC_CONTENT 10000

//Values used in TEB_RemoteControlInterface files.
#define TEB_RemoteControlInterface_TINY_ELECTRONIC_BLOG_FOLDER_NAME "Tiny%20Electronic%20Blog%20folder"  //Name in URL encoding of the Google Drive folder containing the workspace folders of the Remote Control Android application.



//Following all the multilingual strings used in the library.
#if TEB_LibrarySettings_SELECTED_LANGUAGE == 1  //English language.



#define TEB_error_str0 "ERROR "
#define TEB_error_str1 ": "

#define TEB_fatal_error_str0 "FATAL ERROR "
#define TEB_fatal_error_str1 ": "
#define TEB_fatal_error_str2 "\nPROGRAM EXECUTION IS NOW INTERRUPTED. FIX YOUR CODE AND RUN IT AGAIN!"
#define TEB_fatal_error_str3 "text cannot be NULL."
#define TEB_fatal_error_str4 "Value not allowed for mode."



#elif TEB_LibrarySettings_SELECTED_LANGUAGE == 2  //Italian language.



#define TEB_error_str0 "ERRORE "
#define TEB_error_str1 ": "

#define TEB_fatal_error_str0 "ERRORE FATALE "
#define TEB_fatal_error_str1 ": "
#define TEB_fatal_error_str2 "\nPROGRAMMA INTERROTTO. CORREGGILO ED ESEGUILO DI NUOVO!"
#define TEB_fatal_error_str3 "text non puo' essere NULL."
#define TEB_fatal_error_str4 "Valore non consentito per mode."



#endif

#endif
