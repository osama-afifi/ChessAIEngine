#ifndef CONNCECT41_H
#define CONNCECT41_H
#pragma once

#include "include1.h"

//===== for types of piece played =====//
enum c4type {C,R,Y};
// C-> EMPTY SPACE


//===== class representing objects of Red & Yellow =====//
class c4Pieces
{	
public:
	c4type cType;
	c4Pieces():cType(C)
	{}
};

//===== class representing Board of connect4 =====//
class c4Board
{
public:
	c4Pieces game[6][7]; 
};

#endif