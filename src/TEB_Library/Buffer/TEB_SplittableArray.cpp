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

#include "TEB_SplittableArray.h"
#include "../String/TEB_String.h"
#include "../Number/TEB_Number.h"

static TEB_size_t TEB_SplittableArray_number_of_allocated_arrays_ = 0;
static struct TEB_AbstractArray_struct TEB_SplittableArray_allocated_arrays[TEB_MAX_NUMBER_OF_ALLOCABLE_SPLITTABLE_ARRAYS];
static void* TEB_SplittableArray_temporary_array_pointers1[TEB_MAX_NUMBER_OF_ALLOCABLE_SPLITTABLE_ARRAYS];
static void* TEB_SplittableArray_temporary_array_pointers2[TEB_MAX_NUMBER_OF_ALLOCABLE_SPLITTABLE_ARRAYS];

TEB_size_t TEB_SplittableArray_new_array (TEB_size_t sizeof_one_array_element,
                                         TEB_size_t array_length,
                                         void* optional_instantiated_buffer_to_associate) {
  TEB_debug_function_start("TEB_SplittableArray_new_array");
  if (sizeof_one_array_element == 0) TEB_fatal_error(10, "Value not allowed for sizeof_one_array_element.", 2);
  if (array_length == 0) TEB_fatal_error(11, "Value not allowed for array_length.", 2);
  if (TEB_SplittableArray_number_of_allocated_arrays_ >= TEB_MAX_NUMBER_OF_ALLOCABLE_SPLITTABLE_ARRAYS) TEB_fatal_error(12, "You need to increase TEB_MAX_NUMBER_OF_ALLOCABLE_SPLITTABLE_ARRAYS.", 2);
  TEB_small_int r = TEB_AbstractArray_new_array(&TEB_SplittableArray_allocated_arrays[TEB_SplittableArray_number_of_allocated_arrays_],
                                                sizeof_one_array_element, array_length,
                                                optional_instantiated_buffer_to_associate);
  if (r == 1) {
    TEB_SplittableArray_temporary_array_pointers1[TEB_SplittableArray_number_of_allocated_arrays_] = TEB_SplittableArray_allocated_arrays[TEB_SplittableArray_number_of_allocated_arrays_].pointer;
    TEB_SplittableArray_temporary_array_pointers2[TEB_SplittableArray_number_of_allocated_arrays_] = TEB_SplittableArray_allocated_arrays[TEB_SplittableArray_number_of_allocated_arrays_].pointer;
    TEB_SplittableArray_number_of_allocated_arrays_ = TEB_SplittableArray_number_of_allocated_arrays_ + 1;
    TEB_debug_function_end(0);
    return TEB_SplittableArray_number_of_allocated_arrays_;
  } else {
    TEB_debug_function_end(0);
    return 0;
  }
}

TEB_small_int TEB_SplittableArray_delete_last_array () {
  TEB_debug_function_start("TEB_SplittableArray_delete_last_array");
  TEB_SplittableArray_number_of_allocated_arrays_ = TEB_SplittableArray_number_of_allocated_arrays_ - 1;
  TEB_AbstractArray_delete_array(&TEB_SplittableArray_allocated_arrays[TEB_SplittableArray_number_of_allocated_arrays_]);
  TEB_SplittableArray_temporary_array_pointers1[TEB_SplittableArray_number_of_allocated_arrays_] = TEB_NULL_POINTER;
  TEB_SplittableArray_temporary_array_pointers2[TEB_SplittableArray_number_of_allocated_arrays_] = TEB_NULL_POINTER;
  return TEB_debug_function_end(1);
}

