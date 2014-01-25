#ifndef QUEEN_H
#define QUEEN_H
#pragma once
#include "rook.h"
#include "bishop.h"

//* queen
//- small bonus for centralization
//- penalty for staying on the 1st rank, possibly blocking rooks
//*/
int queen_pcsq[8][8] = {
	{ 0,   0,   0,   0,   0,   0,   0,   0},
	{ 0,   0,   1,   1,   1,   1,   0,   0},
	{ 0,   0,   1,   2,   2,   1,   0,   0},
	{ 0,   0,   2,   3,   3,   2,   0,   0},
	{ 0,   0,   2,   3,   3,   2,   0,   0},
	{ 0,   0,   1,   2,   2,   1,   0,   0},
	{ 0,   0,   1,   1,   1,   1,   0,   0},
	{-5,  -5,  -5,  -5,  -5,  -5,  -5,  -5}
};

//==== for getting Queen objects ====//
class Queen : public ChessPieces
{
public:

	//--- constructor for the class ---//
	Queen()
	{setWeight();}

	//----- this function search the board for possible moves of queen using the bishop & rook laws of motion -----//
	vector< pair<int,int> > getPossibleMovesList(short x, short y, ChessBoard B)
	{
		V.clear();
		Bishop Bi;
		Rook Ro;
		V=Bi.getPossibleMovesList(x,y,B);
		vector< pair <int,int> > N;
		N=Ro.getPossibleMovesList(x,y,B);
		V.insert(V.end(),N.begin(),N.end());
		return V;
	}

	//---- this string carry the char representing the pieace ( used in fennotation , loading game & others )
	string virtual tostring()
	{return "Q";}

	//----- gives every position on the board a value for the move of this piece -----//
	void setBonusPosition()
	{
		if(pieceColor==WHITE)
			for(int i=0;i<8;i++)
				for(int j=0;j<8;j++)	
					bonusPosition[i][j]=queen_pcsq[i][j];	
		else for(int i=0;i<8;i++)
			for(int j=0;j<8;j++)
				bonusPosition[i][j]=queen_pcsq[7-i][j];

	}

	//---- piece estimated value ----//
	void setWeight()
	{Weight=975;}

	//----- sets the sfml image related to this piece -----//
	void setImage()
	{
		if(pieceColor==WHITE)
		{
			pieceImage.loadFromFile("Images//Chess//"+Theme+"//Pieces//WhiteQueen.png");
			pieceSprite.setTexture(pieceImage);
		}
		else
		{
			pieceImage.loadFromFile("Images//Chess//"+Theme+"//Pieces//BlackQueen.png");
			pieceSprite.setTexture(pieceImage);
		}
	}
};

#endif