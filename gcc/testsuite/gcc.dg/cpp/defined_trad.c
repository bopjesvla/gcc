/* Copyright (C) 2000 Free Software Foundation, Inc.  */

/* { dg-do preprocess } */
/* { dg-options "-traditional" } */

/* Tests tradcpp0 with defined.  */

/* Source: Glibc, 11 Dec 2000.  */

#if defined REGPARMS
#error REGPARMS should not be defined
#endif

#define REGPARMS 1
#if !defined REGPARMS
#error REGPARMS should be defined
#endif
