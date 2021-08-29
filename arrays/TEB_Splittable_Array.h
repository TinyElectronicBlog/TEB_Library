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

#ifndef TEB_Splittable_Array_h
#define TEB_Splittable_Array_h

#include "TEB_Abstract_Array.h"

/**
    \class TEB_Splittable_Array
    \brief This class extends TEB_Splittable_Array and treats the array attached to its instance as a large array that can be split into chunks in three ways:\n - mode 1, for permanently stored chunks of defined length;\n - mode 2, for permanently stored chunks of indefinite length;\n - mode 3, for temporary chunks.\n The SX functions save data from the first free element of the array with the smallest index going up, while the DX functions from the first free element with the largest index going down; in this way it is like having two independent arrays separated by free space, in which chunks can be saved. The reverseDX functions also allow you to save data incrementally on the right side.\n When creating a type 1 chunk it is not possible to create other chunks on the same side of the array. addDX and addDXreverse cannot be used simultaneously to create the same chunk.
*/
class TEB_Splittable_Array : public TEB_Abstract_Array {

  protected:

    uint8_t* p_sx; //first free element on sx
    uint8_t* p_sx_t;
    uint8_t* p_dx; //first free element on dx
    uint8_t* p_dx_t;

    void begin ();

    int8_t allocate (uint8_t type, void* external_array, size_t array_size);

#ifdef TEB_DB_DEBUG
    size_t max_space_occupied;

    bool type_1_array_in_use_sx;
    uint8_t type_1_array_in_use_dx;

    struct split_address {
      uint8_t* address; //addresses returned by split functions
      uint8_t type; //0 splitSX (), 1 splitDX (), 2 splitSX (const void* lastArrayElement), 3 splitDX (const void* lastArrayElement), 4 splitDXreverse
    };

    split_address split_addresses_sx[TEB_Splittable_Array_MAX_SPLIT_ADDRESSES_SX];
    size_t split_addresses_index_sx;

    split_address split_addresses_dx[TEB_Splittable_Array_MAX_SPLIT_ADDRESSES_DX];
    size_t split_addresses_index_dx;

    void add_split_address (uint8_t* address, uint8_t type);
    void remove_split_address (uint8_t* address, uint8_t type);

    size_t maxSpaceOccupied ();
#endif

  public:

    TEB_Splittable_Array ();
    ~TEB_Splittable_Array ();

    /**
         \brief Disassociates the array bound to this instance.
         \return 1 if everything is ok, otherwise -1.
         \details After this function, before you can reuse this instance you need to run dynamicAllocation or arrayImport.
    */
    int8_t deallocate ();

    //FUNCTIONS TO CREATE PERMANENTLY STORED CHUNKS OF DEFINED LENGTH (MODE 1)
    /**
       \brief Adds data to the left side of the array bound to this instance. It is used to create type 1 chunks.
       \param [in] array The source of the data. Set it to NULL to save empty space.
       \param [in] sizeInBytes Size in bytes of the source array. Must be > 0.
    */
    void addSX (const void* array, size_t sizeInBytes);

    /**
       \brief Adds data to the left side of the array bound to this instance. It is used to create type 1 chunks.
       \param [in] array The source of the data. Set it to NULL to save empty space.
       \param [in] sizeInBytes Size in bytes of the source array. Must be > 0.
       \param [in] numberOfElements Number of array elements. Must be > 0.
       \param [in] sizeOf1ElementInBytes Size in bytes of an element. Must be > 0.
    */
    void addSX (const void* array, size_t numberOfElements, size_t sizeOf1ElementInBytes);

    /**
        \brief Adds PROGMEM data to the left side of the array bound to this instance. It is used to create type 1 chunks.
        \param [in] array The source of the data. It must end with \0 and cannot be NULL.
    */
    void addSX_P (const char* array);

    /**
       \brief Adds PROGMEM data to the left side of the array bound to this instance. It is used to create type 1 chunks.
       \param [in] array The source of the data. It cannot be NULL.
       \param [in] sizeInBytes Size in bytes of the source array. Must be > 0.
    */
    void addSX_P (const char* array, size_t sizeInBytes);

