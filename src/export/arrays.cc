// arrays.cc
#include <iostream>
#include "arrayutil.hpp"
#include <regex>

namespace arrays {


using std::cout;
using std::string;
using std::getenv;
using std::regex;
using std::smatch;

using v8::Local;
using v8::Object;

void InitAll(Local<Object> exports) {
  ArrayUtil::Init(exports);

  if (const char* env_d = getenv("DEBUG")) {
    regex all ("(,|\\s|^)+(\\*)(,|\\s|$)+");
    regex nocpputil ("(,|\\s|^)+(-cpputilities)(\\b|,|\\s|$)+");
    regex cpputil ("(,|\\s|^)+(cpputilities(\\.|::?)?\\*?)(,|\\s|$)+");
    regex arrutil ("(,|\\s|^)+(cpputilities(\\.|::?)arrays(\\.|::?)?\\*?)(,|\\s|$)+");

    string d(env_d);
    smatch m;

    if (std::regex_search (d, m, all) ||
      (
        !std::regex_search (d, m, nocpputil) &&
        (
          std::regex_search (d, m, cpputil) ||
          std::regex_search (d, m, arrutil)
        )
      )) {
      cout << "\033[1;31mArrays Initiated!\033[0m\n";
    }
  }
}

NODE_MODULE(addon, InitAll)


}  // namespace arrays
