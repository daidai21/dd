/* ****************************************************************************
 * File Name   : libdd.hpp
 * Author      : DaiDai
 * Mail        : daidai4269@aliyun.com
 * Created Time: 四 11/ 5 17:17:57 2020
 * GCC version : C++11
 * Platform    : Unix-like
 *************************************************************************** */

/**
 * API like: Python3, Java8
 */

#ifndef __LIBDD__HPP__
#define __LIBDD__HPP__

#include <stdint.h>

#include <exception>
#include <string>
#include <iostream>

namespace libdd {

/**
 * basic define
 */
// basic type
typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef unsigned char byte;

// limits of type value
// UINT8_MAX, UINT16_MAX, UINT32_MAX, UINT64_MAX macro already defined.

#define UINT8_MIN 0
#define UINT16_MIN 0
#define UINT32_MIN 0
#define UINT64_MIN 0

#define MAX_INT8 ((int8_t)(UINT8_MAX >> 1))
#define MAX_INT16 ((int16_t)(UINT16_MAX >> 1))
#define MAX_INT32 ((int32_t)(UINT32_MAX >> 1))
#define MAX_INT64 ((int64_t)(UINT64_MAX >> 1))

#define MIN_INT8 ((int8_t)~INT8_MAX)
#define MIN_INT16 ((int16_t)~INT16_MAX)
#define MIN_INT32 ((int32_t)~INT32_MAX)
#define MIN_INT64 ((int64_t)~INT64_MAX)

// load/save with 1,2,4,8 byte
#define load_byte1(val) (*(const uint8_t*)(val))
#define load_byte2(val) (*(const uint16_t*)(val))
#define load_byte4(val) (*(const uint32_t*)(val))
#define load_byte8(val) (*(const uint64_t*)(val))

#define save_byte1(to, from) (*(uint8_t*)(to) = (from))
#define save_byte2(to, from) (*(uint16_t*)(to) = (from))
#define save_byte4(to, from) (*(uint32_t*)(to) = (from))
#define save_byte8(to, from) (*(uint64_t*)(to) = (from))

// constant
#define PI acos(-1)  // 3.1415926

// macro
#define DD_CAS(val, old_val, new_val) __sync_bool_compare_and_swap((val), (old_val), (new_val))

#define DD_ERR_EXIT(m)  \
  do {                  \
    perror(m);          \
    exit(EXIT_FAILURE); \
  } while (0)

#define GET_CURRENT_MICRO std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()

/**
 * class util
 */
// .
#define DISALLOW_COPY_AND_ASSIGN(Type) \
  Type(const Type&) = delete;          \
  void operator=(const Type&) = delete

// copyable and non-copyable
class Copyable {
 protected:
  Copyable() = default;
  ~Copyable() = default;
};

class NonCopyable {
 public:
  NonCopyable(const NonCopyable&) = delete;
  NonCopyable& operator=(const NonCopyable&) = delete;

 protected:
  NonCopyable() = default;
  ~NonCopyable() = default;
};

// singleton pattern: support thread safe
class Singleton {
 private:
  Singleton() {}
  ~Singleton() {}

 public:
  Singleton(Singleton const&) = delete;
  Singleton& operator=(Singleton const&) = delete;

  static Singleton& get_instance() {
    static Singleton instance;
    return instance;
  }
};

/**
 * type cast and convert
 */
// force_cast
template <typename To, typename From>
inline To force_cast(From f) {
  To res;
  try {
    res = (To)f;
  } catch (const char* err_msg) {
    std::cerr << err_msg << std::endl;
    throw "force_cast err";
    return NULL;
  }
  return res;
}

// saft_cast type convert: char <-> int <-> long <-> long long int <-> float <-> double <-> string ...
// TODO
// base convert: 2 <-> 8 <-> 10 <-> 16 <-> 32 <-> 64 <-> 128 <-> 256 ...
// TODO

}  // namespace libdd

#endif  // __LIBDD__HPP__
