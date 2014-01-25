#ifndef ROOK_H
#define ROOK_H
#pragma once


//*  rook
//- bonus for 7th and 8th ranks
//- penalty for a/h columns
//- small centralization bonus
//*/
int rook_pcsq[8][8] = {
	{  5,   5,   5,   5,   5,   5,   5,   5},
	{ 20,  20,  20,  20,  20,  20,  20,  20},
	{ -5,   0,   0,   0,   0,   0,   0,  -5},
	{ -5,   0,   0,   0,   0,   0,   0,  -5},
	{ -5,   0,   0,   0,   0,   0,   0,  -5},
	{ -5,   0,   0,   0,   0,   0,   0,  -5},
	{ -5,   0,   0,   0,   0,   0,   0,  -5},
	{  0,   0,   0,   2,   2,   0,   0,   0 }
};

//==== for getting Rook objects ====//
class Rook : public ChessPieces
{
public:

	//--- constructor for the class ---//
	Rook()
	{setWeight();}

	//----- this function search the board for possible moves of rook according to the laws of its motion -----//
	vector< pair<int,int> >  getPossibleMovesList(short x,short y,ChessBoard B)
	{
		pair <int,int> temp;
		V.clear();
		//Right
		for(int i=y+1 ; i<8 ; i++)
		{
			if(B.Board[x][i]==EMPTY || B.Board[x][i]->pieceColor!=B.Board[x][y]->pieceColor)
			{
				if(B.Board[x][i]==EMPTY)
				{
					temp.first=x;
					temp.second=i;
					V.push_back(temp);
				}
				else 
				{
					temp.first=x;
					temp.second=i;
					V.push_back(temp);
					break;
				}
			}
			else break;

		}
		//Left
		for(int i=y-1 ; i>=0 ; i--)
		{
			if(B.Board[x][i]==EMPTY || B.Board[x][i]->pieceColor!=B.Board[x][y]->pieceColor)
			{
				if(B.Board[x][i]==EMPTY)
				{
					temp.first=x;
					temp.second=i;
					V.push_back(temp);
				}
				else 
				{
					temp.first=x;
					temp.second=i;
					V.push_back(temp);
					break;
				}
			}
			else break;

		}
		// Up
		for(int i=x+1; i<8 ;i++)
		{
			if(B.Board[i][y]==EMPTY || B.Board[i][y]->pieceColor!=B.Board[x][y]->pieceColor)
			{
				if(B.Board[i][y]==EMPTY)
				{
					temp.first=i;
					temp.second=y;
					V.push_back(temp);
				}
				else 
				{
					temp.first=i;
					temp.second=y;
					V.push_back(temp);
					break;
				}
			}
			else break;

		}
		//Down
		for(int i=x-1; i>=0 ;i--)
		{
			if(B.Board[i][y]==EMPTY || B.Board[i][y]->pieceColor!=B.Board[x][y]->pieceColor)
			{
				if(B.Board[i][y]==EMPTY)
				{
					temp.first=i;
					temp.second=y;
					V.push_back(temp);
				}
				else 
				{
					temp.first=i;
					temp.second=y;
					V.push_back(temp);
					break;
				}
			}
			else break;

		}
		return V;
	}

	//---- this string carry the char representing the pieace ( used in fennotation , loading game & others )
	string virtual tostring()
	{return "R";}

	//----- gives every position on the board a value for the move of this piece -----//
	void setBonusPosition()
	{
		if(pieceColor==WHITE)
			for(int i=0;i<8;i++)
				for(int j=0;j<8;j++)	
					bonusPosition[i][j]=rook_pcsq[i][j];	
		else for(int i=0;i<8;i++)
			for(int j=0;j<8;j++)
				bonusPosition[i][j]=rook_pcsq[7-i][7-j];

	}

	//---- piece estimated value ----//
	void setWeight()
	{Weight=500;}

	//----- sets the sfml image related to this piece -----//
	void setImage()
	{
		if(pieceColor==WHITE)
		{
			pieceImage.loadFromFile("Images//Chess//"+Theme+"//Pieces//WhiteRook.png");
			pieceSprite.setTexture(pieceImage);
		}
		else
		{
			pieceImage.loadFromFile("Images//Chess//"+Theme+"//Pieces//BlackRook.png");
			pieceSprite.setTexture(pieceImage);
		}
	}
}; 

#endif