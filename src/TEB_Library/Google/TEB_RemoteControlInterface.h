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

#ifndef TEB_RemoteControlInterface_h
#define TEB_RemoteControlInterface_h

#include "../../TEB_LibrarySettings.h"
#include "../DeviceInterfaces/TEB_DeviceInterfaces.h"

/**
    \brief The functions of this file are designed to simplify communication between the device and an Android Remote control (for more information see the guide https://sites.google.com/view/tiny-electronic-blog/home/remote-control-for-android-operating-system). Attention, some input parameters of the functions must be provided URL encoded.
*/

/**
       \brief Retrieve the workspace folder ID.
       \param [in] access_token An access token.
       \param [in] workspace_folder_name The workspace folder name. Must be URL encoded.
       \param [in] workspace_folder_id_buffer The buffer in which to save the ID.
       \param [in] function_buffer Buffer needed by the function to execute its instructions. It must be at least TEB_GDrive_SPLITTABLE_BUFFER_SIZE_FOR_FOR_SEARCH_FILE (see TEB_LibrarySettings.h) elements long. If the value NULL is set, the function dynamically allocates a temporary buffer.  
		\return 0 on success, 1 if the Tiny Electronic Blog folder does not exist, 2 if the workspace folder does not exist, otherwise a negative value.
    */
TEB_small_int TEB_RemoteControlInterface_get_workspace_folder_id (const TEB_char* access_token,
                                                                 const TEB_char* workspace_folder_name,
                                                                 TEB_char* workspace_folder_id_buffer,
                                                                 TEB_char* function_buffer);

/**
       \brief Generates a new device file in the workspace folder and returns its ID.
       \param [in] access_token An access token.
       \param [in] device_id The device ID.
       \param [in] workspace_folder_id The workspace folder ID.
       \param [in] device_file_id_buffer The buffer in which to save the ID, even if 1 or -2 is returned.
       \param [in] function_buffer Buffer needed by the function to execute its instructions. It must be at least TEB_GDrive_SPLITTABLE_BUFFER_SIZE_FOR_FOR_CREATE_METADATA_ONLY_FILE (see TEB_LibrarySettings.h) elements long. If the value NULL is set, the function dynamically allocates a temporary buffer.  
		\return 0 on success, 1 if the device file already exists, otherwise a negative value (-2 if there are two or more device files).
    */
TEB_small_int TEB_RemoteControlInterface_new_device_file (const TEB_char* access_token,
                                                         const TEB_char* device_id,
                                                         const TEB_char* workspace_folder_id,
                                                         TEB_char* device_file_id_buffer,
                                                         TEB_char* function_buffer);

/**
       \brief Retrieves the device file ID present in the workspace folder.
       \param [in] access_token An access token.
       \param [in] device_id The device ID. Must be URL encoded.
       \param [in] workspace_folder_id The workspace folder ID.
       \param [in] device_file_id_buffer The buffer in which to save the ID, even if -2 is returned (the first id found is saved in this case).
       \param [in] function_buffer Buffer needed by the function to execute its instructions. It must be at least TEB_GDrive_SPLITTABLE_BUFFER_SIZE_FOR_FOR_SEARCH_FILE (see TEB_LibrarySettings.h) elements long. If the value NULL is set, the function dynamically allocates a temporary buffer.  
		\return 0 on success, 1 if the device file does not exist, otherwise a negative value (-2 if there are two or more device files).
    */
TEB_small_int TEB_RemoteControlInterface_get_device_file_id (const TEB_char* access_token,
                                                            const TEB_char* device_id,
                                                            const TEB_char* workspace_folder_id,
                                                            TEB_char* device_file_id_buffer,
                                                            TEB_char* function_buffer);

/**
       \brief Retrieves the text of the device file present in the workspace folder.
       \param [in] access_token An access token.
       \param [in] device_file_id The device file ID.
       \param [in] text_buffer The buffer in which to save the text.
       \param [in] function_buffer Buffer needed by the function to execute its instructions. It must be at least TEB_GDrive_SPLITTABLE_BUFFER_SIZE_FOR_FOR_GET_FILE_CONTENT (see TEB_LibrarySettings.h) elements long. If the value NULL is set, the function dynamically allocates a temporary buffer.  
       \return 1 on success, otherwise a negative value.
    */
