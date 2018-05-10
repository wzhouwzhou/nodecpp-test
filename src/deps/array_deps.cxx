#include <node.h>
#include <random>
#include <iostream>
#include <vector>
#include <set>

using v8::Local;
using v8::Array;
using v8::Isolate;
using v8::Value;
using v8::Number;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::vector;
using std::pair;
using std::set;

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
  int r1 = arr1.size(), c2 = arr2[0].size(), r2 = arr2.size();

  vector<vector<double> > mult;
  mult.resize(r1);
  for(int i = 0; i < r1; ++i) {
    vector<double> temp;
    temp.resize(c2);
    for(int j = 0; j < c2; ++j) {
      temp[j] = 0;
      for(int k = 0; k < r2; ++k) {
        temp[j] += arr1[i][k] * arr2[k][j];
      }
    }
    mult[i] = temp;
  }

  return mult;
}

vector<vector<double> > native2d(Local<Array> arr) {
  int cc = Local<Array>::Cast(arr->Get(0))->Length(), rc = arr->Length();
  // std::cout << "Wrapping from v8 to native, rc:" << rc << " cc: " << cc << std::endl;
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

//\\===================================================================================================\\//
vector<vector<double> > get_cofactor(vector<vector<double> > input, vector<vector<double> > temp, int p, int q, int n) {
  int i = 0, j = 0;
  for(int row = 0;row < n; ++row) {
    for(int col = 0;col < n; ++col) {
      if (row != p && col != q) {
        temp[i][j++] = input[row][col];
        // std::cout << "Storing cofactor " << input[row][col] << std::endl;
        if (j == n - 1) {
          j = 0;
          ++i;
        }
      }
    }
  }
  return temp;
}

vector<vector<double> > resize(vector<vector<double> > input, int size) {
  // std::cout << "Resizing to size " << size;
  input.resize(size);
  for (int i = 0; i < size; i++) input[i].resize(size);
  // std::cout << "... Done" << std::endl;
  return input;
}

double determinant(vector<vector<double> > input, int n) {
  // std::cout << "Call to determinant, n:" << n << std::endl;
  // std::cout << input[0][0] << ":" << input[0][1] << std::endl;
  // std::cout << input[1][0] << ":" << input[1][1] << std::endl;
  if (n == 1) return input[0][0];

  double det = 0;

  vector<vector<double> > cofactors;
  cofactors = resize(cofactors, input.size());
  double sign = 1;

  for (int f = 0; f < n; ++f) {
    cofactors = get_cofactor(input, cofactors, 0, f, n);
    double dett = determinant(cofactors, n - 1);
    double preterm = input[0][f] * dett;
    double term = preterm == 0 || preterm == -0 ? 0 : sign * preterm;
    // std::cout << "Contributing term: " << term << " Input " << input[0][f] << " Det " << dett << std::endl;
    det += term;
    sign = -sign;
  }

  return det;
}

vector<vector<double> > adjoint(vector<vector<double> > input) {
  // std::cout << "Call to adjoint" << std::endl;
  vector<vector<double> > adj;
  int N = input.size();
  adj = resize(adj, N);
  if (N == 1) {
    // std::cout << "A" << std::endl;
    adj[0][0] = 1;
    // std::cout << "B" << std::endl;
    return adj;
  }
  // std::cout << "C" << std::endl;
  int sign = 1;
  vector<vector<double> > cofactors;
  cofactors = resize(cofactors, N);

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      // std::cout << "D" << std::endl;
      cofactors = get_cofactor(input, cofactors, i, j, N);
      sign = ((i + j) % 2 == 0) ? 1 : -1;
      double preterm = determinant(cofactors, N - 1);
      adj[j][i] = preterm == 0 || preterm == -0 ? 0 : sign * preterm;

      // std::cout << "E" << std::endl;
    }
  }
  return adj;
}

vector<vector<double> > inverse(vector<vector<double> > input) {
  vector<vector<double> > inverse;
  int N = input.size();
  inverse = resize(inverse, N);
  double det = determinant(input, N);
  if (det == 0) {
    std::cout << "Singular matrix, can't find its inverse" << std::endl;
    return inverse;
  }

  vector<vector<double> > adj = adjoint(input);
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j) {
      double preterm = adj[i][j] / double(det);
      inverse[i][j] = preterm == 0 || preterm == -0 ? 0 : preterm;
    }

  return inverse;
}

vector<vector<double> > to_exp_length_mat(vector<vector<double> > input) {
  vector<vector<double> > result;
  int N = input.size() - 1;
  result = resize(result, N);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (j != N) result[i][j] = input[i][j];
      else result[i][j] = 0;

      if (i == j) {
        double preterm = result[i][j] - 1;
        result[j][i] = preterm == 0 || preterm == -0 ? 0 : preterm;
      }
    }
  }
  return result;
}

vector<vector<double> > inv_exp_length_mat(vector<vector<double> > input) {
  return inverse(to_exp_length_mat(input));
}

Local<Array> v8transpose(Local<Array> input) {
  Isolate* isolate = Isolate::GetCurrent();
  int c1 = Local<Array>::Cast(input->Get(0))->Length(), r1 = input->Length();
  Local<Array> temp, out = Array::New(isolate, c1);
  for (int i = 0; i < c1; ++i) {
    temp = Array::New(isolate, r1);
    for (int j = 0; j < r1; ++j) {
      temp->Set(Number::New(isolate, j), Local<Array>::Cast(input->Get(j))->Get(i));
    }
    out->Set(Number::New(isolate, i), temp);
  }
  return out;
}


