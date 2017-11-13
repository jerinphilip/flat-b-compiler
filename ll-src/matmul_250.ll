; ModuleID = 'main'
source_filename = "main"
target triple = "x86_64-pc-linux-gnu"

@C = common global [62500 x i64] zeroinitializer
@B = common global [62500 x i64] zeroinitializer
@A = common global [62500 x i64] zeroinitializer
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
  %vr = sub i64 250, 1
  store i64 %vr, i64* @n
  store i64 0, i64* @i
  br label %for_pre

for_pre:                                          ; preds = %for_post7, %main_fn
  %vr1 = load i64, i64* @i
  %vr2 = load i64, i64* @n
  %vr3 = icmp sle i64 %vr1, %vr2
  %zext = zext i1 %vr3 to i64
  %vr4 = icmp ne i64 %zext, 0
  br i1 %vr4, label %for_body, label %for_post

for_body:                                         ; preds = %for_pre
  store i64 0, i64* @j
  br label %for_pre5

for_post:                                         ; preds = %for_pre
  store i64 0, i64* @i
  br label %for_pre36

for_pre5:                                         ; preds = %merge_block, %for_body
  %vr8 = load i64, i64* @j
  %vr9 = load i64, i64* @n
  %vr10 = icmp sle i64 %vr8, %vr9
  %zext11 = zext i1 %vr10 to i64
  %vr12 = icmp ne i64 %zext11, 0
  br i1 %vr12, label %for_body6, label %for_post7

for_body6:                                        ; preds = %for_pre5
  %vr13 = load i64, i64* @i
  %vr14 = load i64, i64* @j
  %vr15 = icmp eq i64 %vr13, %vr14
  %zext16 = zext i1 %vr15 to i64
  %vr17 = icmp ne i64 %zext16, 0
  br i1 %vr17, label %if_block, label %else_block

for_post7:                                        ; preds = %for_pre5
  %vr34 = load i64, i64* @i
  %vr35 = add i64 %vr34, 1
  store i64 %vr35, i64* @i
  br label %for_pre

if_block:                                         ; preds = %for_body6
  %vr18 = load i64, i64* @i
  %vr19 = load i64, i64* @n
  %vr20 = mul i64 %vr18, %vr19
  %vr21 = load i64, i64* @j
  %vr22 = add i64 %vr20, %vr21
  store i64 %vr22, i64* @a
  %vr23 = load i64, i64* @a
  %vr24 = getelementptr inbounds [62500 x i64], [62500 x i64]* @A, i64 0, i64 %vr23
  store i64 1, i64* %vr24
  br label %merge_block

merge_block:                                      ; preds = %else_block, %if_block
  %vr32 = load i64, i64* @j
  %vr33 = add i64 %vr32, 1
  store i64 %vr33, i64* @j
  br label %for_pre5

else_block:                                       ; preds = %for_body6
  %vr25 = load i64, i64* @i
  %vr26 = load i64, i64* @n
  %vr27 = mul i64 %vr25, %vr26
  %vr28 = load i64, i64* @j
  %vr29 = add i64 %vr27, %vr28
  store i64 %vr29, i64* @a
  %vr30 = load i64, i64* @a
  %vr31 = getelementptr inbounds [62500 x i64], [62500 x i64]* @A, i64 0, i64 %vr30
  store i64 0, i64* %vr31
  br label %merge_block

for_pre36:                                        ; preds = %for_post46, %for_post
  %vr39 = load i64, i64* @i
  %vr40 = load i64, i64* @n
  %vr41 = icmp sle i64 %vr39, %vr40
  %zext42 = zext i1 %vr41 to i64
  %vr43 = icmp ne i64 %zext42, 0
  br i1 %vr43, label %for_body37, label %for_post38

for_body37:                                       ; preds = %for_pre36
  store i64 0, i64* @j
  br label %for_pre44

for_post38:                                       ; preds = %for_pre36
  store i64 0, i64* @i
  br label %for_pre78

for_pre44:                                        ; preds = %merge_block58, %for_body37
  %vr47 = load i64, i64* @j
  %vr48 = load i64, i64* @n
  %vr49 = icmp sle i64 %vr47, %vr48
  %zext50 = zext i1 %vr49 to i64
  %vr51 = icmp ne i64 %zext50, 0
  br i1 %vr51, label %for_body45, label %for_post46

