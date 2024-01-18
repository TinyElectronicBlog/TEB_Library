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

#include "TEB_AbstractArray.h"
#include "../String/TEB_String.h"
#include "../Number/TEB_Number.h"

TEB_small_int TEB_AbstractArray_new_array (struct TEB_AbstractArray_struct* abstract_array_to_initialize,
									       TEB_size_t sizeof_one_array_element,
										   TEB_size_t array_length,
										   void* optional_instantiated_buffer_to_associate) {
  TEB_debug_function_start("TEB_AbstractArray_new_array");
  if (abstract_array_to_initialize == TEB_NULL_POINTER) TEB_fatal_error(1, "abstract_array_to_initialize cannot be NULL.", 2);
  if (abstract_array_to_initialize->allocation_mode == 1 || abstract_array_to_initialize->allocation_mode == 2) TEB_fatal_error(377, "It is not possible to initialize an already instantiated TEB_AbstractArray_struct.", 2);
  if (sizeof_one_array_element == 0) TEB_fatal_error(3, "Value not allowed for sizeof_one_array_element.", 2);
  if (array_length == 0) TEB_fatal_error(4, "Value not allowed for array_length.", 2);
  abstract_array_to_initialize->sizeof_one_element = sizeof_one_array_element;
  abstract_array_to_initialize->length = array_length;
  if (optional_instantiated_buffer_to_associate == TEB_NULL_POINTER) {
    abstract_array_to_initialize->allocation_mode = 1;
    abstract_array_to_initialize->pointer = malloc(sizeof_one_array_element * array_length);
  } else {
    abstract_array_to_initialize->allocation_mode = 2;
    abstract_array_to_initialize->pointer = optional_instantiated_buffer_to_associate;
  }
  return TEB_debug_function_end(1);
}

TEB_small_int TEB_AbstractArray_delete_array (struct TEB_AbstractArray_struct* abstract_array_to_delete) {
  TEB_debug_function_start("TEB_AbstractArray_delete_array");
  if (abstract_array_to_delete == TEB_NULL_POINTER) TEB_fatal_error(5, "abstract_array_to_delete cannot be NULL.", 2);
  if (abstract_array_to_delete->allocation_mode == 1) {
    free(abstract_array_to_delete->pointer);
  }
  abstract_array_to_delete->allocation_mode = 0;
  abstract_array_to_delete->pointer = TEB_NULL_POINTER;
  abstract_array_to_delete->sizeof_one_element = 0;
  abstract_array_to_delete->length = 0;
  return TEB_debug_function_end(1);
}

void* TEB_AbstractArray_get_pointer (struct TEB_AbstractArray_struct* abstract_array) {
  TEB_debug_function_start("TEB_AbstractArray_get_pointer");
  if (abstract_array == TEB_NULL_POINTER) TEB_fatal_error(6, "abstract_array cannot be NULL.", 2);
  TEB_debug_function_end(0);
  return abstract_array->pointer;
}

TEB_size_t TEB_AbstractArray_get_sizeof_one_element (struct TEB_AbstractArray_struct* abstract_array) {
  TEB_debug_function_start("TEB_AbstractArray_get_sizeof_one_element");
  if (abstract_array == TEB_NULL_POINTER) TEB_fatal_error(7, "abstract_array cannot be NULL.", 2);
  TEB_debug_function_end(0);
  return abstract_array->sizeof_one_element;
}

TEB_size_t TEB_AbstractArray_get_length (struct TEB_AbstractArray_struct* abstract_array) {
  TEB_debug_function_start("TEB_AbstractArray_get_length");
  if (abstract_array == TEB_NULL_POINTER) TEB_fatal_error(8, "abstract_array cannot be NULL.", 2);
  TEB_debug_function_end(0);
  return abstract_array->length;
}

TEB_small_u_int TEB_AbstractArray_get_allocation_mode (struct TEB_AbstractArray_struct* abstract_array) {
  TEB_debug_function_start("TEB_AbstractArray_get_allocation_mode");
  if (abstract_array == TEB_NULL_POINTER) TEB_fatal_error(9, "abstract_array cannot be NULL.", 2);
  return TEB_debug_function_end(abstract_array->allocation_mode);
}

#ifdef TEB_LibrarySettings_DEBUG_MODE
static void TEB_AbstractArray_function_end (const TEB_char* f_name, TEB_bool ok) {
  if (ok == 0) {
    TEB_debug_print("\n");
    TEB_debug_print(f_name);
    TEB_debug_print(" ko");
  } else {
    TEB_debug_print("\n");
    TEB_debug_print(f_name);
    TEB_debug_print(" ok");
  }
}

TEB_small_int TEB_AbstractArray_test () {
  TEB_debug_function_start("TEB_AbstractArray_test");

  struct TEB_AbstractArray_struct aa1, aa2;
  TEB_medium_int b1[10];

  if (TEB_AbstractArray_new_array(&aa1, sizeof(TEB_medium_int), 10, b1) == 1) TEB_AbstractArray_function_end("TEB_AbstractArray_new_array1", 1);
  else {
    TEB_AbstractArray_function_end("TEB_AbstractArray_new_array1", 0);
    return TEB_debug_function_end(-1);
  }

  if (TEB_AbstractArray_new_array(&aa2, sizeof(TEB_medium_int), 10, TEB_NULL_POINTER) == 1) TEB_AbstractArray_function_end("TEB_AbstractArray_new_array2", 1);
  else {
    TEB_AbstractArray_function_end("TEB_AbstractArray_new_array2", 0);
    return TEB_debug_function_end(-2);
  }

  if (TEB_AbstractArray_delete_array(&aa1) == 1) TEB_AbstractArray_function_end("TEB_AbstractArray_delete_array1", 1);
  else {
    TEB_AbstractArray_function_end("TEB_AbstractArray_delete_array1", 0);
    return TEB_debug_function_end(-3);
  }

  if (TEB_AbstractArray_delete_array(&aa2) == 1) TEB_AbstractArray_function_end("TEB_AbstractArray_delete_array2", 1);
  else {
    TEB_AbstractArray_function_end("TEB_AbstractArray_delete_array2", 0);
    return TEB_debug_function_end(-4);
  }

  return TEB_debug_function_end(1);
}
#endif
