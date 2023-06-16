#pragma once

enum class FlatBType {
  Int,
  Bool,
  Char,
  CharArray,
  IntArray,
  Pointer,
};

struct FlatBValue {
  FlatBType type;
  union {
    int *IntArray;
    int Int;
    bool Bool;
    int *Pointer;
    char *CharArray;
  } underlying;

  FlatBValue operator+(FlatBValue x) {
    FlatBValue result;
    result.type = type;
    switch (type) {
      case FlatBType::Int:
        result.underlying.Int = underlying.Int + x.underlying.Int;
        break;
      default:
        break;
    }
    return result;
  }

  FlatBValue operator-(FlatBValue x) {
    FlatBValue result;
    result.type = type;
    switch (type) {
      case FlatBType::Int:
        result.underlying.Int = underlying.Int - x.underlying.Int;
        break;
      default:
        break;
    }
    return result;
  }

  FlatBValue operator*(FlatBValue x) {
    FlatBValue result;
    result.type = type;
    switch (type) {
      case FlatBType::Int:
        result.underlying.Int = underlying.Int * x.underlying.Int;
        break;
      default:
        break;
    }
    return result;
  }

  FlatBValue operator/(FlatBValue x) {
    FlatBValue result;
    result.type = type;
    switch (type) {
      case FlatBType::Int:
        result.underlying.Int = underlying.Int / x.underlying.Int;
        break;
      default:
        break;
    }
    return result;
  }

  FlatBValue operator<(FlatBValue x) {
    FlatBValue result;
    result.type = FlatBType::Bool;
    switch (type) {
      case FlatBType::Int:
        result.underlying.Int = underlying.Int < x.underlying.Int;
        break;
      default:
        break;
    }
    return result;
  }

  FlatBValue operator>(FlatBValue x) {
    FlatBValue result;
    result.type = FlatBType::Bool;
    switch (type) {
      case FlatBType::Int:
        result.underlying.Int = underlying.Int > x.underlying.Int;
        break;
      default:
        break;
    }
    return result;
  }

  FlatBValue operator<=(FlatBValue x) {
    FlatBValue result;
    result.type = FlatBType::Bool;
    switch (type) {
      case FlatBType::Int:
        result.underlying.Int = underlying.Int <= x.underlying.Int;
        break;
      default:
        break;
    }
    return result;
  }

  FlatBValue operator>=(FlatBValue x) {
    FlatBValue result;
    result.type = FlatBType::Bool;
    switch (type) {
      case FlatBType::Int:
        result.underlying.Int = underlying.Int >= x.underlying.Int;
        break;
      default:
        break;
    }
    return result;
  }

  FlatBValue operator==(FlatBValue x) {
    FlatBValue result;
    result.type = FlatBType::Bool;
    switch (type) {
      case FlatBType::Int:
        result.underlying.Int = underlying.Int == x.underlying.Int;
        break;
      default:
        break;
    }
    return result;
  }
};
