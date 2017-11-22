// arrayutil.h
#ifndef ARRAYUTIL_H
#define ARRAYUTIL_H

#include <node.h>
#include <node_object_wrap.h>

namespace arrays {


class ArrayUtil : public node::ObjectWrap {
 public:
  static void Init(v8::Local<v8::Object> exports);

 private:
  explicit ArrayUtil(bool safe);
  ~ArrayUtil();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Shuffle(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Sample(const v8::FunctionCallbackInfo<v8::Value>& args);
  static v8::Persistent<v8::Function> constructor;
  bool safe_;
};


}  // namespace arrays

#endif
