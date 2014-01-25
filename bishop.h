#ifndef BISHOP_H
#define BISHOP_H
#pragma once


//* bishop
//- centralization bonus
//- penalty for not being developed
//- good squares on the own half of the board
//*/
int bishop_pcsq[8][8] = {
	{ -4,  -4,  -4,  -4,  -4,  -4,  -4,  -4},
	{ -4,   0,   0,   0,   0,   0,   0,  -4},
	{ -4,   0,   2,   2,   2,   2,   0,  -4},
	{ -4,   0,   2,   4,   4,   2,   0,  -4},
	{ -4,   0,   2,   4,   4,   2,   0,  -4},
	{ -4,   1,   2,   2,   2,   2,   1,  -4},
	{ -4,   2,   1,   1,   1,   1,   2,  -4},
	{ -4,  -4, -12,  -4,  -4, -12,  -4,  -4}
};

//==== for getting Bishop objects ====//
class Bishop : public ChessPieces
{
public:

	//--- constructor for the class ---//
	Bishop()
	{
		setWeight();
	}

	//----- this function search the board for possible moves of bishop according to the laws of its motion -----//
	vector< pair<int,int> >  getPossibleMovesList(short x,short y,ChessBoard B)
	{
		pair <int,int> temp;
		V.clear();
		//south east
		for(int i=x+1,j=y-1 ; i<8 && j>=0 ; j--, i++)
		{
			if(B.Board[i][j] == EMPTY || B.Board[i][j]->pieceColor != B.Board[x][y]->pieceColor)
			{
				if(B.Board[i][j] == EMPTY)
				{
					temp.first=i;
					temp.second=j;
					V.push_back(temp);
				}
				else 
				{
					temp.first=i;
					temp.second=j;
					V.push_back(temp);
					break;
				}
			}
			else break;

		}
		//north west
		for(int j=y+1, i=x-1 ; j<8 && i>=0 ; i-- ,j++ )
		{
			if(B.Board[i][j] == EMPTY || B.Board[i][j]->pieceColor != B.Board[x][y]->pieceColor)
			{
				if(B.Board[i][j] == EMPTY)
				{
					temp.first=i;
					temp.second=j;
					V.push_back(temp);
				}
				else
				{
					temp.first=i;
					temp.second=j;
					V.push_back(temp);
					break;
				}
			}
			else break;

		}
		// north east
		for(int j=y+1 , i=x+1 ; i<8 && j<8 ; j++ , i++)
		{
			if(B.Board[i][j] == EMPTY || B.Board[i][j]->pieceColor != B.Board[x][y]->pieceColor )
			{
				if(B.Board[i][j] == EMPTY)
				{
					temp.first=i;
					temp.second=j;
					V.push_back(temp);
				}
				else 
				{
					temp.first=i;
					temp.second=j;
					V.push_back(temp);
					break;
				}
			}
			else break;
		}
		//south west
		for(int j=y-1 , i=x-1 ; i>=0 && j>=0 ; j-- , i--)
		{
			if(B.Board[i][j] == EMPTY || B.Board[i][j]->pieceColor != B.Board[x][y]->pieceColor)
			{
				if(B.Board[i][j] == EMPTY)
				{
					temp.first=i;
					temp.second=j;
					V.push_back(temp);
				}
				else 
				{
					temp.first=i;
					temp.second=j;
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
	{
		return "B";
	}

	//----- gives every position on the board a value for the move of this piece -----//
	void setBonusPosition()
	{
		if(pieceColor==WHITE)
			for(int i=0;i<8;i++)
				for(int j=0;j<8;j++)	
					bonusPosition[i][j]=bishop_pcsq[i][j];	
		else for(int i=0;i<8;i++)
			for(int j=0;j<8;j++)
				bonusPosition[i][j]=bishop_pcsq[7-i][j];

	}

	//---- piece estimated value ----//
	void setWeight()
	{
		Weight=350;
	}

	//----- sets the sfml image related to this piece -----//
	void setImage()
	{
		if(pieceColor==WHITE)
		{
			pieceImage.loadFromFile("Images//Chess//"+Theme+"//Pieces//WhiteBishop.png");
			pieceSprite.setTexture(pieceImage);
		}
		else
		{
			pieceImage.loadFromFile("Images//Chess//"+Theme+"//Pieces//BlackBishop.png");
			pieceSprite.setTexture(pieceImage);
		}
	}
};
#endif