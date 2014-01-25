#ifndef CONNCECT42_H
#define CONNCECT42_H
#pragma once

#include "connect4 1.h"
#include "vmode.h"


//====== class controling connect4 game =======// 
class c4Game
{
private :
	int SearchDepth;//== carry number representing depth of searching engine ( easy - medium - hard )
	vector<pair<int,int> > Turns;// ==carry the played games ( used in undo)
	pair < int,int > temp;
public :
	c4Pieces  c4_C;// piece objects
	c4Board c4;// board object
	int arr[7];//carry the horizontal coordinate of board
	int Player;

	//====== Graphics ======//
	sf::Sprite Board[6][7];
	sf::Sprite Grid;
	sf::Sprite S_BG;

	sf::Texture T_Easy;
	sf::Texture T_Moderate;
	sf::Texture T_Hard;
	sf::Texture T_Yes;
	sf::Texture T_No;

	sf::Sprite S_yWin;
	sf::Sprite S_rWin;
	sf::Sprite S_Draw;
	sf::Texture T_yWin;
	sf::Texture T_rWin;
	sf::Texture T_Draw;

	sf::Texture T_1; 
	sf::Texture T_2;

	sf::Sprite S_1; 
	sf::Sprite S_2;
	sf::Sprite S_E;

	sf::Texture T_E;
	sf::Texture T_Board;
	sf::Texture T_BG;

	sf::Text  Menu[6];

	sf::Texture T_Menu_BG;
	sf::Sprite S_Menu_BG;

	//---- Sounds ----//
	sf::SoundBuffer B_Move1;
	sf::Sound Sound_Move1;
	sf::SoundBuffer B_Error;
	sf::Sound Sound_Error;

	//=== constructor for the class ===//
	c4Game() : Player(Player1) , SearchDepth(5)
	{}

	//==== check if the mouse click is on the right pictures of windows ====//
	bool inRangeXY(int x,int y , float r1x , float r1y , float r2x , float r2y)
	{
		if(x>=r1x && x<=r2x /*&& y>=r1y && y<=r2y */ )
			return true;
		return false;
	}

	//===== change mouse coordinates to board coordinates =====//
	int cord_index_x( float x_cord)
	{
		return ((x_cord-430)/72);

	}
	int cord_index_y( float y_cord)
	{
		return ((y_cord-180)/61);

	}
	int Menu_Cord_Index(int y)
	{
		return ((float)(float(y-99)/165.0)*4.0)+0.5;
	}


	//===== change board coordinates to mouse coordinates =====//
	float index_cord_x( int x_index)
	{
		return (75*(x_index))+430;

	}
	float index_cord_y( int y_index)
	{
		return (63*(6-y_index))+80;

	}
	int Menu_Index_Cord(int y)
	{
		return (40*(y))+200;
	}

	//==== check if the mouse click is in the board range ====//
	bool inBoardRange(int x,int y)
	{
		if(cord_index_x(x)>=0 && cord_index_x(x)<7 && cord_index_y(y)>=0 && cord_index_y(y)<6  )
			return true;
		return false;
	}

	//==== check if the mouse click is in the menu range ====//
	bool Menu_Range(int x, int y)
	{
		if( y>100 && y<265 && x>95 && x<330 )return true;
		return false;
	}

