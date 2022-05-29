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
#include "TEB_Splittable_Array.h"

TEB_Splittable_Array::TEB_Splittable_Array () : TEB_Abstract_Array () {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::TEB_Splittable_Array ()"));
#endif
  begin();
}

TEB_Splittable_Array::~TEB_Splittable_Array () {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::~TEB_Splittable_Array ()"));
#endif
  if (p_sx != NULL) TEB_Splittable_Array::deallocate();
}

void TEB_Splittable_Array::begin () {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::begin ()"));
#endif
  p_sx = NULL;
  p_sx_t = NULL;
  p_dx = NULL;
  p_dx_t = NULL;
#ifdef TEB_DB_DEBUG
  max_space_occupied = 0;
  type_1_array_in_use_sx = false;
  type_1_array_in_use_dx = 0; //1 addDX, 2 addDXreverse
  split_addresses_index_sx = 0;
  split_addresses_index_dx = 0;
#endif
}

int8_t TEB_Splittable_Array::allocate (uint8_t type, void* external_array, size_t array_size) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::allocate (uint8_t type, void* external_array, size_t array_size)"));
#endif
  int8_t r = TEB_Abstract_Array::allocate(type, external_array, array_size);
  if (r == 1 || r == 2) {
    p_sx = array_pointer;
    p_sx_t = array_pointer;
    p_dx = array_pointer + array_size - 1;
    p_dx_t = p_dx;
  }
  else {
#ifdef TEB_DB_DEBUG
    TEB_Debug::error(53, F("Unable to initialize an array."));
#endif
  }
  return r;
}

#ifdef TEB_DB_DEBUG
void TEB_Splittable_Array::add_split_address (uint8_t* address, uint8_t type) {
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::add_split_address (uint8_t* address, uint8_t type)"));
  if (type == 0 || type == 2) {
    if (split_addresses_index_sx >= TEB_Splittable_Array_MAX_SPLIT_ADDRESSES_SX) {
      TEB_Debug::fatalError(11, F("You need to increase TEB_Splittable_Array_MAX_SPLIT_ADDRESSES_SX in the file TEB_Splittable_Array.h"));
    }
    split_addresses_sx[split_addresses_index_sx].address = address;
    split_addresses_sx[split_addresses_index_sx].type = type;
    split_addresses_index_sx++;
  }
  else {
    if (split_addresses_index_dx >= TEB_Splittable_Array_MAX_SPLIT_ADDRESSES_DX) {
      TEB_Debug::fatalError(12, F("You need to increase TEB_Splittable_Array_MAX_SPLIT_ADDRESSES_DX in the file TEB_Splittable_Array.h"));
    }
    split_addresses_dx[split_addresses_index_dx].address = address;
    split_addresses_dx[split_addresses_index_dx].type = type;
    split_addresses_index_dx++;
  }
}

void TEB_Splittable_Array::remove_split_address (uint8_t* address, uint8_t type) {
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::remove_split_address (uint8_t* address, uint8_t type)"));
  size_t i;
  if (type == 0 || type == 2) {
    i = split_addresses_index_sx;
    do {
      i--;
      if (split_addresses_sx[i].address == address) {
        split_addresses_index_sx = i;
        return;
      }
    } while (i > 0);
    TEB_Debug::print(F("\nThe input parameters of a function "));
    if (type == 0) TEB_Debug::print(F("void freeSX (size_t numberOfBytes) or void freeSX (size_t numberOfElements, size_t sizeOf1ElementInBytes)"));
    else TEB_Debug::print(F("void freeSX (void* fromAddress)"));
    TEB_Debug::print(F(" are not correct.\n"));
    TEB_Debug::fatalError(13, F("Problem with remove_split_address function."));
  }
  else {
    i = split_addresses_index_dx;
    do {
      i--;
      if (split_addresses_dx[i].address == address) {
        split_addresses_index_dx = i;
        return;
      }
    } while (i > 0);
    TEB_Debug::print(F("\nThe input parameters of a function "));
    if (type == 1) TEB_Debug::print(F("void freeDX (size_t numberOfBytes) o void freeDX (size_t numberOfElements, size_t sizeOf1ElementInBytes)"));
    else TEB_Debug::print(F("void freeDX (void* fromAddress)"));
    TEB_Debug::print(F(" are not correct.\n"));
    TEB_Debug::fatalError(14, F("Problem with remove_split_address function."));
  }
}
#endif

