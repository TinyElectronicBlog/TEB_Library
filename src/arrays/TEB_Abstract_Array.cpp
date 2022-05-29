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

#include "../TEB_Some_global_values.h"
#include "TEB_Abstract_Array.h"

TEB_Abstract_Array::TEB_Abstract_Array () {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Abstract_Array::TEB_Abstract_Array ()"));
#endif
  TEB_Abstract_Array::begin();
}

TEB_Abstract_Array::~TEB_Abstract_Array () {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Abstract_Array::~TEB_Abstract_Array ()"));
#endif
  if (array_type != 0) TEB_Abstract_Array::deallocate();
}

void TEB_Abstract_Array::begin () {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Abstract_Array::begin ()"));
#endif
  array_pointer = NULL;
  array_size = 0;
  array_type = 0;
#ifdef TEB_DB_DEBUG
  initial_free_heap = 0;
#endif
}

int8_t TEB_Abstract_Array::allocate (uint8_t type, void* external_array, size_t array_size) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Abstract_Array::allocate (uint8_t type, void* external_array, size_t array_size)"));
  if (array_pointer != 0) {
    TEB_Debug::fatalError(1, F("Using this function with an already allocated array is wrong."));
  }
#endif
  switch (type) {
    case 1:
#ifdef TEB_DB_DEBUG
      if (array_size > 0) {
        initial_free_heap = TEB_Debug::totalFreeHeap();
#endif
        array_pointer = (uint8_t*)malloc(array_size);
        if (array_pointer != NULL) {
          this->array_size = array_size;
          array_type = 1;
#ifdef TEB_DB_DEBUG
          TEB_Debug::print(F("\nDynamically allocated a new "));
          TEB_Debug::print(array_size);
          TEB_Debug::print(F("-element array. The amount of free heap before the array allocation was "));
          TEB_Debug::print(initial_free_heap);
          TEB_Debug::print(F(" units.\n"));
#endif
          return 1;
        }
#ifdef TEB_DB_DEBUG
        else {
          initial_free_heap = 0;
          TEB_Debug::error(1, F("There is not enough free heap to dynamically allocate an array."));
          return -1;
        }
      }
      else TEB_Debug::fatalError(2, F("array_size cannot be 0."));
#endif
      break;
    case 2:
#ifdef TEB_DB_DEBUG
      if (external_array != NULL && array_size > 0) {
#endif
        array_pointer = (uint8_t*)external_array;
        this->array_size = array_size;
        array_type = 2;
#ifdef TEB_DB_DEBUG
        TEB_Debug::print(F("\nImported an external array of "));
        TEB_Debug::print(array_size);
        TEB_Debug::print(F(" units."));
#endif
        return 2;
#ifdef TEB_DB_DEBUG
      }
      else {
        if (external_array == NULL) TEB_Debug::fatalError(3, F("external_array cannot be NULL."));
        if (array_size == 0) TEB_Debug::fatalError(4, F("array_size cannot be 0."));
      }
#endif
  }
#ifdef TEB_DB_DEBUG
  TEB_Debug::fatalError(5, F("Wrong value of type."));
#endif
  return -3;
}

int8_t TEB_Abstract_Array::dynamicAllocation (size_t sizeInBytes) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Abstract_Array::dynamicAllocation (size_t sizeInBytes)"));
#endif
  if (allocate(1, 0, sizeInBytes) == 1) return 1;
  else {
#ifdef TEB_DB_DEBUG
    TEB_Debug::error(2, F("TEB_Abstract_Array::dynamicAllocation returned -1."));
#endif
    return -1;
  }
}

int8_t TEB_Abstract_Array::dynamicAllocation (size_t numberOfElements, size_t sizeOf1ElementInBytes) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Abstract_Array::dynamicAllocation (size_t numberOfElements, size_t sizeOf1ElementInBytes)"));
#endif
  return dynamicAllocation(numberOfElements * sizeOf1ElementInBytes);
}

int8_t TEB_Abstract_Array::arrayImport (void* externalArray, size_t sizeInBytes) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Abstract_Array::arrayImport (void* externalArray, size_t sizeInBytes)"));
#endif
  if (allocate(2, externalArray, sizeInBytes) == 2) return 1;
  else {
#ifdef TEB_DB_DEBUG
    TEB_Debug::fatalError(3, F("TEB_Abstract_Array::arrayImport returned -1."));
#endif
    return -1;
  }
}