	//==== show the pop message using sfml library ====//
	void YwinPopMessage()
	{
		sf::VideoMode Ywin(300,300,32);
		sf::RenderWindow Window(Ywin,"Yellow wins",sf::Style::Close);
		S_yWin.setScale((float)Ywin.width/(float)T_yWin.getSize().x,(float)Ywin.height/(float)T_yWin.getSize().y);
		while(Window.isOpen())
		{
			sf::Event Ywin;
			while(Window.pollEvent(Ywin))
			{
				//Window.clear(sf::Color(255,255,255));
				Window.draw(S_yWin);
				Window.display();
				if(Ywin.type==Ywin.MouseButtonPressed || Ywin.type== sf::Event::LostFocus || (Ywin.type==sf::Event::Closed))
				{
					Window.close();
					return;
				}
			}
		}
	}
	void RwinPopMessage()
	{
		sf::VideoMode Rwin(300,300,32);
		sf::RenderWindow Window(Rwin,"Red wins",sf::Style::Close);
		S_rWin.setScale((float)Rwin.width/(float)T_rWin.getSize().x,(float)Rwin.height/(float)T_rWin.getSize().y);
		while(Window.isOpen())
		{
			sf::Event Rwin;
			while(Window.pollEvent(Rwin))
			{
				//Window.clear(sf::Color(255,255,255));
				Window.draw(S_rWin);
				Window.display();
				if(Rwin.type==Rwin.MouseButtonPressed || Rwin.type== sf::Event::LostFocus || (Rwin.type==sf::Event::Closed))
				{
					Window.close();
					return;
				}
			}

		}
	}
	void DrawPopMessage()
	{
		sf::VideoMode ryDraw(300,300,32);
		sf::RenderWindow Window(ryDraw,"Draw Game",sf::Style::Close);
		S_Draw.setScale((float)ryDraw.width/(float)T_Draw.getSize().x,(float)ryDraw.height/(float)T_Draw.getSize().y);
		while(Window.isOpen())
		{
			sf::Event ryDraw;
			while(Window.pollEvent(ryDraw))
			{
				//Window.clear(sf::Color(255,255,255));
				Window.draw(S_Draw);
				Window.display();
				if(ryDraw.type==ryDraw.MouseButtonPressed || ryDraw.type== sf::Event::LostFocus || (ryDraw.type==sf::Event::Closed))
				{
					Window.close();
					return;
				}
			}

		}
	}
	int PlayAgainPopMessage()
	{
		sf::VideoMode Ranking(400,120,32);
		sf::RenderWindow Window(Ranking,"Play Again ?",sf::Style::Titlebar);
		while(Window.isOpen())
		{
			sf::Event ESure;
			sf::Mouse Mouse;

			sf::Text Sure;
			Sure.setString("Play Again ?");
			Sure.setColor(sf::Color(0,0,0));
			Sure.setPosition(120,0);
			sf::Sprite Yes;
			Yes.setTexture(T_Yes);
			Yes.setPosition(60+(float)0.0*400/2.0,30);
			sf::Sprite No;
			No.setTexture(T_No);
			No.setPosition(60+(float)1.0*400/2.0,30);

			Window.clear();
			Window.clear(sf::Color(255,255,255));
			Window.draw(Yes);
			Window.draw(No);
			Window.draw(Sure);

			Window.display();

			while(Window.pollEvent(ESure))
			{
				if (ESure.type == sf::Event::Closed)
					Window.close();
				int x=Mouse.getPosition().x;
				if (ESure.type == sf::Event::MouseButtonPressed)
				{
					if(inRangeXY(x,0,490+(float)0*400/2.0,0,490+(float)1.0*400/2.0,0))
						return 1;
					else if(inRangeXY(x,0,490+(float)1.0*400/2.0,0,490+(float)2.0*400/2.0,0))
						return 2;

				}


				Window.clear();
				Window.clear(sf::Color(255,255,255));
				Window.draw(Yes);
				Window.draw(No);
				Window.draw(Sure);

				Window.display();

			}

		}
	}
	int SurePopMessage()
	{
		sf::VideoMode Ranking(400,120,32);
		sf::RenderWindow Window(Ranking,"Are You Sure ?",sf::Style::Titlebar);
		while(Window.isOpen())
		{
			sf::Event ESure;
			sf::Mouse Mouse;

			sf::Text Sure;
			Sure.setString("Are you Sure ?");
			Sure.setColor(sf::Color(0,0,0));
			Sure.setPosition(120,0);
			sf::Sprite Yes;
			Yes.setTexture(T_Yes);
			Yes.setPosition(60+(float)0.0*400/2.0,30);
			sf::Sprite No;
			No.setTexture(T_No);
			No.setPosition(60+(float)1.0*400/2.0,30);

			Window.clear();
			Window.clear(sf::Color(255,255,255));
			Window.draw(Yes);
			Window.draw(No);
			Window.draw(Sure);

			Window.display();

			while(Window.pollEvent(ESure))
			{
				if (ESure.type == sf::Event::Closed)
					Window.close();
				int x=Mouse.getPosition().x;
				if (ESure.type == sf::Event::MouseButtonPressed)
				{
					if(inRangeXY(x,0,490+(float)0*400/2.0,0,490+(float)1.0*400/2.0,0))
						return 1;
					else if(inRangeXY(x,0,490+(float)1.0*400/2.0,0,490+(float)2.0*400/2.0,0))
						return 2;

				}


				Window.clear();
				Window.clear(sf::Color(255,255,255));
				Window.draw(Yes);
				Window.draw(No);
				Window.draw(Sure);

				Window.display();

			}

		}
	}
	int LevelPopMessage()
	{
		sf::VideoMode Ranking(400,120,32);
		sf::RenderWindow Window(Ranking,"Level");
		while(Window.isOpen())
		{
			sf::Event ELevel;
			sf::Mouse Mouse;

			sf::Sprite Check;
			Check.setPosition(105+(float)(SearchDepth-3)*400/3.0,80);

			sf::Sprite Easy;
			Easy.setTexture(T_Easy);
			Easy.setPosition(20+(float)0.0*400/3.0,20);
			sf::Sprite Moderate;
			Moderate.setTexture(T_Moderate);
			Moderate.setPosition(20+(float)1.0*400/3.0,20);
			sf::Sprite Hard;
			Hard.setTexture(T_Hard);
			Hard.setPosition(20+(float)2.0*400/3.0,20);

			Window.clear();
			Window.clear(sf::Color(255,255,255));
			Window.draw(Easy);
			Window.draw(Moderate);
			Window.draw(Hard);
			Window.draw(Check);
			Window.display();

			while(Window.pollEvent(ELevel))
			{
				if (ELevel.type == sf::Event::Closed)
					Window.close();
				if (ELevel.type == sf::Event::Resized)
					Window.close();
				if (ELevel.type == sf::Event::LostFocus)
					Window.close();




				if (ELevel.type == sf::Event::MouseButtonPressed)
				{
					int x=Mouse.getPosition().x;

					if(inRangeXY(x,0,490+(float)0*400/3.0,0,490+(float)1.0*400/3.0,0))
						return 1;
					else if(inRangeXY(x,0,490+(float)1.0*400/3.0,0,490+(float)2.0*400/3.0,0))
						return 2;
					else if(inRangeXY(x,0,490+(float)2.0*400/3.0,0,490+(float)3.0*400/3.0,0))
						return 3;

				}



				Window.clear();
				Window.clear(sf::Color(255,255,255));
				Window.draw(Easy);
				Window.draw(Moderate);
				Window.draw(Hard);
				Window.draw(Check);


				Window.display();

			}

		}
	}

