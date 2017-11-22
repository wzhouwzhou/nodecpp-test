// arrays.cc
#include <iostream>
#include "arrayutil.hpp"

using std::cout;
using v8::Local;
using v8::Object;

namespace arrays {

using v8::Local;
using v8::Object;

void InitAll(Local<Object> exports) {
  ArrayUtil::Init(exports);
  cout << "\033[1;31mArrays Initiated!\033[0m\n";
}

NODE_MODULE(addon, InitAll)


}  // namespace arrays