TEB_small_int TEB_SplittableArray_add_elements (TEB_size_t splittable_array_index,
                                               const void* elements_to_store,
                                               TEB_size_t number_of_elements_to_store) {
  TEB_debug_function_start("TEB_SplittableArray_add_elements");
  if (number_of_elements_to_store == 0) TEB_fatal_error(14, "Value not allowed for number_of_elements_to_store.", 2);
  if (splittable_array_index == 0 || splittable_array_index > TEB_SplittableArray_number_of_allocated_arrays_) TEB_fatal_error(15, "Value not allowed for splittable_array_index.", 2);
  splittable_array_index = splittable_array_index - 1;
  if (elements_to_store == TEB_NULL_POINTER) {
    TEB_SplittableArray_temporary_array_pointers2[splittable_array_index] = (TEB_data_type_to_copy_buffer*)TEB_SplittableArray_temporary_array_pointers2[splittable_array_index] + (number_of_elements_to_store * TEB_SplittableArray_allocated_arrays[splittable_array_index].sizeof_one_element);
  } else {
    const TEB_data_type_to_copy_buffer* source = (const TEB_data_type_to_copy_buffer*)elements_to_store;
    TEB_data_type_to_copy_buffer* destination = (TEB_data_type_to_copy_buffer*)(TEB_SplittableArray_temporary_array_pointers2[splittable_array_index]);
    TEB_data_type_to_copy_buffer* end = (TEB_data_type_to_copy_buffer*)(destination + (number_of_elements_to_store * TEB_SplittableArray_allocated_arrays[splittable_array_index].sizeof_one_element));
    while (destination < end) {
      *destination = *source;
      source = source + 1;
      destination = destination + 1;
    }
    TEB_SplittableArray_temporary_array_pointers2[splittable_array_index] = end;
  }
  return TEB_debug_function_end(1);
}

void* TEB_SplittableArray_add_elements_end (TEB_size_t splittable_array_index,
                                           const void* elements_to_store_temporarily_to_the_end_of_the_buffer,
                                           TEB_size_t number_of_elements_to_store) {
  TEB_debug_function_start("TEB_SplittableArray_add_elements_end");
  if (elements_to_store_temporarily_to_the_end_of_the_buffer == TEB_NULL_POINTER) TEB_fatal_error(16, "elements_to_store_temporarily_to_the_end_of_the_buffer cannot be NULL.", 2);
  if (number_of_elements_to_store == 0) TEB_fatal_error(17, "Value not allowed for number_of_elements_to_store.", 2);
  if (splittable_array_index == 0 || splittable_array_index > TEB_SplittableArray_number_of_allocated_arrays_) TEB_fatal_error(18, "Value not allowed for splittable_array_index.", 2);
  splittable_array_index = splittable_array_index - 1;
  const TEB_data_type_to_copy_buffer* source = ((const TEB_data_type_to_copy_buffer*)elements_to_store_temporarily_to_the_end_of_the_buffer) + ((number_of_elements_to_store * TEB_SplittableArray_allocated_arrays[splittable_array_index].sizeof_one_element) - 1);
  TEB_data_type_to_copy_buffer* destination = (TEB_data_type_to_copy_buffer*)TEB_SplittableArray_last_element_pointer(splittable_array_index + 1);
  destination = destination + (TEB_SplittableArray_allocated_arrays[splittable_array_index].sizeof_one_element - 1);
  TEB_data_type_to_copy_buffer* end = destination - ((number_of_elements_to_store * TEB_SplittableArray_allocated_arrays[splittable_array_index].sizeof_one_element) - 1);
  while (destination > end) {
    *destination = *source;
    source = source - 1;
    destination = destination - 1;
  }
  *destination = *source;
  TEB_debug_function_end(0);
  return destination;
}

void* TEB_SplittableArray_split_array (TEB_size_t splittable_array_index) {
  TEB_debug_function_start("TEB_SplittableArray_split_array");
  if (splittable_array_index == 0 || splittable_array_index > TEB_SplittableArray_number_of_allocated_arrays_) TEB_fatal_error(19, "Value not allowed for splittable_array_index.", 2);
  splittable_array_index = splittable_array_index - 1;
  void* r = TEB_SplittableArray_temporary_array_pointers1[splittable_array_index];
  TEB_SplittableArray_temporary_array_pointers1[splittable_array_index] = TEB_SplittableArray_temporary_array_pointers2[splittable_array_index];
  TEB_debug_function_end(0);
  return r;
}

