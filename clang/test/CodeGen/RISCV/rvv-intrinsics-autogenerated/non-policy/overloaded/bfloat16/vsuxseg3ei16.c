// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py UTC_ARGS: --version 4
// REQUIRES: riscv-registered-target
// RUN: %clang_cc1 -triple riscv64 -target-feature +v \
// RUN:   -target-feature +zvfbfmin \
// RUN:   -target-feature +zvfbfwma -disable-O0-optnone \
// RUN:   -emit-llvm %s -o - | opt -S -passes=mem2reg | \
// RUN:   FileCheck --check-prefix=CHECK-RV64 %s

#include <riscv_vector.h>

// CHECK-RV64-LABEL: define dso_local void @test_vsuxseg3ei16_v_bf16mf4x3(
// CHECK-RV64-SAME: ptr noundef [[RS1:%.*]], <vscale x 1 x i16> [[VS2:%.*]], { <vscale x 1 x bfloat>, <vscale x 1 x bfloat>, <vscale x 1 x bfloat> } [[VS3:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0:[0-9]+]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = extractvalue { <vscale x 1 x bfloat>, <vscale x 1 x bfloat>, <vscale x 1 x bfloat> } [[VS3]], 0
// CHECK-RV64-NEXT:    [[TMP1:%.*]] = extractvalue { <vscale x 1 x bfloat>, <vscale x 1 x bfloat>, <vscale x 1 x bfloat> } [[VS3]], 1
// CHECK-RV64-NEXT:    [[TMP2:%.*]] = extractvalue { <vscale x 1 x bfloat>, <vscale x 1 x bfloat>, <vscale x 1 x bfloat> } [[VS3]], 2
// CHECK-RV64-NEXT:    call void @llvm.riscv.vsuxseg3.nxv1bf16.nxv1i16.i64(<vscale x 1 x bfloat> [[TMP0]], <vscale x 1 x bfloat> [[TMP1]], <vscale x 1 x bfloat> [[TMP2]], ptr [[RS1]], <vscale x 1 x i16> [[VS2]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret void
//
void test_vsuxseg3ei16_v_bf16mf4x3(__bf16 *rs1, vuint16mf4_t vs2,
                                   vbfloat16mf4x3_t vs3, size_t vl) {
  return __riscv_vsuxseg3ei16(rs1, vs2, vs3, vl);
}

// CHECK-RV64-LABEL: define dso_local void @test_vsuxseg3ei16_v_bf16mf2x3(
// CHECK-RV64-SAME: ptr noundef [[RS1:%.*]], <vscale x 2 x i16> [[VS2:%.*]], { <vscale x 2 x bfloat>, <vscale x 2 x bfloat>, <vscale x 2 x bfloat> } [[VS3:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = extractvalue { <vscale x 2 x bfloat>, <vscale x 2 x bfloat>, <vscale x 2 x bfloat> } [[VS3]], 0
// CHECK-RV64-NEXT:    [[TMP1:%.*]] = extractvalue { <vscale x 2 x bfloat>, <vscale x 2 x bfloat>, <vscale x 2 x bfloat> } [[VS3]], 1
// CHECK-RV64-NEXT:    [[TMP2:%.*]] = extractvalue { <vscale x 2 x bfloat>, <vscale x 2 x bfloat>, <vscale x 2 x bfloat> } [[VS3]], 2
// CHECK-RV64-NEXT:    call void @llvm.riscv.vsuxseg3.nxv2bf16.nxv2i16.i64(<vscale x 2 x bfloat> [[TMP0]], <vscale x 2 x bfloat> [[TMP1]], <vscale x 2 x bfloat> [[TMP2]], ptr [[RS1]], <vscale x 2 x i16> [[VS2]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret void
//
void test_vsuxseg3ei16_v_bf16mf2x3(__bf16 *rs1, vuint16mf2_t vs2,
                                   vbfloat16mf2x3_t vs3, size_t vl) {
  return __riscv_vsuxseg3ei16(rs1, vs2, vs3, vl);
}

