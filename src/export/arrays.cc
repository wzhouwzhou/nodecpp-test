// arrays.cc
#include <iostream>
#include "arrayutil.hpp"

using std::cout;
/*
using v8::FunctionCallbackInfo;
using v8::Value;*/
using v8::Local;
using v8::Object;
/*using v8::Array;
using v8::Isolate;
using v8::String;
using v8::Function;
using v8::FunctionTemplate;*/

namespace arrays {

using v8::Local;
using v8::Object;

void InitAll(Local<Object> exports) {
  ArrayUtil::Init(exports);
  cout << "\033[1;31mArrays Initiated!\033[0m\n";
}
/*
void ReallyInit(const FunctionCallbackInfo<Value>& args) {
Isolate* isolate = args.GetIsolate();
Local<Object> exports = Local<Object>::Cast(args[0]);
Local<Object> obj = args[0]->IsUndefined() ? Object::New(isolate) : Local<Object>::Cast(args[0]);


cout << "\033[1;31mArrays Initiated!\033[0m\n";
args.GetReturnValue().Set(obj);
}

void Init(Local<Object> exports) {
NODE_SET_METHOD(exports, "__init", ReallyInit);
}*/

NODE_MODULE(addon, InitAll)


}  // namespace arrays
