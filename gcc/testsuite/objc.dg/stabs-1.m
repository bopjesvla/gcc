/* Check if the final SO STABS record goes into the .text section.  */
/* Contributed by Ziemowit Laski <zlaski@apple.com> */

/* { dg-do compile } */
/* { dg-skip-if "No stabs" { mmix-*-* *-*-aix* alpha*-*-* ia64-*-* } { "*" } { "" } } */
/* { dg-options "-gstabs" } */

@interface MyClass
+ newWithArg: arg;
@end

@implementation MyClass
+ newWithArg: arg
{
}
@end

/* { dg-final { scan-assembler ".text\"?\n\t.stabs.*100,0,0,(\\.)?L?Letext\[0-9\]*\n(\\.)?L?Letext" } } */
