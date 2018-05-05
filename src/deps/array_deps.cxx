#include <node.h>
#include <random>
// #include <iostream>
#include <vector>

using v8::Local;
using v8::Array;
using v8::Isolate;
using v8::Value;
using v8::Number;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::vector;

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
  Local<Array> temp, mult = Array::New(isolate, r1);
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

vector<vector<double> > nativeDot(vector<vector<double> > arr1, vector<vector<double> > arr2) {
  int i, j, k, r1 = arr1[0].size(), c1 = arr1.size(), c2 = arr2.size();
  vector<vector<double> > mult;
  mult.resize(r1);
  for(i = 0; i < r1; ++i) {
    vector<double> temp;
    temp.resize(c1);
    for(j = 0; j < c2; ++j) {
      temp[j] = 0;
      for(k = 0; k < c1; ++k) {
        temp[j] += arr1[i][k] * arr2[k][j];
      }
    }
    mult[i] = temp;
  }

  return mult;
}

vector<vector<double> > native2d(Local<Array> arr) {
  int cc = Local<Array>::Cast(arr->Get(0))->Length(), rc = arr->Length();
  vector<vector<double> > array;
  array.resize(rc);
  for (int i = 0; i < rc; ++i) {
    array[i].resize(cc);
    for (int j = 0; j < cc; ++j) {
      array[i][j] = Local<Array>::Cast(arr->Get(i))->Get(j)->NumberValue();
    }
  }
  return array;
}

Local<Array> wrap2d(vector<vector<double> > a) {
  Isolate* isolate = Isolate::GetCurrent();
  int rc = a.size(), cc = a[0].size();
  Local<Array> temp, array = Array::New(isolate, rc);
  for (int i = 0; i < rc; ++i) {
    temp = Array::New(isolate, cc);
    for (int j = 0; j < cc; ++j) {
      temp->Set(Number::New(isolate, j), Number::New(isolate, a[i][j]));
    }
    array->Set(Number::New(isolate, i), temp);
  }

  return array;
}

Local<Array> dotexp(Local<Array> arr, int power = 1) {
  // std::cout << "Using wrapped operations" << std::endl;
  Local<Array> result = arr;
  for(int i = 0; i < power - 1; ++i)
    result = dot(result, arr);
  return result;
}

Local<Array> nativedotexp(Local<Array> _arr, int power = 1) {
  // std::cout << "Using native operations" << std::endl;
  vector<vector<double> > arr = native2d(_arr), result = arr;
  for(int i = 0; i < power - 1; ++i)
    result = nativeDot(result, arr);
  return wrap2d(result);
}
