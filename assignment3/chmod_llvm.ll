; ModuleID = 'chmod_llvm.c'
source_filename = "chmod_llvm.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [10 x i8] c"arg count\00", align 1
@.str.1 = private unnamed_addr constant [9 x i8] c"bad mode\00", align 1

; Function Attrs: noinline nounwind sspstrong uwtable
define dso_local i32 @main(i32 noundef %0, ptr noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca ptr, align 8
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i8, align 1
  %9 = alloca i32, align 4
  store i32 0, ptr %3, align 4
  store i32 %0, ptr %4, align 4
  store ptr %1, ptr %5, align 8
  %10 = load i32, ptr %4, align 4
  %11 = icmp slt i32 %10, 3
  br i1 %11, label %12, label %14

12:                                               ; preds = %2
  %13 = call i32 (ptr, ...) @printf(ptr noundef @.str)
  call void @exit(i32 noundef 1) #5
  unreachable

14:                                               ; preds = %2
  %15 = load ptr, ptr %5, align 8
  %16 = getelementptr inbounds ptr, ptr %15, i64 1
  %17 = load ptr, ptr %16, align 8
  %18 = getelementptr inbounds i8, ptr %17, i64 0
  %19 = load i8, ptr %18, align 1
  store i8 %19, ptr %8, align 1
  store i32 0, ptr %7, align 4
  br label %20

20:                                               ; preds = %34, %14
  %21 = load i8, ptr %8, align 1
  %22 = sext i8 %21 to i32
  %23 = icmp ne i32 %22, 0
  br i1 %23, label %24, label %41

24:                                               ; preds = %20
  %25 = load i8, ptr %8, align 1
  %26 = sext i8 %25 to i32
  %27 = icmp slt i32 %26, 48
  br i1 %27, label %32, label %28

28:                                               ; preds = %24
  %29 = load i8, ptr %8, align 1
  %30 = sext i8 %29 to i32
  %31 = icmp sgt i32 %30, 55
  br i1 %31, label %32, label %34

32:                                               ; preds = %28, %24
  %33 = call i32 (ptr, ...) @printf(ptr noundef @.str.1)
  call void @exit(i32 noundef 1) #5
  unreachable

34:                                               ; preds = %28
  %35 = load i32, ptr %7, align 4
  %36 = mul nsw i32 %35, 8
  %37 = load i8, ptr %8, align 1
  %38 = sext i8 %37 to i32
  %39 = sub nsw i32 %38, 48
  %40 = add nsw i32 %36, %39
  store i32 %40, ptr %7, align 4
  store i8 1, ptr %8, align 1
  br label %20, !llvm.loop !6

41:                                               ; preds = %20
  store i32 0, ptr %9, align 4
  store i32 2, ptr %6, align 4
  br label %42

42:                                               ; preds = %64, %41
  %43 = load i32, ptr %6, align 4
  %44 = load i32, ptr %4, align 4
  %45 = icmp slt i32 %43, %44
  br i1 %45, label %46, label %67

46:                                               ; preds = %42
  %47 = load ptr, ptr %5, align 8
  %48 = load i32, ptr %6, align 4
  %49 = sext i32 %48 to i64
  %50 = getelementptr inbounds ptr, ptr %47, i64 %49
  %51 = load ptr, ptr %50, align 8
  %52 = load i32, ptr %7, align 4
  %53 = call i32 @chmod(ptr noundef %51, i32 noundef %52) #6
  %54 = icmp slt i32 %53, 0
  br i1 %54, label %55, label %63

55:                                               ; preds = %46
  %56 = load i32, ptr %9, align 4
  %57 = add nsw i32 %56, 1
  store i32 %57, ptr %9, align 4
  %58 = load ptr, ptr %5, align 8
  %59 = load i32, ptr %6, align 4
  %60 = sext i32 %59 to i64
  %61 = getelementptr inbounds ptr, ptr %58, i64 %60
  %62 = load ptr, ptr %61, align 8
  call void @perror(ptr noundef %62) #7
  br label %63

63:                                               ; preds = %55, %46
  br label %64

64:                                               ; preds = %63
  %65 = load i32, ptr %6, align 4
  %66 = add nsw i32 %65, 1
  store i32 %66, ptr %6, align 4
  br label %42, !llvm.loop !8

67:                                               ; preds = %42
  %68 = load i32, ptr %9, align 4
  call void @exit(i32 noundef %68) #5
  unreachable
}

declare i32 @printf(ptr noundef, ...) #1

; Function Attrs: noreturn nounwind
declare void @exit(i32 noundef) #2

; Function Attrs: nounwind
declare i32 @chmod(ptr noundef, i32 noundef) #3

; Function Attrs: cold
declare void @perror(ptr noundef) #4

attributes #0 = { noinline nounwind sspstrong uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { noreturn nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { cold "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #5 = { noreturn nounwind }
attributes #6 = { nounwind }
attributes #7 = { cold }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"clang version 22.1.5"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