void* TEB_SplittableArray_last_element_pointer (TEB_size_t splittable_array_index) {
  TEB_debug_function_start("TEB_SplittableArray_last_element_pointer");
  if (splittable_array_index == 0 || splittable_array_index > TEB_SplittableArray_number_of_allocated_arrays_) TEB_fatal_error(20, "Value not allowed for splittable_array_index.", 2);
  TEB_debug_function_end(0);
  return ((TEB_data_type_to_copy_buffer*)(TEB_SplittableArray_allocated_arrays[splittable_array_index - 1].pointer)) + (TEB_SplittableArray_allocated_arrays[splittable_array_index - 1].sizeof_one_element * (TEB_SplittableArray_allocated_arrays[splittable_array_index - 1].length - 1));
}

TEB_small_int TEB_SplittableArray_release_elements (TEB_size_t splittable_array_index, 
										         void* from_address_returned_by_split_array) {
  TEB_debug_function_start("TEB_SplittableArray_release_elements");
  if (splittable_array_index == 0 || splittable_array_index > TEB_SplittableArray_number_of_allocated_arrays_) TEB_fatal_error(21, "Value not allowed for splittable_array_index.", 2);
  if (from_address_returned_by_split_array == TEB_NULL_POINTER) TEB_fatal_error(22, "from_address_returned_by_split_array cannot be NULL.", 2);
  splittable_array_index = splittable_array_index - 1;
  TEB_SplittableArray_temporary_array_pointers1[splittable_array_index] = from_address_returned_by_split_array;
  TEB_SplittableArray_temporary_array_pointers2[splittable_array_index] = from_address_returned_by_split_array;
  return TEB_debug_function_end(1);
}

TEB_small_int TEB_SplittableArray_reset_array (TEB_size_t splittable_array_index) {
  TEB_debug_function_start("TEB_SplittableArray_reset_array");
  if (splittable_array_index == 0 || splittable_array_index > TEB_SplittableArray_number_of_allocated_arrays_) TEB_fatal_error(23, "Value not allowed for splittable_array_index.", 2);
  splittable_array_index = splittable_array_index - 1;
  TEB_SplittableArray_temporary_array_pointers1[splittable_array_index] = TEB_SplittableArray_allocated_arrays[splittable_array_index].pointer;
  TEB_SplittableArray_temporary_array_pointers2[splittable_array_index] = TEB_SplittableArray_allocated_arrays[splittable_array_index].pointer;
  return TEB_debug_function_end(1);
}

TEB_size_t TEB_SplittableArray_number_of_free_elements (TEB_size_t splittable_array_index) {
  TEB_debug_function_start("TEB_SplittableArray_number_of_free_elements");
  if (splittable_array_index == 0 || splittable_array_index > TEB_SplittableArray_number_of_allocated_arrays_) TEB_fatal_error(24, "Value not allowed for splittable_array_index.", 2);
  splittable_array_index = splittable_array_index - 1;
  TEB_size_t r = TEB_SplittableArray_allocated_arrays[splittable_array_index].length - TEB_SplittableArray_number_of_occupied_elements(splittable_array_index + 1);
  TEB_debug_function_end(0);
  return r;
}

TEB_size_t TEB_SplittableArray_number_of_occupied_elements (TEB_size_t splittable_array_index) {
  TEB_debug_function_start("TEB_SplittableArray_number_of_occupied_elements");
  if (splittable_array_index == 0 || splittable_array_index > TEB_SplittableArray_number_of_allocated_arrays_) TEB_fatal_error(25, "Value not allowed for splittable_array_index.", 2);
  splittable_array_index = splittable_array_index - 1;
  TEB_size_t r = ((TEB_size_t)TEB_SplittableArray_temporary_array_pointers2[splittable_array_index] - (TEB_size_t)TEB_SplittableArray_allocated_arrays[splittable_array_index].pointer) / TEB_SplittableArray_allocated_arrays[splittable_array_index].sizeof_one_element;
  TEB_debug_function_end(0);
  return r;
}

TEB_size_t TEB_SplittableArray_number_of_allocated_arrays () {
  TEB_debug_function_start("TEB_SplittableArray_number_of_allocated_arrays");
  TEB_size_t r = TEB_SplittableArray_number_of_allocated_arrays_;
  TEB_debug_function_end(0);
  return r;
}