for_body45:                                       ; preds = %for_pre44
  %vr52 = load i64, i64* @i
  %vr53 = load i64, i64* @j
  %vr54 = icmp eq i64 %vr52, %vr53
  %zext55 = zext i1 %vr54 to i64
  %vr56 = icmp ne i64 %zext55, 0
  br i1 %vr56, label %if_block57, label %else_block66

for_post46:                                       ; preds = %for_pre44
  %vr76 = load i64, i64* @i
  %vr77 = add i64 %vr76, 1
  store i64 %vr77, i64* @i
  br label %for_pre36

if_block57:                                       ; preds = %for_body45
  %vr59 = load i64, i64* @i
  %vr60 = load i64, i64* @n
  %vr61 = mul i64 %vr59, %vr60
  %vr62 = load i64, i64* @j
  %vr63 = add i64 %vr61, %vr62
  store i64 %vr63, i64* @a
  %vr64 = load i64, i64* @a
  %vr65 = getelementptr inbounds [62500 x i64], [62500 x i64]* @B, i64 0, i64 %vr64
  store i64 1, i64* %vr65
  br label %merge_block58

merge_block58:                                    ; preds = %else_block66, %if_block57
  %vr74 = load i64, i64* @j
  %vr75 = add i64 %vr74, 1
  store i64 %vr75, i64* @j
  br label %for_pre44

else_block66:                                     ; preds = %for_body45
  %vr67 = load i64, i64* @i
  %vr68 = load i64, i64* @n
  %vr69 = mul i64 %vr67, %vr68
  %vr70 = load i64, i64* @j
  %vr71 = add i64 %vr69, %vr70
  store i64 %vr71, i64* @a
  %vr72 = load i64, i64* @a
  %vr73 = getelementptr inbounds [62500 x i64], [62500 x i64]* @B, i64 0, i64 %vr72
  store i64 0, i64* %vr73
  br label %merge_block58

for_pre78:                                        ; preds = %for_post88, %for_post38
  %vr81 = load i64, i64* @i
  %vr82 = load i64, i64* @n
  %vr83 = icmp sle i64 %vr81, %vr82
  %zext84 = zext i1 %vr83 to i64
  %vr85 = icmp ne i64 %zext84, 0
  br i1 %vr85, label %for_body79, label %for_post80

for_body79:                                       ; preds = %for_pre78
  store i64 0, i64* @j
  br label %for_pre86

for_post80:                                       ; preds = %for_pre78
  %printf = call i64 (...) @printf([4 x i8]* @literal.1, [3 x i8]* @literal)
  store i64 0, i64* @i
  br label %for_pre136

for_pre86:                                        ; preds = %for_post96, %for_body79
  %vr89 = load i64, i64* @j
  %vr90 = load i64, i64* @n
  %vr91 = icmp sle i64 %vr89, %vr90
  %zext92 = zext i1 %vr91 to i64
  %vr93 = icmp ne i64 %zext92, 0
  br i1 %vr93, label %for_body87, label %for_post88

for_body87:                                       ; preds = %for_pre86
  store i64 0, i64* @k
  br label %for_pre94

for_post88:                                       ; preds = %for_pre86
  %vr134 = load i64, i64* @i
  %vr135 = add i64 %vr134, 1
  store i64 %vr135, i64* @i
  br label %for_pre78

for_pre94:                                        ; preds = %for_body95, %for_body87
  %vr97 = load i64, i64* @k
  %vr98 = load i64, i64* @n
  %vr99 = icmp sle i64 %vr97, %vr98
  %zext100 = zext i1 %vr99 to i64
  %vr101 = icmp ne i64 %zext100, 0
  br i1 %vr101, label %for_body95, label %for_post96

