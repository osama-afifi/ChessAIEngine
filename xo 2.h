#ifndef XO2_H
#define XO2_H
#pragma once

#include "xo 1.h"
#include "vmode.h"


//====== class controling XO game =======// 
class xoGame
{

	vector<int> Turns; // carry the played games ( used in undo)
public :
	xoPieces p0; // piece object
	xoBoard xo; // board object
	int Player;


	//====== Graphics ======//
	sf::Sprite Board[3][3];
	sf::Sprite Grid;
	sf::Sprite S_BG;

	sf::Texture T_Yes;
	sf::Texture T_No;

	sf::Texture T_X;
	sf::Texture T_O;
	sf::Texture T_E;
	sf::Texture T_Board;
	sf::Texture T_BG;

	sf::Text  Menu[6];

	sf::Sprite S_xWin;
	sf::Sprite S_oWin;
	sf::Sprite S_xoDraw;
	sf::Texture T_xWin;
	sf::Texture T_oWin;
	sf::Texture T_xoDraw;

	sf::Sprite S_X; 
	sf::Sprite S_O;
	sf::Sprite S_E;

	sf::Sprite S_Yes;
	sf::Sprite S_No;

	sf::Texture T_Menu_BG;
	sf::Sprite S_Menu_BG;

	//---- Sounds ----//
	sf::SoundBuffer B_Move1;
	sf::Sound Sound_Move1;
	sf::SoundBuffer B_Error;
	sf::Sound Sound_Error;


	//=== constructor for the class ===//
	xoGame() : Player(Player1)
	{}

	//==== check if the mouse click is in the board range ====//
	bool inBoardRange(int x,int y)
	{
		if(cord_index_x(x)>=0 && cord_index_x(x)<3 && cord_index_y(y)>=0 && cord_index_y(y)<3  )
			return true;
		return false;
	}

	//==== check if the mouse click is in the menu range ====//
	bool Menu_Range(int x, int y)
	{
		if( y>100 && y<265 && x>95 && x<330 )return true;
		return false;
	}

	//==== check if the mouse click is on the right pictures of windows ====//
	bool inRangeXY(int x,int y , float r1x , float r1y , float r2x , float r2y)
	{
		if(x>=r1x && x<=r2x  )
			return true;
		return false;
	}

	//===== change mouse coordinates to board coordinates =====//
	int cord_index_x( float x_cord)
	{
		return ((x_cord-390)/200);

	}
	int cord_index_y( float y_cord)
	{
		return ((y_cord-120)/190);

	}
	int Menu_Cord_Index(int y)
	{
		return ((float)(float(y-99)/165.0)*4.0)+0.5;
	}

	//===== change board coordinates to mouse coordinates =====//
	float index_cord_x( int x_index)
	{
		return (200*(x_index-1))+430;

	}
	float index_cord_y( int y_index)
	{
		return (200*(y_index-1))+235;

	}
	int Menu_Index_Cord(int y)
	{
		return (40*(y))+200;
	}

	//===== load sounds for the game =====//
	void LoadingSounds()
	{
		B_Move1.loadFromFile("Sounds//move1.wav");
		Sound_Move1.setBuffer(B_Move1);
		B_Error.loadFromFile("Sounds//error.wav");
		Sound_Error.setBuffer(B_Error);
	}