	//===== sets up the default positions and board ====//
	void Default ()
	{
		Player=Player1;
		memset(arr,-1,sizeof(arr));
		c4_C.cType=C;
		for ( int i=0 ; i<6 ; i++ )
			for ( int j=0 ; j<7 ; j++ )
			{
				c4.game[i][j]=c4_C;
				Board[i][j].setTexture(T_E);
			}
	}

	//===== load images for the game =====//
	void LoadImages()
	{
		T_1.loadFromFile("Images//connect4//1.png");
		T_2.loadFromFile("Images//connect4//2.png");



		T_yWin.loadFromFile("Images//connect4//yWin.png");
		T_rWin.loadFromFile("Images//connect4//rWin.png");
		T_Draw.loadFromFile("Images//connect4//Draw.png");
		T_Board.loadFromFile("Images//connect4//board.png");
		T_E.loadFromFile("Images//connect4//empty.png");
		T_BG.loadFromFile("Images//connect4//BG.jpg");
		T_Easy.loadFromFile("Images//connect4//easy.png");
		T_Moderate.loadFromFile("Images//connect4//moderate.png");
		T_Hard.loadFromFile("Images//connect4//hard.png");
		T_Yes.loadFromFile("Images//connect4//yes.jpg");
		T_No.loadFromFile("Images//connect4//no.jpg");
		T_Menu_BG.loadFromFile("Images//connect4//Menu_BG.png");
		S_Menu_BG.setTexture(T_Menu_BG);
		S_Menu_BG.setPosition(50,60);
		S_BG.setTexture(T_BG);
		S_BG.setScale((float)VMode.width/(float)T_BG.getSize().x,(float)VMode.height/(float)T_BG.getSize().y);
		Grid.setTexture(T_Board);
		Grid.setPosition(280,90);
		S_1.setTexture(T_1);
		S_2.setTexture(T_2);
		S_E.setTexture(T_E);
		S_Draw.setTexture(T_Draw);
		S_yWin.setTexture(T_yWin);
		S_rWin.setTexture(T_rWin);
		for(int i=0;i<6;i++)
		{
			for(int j=0;j<7;j++)
			{
				Board[i][j].setPosition(index_cord_x(j),index_cord_y(i));
				Board[i][j].setTexture(T_E);
			}
		}
	}

