#include "Utils/AArch64SMEAttributes.h"
#include "llvm/AsmParser/Parser.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/SourceMgr.h"

#include "gtest/gtest.h"

using namespace llvm;
using SA = SMEAttrs;

std::unique_ptr<Module> parseIR(const char *IR) {
  static LLVMContext C;
  SMDiagnostic Err;
  return parseAssemblyString(IR, Err, C);
}

TEST(SMEAttributes, Constructors) {
  LLVMContext Context;

  ASSERT_TRUE(SA(*parseIR("declare void @foo()")->getFunction("foo"))
                  .hasNonStreamingInterfaceAndBody());

  ASSERT_TRUE(SA(*parseIR("declare void @foo() \"aarch64_pstate_sm_body\"")
                      ->getFunction("foo"))
                  .hasNonStreamingInterface());

  ASSERT_TRUE(SA(*parseIR("declare void @foo() \"aarch64_pstate_sm_enabled\"")
                      ->getFunction("foo"))
                  .hasStreamingInterface());

  ASSERT_TRUE(SA(*parseIR("declare void @foo() \"aarch64_pstate_sm_body\"")
                      ->getFunction("foo"))
                  .hasStreamingBody());

  ASSERT_TRUE(
      SA(*parseIR("declare void @foo() \"aarch64_pstate_sm_compatible\"")
              ->getFunction("foo"))
          .hasStreamingCompatibleInterface());

  ASSERT_TRUE(
      SA(*parseIR("declare void @foo() \"aarch64_in_za\"")->getFunction("foo"))
          .isInZA());
  ASSERT_TRUE(
      SA(*parseIR("declare void @foo() \"aarch64_out_za\"")->getFunction("foo"))
          .isOutZA());
  ASSERT_TRUE(SA(*parseIR("declare void @foo() \"aarch64_inout_za\"")
                      ->getFunction("foo"))
                  .isInOutZA());
  ASSERT_TRUE(SA(*parseIR("declare void @foo() \"aarch64_preserves_za\"")
                      ->getFunction("foo"))
                  .isPreservesZA());
  ASSERT_TRUE(
      SA(*parseIR("declare void @foo() \"aarch64_new_za\"")->getFunction("foo"))
          .isNewZA());

  ASSERT_TRUE(
      SA(*parseIR("declare void @foo() \"aarch64_in_zt0\"")->getFunction("foo"))
          .isInZT0());
  ASSERT_TRUE(SA(*parseIR("declare void @foo() \"aarch64_out_zt0\"")
                      ->getFunction("foo"))
                  .isOutZT0());
  ASSERT_TRUE(SA(*parseIR("declare void @foo() \"aarch64_inout_zt0\"")
                      ->getFunction("foo"))
                  .isInOutZT0());
  ASSERT_TRUE(SA(*parseIR("declare void @foo() \"aarch64_preserves_zt0\"")
                      ->getFunction("foo"))
                  .isPreservesZT0());
  ASSERT_TRUE(SA(*parseIR("declare void @foo() \"aarch64_new_zt0\"")
                      ->getFunction("foo"))
                  .isNewZT0());
  ASSERT_TRUE(
      SA(cast<CallBase>((parseIR("declare void @callee()\n"
                                 "define void @foo() {"
                                 "call void @callee() \"aarch64_zt0_undef\"\n"
                                 "ret void\n}")
                             ->getFunction("foo")
                             ->begin()
                             ->front())))
          .isUndefZT0());

  // Invalid combinations.
  EXPECT_DEBUG_DEATH(SA(SA::SM_Enabled | SA::SM_Compatible),
                     "SM_Enabled and SM_Compatible are mutually exclusive");

  // Test that the set() methods equally check validity.
  EXPECT_DEBUG_DEATH(SA(SA::SM_Enabled).set(SA::SM_Compatible),
                     "SM_Enabled and SM_Compatible are mutually exclusive");
  EXPECT_DEBUG_DEATH(SA(SA::SM_Compatible).set(SA::SM_Enabled),
                     "SM_Enabled and SM_Compatible are mutually exclusive");
}