    /**
       \brief Finalize a type 1 chunk created with addSX.
       \return A pointer to the chunk.
       \details Remember to cast the returned pointer.
    */
    const void* splitSX ();

    /**
       \brief Adds data to the right side of the array bound to this instance. It is used to create type 1 chunks.
       \param [in] array The source of the data. Set it to NULL to save empty space.
       \param [in] sizeInBytes Size in bytes of the source array. Must be > 0.
    */
    void addDX (const void* array, size_t sizeInBytes);

    /**
       \brief Adds data to the right side of the array bound to this instance. It is used to create type 1 chunks.
       \param [in] array The source of the data. Set it to NULL to save empty space.
       \param [in] numberOfElements Number of array elements. Must be > 0.
       \param [in] sizeOf1ElementInBytes Size in bytes of an element. Must be > 0.
    */
    void addDX (const void* array, size_t numberOfElements, size_t sizeOf1ElementInBytes);

    /**
       \brief Adds data to the right side of the array bound to this instance. It is used to create type 1 chunks. addDXreverse saves data increasingly.
       \param [in] array The source of the data. Set it to NULL to save empty space.
       \param [in] sizeInBytes Size in bytes of the source array. Must be > 0.
    */
    void addDXreverse (const void* array, size_t sizeInBytes);

    /**
       \brief Adds data to the right side of the array bound to this instance. It is used to create type 1 chunks. addDXreverse saves data increasingly.
       \param [in] array The source of the data. It cannot be NULL.
       \param [in] numberOfElements Number of array elements. Must be > 0.
       \param [in] sizeOf1ElementInBytes Size in bytes of an element. Must be > 0.
    */
    void addDXreverse (const void* array, size_t numberOfElements, size_t sizeOf1ElementInBytes);

    /**
       \brief Adds PROGMEM data to the right side of the array bound to this instance. It is used to create type 1 chunks. addDXreverse_P saves data increasingly.
       \param [in] array The source of the data. It must end with \0 and cannot be NULL.
    */
    void addDXreverse_P (const char* array);

    /**
       \brief Adds data to the right side of the array bound to this instance. It is used to create type 1 chunks. addDXreverse saves data increasingly.
       \param [in] array The source of the data. It cannot be NULL.
       \param [in] sizeInBytes Size in bytes of the source array. Must be > 0.
    */
    void addDXreverse_P (const char* array, size_t sizeInBytes);

    /**
       \brief Finalize a type 1 chunk created with addDX.
       \return A pointer to the chunk.
       \details Remember to cast the returned pointer.
    */
    const void* splitDX ();

    /**
       \brief Finalize a type 1 chunk created with addDXreverse.
       \return A pointer to the chunk.
       \details Remember to cast the returned pointer.
    */
    const void* splitDXreverse ();

    //FUNCTIONS TO CREATE PERMANENTLY STORED CHUNKS OF UNDEFINED LENGTH (MODE 2)
    /**
       \brief It is used to create type 2 chunks. It also serves to create type 3 chunks if splitSX is not executed at the end.
       \return A pointer to the first free byte on the left of the array tied to this instance.
       \details Remember to cast the returned pointer. The data must be saved in increasing order.
    */
    const void* SX ();

#ifdef TEB_DB_DEBUG
    /**
        \param [in] firstElementAfterChunk A pointer to the first free byte after the last stored data. Must be != NULL.
        \return The remaining free space in bytes.
    	\details This function is present only with the debug mode active. This function can also be used with type 3 chunks.
    */
    size_t freeSpaceSX (const void* firstElementAfterChunk);
#endif

    /**
       \brief Finalize a type 2 chunk created with SX.
       \param [in] firstElementAfterChunk A pointer to the first free byte after the finalized chunk. Must be != NULL.
       \return A pointer to the chunk.
       \details Remember to cast the returned pointer.
    */
    const void* splitSX (const void* firstElementAfterChunk);