TEB_small_int TEB_RemoteControlInterface_get_device_file_text (const TEB_char* access_token,
                                                              const TEB_char* device_file_id,
                                                              TEB_char* text_buffer,
                                                              TEB_char* function_buffer);

    /**
       \brief Updates the text of the device file present in the workspace folder.
       \param [in] access_token An access token.
       \param [in] device_file_id The device file ID.
       \param [in] text The new text.
       \param [in] function_buffer Buffer needed by the function to execute its instructions. It must be at least TEB_GDrive_SPLITTABLE_BUFFER_SIZE_FOR_FOR_UPDATE_FILE_CONTENT (see TEB_LibrarySettings.h) elements long. If the value NULL is set, the function dynamically allocates a temporary buffer.  
       \return 1 on success, otherwise a negative value.
    */
TEB_small_int TEB_RemoteControlInterface_update_device_file_text (const TEB_char* access_token,
                                                                 const TEB_char* device_file_id,
                                                                 const TEB_char* text,
                                                                 TEB_char* function_buffer);

/**
       \brief Deletes the device file present in the workspace folder.
       \param [in] access_token An access token.
       \param [in] device_file_id The device file ID.
       \param [in] function_buffer Buffer needed by the function to execute its instructions. It must be at least TEB_GDrive_SPLITTABLE_BUFFER_SIZE_FOR_FOR_DELETE_FILE (see TEB_LibrarySettings.h) elements long. If the value NULL is set, the function dynamically allocates a temporary buffer.  
       \return 1 on success, otherwise a negative value.
    */
TEB_small_int TEB_RemoteControlInterface_delete_device_file (const TEB_char* access_token,
                                                            const TEB_char* device_file_id,
                                                            TEB_char* function_buffer);

/**
       \brief Check for ACK of this device in the workspace folder.
       \param [in] access_token An access token.
       \param [in] device_id The device ID. Must be URL encoded.
       \param [in] workspace_folder_id The workspace folder ID.
       \param [in] function_buffer Buffer needed by the function to execute its instructions. It must be at least TEB_GDrive_SPLITTABLE_BUFFER_SIZE_FOR_FOR_SEARCH_FILE (see TEB_LibrarySettings.h) elements long. If the value NULL is set, the function dynamically allocates a temporary buffer.  
       \return 0 if there is at least one ACK, 1 if there are none, otherwise a negative value.
    */
TEB_small_int TEB_RemoteControlInterface_is_there_ack (const TEB_char* access_token,
                                                      const TEB_char* device_id,
                                                      const TEB_char* workspace_folder_id,
                                                      TEB_char* function_buffer);

/**
       \brief Retrieves the name of the oldest command addressed to this device.
       \param [in] access_token An access token.
       \param [in] device_id The device ID.
       \param [in] workspace_folder_id The workspace folder ID.
       \param [in] command_name_buffer The buffer in which to save the name.
       \param [in] function_buffer Buffer needed by the function to execute its instructions. It must be at least TEB_GDrive_SPLITTABLE_BUFFER_SIZE_FOR_FOR_SEARCH_FILE (see TEB_LibrarySettings.h) elements long. If the value NULL is set, the function dynamically allocates a temporary buffer.  
       \return 0 if there is at least one command, 1 if there are none, otherwise a negative value.
    */
TEB_small_int TEB_RemoteControlInterface_get_command (const TEB_char* access_token,
                                                     const TEB_char* device_id,
                                                     const TEB_char* workspace_folder_id,
                                                     TEB_char* command_name_buffer,
                                                     TEB_char* function_buffer);

/**
       \brief Send the ACK for a received command.
       \param [in] access_token An access token.
       \param [in] device_id The device ID.
       \param [in] command_name The command name.
       \param [in] workspace_folder_id The workspace folder ID.
       \param [in] function_buffer Buffer needed by the function to execute its instructions. It must be at least TEB_GDrive_SPLITTABLE_BUFFER_SIZE_FOR_FOR_CREATE_METADATA_ONLY_FILE (see TEB_LibrarySettings.h) elements long. If the value NULL is set, the function dynamically allocates a temporary buffer.  
       \return 1 on success, otherwise a negative value.
    */