	//===== load sounds for the game =====//
	void LoadingSounds()
	{
		B_Move1.loadFromFile("Sounds//move1.wav");
		Sound_Move1.setBuffer(B_Move1);
		B_Error.loadFromFile("Sounds//error.wav");
		Sound_Error.setBuffer(B_Error);
	}

	//===== change the depth of minimax algorithm for the difficulty of game =====//
	void setDifficulty()
	{
		switch(LevelPopMessage())
		{
		case 1:
			SearchDepth=5;
			break;
		case 2:
			SearchDepth=6;
			break;
		case 3:
			SearchDepth=7;
			break;
		}
	}

	//=== used in minimax algorithm ===//
	int RandomNumber()
	{
		time_t sec; 
		time(&sec);
		srand(sec);	

		int RANDOM=(rand());
		return RANDOM;
	}

	//==== create the sub menu of connect4 ====//
	void SetMenu()
	{	
		Menu[0].setString("Main Menu");
		Menu[1].setString("New Game");
		Menu[2].setString("Undo Move");
		Menu[3].setString("Difficulty"); 

		for(int i=0;i<4;i++)
		{
			Menu[i].setPosition( 100,Menu_Index_Cord(i-3));
			Menu[i].setColor(sf::Color(0,0,0,50));
		}

	}

	//==== make the choices of menu glow when the mouse is on it ====/
	void TextGlow(int y)
	{
		Menu[y].setColor(sf::Color(0,0,0,150));
		for(int i=0;i<4;i++)
			if(i!=y)
				Menu[i].setColor(sf::Color(0,0,0,70));
	}

	//==== reset glow of menu words ====//
	void resetGlow()
	{		for(int i=0;i<4;i++)
	Menu[i].setColor(sf::Color(0,0,0,70));
	}

	//==== undo last move of the game ====//
	void undoMove ()
	{
		if (Turns.size()<1 )
			return;
		temp = Turns[ Turns.size()-1 ];
		Turns.pop_back();
		c4.game[temp.first][temp.second].cType=C;
		arr[temp.second]--;
		Board[temp.first][temp.second].setTexture(T_E);
		switchPlayer();
	}

