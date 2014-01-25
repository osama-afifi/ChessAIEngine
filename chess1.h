#ifndef CHESS1_H
#define CHESS1_H
#pragma once
#include "include1.h"


enum color {WHITE,BLACK};//--- for pieces colors
enum Mode {Human,Computer,None};//--- in saving game to know the saved game is for 1 or 2 players
Mode PlayMode;

string Theme = "Funny";

class ChessPieces;

//------  used in getting possible moves of knight -----//
int HORSE_ATTACK_X[]={-1,-1,1,1,2,2,-2,-2};
int HORSE_ATTACK_Y[]={2,-2,2,-2,1,-1,1,-1};

//------ used in getting possible moves of king -----//
int KING_ATTACK_X[]={-1,-1,-1,0,0,1,1,1};
int KING_ATTACK_Y[]={-1,0,1,1,-1,-1,0,1};


//---- class formig a chess board object ----//
class ChessBoard
{
public:
	ChessPieces* Board[8][8];
};

//---- the base class for all pieces of chess ----//
class ChessPieces
{

public:
	bool isMoved;//-- to know if castling can takeplace
	int Weight;//--- used in evaluation

	//---- Graphics pictures ----//
	sf::Texture pieceImage;
	sf::Sprite pieceSprite;

	//---- gives every place on the board avalue for the existance of this peace ----//
	int bonusPosition[8][8];

	vector < pair<int,int> > V;

	//---- carry piece color---//
	color pieceColor;

	//---- carry possible moves of the piece ----// 
	vector < pair<int,int> > virtual getPossibleMovesList(short x, short y,ChessBoard B)=0;

	//---- constructor of the class ----//
	ChessPieces(): pieceColor(WHITE) , Weight(500) , isMoved (false)
	{}

	//---- change the value of the ismoved variable ----//
	void setMoved(bool b)
	{
	isMoved=b;
	}

	//---- this string carry the char representing the pieace ( used in fennotation , loading game & others )
	string virtual tostring()=0;

	//----- gives every position on the board a value for the move of this piece -----//
	void virtual setBonusPosition()=0;

	//---- piece estimated value ----//
	void virtual setWeight()=0;

	//----- sets the sfml image related to this piece -----//
	void virtual setImage()=0;
};

#endif 