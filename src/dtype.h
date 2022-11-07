#ifndef DTYPE_H
#define DTYPE_H
#include "ast.h"

struct DataType {
  Type dtype;
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
    case Type::Int:
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
    case Type::Int:
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
    case Type::Int:
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
    case Type::Int:
      result.T.i = T.i / x.T.i;
      break;
    default:
      break;
    }
    return result;
  }

  DataType operator<(DataType x) {
    DataType result;
    result.dtype = Type::Bool;
    switch (dtype) {
    case Type::Int:
      result.T.i = T.i < x.T.i;
      break;
    default:
      break;
    }
    return result;
  }
  DataType operator>(DataType x) {
    DataType result;
    result.dtype = Type::Bool;
    switch (dtype) {
    case Type::Int:
      result.T.i = T.i > x.T.i;
      break;
    default:
      break;
    }
    return result;
  }

  DataType operator<=(DataType x) {
    DataType result;
    result.dtype = Type::Bool;
    switch (dtype) {
    case Type::Int:
      result.T.i = T.i <= x.T.i;
      break;
    default:
      break;
    }
    return result;
  }

  DataType operator>=(DataType x) {
    DataType result;
    result.dtype = Type::Bool;
    switch (dtype) {
    case Type::Int:
      result.T.i = T.i >= x.T.i;
      break;
    default:
      break;
    }
    return result;
  }

  DataType operator==(DataType x) {
    DataType result;
    result.dtype = Type::Bool;
    switch (dtype) {
    case Type::Int:
      result.T.i = T.i == x.T.i;
      break;
    default:
      break;
    }
    return result;
  }
};

#endif
