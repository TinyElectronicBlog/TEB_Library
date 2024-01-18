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

#ifndef TEB_SplittableArray_h
#define TEB_SplittableArray_h

#include "TEB_AbstractArray.h"

/**
    \brief The functions in this file treat the struct TEB_AbstractArray_struct as large arrays that can be split into sub-arrays.
*/

/**
        \brief Initialize a splittable array.
        \param [in] sizeof_one_array_element Size of an array element (e.g. sizeof(int) for an array of int).
        \param [in] array_length Number of array elements.
        \param [in] optional_instantiated_buffer_to_associate A pointer to the array to associate or NULL to associate a new dynamically allocated array.
        \return id of the initialized splittable array (the first is 1, the second 2 ...), otherwise 0 in case of problems.
    */
TEB_size_t TEB_SplittableArray_new_array (TEB_size_t sizeof_one_array_element,
                                         TEB_size_t array_length,
                                         void* optional_instantiated_buffer_to_associate);

/**
         \brief Deinitializes the last splittable array initialized.
         \return 1 if everything is ok.
    */
TEB_small_int TEB_SplittableArray_delete_last_array ();

/**   
         \brief Save data or reserve empty space at the beginning of the splittable array.
         \param [in] splittable_array_index ID of the splittable array.
         \param [in] elements_to_store Elements to store.
         \param [in] number_of_elements_to_store Number of elements to store.
         \return 1 if everything is ok.
    */
TEB_small_int TEB_SplittableArray_add_elements (TEB_size_t splittable_array_index,
                                               const void* elements_to_store,
                                               TEB_size_t number_of_elements_to_store);

/**   
         \brief Saves data temporarily at the end of the splittable array. A new execution of this function overwrites the previous data.
         \param [in] splittable_array_index ID of the splittable array.
         \param [in] elements_to_store_temporarily_to_the_end_of_the_buffer Elements to store.
         \param [in] number_of_elements_to_store Number of elements to store.
         \return A pointer to the data saved in the splittable buffer.
    */
void* TEB_SplittableArray_add_elements_end (TEB_size_t splittable_array_index,
                                           const void* elements_to_store_temporarily_to_the_end_of_the_buffer,
                                           TEB_size_t number_of_elements_to_store);

/** 
         \brief Creates a sub-array with the data stored at the beginning of the splittable array using TEB_SplittableArray_add_elements. Adding additional data will not overwrite the sub-array.
         \param [in] splittable_array_index ID of the splittable array.
         \return A pointer to the sub-array.
    */
void* TEB_SplittableArray_split_array (TEB_size_t splittable_array_index);

/** 
         \param [in] splittable_array_index ID of the splittable array.
         \return Last element of the array (takes into account the size of an element).
    */
void* TEB_SplittableArray_last_element_pointer (TEB_size_t splittable_array_index);

/** 
         \brief Deletes sub-arrays created with TEB_SplittableArray_split_array.
         \param [in] splittable_array_index ID of the splittable array.
         \param [in] from_address_returned_by_split_array Enter one of the pointers returned by TEB_SplittableArray_split_array.
         \return 1 if all ok.
		 \details All sub-arrays created from_address_returned_by_split_array onward are deleted.
    */
TEB_small_int TEB_SplittableArray_release_elements (TEB_size_t splittable_array_index, 
										         void* from_address_returned_by_split_array);

/** 
         \brief Deletes all sub-arrays of a splittable array created with TEB_SplittableArray_split_array.
         \param [in] splittable_array_index ID of the splittable array.
         \return 1 if all ok.
    */
TEB_small_int TEB_SplittableArray_reset_array (TEB_size_t splittable_array_index);

/** 
         \param [in] splittable_array_index ID of the splittable array.
         \return The number of free elements (those not occupied by sub-arrays) of a splittable array.
    */
TEB_size_t TEB_SplittableArray_number_of_free_elements (TEB_size_t splittable_array_index);

/** 
         \param [in] splittable_array_index ID of the splittable array.
         \return The number of occupied elements (those occupied by sub-arrays) of a splittable array.
    */
TEB_size_t TEB_SplittableArray_number_of_occupied_elements (TEB_size_t splittable_array_index);

/** 
         \return The number of allocated splittable arrays.
    */
TEB_size_t TEB_SplittableArray_number_of_allocated_arrays ();

#ifdef TEB_LibrarySettings_DEBUG_MODE
TEB_small_int TEB_SplittableArray_test ();
#endif

struct TEB_SplittableArray_rename_f {
  TEB_size_t (*newArray)(TEB_size_t, TEB_size_t, void*);
  TEB_small_int (*deleteLastArray)();
  TEB_small_int (*add)(TEB_size_t, const void*, TEB_size_t);
  void* (*addEnd)(TEB_size_t, const void*, TEB_size_t);
  void* (*split)(TEB_size_t);
  void* (*lastElement)(TEB_size_t);
  TEB_small_int (*release)(TEB_size_t, void*);
  TEB_small_int (*reset)(TEB_size_t);
  TEB_size_t (*freeElements)(TEB_size_t);
  TEB_size_t (*occupiedElements)(TEB_size_t);
  TEB_size_t (*numberOfAllocatedArrays)();
};

#endif