int8_t TEB_Splittable_Array::deallocate () {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::deallocate ()"));
  size_t array_size_t = array_size;
#endif
  int8_t r = TEB_Abstract_Array::deallocate();
  if (r == 1) {
#ifdef TEB_DB_DEBUG
    TEB_Debug::print(F("\nA maximum of "));
    TEB_Debug::print(maxSpaceOccupied());
    TEB_Debug::print(F(" bytes out of "));
    TEB_Debug::print(array_size_t);
    TEB_Debug::print(F(" bytes have been occupied.\n"));
#endif
    begin();
  }
#ifdef TEB_DB_DEBUG
  else {
    TEB_Debug::fatalError(15, F("Unable to deallocate an unallocated array."));
  }
#endif
  return r;
}

void TEB_Splittable_Array::addSX (const void* array, size_t sizeInBytes) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::addSX (const void* array, size_t sizeInBytes)"));
  if (p_dx == NULL) {
    TEB_Debug::fatalError(16, F("Array not allocated."));
  }
  if (sizeInBytes == 0) {
    TEB_Debug::fatalError(17, F("sizeInBytes cannot be 0."));
  }
  if (freeSpace() < sizeInBytes) {
    TEB_Debug::fatalError(18, F("Space in array terminated."));
  }
  if (!type_1_array_in_use_sx) type_1_array_in_use_sx = true;
#endif
  if (array == NULL) {
    p_sx_t = p_sx_t + sizeInBytes;
  }
  else {
    const char* const end = (const char*)array + sizeInBytes;
    while (array < end) {
      *p_sx_t = *((uint8_t*)array);
      p_sx_t++;
      array++;
    }
  }
}

void TEB_Splittable_Array::addSX (const void* array, size_t numberOfElements, size_t sizeOf1ElementInBytes) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::addSX (const void* array, size_t numberOfElements, size_t sizeOf1ElementInBytes)"));
  if (numberOfElements == 0) {
    TEB_Debug::fatalError(19, F("numberOfElements cannot be 0."));
  }
  if (sizeOf1ElementInBytes == 0) {
    TEB_Debug::fatalError(20, F("sizeOf1ElementInBytes cannot be 0."));
  }
#endif
  addSX(array, numberOfElements * sizeOf1ElementInBytes);
}

void TEB_Splittable_Array::addSX_P (const char* array) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::addSX_P (const char* array)"));
  if (array == NULL) {
    TEB_Debug::fatalError(21, F("array cannot be NULL."));
  }
#endif
  addSX_P(array, strlen_P(array));
}

void TEB_Splittable_Array::addSX_P (const char* array, size_t sizeInBytes) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::addSX_P (const char* array, size_t sizeInBytes)"));
  if (p_dx == NULL) {
    TEB_Debug::fatalError(22, F("Array not allocated."));
  }
  if (array == NULL) {
    TEB_Debug::fatalError(23, F("array cannot be NULL."));
  }
  if (sizeInBytes == 0) {
    TEB_Debug::fatalError(24, F("sizeInBytes cannot be 0."));
  }
  if (freeSpace() < sizeInBytes) {
    TEB_Debug::fatalError(25, F("Space in array terminated."));
  }
  if (!type_1_array_in_use_sx) type_1_array_in_use_sx = true;
#endif
  p_sx_t = (uint8_t*)strncpy_P((char*)p_sx_t, array, sizeInBytes) + sizeInBytes;
}

const void* TEB_Splittable_Array::splitSX () {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::splitSX ()"));
  if (p_dx == NULL) {
    TEB_Debug::fatalError(26, F("Array not allocated."));
  }
  if (type_1_array_in_use_sx) type_1_array_in_use_sx = false;
  else {
    TEB_Debug::fatalError(27, F("You cannot use this function without first using addSX."));
  }
#endif
  uint8_t* t = p_sx;
  p_sx = p_sx_t;
#ifdef TEB_DB_DEBUG
  add_split_address(t, 0);
  freeSpace();
#endif
  return t;
}

