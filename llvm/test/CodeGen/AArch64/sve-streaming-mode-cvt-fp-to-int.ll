; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc -mattr=+sve -force-streaming-compatible < %s | FileCheck %s
; RUN: llc -mattr=+sme -force-streaming < %s | FileCheck %s
; RUN: llc -force-streaming-compatible < %s | FileCheck %s --check-prefix=NONEON-NOSVE

target triple = "aarch64-unknown-linux-gnu"

define i32 @f16_to_s32(half %x) {
; CHECK-LABEL: f16_to_s32:
; CHECK:       // %bb.0: // %entry
; CHECK-NEXT:    ptrue p0.s
; CHECK-NEXT:    // kill: def $h0 killed $h0 def $z0
; CHECK-NEXT:    fcvtzs z0.s, p0/m, z0.h
; CHECK-NEXT:    fmov w0, s0
; CHECK-NEXT:    ret
;
; NONEON-NOSVE-LABEL: f16_to_s32:
; NONEON-NOSVE:       // %bb.0: // %entry
; NONEON-NOSVE-NEXT:    fcvt s0, h0
; NONEON-NOSVE-NEXT:    fcvtzs w0, s0
; NONEON-NOSVE-NEXT:    ret
  entry:
  %cvt = fptosi half %x to i32
  ret i32 %cvt
}

define i64 @f16_to_s64(half %x) {
; CHECK-LABEL: f16_to_s64:
; CHECK:       // %bb.0: // %entry
; CHECK-NEXT:    ptrue p0.d
; CHECK-NEXT:    // kill: def $h0 killed $h0 def $z0
; CHECK-NEXT:    fcvtzs z0.d, p0/m, z0.h
; CHECK-NEXT:    fmov x0, d0
; CHECK-NEXT:    ret
;
; NONEON-NOSVE-LABEL: f16_to_s64:
; NONEON-NOSVE:       // %bb.0: // %entry
; NONEON-NOSVE-NEXT:    fcvt s0, h0
; NONEON-NOSVE-NEXT:    fcvtzs x0, s0
; NONEON-NOSVE-NEXT:    ret
  entry:
  %cvt = fptosi half %x to i64
  ret i64 %cvt
}

define i32 @f32_to_s32(float %x) {
; CHECK-LABEL: f32_to_s32:
; CHECK:       // %bb.0: // %entry
; CHECK-NEXT:    ptrue p0.s
; CHECK-NEXT:    // kill: def $s0 killed $s0 def $z0
; CHECK-NEXT:    fcvtzs z0.s, p0/m, z0.s
; CHECK-NEXT:    fmov w0, s0
; CHECK-NEXT:    ret
;
; NONEON-NOSVE-LABEL: f32_to_s32:
; NONEON-NOSVE:       // %bb.0: // %entry
; NONEON-NOSVE-NEXT:    fcvtzs w0, s0
; NONEON-NOSVE-NEXT:    ret
  entry:
  %cvt = fptosi float %x to i32
  ret i32 %cvt
}

define i64 @f32_to_s64(float %x) {
; CHECK-LABEL: f32_to_s64:
; CHECK:       // %bb.0: // %entry
; CHECK-NEXT:    ptrue p0.d
; CHECK-NEXT:    // kill: def $s0 killed $s0 def $z0
; CHECK-NEXT:    fcvtzs z0.d, p0/m, z0.s
; CHECK-NEXT:    fmov x0, d0
; CHECK-NEXT:    ret
;
; NONEON-NOSVE-LABEL: f32_to_s64:
; NONEON-NOSVE:       // %bb.0: // %entry
; NONEON-NOSVE-NEXT:    fcvtzs x0, s0
; NONEON-NOSVE-NEXT:    ret
  entry:
  %cvt = fptosi float %x to i64
  ret i64 %cvt
}

define i32 @f64_to_s32(double %x) {
; CHECK-LABEL: f64_to_s32:
; CHECK:       // %bb.0: // %entry
; CHECK-NEXT:    fcvtzs w0, d0
; CHECK-NEXT:    ret
;
; NONEON-NOSVE-LABEL: f64_to_s32:
; NONEON-NOSVE:       // %bb.0: // %entry
; NONEON-NOSVE-NEXT:    fcvtzs w0, d0
; NONEON-NOSVE-NEXT:    ret
  entry:
  %cvt = fptosi double %x to i32
  ret i32 %cvt
}

define i64 @f64_to_s64(double %x) {
; CHECK-LABEL: f64_to_s64:
; CHECK:       // %bb.0: // %entry
; CHECK-NEXT:    ptrue p0.d
; CHECK-NEXT:    // kill: def $d0 killed $d0 def $z0
; CHECK-NEXT:    fcvtzs z0.d, p0/m, z0.d
; CHECK-NEXT:    fmov x0, d0
; CHECK-NEXT:    ret
;
; NONEON-NOSVE-LABEL: f64_to_s64:
; NONEON-NOSVE:       // %bb.0: // %entry
; NONEON-NOSVE-NEXT:    fcvtzs x0, d0
; NONEON-NOSVE-NEXT:    ret
  entry:
  %cvt = fptosi double %x to i64
  ret i64 %cvt
}

define i32 @f16_to_u32(half %x) {
; CHECK-LABEL: f16_to_u32:
; CHECK:       // %bb.0: // %entry
; CHECK-NEXT:    ptrue p0.s
; CHECK-NEXT:    // kill: def $h0 killed $h0 def $z0
; CHECK-NEXT:    fcvtzu z0.s, p0/m, z0.h
; CHECK-NEXT:    fmov w0, s0
; CHECK-NEXT:    ret
;
; NONEON-NOSVE-LABEL: f16_to_u32:
; NONEON-NOSVE:       // %bb.0: // %entry
; NONEON-NOSVE-NEXT:    fcvt s0, h0
; NONEON-NOSVE-NEXT:    fcvtzu w0, s0
; NONEON-NOSVE-NEXT:    ret
  entry:
  %cvt = fptoui half %x to i32
  ret i32 %cvt
}

