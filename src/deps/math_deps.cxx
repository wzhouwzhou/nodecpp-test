#include <node.h>
#include <iostream>

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
  Isolate* isolate = args.GetIsolate();
  if(checkArgs(isolate, args)){
    double result = addAll(args);
    std::cout<<"Debug: "<<"Math: Add: "<<result<<"\n";
    return Number::New(isolate, result);
  }

  return Number::New(isolate, -1);
}

//////////////
// Subtract //
//////////////

double subtractAll (const FunctionCallbackInfo<Value>& args){
  double value = 0;
  for(int i = 0; i<args.Length(); ++i)
    value -= args[i]->NumberValue();
  return value;
}

Local<Number> subtract (const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = args.GetIsolate();
  if(checkArgs(isolate, args)){
    double result = subtractAll(args);
    std::cout<<"Debug: "<<"Math: Subtract: "<<result<<"\n";
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
  Isolate* isolate = args.GetIsolate();
  if(checkArgsL(1, isolate, args))
    return Number::New(isolate, roundInternal(args[0]->NumberValue()));
  return Number::New(isolate, -1);
}
