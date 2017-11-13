; ModuleID = 'main'
source_filename = "main"
target triple = "x86_64-pc-linux-gnu"

@b = common global i64 0
@a = common global i64 0
@n = common global i64 0
@t = common global i64 0
@literal = internal constant [7 x i8] c"%d %d\0A\00"

define void @main() {
main_fn:
  store i64 12, i64* @n
  store i64 0, i64* @a
  store i64 1, i64* @b
  br label %pre

pre:                                              ; preds = %body, %main_fn
  %vr = load i64, i64* @n
  %vr1 = icmp sgt i64 %vr, 0
  %zext = zext i1 %vr1 to i64
  %vr2 = icmp ne i64 %zext, 0
  br i1 %vr2, label %body, label %post

body:                                             ; preds = %pre
  %vr3 = load i64, i64* @a
  store i64 %vr3, i64* @t
  %vr4 = load i64, i64* @b
  store i64 %vr4, i64* @a
  %vr5 = load i64, i64* @b
  %vr6 = load i64, i64* @t
  %vr7 = add i64 %vr5, %vr6
  store i64 %vr7, i64* @b
  %vr8 = load i64, i64* @a
  %vr9 = load i64, i64* @b
  %printf = call i64 (...) @printf([7 x i8]* @literal, i64 %vr8, i64 %vr9)
  %vr10 = load i64, i64* @n
  %vr11 = sub i64 %vr10, 1
  store i64 %vr11, i64* @n
  br label %pre

post:                                             ; preds = %pre
  ret void
}

declare i64 @printf(...)

declare i64 @scanf(...)