define i64 @f16_to_u64(half %x) {
; CHECK-LABEL: f16_to_u64:
; CHECK:       // %bb.0: // %entry
; CHECK-NEXT:    ptrue p0.d
; CHECK-NEXT:    // kill: def $h0 killed $h0 def $z0
; CHECK-NEXT:    fcvtzu z0.d, p0/m, z0.h
; CHECK-NEXT:    fmov x0, d0
; CHECK-NEXT:    ret
;
; NONEON-NOSVE-LABEL: f16_to_u64:
; NONEON-NOSVE:       // %bb.0: // %entry
; NONEON-NOSVE-NEXT:    fcvt s0, h0
; NONEON-NOSVE-NEXT:    fcvtzu x0, s0
; NONEON-NOSVE-NEXT:    ret
  entry:
  %cvt = fptoui half %x to i64
  ret i64 %cvt
}

define i32 @f32_to_u32(float %x) {
; CHECK-LABEL: f32_to_u32:
; CHECK:       // %bb.0: // %entry
; CHECK-NEXT:    ptrue p0.s
; CHECK-NEXT:    // kill: def $s0 killed $s0 def $z0
; CHECK-NEXT:    fcvtzu z0.s, p0/m, z0.s
; CHECK-NEXT:    fmov w0, s0
; CHECK-NEXT:    ret
;
; NONEON-NOSVE-LABEL: f32_to_u32:
; NONEON-NOSVE:       // %bb.0: // %entry
; NONEON-NOSVE-NEXT:    fcvtzu w0, s0
; NONEON-NOSVE-NEXT:    ret
  entry:
  %cvt = fptoui float %x to i32
  ret i32 %cvt
}

define i64 @f32_to_u64(float %x) {
; CHECK-LABEL: f32_to_u64:
; CHECK:       // %bb.0: // %entry
; CHECK-NEXT:    ptrue p0.d
; CHECK-NEXT:    // kill: def $s0 killed $s0 def $z0
; CHECK-NEXT:    fcvtzu z0.d, p0/m, z0.s
; CHECK-NEXT:    fmov x0, d0
; CHECK-NEXT:    ret
;
; NONEON-NOSVE-LABEL: f32_to_u64:
; NONEON-NOSVE:       // %bb.0: // %entry
; NONEON-NOSVE-NEXT:    fcvtzu x0, s0
; NONEON-NOSVE-NEXT:    ret
  entry:
  %cvt = fptoui float %x to i64
  ret i64 %cvt
}

define i32 @f64_to_u32(double %x) {
; CHECK-LABEL: f64_to_u32:
; CHECK:       // %bb.0: // %entry
; CHECK-NEXT:    fcvtzu w0, d0
; CHECK-NEXT:    ret
;
; NONEON-NOSVE-LABEL: f64_to_u32:
; NONEON-NOSVE:       // %bb.0: // %entry
; NONEON-NOSVE-NEXT:    fcvtzu w0, d0
; NONEON-NOSVE-NEXT:    ret
  entry:
  %cvt = fptoui double %x to i32
  ret i32 %cvt
}

define i64 @f64_to_u64(double %x) {
; CHECK-LABEL: f64_to_u64:
; CHECK:       // %bb.0: // %entry
; CHECK-NEXT:    ptrue p0.d
; CHECK-NEXT:    // kill: def $d0 killed $d0 def $z0
; CHECK-NEXT:    fcvtzu z0.d, p0/m, z0.d
; CHECK-NEXT:    fmov x0, d0
; CHECK-NEXT:    ret
;
; NONEON-NOSVE-LABEL: f64_to_u64:
; NONEON-NOSVE:       // %bb.0: // %entry
; NONEON-NOSVE-NEXT:    fcvtzu x0, d0
; NONEON-NOSVE-NEXT:    ret
  entry:
  %cvt = fptoui double %x to i64
  ret i64 %cvt
}

define i32 @strict_convert_signed(double %x) {
; CHECK-LABEL: strict_convert_signed:
; CHECK:       // %bb.0: // %entry
; CHECK-NEXT:    fcvtzs w0, d0
; CHECK-NEXT:    ret
;
; NONEON-NOSVE-LABEL: strict_convert_signed:
; NONEON-NOSVE:       // %bb.0: // %entry
; NONEON-NOSVE-NEXT:    fcvtzs w0, d0
; NONEON-NOSVE-NEXT:    ret
  entry:
  %cvt = call i32 @llvm.experimental.constrained.fptosi.i32.f64(double %x, metadata !"fpexcept.strict") #0
  ret i32 %cvt
}

define i32 @strict_convert_unsigned(float %x) {
; CHECK-LABEL: strict_convert_unsigned:
; CHECK:       // %bb.0: // %entry
; CHECK-NEXT:    fcvtzu w0, s0
; CHECK-NEXT:    ret
;
; NONEON-NOSVE-LABEL: strict_convert_unsigned:
; NONEON-NOSVE:       // %bb.0: // %entry
; NONEON-NOSVE-NEXT:    fcvtzu w0, s0
; NONEON-NOSVE-NEXT:    ret
  entry:
  %cvt = call i32 @llvm.experimental.constrained.fptoui.i32.f32(float %x, metadata !"fpexcept.strict") #0
  ret i32 %cvt
}

attributes #0 = { strictfp }
