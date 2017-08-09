#include <node.h>
#include <iostream>
#include <chrono>
struct MeasureTime {
  using precision = std::chrono::nanoseconds;
  std::vector<std::chrono::steady_clock::time_point> times;
  std::chrono::steady_clock::time_point oneLast;
  void p() {
    std::cout << "Execution speed (nanoseconds): "
              << std::chrono::duration_cast<precision>(times.back() - oneLast).count()
              << "\n";
  }
  void m() {
    oneLast = times.back();
    times.push_back(std::chrono::steady_clock::now());
  }
  void t() {
    m();
    p();
    m();
  }
  MeasureTime() {
    times.push_back(std::chrono::steady_clock::now());
  }
};

using v8::Exception;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::String;
using v8::Value;

bool checkArgsL (const int l, Isolate* isolate, const FunctionCallbackInfo<Value>& args){
  if (args.Length() < l) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong number of arguments")));
    return false;
  }

  for(int i = 0; i<args.Length(); i++)
    if(!args[i]->IsNumber()){
      isolate->ThrowException(Exception::TypeError(
          String::NewFromUtf8(isolate, "Wrong arguments")));
      return false;
    }
  return true;
}

bool checkArgs (Isolate* isolate, const FunctionCallbackInfo<Value>& args){
  return checkArgsL(2, isolate, args);
}

/////////
// Add //
/////////

double addAll (const FunctionCallbackInfo<Value>& args){
  double value = 0;
  for(int i = 0; i<args.Length(); ++i)
    value += args[i]->NumberValue();
  return value;
}

Local<Number> add (const FunctionCallbackInfo<Value>& args){
  MeasureTime m;
  Isolate* isolate = args.GetIsolate();
  if(checkArgs(isolate, args)){
    double result = addAll(args);
    std::cout<<"Debug: "<<"Math: Add: "<<result<<"\n";
    m.t();
    return Number::New(isolate, result);
  }

  return Number::New(isolate, -1);
}

//////////////
// Subtract //
//////////////

double subtractAll (const FunctionCallbackInfo<Value>& args){
  double value = args[0]->NumberValue();
  for(int i = 1; i<args.Length(); ++i)
    value -= args[i]->NumberValue();
  return value;
}

Local<Number> subtract (const FunctionCallbackInfo<Value>& args){
  MeasureTime m;
  Isolate* isolate = args.GetIsolate();
  if(checkArgs(isolate, args)){
    double result = subtractAll(args);
    std::cout<<"Debug: "<<"Math: Subtract: "<<result<<"\n";
    m.t();
    return Number::New(isolate, result);
  }

  return Number::New(isolate, -1);
}

///////////
// Round //
///////////

long long roundInternal (long double x){
  return (long long)(x+0.5);
}

Local<Number> round (const FunctionCallbackInfo<Value>& args){
  MeasureTime m;
  Isolate* isolate = args.GetIsolate();
  if(checkArgsL(1, isolate, args)){
    m.t();
    return Number::New(isolate, roundInternal(args[0]->NumberValue()));
  }
  return Number::New(isolate, -1);
}
