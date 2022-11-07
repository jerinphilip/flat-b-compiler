#ifndef DTYPE_H
#define DTYPE_H
#include "ast.h"

struct dataType {
  type dtype;
  union {
    int *A;
    int i;
    bool b;
    int *p;
    char *s;
  } T;

  dataType operator+(dataType x) {
    dataType result;
    result.dtype = dtype;
    switch (dtype) {
    case type::Int:
      result.T.i = T.i + x.T.i;
      break;
    default:
      break;
    }
    return result;
  }

  dataType operator-(dataType x) {
    dataType result;
    result.dtype = dtype;
    switch (dtype) {
    case type::Int:
      result.T.i = T.i - x.T.i;
      break;
    default:
      break;
    }
    return result;
  }

  dataType operator*(dataType x) {
    dataType result;
    result.dtype = dtype;
    switch (dtype) {
    case type::Int:
      result.T.i = T.i * x.T.i;
      break;
    default:
      break;
    }
    return result;
  }

  dataType operator/(dataType x) {
    dataType result;
    result.dtype = dtype;
    switch (dtype) {
    case type::Int:
      result.T.i = T.i / x.T.i;
      break;
    default:
      break;
    }
    return result;
  }

  dataType operator<(dataType x) {
    dataType result;
    result.dtype = type::Bool;
    switch (dtype) {
    case type::Int:
      result.T.i = T.i < x.T.i;
      break;
    default:
      break;
    }
    return result;
  }
  dataType operator>(dataType x) {
    dataType result;
    result.dtype = type::Bool;
    switch (dtype) {
    case type::Int:
      result.T.i = T.i > x.T.i;
      break;
    default:
      break;
    }
    return result;
  }

  dataType operator<=(dataType x) {
    dataType result;
    result.dtype = type::Bool;
    switch (dtype) {
    case type::Int:
      result.T.i = T.i <= x.T.i;
      break;
    default:
      break;
    }
    return result;
  }

  dataType operator>=(dataType x) {
    dataType result;
    result.dtype = type::Bool;
    switch (dtype) {
    case type::Int:
      result.T.i = T.i >= x.T.i;
      break;
    default:
      break;
    }
    return result;
  }

  dataType operator==(dataType x) {
    dataType result;
    result.dtype = type::Bool;
    switch (dtype) {
    case type::Int:
      result.T.i = T.i == x.T.i;
      break;
    default:
      break;
    }
    return result;
  }
};

#endif
