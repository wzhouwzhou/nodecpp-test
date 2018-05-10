// ArrayUtil.cpp
#include "arrays.h"
#include "arrayutil.hpp"
#include "math_deps.h"

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

ArrayUtil::ArrayUtil(bool safe) : safe_(safe) {}

ArrayUtil::~ArrayUtil() {}

void ArrayUtil::Init(Local<Object> exports) {
  Isolate* isolate = exports->GetIsolate();

  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "ArrayUtil"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  NODE_SET_PROTOTYPE_METHOD(tpl, "shuffle", Shuffle);
  NODE_SET_PROTOTYPE_METHOD(tpl, "sample", Sample);
  NODE_SET_PROTOTYPE_METHOD(tpl, "dot", Dot);
  NODE_SET_PROTOTYPE_METHOD(tpl, "sumAll", SumAll);
  NODE_SET_PROTOTYPE_METHOD(tpl, "dotexp", DotExp);
  NODE_SET_PROTOTYPE_METHOD(tpl, "nativedotexp", DotExpNative);
  NODE_SET_PROTOTYPE_METHOD(tpl, "nativeinverse", InverseNative);
  NODE_SET_PROTOTYPE_METHOD(tpl, "wrapped_inv_exp_length_mat", WrappedInvExpLengthMat);
  NODE_SET_PROTOTYPE_METHOD(tpl, "transpose", Transpose);
  NODE_SET_PROTOTYPE_METHOD(tpl, "wrapped_to_steady_state_mat", WrappedToSteadyStateMat);
  NODE_SET_PROTOTYPE_METHOD(tpl, "get_prob_mat", GetProbMat);
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

void ArrayUtil::SumAll(const FunctionCallbackInfo<Value>& args) {
  args.GetReturnValue().Set(add(args));
}

void ArrayUtil::Dot(const FunctionCallbackInfo<Value>& args) {
  Local<Array> array2, array = Local<Array>::Cast(args[0]);
  if (args.Length() == 1) {
    array2 = array;
  } else {
    Local<Value> temp = args[1];
    if(temp->IsNull() || temp->IsUndefined())
      array2 = array;
    else
      array2 = Local<Array>::Cast(args[1]);
  }
  args.GetReturnValue().Set(native_export_dot(array, array2));
}

void ArrayUtil::DotExp(const FunctionCallbackInfo<Value>& args) {
  Local<Array> array = Local<Array>::Cast(args[0]);
  int power = args[1]->Int32Value();
  args.GetReturnValue().Set(dotexp(array, power));
}

void ArrayUtil::DotExpNative(const FunctionCallbackInfo<Value>& args) {
  Local<Array> array = Local<Array>::Cast(args[0]);
  int power = args[1]->Int32Value();
  args.GetReturnValue().Set(nativedotexp(array, power));
}

void ArrayUtil::Transpose(const FunctionCallbackInfo<Value>& args) {
  Local<Array> array = Local<Array>::Cast(args[0]);
  args.GetReturnValue().Set(wrapped_transpose(array));
}

void ArrayUtil::InverseNative(const FunctionCallbackInfo<Value>& args) {
  Local<Array> array = Local<Array>::Cast(args[0]);
  args.GetReturnValue().Set(nativeinverse(array));
}

void ArrayUtil::WrappedInvExpLengthMat(const FunctionCallbackInfo<Value>& args) {
  Local<Array> array = Local<Array>::Cast(args[0]);
  args.GetReturnValue().Set(wrapped_inv_exp_length_mat(array));
}

void ArrayUtil::WrappedToSteadyStateMat(const FunctionCallbackInfo<Value>& args) {
  Local<Array> array = Local<Array>::Cast(args[0]);
  args.GetReturnValue().Set(wrapped_to_steady_state_mat(array));
}

void ArrayUtil::GetProbMat(const FunctionCallbackInfo<Value>& args) {
  Local<Array> jumps = Local<Array>::Cast(args[0]);
  int spinner = args[1]->Int32Value();
  int rows = args[2]->Int32Value();
  int cols = args[3]->Int32Value();
  args.GetReturnValue().Set(get_prob_mat(jumps, spinner, rows, cols));
}

}  // namespace arrays