void TEB_Splittable_Array::addDX (const void* array, size_t sizeInBytes) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::addDX (const void* array, size_t sizeInBytes)"));
  if (p_dx == NULL) {
    TEB_Debug::fatalError(28, F("Array not allocated."));
  }
  if (sizeInBytes == 0) {
    TEB_Debug::fatalError(29, F("sizeInBytes cannot be 0."));
  }
  if (freeSpace() < sizeInBytes) {
    TEB_Debug::fatalError(30, F("Space in array terminated."));
  }
  if (type_1_array_in_use_dx == 2) {
    TEB_Debug::fatalError(31, F("You cannot use this function while you are using addDXreverse."));
  }
  if (type_1_array_in_use_dx != 1) type_1_array_in_use_dx = 1;
#endif
  if (array == NULL) {
    p_dx_t = p_dx_t - sizeInBytes;
  }
  else {
    const char* const end = (const char*)array + sizeInBytes;
    while (array < end) {
      *p_dx_t = *((uint8_t*)array);
      p_dx_t--;
      array++;
    }
  }
}

void TEB_Splittable_Array::addDX (const void* array, size_t numberOfElements, size_t sizeOf1ElementInBytes) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::addDX (const void* array, size_t numberOfElements, size_t sizeOf1ElementInBytes)"));
  if (numberOfElements == 0) {
    TEB_Debug::fatalError(32, F("numberOfElements cannot be 0."));
  }
  if (sizeOf1ElementInBytes == 0) {
    TEB_Debug::fatalError(33, F("sizeOf1ElementInBytes cannot be 0."));
  }
#endif
  addDX(array, numberOfElements * sizeOf1ElementInBytes);
}

void TEB_Splittable_Array::addDXreverse (const void* array, size_t sizeInBytes) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::addDXreverse (const void* array, size_t sizeInBytes)"));
  if (p_dx == NULL) {
    TEB_Debug::fatalError(34, F("Array not allocated."));
  }
  if (sizeInBytes == 0) {
    TEB_Debug::fatalError(35, F("sizeInBytes cannot be 0."));
  }
  if (freeSpace() < sizeInBytes) {
    TEB_Debug::fatalError(36, F("Space in array terminated."));
  }
  if (type_1_array_in_use_dx == 1) {
    TEB_Debug::fatalError(37, F("You cannot use this function while you are using addDX."));
  }
  if (type_1_array_in_use_dx != 2) type_1_array_in_use_dx = 2;
#endif
  if (array == NULL) {
    p_dx_t = p_dx_t - sizeInBytes;
  }
  else {
    const char* end = (const char*)array + sizeInBytes - 1;
    while (array <= end) {
      *p_dx_t = *((uint8_t*)end);
      p_dx_t--;
      end--;
    }
  }
}

void TEB_Splittable_Array::addDXreverse (const void* array, size_t numberOfElements, size_t sizeOf1ElementInBytes) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::addDXreverse (const void* array, size_t numberOfElements, size_t sizeOf1ElementInBytes)"));
  if (numberOfElements == 0) {
    TEB_Debug::fatalError(38, F("numberOfElements cannot be 0."));
  }
  if (sizeOf1ElementInBytes == 0) {
    TEB_Debug::fatalError(39, F("sizeOf1ElementInBytes cannot be 0."));
  }
#endif
  addDXreverse(array, numberOfElements * sizeOf1ElementInBytes);
}

void TEB_Splittable_Array::addDXreverse_P (const char* array) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::addDXreverse_P (const char* array)"));
  if (array == NULL) {
    TEB_Debug::fatalError(40, F("array cannot be NULL."));
  }
#endif
  addDXreverse_P(array, strlen_P(array));
}

void TEB_Splittable_Array::addDXreverse_P (const char* array, size_t sizeInBytes) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::addDXreverse_P (const char* array, size_t sizeInBytes)"));
  if (p_dx == NULL) {
    TEB_Debug::fatalError(41, F("Array not allocated."));
  }
  if (array == NULL) {
    TEB_Debug::fatalError(42, F("array cannot be NULL."));
  }
  if (sizeInBytes == 0) {
    TEB_Debug::fatalError(43, F("sizeInBytes cannot be 0."));
  }
  if (freeSpace() < sizeInBytes) {
    TEB_Debug::fatalError(44, F("Space in array terminated."));
  }
  if (type_1_array_in_use_dx == 1) {
    TEB_Debug::fatalError(45, F("You cannot use this function while you are using addDX."));
  }
  if (type_1_array_in_use_dx != 2) type_1_array_in_use_dx = 2;