	//===== check the board if one player has won =====//
	int CheckWin(int x,int y,c4Pieces connect4[6][7])
	{
		if ( connect4[x][y].cType == C )
			return 0;
		int NumberOfWins=0;
		// === check the column
		if ( x-3 >= 0 )
		{
			if ( connect4[x][y].cType==connect4[x-1][y].cType && connect4[x][y].cType==connect4[x-2][y].cType && connect4[x][y].cType==connect4[x-3][y].cType )
			{
				if ( connect4[x][y].cType==R)
					NumberOfWins++;
				else
					NumberOfWins--;
			}
		}

		//=== check the Rows
		if( y-3 >=0 )
		{
			if ( connect4[x][y].cType==connect4[x][y-1].cType && connect4[x][y].cType==connect4[x][y-2].cType && connect4[x][y].cType==connect4[x][y-3].cType )
			{
				if ( connect4[x][y].cType==R)
					NumberOfWins++;
				else
					NumberOfWins--;
			}
		}
		if ( y+3 <= 6 )
		{
			if ( connect4[x][y].cType==connect4[x][y+1].cType && connect4[x][y].cType==connect4[x][y+2].cType && connect4[x][y].cType==connect4[x][y+3].cType )
			{
				if ( connect4[x][y].cType==R)
					NumberOfWins++;
				else
					NumberOfWins--;
			}
		}
		if ( y-1>=0 && y+2<=6 )
		{
			if ( connect4[x][y].cType==connect4[x][y-1].cType && connect4[x][y].cType==connect4[x][y+1].cType && connect4[x][y].cType==connect4[x][y+2].cType )
			{
				if ( connect4[x][y].cType==R)
					NumberOfWins++;
				else
					NumberOfWins--;
			}
		}
		if ( y-2>=0 && y+1<=6 )
		{
			if ( connect4[x][y].cType==connect4[x][y-1].cType && connect4[x][y].cType==connect4[x][y-2].cType && connect4[x][y].cType==connect4[x][y+1].cType )
			{
				if ( connect4[x][y].cType==R)
					NumberOfWins++;
				else
					NumberOfWins--;
			}
		}

		//check the diagonals Diagonals
		if ( y-3>=0 && x-3>=0)//
		{
			if ( connect4[x][y].cType==connect4[x-1][y-1].cType && connect4[x][y].cType==connect4[x-2][y-2].cType && connect4[x][y].cType==connect4[x-3][y-3].cType )
			{
				if ( connect4[x][y].cType==R)
					NumberOfWins++;
				else
					NumberOfWins--;
			}
		}
		if (y+3<=6 && x>=3)//
		{
			if ( connect4[x][y].cType==connect4[x-1][y+1].cType && connect4[x][y].cType==connect4[x-2][y+2].cType && connect4[x][y].cType==connect4[x-3][y+3].cType )
			{
				if ( connect4[x][y].cType==R)
					NumberOfWins++;
				else
					NumberOfWins--;
			}
		}
		if (y+3<=6 && x+3<=5)//
		{
			if ( connect4[x][y].cType==connect4[x+1][y+1].cType && connect4[x][y].cType==connect4[x+2][y+2].cType && connect4[x][y].cType==connect4[x+3][y+3].cType )
			{
				if ( connect4[x][y].cType==R)
					NumberOfWins++;
				else
					NumberOfWins--;
			}
		}
		if ( y-3>=0 && x<3)//
		{
			if ( connect4[x][y].cType==connect4[x+1][y-1].cType && connect4[x][y].cType==connect4[x+2][y-2].cType && connect4[x][y].cType==connect4[x+3][y-3].cType )
			{
				if ( connect4[x][y].cType==R)
					NumberOfWins++;
				else
					NumberOfWins--;
			}
		}
		if ( x-1>=0 && x+2<=5 && y-1>=0 && y+2<=6)
		{
			if ( connect4[x][y].cType==connect4[x-1][y-1].cType && connect4[x][y].cType==connect4[x+1][y+1].cType && connect4[x][y].cType==connect4[x+2][y+2].cType )
			{
				if ( connect4[x][y].cType==R)
					NumberOfWins++;
				else
					NumberOfWins--;
			}
		}
		if ( x-2>=0 && x+1<=5 && y-2>=0 && y+1<=6)
		{
			if ( connect4[x][y].cType==connect4[x-2][y-2].cType && connect4[x][y].cType==connect4[x-1][y-1].cType && connect4[x][y].cType==connect4[x+1][y+1].cType )
			{
				if ( connect4[x][y].cType==R)
					NumberOfWins++;
				else
					NumberOfWins--;
			}
		}
		if ( x-1>=0 && x+2<=5 && y-2>=0 && y+1<=6)//
		{
			if ( connect4[x][y].cType==connect4[x-1][y+1].cType && connect4[x][y].cType==connect4[x+1][y-1].cType && connect4[x][y].cType==connect4[x+2][y-2].cType )
			{
				if ( connect4[x][y].cType==R)
					NumberOfWins++;
				else
					NumberOfWins--;
			}
		}
		if ( x-2>=0 && x+1<=5 && y-1>=0 && y+2<=6)//
		{
			if ( connect4[x][y].cType==connect4[x-2][y+2].cType && connect4[x][y].cType==connect4[x-1][y+1].cType && connect4[x][y].cType==connect4[x+1][y-1].cType )
			{
				if ( connect4[x][y].cType==R)
					NumberOfWins++;
				else
					NumberOfWins--;
			}
		}
		return NumberOfWins*10000;
	}