// CHECK-RV64-LABEL: define dso_local void @test_vsuxseg3ei16_v_bf16m1x3(
// CHECK-RV64-SAME: ptr noundef [[RS1:%.*]], <vscale x 4 x i16> [[VS2:%.*]], { <vscale x 4 x bfloat>, <vscale x 4 x bfloat>, <vscale x 4 x bfloat> } [[VS3:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = extractvalue { <vscale x 4 x bfloat>, <vscale x 4 x bfloat>, <vscale x 4 x bfloat> } [[VS3]], 0
// CHECK-RV64-NEXT:    [[TMP1:%.*]] = extractvalue { <vscale x 4 x bfloat>, <vscale x 4 x bfloat>, <vscale x 4 x bfloat> } [[VS3]], 1
// CHECK-RV64-NEXT:    [[TMP2:%.*]] = extractvalue { <vscale x 4 x bfloat>, <vscale x 4 x bfloat>, <vscale x 4 x bfloat> } [[VS3]], 2
// CHECK-RV64-NEXT:    call void @llvm.riscv.vsuxseg3.nxv4bf16.nxv4i16.i64(<vscale x 4 x bfloat> [[TMP0]], <vscale x 4 x bfloat> [[TMP1]], <vscale x 4 x bfloat> [[TMP2]], ptr [[RS1]], <vscale x 4 x i16> [[VS2]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret void
//
void test_vsuxseg3ei16_v_bf16m1x3(__bf16 *rs1, vuint16m1_t vs2,
                                  vbfloat16m1x3_t vs3, size_t vl) {
  return __riscv_vsuxseg3ei16(rs1, vs2, vs3, vl);
}

// CHECK-RV64-LABEL: define dso_local void @test_vsuxseg3ei16_v_bf16m2x3(
// CHECK-RV64-SAME: ptr noundef [[RS1:%.*]], <vscale x 8 x i16> [[VS2:%.*]], { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[VS3:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = extractvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[VS3]], 0
// CHECK-RV64-NEXT:    [[TMP1:%.*]] = extractvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[VS3]], 1
// CHECK-RV64-NEXT:    [[TMP2:%.*]] = extractvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[VS3]], 2
// CHECK-RV64-NEXT:    call void @llvm.riscv.vsuxseg3.nxv8bf16.nxv8i16.i64(<vscale x 8 x bfloat> [[TMP0]], <vscale x 8 x bfloat> [[TMP1]], <vscale x 8 x bfloat> [[TMP2]], ptr [[RS1]], <vscale x 8 x i16> [[VS2]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret void
//
void test_vsuxseg3ei16_v_bf16m2x3(__bf16 *rs1, vuint16m2_t vs2,
                                  vbfloat16m2x3_t vs3, size_t vl) {
  return __riscv_vsuxseg3ei16(rs1, vs2, vs3, vl);
}

// CHECK-RV64-LABEL: define dso_local void @test_vsuxseg3ei16_v_bf16mf4x3_m(
// CHECK-RV64-SAME: <vscale x 1 x i1> [[VM:%.*]], ptr noundef [[RS1:%.*]], <vscale x 1 x i16> [[VS2:%.*]], { <vscale x 1 x bfloat>, <vscale x 1 x bfloat>, <vscale x 1 x bfloat> } [[VS3:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = extractvalue { <vscale x 1 x bfloat>, <vscale x 1 x bfloat>, <vscale x 1 x bfloat> } [[VS3]], 0
// CHECK-RV64-NEXT:    [[TMP1:%.*]] = extractvalue { <vscale x 1 x bfloat>, <vscale x 1 x bfloat>, <vscale x 1 x bfloat> } [[VS3]], 1
// CHECK-RV64-NEXT:    [[TMP2:%.*]] = extractvalue { <vscale x 1 x bfloat>, <vscale x 1 x bfloat>, <vscale x 1 x bfloat> } [[VS3]], 2
// CHECK-RV64-NEXT:    call void @llvm.riscv.vsuxseg3.mask.nxv1bf16.nxv1i16.i64(<vscale x 1 x bfloat> [[TMP0]], <vscale x 1 x bfloat> [[TMP1]], <vscale x 1 x bfloat> [[TMP2]], ptr [[RS1]], <vscale x 1 x i16> [[VS2]], <vscale x 1 x i1> [[VM]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret void
//
void test_vsuxseg3ei16_v_bf16mf4x3_m(vbool64_t vm, __bf16 *rs1,
                                     vuint16mf4_t vs2, vbfloat16mf4x3_t vs3,
                                     size_t vl) {
  return __riscv_vsuxseg3ei16(vm, rs1, vs2, vs3, vl);
}

