#include "errors.h"

#pragma once

// Basics

#define nil 0
typedef enum { false, true } bool;

// Numeric types

#define isize size_t
#define itime time_t

#define i8 signed char
#define u8 unsigned char

#define i16 short int
#define u16 unsigned short int

#define i32 int
#define u32 unsigned int

#define i64 long int
#define u64 unsigned long int

#define f32 float
#define f64 double

// Errors

#define error i32
