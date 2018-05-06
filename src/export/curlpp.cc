// curlpp.cc
#include <node.h>
// #include <curl/curl.h>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Easy.hpp>

// RAII cleanup

curlpp::Cleanup myCleanup;

#include <iostream>
#include <regex>
#include <sstream>

namespace curlpp {

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
using v8::String;
using v8::Isolate;

void GET(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  std::ostringstream os;

  using namespace curlpp::Options;
  curlpp::Easy request;
  request.setOpt(Verbose(false));
  String::Utf8Value s(args[0]);
  std::string str(*s);
  auto _url = args[0]->IsUndefined() ? "https://chipsbot.me/api/membercount" : str;
  string url(_url);
  request.setOpt(Url(url));
  request.setOpt( new curlpp::options::WriteStream( &os ) );
  request.perform();
  string result = os.str();
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
}

void Init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "GET", GET);

  if (const char* env_d = getenv("DEBUG")) {
    regex all ("(,|\\s|^)+(\\*)(,|\\s|$)+");
    regex nocpputil ("(,|\\s|^)+(-cpputilities)(\\b|,|\\s|$)+");
    regex cpputil ("(,|\\s|^)+(cpputilities(\\.|::?)?\\*?)(,|\\s|$)+");
    regex curlpputil ("(,|\\s|^)+(cpputilities(\\.|::?)curlpp(\\.|::?)?\\*?)(,|\\s|$)+");

    string d(env_d);
    smatch m;

    if (regex_search (d, m, all) ||
      (
        !regex_search (d, m, nocpputil) &&
        (
          regex_search (d, m, cpputil) ||
          regex_search (d, m, curlpputil)
        )
      )) {
      cout << "\033[1;31mCurlpp Initiated!\033[0m\n";
    }
  }
}

NODE_MODULE(addon, Init)


}  // namespace curlpp
