// 
//	Author : vaibhavs@flux.utah.edu
//	Description: common header file for types and other header files 
//


#ifndef TYPES_H
#define TYPES_H

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>


//
//	typedefs
//
typedef long		_long;
typedef int		_int;
typedef char 	        _byte;
typedef bool 		_bool;
typedef unsigned int 	_uint;
typedef unsigned long	_ulong;
typedef const char*	_string;

const long size_power2 = 131072;
// this corresponds to the number of index which bloated bloom will provide
// and since we are using 4 bit unit for storage 
// a normal bloom would have 4 times as much indexes ( or m )
const _long Index_BB =/* 524288-1*/size_power2-1;
const _long Index_B = size_power2*4 -1;
const _int window_size = 10;
const _int num_hash = 8;
#define SORTED

typedef struct _node{
	_long hValue;
	_uint count;
	struct _node * next;
}node;

#endif