TEST(SMEAttributes, Basics) {
  // Test PSTATE.SM interfaces.
  ASSERT_TRUE(SA(SA::Normal).hasNonStreamingInterfaceAndBody());
  ASSERT_TRUE(SA(SA::SM_Enabled).hasStreamingInterface());
  ASSERT_TRUE(SA(SA::SM_Body).hasStreamingBody());
  ASSERT_TRUE(SA(SA::SM_Body).hasNonStreamingInterface());
  ASSERT_FALSE(SA(SA::SM_Body).hasNonStreamingInterfaceAndBody());
  ASSERT_FALSE(SA(SA::SM_Body).hasStreamingInterface());
  ASSERT_TRUE(SA(SA::SM_Compatible).hasStreamingCompatibleInterface());
  ASSERT_TRUE(
      SA(SA::SM_Compatible | SA::SM_Body).hasStreamingCompatibleInterface());
  ASSERT_TRUE(SA(SA::SM_Compatible | SA::SM_Body).hasStreamingBody());
  ASSERT_FALSE(SA(SA::SM_Compatible | SA::SM_Body).hasNonStreamingInterface());

  // Test ZA State interfaces
  SA ZA_In = SA(SA::encodeZAState(SA::StateValue::In));
  ASSERT_TRUE(ZA_In.isInZA());
  ASSERT_FALSE(ZA_In.isOutZA());
  ASSERT_FALSE(ZA_In.isInOutZA());
  ASSERT_FALSE(ZA_In.isPreservesZA());
  ASSERT_FALSE(ZA_In.isNewZA());
  ASSERT_TRUE(ZA_In.sharesZA());
  ASSERT_TRUE(ZA_In.hasZAState());
  ASSERT_TRUE(ZA_In.hasSharedZAInterface());
  ASSERT_FALSE(ZA_In.hasPrivateZAInterface());

  SA ZA_Out = SA(SA::encodeZAState(SA::StateValue::Out));
  ASSERT_TRUE(ZA_Out.isOutZA());
  ASSERT_FALSE(ZA_Out.isInZA());
  ASSERT_FALSE(ZA_Out.isInOutZA());
  ASSERT_FALSE(ZA_Out.isPreservesZA());
  ASSERT_FALSE(ZA_Out.isNewZA());
  ASSERT_TRUE(ZA_Out.sharesZA());
  ASSERT_TRUE(ZA_Out.hasZAState());
  ASSERT_TRUE(ZA_Out.hasSharedZAInterface());
  ASSERT_FALSE(ZA_Out.hasPrivateZAInterface());

  SA ZA_InOut = SA(SA::encodeZAState(SA::StateValue::InOut));
  ASSERT_TRUE(ZA_InOut.isInOutZA());
  ASSERT_FALSE(ZA_InOut.isInZA());
  ASSERT_FALSE(ZA_InOut.isOutZA());
  ASSERT_FALSE(ZA_InOut.isPreservesZA());
  ASSERT_FALSE(ZA_InOut.isNewZA());
  ASSERT_TRUE(ZA_InOut.sharesZA());
  ASSERT_TRUE(ZA_InOut.hasZAState());
  ASSERT_TRUE(ZA_InOut.hasSharedZAInterface());
  ASSERT_FALSE(ZA_InOut.hasPrivateZAInterface());

  SA ZA_Preserved = SA(SA::encodeZAState(SA::StateValue::Preserved));
  ASSERT_TRUE(ZA_Preserved.isPreservesZA());
  ASSERT_FALSE(ZA_Preserved.isInZA());
  ASSERT_FALSE(ZA_Preserved.isOutZA());
  ASSERT_FALSE(ZA_Preserved.isInOutZA());
  ASSERT_FALSE(ZA_Preserved.isNewZA());
  ASSERT_TRUE(ZA_Preserved.sharesZA());
  ASSERT_TRUE(ZA_Preserved.hasZAState());
  ASSERT_TRUE(ZA_Preserved.hasSharedZAInterface());
  ASSERT_FALSE(ZA_Preserved.hasPrivateZAInterface());

  SA ZA_New = SA(SA::encodeZAState(SA::StateValue::New));
  ASSERT_TRUE(ZA_New.isNewZA());
  ASSERT_FALSE(ZA_New.isInZA());
  ASSERT_FALSE(ZA_New.isOutZA());
  ASSERT_FALSE(ZA_New.isInOutZA());
  ASSERT_FALSE(ZA_New.isPreservesZA());
  ASSERT_FALSE(ZA_New.sharesZA());
  ASSERT_TRUE(ZA_New.hasZAState());
  ASSERT_FALSE(ZA_New.hasSharedZAInterface());
  ASSERT_TRUE(ZA_New.hasPrivateZAInterface());

  ASSERT_FALSE(SA(SA::Normal).isInZA());
  ASSERT_FALSE(SA(SA::Normal).isOutZA());
  ASSERT_FALSE(SA(SA::Normal).isInOutZA());
  ASSERT_FALSE(SA(SA::Normal).isPreservesZA());
  ASSERT_FALSE(SA(SA::Normal).isNewZA());
  ASSERT_FALSE(SA(SA::Normal).sharesZA());
  ASSERT_FALSE(SA(SA::Normal).hasZAState());

  // Test ZT0 State interfaces
  SA ZT0_In = SA(SA::encodeZT0State(SA::StateValue::In));
  ASSERT_TRUE(ZT0_In.isInZT0());
  ASSERT_FALSE(ZT0_In.isOutZT0());
  ASSERT_FALSE(ZT0_In.isInOutZT0());
  ASSERT_FALSE(ZT0_In.isPreservesZT0());
  ASSERT_FALSE(ZT0_In.isNewZT0());
  ASSERT_TRUE(ZT0_In.sharesZT0());
  ASSERT_TRUE(ZT0_In.hasZT0State());
  ASSERT_TRUE(ZT0_In.hasSharedZAInterface());
  ASSERT_FALSE(ZT0_In.hasPrivateZAInterface());

  SA ZT0_Out = SA(SA::encodeZT0State(SA::StateValue::Out));
  ASSERT_TRUE(ZT0_Out.isOutZT0());
  ASSERT_FALSE(ZT0_Out.isInZT0());
  ASSERT_FALSE(ZT0_Out.isInOutZT0());
  ASSERT_FALSE(ZT0_Out.isPreservesZT0());
  ASSERT_FALSE(ZT0_Out.isNewZT0());
  ASSERT_TRUE(ZT0_Out.sharesZT0());
  ASSERT_TRUE(ZT0_Out.hasZT0State());
  ASSERT_TRUE(ZT0_Out.hasSharedZAInterface());
  ASSERT_FALSE(ZT0_Out.hasPrivateZAInterface());

  SA ZT0_InOut = SA(SA::encodeZT0State(SA::StateValue::InOut));
  ASSERT_TRUE(ZT0_InOut.isInOutZT0());
  ASSERT_FALSE(ZT0_InOut.isInZT0());
  ASSERT_FALSE(ZT0_InOut.isOutZT0());
  ASSERT_FALSE(ZT0_InOut.isPreservesZT0());
  ASSERT_FALSE(ZT0_InOut.isNewZT0());
  ASSERT_TRUE(ZT0_InOut.sharesZT0());
  ASSERT_TRUE(ZT0_InOut.hasZT0State());
  ASSERT_TRUE(ZT0_InOut.hasSharedZAInterface());
  ASSERT_FALSE(ZT0_InOut.hasPrivateZAInterface());

  SA ZT0_Preserved = SA(SA::encodeZT0State(SA::StateValue::Preserved));
  ASSERT_TRUE(ZT0_Preserved.isPreservesZT0());
  ASSERT_FALSE(ZT0_Preserved.isInZT0());
  ASSERT_FALSE(ZT0_Preserved.isOutZT0());
  ASSERT_FALSE(ZT0_Preserved.isInOutZT0());
  ASSERT_FALSE(ZT0_Preserved.isNewZT0());
  ASSERT_TRUE(ZT0_Preserved.sharesZT0());
  ASSERT_TRUE(ZT0_Preserved.hasZT0State());
  ASSERT_TRUE(ZT0_Preserved.hasSharedZAInterface());
  ASSERT_FALSE(ZT0_Preserved.hasPrivateZAInterface());

  SA ZT0_New = SA(SA::encodeZT0State(SA::StateValue::New));
  ASSERT_TRUE(ZT0_New.isNewZT0());
  ASSERT_FALSE(ZT0_New.isInZT0());
  ASSERT_FALSE(ZT0_New.isOutZT0());
  ASSERT_FALSE(ZT0_New.isInOutZT0());
  ASSERT_FALSE(ZT0_New.isPreservesZT0());
  ASSERT_FALSE(ZT0_New.sharesZT0());
  ASSERT_TRUE(ZT0_New.hasZT0State());
  ASSERT_FALSE(ZT0_New.hasSharedZAInterface());
  ASSERT_TRUE(ZT0_New.hasPrivateZAInterface());

  SA ZT0_Undef = SA(SA::ZT0_Undef | SA::encodeZT0State(SA::StateValue::New));
  ASSERT_TRUE(ZT0_Undef.isNewZT0());
  ASSERT_FALSE(ZT0_Undef.isInZT0());
  ASSERT_FALSE(ZT0_Undef.isOutZT0());
  ASSERT_FALSE(ZT0_Undef.isInOutZT0());
  ASSERT_FALSE(ZT0_Undef.isPreservesZT0());
  ASSERT_FALSE(ZT0_Undef.sharesZT0());
  ASSERT_TRUE(ZT0_Undef.hasZT0State());
  ASSERT_FALSE(ZT0_Undef.hasSharedZAInterface());
  ASSERT_TRUE(ZT0_Undef.hasPrivateZAInterface());
  ASSERT_TRUE(ZT0_Undef.isUndefZT0());

  ASSERT_FALSE(SA(SA::Normal).isInZT0());
  ASSERT_FALSE(SA(SA::Normal).isOutZT0());
  ASSERT_FALSE(SA(SA::Normal).isInOutZT0());
  ASSERT_FALSE(SA(SA::Normal).isPreservesZT0());
  ASSERT_FALSE(SA(SA::Normal).isNewZT0());
  ASSERT_FALSE(SA(SA::Normal).sharesZT0());
  ASSERT_FALSE(SA(SA::Normal).hasZT0State());
}

