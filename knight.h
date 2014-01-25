#ifndef KNIGHT_H
#define KNIGHT_H
#pragma once


//* knight
//- centralization bonus
//- penalty for not being developed
//*/
int knight_pcsq[8][8] = {
	{-4,  -4,  -4,  -4,  -4,  -4,  -4,  -4},
	{-4,   0,   0,   0,   0,   0,   0,  -4},
	{-4,   0,   2,   2,   2,   2,   0,  -4},
	{-4,   0,   2,   4,   4,   2,   0,  -4},
	{-4,   0,   2,   4,   4,   2,   0,  -4},
	{-4,   0,   2,   2,   2,   2,   0,  -4},
	{-4,   0,   1,   1,   1,   1,   0,  -4},
	{-4,  -12, -4,  -4,  -4,  -4, -12,  -4}
};

//==== for getting Knight objects ====//
class Knight : public ChessPieces
{
public:

	//--- constructor for the class ---//
	Knight()
	{
		setWeight();
	}

	//----- this function search the board for possible moves of knight according to the laws of its motion -----//
	vector< pair<int, int> >  getPossibleMovesList(short x,short y,ChessBoard B)
	{
		pair <int,int> temp;
		V.clear();
		if ( y+2<8 )
		{
			if(x+1<8 &&(B.Board[x+1][y+2]==EMPTY || B.Board[x+1][y+2]->pieceColor!=B.Board[x][y]->pieceColor ))
			{
				temp.first=x+1;
				temp.second=y+2;
				V.push_back(temp);
			}
			if(x-1>=0 && ( B.Board[x-1][y+2]==EMPTY || B.Board[x-1][y+2]->pieceColor!=B.Board[x][y]->pieceColor ))
			{
				temp.first=x-1;
				temp.second=y+2;
				V.push_back(temp);
			}
		}
		if ( y-2>=0 )
		{
			if(x+1<8 && ( B.Board[x+1][y-2]==EMPTY || B.Board[x+1][y-2]->pieceColor!=B.Board[x][y]->pieceColor ))
			{
				temp.first=x+1;
				temp.second=y-2;
				V.push_back(temp);
			}
			if(x-1>=0  && ( B.Board[x-1][y-2]==EMPTY || B.Board[x-1][y-2]->pieceColor!=B.Board[x][y]->pieceColor))
			{
				temp.first=x-1;
				temp.second=y-2;
				V.push_back(temp);
			}
		}
		if ( x+2<8 )
		{
			if(y+1<8 && ( B.Board[x+2][y+1]==EMPTY || B.Board[x+2][y+1]->pieceColor!=B.Board[x][y]->pieceColor))
			{
				temp.first=x+2;
				temp.second=y+1;
				V.push_back(temp);
			}
			if(y-1>=0 && ( B.Board[x+2][y-1]==EMPTY || B.Board[x+2][y-1]->pieceColor!=B.Board[x][y]->pieceColor))
			{
				temp.first=x+2;
				temp.second=y-1;
				V.push_back(temp);
			}
		}
		if ( x-2>=0 )
		{
			if(y+1<8 && ( B.Board[x-2][y+1]==EMPTY || B.Board[x-2][y+1]->pieceColor!=B.Board[x][y]->pieceColor) )
			{
				temp.first=x-2;
				temp.second=y+1;
				V.push_back(temp);
			}
			if(y-1>=0 && (  B.Board[x-2][y-1]==EMPTY || B.Board[x-2][y-1]->pieceColor!=B.Board[x][y]->pieceColor) )
			{
				temp.first=x-2;
				temp.second=y-1;
				V.push_back(temp);
			}
		}
		return V;
	}

	//---- this string carry the char representing the pieace ( used in fennotation , loading game & others )
	string virtual tostring()
	{
		return "H";
	}

	//----- gives every position on the board a value for the move of this piece -----//
	void setBonusPosition()
	{
		if(pieceColor==WHITE)
			for(int i=0;i<8;i++)
				for(int j=0;j<8;j++)	
					bonusPosition[i][j]=knight_pcsq[i][j];	
		else for(int i=0;i<8;i++)
			for(int j=0;j<8;j++)
				bonusPosition[i][j]=knight_pcsq[7-i][j];

	}

	//---- piece estimated value ----//
	void setWeight()
	{
		Weight=325;
	}

	//----- sets the sfml image related to this piece -----//
	void setImage()
	{
		if(pieceColor==WHITE)
		{
			pieceImage.loadFromFile("Images//Chess//"+Theme+"//Pieces//WhiteKnight.png");
			pieceSprite.setTexture(pieceImage);
		}
		else
		{
			pieceImage.loadFromFile("Images//Chess//"+Theme+"//Pieces//BlackKnight.png");
			pieceSprite.setTexture(pieceImage);
		}
	}
};

#endif