    /**
       \brief It is used to create type 2 chunks. It also serves to create type 3 chunks if splitDX is not executed at the end.
       \return A pointer to the first free byte on the right of the array tied to this instance.
       \details Remember to cast the returned pointer. The data must be saved in descending order.
    */
    const void* DX ();

#ifdef TEB_DB_DEBUG
    /**
        \param [in] firstElementAfterChunk A pointer to the first free byte after the last stored data. Must be != NULL.
        \return The remaining free space in bytes.
    	\details This function is present only with the debug mode active. This function can also be used with type 3 chunks.
    */
    size_t freeSpaceDX (const void* firstElementAfterChunk);
#endif

    /**
       \brief Finalize a type 2 chunk created with DX.
       \param [in] firstElementAfterChunk A pointer to the first free byte after the finalized chunk. Must be != NULL.
       \return A pointer to the chunk.
       \details Remember to cast the returned pointer.
    */
    const void* splitDX (const void* firstElementAfterChunk);

    /*FUNCTIONS FOR CREATING TEMPORARY CHUNKS (MODE 3, same as mode 2 but without using splitSX or splitDX at the end)
      const void* SX ();
      size_t freeSpaceSX (const void* firstElementAfterChunk);

      const void* DX ();
      size_t freeSpaceDX (const void* firstElementAfterChunk);
    */

    //FUNCTIONS FOR DESTROYING CHUNKS (FOR MODE 1 AND 2)
    /**
        \brief Destroys one or more of the last chunks saved on the left side of the array attached to this instance.
        \param [in] numberOfBytes Number of bytes to be released from the last saved. Must be > 0 and equal to the sum of the sizes of one or more chunks.
    */
    void freeSX (size_t numberOfBytes);

    /**
        \brief Destroys one or more of the last chunks saved on the left side of the array attached to this instance.
        \param [in] numberOfElements Number of elements to be released from the last saved. Must be > 0 and equal to the sum of elements of one or more chunks (chunks must have elements of the same size).
        \param [in] sizeOf1ElementInBytes Size in bytes of an element. Must be > 0.
    */
    void freeSX (size_t numberOfElements, size_t sizeOf1ElementInBytes);

    /**
        \brief Destroys one or more of the last chunks saved on the left side of the array attached to this instance.
        \param [in] fromAddress Release all space from fromAddress onwards. fromAddress must only accept a value returned by a splitSX.
    */
    void freeSX (const void* fromAddress);

    /**
        \brief Destroys one or more of the last chunks saved on the right side of the array attached to this instance.
        \param [in] numberOfBytes Number of bytes to be released from the last saved. Must be > 0 and equal to the sum of the sizes of one or more chunks.
    */
    void freeDX (size_t numberOfBytes);

    /**
        \brief Destroys one or more of the last chunks saved on the right side of the array attached to this instance.
        \param [in] numberOfElements Number of elements to be released from the last saved. Must be > 0 and equal to the sum of elements of one or more chunks (chunks must have elements of the same size).
        \param [in] sizeOf1ElementInBytes Size in bytes of an element. Must be > 0.
    */	
    void freeDX (size_t numberOfElements, size_t sizeOf1ElementInBytes);

    /**
        \brief Destroys one or more of the last chunks saved on the right side of the array attached to this instance.
        \param [in] fromAddress Release all space from fromAddress onwards. fromAddress must only accept a value returned by a splitDX (not splitDXreverse).
    */	
	void freeDX (const void* fromAddress);

    /**
       \brief Deletes all chunks saved on the left side of the array bound to this instance.
       \details It can be performed at any time.
    */
    void resetSX ();

    /**
       \brief Deletes all chunks saved on the right side of the array bound to this instance.
       \details It can be performed at any time.
    */
    void resetDX ();

    /**
       \return The number of free bytes in the array bound to this instance. It also takes into account bytes stored with addSX, addDX or addDXreverse before finalizing a type 1 chunk.
       \details It can be performed at any time.
    */
    size_t freeSpace ();

    /**
       \return The number of occupied bytes in the array bound to this instance. It also takes into account bytes stored with addSX, addDX or addDXreverse before finalizing a type 1 chunk.
       \details It can be performed at any time.
    */
    size_t occupiedSpace ();

#ifdef TEB_DB_DEBUG
    static void test ();
#endif

};
#endif