TEST(SMEAttributes, Transitions) {
  // Normal -> Normal
  ASSERT_FALSE(SA(SA::Normal).requiresSMChange(SA(SA::Normal)));
  ASSERT_FALSE(SA(SA::Normal).requiresPreservingZT0(SA(SA::Normal)));
  ASSERT_FALSE(SA(SA::Normal).requiresDisablingZABeforeCall(SA(SA::Normal)));
  ASSERT_FALSE(SA(SA::Normal).requiresEnablingZAAfterCall(SA(SA::Normal)));
  // Normal -> Normal + LocallyStreaming
  ASSERT_FALSE(SA(SA::Normal).requiresSMChange(SA(SA::Normal | SA::SM_Body)));

  // Normal -> Streaming
  ASSERT_TRUE(SA(SA::Normal).requiresSMChange(SA(SA::SM_Enabled)));
  // Normal -> Streaming + LocallyStreaming
  ASSERT_TRUE(
      SA(SA::Normal).requiresSMChange(SA(SA::SM_Enabled | SA::SM_Body)));

  // Normal -> Streaming-compatible
  ASSERT_FALSE(SA(SA::Normal).requiresSMChange(SA(SA::SM_Compatible)));
  // Normal -> Streaming-compatible + LocallyStreaming
  ASSERT_FALSE(
      SA(SA::Normal).requiresSMChange(SA(SA::SM_Compatible | SA::SM_Body)));

  // Streaming -> Normal
  ASSERT_TRUE(SA(SA::SM_Enabled).requiresSMChange(SA(SA::Normal)));
  // Streaming -> Normal + LocallyStreaming
  ASSERT_TRUE(
      SA(SA::SM_Enabled).requiresSMChange(SA(SA::Normal | SA::SM_Body)));

  // Streaming -> Streaming
  ASSERT_FALSE(SA(SA::SM_Enabled).requiresSMChange(SA(SA::SM_Enabled)));
  // Streaming -> Streaming + LocallyStreaming
  ASSERT_FALSE(
      SA(SA::SM_Enabled).requiresSMChange(SA(SA::SM_Enabled | SA::SM_Body)));

  // Streaming -> Streaming-compatible
  ASSERT_FALSE(SA(SA::SM_Enabled).requiresSMChange(SA(SA::SM_Compatible)));
  // Streaming -> Streaming-compatible + LocallyStreaming
  ASSERT_FALSE(
      SA(SA::SM_Enabled).requiresSMChange(SA(SA::SM_Compatible | SA::SM_Body)));

  // Streaming-compatible -> Normal
  ASSERT_TRUE(SA(SA::SM_Compatible).requiresSMChange(SA(SA::Normal)));
  ASSERT_TRUE(
      SA(SA::SM_Compatible).requiresSMChange(SA(SA::Normal | SA::SM_Body)));

  // Streaming-compatible -> Streaming
  ASSERT_TRUE(SA(SA::SM_Compatible).requiresSMChange(SA(SA::SM_Enabled)));
  // Streaming-compatible -> Streaming + LocallyStreaming
  ASSERT_TRUE(
      SA(SA::SM_Compatible).requiresSMChange(SA(SA::SM_Enabled | SA::SM_Body)));

  // Streaming-compatible -> Streaming-compatible
  ASSERT_FALSE(SA(SA::SM_Compatible).requiresSMChange(SA(SA::SM_Compatible)));
  // Streaming-compatible -> Streaming-compatible + LocallyStreaming
  ASSERT_FALSE(SA(SA::SM_Compatible)
                   .requiresSMChange(SA(SA::SM_Compatible | SA::SM_Body)));

  SA Private_ZA = SA(SA::Normal);
  SA ZA_Shared = SA(SA::encodeZAState(SA::StateValue::In));
  SA ZT0_Shared = SA(SA::encodeZT0State(SA::StateValue::In));
  SA ZA_ZT0_Shared = SA(SA::encodeZAState(SA::StateValue::In) |
                        SA::encodeZT0State(SA::StateValue::In));
  SA Undef_ZT0 = SA(SA::ZT0_Undef);

  // Shared ZA -> Private ZA Interface
  ASSERT_FALSE(ZA_Shared.requiresDisablingZABeforeCall(Private_ZA));
  ASSERT_TRUE(ZA_Shared.requiresEnablingZAAfterCall(Private_ZA));

  // Shared ZT0 -> Private ZA Interface
  ASSERT_TRUE(ZT0_Shared.requiresDisablingZABeforeCall(Private_ZA));
  ASSERT_TRUE(ZT0_Shared.requiresPreservingZT0(Private_ZA));
  ASSERT_TRUE(ZT0_Shared.requiresEnablingZAAfterCall(Private_ZA));

  // Shared Undef ZT0 -> Private ZA Interface
  // Note: "Undef ZT0" is a callsite attribute that means ZT0 is undefined at
  // point the of the call.
  ASSERT_TRUE(ZT0_Shared.requiresDisablingZABeforeCall(Undef_ZT0));
  ASSERT_FALSE(ZT0_Shared.requiresPreservingZT0(Undef_ZT0));
  ASSERT_TRUE(ZT0_Shared.requiresEnablingZAAfterCall(Undef_ZT0));

  // Shared ZA & ZT0 -> Private ZA Interface
  ASSERT_FALSE(ZA_ZT0_Shared.requiresDisablingZABeforeCall(Private_ZA));
  ASSERT_TRUE(ZA_ZT0_Shared.requiresPreservingZT0(Private_ZA));
  ASSERT_TRUE(ZA_ZT0_Shared.requiresEnablingZAAfterCall(Private_ZA));

  // Shared ZA -> Shared ZA Interface
  ASSERT_FALSE(ZA_Shared.requiresDisablingZABeforeCall(ZT0_Shared));
  ASSERT_FALSE(ZA_Shared.requiresEnablingZAAfterCall(ZT0_Shared));

  // Shared ZT0 -> Shared ZA Interface
  ASSERT_FALSE(ZT0_Shared.requiresDisablingZABeforeCall(ZT0_Shared));
  ASSERT_FALSE(ZT0_Shared.requiresPreservingZT0(ZT0_Shared));
  ASSERT_FALSE(ZT0_Shared.requiresEnablingZAAfterCall(ZT0_Shared));

  // Shared ZA & ZT0 -> Shared ZA Interface
  ASSERT_FALSE(ZA_ZT0_Shared.requiresDisablingZABeforeCall(ZT0_Shared));
  ASSERT_FALSE(ZA_ZT0_Shared.requiresPreservingZT0(ZT0_Shared));
  ASSERT_FALSE(ZA_ZT0_Shared.requiresEnablingZAAfterCall(ZT0_Shared));
}