int8_t TEB_Abstract_Array::arrayImport (void* externalArray, size_t numberOfElements, size_t sizeOf1ElemenInBytes) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Abstract_Array::arrayImport (void* externalArray, size_t numberOfElements, size_t sizeOf1ElemenInBytes)"));
#endif
  return arrayImport(externalArray, numberOfElements * sizeOf1ElemenInBytes);
}

int8_t TEB_Abstract_Array::deallocate () {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Abstract_Array::deallocate ()"));
  size_t current_free_heap;
#endif
  switch (array_type) {
    case 1:
      free(array_pointer);
#ifdef TEB_DB_DEBUG
      current_free_heap = TEB_Debug::totalFreeHeap();
      TEB_Debug::print(F("\nDynamically deallocated a "));
      TEB_Debug::print(array_size);
      TEB_Debug::print(F("-element array.\nThe free heap is now "));
      TEB_Debug::print(current_free_heap);
      TEB_Debug::print(F(" units.\n"));
      if (current_free_heap == initial_free_heap) {
        TEB_Debug::print(F("The amount of free heap after the deallocation of the array remained unchanged.\n"));
      }
      else if (current_free_heap > initial_free_heap) {
        TEB_Debug::print(F("Attention, the amount of free heap after the deallocation of the array has gone up by +"));
        TEB_Debug::print(current_free_heap - initial_free_heap);
        TEB_Debug::print(F(" units.\n"));
      }
      else {
        TEB_Debug::print(F("Attention, the amount of free heap after the deallocation of the array has decreased by -"));
        TEB_Debug::print(initial_free_heap - current_free_heap);
        TEB_Debug::print(F(" units.\n"));
      }
#endif
      TEB_Abstract_Array::begin();
      return 1;
    case 2:
#ifdef TEB_DB_DEBUG
      TEB_Debug::print(F("\nDeallocated an external array of "));
      TEB_Debug::print(array_size);
      TEB_Debug::print(F("-element array.\n"));
#endif
      TEB_Abstract_Array::begin();
      return 1;
  }
#ifdef TEB_DB_DEBUG
  TEB_Debug::fatalError(6, F("Unable to deallocate an unallocated array."));
#endif
  return -1;
}

void* TEB_Abstract_Array::pointer () {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Abstract_Array::pointer ()"));
  if (array_pointer == NULL) {
    TEB_Debug::fatalError(7, F("A buffer must be allocated before executing this function."));
  }
#endif
  return array_pointer;
}

size_t TEB_Abstract_Array::size () {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Abstract_Array::size ()"));
  if (array_size == 0) {
    TEB_Debug::fatalError(8, F("A buffer must be allocated before executing this function."));
  }
#endif
  return array_size;
}

uint8_t TEB_Abstract_Array::type () {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Abstract_Array::type ()"));
  if (array_type == 0) {
    TEB_Debug::fatalError(10, F("A buffer must be allocated before executing this function."));
  }
#endif
  return array_type;
}

#ifdef TEB_DB_DEBUG
void TEB_Abstract_Array::test () {
  TEB_Debug tebdb = TEB_Debug(F("TEB_Abstract_Array::test ()"));
  TEB_Debug::print(TEB_Library_global_string_for_debugging1);
  TEB_Debug::print(F("TEB_Abstract_Array"));
  TEB_Debug::print(TEB_Library_global_string_for_debugging2);
  TEB_Abstract_Array array;
  if (array.dynamicAllocation(37, sizeof(char)) != 1) return;
  char* p = (char*)array.pointer();
  strcpy(p, "1234567890qwertyuiopasdfghjklzxcvbnm\0");
  TEB_Debug::print(F("\n"));
  TEB_Debug::print(p);
  TEB_Debug::print(F("\n"));
  array.deallocate();
  int externalArray[50];
  if (array.arrayImport(externalArray, 50, sizeof(int)) != 1) return;
  int* p2 = (int*)array.pointer();
  TEB_Debug::print(F("\n\n"));
  for (uint8_t i = 0; i < array.size() / sizeof(int); i++) {
    p2[i] = i;
    TEB_Debug::print(p2[i]);
    TEB_Debug::print(" ");
  }
  TEB_Debug::print(F("\n"));
  TEB_Debug::print(TEB_Library_global_string_for_debugging3);
}
#endif