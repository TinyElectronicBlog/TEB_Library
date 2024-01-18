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

#ifndef TEB_GDrive_h
#define TEB_GDrive_h

#include "../../TEB_LibrarySettings.h"
#include "../DeviceInterfaces/TEB_DeviceInterfaces.h"

/**
    \brief The functions of this file allow basic management of files on Google Drive. For more information see https://developers.google.com/drive/api/v3/reference. These functions require an access token which can be obtained with TEB_OAuth2. Attention, some input parameters of the functions must be provided URL encoded; to know which ones precisely (the information in this file may be inaccurate), you can help yourself with the "Try this method" function present in the online Google documentation of a method (e.g. https://developers.google.com/drive/api/v3/reference/about/get).
*/

/**
       \brief Creates a new file.
	   \param [in] access_token An access token.
       \param [in] name File name. It cannot be NULL.
       \param [in] parents The ID of the parent folder (insert one only).
       \param [in] mime_type The MIME type of the file.
       \param [in] file_id_buffer Buffer in which the ID of the created file is saved. It cannot be NULL.
       \param [in] function_buffer Buffer needed by the function to execute its instructions. It must be at least TEB_GDrive_SPLITTABLE_BUFFER_SIZE_FOR_FOR_CREATE_METADATA_ONLY_FILE (see TEB_LibrarySettings.h) elements long. If the value NULL is set, the function dynamically allocates a temporary buffer. 
       \return 1 on success, otherwise a negative value.
       \details parents and mime_type are optional parameters. For more information see https://developers.google.com/drive/api/v3/reference/files/create.
    */
TEB_small_int TEB_GDrive_create_metadata_only_file (const TEB_char* access_token,
                                                   const TEB_char* name,
                                                   const TEB_char* parents,
                                                   const TEB_char* mime_type,
                                                   TEB_char* file_id_buffer,
                                                   TEB_char* function_buffer);

/**
       \brief Updates a file's metadata to rename or move a file.
	   	   \param [in] access_token An access token.
       \param [in] file_id It cannot be NULL.
       \param [in] file_name The new file name.
       \param [in] add_parents The ID of the new parent folder (insert one only) where to move the file.
       \param [in] remove_parents The ID of the old parent folder (insert one only).
        \param [in] function_buffer Buffer needed by the function to execute its instructions. It must be at least TEB_GDrive_SPLITTABLE_BUFFER_SIZE_FOR_FOR_UPDATE_FILE_METADATA (see TEB_LibrarySettings.h) elements long. If the value NULL is set, the function dynamically allocates a temporary buffer. 
      \return 1 on success, otherwise a negative value.
       \details file_name, add_parents and remove_parents are optional parameters. For more information see https://developers.google.com/drive/api/v3/reference/files/update.
    */
TEB_small_int TEB_GDrive_update_file_metadata (const TEB_char* access_token,
                                              const TEB_char* file_id,
                                              const TEB_char* file_name,
                                              const TEB_char* add_parents,
                                              const TEB_char* remove_parents,
                                              TEB_char* function_buffer);

/**
       \brief Updates a file's content.
   	   \param [in] access_token An access token.
       \param [in] file_id It cannot be NULL.
       \param [in] file_content The new file content. It cannot be NULL.
       \param [in] mime_type The new MIME type of the file. It cannot be NULL.
       \param [in] function_buffer Buffer needed by the function to execute its instructions. It must be at least TEB_GDrive_SPLITTABLE_BUFFER_SIZE_FOR_FOR_UPDATE_FILE_CONTENT (see TEB_LibrarySettings.h) elements long. If the value NULL is set, the function dynamically allocates a temporary buffer. 
       \return 1 on success, otherwise a negative value.
       \details For more information see https://developers.google.com/drive/api/v3/reference/files/update.
    */
TEB_small_int TEB_GDrive_update_file_content (const TEB_char* access_token,
                                             const TEB_char* file_id,
                                             const TEB_char* file_content,
                                             const TEB_char* mime_type,
                                             TEB_char* function_buffer);

/**
       \brief Searches files.
	   \param [in] access_token An access token.
       \param [in] q A query for filtering the results.
       \param [in] order_by A list of sort keys.
       \param [in] fields The paths of the fields you want included in the response.
       \param [in] page_size The maximum number of files to return per page. Enter 0 to set the default value.
       \param [in] page_token The token for continuing a previous request.
       \param [in] response_buffer Buffer in which the body of the http response is saved. It cannot be NULL.
        \param [in] function_buffer Buffer needed by the function to execute its instructions. It must be at least TEB_GDrive_SPLITTABLE_BUFFER_SIZE_FOR_FOR_SEARCH_FILE (see TEB_LibrarySettings.h) elements long. If the value NULL is set, the function dynamically allocates a temporary buffer. 
		\return 1 on success, otherwise a negative value.
       \details q, order_by, fields, page_size and page_token are optional parameters. For more information see https://developers.google.com/drive/api/v3/reference/files/list.
    */
