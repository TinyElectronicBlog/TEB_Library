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

#ifndef TEB_Drive_Remote_Control_Interface_h
#define TEB_Drive_Remote_Control_Interface_h

/**
    \class TEB_Drive_Remote_Control_Interface
    \brief This class is designed to simplify communication between the development board and an Android Remote control (for more information see the guide https://sites.google.com/view/tiny-electronic-blog/home/remote-control-for-android-operating-system). Before you can use it, you need to initialize the TEB_Drive class. Attention, some input parameters of the functions must be provided URL encoded.
*/
class TEB_Drive_Remote_Control_Interface
{
  private:

    static const char str1[];
    static const char str2[];
    static const char str3[];
    static const char str4[];
    static const char str5[];
    static const char str6[];
    static const char str7[];
    static const char str8[];
    static const char str9[];
    static const char str10[];
    static const char str11[];
    static const char str12[];
    static const char str13[];
    static const char str14[];
    static const char str15[];
    static const char str16[];
    static const char str17[];
    static const char str18[];
    static const char str19[];
    static const char str20[];
    static const char str21[];

  public:

    /**
       \brief Retrieve the workspace folder ID.
       \param [in] workspaceFolderName The workspace folder name. Must be URL encoded.
       \param [in] workspaceFolderIDBuffer The buffer in which to save the ID.
       \return 0 on success, 1 if the Tiny Electronic Blog folder does not exist, 2 if the workspace folder does not exist, otherwise a negative value.
    */
    static int8_t getWorkspaceFolderID (const char* workspaceFolderName, char* workspaceFolderIDBuffer);

    /**
       \brief Generates a new device file in the workspace folder and returns its ID.
       \param [in] deviceID The device ID.
       \param [in] workspaceFolderID The workspace folder ID.
       \param [in] deviceFileIDBuffer The buffer in which to save the ID (even if it returns 1).
       \return 0 on success, 1 if the device file already exists, otherwise a negative value.
    */
    static int8_t newDeviceFile (const char* deviceID, const char* workspaceFolderID, char* deviceFileIDBuffer);

    /**
       \brief Retrieves the device file ID present in the workspace folder.
       \param [in] deviceID The device ID. Must be URL encoded.
       \param [in] workspaceFolderID The workspace folder ID.
       \param [in] deviceFileIDBuffer The buffer in which to save the ID.
       \return 0 on success, 1 if the device file does not exist, otherwise a negative value.
    */
    static int8_t getDeviceFileID (const char* deviceID, const char* workspaceFolderID, char* deviceFileIDBuffer);

    /**
       \brief Retrieves the text of the device file present in the workspace folder.
       \param [in] deviceFileID The device file ID.
       \param [in] textBuffer The buffer in which to save the text.
       \return 1 on success, otherwise a negative value.
    */
    static int8_t getDeviceFileText (const char* deviceFileID, char* textBuffer);

    /**
       \brief Updates the text of the device file present in the workspace folder.
       \param [in] deviceFileID The device file ID.
       \param [in] text The new text.
       \return 1 on success, otherwise a negative value.
    */
    static int8_t updateDeviceFileText (const char* deviceFileID, const char* text);

    /**
       \brief Deletes the device file present in the workspace folder.
       \param [in] deviceFileID The device file ID.
       \return 1 on success, otherwise a negative value.
    */
    static int8_t deleteDeviceFile (const char* deviceFileID);

    /**
       \brief Check for ACK of this device in the workspace folder.
       \param [in] deviceID The device ID. Must be URL encoded.
       \param [in] workspaceFolderID The workspace folder ID.
       \return 0 if there is at least one ACK, 1 if there are none, otherwise a negative value.
    */
    static int8_t isThereACK (const char* deviceID, const char* workspaceFolderID);

    /**
       \brief Retrieves the name of the oldest command addressed to this device.
       \param [in] deviceID The device ID.
       \param [in] workspaceFolderID The workspace folder ID.
       \param [in] commandNameBuffer The buffer in which to save the name.
       \return 0 if there is at least one command, 1 if there are none, otherwise a negative value.
    */
    static int8_t getCommand (const char* deviceID, const char* workspaceFolderID, char* commandNameBuffer);

    /**
       \brief Send the ACK for a received command.
       \param [in] deviceID The device ID.
       \param [in] commandName The command name.
       \param [in] workspaceFolderID The workspace folder ID.
       \return 1 on success, otherwise a negative value.
    */
    static int8_t sendCommandACK (const char* deviceID, const char* commandName, const char* workspaceFolderID);

    /**
       \brief Retrieves the name of the oldest custom command addressed to this device.
       \param [in] deviceID The device ID.
       \param [in] workspaceFolderID The workspace folder ID.
       \param [in] commandNameBuffer The buffer in which to save the name.
       \return 0 if there is at least one command, 1 if there are none, otherwise a negative value.
    */
    static int8_t getCustomCommand (const char* deviceID, const char* workspaceFolderID, char* commandNameBuffer);

    /**
       \brief Delete a custom command (including any duplicates) addressed to this device.
       \param [in] deviceID The device ID. Must be URL encoded.
       \param [in] commandName The command name. Must be URL encoded.
       \param [in] workspaceFolderID The workspace folder ID.
       \return 1 on success, otherwise a negative value.
    */
    static int8_t deleteCustomCommand (const char* deviceID, const char* commandName, const char* workspaceFolderID);

#ifdef TEB_DB_DEBUG
    static void test (const char* ssid, const char* password, uint32_t timeOut);
#endif

};

#endif