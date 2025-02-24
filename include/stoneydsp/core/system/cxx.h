/**
 * @file cxx.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version @STONEYDSP_CORE_VERSION@
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once

#ifndef STONEYDSP_CXX_H_INCLUDED
  #define STONEYDSP_CXX_H_INCLUDED

//==============================================================================

  #ifdef __cplusplus

  //==============================================================================

    #define STONEYDSP_DELETE_CONSTRUCTOR(className) className () = delete;

    #define STONEYDSP_DELETE_COPY_CONSTRUCTOR(className)                      \
      className (const className &) = delete;

    #define STONEYDSP_DELETE_MOVE_CONSTRUCTOR(className)                      \
      className (const className &&) = delete;

    #define STONEYDSP_DELETE_COPY_ASSIGNMENT_OPERATOR(className)              \
      className &operator= (const className &) = delete;

    #define STONEYDSP_DELETE_MOVE_ASSIGNMENT_OPERATOR(className)              \
      className &operator= (className &&) = delete;

    #define STONEYDSP_DELETE_DYNAMIC_NEW_OPERATOR                             \
      static void *operator new (size_t) = delete;

    #define STONEYDSP_DELETE_DYNAMIC_DELETE_OPERATOR                          \
      static void operator delete (void *) = delete;

    #define STONEYDSP_DELETE_DYNAMIC_ARRAY_NEW_OPERATOR                       \
      static void *operator new[] (size_t) = delete;

    #define STONEYDSP_DELETE_DYNAMIC_ARRAY_DELETE_OPERATOR                    \
      static void operator delete[] (void *) = delete;

  //==============================================================================

    /**
     * @brief This is a shorthand macro for deleting a class's constructor.
     *
     */
    #define STONEYDSP_DECLARE_NON_CONSTRUCTABLE(className)                    \
      STONEYDSP_DELETE_CONSTRUCTOR (className)

  //==============================================================================

    /**
     * @brief This is a shorthand macro for deleting a class's copy constructor
     * and copy assignment operator.
     *
     */
    #define STONEYDSP_DECLARE_NON_COPYABLE(className)                         \
      STONEYDSP_DELETE_COPY_CONSTRUCTOR (className)                           \
      STONEYDSP_DELETE_COPY_ASSIGNMENT_OPERATOR (className)

  //==============================================================================

    /**
     * @brief This is a shorthand macro for deleting a class's move constructor
     * and move assignment operator.
     *
     */
    #define STONEYDSP_DECLARE_NON_MOVEABLE(className)                         \
      STONEYDSP_DELETE_MOVE_CONSTRUCTOR (className)                           \
      STONEYDSP_DELETE_MOVE_ASSIGNMENT_OPERATOR (className)

  //==============================================================================

    /**
     * @brief This macro can be added to class definitions to disable the use
     * of new/delete to allocate the object on the heap, forcing it to only be
     * used as a stack or member variable.
     *
     */
    #define STONEYDSP_PREVENT_HEAP_ALLOCATION                                 \
      STONEYDSP_DELETE_DYNAMIC_NEW_OPERATOR                                   \
      STONEYDSP_DELETE_DYNAMIC_DELETE_OPERATOR

  //==============================================================================

  #endif // __cplusplus

//==============================================================================

#endif // STONEYDSP_CXX_H_INCLUDED

//=========================================================================//EOF