#ifdef TEB_LibrarySettings_DEBUG_MODE
static void TEB_SplittableArray_function_end (const TEB_char* f_name, TEB_bool ok) {
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

TEB_small_int TEB_SplittableArray_test () {
  TEB_debug_function_start("TEB_SplittableArray_test");

  const TEB_medium_int buffer_length = 20;
  TEB_medium_int optional_instantiated_buffer_to_associate[buffer_length];
  TEB_medium_int before = TEB_SplittableArray_number_of_allocated_arrays();

  TEB_size_t id1 = TEB_SplittableArray_new_array(sizeof(TEB_medium_int), buffer_length, optional_instantiated_buffer_to_associate);
  TEB_size_t id2 = TEB_SplittableArray_new_array(sizeof(TEB_medium_int), buffer_length, TEB_NULL_POINTER);
  if (id1 != 0 && id2 != 0) TEB_SplittableArray_function_end("TEB_SplittableArray_new_array", 1);
  else {
    TEB_SplittableArray_function_end("TEB_SplittableArray_new_array", 0);
    return TEB_debug_function_end(-1);
  }

  if (before + 2 == TEB_SplittableArray_number_of_allocated_arrays()) TEB_SplittableArray_function_end("TEB_SplittableArray_new_array", 1);
  else {
    TEB_SplittableArray_function_end("TEB_SplittableArray_new_array", 0);
    return TEB_debug_function_end(-2);
  }

  TEB_medium_int c[] = { 0, 1, 2, 3, 4, 5 };
  TEB_medium_int d[] = { 6, 7, 8, 9, 10 };
  if (TEB_SplittableArray_add_elements(id1, c, 6) == 1 && TEB_SplittableArray_add_elements(id2, c, 6) == 1 && TEB_SplittableArray_add_elements(id1, d, 5) == 1 && TEB_SplittableArray_add_elements(id2, d, 5) == 1) TEB_SplittableArray_function_end("TEB_SplittableArray_add_elements", 1);
  else {
    TEB_SplittableArray_function_end("TEB_SplittableArray_add_elements", 0);
    return TEB_debug_function_end(-3);
  }

  TEB_medium_int* e = (TEB_medium_int*)TEB_SplittableArray_split_array(id1);
  TEB_medium_int* f = (TEB_medium_int*)TEB_SplittableArray_split_array(id2);
  TEB_medium_int i = 0;
  while (i < (sizeof(c) + sizeof(d)) / sizeof(c[0])) {
    if (e[i] != i || f[i] != i) break;
    i = i + 1;
  }
  if (i == (sizeof(c) + sizeof(d)) / sizeof(c[0])) TEB_SplittableArray_function_end("TEB_SplittableArray_split_array", 1);
  else {
    TEB_SplittableArray_function_end("TEB_SplittableArray_split_array", 0);
    return TEB_debug_function_end(-4);
  }

  if ((TEB_medium_int*)TEB_SplittableArray_last_element_pointer(id1) == e + buffer_length - 1 && (TEB_medium_int*)TEB_SplittableArray_last_element_pointer(id2) == f + buffer_length - 1) TEB_SplittableArray_function_end("TEB_SplittableArray_last_element_pointer", 1);
  else {
    TEB_SplittableArray_function_end("TEB_SplittableArray_last_element_pointer", 0);
    return TEB_debug_function_end(-12);
  }

  if (TEB_SplittableArray_number_of_free_elements(id1) == buffer_length - (sizeof(c) + sizeof(d)) / sizeof(c[0]) && TEB_SplittableArray_number_of_free_elements(id2) == buffer_length - (sizeof(c) + sizeof(d)) / sizeof(c[0])) TEB_SplittableArray_function_end("TEB_SplittableArray_number_of_free_elements", 1);
  else {
    TEB_SplittableArray_function_end("TEB_SplittableArray_number_of_free_elements", 0);
    return TEB_debug_function_end(-5);
  }

  TEB_medium_int g_l = TEB_SplittableArray_number_of_free_elements(id1);
  TEB_medium_int h_l = TEB_SplittableArray_number_of_free_elements(id2);
  TEB_SplittableArray_add_elements(id1, TEB_NULL_POINTER, g_l);
  TEB_SplittableArray_add_elements(id2, TEB_NULL_POINTER, h_l);
  TEB_medium_int* g = (TEB_medium_int*)TEB_SplittableArray_split_array(id1);
  TEB_medium_int* h = (TEB_medium_int*)TEB_SplittableArray_split_array(id2);
  if (TEB_SplittableArray_number_of_free_elements(id1) == 0 && TEB_SplittableArray_number_of_free_elements(id2) == 0) TEB_SplittableArray_function_end("TEB_SplittableArray_split_array2", 1);
  else {
    TEB_SplittableArray_function_end("TEB_SplittableArray_split_array2", 0);
    return TEB_debug_function_end(-6);
  }

  i = 0;
  while (i < g_l) {
    g[i] = 1;
    h[i] = 1;
    i = i + 1;
  }
  i = 0;
  while (i < g_l) {
    if (g[i] != 1 || h[i] != 1) break;
    i = i + 1;
  }
  if (i == g_l) TEB_SplittableArray_function_end("TEB_SplittableArray_add_elements", 1);
  else {
    TEB_SplittableArray_function_end("TEB_SplittableArray_add_elements", 0);
    return TEB_debug_function_end(-7);
  }

  if (TEB_SplittableArray_release_elements(id1, e) == 1 && TEB_SplittableArray_reset_array(id2) == 1) TEB_SplittableArray_function_end("TEB_SplittableArray_release_elements and TEB_SplittableArray_reset_array", 1);
  else {
    TEB_SplittableArray_function_end("TEB_SplittableArray_release_elements and TEB_SplittableArray_reset_array", 0);
    return TEB_debug_function_end(-8);
  }

  if (TEB_SplittableArray_number_of_free_elements(id1) == buffer_length && TEB_SplittableArray_number_of_free_elements(id2) == buffer_length) TEB_SplittableArray_function_end("TEB_SplittableArray_number_of_free_elements", 1);
  else {
    TEB_SplittableArray_function_end("TEB_SplittableArray_number_of_free_elements", 0);
    return TEB_debug_function_end(-9);
  }

  if (TEB_SplittableArray_delete_last_array() == 1 && TEB_SplittableArray_delete_last_array() == 1) TEB_SplittableArray_function_end("TEB_SplittableArray_delete_last_array", 1);
  else {
    TEB_SplittableArray_function_end("TEB_SplittableArray_delete_last_array", 0);
    return TEB_debug_function_end(-10);
  }

  if (0 == TEB_SplittableArray_number_of_allocated_arrays()) TEB_SplittableArray_function_end("TEB_SplittableArray_delete_last_array", 1);
  else {
    TEB_SplittableArray_function_end("TEB_SplittableArray_delete_last_array", 0);
    return TEB_debug_function_end(-11);
  }

  TEB_small_u_int l = 3;
  TEB_big_int k[l];
  k[0] = 4833;
  k[1] = 765;
  k[2] = 94678;
  id2 = TEB_SplittableArray_new_array(sizeof(TEB_big_int), l, TEB_NULL_POINTER);
  TEB_big_int* k_sp = (TEB_big_int*)TEB_SplittableArray_add_elements_end(id2, k, l);
  TEB_big_int* k_sp_inv = (TEB_big_int*)TEB_SplittableArray_last_element_pointer(id2);
  if (k_sp != 0 && k[0] == *k_sp && k[1] == *(k_sp + 1) && k[2] == *(k_sp + 2) && k[2] == *k_sp_inv && k[1] == *(k_sp_inv - 1) && k[0] == *(k_sp_inv - 2)) TEB_SplittableArray_function_end("TEB_SplittableArray_add_elements_end", 1);
  else {
    TEB_SplittableArray_function_end("TEB_SplittableArray_add_elements_end", 0);
    return TEB_debug_function_end(-13);
  }
  TEB_SplittableArray_delete_last_array();

  return TEB_debug_function_end(1);
}
#endif
