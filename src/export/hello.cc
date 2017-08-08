// hello.cc
#include <node.h>
#include <iostream>

namespace hello8 {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void Method(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
  std::cout<<"Console: Hello World!\n";
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "hello", Method);
  std::cout << "\033[1;31mHello Initiated!\033[0m\n";
}

NODE_MODULE(addon, init)

}  // namespace hello
