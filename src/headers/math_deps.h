
#ifndef MATH_DEPS_H
#define MATH_DEPS_H

#include <node.h>

v8::Local<v8::Number> add(const v8::FunctionCallbackInfo<v8::Value>& args);
v8::Local<v8::Number> subtract(const v8::FunctionCallbackInfo<v8::Value>& args);
v8::Local<v8::Number> round(const v8::FunctionCallbackInfo<v8::Value>& args);

#endif