TEB_small_int TEB_GDrive_search_file (const TEB_char* access_token,
                                     const TEB_char* q,
                                     const TEB_char* order_by,
                                     const TEB_char* fields,
                                     TEB_medium_u_int page_size,
                                     const TEB_char* page_token,
                                     TEB_char* response_buffer,
                                     TEB_char* function_buffer);

/**
       \brief Gets a file's content.
   	   \param [in] access_token An access token.
       \param [in] file_id It cannot be NULL.
       \param [in] response_buffer Buffer in which the contents of the file is saved. It cannot be NULL.
       \param [in] function_buffer Buffer needed by the function to execute its instructions. It must be at least TEB_GDrive_SPLITTABLE_BUFFER_SIZE_FOR_FOR_GET_FILE_CONTENT (see TEB_LibrarySettings.h) elements long. If the value NULL is set, the function dynamically allocates a temporary buffer. 
	   \return 1 on success, otherwise a negative value.
       \details For more information see https://developers.google.com/drive/api/v3/reference/files/get.
    */
TEB_small_int TEB_GDrive_get_file_content (const TEB_char* access_token,
                                          const TEB_char* file_id,
                                          TEB_char* response_buffer,
                                          TEB_char* function_buffer);

/**
       \brief Permanently deletes a file.
   	   \param [in] access_token An access token.
       \param [in] file_id It cannot be NULL.
       \param [in] function_buffer Buffer needed by the function to execute its instructions. It must be at least TEB_GDrive_SPLITTABLE_BUFFER_SIZE_FOR_FOR_DELETE_FILE (see TEB_LibrarySettings.h) elements long. If the value NULL is set, the function dynamically allocates a temporary buffer. 
	   \return 1 on success, otherwise a negative value.
       \details For more information see https://developers.google.com/drive/api/v3/reference/files/delete.
    */
TEB_small_int TEB_GDrive_delete_file (const TEB_char* access_token,
                                     const TEB_char* file_id,
                                     TEB_char* function_buffer);

/**
       \brief Exports a Google Doc.
        \param [in] access_token An access token.
		\param [in] file_id It cannot be NULL.
       \param [in] mime_type MIME type export. It cannot be NULL.
       \param [in] response_buffer Buffer in which the contents of the file is saved. It cannot be NULL.
        \param [in] function_buffer Buffer needed by the function to execute its instructions. It must be at least TEB_GDrive_SPLITTABLE_BUFFER_SIZE_FOR_FOR_EXPORT_GOOGLE_DOC_CONTENT (see TEB_LibrarySettings.h) elements long. If the value NULL is set, the function dynamically allocates a temporary buffer. 
		\return 1 on success, otherwise a negative value.
       \details For more information see https:developers.google.com/drive/api/v3/reference/files/export.
    */
TEB_small_int TEB_GDrive_export_google_document (const TEB_char* access_token,
                                                const TEB_char* file_id,
                                                const TEB_char* mime_type,
                                                TEB_char* response_buffer,
                                                TEB_char* function_buffer);
												
/**
       \brief Algorithm for receiving an HTTP response used in TEB_GDrive.
    */
TEB_char* TEB_GDrive_response_reception_algorithm (TEB_char* response_buffer,
                                                  TEB_size_t response_buffer_length,
                                                  TEB_time_t response_delay_in_ms,
                                                  void* additional_parameters,
												  TEB_medium_u_int mode);

#ifdef TEB_LibrarySettings_DEBUG_MODE
TEB_small_int TEB_GDrive_test (const TEB_char* access_token);
#endif

struct TEB_GDrive_rename_f {
  TEB_small_int (*createMetadataOnlyFile)(const TEB_char*, const TEB_char*, const TEB_char*, const TEB_char*, TEB_char*, TEB_char*);
  TEB_small_int (*updateFileMetadata)(const TEB_char*, const TEB_char*, const TEB_char*, const TEB_char*, const TEB_char*, TEB_char*);
  TEB_small_int (*updateFileContent)(const TEB_char*, const TEB_char*, const TEB_char*, const TEB_char*, TEB_char*);
  TEB_small_int (*searchFile)(const TEB_char*, const TEB_char*, const TEB_char*, const TEB_char*, TEB_medium_u_int, const TEB_char*, TEB_char*, TEB_char*);
  TEB_small_int (*getFileContent)(const TEB_char*, const TEB_char*, TEB_char*, TEB_char*);
  TEB_small_int (*deleteFile)(const TEB_char*, const TEB_char*, TEB_char*);
  TEB_small_int (*exportGoogleDocument)(const TEB_char*, const TEB_char*, const TEB_char*, TEB_char*, TEB_char*);
  TEB_char* (*responseReceptionAlgorithm)(TEB_char*, TEB_size_t, TEB_time_t, void*, TEB_medium_u_int);
};

#endif