#ifndef KING_H
#define KING_H
#pragma once
#include "chess1.h"


int king_pcsq[8][8] = {
	{-40, -40, -40, -40, -40, -40, -40, -40},
	{-40, -40, -40, -40, -40, -40, -40, -40},
	{-40, -40, -40, -40, -40, -40, -40, -40},
	{-40, -40, -40, -40, -40, -40, -40, -40},
	{-40, -40, -40, -40, -40, -40, -40, -40},
	{-40, -40, -40, -40, -40, -40, -40, -40},
	{-20, -20, -20, -20, -20, -20, -20, -20},
	{  0,  20,  40, -30,   0, -20,  40,  20}
};

//==== for getting King objects ====//
class King : public ChessPieces
{
public:

	pair <int ,int > kingPosition;

	//--- constructor for the class ---//
	King()
	{setWeight();}

	void updatePosition(int x , int y)
	{
		kingPosition.first=x;
		kingPosition.second=y;
	}

	//----- this function search the board for possible moves of king according to the laws of its motion -----//
	vector< pair<int, int> > getPossibleMovesList(short x,short y,ChessBoard B)
	{
		pair<int,int> temp;
		V.clear();
		updatePosition(x,y);
		//Up
		if( x<7  && (B.Board[x+1][y] ==EMPTY || B.Board[x+1][y]->pieceColor !=  B.Board[x][y]->pieceColor ) )
		{
			temp.first=x+1;
			temp.second=y;
			V.push_back(temp);
		}
		//Down
		if( x>0 &&  (B.Board[x-1][y] ==EMPTY || B.Board[x-1][y]->pieceColor != B.Board[x][y]->pieceColor))
		{
			temp.first=x-1;
			temp.second=y;
			V.push_back(temp);
		}
		// Right
		if( y>0 && (B.Board[x][y-1]==EMPTY || B.Board[x][y-1]->pieceColor != B.Board[x][y]->pieceColor ))
		{
			temp.first=x;
			temp.second=y-1;
			V.push_back(temp);
		}
		//Left
		if( y<7 && (B.Board[x][y+1] ==EMPTY || B.Board[x][y+1]->pieceColor!=B.Board[x][y]->pieceColor))
		{
			temp.first=x;
			temp.second=y+1;
			V.push_back(temp);
		}
		//Up left
		if( x<7 && y<7 && (B.Board[x+1][y+1] ==EMPTY || B.Board[x+1][y+1]->pieceColor!=B.Board[x][y]->pieceColor ))
		{
			temp.first=x+1;
			temp.second=y+1;
			V.push_back(temp);

		}
		//Down left
		if( x>0 && y<7 &&  (B.Board[x-1][y+1] ==EMPTY || B.Board[x-1][y+1]->pieceColor!=B.Board[x][y]->pieceColor ))
		{
			temp.first=x-1;
			temp.second=y+1;
			V.push_back(temp);
		}
		//Up Right
		if( x<7 && y>0 &&( B.Board[x+1][y-1] ==EMPTY || B.Board[x+1][y-1]->pieceColor!=B.Board[x][y]->pieceColor))
		{
			temp.first=x+1;
			temp.second=y-1;
			V.push_back(temp);
		}	
		//Down Right
		if( x>0 && y>0 && (B.Board[x-1][y-1] ==EMPTY ||  B.Board[x-1][y-1]->pieceColor!=B.Board[x][y]->pieceColor))
		{
			temp.first=x-1;
			temp.second=y-1;
			V.push_back(temp);
		}	
		return V;
	}

	//---- this string carry the char representing the pieace ( used in fennotation , loading game & others )
	string tostring()
	{return "K";}

	//----- gives every position on the board a value for the move of this piece -----//
	void setBonusPosition()
	{
		if(pieceColor==WHITE)
			for(int i=0;i<8;i++)
				for(int j=0;j<8;j++)	
					bonusPosition[i][j]=king_pcsq[i][j];
		else for(int i=0;i<8;i++)
			for(int j=0;j<8;j++)	
				bonusPosition[i][j]=king_pcsq[7-i][j];
	}

	//---- piece estimated value ----//
	void setWeight()
	{
		Weight=9999999;
	}

	//----- sets the sfml image related to this piece -----//
	void setImage()
	{
		if(pieceColor==WHITE)
		{
			pieceImage.loadFromFile("Images//Chess//"+Theme+"//Pieces//WhiteKing.png");
			pieceSprite.setTexture(pieceImage);
		}
		else
		{
			pieceImage.loadFromFile("Images//Chess//"+Theme+"//Pieces//BlackKing.png");
			pieceSprite.setTexture(pieceImage);
		}
	}
};

#endif