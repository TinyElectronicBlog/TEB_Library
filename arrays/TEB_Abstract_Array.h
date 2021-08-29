/*
  MIT License

  Copyright (c) 2021 TinyElectronicBlog

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

#ifndef TEB_Abstract_Array_h
#define TEB_Abstract_Array_h

#ifdef TEB_DB_DEBUG
#include "../development_board/TEB_DevelopmentBoard.h"
#endif 

/**
    \class TEB_Abstract_Array
    \brief TEB_Abstract_Array The link https://learn.adafruit.com/memories-of-an-arduino/optimizing-sram explains how to optimize the use of sram; in summary, it is better to prefer local allocations because they do not create heap fragmentation and do not remain permanently in memory. However, global and dynamic allocations are mandatory choices when working with very large variables, as they allow you to allocate more memory than local ones.\n An instance of this class can act as an interface to any array, regardless of the allocation and data type. The functions of the class allow you to manage the array by hiding it from the rest of the code; this makes it easier to replace an array without rewriting many lines of code.\n The name Abstract Array derives from the fact that an instance of this class alone does not represent a concrete array.
*/
class TEB_Abstract_Array {

  protected:

#ifdef TEB_DB_DEBUG
    size_t initial_free_heap;
#endif

    uint8_t* array_pointer;
    size_t array_size; //in uint8_t
    uint8_t array_type; //0 uninitialized, 1 dynamic allocation, 2 imported array

    virtual void begin ();

    /*
      Returns:
      1 if an array has been dynamically allocated
      2 if an array has been imported
      -1 if an array could not be allocated dynamically
      -3 if type is != 1 && != 2
    */
    virtual int8_t allocate (uint8_t type, void* external_array, size_t array_size);

  public:

    TEB_Abstract_Array ();
    ~TEB_Abstract_Array ();

    /**
        \brief Associate this instance with a dynamically allocated array.
        \param [in] sizeInBytes Array size in bytes. Must be > 0.
        \return 1 if everything is ok, otherwise -1.
        \details This or arrayImport must be used before any other function.
    */
    virtual int8_t dynamicAllocation (size_t sizeInBytes);

    /**
       \brief Associate this instance with a dynamically allocated array.
       \param [in] numberOfElements Number of array elements. Must be > 0.
       \param [in] sizeOf1ElementInBytes Size in bytes of an element. Must be > 0.
       \return 1 if everything is ok, otherwise -1.
       \details This or arrayImport must be used before any other function.
    */
    virtual int8_t dynamicAllocation (size_t numberOfElements, size_t sizeOf1ElementInBytes);

    /**
       \brief Associate this instance with externalArray.
       \param [in] externalArray The array to import. Must not be NULL.
       \param [in] sizeInBytes Array size in bytes. Must be > 0.
       \return 1 if everything is ok, otherwise -1.
       \details This or dynamicAllocation must be used before any other function.
    */
    virtual int8_t arrayImport (void* externalArray, size_t sizeInBytes);

    /**
        \brief Associate this instance with externalArray.
        \param [in] externalArray The array to import. Must not be NULL.
        \param [in] numberOfElements Number of array elements. Must be > 0.
        \param [in] sizeOf1ElementInBytes Size in bytes of an element. Must be > 0.
        \return 1 if everything is ok, otherwise -1.
        \details This or dynamicAllocation must be used before any other function.
    */
    virtual int8_t arrayImport (void* externalArray, size_t numberOfElements, size_t sizeOf1ElemenInBytes);

    /**
         \brief Disassociates the array bound to this instance.
         \return 1 if everything is ok, otherwise -1.
         \details After this function, before you can reuse this instance you need to run dynamicAllocation or arrayImport.
    */
    virtual int8_t deallocate ();

    /**
         \return An array pointer attached to this instance.
         \details Remember to cast the pointer.
    */
    virtual void* pointer ();

    /**
         \return The size in bytes of the array associated with this instance.
    */
    virtual size_t size ();

    /**
         \return 1 if the array associated with this instance has been dynamically allocated, otherwise 2.
    */
    virtual uint8_t type ();

#ifdef TEB_DB_DEBUG
    static void test ();
#endif

};
#endif
