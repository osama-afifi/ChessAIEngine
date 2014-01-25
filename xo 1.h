#ifndef XO1_H
#define XO1_H
#pragma once

#include "include1.h"


//===== for types of piece played =====//
enum type {N,X,O};
// N-> EMPTY SPACE

//===== class representing objects of X & O =====//
class xoPieces
{	
public:
	type pieceType;

	//=== construct for the class ===//
	xoPieces(): pieceType(N)
	{}
};


//===== class representing Board of XO =====//
class xoBoard
{
public:
	xoPieces arr[9]; 
};

#endif