	//===== load images for the game =====//
	void LoadImages()
	{

		T_X.loadFromFile("Images//XO//x.png");
		T_O.loadFromFile("Images//XO//o.png");
		T_Board.loadFromFile("Images//XO//xo.png");
		T_E.loadFromFile("Images//XO//empty.png");
		T_BG.loadFromFile("Images//XO//BG.png");
		T_xoDraw.loadFromFile("Images//XO//xoDraw.png");
		T_xWin.loadFromFile("Images//XO//xWin.png");
		T_oWin.loadFromFile("Images//XO//oWin.png");
		T_Yes.loadFromFile("Images//XO//yes.jpg");
		T_No.loadFromFile("Images//XO//no.jpg");
		T_Menu_BG.loadFromFile("Images//XO//Menu_BG.png");
		S_Menu_BG.setTexture(T_Menu_BG);
		S_Menu_BG.setPosition(50,50);
		
		S_X.setTexture(T_X);
		S_O.setTexture(T_O);
		S_xoDraw.setTexture(T_xoDraw);
		S_xWin.setTexture(T_xWin);
		S_oWin.setTexture(T_oWin);
		S_Yes.setTexture(T_Yes);
		S_No.setTexture(T_No);
		S_BG.setTexture(T_BG);
		S_BG.setScale((float)VMode.width/(float)T_BG.getSize().x,(float)VMode.height/(float)T_BG.getSize().y);

		Grid.setTexture(T_Board);
		Grid.setPosition(380,90);
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				Board[i][j].setPosition(index_cord_x(i),index_cord_y(j));
				Board[i][j].setTexture(T_E);
			}
		}
	}

	//===== sets up the default positions and board ====//
	void Default ()
	{
		// === Empty the board from its pieces (new game) ===//
		for ( int i=0 ; i<9 ; i++ )
		{
			xo.arr[i].pieceType=N;
			Board[i/3][i%3].setTexture(T_E);
		}

		while (! Turns.empty() )
			Turns.pop_back();

		Player=Player1;
	}

	//==== show the pop message using sfml library ====//
	int SurePopMessage()
	{
		sf::VideoMode Ranking(400,120,32);
		sf::RenderWindow Window(Ranking,"Are You Sure ?",sf::Style::Titlebar);
		while(Window.isOpen())
		{
			sf::Event ESure;
			sf::Mouse Mouse;

			sf::Text Sure;
			Sure.setString("Are you Sure ?");//== creating string 
			Sure.setColor(sf::Color(0,0,0));//==string color
			Sure.setPosition(120,0);//==string position
			sf::Sprite Yes;
			Yes.setTexture(T_Yes);
			Yes.setPosition(60+(float)0.0*400/2.0,30);//==sets up coordinates of picture
			sf::Sprite No;
			No.setTexture(T_No);
			No.setPosition(60+(float)1.0*400/2.0,30);

			Window.clear();
			Window.clear(sf::Color(255,255,255)); //== window color
			Window.draw(Yes); //== draw picture of yes choice
			Window.draw(No);//== draw picture of no choice
			Window.draw(Sure);//== draw pidture of sure string  choice

			Window.display();//== displaying the window

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

			//==== draw the window ====//
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
	void OwinPopMessage()
	{
		sf::VideoMode Owin(300,300,32);
		sf::RenderWindow Window(Owin,"O wins",sf::Style::Close);
		S_oWin.setScale((float)Owin.width/(float)T_oWin.getSize().x,(float)Owin.height/(float)T_oWin.getSize().y);
		while(Window.isOpen())
		{
			sf::Event Owin;
			while(Window.pollEvent(Owin))
			{
				//Window.clear(sf::Color(255,255,255));
				Window.draw(S_oWin);
				Window.display();
				if(Owin.type==Owin.MouseButtonPressed || Owin.type== sf::Event::LostFocus || (Owin.type==sf::Event::Closed))
				{
					Window.close();
					return;
				}
			}
		}
	}
	void XwinPopMessage()
	{
		sf::VideoMode Xwin(300,300,32);
		sf::RenderWindow Window(Xwin,"X wins",sf::Style::Close);
		S_xWin.setScale((float)Xwin.width/(float)T_xWin.getSize().x,(float)Xwin.height/(float)T_xWin.getSize().y);
		while(Window.isOpen())
		{
			sf::Event Xwin;
			while(Window.pollEvent(Xwin))
			{
				//Window.clear(sf::Color(255,255,255));
				Window.draw(S_xWin);
				Window.display();
				if(Xwin.type==Xwin.MouseButtonPressed || Xwin.type== sf::Event::LostFocus || (Xwin.type==sf::Event::Closed))
				{
					Window.close();
					return;
				}
			}

		}
	}
	void XOdrawPopMessage()
	{
		sf::VideoMode OXwin(300,300,32);
		sf::RenderWindow Window(OXwin,"Xo Draw",sf::Style::Close);
		S_xoDraw.setScale((float)OXwin.width/(float)T_xoDraw.getSize().x,(float)OXwin.height/(float)T_xoDraw.getSize().y);
		while(Window.isOpen())
		{
			sf::Event OXwin;
			while(Window.pollEvent(OXwin))
			{
				//Window.clear(sf::Color(255,255,255));
				Window.draw(S_xoDraw);
				Window.display();
				if(OXwin.type==OXwin.MouseButtonPressed || OXwin.type== sf::Event::LostFocus || (OXwin.type==sf::Event::Closed))
				{
					Window.close();
					return;
				}
			}

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


	//==== create the sub menu of XO ====//
	void SetMenu()
	{	
		//===  choices strings ===//
		Menu[0].setString("Main Menu");
		Menu[1].setString("New Game");
		Menu[2].setString("Undo Move");

		for(int i=0;i<3;i++)
		{
			Menu[i].setPosition( 100,Menu_Index_Cord(i-3));//==position of each choice
			Menu[i].setColor(sf::Color(0,0,0,50));//==color of each choice
		}

	}

	//==== make the choices of menu glow when the mouse is on it ====//
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
		//=== if the vector is empty it returns ===//
		if ( Turns.size()<1 )
			return;

		int temp = Turns[ Turns.size()-1 ];//==last game played
		Turns.pop_back();

		//== removing the last game played
		xo.arr[temp].pieceType = N;
		Board[temp/3][temp%3].setTexture(T_E);
		switchPlayer();
	}

	//===== check the board if one player has won =====//
	int CheckWin(xoPieces _board[9])
	{
		int NumberOfWins=0;

		//==== check the Rows
		for ( int i=2 ; i<9 ; i+=3 )
		{
			if ( _board[i].pieceType != N && _board[i-2].pieceType == _board[i-1].pieceType && _board[i-1].pieceType == _board[i].pieceType )
			{
				if(_board[i].pieceType == X)
					NumberOfWins++;
				else 
					NumberOfWins--;
			}
		}

		//==== check the Columns
		for ( int i=0 ; i<3 ; i++ )
		{
			if ( _board[i].pieceType != N && _board[i].pieceType == _board[i+3].pieceType && _board[i+3].pieceType== _board[i+6].pieceType)
			{
				if(_board[i].pieceType== X)
					NumberOfWins++;
				else 
					NumberOfWins--;
			}
		}

		//==== check the two Diagonals
		if ( _board[0].pieceType!= N && _board[0].pieceType== _board[4].pieceType&& _board[4].pieceType== _board[8].pieceType )
		{
			if(_board[0].pieceType== X)
				NumberOfWins++;
			else 
				NumberOfWins--;
		}
		if( _board[6].pieceType!= N && _board[6].pieceType== _board[4].pieceType&& _board[4].pieceType== _board[2].pieceType)
		{
			if(_board[6].pieceType== X)
				NumberOfWins++;
			else 
				NumberOfWins--;
		}
		return NumberOfWins*10000;
	}

	//===== check if the game has ended without winning =====//
	bool Draw (xoPieces _board[9])
	{
		for(int i=0;i<9;i++)
			if(_board[i].pieceType==N)
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
	int Evaluate(xoPieces _board[9]);

	//--------- search engin for the most perfect game -------//
	int minimax( xoPieces _board[9] );

	int minSearch( xoPieces _board[9] );

	int maxSearch( xoPieces _board[9] );

	//===== control the xo game of 2 players =====//
	void HumanPlay();

	//===== control the xo game of 1 player =====//
	void ComputerPlay();
};


//-------------- Game AI ------------//
int xoGame::Evaluate(xoPieces _board[9])
{
	if(CheckWin(_board)==0)//=== no one wins through this move
	{
		if(Draw(_board))
			return 0;
		else 
			return -1;
	}
	else 
		return CheckWin(_board);
}

int xoGame::minimax( xoPieces _board[9] )
{
	short int i;
	int bestValue = 10000, index = 0;
	int bestMoves[9] = {0};

	//==== check its game in every square of board if it's empty ==//
	for( i = 0; i < 9; i++ )
	{
		if( _board[i].pieceType== N )
		{
			_board[i].pieceType= O;

			int value = maxSearch( _board );//=== send the board to maxSearch function to cotinue its search engine

			if( value < bestValue )//=== carry the best value returned by the function in bestValue variable
			{
				bestValue = value;
				index = 0;
				bestMoves[index] = i;
			}

			//== if the function return more than best value of same value ==//
			else if( value == bestValue )
				bestMoves[index++] = i;
			_board[i].pieceType= N;
		}
	}

	//=== choose between the best values returned to get the desired move ===//
	if( index > 0 )
		index = RandomNumber ()% index;
	return bestMoves[index];
}

int xoGame::minSearch( xoPieces _board[9] )
{
	short int i;

	int pos_value=Evaluate(_board);//=== evaluate the state of the board and return a value

	if(pos_value != -1)//=== means the game isn't finished and no one wins
		return pos_value;

	int bestValue = 10000;
	for( i = 0; i < 9; i++ ) //=== fill the empty space in board with O piece 
	{
		if( _board[i].pieceType== N )
		{
			_board[i].pieceType= O;

			int value=maxSearch(_board);//=== send the board to maxSearch function to cotinue its search engine
			if( value < bestValue )//=== carry the best value returned by the function in bestValue variable
				bestValue = value;
			_board[i].pieceType= N;
		}
	}
	return bestValue; // return the value of the  best game for O player 
}

int xoGame::maxSearch( xoPieces _board[9] )
{
	short int i;
	int pos_value=Evaluate(_board);
	if(pos_value != -1)
		return pos_value;

	int bestValue = -10000;
	for( i = 0; i < 9; i++ ) //=== fill the empty space in board with X piece 
	{
		if( _board[i].pieceType== N )
		{
			_board[i].pieceType= X;
			int value=minSearch(_board);//=== send the board to minSearch function to cotinue its search engine

			if(value > bestValue )//=== carry the best value returned by the function in bestValue variable
				bestValue = value;
			_board[i].pieceType= N;
		}
	}
	return bestValue; // return the value of the  best game for X player 
}

//===== control the xo players game =====//
void xoGame::HumanPlay() 
{
	LoadImages();//load images of game
	LoadingSounds();//load sounds of game
	SetMenu();// set the sub menu

	while(Window.isOpen())//open the window of the payed game
	{
		sf::Event Event;
		sf::Mouse Mouse;
		while(Window.pollEvent(Event))
		{

			//=== check if one player has won
			if ( CheckWin(xo.arr)!= 0 )
			{
				if(Player==Player1)
					OwinPopMessage();
				else
					XwinPopMessage();
				//== ask if the player want to play again
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
			//=====check if the game ended & no one wins
			if ( Draw(xo.arr) )
			{
				XOdrawPopMessage();
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

			//====take action if the pressed mouse click is in board range
			if(Event.type==Event.MouseButtonPressed && inBoardRange(Mouse.getPosition().x,Mouse.getPosition().y))
			{
				//==== change the coordinates of mouse click into the position of game in the board
				int x=cord_index_x(Mouse.getPosition().x);
				int y=cord_index_y(Mouse.getPosition().y);

				int Mark=x*3+y;//=== get the position of played game in the board array

				if(Player==Player1)
				{

					if(xo.arr[Mark].pieceType==N)
					{
						xo.arr[Mark].pieceType=X;//==set piece type
						Turns.push_back(Mark);
						Board[Mark/3][Mark%3]=S_X;//==set piece picture
						Board[Mark/3][Mark%3].setPosition(index_cord_x(Mark/3),index_cord_y(Mark%3));
						Sound_Move1.play();
						switchPlayer();
					}
					else
					{
						//=== if the board space has already an object
						Sound_Error.play();
						continue;
					}
				}
				else
				{
					if(xo.arr[Mark].pieceType==N)
					{
						xo.arr[Mark].pieceType=O;//==set piece type
						Turns.push_back(Mark);
						Board[Mark/3][Mark%3]=S_O; // appear the photo of O
						Board[Mark/3][Mark%3].setPosition(index_cord_x(Mark/3),index_cord_y(Mark%3));
						Sound_Move1.play();
						switchPlayer();
					}
					else
					{
						Sound_Error.play();
						continue;
					}
				}
			}

			//====== the glow and reset of glow for menu when the mouse pointer moves there
			if(Menu_Range(Mouse.getPosition().x,Mouse.getPosition().y))
				TextGlow(Menu_Cord_Index(Mouse.getPosition().y));
			else resetGlow();

			//== take action if a button in the menu is pressed
			if(Menu_Range(Mouse.getPosition().x,Mouse.getPosition().y) && Event.type==Event.MouseButtonPressed )
			{
				int choice = Menu_Cord_Index(Mouse.getPosition().y)+1;
				switch (choice)
				{
				case 1:// Mainmenu
					return;
					break;
				case 2:// New Game
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
				case 3:// choose to undo last game
					undoMove();
					break;
				}
			}

			// ======= draw the board and the pieces ======== //
			if(Event.type ==sf::Event::Closed)
				Window.close();
			Window.clear();
			Window.clear(sf::Color(255,255,255));
			Window.draw(S_BG);//==background picture
			Window.draw(S_Menu_BG);
			Window.draw(Grid);

			for(int i=0;i<3;i++)
				for(int j=0;j<3;j++)
					Window.draw(Board[i][j]);
			for(int i=0;i<3;i++)
				Window.draw(Menu[i]);

			Window.display();
		}
	}
}

void xoGame::ComputerPlay()
{
	LoadImages();//load images of game
	LoadingSounds();//load sounds of game
	SetMenu();// set the sub menu

	while(Window.isOpen())
	{
		sf::Event Event;
		sf::Mouse Mouse;
		while(Window.pollEvent(Event))
		{
			//=== check if one player has won
			if ( CheckWin(xo.arr)!= 0 )
			{
				if(Player==Player1)
					OwinPopMessage();
				else
					XwinPopMessage();
				//== ask if the player want to play again
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
			//=====check if the game ended & no one wins
			if ( Draw(xo.arr) )
			{
				XOdrawPopMessage();
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

			//====take action if the pressed mouse click is in board range
			if ( Player == Player1 )
			{
				if(Event.type==Event.MouseButtonPressed && inBoardRange(Mouse.getPosition().x,Mouse.getPosition().y))
				{
					//==== change the coordinates of mouse click into the position of game in the board
					int x=cord_index_x(Mouse.getPosition().x);
					int y=cord_index_y(Mouse.getPosition().y);

					int Mark=x*3+y;//=== get the position of played game in the board array

					if(xo.arr[Mark].pieceType==N)
					{
						xo.arr[Mark].pieceType=X;
						Turns.push_back(Mark);
						Board[Mark/3][Mark%3]=S_X;//==set piece picture
						Board[Mark/3][Mark%3].setPosition(index_cord_x(Mark/3),index_cord_y(Mark%3));
						Sound_Move1.play();
						switchPlayer();
					}
					else//==if the board space has already a piece 
					{
						Sound_Error.play();
						continue;
					}			
				}
			}
			else // computer play
			{

				int Mark=minimax(xo.arr);//== get the position of the mark from minimax algorithm

				Turns.push_back(Mark);
				xo.arr[Mark].pieceType=O;//=== set the position of the game on board
				Board[Mark/3][Mark%3]=S_O; // appear the photo of O
				Board[Mark/3][Mark%3].setPosition(index_cord_x(Mark/3),index_cord_y(Mark%3));
				Sound_Move1.play();
				switchPlayer();
			}

			//====== the glow and reset of glow for menu when the mouse pointer moves there
			if(Menu_Range(Mouse.getPosition().x,Mouse.getPosition().y))
				TextGlow(Menu_Cord_Index(Mouse.getPosition().y));
			else 
				resetGlow();

			//== take action if a button in the menu is pressed
			if(Menu_Range(Mouse.getPosition().x,Mouse.getPosition().y) && Event.type==Event.MouseButtonPressed )
			{
				int choice = Menu_Cord_Index(Mouse.getPosition().y)+1;
				switch (choice)
				{
				case 1:// Mainmenu
					return;
					break;
				case 2:// New Game
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
				case 3:// choose to undo last game
					undoMove();
					undoMove();
					break;
				}
			}

			// ======= draw the board and the pieces ======== //
			if(Event.type ==sf::Event::Closed)
				Window.close();
			Window.clear();
			Window.clear(sf::Color(255,255,255));
			Window.draw(S_BG);//== background picture
			Window.draw(S_Menu_BG);
			Window.draw(Grid);

			for(int i=0;i<3;i++)
				for(int j=0;j<3;j++)
					Window.draw(Board[i][j]);
			for(int i=0;i<3;i++)
				Window.draw(Menu[i]);

			Window.display();

		}
	}
}


#endif