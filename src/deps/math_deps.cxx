#include <node.h>
#include <iostream>

#include "timings.hpp"

using v8::Exception;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Function;

bool checkArgsL (const int l, Isolate* isolate, const FunctionCallbackInfo<Value>& args){
  if (args.Length() < l) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong number of arguments")));
    return false;
  }

  for(int i = 0; i<args.Length()-1; i++)
    if(!args[i]->IsNumber()){
      isolate->ThrowException(Exception::TypeError(
          String::NewFromUtf8(isolate, "Wrong arguments")));
      return false;
    }

  if(!args[args.Length()-1]->IsNumber() && !args[args.Length()-1]->IsFunction()) return false;

  return true;
}

bool checkArgs (Isolate* isolate, const FunctionCallbackInfo<Value>& args){
  return checkArgsL(2, isolate, args);
}

/////////
// Add //
/////////

double addAll (const FunctionCallbackInfo<Value>& args, bool l = false){
  double value = 0;
  int m = l ? args.Length() - 1 : args.Length();
  for(int i = 0; i < m; ++i)
    value += args[i]->NumberValue();
  return value;
}

Local<Number> add (const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = args.GetIsolate();
  if(checkArgs(isolate, args)){
    bool useTime = false;
    if(args[args.Length()-1]->IsFunction()) useTime = true;
    if(useTime){
      MeasureTime m;

      const unsigned argc = 1;

      double result = addAll(args, true);
      std::cout<<"Debug: "<<"Math: Add: "<<result<<" | ";
      Local<Value> argv[argc] = { String::NewFromUtf8(isolate, m.t()) };
      Local<Function> cb = Local<Function>::Cast(args[args.Length()-1]);

      cb->Call(Null(isolate), argc, argv);

      return Number::New(isolate, result);
    } else {
      return Number::New(isolate, addAll(args));
    }
  }

  return Number::New(isolate, -1);
}

//////////////
// Subtract //
//////////////

double subtractAll (const FunctionCallbackInfo<Value>& args, bool l = false){
  double value = args[0]->NumberValue();
  int m = l ? args.Length() - 1 : args.Length();
  for(int i = 0; i < m; ++i)
    value -= args[i]->NumberValue();
  return value;
}

Local<Number> subtract (const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = args.GetIsolate();
  if(checkArgs(isolate, args)){
    bool useTime = false;
    if(args[args.Length()-1]->IsFunction()) useTime = true;
    if(useTime){
      MeasureTime m;

      const unsigned argc = 1;

      double result = subtractAll(args, true);
      std::cout<<"Debug: "<<"Math: Subtract: "<<result<<" | ";
      Local<Value> argv[argc] = { String::NewFromUtf8(isolate, m.t()) };
      Local<Function> cb = Local<Function>::Cast(args[args.Length()-1]);

      cb->Call(Null(isolate), argc, argv);

      return Number::New(isolate, result);
    } else {
      return Number::New(isolate, subtractAll(args));
    }
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
