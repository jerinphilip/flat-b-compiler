; ModuleID = 'main'
source_filename = "main"
target triple = "x86_64-pc-linux-gnu"

@A = common global [100 x i64] zeroinitializer
@mid = common global i64 0
@n = common global i64 0
@j = common global i64 0
@i = common global i64 0
@t = common global i64 0
@literal = internal constant [1 x i8] zeroinitializer
@literal.1 = internal constant [6 x i8] c"%d %s\00"
@literal.2 = internal constant [1 x i8] zeroinitializer
@literal.3 = internal constant [4 x i8] c"%s\0A\00"
@literal.4 = internal constant [9 x i8] c"Swapping\00"
@literal.5 = internal constant [10 x i8] c"%s %d %d\0A\00"
@literal.6 = internal constant [1 x i8] zeroinitializer
@literal.7 = internal constant [6 x i8] c"%d %s\00"
@literal.8 = internal constant [1 x i8] zeroinitializer
@literal.9 = internal constant [4 x i8] c"%s\0A\00"

define void @main() {
main_fn:
  store i64 100, i64* @n
  store i64 0, i64* @i
  br label %for_pre

for_pre:                                          ; preds = %for_body, %main_fn
  %vr = load i64, i64* @i
  %vr1 = load i64, i64* @n
  %vr2 = sub i64 %vr1, 1
  %vr3 = icmp sle i64 %vr, %vr2
  %zext = zext i1 %vr3 to i64
  %vr4 = icmp ne i64 %zext, 0
  br i1 %vr4, label %for_body, label %for_post

for_body:                                         ; preds = %for_pre
  %vr5 = load i64, i64* @i
  %vr6 = load i64, i64* @i
  %vr7 = getelementptr inbounds [100 x i64], [100 x i64]* @A, i64 0, i64 %vr6
  store i64 %vr5, i64* %vr7
  %vr8 = load i64, i64* @i
  %vr9 = add i64 %vr8, 1
  store i64 %vr9, i64* @i
  br label %for_pre

for_post:                                         ; preds = %for_pre
  store i64 0, i64* @i
  br label %for_pre10

for_pre10:                                        ; preds = %for_body11, %for_post
  %vr13 = load i64, i64* @i
  %vr14 = load i64, i64* @n
  %vr15 = sub i64 %vr14, 1
  %vr16 = icmp sle i64 %vr13, %vr15
  %zext17 = zext i1 %vr16 to i64
  %vr18 = icmp ne i64 %zext17, 0
  br i1 %vr18, label %for_body11, label %for_post12

for_body11:                                       ; preds = %for_pre10
  %vr19 = load i64, i64* @i
  %vr20 = getelementptr inbounds [100 x i64], [100 x i64]* @A, i64 0, i64 %vr19
  %vr21 = load i64, i64* %vr20
  %printf = call i64 (...) @printf([6 x i8]* @literal.1, i64 %vr21, [1 x i8]* @literal)
  %vr22 = load i64, i64* @i
  %vr23 = add i64 %vr22, 1
  store i64 %vr23, i64* @i
  br label %for_pre10

for_post12:                                       ; preds = %for_pre10
  %printf24 = call i64 (...) @printf([4 x i8]* @literal.3, [1 x i8]* @literal.2)
  %vr25 = load i64, i64* @n
  %vr26 = sdiv i64 %vr25, 2
  store i64 %vr26, i64* @mid
  store i64 0, i64* @i
  br label %for_pre27

for_pre27:                                        ; preds = %for_body28, %for_post12
  %vr30 = load i64, i64* @i
  %vr31 = load i64, i64* @mid
  %vr32 = sub i64 %vr31, 1
  %vr33 = icmp sle i64 %vr30, %vr32
  %zext34 = zext i1 %vr33 to i64
  %vr35 = icmp ne i64 %zext34, 0
  br i1 %vr35, label %for_body28, label %for_post29

for_body28:                                       ; preds = %for_pre27
  %vr36 = load i64, i64* @n
  %vr37 = sub i64 %vr36, 1
  %vr38 = load i64, i64* @i
  %vr39 = sub i64 %vr37, %vr38
  store i64 %vr39, i64* @j
  %vr40 = load i64, i64* @i
  %vr41 = load i64, i64* @j
  %printf42 = call i64 (...) @printf([10 x i8]* @literal.5, [9 x i8]* @literal.4, i64 %vr40, i64 %vr41)
  %vr43 = load i64, i64* @i
  %vr44 = getelementptr inbounds [100 x i64], [100 x i64]* @A, i64 0, i64 %vr43
  %vr45 = load i64, i64* %vr44
  store i64 %vr45, i64* @t
  %vr46 = load i64, i64* @j
  %vr47 = getelementptr inbounds [100 x i64], [100 x i64]* @A, i64 0, i64 %vr46
  %vr48 = load i64, i64* %vr47
  %vr49 = load i64, i64* @i
  %vr50 = getelementptr inbounds [100 x i64], [100 x i64]* @A, i64 0, i64 %vr49
  store i64 %vr48, i64* %vr50
  %vr51 = load i64, i64* @t
  %vr52 = load i64, i64* @j
  %vr53 = getelementptr inbounds [100 x i64], [100 x i64]* @A, i64 0, i64 %vr52
  store i64 %vr51, i64* %vr53
  %vr54 = load i64, i64* @i
  %vr55 = add i64 %vr54, 1
  store i64 %vr55, i64* @i
  br label %for_pre27

for_post29:                                       ; preds = %for_pre27
  store i64 0, i64* @i
  br label %for_pre56

for_pre56:                                        ; preds = %for_body57, %for_post29
  %vr59 = load i64, i64* @i
  %vr60 = load i64, i64* @n
  %vr61 = sub i64 %vr60, 1
  %vr62 = icmp sle i64 %vr59, %vr61
  %zext63 = zext i1 %vr62 to i64
  %vr64 = icmp ne i64 %zext63, 0
  br i1 %vr64, label %for_body57, label %for_post58

for_body57:                                       ; preds = %for_pre56
  %vr65 = load i64, i64* @i
  %vr66 = getelementptr inbounds [100 x i64], [100 x i64]* @A, i64 0, i64 %vr65
  %vr67 = load i64, i64* %vr66
  %printf68 = call i64 (...) @printf([6 x i8]* @literal.7, i64 %vr67, [1 x i8]* @literal.6)
  %vr69 = load i64, i64* @i
  %vr70 = add i64 %vr69, 1
  store i64 %vr70, i64* @i
  br label %for_pre56

for_post58:                                       ; preds = %for_pre56
  %printf71 = call i64 (...) @printf([4 x i8]* @literal.9, [1 x i8]* @literal.8)
  ret void
}

declare i64 @printf(...)

declare i64 @scanf(...)