#endif
  p_dx_t = p_dx_t - sizeInBytes;
  strncpy_P((char*)p_dx_t + 1, array, sizeInBytes);
}

const void* TEB_Splittable_Array::splitDX () {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::splitDX ()"));
  if (p_dx == NULL) {
    TEB_Debug::fatalError(46, F("Array not allocated."));
  }
  if (type_1_array_in_use_dx == 1) type_1_array_in_use_dx = 0;
  else {
    TEB_Debug::fatalError(47, F("You cannot use this function without first using addDX."));
  }
#endif
  uint8_t* t = p_dx;
  p_dx = p_dx_t;
#ifdef TEB_DB_DEBUG
  add_split_address(t, 1);
  freeSpace();
#endif
  return t;
}

const void* TEB_Splittable_Array::splitDXreverse () {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::splitDXreverse ()"));
  if (p_dx == NULL) {
    TEB_Debug::fatalError(48, F("Array not allocated."));
  }
  if (type_1_array_in_use_dx == 2) type_1_array_in_use_dx = 0;
  else {
    TEB_Debug::fatalError(49, F("You cannot use this function without first using addDXreverse."));
  }
  add_split_address(p_dx, 4);
#endif
  p_dx = p_dx_t;
#ifdef TEB_DB_DEBUG
  freeSpace();
#endif
  return p_dx + 1;
}

const void* TEB_Splittable_Array::SX () {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::SX ()"));
  if (p_dx == NULL) {
    TEB_Debug::fatalError(50, F("Array not allocated."));
  }
  if (type_1_array_in_use_sx) {
    TEB_Debug::fatalError(51, F("You cannot use this function while you are creating a type 1 array on the left."));
  }
  if (freeSpace() < 1) {
    TEB_Debug::fatalError(52, F("Out of space."));
  }
#endif
  return p_sx;
}

#ifdef TEB_DB_DEBUG
size_t TEB_Splittable_Array::freeSpaceSX (const void* firstElementAfterChunk) {
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::freeSpaceSX (const void* firstElementAfterChunk)"));
  if (p_dx == NULL) {
    TEB_Debug::fatalError(53, F("Array not allocated."));
  }
  if (type_1_array_in_use_sx) {
    TEB_Debug::fatalError(54, F("You cannot use this function while you are creating a type 1 array on the left."));
  }
  if (firstElementAfterChunk == NULL) {
    TEB_Debug::fatalError(55, F("firstElementAfterChunk cannot be NULL."));
  }
  if (firstElementAfterChunk < p_sx + 1 || p_dx_t + 1 < firstElementAfterChunk) {
    TEB_Debug::fatalError(56, F("firstElementAfterChunk has a prohibited value."));
  }
  return p_dx_t - (uint8_t*)(firstElementAfterChunk - 1);
}
#endif

const void* TEB_Splittable_Array::splitSX (const void* firstElementAfterChunk) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::splitSX (const void* firstElementAfterChunk)"));
  if (p_dx == NULL) {
    TEB_Debug::fatalError(57, F("Array not allocated."));
  }
  if (type_1_array_in_use_sx) {
    TEB_Debug::fatalError(58, F("You cannot use this function while you are creating a type 1 array on the left."));
  }
  if (firstElementAfterChunk == NULL) {
    TEB_Debug::fatalError(59, F("firstElementAfterChunk cannot be NULL."));
  }
  if (firstElementAfterChunk < p_sx + 1 || p_dx_t + 1 < firstElementAfterChunk) {
    TEB_Debug::fatalError(60, F("firstElementAfterChunk has a prohibited value."));
  }
#endif
  uint8_t* t = p_sx;
  p_sx = (uint8_t*)(firstElementAfterChunk);
  p_sx_t = p_sx;
#ifdef TEB_DB_DEBUG
  add_split_address(t, 2);
  freeSpace();
#endif
  return t;
}