for_body95:                                       ; preds = %for_pre94
  %vr102 = load i64, i64* @i
  %vr103 = load i64, i64* @n
  %vr104 = mul i64 %vr102, %vr103
  %vr105 = load i64, i64* @k
  %vr106 = add i64 %vr104, %vr105
  store i64 %vr106, i64* @a
  %vr107 = load i64, i64* @k
  %vr108 = load i64, i64* @n
  %vr109 = mul i64 %vr107, %vr108
  %vr110 = load i64, i64* @j
  %vr111 = add i64 %vr109, %vr110
  store i64 %vr111, i64* @b
  %vr112 = load i64, i64* @i
  %vr113 = load i64, i64* @n
  %vr114 = mul i64 %vr112, %vr113
  %vr115 = load i64, i64* @j
  %vr116 = add i64 %vr114, %vr115
  store i64 %vr116, i64* @c
  %vr117 = load i64, i64* @c
  %vr118 = getelementptr inbounds [62500 x i64], [62500 x i64]* @C, i64 0, i64 %vr117
  %vr119 = load i64, i64* %vr118
  %vr120 = load i64, i64* @a
  %vr121 = getelementptr inbounds [62500 x i64], [62500 x i64]* @A, i64 0, i64 %vr120
  %vr122 = load i64, i64* %vr121
  %vr123 = load i64, i64* @b
  %vr124 = getelementptr inbounds [62500 x i64], [62500 x i64]* @B, i64 0, i64 %vr123
  %vr125 = load i64, i64* %vr124
  %vr126 = mul i64 %vr122, %vr125
  %vr127 = add i64 %vr119, %vr126
  %vr128 = load i64, i64* @c
  %vr129 = getelementptr inbounds [62500 x i64], [62500 x i64]* @C, i64 0, i64 %vr128
  store i64 %vr127, i64* %vr129
  %vr130 = load i64, i64* @k
  %vr131 = add i64 %vr130, 1
  store i64 %vr131, i64* @k
  br label %for_pre94

for_post96:                                       ; preds = %for_pre94
  %vr132 = load i64, i64* @j
  %vr133 = add i64 %vr132, 1
  store i64 %vr133, i64* @j
  br label %for_pre86

for_pre136:                                       ; preds = %for_post146, %for_post80
  %vr139 = load i64, i64* @i
  %vr140 = load i64, i64* @n
  %vr141 = icmp sle i64 %vr139, %vr140
  %zext142 = zext i1 %vr141 to i64
  %vr143 = icmp ne i64 %zext142, 0
  br i1 %vr143, label %for_body137, label %for_post138

for_body137:                                      ; preds = %for_pre136
  store i64 0, i64* @j
  br label %for_pre144

for_post138:                                      ; preds = %for_pre136
  %printf166 = call i64 (...) @printf([4 x i8]* @literal.7, [4 x i8]* @literal.6)
  %printf167 = call i64 (...) @printf([4 x i8]* @literal.9, [3 x i8]* @literal.8)
  store i64 0, i64* @i
  br label %for_pre168

for_pre144:                                       ; preds = %for_body145, %for_body137
  %vr147 = load i64, i64* @j
  %vr148 = load i64, i64* @n
  %vr149 = icmp sle i64 %vr147, %vr148
  %zext150 = zext i1 %vr149 to i64
  %vr151 = icmp ne i64 %zext150, 0
  br i1 %vr151, label %for_body145, label %for_post146

for_body145:                                      ; preds = %for_pre144
  %vr152 = load i64, i64* @i
  %vr153 = load i64, i64* @n
  %vr154 = mul i64 %vr152, %vr153
  %vr155 = load i64, i64* @j
  %vr156 = add i64 %vr154, %vr155
  store i64 %vr156, i64* @a
  %vr157 = load i64, i64* @a
  %vr158 = getelementptr inbounds [62500 x i64], [62500 x i64]* @A, i64 0, i64 %vr157
  %vr159 = load i64, i64* %vr158
  %printf160 = call i64 (...) @printf([6 x i8]* @literal.3, i64 %vr159, [2 x i8]* @literal.2)
  %vr161 = load i64, i64* @j
  %vr162 = add i64 %vr161, 1
  store i64 %vr162, i64* @j
  br label %for_pre144

for_post146:                                      ; preds = %for_pre144
  %printf163 = call i64 (...) @printf([4 x i8]* @literal.5, [1 x i8]* @literal.4)
  %vr164 = load i64, i64* @i
  %vr165 = add i64 %vr164, 1
  store i64 %vr165, i64* @i
  br label %for_pre136

for_pre168:                                       ; preds = %for_post178, %for_post138
  %vr171 = load i64, i64* @i
  %vr172 = load i64, i64* @n
  %vr173 = icmp sle i64 %vr171, %vr172
  %zext174 = zext i1 %vr173 to i64
  %vr175 = icmp ne i64 %zext174, 0
  br i1 %vr175, label %for_body169, label %for_post170

