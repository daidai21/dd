/* ****************************************************************************
 * File Name   : libdd.hpp
 * Author      : DaiDai
 * Mail        : daidai4269@aliyun.com
 * Created Time: 四 11/ 5 17:17:57 2020
 * GCC version : C++11
 * Platform    : Unix-like
 *************************************************************************** */

/*
* API like: Python3, Java8
*/

#ifndef __LIBDD__HPP__
#define __LIBDD__HPP__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <chrono>
#include <exception>
#include <iostream>
#include <mutex>
#include <random>
#include <string>
#include <vector>

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
const std::string DD_CHARS_AZ = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string DD_CHARS_az = "abcdefghijklmnopqrstuvwxyz";
const std::string DD_CHARS_AZaz = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

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
template <typename FromType, typename ToType>
struct converter {};

template <typename FromType>
struct converter<int, FromType> {
 public:
  static int convert(const std::string& from) {
    return std::atoi(from.c_str());
  }

  static int convert(const char* from) {
    return std::atoi(from);
  }
};

template <typename FromType>
struct converter<long int, FromType> {
 public:
  static long int convert(const std::string& from) {
    return std::atol(from.c_str());
  }

  static long int convert(const char* from) {
    return std::atol(from);
  }
};

template <typename FromType>
struct converter<long long int, FromType> {
 public:
  static long long int convert(const std::string& from) {
    return std::atoll(from.c_str());
  }

  static long long int convert(const char* from) {
    return std::atoll(from);
  }
};

template <typename FromType>
struct converter<double, FromType> {
 public:
  static double convert(const std::string& from) {
    return std::atof(from.c_str());
  }

  static double convert(const char* from) {
    return std::atof(from);
  }
};

template <typename FromType>
struct converter<float, FromType> {
 public:
  static double convert(const std::string& from) {
    return static_cast<float>(std::atof(from.c_str()));
  }

  static double convert(const char* from) {
    return static_cast<float>(std::atof(from));
  }
};

template <typename FromType>
struct converter<bool, FromType> {
 public:
  static bool convert(int from) {
    return from > 0 ? true : false;
  }

  static bool convert(const std::string& from) {
    return std::atoi(from.c_str()) > 0 ? true : false;
  }
};

template <typename FromType>
struct converter<std::string, FromType> {
 public:
  static std::string convert(int from) {
    return std::to_string(from);
  }

  static std::string convert(double from) {
    return std::to_string(from);
  }

  static std::string convert(float from) {
    return std::to_string(from);
  }

  static std::string convert(const std::string& from) {
    return from;
  }

  static std::string convert(const char* from) {
    return from;
  }

  static std::string convert(char from) {
    return std::string(&from);
  }
};

template <typename ToType, typename FromType>
ToType safe_cast(const FromType& from) {
  return converter<ToType, FromType>::convert(from);
}

// base convert: 2 <-> 8 <-> 10 <-> 16 <-> 32 <-> 64 <-> 128 <-> 256 ...
// itoa func ref: https://www.techiedelight.com/implement-itoa-function-in-c/
inline void swap(char* x, char* y) {
  char t = *x;
  *x = *y;
  *y = t;
}

char* reverse(char* buffer, int i, int j) {
  while (i < j)
    swap(&buffer[i++], &buffer[j--]);
  return buffer;
}

char* itoa(int value, char* buffer, int base) {  // FIXME
  if (base < 2 || base > 32)
    return buffer;
  int n = abs(value);
  int i = 0;
  while (n) {
    int r = n % base;
    if (r >= 10)
      buffer[i++] = 65 + (r - 10);
    else
      buffer[i++] = 48 + r;
    n = n / base;
  }
  if (i == 0)
    buffer[i++] = '0';
  if (value < 0 && base == 10)
    buffer[i++] = '-';
  buffer[i] = '\0';
  return reverse(buffer, 0, i - 1);
}

std::string base_convert(const std::string& val, int from_base, int to_base) {
  char* buf;
  strtol(val.c_str(), &buf, from_base);
  char* res = nullptr;
  itoa(safe_cast<int>(buf), res, to_base);
  return std::string(res);
}

template <typename FromType>
std::string base_convert(const FromType& val, int from_base, int to_base) {
  return base_convert(safe_cast<std::string>(val), from_base, to_base);
}

/**
 * random
 */
class Random {
 public:
  Random() {
    seed_ = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    engine_.seed(seed_);
  }

  Random(long long int seed) {
    seed_ = seed;
    engine_.seed(seed_);
  }

  int randint(int start, int end) {
    std::uniform_int_distribution<int> res(start, end);
    return res(engine_);
  }

  bool randbool() {
    return randint(0, 1) == 1 ? true : false;
  }

  double uniform(double start, double end) {
    std::uniform_int_distribution<double> res(start, end);
    return res(engine_);
  }

  template <typename Type>
  Type choice(const std::vector<Type>& arr) {
    int idx = randint(0, arr.size() - 1);
    return arr[idx];
  }

  char choice(const std::string& arr) {
    int idx = randint(0, arr.size() - 1);
    return arr[idx];
  }

  int randrange(int start, int end, int step) {
    std::vector<int> tmp;
    for (int i = start; i < end; i += step) {
      tmp.push_back(i);
    }
    int idx = randint(0, tmp.size() - 1);
    return tmp[idx];
  }

  template <typename Type>
  void shuffle(std::vector<Type>& arr) {  // FIXME: array...
    std::shuffle(arr.begin(), arr.end(), engine_);
  }

  template <typename Type>
  std::vector<Type> sample(const std::vector<Type>& arr, int num) {
    std::vector<Type> res(num);
    for (int i = 0; i < num; ++i) {
      res[i] = choice(arr);
    }
    return res;
  }

  std::string sample(const std::string& arr, int num) {
    std::string res;
    for (int i = 0; i < num; ++i) {
      res.push_back(choice(arr));
    }
    return res;
  }

 private:
  std::default_random_engine engine_;
  long long int seed_;
};

/**
 * ID generate
 * 
 * rand-str, rand-num, snowflake, auto-inc-id
 * TODO: UUID, segment mode, ...
 */
// ID: 0 - 41 bits timestamp - 5 bits data center id - 5 bits machine id - 12 bits sequence number
// support thread safe
class SnowFlake {
 public:
  SnowFlake(const int data_center_id, const int machine_id);

  std::uint64_t next_id();

 private:
  std::uint64_t get_next_ms();
  std::uint64_t get_curr_timestamp();

 private:
  static const std::uint64_t start_timestamp = 1480166465631;

  static const std::uint64_t sequence_bit = 12;
  static const std::uint64_t machine_bit = 5;
  static const std::uint64_t data_center_bit = 5;

  static const std::uint64_t sequence_max_val = -1 ^ (std::uint64_t(-1) << sequence_bit);
  static const std::uint64_t machine_max_val = -1 ^ (std::uint64_t(-1) << machine_bit);
  static const std::uint64_t data_center_max_val = -1 ^ (std::uint64_t(-1) << data_center_bit);

  static const std::uint64_t machine_left = sequence_bit;
  static const std::uint64_t data_center_left = sequence_bit + machine_bit;
  static const std::uint64_t timestamp_left = data_center_left + data_center_bit;

  std::uint64_t data_center_id;
  std::uint64_t machine_id;
  std::uint64_t sequence_id;
  std::uint64_t last_timestamp;

  std::mutex mtx;
};

}  // namespace libdd

#endif  // __LIBDD__HPP__
