// arrayutil.hpp
#ifndef ARRAYUTIL_HPP
#define ARRAYUTIL_HPP

#include <node.h>
#include <node_object_wrap.h>

namespace arrays {


class ArrayUtil : public node::ObjectWrap {
 public:
  static void Init(v8::Local<v8::Object> exports);
  static void Shuffle(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Sample(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void SumAll(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Dot(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void DotExp(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void DotExpNative(const v8::FunctionCallbackInfo<v8::Value>& args);

 private:
  explicit ArrayUtil(bool safe);
  ~ArrayUtil();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

  static v8::Persistent<v8::Function> constructor;
  bool safe_;
};


}  // namespace arrays

#endif