	//===== check if the game has ended without winning =====//
	bool Draw (c4Pieces _board[6][7])
	{
		for( int j=0 ; j<7 ; j++ )
			for ( int i=0 ; i<6 ; i++ )
				if(_board[i][j].cType==C)
					return false;
		return true;
	}

	//=== change the player ===//
	void switchPlayer()
	{
		if(Player==Player1)
			Player=Player2;
		else
			Player=Player1;
	}

	//--------- return move value to the minimax -------//
	int Evaluate(int x,int y,c4Pieces board[6][7]);

	//--------- search engin for the most perfect game -------//

	int minimax(int depth, c4Pieces _board[6][7] );

	int minSearch(int depth ,int x,int y, c4Pieces _board[6][7] );

	int maxSearch(int depth, int x, int y,c4Pieces _board[6][7] );


	//===== control the xo game of 1 player =====//
	void ComputerPlay();

	//===== control the xo game of 2 players =====//
	void HumanPlay();

};

//-------------- Game AI ------------//
int c4Game::Evaluate(int x,int y,c4Pieces board[6][7])
{
	bool draw=true;
	int value=CheckWin(x,y,board);
	if(value==0)
	{
		for( int j=0 ; j<7 ; j++ )
			for ( int i=0 ; i<6 ; i++ )
			{
				if(board[i][j].cType== C)
				{
					draw=false;
					break;
				}
			}
			if(draw==true)return 0;
			else return -1;
	}
	else 
		return value;
}

int c4Game::minimax(int depth, c4Pieces _board[6][7] )
{
	int bestValue = 10000, index = 0;
	int bestMoves[42] ;
	for( int j=0; j<7; j++ )
	{
		for ( int i=0 ; i<6 ; i++ )
		{
			if( _board[i][j].cType == C )
			{
				_board[i][j].cType = Y;
				int value = maxSearch(depth,i,j, _board );
				if( value < bestValue )
				{
					bestValue = value;
					index = 0;
					bestMoves[index] = j;
				}

				else if( value == bestValue )
				{
					bestMoves[index++] = j;
				}
				_board[i][j].cType = C;
				break;
			}
		}
	}
	if( index > 0 )
		index = RandomNumber ()% index;
	return bestMoves[index];
}


int c4Game::minSearch(int depth ,int x,int y, c4Pieces _board[6][7] )
{
	int pos_value=Evaluate(x,y,_board);
	if(pos_value != -1 || depth==0)
		return pos_value;

	int bestValue = 10000;
	for(int j=0 ; j<7 ; j++ )
	{
		for ( int i=0 ; i<6 ; i++ )
		{
			if( _board[i][j].cType == C )
			{
				_board[i][j].cType = Y;

				int value=maxSearch(depth-1,i,j,_board);
				if( value < bestValue )
					bestValue = value;
				_board[i][j].cType = C;
				break;
			}
		}
	}
	return bestValue;
}

