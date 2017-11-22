#include <node.h>
#include <math.h>
#include <vector>
#include <iostream>

#include <algorithm>
#include <iterator>
#include <random>

using namespace v8;
using namespace std;

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