TEB_small_int TEB_RemoteControlInterface_send_command_ack (const TEB_char* access_token,
                                                          const TEB_char* device_id,
                                                          const TEB_char* command_name,
                                                          const TEB_char* workspace_folder_id,
                                                          TEB_char* function_buffer);

/**
       \brief Retrieves the name of the oldest custom command addressed to this device.
       \param [in] access_token An access token.
       \param [in] device_id The device ID.
       \param [in] workspace_folder_id The workspace folder ID.
       \param [in] command_name_buffer The buffer in which to save the name.
       \param [in] function_buffer Buffer needed by the function to execute its instructions. It must be at least TEB_GDrive_SPLITTABLE_BUFFER_SIZE_FOR_FOR_SEARCH_FILE (see TEB_LibrarySettings.h) elements long. If the value NULL is set, the function dynamically allocates a temporary buffer.  
       \return 0 if there is at least one command, 1 if there are none, otherwise a negative value.
    */
TEB_small_int TEB_RemoteControlInterface_get_custom_command (const TEB_char* access_token,
                                                            const TEB_char* device_id,
                                                            const TEB_char* workspace_folder_id,
                                                            TEB_char* command_name_buffer,
                                                            TEB_char* function_buffer);

/**
       \brief Delete a custom command (including any duplicates) addressed to this device.
       \param [in] access_token An access token.
       \param [in] device_id The device ID. Must be URL encoded.
       \param [in] command_name The command name. Must be URL encoded.
       \param [in] workspace_folder_id The workspace folder ID.
       \param [in] function_buffer Buffer needed by the function to execute its instructions. It must be at least TEB_GDrive_SPLITTABLE_BUFFER_SIZE_FOR_FOR_SEARCH_FILE (see TEB_LibrarySettings.h) elements long. If the value NULL is set, the function dynamically allocates a temporary buffer.  
       \return 1 on success, otherwise a negative value.
    */
TEB_small_int TEB_RemoteControlInterface_delete_custom_command (const TEB_char* access_token,
                                                               const TEB_char* device_id,
                                                               const TEB_char* command_name,
                                                               const TEB_char* workspace_folder_id,
                                                               TEB_char* function_buffer);

#ifdef TEB_LibrarySettings_DEBUG_MODE
TEB_small_int TEB_RemoteControlInterface_test (const TEB_char* access_token);
#endif

struct TEB_RemoteControlInterface_rename_f {
  TEB_small_int (*getWorkspaceFolderID)(const TEB_char*, const TEB_char*, TEB_char*, TEB_char*);
  TEB_small_int (*newDeviceFile)(const TEB_char*, const TEB_char*, const TEB_char*, TEB_char*, TEB_char*);
  TEB_small_int (*getDeviceFileID)(const TEB_char*, const TEB_char*, const TEB_char*, TEB_char*, TEB_char*);
  TEB_small_int (*getDeviceFileText)(const TEB_char*, const TEB_char*, TEB_char*, TEB_char*);
  TEB_small_int (*updateDeviceFileText)(const TEB_char*, const TEB_char*, const TEB_char*, TEB_char*);
  TEB_small_int (*deleteDeviceFile)(const TEB_char*, const TEB_char*, TEB_char*);
  TEB_small_int (*isThereACK)(const TEB_char*, const TEB_char*, const TEB_char*, TEB_char*);
  TEB_small_int (*getCommand)(const TEB_char*, const TEB_char*, const TEB_char*, TEB_char*, TEB_char*);
  TEB_small_int (*sendCommandACK)(const TEB_char*, const TEB_char*, const TEB_char*, const TEB_char*, TEB_char*);
  TEB_small_int (*getCustomCommand)(const TEB_char*, const TEB_char*, const TEB_char*, TEB_char*, TEB_char*);
  TEB_small_int (*deleteCustomCommand)(const TEB_char*, const TEB_char*, const TEB_char*, const TEB_char*, TEB_char*);
};

#endif
