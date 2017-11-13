; ModuleID = 'main'
source_filename = "main"
target triple = "x86_64-pc-linux-gnu"

@C = common global [2500 x i64] zeroinitializer
@B = common global [2500 x i64] zeroinitializer
@A = common global [2500 x i64] zeroinitializer
@n = common global i64 0
@k = common global i64 0
@j = common global i64 0
@i = common global i64 0
@c = common global i64 0
@b = common global i64 0
@a = common global i64 0
@literal = internal constant [3 x i8] c"A:\00"
@literal.1 = internal constant [4 x i8] c"%s\0A\00"
@literal.2 = internal constant [2 x i8] c" \00"
@literal.3 = internal constant [6 x i8] c"%d %s\00"
@literal.4 = internal constant [1 x i8] zeroinitializer
@literal.5 = internal constant [4 x i8] c"%s\0A\00"
@literal.6 = internal constant [4 x i8] c"---\00"
@literal.7 = internal constant [4 x i8] c"%s\0A\00"
@literal.8 = internal constant [3 x i8] c"B:\00"
@literal.9 = internal constant [4 x i8] c"%s\0A\00"
@literal.10 = internal constant [2 x i8] c" \00"
@literal.11 = internal constant [6 x i8] c"%d %s\00"
@literal.12 = internal constant [1 x i8] zeroinitializer
@literal.13 = internal constant [4 x i8] c"%s\0A\00"
@literal.14 = internal constant [4 x i8] c"---\00"
@literal.15 = internal constant [4 x i8] c"%s\0A\00"
@literal.16 = internal constant [8 x i8] c"AB = C:\00"
@literal.17 = internal constant [4 x i8] c"%s\0A\00"
@literal.18 = internal constant [2 x i8] c" \00"
@literal.19 = internal constant [6 x i8] c"%d %s\00"
@literal.20 = internal constant [1 x i8] zeroinitializer
@literal.21 = internal constant [4 x i8] c"%s\0A\00"
@literal.22 = internal constant [4 x i8] c"---\00"
@literal.23 = internal constant [4 x i8] c"%s\0A\00"

