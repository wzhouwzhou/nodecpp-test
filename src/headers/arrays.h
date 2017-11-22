
#ifndef ARRAYS_H
#define ARRAYS_H

#include <node.h>

v8::Local<v8::Array> shuffle(v8::Local<v8::Array> arr, bool b);
v8::Local<v8::Value> sample(v8::Local<v8::Array> array);

#endif
