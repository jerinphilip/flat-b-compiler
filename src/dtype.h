#ifndef DTYPE_H
#define DTYPE_H
#include "ast.h"

struct DataType {
  FlatBType dtype;
  union {
    int *A;
    int i;
    bool b;
    int *p;
    char *s;
  } T;

  DataType operator+(DataType x) {
    DataType result;
    result.dtype = dtype;
    switch (dtype) {
    case FlatBType::Int:
      result.T.i = T.i + x.T.i;
      break;
    default:
      break;
    }
    return result;
  }

  DataType operator-(DataType x) {
    DataType result;
    result.dtype = dtype;
    switch (dtype) {
    case FlatBType::Int:
      result.T.i = T.i - x.T.i;
      break;
    default:
      break;
    }
    return result;
  }

  DataType operator*(DataType x) {
    DataType result;
    result.dtype = dtype;
    switch (dtype) {
    case FlatBType::Int:
      result.T.i = T.i * x.T.i;
      break;
    default:
      break;
    }
    return result;
  }

  DataType operator/(DataType x) {
    DataType result;
    result.dtype = dtype;
    switch (dtype) {
    case FlatBType::Int:
      result.T.i = T.i / x.T.i;
      break;
    default:
      break;
    }
    return result;
  }

  DataType operator<(DataType x) {
    DataType result;
    result.dtype = FlatBType::Bool;
    switch (dtype) {
    case FlatBType::Int:
      result.T.i = T.i < x.T.i;
      break;
    default:
      break;
    }
    return result;
  }
  DataType operator>(DataType x) {
    DataType result;
    result.dtype = FlatBType::Bool;
    switch (dtype) {
    case FlatBType::Int:
      result.T.i = T.i > x.T.i;
      break;
    default:
      break;
    }
    return result;
  }

  DataType operator<=(DataType x) {
    DataType result;
    result.dtype = FlatBType::Bool;
    switch (dtype) {
    case FlatBType::Int:
      result.T.i = T.i <= x.T.i;
      break;
    default:
      break;
    }
    return result;
  }

  DataType operator>=(DataType x) {
    DataType result;
    result.dtype = FlatBType::Bool;
    switch (dtype) {
    case FlatBType::Int:
      result.T.i = T.i >= x.T.i;
      break;
    default:
      break;
    }
    return result;
  }

  DataType operator==(DataType x) {
    DataType result;
    result.dtype = FlatBType::Bool;
    switch (dtype) {
    case FlatBType::Int:
      result.T.i = T.i == x.T.i;
      break;
    default:
      break;
    }
    return result;
  }
};

#endif
