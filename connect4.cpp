#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

# include <iostream>
# include <iomanip>
# include <cstdlib>
# include <algorithm>
# include <cmath>
# include <map>
# include <set>
# include <vector>
# include <sstream>
# include <cstring>
# include <windows.h>
# include <math.h>  
# include <Wincon.h>
# include <dos.h>
# include <stdio.h>
# include <conio.h>
# include <ctime>
# include <fstream>  
# include <mmsystem.h>
# pragma comment(lib, "winmm.lib")
#define _WIn32_WInnT 0n500

#define Player1 0
#define Player2 1
#define INFINITY INT_MAX
#define EMPTY NULL

using namespace std;


enum c4type {C,R,Y};

sf::VideoMode VMode=sf::VideoMode::getDesktopMode();
sf::RenderWindow Window(VMode,"Chess Game");

class c4Pieces
{	
public:
	c4type cType;
	c4Pieces():cType(C)
	{}
};

class c4Board
{
public:
	c4Pieces game[6][7]; 
};


class c4Game
{
private :
	int SearchDepth;
	vector<pair<int,int> > Turns;
	pair < int,int > temp;
public :
	c4Pieces c4_R , c4_Y , c4_C;
	c4Board c4;
	int arr[7];
	int Player;

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
	sf::Texture T_E;
	sf::Texture T_Board;
	sf::Texture T_BG;

	sf::Text  Menu[6];

	sf::Texture T_Menu_BG;
	sf::Sprite S_Menu_BG;
	sf::Texture T_Out_BG;
	sf::Sprite S_Out_BG1;
	sf::Sprite S_Out_BG2;

	sf::SoundBuffer B_Move1;
	sf::Sound Sound_Move1;
	sf::SoundBuffer B_Move2;
	sf::Sound Sound_Move2;

	c4Game() : Player(Player1) , SearchDepth(3)
	{}
	int cord_index_x( float x_cord)
	{
		return ((x_cord-440)/71);

	}
	int cord_index_y( float y_cord)
	{
		return ((y_cord-180)/61);

	}

	bool inRangeXY(int x,int y , float r1x , float r1y , float r2x , float r2y)
	{
		if(x>=r1x && x<=r2x /*&& y>=r1y && y<=r2y */ )
			return true;
		return false;
	}

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
	int Menu_Cord_Index(int y)
	{
		return ((float)(float(y-99)/165.0)*4.0)+0.5;
	}

	bool inBoardRange(int x,int y)
	{
		if(cord_index_x(x)>=0 && cord_index_x(x)<6 && cord_index_y(y)>=0 && cord_index_y(y)<7  )
			return true;
		return false;
	}

	void LoadingSounds()
	{
		B_Move1.loadFromFile("Sounds//move1.wav");
		Sound_Move1.setBuffer(B_Move1);
		B_Move2.loadFromFile("Sounds//move2.wav");
		Sound_Move2.setBuffer(B_Move2);
	}

