; ModuleID = 'main'
source_filename = "main"
target triple = "x86_64-pc-linux-gnu"

@A = common global [100 x i64] zeroinitializer
@t = common global i64 0
@j = common global i64 0
@i = common global i64 0
@n = common global i64 0
@literal = internal constant [4 x i8] c"%d\0A\00"
@literal.1 = internal constant [2 x i8] c"=\00"
@literal.2 = internal constant [15 x i8] c"%d %d %s %d %d\00"
@literal.3 = internal constant [10 x i8] c" Swapping\00"
@literal.4 = internal constant [3 x i8] c"%s\00"
@literal.5 = internal constant [1 x i8] zeroinitializer
@literal.6 = internal constant [4 x i8] c"%s\0A\00"
@literal.7 = internal constant [4 x i8] c"%d\0A\00"

define void @main() {
main_fn:
  %vr = sub i64 100, 1
  store i64 %vr, i64* @n
  store i64 0, i64* @j
  br label %for_pre

for_pre:                                          ; preds = %for_body, %main_fn
  %vr1 = load i64, i64* @j
  %vr2 = load i64, i64* @n
  %vr3 = icmp sle i64 %vr1, %vr2
  %zext = zext i1 %vr3 to i64
  %vr4 = icmp ne i64 %zext, 0
  br i1 %vr4, label %for_body, label %for_post

for_body:                                         ; preds = %for_pre
  %vr5 = load i64, i64* @j
  %vr6 = sub i64 100, %vr5
  %vr7 = load i64, i64* @j
  %vr8 = getelementptr inbounds [100 x i64], [100 x i64]* @A, i64 0, i64 %vr7
  store i64 %vr6, i64* %vr8
  %vr9 = load i64, i64* @j
  %vr10 = getelementptr inbounds [100 x i64], [100 x i64]* @A, i64 0, i64 %vr9
  %vr11 = load i64, i64* %vr10
  %printf = call i64 (...) @printf([4 x i8]* @literal, i64 %vr11)
  %vr12 = load i64, i64* @j
  %vr13 = add i64 %vr12, 1
  store i64 %vr13, i64* @j
  br label %for_pre

for_post:                                         ; preds = %for_pre
  store i64 0, i64* @i
  br label %for_pre14

for_pre14:                                        ; preds = %for_post24, %for_post
  %vr17 = load i64, i64* @i
  %vr18 = load i64, i64* @n
  %vr19 = icmp sle i64 %vr17, %vr18
  %zext20 = zext i1 %vr19 to i64
  %vr21 = icmp ne i64 %zext20, 0
  br i1 %vr21, label %for_body15, label %for_post16

for_body15:                                       ; preds = %for_pre14
  %vr25 = load i64, i64* @i
  store i64 %vr25, i64* @j
  br label %for_pre22

for_post16:                                       ; preds = %for_pre14
  store i64 0, i64* @j
  br label %for_pre66

for_pre22:                                        ; preds = %merge_block, %for_body15
  %vr26 = load i64, i64* @j
  %vr27 = load i64, i64* @n
  %vr28 = icmp sle i64 %vr26, %vr27
  %zext29 = zext i1 %vr28 to i64
  %vr30 = icmp ne i64 %zext29, 0
  br i1 %vr30, label %for_body23, label %for_post24

for_body23:                                       ; preds = %for_pre22
  %vr31 = load i64, i64* @i
  %vr32 = load i64, i64* @j
  %vr33 = load i64, i64* @i
  %vr34 = getelementptr inbounds [100 x i64], [100 x i64]* @A, i64 0, i64 %vr33
  %vr35 = load i64, i64* %vr34
  %vr36 = load i64, i64* @j
  %vr37 = getelementptr inbounds [100 x i64], [100 x i64]* @A, i64 0, i64 %vr36
  %vr38 = load i64, i64* %vr37
  %printf39 = call i64 (...) @printf([15 x i8]* @literal.2, i64 %vr31, i64 %vr32, [2 x i8]* @literal.1, i64 %vr35, i64 %vr38)
  %vr40 = load i64, i64* @j
  %vr41 = getelementptr inbounds [100 x i64], [100 x i64]* @A, i64 0, i64 %vr40
  %vr42 = load i64, i64* %vr41
  %vr43 = load i64, i64* @i
  %vr44 = getelementptr inbounds [100 x i64], [100 x i64]* @A, i64 0, i64 %vr43
  %vr45 = load i64, i64* %vr44
  %vr46 = icmp slt i64 %vr42, %vr45
  %zext47 = zext i1 %vr46 to i64
  %vr48 = icmp ne i64 %zext47, 0
  br i1 %vr48, label %if_block, label %merge_block

for_post24:                                       ; preds = %for_pre22
  %vr64 = load i64, i64* @i
  %vr65 = add i64 %vr64, 1
  store i64 %vr65, i64* @i
  br label %for_pre14

if_block:                                         ; preds = %for_body23
  %vr49 = load i64, i64* @j
  %vr50 = getelementptr inbounds [100 x i64], [100 x i64]* @A, i64 0, i64 %vr49
  %vr51 = load i64, i64* %vr50
  store i64 %vr51, i64* @t
  %vr52 = load i64, i64* @i
  %vr53 = getelementptr inbounds [100 x i64], [100 x i64]* @A, i64 0, i64 %vr52
  %vr54 = load i64, i64* %vr53
  %vr55 = load i64, i64* @j
  %vr56 = getelementptr inbounds [100 x i64], [100 x i64]* @A, i64 0, i64 %vr55
  store i64 %vr54, i64* %vr56
  %vr57 = load i64, i64* @t
  %vr58 = load i64, i64* @i
  %vr59 = getelementptr inbounds [100 x i64], [100 x i64]* @A, i64 0, i64 %vr58
  store i64 %vr57, i64* %vr59
  %printf60 = call i64 (...) @printf([3 x i8]* @literal.4, [10 x i8]* @literal.3)
  br label %merge_block

merge_block:                                      ; preds = %for_body23, %if_block
  %printf61 = call i64 (...) @printf([4 x i8]* @literal.6, [1 x i8]* @literal.5)
  %vr62 = load i64, i64* @j
  %vr63 = add i64 %vr62, 1
  store i64 %vr63, i64* @j
  br label %for_pre22

for_pre66:                                        ; preds = %for_body67, %for_post16
  %vr69 = load i64, i64* @j
  %vr70 = load i64, i64* @n
  %vr71 = icmp sle i64 %vr69, %vr70
  %zext72 = zext i1 %vr71 to i64
  %vr73 = icmp ne i64 %zext72, 0
  br i1 %vr73, label %for_body67, label %for_post68

for_body67:                                       ; preds = %for_pre66
  %vr74 = load i64, i64* @j
  %vr75 = getelementptr inbounds [100 x i64], [100 x i64]* @A, i64 0, i64 %vr74
  %vr76 = load i64, i64* %vr75
  %printf77 = call i64 (...) @printf([4 x i8]* @literal.7, i64 %vr76)
  %vr78 = load i64, i64* @j
  %vr79 = add i64 %vr78, 1
  store i64 %vr79, i64* @j
  br label %for_pre66

for_post68:                                       ; preds = %for_pre66
  ret void
}

declare i64 @printf(...)

declare i64 @scanf(...)