define void @main() {
main_fn:
  store i64 5, i64* @n
  store i64 0, i64* @i
  br label %for_pre

for_pre:                                          ; preds = %for_post6, %main_fn
  %vr = load i64, i64* @i
  %vr1 = load i64, i64* @n
  %vr2 = icmp sle i64 %vr, %vr1
  %zext = zext i1 %vr2 to i64
  %vr3 = icmp ne i64 %zext, 0
  br i1 %vr3, label %for_body, label %for_post

for_body:                                         ; preds = %for_pre
  store i64 0, i64* @j
  br label %for_pre4

for_post:                                         ; preds = %for_pre
  store i64 0, i64* @i
  br label %for_pre35

for_pre4:                                         ; preds = %merge_block, %for_body
  %vr7 = load i64, i64* @j
  %vr8 = load i64, i64* @n
  %vr9 = icmp sle i64 %vr7, %vr8
  %zext10 = zext i1 %vr9 to i64
  %vr11 = icmp ne i64 %zext10, 0
  br i1 %vr11, label %for_body5, label %for_post6

for_body5:                                        ; preds = %for_pre4
  %vr12 = load i64, i64* @i
  %vr13 = load i64, i64* @j
  %vr14 = icmp eq i64 %vr12, %vr13
  %zext15 = zext i1 %vr14 to i64
  %vr16 = icmp ne i64 %zext15, 0
  br i1 %vr16, label %if_block, label %else_block

for_post6:                                        ; preds = %for_pre4
  %vr33 = load i64, i64* @i
  %vr34 = add i64 %vr33, 1
  store i64 %vr34, i64* @i
  br label %for_pre

if_block:                                         ; preds = %for_body5
  %vr17 = load i64, i64* @i
  %vr18 = load i64, i64* @n
  %vr19 = mul i64 %vr17, %vr18
  %vr20 = load i64, i64* @j
  %vr21 = add i64 %vr19, %vr20
  store i64 %vr21, i64* @a
  %vr22 = load i64, i64* @a
  %vr23 = getelementptr inbounds [2500 x i64], [2500 x i64]* @A, i64 0, i64 %vr22
  store i64 1, i64* %vr23
  br label %merge_block

merge_block:                                      ; preds = %else_block, %if_block
  %vr31 = load i64, i64* @j
  %vr32 = add i64 %vr31, 1
  store i64 %vr32, i64* @j
  br label %for_pre4

else_block:                                       ; preds = %for_body5
  %vr24 = load i64, i64* @i
  %vr25 = load i64, i64* @n
  %vr26 = mul i64 %vr24, %vr25
  %vr27 = load i64, i64* @j
  %vr28 = add i64 %vr26, %vr27
  store i64 %vr28, i64* @a
  %vr29 = load i64, i64* @a
  %vr30 = getelementptr inbounds [2500 x i64], [2500 x i64]* @A, i64 0, i64 %vr29
  store i64 0, i64* %vr30
  br label %merge_block

for_pre35:                                        ; preds = %for_post45, %for_post
  %vr38 = load i64, i64* @i
  %vr39 = load i64, i64* @n
  %vr40 = icmp sle i64 %vr38, %vr39
  %zext41 = zext i1 %vr40 to i64
  %vr42 = icmp ne i64 %zext41, 0
  br i1 %vr42, label %for_body36, label %for_post37

for_body36:                                       ; preds = %for_pre35
  store i64 0, i64* @j
  br label %for_pre43

for_post37:                                       ; preds = %for_pre35
  store i64 0, i64* @i
  br label %for_pre77

for_pre43:                                        ; preds = %merge_block57, %for_body36
  %vr46 = load i64, i64* @j
  %vr47 = load i64, i64* @n
  %vr48 = icmp sle i64 %vr46, %vr47
  %zext49 = zext i1 %vr48 to i64
  %vr50 = icmp ne i64 %zext49, 0
  br i1 %vr50, label %for_body44, label %for_post45

for_body44:                                       ; preds = %for_pre43
  %vr51 = load i64, i64* @i
  %vr52 = load i64, i64* @j
  %vr53 = icmp eq i64 %vr51, %vr52
  %zext54 = zext i1 %vr53 to i64
  %vr55 = icmp ne i64 %zext54, 0
  br i1 %vr55, label %if_block56, label %else_block65

for_post45:                                       ; preds = %for_pre43
  %vr75 = load i64, i64* @i
  %vr76 = add i64 %vr75, 1
  store i64 %vr76, i64* @i
  br label %for_pre35

if_block56:                                       ; preds = %for_body44
  %vr58 = load i64, i64* @i
  %vr59 = load i64, i64* @n
  %vr60 = mul i64 %vr58, %vr59
  %vr61 = load i64, i64* @j
  %vr62 = add i64 %vr60, %vr61
  store i64 %vr62, i64* @a
  %vr63 = load i64, i64* @a
  %vr64 = getelementptr inbounds [2500 x i64], [2500 x i64]* @B, i64 0, i64 %vr63
  store i64 1, i64* %vr64
  br label %merge_block57

merge_block57:                                    ; preds = %else_block65, %if_block56
  %vr73 = load i64, i64* @j
  %vr74 = add i64 %vr73, 1
  store i64 %vr74, i64* @j
  br label %for_pre43

else_block65:                                     ; preds = %for_body44
  %vr66 = load i64, i64* @i
  %vr67 = load i64, i64* @n
  %vr68 = mul i64 %vr66, %vr67
  %vr69 = load i64, i64* @j
  %vr70 = add i64 %vr68, %vr69
  store i64 %vr70, i64* @a
  %vr71 = load i64, i64* @a
  %vr72 = getelementptr inbounds [2500 x i64], [2500 x i64]* @B, i64 0, i64 %vr71
  store i64 0, i64* %vr72
  br label %merge_block57

for_pre77:                                        ; preds = %for_post87, %for_post37
  %vr80 = load i64, i64* @i
  %vr81 = load i64, i64* @n
  %vr82 = icmp sle i64 %vr80, %vr81
  %zext83 = zext i1 %vr82 to i64
  %vr84 = icmp ne i64 %zext83, 0
  br i1 %vr84, label %for_body78, label %for_post79

for_body78:                                       ; preds = %for_pre77
  store i64 0, i64* @j
  br label %for_pre85

for_post79:                                       ; preds = %for_pre77
  %printf = call i64 (...) @printf([4 x i8]* @literal.1, [3 x i8]* @literal)
  store i64 0, i64* @i
  br label %for_pre135

for_pre85:                                        ; preds = %for_post95, %for_body78
  %vr88 = load i64, i64* @j
  %vr89 = load i64, i64* @n
  %vr90 = icmp sle i64 %vr88, %vr89
  %zext91 = zext i1 %vr90 to i64
  %vr92 = icmp ne i64 %zext91, 0
  br i1 %vr92, label %for_body86, label %for_post87

for_body86:                                       ; preds = %for_pre85
  store i64 0, i64* @k
  br label %for_pre93

for_post87:                                       ; preds = %for_pre85
  %vr133 = load i64, i64* @i
  %vr134 = add i64 %vr133, 1
  store i64 %vr134, i64* @i
  br label %for_pre77

for_pre93:                                        ; preds = %for_body94, %for_body86
  %vr96 = load i64, i64* @k
  %vr97 = load i64, i64* @n
  %vr98 = icmp sle i64 %vr96, %vr97
  %zext99 = zext i1 %vr98 to i64
  %vr100 = icmp ne i64 %zext99, 0
  br i1 %vr100, label %for_body94, label %for_post95

for_body94:                                       ; preds = %for_pre93
  %vr101 = load i64, i64* @i
  %vr102 = load i64, i64* @n
  %vr103 = mul i64 %vr101, %vr102
  %vr104 = load i64, i64* @k
  %vr105 = add i64 %vr103, %vr104
  store i64 %vr105, i64* @a
  %vr106 = load i64, i64* @k
  %vr107 = load i64, i64* @n
  %vr108 = mul i64 %vr106, %vr107
  %vr109 = load i64, i64* @j
  %vr110 = add i64 %vr108, %vr109
  store i64 %vr110, i64* @b
  %vr111 = load i64, i64* @i
  %vr112 = load i64, i64* @n
  %vr113 = mul i64 %vr111, %vr112
  %vr114 = load i64, i64* @j
  %vr115 = add i64 %vr113, %vr114
  store i64 %vr115, i64* @c
  %vr116 = load i64, i64* @c
  %vr117 = getelementptr inbounds [2500 x i64], [2500 x i64]* @C, i64 0, i64 %vr116
  %vr118 = load i64, i64* %vr117
  %vr119 = load i64, i64* @a
  %vr120 = getelementptr inbounds [2500 x i64], [2500 x i64]* @A, i64 0, i64 %vr119
  %vr121 = load i64, i64* %vr120
  %vr122 = load i64, i64* @b
  %vr123 = getelementptr inbounds [2500 x i64], [2500 x i64]* @B, i64 0, i64 %vr122
  %vr124 = load i64, i64* %vr123
  %vr125 = mul i64 %vr121, %vr124
  %vr126 = add i64 %vr118, %vr125
  %vr127 = load i64, i64* @c
  %vr128 = getelementptr inbounds [2500 x i64], [2500 x i64]* @C, i64 0, i64 %vr127
  store i64 %vr126, i64* %vr128
  %vr129 = load i64, i64* @k
  %vr130 = add i64 %vr129, 1
  store i64 %vr130, i64* @k
  br label %for_pre93

for_post95:                                       ; preds = %for_pre93
  %vr131 = load i64, i64* @j
  %vr132 = add i64 %vr131, 1
  store i64 %vr132, i64* @j
  br label %for_pre85

for_pre135:                                       ; preds = %for_post145, %for_post79
  %vr138 = load i64, i64* @i
  %vr139 = load i64, i64* @n
  %vr140 = icmp sle i64 %vr138, %vr139
  %zext141 = zext i1 %vr140 to i64
  %vr142 = icmp ne i64 %zext141, 0
  br i1 %vr142, label %for_body136, label %for_post137

for_body136:                                      ; preds = %for_pre135
  store i64 0, i64* @j
  br label %for_pre143

for_post137:                                      ; preds = %for_pre135
  %printf165 = call i64 (...) @printf([4 x i8]* @literal.7, [4 x i8]* @literal.6)
  %printf166 = call i64 (...) @printf([4 x i8]* @literal.9, [3 x i8]* @literal.8)
  store i64 0, i64* @i
  br label %for_pre167

for_pre143:                                       ; preds = %for_body144, %for_body136
  %vr146 = load i64, i64* @j
  %vr147 = load i64, i64* @n
  %vr148 = icmp sle i64 %vr146, %vr147
  %zext149 = zext i1 %vr148 to i64
  %vr150 = icmp ne i64 %zext149, 0
  br i1 %vr150, label %for_body144, label %for_post145

for_body144:                                      ; preds = %for_pre143
  %vr151 = load i64, i64* @i
  %vr152 = load i64, i64* @n
  %vr153 = mul i64 %vr151, %vr152
  %vr154 = load i64, i64* @j
  %vr155 = add i64 %vr153, %vr154
  store i64 %vr155, i64* @a
  %vr156 = load i64, i64* @a
  %vr157 = getelementptr inbounds [2500 x i64], [2500 x i64]* @A, i64 0, i64 %vr156
  %vr158 = load i64, i64* %vr157
  %printf159 = call i64 (...) @printf([6 x i8]* @literal.3, i64 %vr158, [2 x i8]* @literal.2)
  %vr160 = load i64, i64* @j
  %vr161 = add i64 %vr160, 1
  store i64 %vr161, i64* @j
  br label %for_pre143

for_post145:                                      ; preds = %for_pre143
  %printf162 = call i64 (...) @printf([4 x i8]* @literal.5, [1 x i8]* @literal.4)
  %vr163 = load i64, i64* @i
  %vr164 = add i64 %vr163, 1
  store i64 %vr164, i64* @i
  br label %for_pre135

for_pre167:                                       ; preds = %for_post177, %for_post137
  %vr170 = load i64, i64* @i
  %vr171 = load i64, i64* @n
  %vr172 = icmp sle i64 %vr170, %vr171
  %zext173 = zext i1 %vr172 to i64
  %vr174 = icmp ne i64 %zext173, 0
  br i1 %vr174, label %for_body168, label %for_post169

for_body168:                                      ; preds = %for_pre167
  store i64 0, i64* @j
  br label %for_pre175

for_post169:                                      ; preds = %for_pre167
  %printf197 = call i64 (...) @printf([4 x i8]* @literal.15, [4 x i8]* @literal.14)
  %printf198 = call i64 (...) @printf([4 x i8]* @literal.17, [8 x i8]* @literal.16)
  store i64 0, i64* @i
  br label %for_pre199

for_pre175:                                       ; preds = %for_body176, %for_body168
  %vr178 = load i64, i64* @j
  %vr179 = load i64, i64* @n
  %vr180 = icmp sle i64 %vr178, %vr179
  %zext181 = zext i1 %vr180 to i64
  %vr182 = icmp ne i64 %zext181, 0
  br i1 %vr182, label %for_body176, label %for_post177

for_body176:                                      ; preds = %for_pre175
  %vr183 = load i64, i64* @i
  %vr184 = load i64, i64* @n
  %vr185 = mul i64 %vr183, %vr184
  %vr186 = load i64, i64* @j
  %vr187 = add i64 %vr185, %vr186
  store i64 %vr187, i64* @a
  %vr188 = load i64, i64* @a
  %vr189 = getelementptr inbounds [2500 x i64], [2500 x i64]* @B, i64 0, i64 %vr188
  %vr190 = load i64, i64* %vr189
  %printf191 = call i64 (...) @printf([6 x i8]* @literal.11, i64 %vr190, [2 x i8]* @literal.10)
  %vr192 = load i64, i64* @j
  %vr193 = add i64 %vr192, 1
  store i64 %vr193, i64* @j
  br label %for_pre175

for_post177:                                      ; preds = %for_pre175
  %printf194 = call i64 (...) @printf([4 x i8]* @literal.13, [1 x i8]* @literal.12)
  %vr195 = load i64, i64* @i
  %vr196 = add i64 %vr195, 1
  store i64 %vr196, i64* @i
  br label %for_pre167

for_pre199:                                       ; preds = %for_post209, %for_post169
  %vr202 = load i64, i64* @i
  %vr203 = load i64, i64* @n
  %vr204 = icmp sle i64 %vr202, %vr203
  %zext205 = zext i1 %vr204 to i64
  %vr206 = icmp ne i64 %zext205, 0
  br i1 %vr206, label %for_body200, label %for_post201

for_body200:                                      ; preds = %for_pre199
  store i64 0, i64* @j
  br label %for_pre207

for_post201:                                      ; preds = %for_pre199
  %printf229 = call i64 (...) @printf([4 x i8]* @literal.23, [4 x i8]* @literal.22)
  ret void

for_pre207:                                       ; preds = %for_body208, %for_body200
  %vr210 = load i64, i64* @j
  %vr211 = load i64, i64* @n
  %vr212 = icmp sle i64 %vr210, %vr211
  %zext213 = zext i1 %vr212 to i64
  %vr214 = icmp ne i64 %zext213, 0
  br i1 %vr214, label %for_body208, label %for_post209

for_body208:                                      ; preds = %for_pre207
  %vr215 = load i64, i64* @i
  %vr216 = load i64, i64* @n
  %vr217 = mul i64 %vr215, %vr216
  %vr218 = load i64, i64* @j
  %vr219 = add i64 %vr217, %vr218
  store i64 %vr219, i64* @a
  %vr220 = load i64, i64* @a
  %vr221 = getelementptr inbounds [2500 x i64], [2500 x i64]* @C, i64 0, i64 %vr220
  %vr222 = load i64, i64* %vr221
  %printf223 = call i64 (...) @printf([6 x i8]* @literal.19, i64 %vr222, [2 x i8]* @literal.18)
  %vr224 = load i64, i64* @j
  %vr225 = add i64 %vr224, 1
  store i64 %vr225, i64* @j
  br label %for_pre207

for_post209:                                      ; preds = %for_pre207
  %printf226 = call i64 (...) @printf([4 x i8]* @literal.21, [1 x i8]* @literal.20)
  %vr227 = load i64, i64* @i
  %vr228 = add i64 %vr227, 1
  store i64 %vr228, i64* @i
  br label %for_pre199
}

declare i64 @printf(...)

declare i64 @scanf(...)
