; ModuleID = 'main'
source_filename = "main"
target triple = "x86_64-pc-linux-gnu"

@i = common global i64 0
@literal = internal constant [29 x i8] c"bottles of beer on the wall!\00"
@literal.1 = internal constant [7 x i8] c"%d %s\0A\00"
@literal.2 = internal constant [31 x i8] c"Take one down, pass it around!\00"
@literal.3 = internal constant [4 x i8] c"%s\0A\00"
@literal.4 = internal constant [29 x i8] c"bottles of beer on the wall!\00"
@literal.5 = internal constant [7 x i8] c"%d %s\0A\00"
@literal.6 = internal constant [31 x i8] c"Take one down, pass it around!\00"
@literal.7 = internal constant [4 x i8] c"%s\0A\00"
@literal.8 = internal constant [37 x i8] c"No more bottles of beer on the wall!\00"
@literal.9 = internal constant [4 x i8] c"%s\0A\00"

define void @main() {
main_fn:
  store i64 100, i64* @i
  br label %pre

pre:                                              ; preds = %body, %main_fn
  %vr = load i64, i64* @i
  %vr1 = icmp sgt i64 %vr, 2
  %zext = zext i1 %vr1 to i64
  %vr2 = icmp ne i64 %zext, 0
  br i1 %vr2, label %body, label %post

body:                                             ; preds = %pre
  %vr3 = load i64, i64* @i
  %vr4 = sub i64 %vr3, 1
  store i64 %vr4, i64* @i
  %vr5 = load i64, i64* @i
  %printf = call i64 (...) @printf([7 x i8]* @literal.1, i64 %vr5, [29 x i8]* @literal)
  %printf6 = call i64 (...) @printf([4 x i8]* @literal.3, [31 x i8]* @literal.2)
  br label %pre

post:                                             ; preds = %pre
  %vr7 = load i64, i64* @i
  %vr8 = sub i64 %vr7, 1
  store i64 %vr8, i64* @i
  %vr9 = load i64, i64* @i
  %printf10 = call i64 (...) @printf([7 x i8]* @literal.5, i64 %vr9, [29 x i8]* @literal.4)
  %printf11 = call i64 (...) @printf([4 x i8]* @literal.7, [31 x i8]* @literal.6)
  %printf12 = call i64 (...) @printf([4 x i8]* @literal.9, [37 x i8]* @literal.8)
  ret void
}

declare i64 @printf(...)

declare i64 @scanf(...)