// CHECK-RV64-LABEL: define dso_local void @test_vsuxseg3ei16_v_bf16mf2x3_m(
// CHECK-RV64-SAME: <vscale x 2 x i1> [[VM:%.*]], ptr noundef [[RS1:%.*]], <vscale x 2 x i16> [[VS2:%.*]], { <vscale x 2 x bfloat>, <vscale x 2 x bfloat>, <vscale x 2 x bfloat> } [[VS3:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = extractvalue { <vscale x 2 x bfloat>, <vscale x 2 x bfloat>, <vscale x 2 x bfloat> } [[VS3]], 0
// CHECK-RV64-NEXT:    [[TMP1:%.*]] = extractvalue { <vscale x 2 x bfloat>, <vscale x 2 x bfloat>, <vscale x 2 x bfloat> } [[VS3]], 1
// CHECK-RV64-NEXT:    [[TMP2:%.*]] = extractvalue { <vscale x 2 x bfloat>, <vscale x 2 x bfloat>, <vscale x 2 x bfloat> } [[VS3]], 2
// CHECK-RV64-NEXT:    call void @llvm.riscv.vsuxseg3.mask.nxv2bf16.nxv2i16.i64(<vscale x 2 x bfloat> [[TMP0]], <vscale x 2 x bfloat> [[TMP1]], <vscale x 2 x bfloat> [[TMP2]], ptr [[RS1]], <vscale x 2 x i16> [[VS2]], <vscale x 2 x i1> [[VM]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret void
//
void test_vsuxseg3ei16_v_bf16mf2x3_m(vbool32_t vm, __bf16 *rs1,
                                     vuint16mf2_t vs2, vbfloat16mf2x3_t vs3,
                                     size_t vl) {
  return __riscv_vsuxseg3ei16(vm, rs1, vs2, vs3, vl);
}

// CHECK-RV64-LABEL: define dso_local void @test_vsuxseg3ei16_v_bf16m1x3_m(
// CHECK-RV64-SAME: <vscale x 4 x i1> [[VM:%.*]], ptr noundef [[RS1:%.*]], <vscale x 4 x i16> [[VS2:%.*]], { <vscale x 4 x bfloat>, <vscale x 4 x bfloat>, <vscale x 4 x bfloat> } [[VS3:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = extractvalue { <vscale x 4 x bfloat>, <vscale x 4 x bfloat>, <vscale x 4 x bfloat> } [[VS3]], 0
// CHECK-RV64-NEXT:    [[TMP1:%.*]] = extractvalue { <vscale x 4 x bfloat>, <vscale x 4 x bfloat>, <vscale x 4 x bfloat> } [[VS3]], 1
// CHECK-RV64-NEXT:    [[TMP2:%.*]] = extractvalue { <vscale x 4 x bfloat>, <vscale x 4 x bfloat>, <vscale x 4 x bfloat> } [[VS3]], 2
// CHECK-RV64-NEXT:    call void @llvm.riscv.vsuxseg3.mask.nxv4bf16.nxv4i16.i64(<vscale x 4 x bfloat> [[TMP0]], <vscale x 4 x bfloat> [[TMP1]], <vscale x 4 x bfloat> [[TMP2]], ptr [[RS1]], <vscale x 4 x i16> [[VS2]], <vscale x 4 x i1> [[VM]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret void
//
void test_vsuxseg3ei16_v_bf16m1x3_m(vbool16_t vm, __bf16 *rs1, vuint16m1_t vs2,
                                    vbfloat16m1x3_t vs3, size_t vl) {
  return __riscv_vsuxseg3ei16(vm, rs1, vs2, vs3, vl);
}

// CHECK-RV64-LABEL: define dso_local void @test_vsuxseg3ei16_v_bf16m2x3_m(
// CHECK-RV64-SAME: <vscale x 8 x i1> [[VM:%.*]], ptr noundef [[RS1:%.*]], <vscale x 8 x i16> [[VS2:%.*]], { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[VS3:%.*]], i64 noundef [[VL:%.*]]) #[[ATTR0]] {
// CHECK-RV64-NEXT:  entry:
// CHECK-RV64-NEXT:    [[TMP0:%.*]] = extractvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[VS3]], 0
// CHECK-RV64-NEXT:    [[TMP1:%.*]] = extractvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[VS3]], 1
// CHECK-RV64-NEXT:    [[TMP2:%.*]] = extractvalue { <vscale x 8 x bfloat>, <vscale x 8 x bfloat>, <vscale x 8 x bfloat> } [[VS3]], 2
// CHECK-RV64-NEXT:    call void @llvm.riscv.vsuxseg3.mask.nxv8bf16.nxv8i16.i64(<vscale x 8 x bfloat> [[TMP0]], <vscale x 8 x bfloat> [[TMP1]], <vscale x 8 x bfloat> [[TMP2]], ptr [[RS1]], <vscale x 8 x i16> [[VS2]], <vscale x 8 x i1> [[VM]], i64 [[VL]])
// CHECK-RV64-NEXT:    ret void
//
void test_vsuxseg3ei16_v_bf16m2x3_m(vbool8_t vm, __bf16 *rs1, vuint16m2_t vs2,
                                    vbfloat16m2x3_t vs3, size_t vl) {
  return __riscv_vsuxseg3ei16(vm, rs1, vs2, vs3, vl);
}