int c4Game::maxSearch(int depth, int x, int y,c4Pieces _board[6][7] )
{
	int pos_value=Evaluate(x,y,_board);
	if(pos_value != -1|| depth==0)
		return pos_value;

	int bestValue = -10000;
	for( int j=0 ; j<7 ; j++ )
	{
		for ( int i=0 ; i<6 ; i++ )
		{
			if( _board[i][j].cType == C )
			{
				_board[i][j].cType = R;
				int value=minSearch(depth-1,i,j,_board);

				if(value > bestValue )
					bestValue = value;
				_board[i][j].cType = C;
				break;
			}
		}
	}
	return bestValue;
}


//===== control the connect4 players game =====//
void c4Game::ComputerPlay()
{	
	LoadImages();
	LoadingSounds();
	SetMenu();
	int x=-1,y;

	while(Window.isOpen())
	{
		sf::Event Event;
		sf::Mouse Mouse;
		while(Window.pollEvent(Event))
		{
			if (Player == Player1)
			{
				if(Event.type==Event.MouseButtonPressed && inBoardRange(Mouse.getPosition().x,Mouse.getPosition().y))
				{	
					x=cord_index_x(Mouse.getPosition().x);		

					if (arr[x]==5)
					{
						Sound_Error.play();
						continue ;
					}
					else
					{
						arr[x]++;
						y=arr[x];
					}

					if(c4.game[arr[x]][x].cType == C )
						c4.game[arr[x]][x].cType=R;
					Board[arr[x]][x]=S_1;
					Board[arr[x]][x].setPosition(index_cord_x(x),index_cord_y(arr[x]));
					Sound_Move1.play();
					temp.first = arr[x];
					temp.second = x;
					Turns.push_back(temp);
					switchPlayer();

				}

			}
			else
			{
				x=minimax(SearchDepth,c4.game);
				arr[x]++;
				c4.game[arr[x]][x].cType=Y;
				Board[arr[x]][x]=S_2;
				Board[arr[x]][x].setPosition(index_cord_x(x),index_cord_y(arr[x]));
				Sound_Move1.play();
				temp.first = arr[x];
				temp.second = x;
				Turns.push_back(temp);
				switchPlayer();

			}

			if ( CheckWin(arr[x],x,c4.game)!= 0 )
			{
				Window.clear();
				Window.clear(sf::Color(255,255,255));
				Window.draw(S_BG);
				Window.draw(S_Menu_BG);

				for(int i=0;i<6;i++)
					for(int j=0;j<7;j++)
						Window.draw(Board[i][j]);
				Window.draw(Grid);
				for(int i=0;i<4;i++)
					Window.draw(Menu[i]);
				Window.display();	
				//Window.draw(Board[arr[x]][x]);
				if ( Player==Player1 )
					YwinPopMessage();
				else
					RwinPopMessage();
				switch(PlayAgainPopMessage())
				{
				case 1:
					Default();
					break;
				case 2:
					return;
					break;
				}
			}
			if ( Draw(c4.game) )
			{
				//Window.draw(Board[arr[x]][x]);
				DrawPopMessage();
				switch(PlayAgainPopMessage())
				{
				case 1:
					Default();
					break;
				case 2:
					return;
					break;
				}
			}

			// end	

			if(Menu_Range(Mouse.getPosition().x,Mouse.getPosition().y))
				TextGlow(Menu_Cord_Index(Mouse.getPosition().y));
			else resetGlow();

			if(Menu_Range(Mouse.getPosition().x,Mouse.getPosition().y) && Event.type==Event.MouseButtonPressed )
			{
				int choice = Menu_Cord_Index(Mouse.getPosition().y)+1;
				switch (choice)
				{
				case 1:
					return;
					break;
				case 2:
					switch(SurePopMessage())
					{
					case 1:
						Default();
						break;
					case 2:
						return;
						break;
					}
					break;
				case 3:
					undoMove();
					undoMove();
					break;
				case 4:
					setDifficulty();
					break;
				}
			}

			if(Event.type ==sf::Event::Closed)
				Window.close();
			Window.clear();
			Window.clear(sf::Color(255,255,255));
			Window.draw(S_BG);
			Window.draw(S_Menu_BG);

			for(int i=0;i<6;i++)
				for(int j=0;j<7;j++)
					Window.draw(Board[i][j]);
			Window.draw(Grid);
			for(int i=0;i<4;i++)
				Window.draw(Menu[i]);
			Window.display();	

		}
	}
}

