// math.cc
#include <node.h>
#include "math_deps.h"
#include <iostream>

namespace math {

using v8::FunctionCallbackInfo;
using v8::Local;
using v8::Object;
using v8::Value;

void Add(const FunctionCallbackInfo<Value>& args) {
  args.GetReturnValue().Set(add(args));
}
void Subtract(const FunctionCallbackInfo<Value>& args) {
  args.GetReturnValue().Set(subtract(args));
}
void Round(const FunctionCallbackInfo<Value>& args) {
  args.GetReturnValue().Set(round(args));
}
void Init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "add", Add);
  std::cout<<"Add Initiated!\n";
  NODE_SET_METHOD(exports, "subtract", Subtract);
  std::cout<<"Subtract Initiated!\n";
  NODE_SET_METHOD(exports, "round", Round);
  std::cout<<"Round Initiated!\n";
  std::cout << "\033[1;31mMath Initiated!\033[0m\n";
}

NODE_MODULE(addon, Init)

}  // namespace math
