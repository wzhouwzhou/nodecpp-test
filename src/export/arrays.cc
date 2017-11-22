// arrays.cc
#include <node.h>
#include "arrays.h"
#include <iostream>

using namespace std;
using namespace v8;

namespace arrays {

void Shuffle(const FunctionCallbackInfo<Value>& args) {
  args.GetReturnValue().Set(shuffle(Local<Array>::Cast(args[0]), args[1]->IsUndefined() ? true : args[1]->BooleanValue()));
}

void Init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "shuffle", Shuffle);
  cout<<"Shuffle Initiated!\n";
  cout << "\033[1;31mArrays Initiated!\033[0m\n";
}

NODE_MODULE(addon, Init)

}  // namespace arrays