const void* TEB_Splittable_Array::DX () {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::DX ()"));
  if (p_dx == NULL) {
    TEB_Debug::fatalError(61, F("Array not allocated."));
  }
  if (type_1_array_in_use_dx != 0) {
    TEB_Debug::fatalError(62, F("You cannot use this function while you are creating a type 1 array on the right."));
  }
  if (freeSpace() < 1) {
    TEB_Debug::fatalError(63, F("Out of space."));
  }
#endif
  return p_dx;
}

#ifdef TEB_DB_DEBUG
size_t TEB_Splittable_Array::freeSpaceDX (const void* firstElementAfterChunk) {
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::freeSpaceDX (const void* firstElementAfterChunk)"));
  if (p_dx == NULL) {
    TEB_Debug::fatalError(64, F("Array not allocated."));
  }
  if (type_1_array_in_use_dx != 0) {
    TEB_Debug::fatalError(65, F("You cannot use this function while you are creating a type 1 array on the right."));
  }
  if (firstElementAfterChunk == NULL) {
    TEB_Debug::fatalError(66, F("firstElementAfterChunk cannot be NULL."));
  }
  if (firstElementAfterChunk < p_sx_t - 1 || p_dx - 1 < firstElementAfterChunk) {
    TEB_Debug::fatalError(67, F("firstElementAfterChunk has a prohibited value."));
  }
  return (uint8_t*)(firstElementAfterChunk + 1) - p_sx_t;
}
#endif

const void* TEB_Splittable_Array::splitDX (const void* firstElementAfterChunk) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::splitDX (const void* firstElementAfterChunk)"));
  if (p_dx == NULL) {
    TEB_Debug::fatalError(68, F("Array not allocated."));
  }
  if (type_1_array_in_use_dx != 0) {
    TEB_Debug::fatalError(69, F("You cannot use this function while you are creating a type 1 array on the right."));
  }
  if (firstElementAfterChunk == NULL) {
    TEB_Debug::fatalError(70, F("firstElementAfterChunk cannot be NULL."));
  }
  if (firstElementAfterChunk < p_sx_t - 1 || p_dx - 1 < firstElementAfterChunk) {
    TEB_Debug::fatalError(71, F("firstElementAfterChunk has a prohibited value."));
  }
#endif
  uint8_t* t = p_dx;
  p_dx = (uint8_t*)firstElementAfterChunk;
  p_dx_t = p_dx;
#ifdef TEB_DB_DEBUG
  add_split_address(t, 3);
  freeSpace();
#endif
  return t;
}

void TEB_Splittable_Array::freeSX (size_t numberOfBytes) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::freeSX (size_t numberOfBytes)"));
  if (p_dx == NULL) {
    TEB_Debug::fatalError(72, F("Array not allocated."));
  }
  if (type_1_array_in_use_sx) {
    TEB_Debug::fatalError(73, F("You cannot use this function while you are creating a type 1 array on the left."));
  }
  if (numberOfBytes == 0) {
    TEB_Debug::fatalError(74, F("numberOfBytes cannot be 0."));
  }
  if (p_sx - array_pointer < numberOfBytes) {
    TEB_Debug::fatalError(75, F("It is not possible to free more bytes than those occupied."));
    return;
  }
#endif
  p_sx = p_sx - numberOfBytes;
  p_sx_t = p_sx;
#ifdef TEB_DB_DEBUG
  remove_split_address(p_sx, 0);
#endif
}

void TEB_Splittable_Array::freeSX (size_t numberOfElements, size_t sizeOf1ElementInBytes) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::freeSX (size_t numberOfElements, size_t sizeOf1ElementInBytes)"));
  if (numberOfElements == 0) {
    TEB_Debug::fatalError(76, F("numberOfElements cannot be 0."));
  }
  if (sizeOf1ElementInBytes == 0) {
    TEB_Debug::fatalError(77, F("sizeOf1ElementInBytes cannot be 0."));
  }
#endif
  freeSX(numberOfElements * sizeOf1ElementInBytes);
}

void TEB_Splittable_Array::freeSX (const void* fromAddress) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::freeSX (const void* fromAddress)"));
  if (p_dx == NULL) {
    TEB_Debug::fatalError(78, F("Array not allocated."));
  }
  if (type_1_array_in_use_sx) {
    TEB_Debug::fatalError(79, F("You cannot use this function while you are creating a type 1 array on the left."));
  }
  if (fromAddress == NULL) {
    TEB_Debug::fatalError(80, F("fromAddress cannot be NULL."));
  }
  if (fromAddress < array_pointer || p_sx - 1 < fromAddress) {
    TEB_Debug::fatalError(81, F("fromAddress must point to an allowed address."));
  }