vector<vector<double> > transpose(vector<vector<double> > input) {
  vector<vector<double> > out;
  int N = input.size();

  out.resize(input[0].size());

  for (int i = 0; i < (int) input[0].size(); ++i) {
    out[i].resize(N);
    for (int j = 0; j < N; ++j) {
      out[i][j] = input[j][i];
    }
  }
  return out;
}

vector<vector<double> > to_steady_state_mat(vector<vector<double> > input) {
  vector<vector<double> > sp;
  sp = transpose(input);
  for (unsigned long i = 0; i < input.size(); ++i) sp[i][i] -= 1.;

  int last_row = sp.size() - 1;
  for (unsigned long i = 0; i < sp[last_row].size(); ++i) sp[last_row][i] = 1;

  return sp;
}

void print_array(const vector<vector<double> >& v) {
  for (unsigned long i = 0; i < v.size(); ++i) {
    for (unsigned long j = 0; j < v[i].size(); ++j) {
      std::cout << v[i][j] << "|";
    }
    std::cout << std::endl;
  }
}

vector<vector<double> > get_prob_mat_from_jump(vector<vector<double> > doublejumps, int spinner, int rows, int cols) {
  vector<pair<int, int> > jumps;
  jumps.resize(doublejumps.size());
  // std::cout << "Resized board ... Spinner " << spinner << " rows " << rows << " cols " << cols << std::endl;
  for(unsigned long i = 0; i < doublejumps.size(); ++i) {
    jumps[i].first = (int) doublejumps[i][0];
    jumps[i].second = (int) doublejumps[i][1];
  }
  // std::cout << "creating board" << std::endl;
  vector<vector<double> > board;
  int squares = rows * cols;
  board = resize(board, squares);
  
  for (int i = 0; i < squares; ++i) {
    for (int j = 0; j < squares; ++j) {
      board[i][j] = 0.;
    }
  }
  // std::cout << "Set all values in board to 0" << std::endl;

  double default_rate = 1. / spinner;

  for (int i = 0; i < squares - 1; ++i) {
    for (int j = i + 1; j < i + 1 + spinner; ++j) {
      if (j >= squares) board[i][i] += default_rate;
      else board[i][j] = default_rate;
    }
  }
  board[squares - 1][0] = 1.;
  // print_array(board);
  // std::cout << "Set all values in board to default rate" << std::endl;

  set<int> empty_pos;
  for (unsigned long i = 0; i < jumps.size(); ++i) {
    int start = jumps[i].first;
    int end = jumps[i].second;
    for (int j = 0; j < squares; ++j) {
      if (board[j][start] > 0) {
        board[j][end] += board[j][start];
        board[j][start] = 0.;
      }
    }
    empty_pos.insert(start);
  }
  // std::cout << "Move jumps" << std::endl;
  set<int>::reverse_iterator ritr = empty_pos.rbegin();
  for(; ritr != empty_pos.rend(); ++ritr) {
    for(int i = 0; i < squares; ++i) {
      board[i].erase(board[i].begin() + *ritr);
    }
  }
  // std::cout << "Erased col" << std::endl;
  for (ritr = empty_pos.rbegin(); ritr != empty_pos.rend(); ++ritr) {
    board.erase(board.begin() + *ritr);
  }
  // std::cout << "Erased row" << std::endl;
  return board;
}

//\\===================================================================================================\\//

Local<Array> wrap2d(vector<vector<double> > a) {
  Isolate* isolate = Isolate::GetCurrent();
  int rc = a.size(), cc = a[0].size();
  // std::cout << "Wrapping from native to v8, rc:" << rc << " cc: " << cc << std::endl;
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
  // // std::cout << "Using wrapped operations" << std::endl;
  Local<Array> result = arr;
  for(int i = 0; i < power - 1; ++i)
    result = dot(result, arr);
  return result;
}

Local<Array> nativedotexp(Local<Array> _arr, int power = 1) {
  // // std::cout << "Using native operations" << std::endl;
  vector<vector<double> > arr = native2d(_arr), result = arr;
  for(int i = 0; i < power - 1; ++i)
    result = nativeDot(result, arr);
  return wrap2d(result);
}

Local<Array> nativeinverse(Local<Array> arr) {
  return wrap2d(inverse(native2d(arr)));
}

Local<Array> wrapped_transpose(Local<Array> arr) {
  return v8transpose(arr);
}

//inv_exp_length_mat
Local<Array> wrapped_inv_exp_length_mat(Local<Array> arr) {
  return wrap2d(inv_exp_length_mat(native2d(arr)));
}

Local<Array> native_export_dot(Local<Array> arr1, Local<Array> arr2) {
  return wrap2d(nativeDot(native2d(arr1), native2d(arr2)));
}

//to_steady_state_mat
Local<Array> wrapped_to_steady_state_mat(Local<Array> arr) {
  return wrap2d(to_steady_state_mat(native2d(arr)));
}

Local<Array> get_prob_mat(Local<Array> jumps, int spinner, int rows, int cols) {
  return wrap2d(get_prob_mat_from_jump(native2d(jumps), spinner, rows, cols));
}