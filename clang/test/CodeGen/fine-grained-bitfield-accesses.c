// RUN: %clang -ffine-grained-bitfield-accesses -S -emit-llvm -o - %s | FileCheck %s
// CHECK: define{{.*}} @g(){{.*}} #[[GATTR:[0-9]+]] {
// CHECK: declare{{.*}} void @f(ptr noundef){{.*}} #[[FATTR:[0-9]+]]
// CHECK: attributes #[[GATTR]] = {{.*}} fine_grained_bitfields {{.*}}
// CHECK: attributes #[[FATTR]] = {{.*}} fine_grained_bitfields {{.*}}
//
// Verify that the clang fine-grained-bitfield-accesses option adds the IR
// function attribute fine_grained_bitfields.
struct X {
  int a : 8;
  int b : 24;
};

void f(struct X*);

int g() {
  struct X x;
  x.a = 10;
  f(&x);
  return x.a;
}
