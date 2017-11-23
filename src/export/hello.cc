// hello.cc
#include <node.h>
#include <iostream>
#include <regex>

namespace hello8 {

using std::cout;
using std::string;
using std::getenv;
using std::regex;
using std::smatch;
using std::regex_search;

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void Method(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
  cout<<"Console: Hello World!\n";
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "hello", Method);

  if (const char* env_d = getenv("DEBUG")) {
    regex all ("(,|\\s|^)+(\\*)(,|\\s|$)+");
    regex nocpputil ("(,|\\s|^)+(-cpputilities)(\\b|,|\\s|$)+");
    regex cpputil ("(,|\\s|^)+(cpputilities(\\.|::?)?\\*?)(,|\\s|$)+");
    regex helloutil ("(,|\\s|^)+(cpputilities(\\.|::?)hello(\\.|::?)?\\*?)(,|\\s|$)+");

    string d(env_d);
    smatch m;

    if (regex_search (d, m, all) ||
      (
        !regex_search (d, m, nocpputil) &&
        (
          regex_search (d, m, cpputil) ||
          regex_search (d, m, helloutil)
        )
      )) {
      cout << "\033[1;31mHello Initiated!\033[0m\n";
    }
  }
}

NODE_MODULE(addon, init)

}  // namespace hello
