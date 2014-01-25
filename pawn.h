#ifndef PAWN_H
#define PAWN_H
#pragma once
//pawn
//- small bonus for standing on a3/h3
//- penalty for d/e pawns on their initial squares
//- slight centralization bonus
//*/
int pawn_pcsq[8][8] = {
	{ 0,   0,   0,   0,   0,   0,   0,   0},
	{ 0,   0,   1,   1,   1,   1,   0,   0},
	{ 0,   0,   1,   2,   2,   1,   0,   0},
	{ 0,   0,   2,   4,   4,   2,   0,   0},
	{ 0,   0,   2,   8,   8,   2,   0,   0},
	{ 4,   0,   1,   4,   4,   1,   0,   4},
	{ 0,   0,   1, -12, -12,   1,   0,   0},
	{ 0,   0,   0,   0,   0,   0,   0,   0}
};

//==== for getting Pawn objects ====//
class Pawn : public ChessPieces
{
public:

	//--- constructor for the class ---//
	Pawn()
	{setWeight();}

	//----- this function search the board for possible moves of pawn according to the laws of its motion -----//
	vector< pair<int,int> > getPossibleMovesList(short x,short y,ChessBoard B)
	{
		pair <int,int> temp;
		V.clear();
		if ( B.Board[x][y]->pieceColor==BLACK  )
		{
			if ( x==1 &&  B.Board[x+1][y]==EMPTY && B.Board[x+2][y]==EMPTY)
			{
				temp.first=x+2;
				temp.second=y;
				V.push_back(temp);
			}
			if ( x<7 && B.Board[x+1][y]==EMPTY )
			{
				temp.first=x+1;
				temp.second=y;
				V.push_back(temp);
			}
			if (  y<7 && x<7 && B.Board[x+1][y+1]!=EMPTY && B.Board[x+1][y+1]->pieceColor==WHITE )
			{
				temp.first=x+1;
				temp.second=y+1;
				V.push_back(temp);
			}
			if (y>0 && x<7 && B.Board[x+1][y-1]!=EMPTY  && B.Board[x+1][y-1]->pieceColor==WHITE  )
			{ 
				temp.first=x+1;
				temp.second=y-1;
				V.push_back(temp);
			}
		}
		else
		{
			if ( x==6 && B.Board[x-1][y]==EMPTY && B.Board[x-2][y]==EMPTY)
			{
				temp.first=x-2;
				temp.second=y;
				V.push_back(temp);
			}
			if (  x>0 && B.Board[x-1][y]==EMPTY )
			{
				temp.first=x-1;
				temp.second=y;
				V.push_back(temp);
			}
			if ( x>0 && y<7 && B.Board[x-1][y+1]!=EMPTY && B.Board[x-1][y+1]->pieceColor==BLACK )
			{
				temp.first=x-1;
				temp.second=y+1;
				V.push_back(temp);
			}
			if ( y>0 && x>0 && B.Board[x-1][y-1]!=EMPTY && B.Board[x-1][y-1]->pieceColor==BLACK )
			{
				temp.first=x-1;
				temp.second=y-1;
				V.push_back(temp);
			}
		}
		return V;
	}

	//---- this string carry the char representing the pieace ( used in fennotation , loading game & others )
	string virtual tostring()
	{return "P";}

	//----- gives every position on the board a value for the move of this piece -----//
	void setBonusPosition()
	{
		if(pieceColor==WHITE)
			for(int i=0;i<8;i++)
				for(int j=0;j<8;j++)	
					bonusPosition[i][j]=pawn_pcsq[i][j];	
		else for(int i=0;i<8;i++)
			for(int j=0;j<8;j++)
				bonusPosition[i][j]=pawn_pcsq[7-i][j];

	}

	//---- piece estimated value ----//
	void setWeight()
	{Weight=100;}

	//----- sets the sfml image related to this piece -----//
	void setImage()
	{
		if(pieceColor==WHITE)
		{
			pieceImage.loadFromFile("Images//Chess//"+Theme+"//Pieces//WhitePawn.png");
			pieceSprite.setTexture(pieceImage);
		}
		else
		{
			pieceImage.loadFromFile("Images//Chess//"+Theme+"//Pieces//BlackPawn.png");
			pieceSprite.setTexture(pieceImage);
		}
	}
};
#endif
