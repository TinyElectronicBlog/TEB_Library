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

#ifndef TEB_AbstractArray_h
#define TEB_AbstractArray_h

#include "../../TEB_LibrarySettings.h"
#include "../DeviceInterfaces/TEB_DeviceInterfaces.h"

/**
    \brief The link https://learn.adafruit.com/memories-of-an-arduino/optimizing-sram explains how to optimize the use of sram; in summary, it is better to prefer local allocations because they do not create heap fragmentation and do not remain permanently in memory. However, global and dynamic allocations are mandatory choices when working with very large variables, as they allow you to allocate more memory than local ones.\n An instance of this class can act as an interface to any array, regardless of the allocation and data type. The functions of the class allow you to manage the array by hiding it from the rest of the code; this makes it easier to replace an array without rewriting many lines of code.
*/

/**
	    pointer: pointer to the memory location of the associated array;
	   sizeof_one_element: size of an array element (e.g. sizeof(int) for an array of int);
	   length: number of array elements;
	   allocation_mode: 1 if a new dynamically allocated array is associated, 2 one already instantiated, another value if nothing is associated.
    */
struct TEB_AbstractArray_struct {
  void* pointer;
  TEB_size_t sizeof_one_element;
  TEB_size_t length;
  TEB_small_u_int allocation_mode;
};

/**
        \param [in]  abstract_array_to_initialize The struct TEB_AbstractArray_struct to be initialized.
        \param [in] sizeof_one_array_element Size of an array element (e.g. sizeof(int) for an array of int).
        \param [in] array_length Number of array elements.
        \param [in] optional_instantiated_buffer_to_associate A pointer to the array to associate or NULL to associate a new dynamically allocated array.
        \return 1 if all ok.
    */
TEB_small_int TEB_AbstractArray_new_array (struct TEB_AbstractArray_struct* abstract_array_to_initialize,
									       TEB_size_t sizeof_one_array_element,
										   TEB_size_t array_length,
										   void* optional_instantiated_buffer_to_associate);

/**
         \brief Deinitializes a struct TEB_AbstractArray_struct.
         \param [in] abstract_array_to_delete The struct TEB_AbstractArray_struct to be deinitialized.
         \return 1 if everything is ok.
    */
TEB_small_int TEB_AbstractArray_delete_array (struct TEB_AbstractArray_struct* abstract_array_to_delete);

/**
         \param [in] abstract_array A struct TEB_AbstractArray_struct.
         \return pointer of the struct TEB_AbstractArray_struct.
    */
void* TEB_AbstractArray_get_pointer (struct TEB_AbstractArray_struct* abstract_array);

/**
         \param [in] abstract_array A struct TEB_AbstractArray_struct.
         \return sizeof_one_element of the struct TEB_AbstractArray_struct.
    */
TEB_size_t TEB_AbstractArray_get_sizeof_one_element (struct TEB_AbstractArray_struct* abstract_array);

/**
         \param [in] abstract_array A struct TEB_AbstractArray_struct.
         \return length of the struct TEB_AbstractArray_struct.
    */
TEB_size_t TEB_AbstractArray_get_length (struct TEB_AbstractArray_struct* abstract_array);

/**
         \param [in] abstract_array A struct TEB_AbstractArray_struct.
         \return allocation_mode of the struct TEB_AbstractArray_struct.
    */
TEB_small_u_int TEB_AbstractArray_get_allocation_mode (struct TEB_AbstractArray_struct* abstract_array);

#ifdef TEB_LibrarySettings_DEBUG_MODE
TEB_small_int TEB_AbstractArray_test ();
#endif

struct TEB_AbstractArray_rename_f {
  TEB_small_int (*newArray)(struct TEB_AbstractArray_struct*, TEB_size_t, TEB_size_t, void*);
  TEB_small_int (*deleteArray)(struct TEB_AbstractArray_struct*);
  void* (*pointer)(struct TEB_AbstractArray_struct*);
  TEB_size_t (*sizeofOneElement)(struct TEB_AbstractArray_struct*);
  TEB_size_t (*length)(struct TEB_AbstractArray_struct*);
  TEB_small_u_int (*allocationMode)(struct TEB_AbstractArray_struct*);
};

#endif