#endif
  p_sx = (uint8_t*)fromAddress;
  p_sx_t = p_sx;
#ifdef TEB_DB_DEBUG
  remove_split_address(p_sx, 2);
#endif
}

void TEB_Splittable_Array::freeDX (size_t numberOfBytes) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::freeDX (size_t numberOfBytes)"));
  if (p_dx == NULL) {
    TEB_Debug::fatalError(82, F("Array not allocated."));
  }
  if (type_1_array_in_use_dx != 0) {
    TEB_Debug::fatalError(83, F("You cannot use this function while you are creating a type 1 array on the rigth."));
  }
  if (numberOfBytes == 0) {
    TEB_Debug::fatalError(84, F("numberOfBytes cannot be 0."));
  }
  if (array_pointer + array_size - 1 - p_dx < numberOfBytes) {
    TEB_Debug::fatalError(85, F("Can't free more numberOfBytes bytes than are occupied."));
    return;
  }
#endif
  p_dx = p_dx + numberOfBytes;
  p_dx_t = p_dx;
#ifdef TEB_DB_DEBUG
  remove_split_address(p_dx, 1);
#endif
}

void TEB_Splittable_Array::freeDX (size_t numberOfElements, size_t sizeOf1ElementInBytes) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::freeDX (size_t numberOfElements, size_t sizeOf1ElementInBytes)"));
  if (numberOfElements == 0) {
    TEB_Debug::fatalError(86, F("numberOfElements cannot be 0."));
  }
  if (sizeOf1ElementInBytes == 0) {
    TEB_Debug::fatalError(87, F("sizeOf1ElementInBytes cannot be 0."));
  }
#endif
  freeDX(numberOfElements * sizeOf1ElementInBytes);
}

void TEB_Splittable_Array::freeDX (const void* fromAddress) {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::freeDX (const void* fromAddress)"));
  if (p_dx == NULL) {
    TEB_Debug::fatalError(88, F("Array not allocated."));
  }
  if (type_1_array_in_use_dx != 0) {
    TEB_Debug::fatalError(89, F("You cannot use this function while you are creating a type 1 array on the rigth."));
  }
  if (fromAddress == NULL) {
    TEB_Debug::fatalError(90, F("fromAddress cannot be NULL."));
  }
  if (fromAddress < p_dx + 1 || array_pointer + array_size - 1 < fromAddress) {
    TEB_Debug::fatalError(91, F("fromAddress must point to an allowed address."));
    return;
  }
#endif
  p_dx = (uint8_t*)fromAddress;
  p_dx_t = p_dx;
#ifdef TEB_DB_DEBUG
  remove_split_address(p_dx, 3);
#endif
}

void TEB_Splittable_Array::resetSX () {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::resetSX ()"));
  if (p_sx == NULL) {
    TEB_Debug::fatalError(92, F("Array not allocated."));
  }
#endif
  p_sx = array_pointer;
  p_sx_t = array_pointer;
#ifdef TEB_DB_DEBUG
  type_1_array_in_use_sx = false;
  split_addresses_index_sx = 0;
#endif
}

void TEB_Splittable_Array::resetDX () {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::resetDX ()"));
  if (p_sx == NULL) {
    TEB_Debug::fatalError(93, F("Array not allocated."));
  }
#endif
  p_dx = array_pointer + array_size - 1;
  p_dx_t = p_dx;
#ifdef TEB_DB_DEBUG
  type_1_array_in_use_dx = false;
  split_addresses_index_dx = 0;
#endif
}

size_t TEB_Splittable_Array::freeSpace () {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::freeSpace ()"));
  if (p_dx == NULL) {
    TEB_Debug::fatalError(94, F("Array not allocated."));
  }
  if (array_size - (size_t)((p_dx_t + 1) - p_sx_t) > max_space_occupied) max_space_occupied = array_size - (size_t)((p_dx_t + 1) - p_sx_t);
#endif
  return (p_dx_t + 1) - p_sx_t;
}