	void YwinPopMessage()
	{
		sf::VideoMode Ywin(300,300,32);
		sf::RenderWindow Window(Ywin,"Chess Game",sf::Style::None);
		S_yWin.setScale((float)Ywin.width/(float)T_yWin.getSize().x,(float)Ywin.height/(float)T_yWin.getSize().y);
		while(Window.isOpen())
		{
			sf::Event Ywin;
			while(Window.pollEvent(Ywin))
			{
				Window.clear(sf::Color(255,255,255));
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
		sf::RenderWindow Window(Rwin,"Chess Game",sf::Style::None);
		S_rWin.setScale((float)Rwin.width/(float)T_rWin.getSize().x,(float)Rwin.height/(float)T_rWin.getSize().y);
		while(Window.isOpen())
		{
			sf::Event Rwin;
			while(Window.pollEvent(Rwin))
			{
				Window.clear(sf::Color(255,255,255));
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
		sf::RenderWindow Window(ryDraw,"Chess Game",sf::Style::None);
		S_Draw.setScale((float)ryDraw.width/(float)T_Draw.getSize().x,(float)ryDraw.height/(float)T_Draw.getSize().y);
		while(Window.isOpen())
		{
			sf::Event ryDraw;
			while(Window.pollEvent(ryDraw))
			{
				Window.clear(sf::Color(255,255,255));
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

	void Default ()
	{
		memset(arr,-1,sizeof(arr));
		c4_R.cType=R;
		c4_Y.cType=Y;
		c4_C.cType=C;
		for ( int i=0 ; i<6 ; i++ )
			for ( int j=0 ; j<7 ; j++ )
			{
				c4.game[i][j]=c4_C;
				Board[i][j].setTexture(T_E);
			}
	}	

	void LoadImages()
	{
		T_1.loadFromFile("connect4//1.png");
		T_2.loadFromFile("connect4//2.png");
		T_yWin.loadFromFile("connect4//yWin.png");
		T_rWin.loadFromFile("connect4//rWin.png");
		T_Draw.loadFromFile("connect4//Draw.png");
		T_Board.loadFromFile("connect4//board.png");
		T_E.loadFromFile("connect4//empty.png");
		T_BG.loadFromFile("connect4//BG.jpg");
		T_Easy.loadFromFile("Pieces//easy.png");
		T_Moderate.loadFromFile("Pieces//moderate.png");
		T_Hard.loadFromFile("Pieces//hard.png");
		T_Yes.loadFromFile("Pieces//yes.jpg");
		T_No.loadFromFile("Pieces//no.jpg");
		T_Menu_BG.loadFromFile("Pieces//Menu_BG.png");
		T_Out_BG.loadFromFile("Pieces//Out_BG.png");
		S_Menu_BG.setTexture(T_Menu_BG);
		S_Menu_BG.setPosition(50,50);
		S_Out_BG1.setTexture(T_Menu_BG);
		S_Out_BG2.setTexture(T_Menu_BG);
		S_Out_BG1.setPosition(1015,160);
		S_Out_BG2.setPosition(1015,415);
		S_BG.setTexture(T_BG);
		S_BG.setScale((float)VMode.width/(float)T_BG.getSize().x,(float)VMode.height/(float)T_BG.getSize().y);
		Grid.setTexture(T_Board);
		Grid.setPosition(280,90);

		for(int i=0;i<6;i++)
		{
			for(int j=0;j<7;j++)
			{
				Board[i][j].setPosition(index_cord_x(j),index_cord_y(i));
				Board[i][j].setTexture(T_E);
			}
		}
	}

	void undoMove ()
	{
		temp = Turns[ Turns.size()-1 ];
		Turns.pop_back();
		c4.game[temp.first][temp.second] = c4_C;
		Board[temp.first][temp.second].setTexture(T_E);
		//SwitchPlayer();
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

	void setDifficulty()
	{
		switch(LevelPopMessage())
		{
		case 1:
			SearchDepth=3;
			break;
		case 2:
			SearchDepth=5;
			break;
		case 3:
			SearchDepth=7;
			break;
		}
	}

	bool Menu_Range(int x, int y)
	{
		if( y>100 && y<265 && x>95 && x<330 )return true;
		return false;
	}

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

	void TextGlow(int y)
	{
		Menu[y].setColor(sf::Color(0,0,0,150));
		for(int i=0;i<4;i++)
			if(i!=y)
				Menu[i].setColor(sf::Color(0,0,0,70));
	}

	void resetGlow()
	{		for(int i=0;i<4;i++)
	Menu[i].setColor(sf::Color(0,0,0,70));
	}

	int RandomNumber()
	{
		time_t sec; 
		time(&sec);
		srand(sec);	

		int RANDOM=(rand());
		return RANDOM;
	}

	int CheckWin(int x,int y,c4Pieces connect4[6][7])
	{
		int NumberOfWins=0;
		// column
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

		//Rows
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

		//Diagonals
		if ( y-3>=0 && x>=3)
		{
			if ( connect4[x][y].cType==connect4[x-1][y-1].cType && connect4[x][y].cType==connect4[x-2][y-2].cType && connect4[x][y].cType==connect4[x-3][y-3].cType )
			{
				if ( connect4[x][y].cType==R)
					NumberOfWins++;
				else
					NumberOfWins--;
			}
		}
		if (y+3<=6 && x>=3)
		{
			if ( connect4[x][y].cType==connect4[x-1][y+1].cType && connect4[x][y].cType==connect4[x-2][y+2].cType && connect4[x][y].cType==connect4[x-3][y+3].cType )
			{
				if ( connect4[x][y].cType==R)
					NumberOfWins++;
				else
					NumberOfWins--;
			}
		}
		if (y+3<=6 && x<3)
		{
			if ( connect4[x][y].cType==connect4[x+1][y+1].cType && connect4[x][y].cType==connect4[x+2][y+2].cType && connect4[x][y].cType==connect4[x+3][y+3].cType )
			{
				if ( connect4[x][y].cType==R)
					NumberOfWins++;
				else
					NumberOfWins--;
			}
		}
		if ( y-3>=0 && x<3)
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
		if ( x-1>=0 && x+2<=5 && y-2>=0 && y+1<=6)
		{
			if ( connect4[x][y].cType==connect4[x-1][y+1].cType && connect4[x][y].cType==connect4[x+1][y-1].cType && connect4[x][y].cType==connect4[x+2][y-2].cType )
			{
				if ( connect4[x][y].cType==R)
					NumberOfWins++;
				else
					NumberOfWins--;
			}
		}
		if ( x-2>=0 && x+1<=5 && y-1>=0 && y+2<=6)
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

	bool Draw (c4Pieces _board[6][7])
	{
		for( int j=0 ; j<7 ; j++ )
			for ( int i=0 ; i<6 ; i++ )
				if(_board[i][j].cType==C)
					return false;
		return true;
	}

	int Evaluate(int x,int y,c4Pieces board[6][7])
	{
		bool draw=true;
		int value=CheckWin(x,y,board);
		if(value==0)
		{
			if(Draw(board))
				return 0;
			else 
				return -1;
		}
		else 
			return value;
	}

	int minimax(int depth, c4Pieces _board[6][7] )
	{
		int bestValue = 10000, index = 0;
		int bestMoves[42] ;
		for( int j=0; j<7; j++ )
		{
			for ( int i=0 ; i<6 ; i++ )
			{
				if( _board[i][j].cType == C )
				{
					_board[i][j]= c4_Y;
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
					_board[i][j] = c4_C;
					break;
				}
			}
		}
		if( index > 0 )
			index = RandomNumber ()% index;
		return bestMoves[index];
	}

	int minSearch(int depth ,int x,int y, c4Pieces _board[6][7] )
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
					_board[i][j] = c4_Y;

					int value=maxSearch(depth-1,i,j,_board);
					if( value < bestValue )
						bestValue = value;
					_board[i][j] = c4_C;
					break;
				}
			}
		}
		return bestValue;
	}

	int maxSearch(int depth, int x, int y,c4Pieces _board[6][7] )
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
					_board[i][j] = c4_R;
					int value=minSearch(depth-1,i,j,_board);

					if(value > bestValue )
						bestValue = value;
					_board[i][j] = c4_C;
					break;
				}
			}
		}
		return bestValue;
	}

	void switchPlayer()
	{
		if(Player==Player1)
			Player=Player2;
		else
			Player=Player1;
	}

	void ComputerPlay()
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
				cout<<cord_index_x(Mouse.getPosition().x)<<" "<<cord_index_y(Mouse.getPosition().y)<<endl;
				cout<<Mouse.getPosition().x<<" "<<Mouse.getPosition().y<<endl;

				if (Player == Player1)
				{
					if(Event.type==Event.MouseButtonPressed)
					{	
						x=cord_index_x(Mouse.getPosition().x);
						arr[x]++;
						y=arr[x];

						if (arr[x]>6)
						{
							cout<<"\a\a\a";
							continue ;
						}

						if(c4.game[arr[x]][x].cType == C )
							c4.game[arr[x]][x] = c4_R;
						Board[arr[x]][x].setTexture(T_1);
						Sound_Move1.play();
						temp.first = arr[x];
						temp.second = x;
						Turns.push_back(temp);
						switchPlayer();
						if ( CheckWin(arr[x],x,c4.game)!= 0 )
						{
							YwinPopMessage();
							Window.close();
							return;
						}
						if ( Draw(c4.game) )
						{
							DrawPopMessage();
							Window.close();
							return;
						}
					}

				}
				else
				{
					int x=minimax(SearchDepth,c4.game);
					arr[x]++;
					c4.game[arr[x]][x] = c4_Y;
					Sound_Move1.play();
					temp.first = arr[x];
					temp.second = x;
					Turns.push_back(temp);
					Board[arr[x]][x].setTexture(T_2);
					switchPlayer();
					if ( CheckWin(arr[x],x,c4.game)!= 0 )
					{
						RwinPopMessage();
						Window.close();
						return;
					}
					if ( Draw(c4.game) )
					{
						DrawPopMessage();
						Window.close();
						return;
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
							break;
						}
						break;
					case 3:
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

	void HumanPlay()
	{	
		LoadImages();
		LoadingSounds();
		SetMenu();
		while(Window.isOpen())
		{
			sf::Event Event;
			sf::Mouse Mouse;
			while(Window.pollEvent(Event))
			{
				cout<<cord_index_x(Mouse.getPosition().x)<<" "<<cord_index_y(Mouse.getPosition().y)<<endl;
				cout<<Mouse.getPosition().x<<" "<<Mouse.getPosition().y<<endl;

				if(Event.type==Event.MouseButtonPressed)
				{

					int x=cord_index_x(Mouse.getPosition().x);
					arr[x]++;
					int y = arr[x];

					if (y>6)
					{
						cout<<"\a\a\a";
						continue ;
					}

					if (Player == Player1)
					{
						if(c4.game[arr[x]][x].cType == C )
							c4.game[arr[x]][x] = c4_R;
						Board[arr[x]][x].setTexture(T_1);
						temp.first = arr[x];
						temp.second = x;
						Turns.push_back(temp);
						switchPlayer();
					}
					else
					{
						if(c4.game[arr[x]][x].cType == C )
							c4.game[arr[x]][x] = c4_Y;						
						Board[arr[x]][x].setTexture(T_2);
						temp.first = arr[x];
						temp.second = x;
						Turns.push_back(temp);
						switchPlayer();
					}
					if ( CheckWin(arr[x],x,c4.game)!= 0 )
					{
						cout<<"\a\a\a\a\a\a\a\a\a\a\a\a\a\a\\a\a";
						exit(0);
					}
				}

				// end
				if(Event.type ==sf::Event::Closed)
					Window.close();
				Window.clear();
				Window.clear(sf::Color(255,255,255));
				Window.draw(S_BG);				

				for(int i=0;i<6;i++)
					for(int j=0;j<7;j++)
						Window.draw(Board[i][j]);
				Window.draw(Grid);
				Window.display();

			}
		}
	}

};


int main ()
{
	c4Game C;
	C.Default();
	C.ComputerPlay();
	return 0;
}