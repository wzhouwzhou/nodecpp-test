#include <node.h>
#include <random>
#include <iostream>
using v8::Local;
using v8::Array;
using v8::Isolate;
using v8::Value;
using v8::Number;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

Local<Array> shuffle(Local<Array> arr, bool b = true) {
  random_device rd;
  mt19937 mt(rd());

  Local<Array> array = arr;

  if (b) {
    Isolate* isolate = Isolate::GetCurrent();
    array = Array::New(isolate, array->Length());

    for (int i = array->Length() - 1; i >=0; --i)
      array->Set(i, arr->Get(i));
  }

  for(int it = array->Length(); it > 0; ) {
    uniform_int_distribution<> dis(0, --it);
    const int randomIndex = dis(mt);
    auto element = array->Get(it);
    array->Set(it, array->Get(randomIndex));
    array->Set(randomIndex, element);
  }

  return array;
}

Local<Value> sample(Local<Array> array) {
  random_device rd;
  mt19937 mt(rd());
  uniform_int_distribution<> dis(0, array->Length() - 1);
  return array->Get(dis(mt));
}

Local<Array> dot(Local<Array> arr1, Local<Array> arr2) {
  Isolate* isolate = Isolate::GetCurrent();
  int i, j, k, r1 = Local<Array>::Cast(arr1->Get(0))->Length(), c1 = arr1->Length(), c2 = arr2->Length();
  Local<Array> mult = Array::New(isolate, r1);
  Local<Array> temp;
  for(i = 0; i < r1; ++i) {
    temp = Array::New(isolate, c1);
    for(j = 0; j < c2; ++j) {
      temp->Set(Number::New(isolate, j), Number::New(isolate, 0));
      for(k = 0; k < c1; ++k) {
        temp->Set(Number::New(isolate, j),
          Number::New(isolate,
            temp->Get(j)->NumberValue() +
            Local<Array>::Cast(arr1->Get(i))->Get(k)->NumberValue() * Local<Array>::Cast(arr2->Get(k))->Get(j)->NumberValue()));
      }
    }
    mult->Set(Number::New(isolate, i), temp);
  }
  return mult;
}