void c4Game::HumanPlay()
{	
	LoadImages();
	LoadingSounds();
	SetMenu();

	while(Window.isOpen())
	{
		sf::Event Event;
		sf::Mouse Mouse;
		int y;
		while(Window.pollEvent(Event))
		{
			if(Event.type==Event.MouseButtonPressed && inBoardRange(Mouse.getPosition().x,Mouse.getPosition().y))
			{

				int x=cord_index_x(Mouse.getPosition().x);

				if (arr[x]==5)
				{
					Sound_Error.play();
					continue ;
				}
				else
				{
					arr[x]++;
					y = arr[x];
				}

				if (Player == Player1)
				{
					if(c4.game[arr[x]][x].cType == C )
						c4.game[arr[x]][x].cType=R;
					Board[arr[x]][x]=S_1;
					Board[arr[x]][x].setPosition(index_cord_x(x),index_cord_y(arr[x]));
					Sound_Move1.play();
					temp.first = arr[x];
					temp.second = x;
					Turns.push_back(temp);
					switchPlayer();
				}
				else
				{
					if(c4.game[arr[x]][x].cType == C )
						c4.game[arr[x]][x].cType=Y;						
					Board[arr[x]][x]=S_2;
					Board[arr[x]][x].setPosition(index_cord_x(x),index_cord_y(arr[x]));
					Sound_Move1.play();
					temp.first = arr[x];
					temp.second = x;
					Turns.push_back(temp);
					switchPlayer();
				}
				if ( CheckWin(arr[x],x,c4.game)!= 0 )
				{
					if ( Player=Player1 )
						YwinPopMessage();
					else
						RwinPopMessage();
					switch(PlayAgainPopMessage())
					{
					case 1:
						Default();
						break;
					case 2:
						return;
						break;
					}
				}
				if ( Draw(c4.game) )
				{
					Window.draw(Board[arr[x]][x]);
					DrawPopMessage();
					switch(PlayAgainPopMessage())
					{
					case 1:
						Default();
						break;
					case 2:
						return;
						break;
					}
				}
			}

			// end
			if(Menu_Range(Mouse.getPosition().x,Mouse.getPosition().y))
				TextGlow(Menu_Cord_Index(Mouse.getPosition().y));
			else resetGlow();

			if(Menu_Range(Mouse.getPosition().x,Mouse.getPosition().y) && Event.type==Event.MouseButtonPressed )
			{
				int choice = Menu_Cord_Index(Mouse.getPosition().y)+1;
				switch (choice)
				{
				case 1:
					return;
					break;
				case 2:
					switch(SurePopMessage())
					{
					case 1:
						Default();
						break;
					case 2:
						return;
						break;
					}
					break;
				case 3:
					undoMove();
					break;
				}
			}

			if(Event.type ==sf::Event::Closed)
				Window.close();
			Window.clear();
			Window.clear(sf::Color(255,255,255));
			Window.draw(S_BG);
			Window.draw(S_Menu_BG);

			for(int i=0;i<6;i++)
				for(int j=0;j<7;j++)
					Window.draw(Board[i][j]);
			Window.draw(Grid);
			for(int i=0;i<3;i++)
				Window.draw(Menu[i]);
			Window.display();

		}
	}
}

#endif