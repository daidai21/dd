/* ****************************************************************************
 * File Name   : libdd_test.cpp
 * Author      : DaiDai
 * Mail        : daidai4269@aliyun.com
 * Created Time: 四 11/ 5 17:25:02 2020
 *************************************************************************** */

#include "./libdd.hpp"

using namespace std;
using namespace libdd;

namespace libdd_test {
/* ****************************************************************************
 * basic define
 *************************************************************************** */
namespace basic_define {

void major() {
  cout << "++++++++++++++++++++ "
       << "basic define"
       << " ++++++++++++++++++++" << endl;
  cout << UINT8_MIN << endl;
  cout << UINT16_MIN << endl;
  cout << UINT32_MIN << endl;
  cout << UINT64_MIN << endl;

  cout << PI << endl;
  cout << DD_CHARS_AZ << endl;
  cout << DD_CHARS_az << endl;
  cout << DD_CHARS_AZaz << endl;
}

}  // namespace basic_define

/* ****************************************************************************
 * type cast and convert
 *************************************************************************** */
namespace type_cast_and_convert {

void major() {
}
}  // namespace type_cast_and_convert

/* ****************************************************************************
 * random
 *************************************************************************** */
namespace random {

void major() {
  Random* random = new Random();
  cout << random->randbool() << endl;
}
}  // namespace random

// ****************************************************************************
int main(int argc, char* argv[]) {
  basic_define::major();
  type_cast_and_convert::major();

  return 0;
}
}  // namespace libdd_test
