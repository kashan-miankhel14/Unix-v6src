; ModuleID = 'chmod_llvm.ll'
source_filename = "chmod_llvm.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [10 x i8] c"arg count\00", align 1
@.str.1 = private unnamed_addr constant [9 x i8] c"bad mode\00", align 1

; Function Attrs: noinline nounwind sspstrong uwtable
define dso_local i32 @main(i32 noundef %0, ptr noundef %1) #0 {
  %3 = icmp slt i32 %0, 3
  br i1 %3, label %4, label %6

4:                                                ; preds = %2
  %5 = call i32 (ptr, ...) @printf(ptr noundef @.str)
  call void @exit(i32 noundef 1) #5
  unreachable

6:                                                ; preds = %2
  %7 = getelementptr inbounds ptr, ptr %1, i64 1
  %8 = load ptr, ptr %7, align 8
  %9 = getelementptr inbounds i8, ptr %8, i64 0
  %10 = load i8, ptr %9, align 1
  br label %11

11:                                               ; preds = %22, %6
  %.02 = phi i32 [ 0, %6 ], [ %26, %22 ]
  %.01 = phi i8 [ %10, %6 ], [ 1, %22 ]
  %12 = sext i8 %.01 to i32
  %13 = icmp ne i32 %12, 0
  br i1 %13, label %14, label %27

14:                                               ; preds = %11
  %15 = sext i8 %.01 to i32
  %16 = icmp slt i32 %15, 48
  br i1 %16, label %20, label %17

17:                                               ; preds = %14
  %18 = sext i8 %.01 to i32
  %19 = icmp sgt i32 %18, 55
  br i1 %19, label %20, label %22

20:                                               ; preds = %17, %14
  %21 = call i32 (ptr, ...) @printf(ptr noundef @.str.1)
  call void @exit(i32 noundef 1) #5
  unreachable

22:                                               ; preds = %17
  %23 = mul nsw i32 %.02, 8
  %24 = sext i8 %.01 to i32
  %25 = sub nsw i32 %24, 48
  %26 = add nsw i32 %23, %25
  br label %11, !llvm.loop !6

27:                                               ; preds = %11
  br label %28

28:                                               ; preds = %42, %27
  %.03 = phi i32 [ 2, %27 ], [ %43, %42 ]
  %.0 = phi i32 [ 0, %27 ], [ %.1, %42 ]
  %29 = icmp slt i32 %.03, %0
  br i1 %29, label %30, label %44

30:                                               ; preds = %28
  %31 = sext i32 %.03 to i64
  %32 = getelementptr inbounds ptr, ptr %1, i64 %31
  %33 = load ptr, ptr %32, align 8
  %34 = call i32 @chmod(ptr noundef %33, i32 noundef %.02) #6
  %35 = icmp slt i32 %34, 0
  br i1 %35, label %36, label %41

36:                                               ; preds = %30
  %37 = add nsw i32 %.0, 1
  %38 = sext i32 %.03 to i64
  %39 = getelementptr inbounds ptr, ptr %1, i64 %38
  %40 = load ptr, ptr %39, align 8
  call void @perror(ptr noundef %40) #7
  br label %41

41:                                               ; preds = %36, %30
  %.1 = phi i32 [ %37, %36 ], [ %.0, %30 ]
  br label %42

42:                                               ; preds = %41
  %43 = add nsw i32 %.03, 1
  br label %28, !llvm.loop !8

44:                                               ; preds = %28
  call void @exit(i32 noundef %.0) #5
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