size_t TEB_Splittable_Array::occupiedSpace () {
#ifdef TEB_DB_DEBUG
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::occupiedSpace ()"));
  if (p_dx == NULL) {
    TEB_Debug::fatalError(95, F("Array not allocated."));
  }
  if (array_size - (size_t)((p_dx_t + 1) - p_sx_t) > max_space_occupied) max_space_occupied = array_size - (size_t)((p_dx_t + 1) - p_sx_t);
#endif
  return array_size - ((p_dx_t + 1) - p_sx_t);
}

#ifdef TEB_DB_DEBUG
size_t TEB_Splittable_Array::maxSpaceOccupied () {
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::maxSpaceOccupied ()"));
  return max_space_occupied;
}

void TEB_Splittable_Array::test () {
  TEB_Debug tebdb = TEB_Debug(F("TEB_Splittable_Array::test ()"));
  TEB_Debug::print(TEB_Library_global_string_for_debugging1);
  TEB_Debug::print(F("TEB_Splittable_Array"));
  TEB_Debug::print(TEB_Library_global_string_for_debugging2);
  char num[20];
  TEB_Splittable_Array array;
  if (array.dynamicAllocation(116) != 1) return;
  TEB_Debug::print(F("\nI create two arrays of type 1 on the left.\n"));
  array.addSX("abc", 3, sizeof(char));
  array.addSX("def", 4, sizeof(char));
  char* t1sx = (char*)array.splitSX();
  int i1[3] = {1, 2, 3};
  int i2[3] = {4, 5, 6};
  array.addSX(i1, 3, sizeof(int));
  array.addSX(i2, 3, sizeof(int));
  int* t2sx = (int*)array.splitSX();
  TEB_Debug::print(F("\nThe space currently occupied is "));
  TEB_Debug::print(array.occupiedSpace());
  TEB_Debug::print(F(" bytes.\n"));
  TEB_Debug::print(F("\nI create two arrays of type 1 on the right. Warning: addDX saves data from right to left while addDXreverse from left to right.\n"));
  array.addDX("abc", 3);
  array.addDX("def", 4, sizeof(char));
  char* t1dx = (char*)array.splitDX();
  array.addDXreverse(i2, 3, sizeof(int));
  array.addDXreverse(i1, 3, sizeof(int));
  int* t2dxreverse = (int*)array.splitDXreverse();
  TEB_Debug::print(F("\nThe space currently occupied is "));
  TEB_Debug::print(array.occupiedSpace());
  TEB_Debug::print(F(" bytes.\n"));
  TEB_Debug::print(F("\nI create three arrays of type 2 on the left.\n"));
  int* t3sx = (int*)array.SX();
  *t3sx = 1; t3sx++;
  *t3sx = 2; t3sx++;
  *t3sx = 3; t3sx++;
  TEB_Debug::print(F("\nOccupied "));
  TEB_Debug::print(array.size() - array.freeSpaceSX(t3sx));
  TEB_Debug::print(F(" bytes.\n"));
  t3sx = (int*)array.splitSX(t3sx);
  char* t4sx = (char*)array.SX();
  *t4sx = 'a'; t4sx++;
  *t4sx = 'b'; t4sx++;
  *t4sx = '\0'; t4sx++;
  TEB_Debug::print(F("\nOccupied "));
  TEB_Debug::print(array.size() - array.freeSpaceSX(t4sx));
  TEB_Debug::print(F(" bytes.\n"));
  t4sx = (char*)array.splitSX(t4sx);
  int* t5sx = (int*)array.SX();
  *t5sx = 1; t5sx++;
  *t5sx = 2; t5sx++;
  *t5sx = 3; t5sx++;
  TEB_Debug::print(F("\nOccupied "));
  TEB_Debug::print(array.size() - array.freeSpaceSX(t5sx));
  TEB_Debug::print(F(" bytes.\n"));
  t5sx = (int*)array.splitSX(t5sx);
  TEB_Debug::print(F("\nRather than using the type 2 functions on the right in a specular way, it is also possible to do:\n"));
  byte* t3dx_del = (byte*)array.DX();
  int* t3dx = (int*)(t3dx_del - (sizeof(int) - 1));
  *t3dx = 3; t3dx--;
  *t3dx = 2; t3dx--;
  *t3dx = 1;
  char* t4dx = (char*)t3dx - sizeof(char);
  TEB_Debug::print(F("\nOccupied "));
  TEB_Debug::print(array.size() - array.freeSpaceDX(t4dx));
  TEB_Debug::print(F(" bytes.\n"));
  *t4dx = '\0'; t4dx--;
  *t4dx = 'b'; t4dx--;
  *t4dx = 'a';
  TEB_Debug::print(F("\nOccupied "));
  TEB_Debug::print(array.size() - array.freeSpaceDX(t4dx - 1));
  TEB_Debug::print(F(" bytes.\n"));
  int* t5dx = (int*)(t4dx - sizeof(int));
  *t5dx = 3; t5dx--;
  *t5dx = 2; t5dx--;
  *t5dx = 1;
  TEB_Debug::print(F("\nOccupied "));
  TEB_Debug::print(array.size() - array.freeSpaceDX((byte*)t5dx - 1));
  TEB_Debug::print(F(" bytes.\n"));
  array.splitDX((byte*)t5dx - 1);
  TEB_Debug::print(F("\nTo make type 3 chunks just follow the steps for type 2 chunks but without using the splitSX or splitDX functions at the end.\n"));
  TEB_Debug::print(F("\nThe pieces created are:\nt1sx = ")); TEB_Debug::print(t1sx);
  int i = 0;
  TEB_Debug::print(F("\nt1dx (data saved in reverse) = "));
  while (i < 6) {
    TEB_Debug::print(*t1dx);
    t1dx--;
    i++;
  }
  i = 0;
  TEB_Debug::print(F("\nt2sx = "));
  while (i < 6) {
    TEB_Debug::print(t2sx[i]);
    i++;
  }
  TEB_Debug::print(F("\nt2dxreverse = "));
  i = 0;
  while (i < 6) {
    TEB_Debug::print(t2dxreverse[i]);
    i++;
  }
  i = 0;
  TEB_Debug::print(F("\nt3sx = "));
  while (i < 3) {
    TEB_Debug::print(t3sx[i]);
    i++;
  }
  TEB_Debug::print(F("\nt3dx = "));
  i = 0;
  while (i < 3) {
    TEB_Debug::print(t3dx[i]);
    i++;
  }
  TEB_Debug::print(F("\nt4sx = ")); TEB_Debug::print(t4sx);
  TEB_Debug::print(F("\nt4dx = ")); TEB_Debug::print(t4dx);
  i = 0;
  TEB_Debug::print(F("\nt5sx = "));
  while (i < 3) {
    TEB_Debug::print(t5sx[i]);
    i++;
  }
  TEB_Debug::print(F("\nt5dx = "));
  i = 0;
  while (i < 3) {
    TEB_Debug::print(t5dx[i]);
    i++;
  }
  TEB_Debug::print(F("\n\nNow I remove the chunk 5 on the left."));
  array.freeSX(3, sizeof(int));
  TEB_Debug::print(F(" The space currently occupied is "));
  TEB_Debug::print(array.occupiedSpace());
  TEB_Debug::print(F(" bytes.\n\nNow free chunk 4 on the left."));
  array.freeSX(t4sx);
  TEB_Debug::print(F(" The space currently occupied is "));
  TEB_Debug::print(array.occupiedSpace());
  TEB_Debug::print(F(" bytes.\n\nNow I delete all type 2 chunks on the right."));
  array.freeDX(t3dx_del);
  TEB_Debug::print(F(" The space currently occupied is "));
  TEB_Debug::print(array.occupiedSpace());
  TEB_Debug::print(F(" bytes.\n\nNow I delete all the chunks on the left."));
  array.resetSX();
  TEB_Debug::print(F(" The space currently occupied is "));
  TEB_Debug::print(array.occupiedSpace());
  TEB_Debug::print(F(" bytes.\n\nNow I delete all the chunks on the right."));
  array.resetDX();
  TEB_Debug::print(F(" The space currently occupied is "));
  TEB_Debug::print(array.occupiedSpace());
  TEB_Debug::print(F(" bytes.\n"));
  TEB_Debug::print(TEB_Library_global_string_for_debugging3);
}
#endif