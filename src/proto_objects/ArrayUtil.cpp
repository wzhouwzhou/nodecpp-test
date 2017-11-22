// ArrayUtil.cc
#include "arrays.h"
#include "arrayutil.hpp"

namespace arrays {

using v8::Context;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::Persistent;
using v8::String;
using v8::Value;
using v8::Array;

Persistent<Function> ArrayUtil::constructor;

ArrayUtil::ArrayUtil(bool safe) : safe_(safe) {
}

ArrayUtil::~ArrayUtil() {
}

void ArrayUtil::Init(Local<Object> exports) {
  Isolate* isolate = exports->GetIsolate();

  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "ArrayUtil"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  NODE_SET_PROTOTYPE_METHOD(tpl, "shuffle", Shuffle);
  NODE_SET_PROTOTYPE_METHOD(tpl, "sample", Sample);
  // NODE_SET_STATIC_METHOD(tpl, "ssample", Sample);
  constructor.Reset(isolate, tpl->GetFunction());
  exports->Set(String::NewFromUtf8(isolate, "ArrayUtil"), tpl->GetFunction());
}

void ArrayUtil::New(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.IsConstructCall()) {
    bool _safe = args[0]->IsUndefined() ? true : args[0]->BooleanValue();
    ArrayUtil* obj = new ArrayUtil(_safe);
    obj->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
  } else {
    const int argc = 1;
    Local<Value> argv[argc] = { args[0] };
    Local<Context> ctx = isolate->GetCurrentContext();
    Local<Function> cons = Local<Function>::New(isolate, constructor);
    args.GetReturnValue().Set(cons->NewInstance(ctx, argc, argv).ToLocalChecked());
  }
}

void ArrayUtil::Sample(const FunctionCallbackInfo<Value>& args) {
  Local<Array> array;
  if (args.Length() == 1) {
    array = Local<Array>::Cast(args[0]);
  } else {
    Isolate* isolate = args.GetIsolate();
    array = Array::New(isolate);
    int i = 0;
    for (int argi = 0; argi < args.Length();) {
      Local<Array> arr = Local<Array>::Cast(args[argi++]);
      for (unsigned int eli = 0; eli < arr->Length();) array->Set(i++, arr->Get(eli++));
    }
  }
  args.GetReturnValue().Set(sample(array));
}

void ArrayUtil::Shuffle(const FunctionCallbackInfo<Value>& args) {
  ArrayUtil* obj = ObjectWrap::Unwrap<ArrayUtil>(args.Holder());

  args.GetReturnValue().Set(shuffle(Local<Array>::Cast(args[0]),
    args[1]->IsUndefined() ? obj->safe_ : args[1]->BooleanValue()));
}

}  // namespace arrays
