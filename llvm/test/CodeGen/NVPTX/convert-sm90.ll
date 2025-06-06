; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py UTC_ARGS: --version 5
; RUN: llc < %s -mtriple=nvptx64 -mcpu=sm_90 -mattr=+ptx78| FileCheck --check-prefixes=CHECK %s
; RUN: %if ptxas-12.0 %{ llc < %s -mtriple=nvptx64 -mcpu=sm_90 -mattr=+ptx78| %ptxas-verify -arch=sm_90 %}

declare i32 @llvm.nvvm.f2tf32.rn(float %f1)
declare i32 @llvm.nvvm.f2tf32.rn.relu(float %f1)
declare i32 @llvm.nvvm.f2tf32.rz(float %f1)
declare i32 @llvm.nvvm.f2tf32.rz.relu(float %f1)

define i32 @cvt_rn_tf32_f32(float %f1) {
; CHECK-LABEL: cvt_rn_tf32_f32(
; CHECK:       {
; CHECK-NEXT:    .reg .b32 %r<2>;
; CHECK-NEXT:    .reg .b32 %f<2>;
; CHECK-EMPTY:
; CHECK-NEXT:  // %bb.0:
; CHECK-NEXT:    ld.param.f32 %f1, [cvt_rn_tf32_f32_param_0];
; CHECK-NEXT:    cvt.rn.tf32.f32 %r1, %f1;
; CHECK-NEXT:    st.param.b32 [func_retval0], %r1;
; CHECK-NEXT:    ret;
  %val = call i32 @llvm.nvvm.f2tf32.rn(float %f1)
  ret i32 %val
}

define i32 @cvt_rn_relu_tf32_f32(float %f1) {
; CHECK-LABEL: cvt_rn_relu_tf32_f32(
; CHECK:       {
; CHECK-NEXT:    .reg .b32 %r<2>;
; CHECK-NEXT:    .reg .b32 %f<2>;
; CHECK-EMPTY:
; CHECK-NEXT:  // %bb.0:
; CHECK-NEXT:    ld.param.f32 %f1, [cvt_rn_relu_tf32_f32_param_0];
; CHECK-NEXT:    cvt.rn.relu.tf32.f32 %r1, %f1;
; CHECK-NEXT:    st.param.b32 [func_retval0], %r1;
; CHECK-NEXT:    ret;
  %val = call i32 @llvm.nvvm.f2tf32.rn.relu(float %f1)
  ret i32 %val
}

define i32 @cvt_rz_tf32_f32(float %f1) {
; CHECK-LABEL: cvt_rz_tf32_f32(
; CHECK:       {
; CHECK-NEXT:    .reg .b32 %r<2>;
; CHECK-NEXT:    .reg .b32 %f<2>;
; CHECK-EMPTY:
; CHECK-NEXT:  // %bb.0:
; CHECK-NEXT:    ld.param.f32 %f1, [cvt_rz_tf32_f32_param_0];
; CHECK-NEXT:    cvt.rz.tf32.f32 %r1, %f1;
; CHECK-NEXT:    st.param.b32 [func_retval0], %r1;
; CHECK-NEXT:    ret;
  %val = call i32 @llvm.nvvm.f2tf32.rz(float %f1)
  ret i32 %val
}

define i32 @cvt_rz_relu_tf32_f32(float %f1) {
; CHECK-LABEL: cvt_rz_relu_tf32_f32(
; CHECK:       {
; CHECK-NEXT:    .reg .b32 %r<2>;
; CHECK-NEXT:    .reg .b32 %f<2>;
; CHECK-EMPTY:
; CHECK-NEXT:  // %bb.0:
; CHECK-NEXT:    ld.param.f32 %f1, [cvt_rz_relu_tf32_f32_param_0];
; CHECK-NEXT:    cvt.rz.relu.tf32.f32 %r1, %f1;
; CHECK-NEXT:    st.param.b32 [func_retval0], %r1;
; CHECK-NEXT:    ret;
  %val = call i32 @llvm.nvvm.f2tf32.rz.relu(float %f1)
  ret i32 %val
}