for_body169:                                      ; preds = %for_pre168
  store i64 0, i64* @j
  br label %for_pre176

for_post170:                                      ; preds = %for_pre168
  %printf198 = call i64 (...) @printf([4 x i8]* @literal.15, [4 x i8]* @literal.14)
  %printf199 = call i64 (...) @printf([4 x i8]* @literal.17, [8 x i8]* @literal.16)
  store i64 0, i64* @i
  br label %for_pre200

for_pre176:                                       ; preds = %for_body177, %for_body169
  %vr179 = load i64, i64* @j
  %vr180 = load i64, i64* @n
  %vr181 = icmp sle i64 %vr179, %vr180
  %zext182 = zext i1 %vr181 to i64
  %vr183 = icmp ne i64 %zext182, 0
  br i1 %vr183, label %for_body177, label %for_post178

for_body177:                                      ; preds = %for_pre176
  %vr184 = load i64, i64* @i
  %vr185 = load i64, i64* @n
  %vr186 = mul i64 %vr184, %vr185
  %vr187 = load i64, i64* @j
  %vr188 = add i64 %vr186, %vr187
  store i64 %vr188, i64* @a
  %vr189 = load i64, i64* @a
  %vr190 = getelementptr inbounds [62500 x i64], [62500 x i64]* @B, i64 0, i64 %vr189
  %vr191 = load i64, i64* %vr190
  %printf192 = call i64 (...) @printf([6 x i8]* @literal.11, i64 %vr191, [2 x i8]* @literal.10)
  %vr193 = load i64, i64* @j
  %vr194 = add i64 %vr193, 1
  store i64 %vr194, i64* @j
  br label %for_pre176

for_post178:                                      ; preds = %for_pre176
  %printf195 = call i64 (...) @printf([4 x i8]* @literal.13, [1 x i8]* @literal.12)
  %vr196 = load i64, i64* @i
  %vr197 = add i64 %vr196, 1
  store i64 %vr197, i64* @i
  br label %for_pre168

for_pre200:                                       ; preds = %for_post210, %for_post170
  %vr203 = load i64, i64* @i
  %vr204 = load i64, i64* @n
  %vr205 = icmp sle i64 %vr203, %vr204
  %zext206 = zext i1 %vr205 to i64
  %vr207 = icmp ne i64 %zext206, 0
  br i1 %vr207, label %for_body201, label %for_post202

for_body201:                                      ; preds = %for_pre200
  store i64 0, i64* @j
  br label %for_pre208

for_post202:                                      ; preds = %for_pre200
  %printf230 = call i64 (...) @printf([4 x i8]* @literal.23, [4 x i8]* @literal.22)
  ret void

for_pre208:                                       ; preds = %for_body209, %for_body201
  %vr211 = load i64, i64* @j
  %vr212 = load i64, i64* @n
  %vr213 = icmp sle i64 %vr211, %vr212
  %zext214 = zext i1 %vr213 to i64
  %vr215 = icmp ne i64 %zext214, 0
  br i1 %vr215, label %for_body209, label %for_post210

for_body209:                                      ; preds = %for_pre208
  %vr216 = load i64, i64* @i
  %vr217 = load i64, i64* @n
  %vr218 = mul i64 %vr216, %vr217
  %vr219 = load i64, i64* @j
  %vr220 = add i64 %vr218, %vr219
  store i64 %vr220, i64* @a
  %vr221 = load i64, i64* @a
  %vr222 = getelementptr inbounds [62500 x i64], [62500 x i64]* @C, i64 0, i64 %vr221
  %vr223 = load i64, i64* %vr222
  %printf224 = call i64 (...) @printf([6 x i8]* @literal.19, i64 %vr223, [2 x i8]* @literal.18)
  %vr225 = load i64, i64* @j
  %vr226 = add i64 %vr225, 1
  store i64 %vr226, i64* @j
  br label %for_pre208

for_post210:                                      ; preds = %for_pre208
  %printf227 = call i64 (...) @printf([4 x i8]* @literal.21, [1 x i8]* @literal.20)
  %vr228 = load i64, i64* @i
  %vr229 = add i64 %vr228, 1
  store i64 %vr229, i64* @i
  br label %for_pre200
}

declare i64 @printf(...)

declare i64 @scanf(...)
