// math.cc
#include <node.h>
#include "math_deps.h"
#include <iostream>
#include <regex>

namespace math {


using std::cout;
using std::string;
using std::getenv;
using std::regex;
using std::smatch;
using std::regex_search;

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
  NODE_SET_METHOD(exports, "subtract", Subtract);
  NODE_SET_METHOD(exports, "round", Round);

  if (const char* env_d = getenv("DEBUG")) {
    regex all ("(,|\\s|^)+(\\*)(,|\\s|$)+");
    regex nocpputil ("(,|\\s|^)+(-cpputilities)(\\b|,|\\s|$)+");
    regex cpputil ("(,|\\s|^)+(cpputilities(\\.|::?)?\\*?)(,|\\s|$)+");
    regex mathutil ("(,|\\s|^)+(cpputilities(\\.|::?)maths(\\.|::?)?\\*?)(,|\\s|$)+");

    string d(env_d);
    smatch m;

    if (regex_search (d, m, all) ||
      (
        !regex_search (d, m, nocpputil) &&
        (
          regex_search (d, m, cpputil) ||
          regex_search (d, m, mathutil)
        )
      )) {
      cout << "\033[1;31mMath Initiated!\033[0m\n";
    }
  }
}

NODE_MODULE(addon, Init)


}  // namespace math
