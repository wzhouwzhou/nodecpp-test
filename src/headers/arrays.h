// arrays.h

#ifndef ARRAYS_H
#define ARRAYS_H

#include <node.h>

v8::Local<v8::Array> shuffle(v8::Local<v8::Array> arr, bool b);
v8::Local<v8::Value> sample(v8::Local<v8::Array> array);
v8::Local<v8::Array> dot(v8::Local<v8::Array> arr1, v8::Local<v8::Array> arr2);
v8::Local<v8::Array> dotexp(v8::Local<v8::Array> arr, int power);
v8::Local<v8::Array> nativedotexp(v8::Local<v8::Array> arr, int power);
v8::Local<v8::Array> nativeinverse(v8::Local<v8::Array> arr);
#endif
