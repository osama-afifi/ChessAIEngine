#ifndef CHESS2_H
#define CHESS2_H
#pragma once

#include "king.h"
#include "knight.h"
#include "queen.h"
#include "pawn.h"

//====== class controling chess game =======// 
class ChessGame
{

private:

	int x1,y1,x2,y2;
	int Player;

	bool WhiteCastling;
	bool BlackCastling;
	//-- carry position of enpassant --//
	pair<int,int> BlackEnpassant;
	pair<int,int> WhiteEnpassant;
	//-- carry number of pieces checked --//
	int WhiteOut;
	int BlackOut;
	//-- control the difficulty of game --//
	int SearchDepth;
	//-- carry all played games --//
	vector<string> Turns;
	//-- carry the checked piece --//
	ChessPieces* captured;

	int chosen_x;
	int chosen_y;

public:

	// Pieces and ChessBoard

	King WhiteKing;
	King BlackKing;
	Queen WhiteQueen;
	Queen BlackQueen;
	Rook WhiteRook0;
	Rook BlackRook0;
	Rook WhiteRook1;
	Rook BlackRook1;
	Bishop WhiteBishop0;
	Bishop BlackBishop0;
	Knight WhiteKnight0;
	Knight BlackKnight0;
	Bishop WhiteBishop1;
	Bishop BlackBishop1;
	Knight WhiteKnight1;
	Knight BlackKnight1;
	Pawn WhitePawn0;
	Pawn WhitePawn1;
	Pawn WhitePawn2;
	Pawn WhitePawn3;
	Pawn WhitePawn4;
	Pawn WhitePawn5;
	Pawn WhitePawn6;
	Pawn WhitePawn7;
	Pawn BlackPawn0;
	Pawn BlackPawn1;
	Pawn BlackPawn2;
	Pawn BlackPawn3;
	Pawn BlackPawn4;
	Pawn BlackPawn5;
	Pawn BlackPawn6;
	Pawn BlackPawn7;

	ChessBoard B;

	//Graphics

	sf::Sprite PiecesSprite[8][8];
	sf::Sprite EmptyBoardS;
	sf::Sprite Highlight[8][8];
	sf::Sprite WhiteTaken[20];
	sf::Sprite BlackTaken[20];


	sf::Texture T_Easy;
	sf::Texture T_Moderate;
	sf::Texture T_Hard;
	sf::Texture T_Check;
	sf::Sprite S_No;
	sf::Sprite S_Yes;
	sf::Texture T_Yes;
	sf::Texture T_No;
	sf::Texture T_Draw;
	sf::Sprite S_Draw;
	sf::Texture T_Clock;
	sf::Sprite S_Clock;
	sf::Texture BG;
	sf::Sprite S_BG;
	sf::Sprite S_Empty;
	sf::Texture T_Empty;
	sf::Sprite S_WhiteCheckmate;
	sf::Sprite S_BlackCheckmate;
	sf::Texture Shade_Green;
	sf::Texture Shade_Trans;
	sf::Texture Shade_Orange;
	sf::Texture Shade_Blue;
	sf::Texture Shade_Red;
	sf::Texture T_WhiteCheckmate;
	sf::Texture T_BlackCheckmate;
	sf::Texture T_EmptyBoard;
	sf::Texture T_Menu_BG;
	sf::Sprite S_Menu_BG;
	sf::Texture T_Out_BG;
	sf::Sprite S_Out_BG1;
	sf::Sprite S_Out_BG2;
	sf::Sprite S_Shade_Trans;
	// Text
	sf::Text  Menu[6];
	//Sound
	sf::Music music;
	sf::SoundBuffer B_Check;
	sf::Sound Sound_Check;
	sf::SoundBuffer B_Move1;
	sf::Sound Sound_Move1;
	sf::SoundBuffer B_Move2;
	sf::Sound Sound_Move2;
	sf::SoundBuffer B_Error;
	sf::Sound Sound_Error;

	//-- class constructor --//
	ChessGame() : Player(Player1) , BlackCastling(false) , WhiteCastling(false), WhiteOut(0), BlackOut(0) , SearchDepth(3) , captured(EMPTY), chosen_x(-1), chosen_y(-1)
	{
		defaultPosition();
	}

	//---- setting up the coordinates of the mouse clicks ----//
	int cord_index_x( float x_cord)
	{
		return ((x_cord-470)/74)+0.92;

	}
	int cord_index_y( float y_cord)
	{
		return ((y_cord-175)/75)+1.5;

	}
	float index_cord_x( int x_index)
	{
		return (74*(x_index-1))+398;

	}
	float index_cord_y( int y_index)
	{
		return (74*(y_index-1))+25;

	}
	float W_index_out_x( int x_index)
	{
		return (50*(x_index))+1020;

	}
	float W_index_out_y( int y_index)
	{
		return (50*(y_index))+0;

	}
	float B_index_out_x( int x_index)
	{
		return (50*(x_index))+1020;

	}
	float B_index_out_y( int y_index)
	{
		return (50*(y_index))+350;

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
		if(cord_index_x(x)>=0 && cord_index_x(x)<8 && cord_index_y(y)>=0 && cord_index_y(y)<8  )
			return true;
		return false;
	}
	bool inRangeXY(int x, int y , float r1x , float r1y , float r2x , float r2y)
	{
		if(x>=r1x && x<=r2x && y>=r1y && y<=r2y  )
			return true;
		return false;
	}

	//--- save the state of the board a string ---//
	string FENnotation()
	{
		string line="";
		int num=0;
		char c;
		for ( int i=0 ; i<8 ; i++ )
		{
			if(i !=0 )
				line+="\\";
			num=0;
			for ( int j=0 ; j<8 ; j++ )
			{
				if ( B.Board[i][j] == EMPTY )
					num++;
				else
				{
					if(num != 0)
					{
						c=num+'0';
						line.push_back(c);
						num=0;
					}
					if( B.Board[i][j]->pieceColor == WHITE )
						line+=B.Board[i][j]->tostring();
					else
						line+=tolower(B.Board[i][j]->tostring()[0]);
				}
			}
			if(num != 0 )
			{
				c=num+'0';
				line.push_back(c);
				num=0;
			}

		}
		if (Player == Player1)
			line.append(" w ");
		else
			line.append(" b ");
		if ( WhiteKing.isMoved == false )
		{
			if(WhiteRook1.isMoved==false)
				line.append("K");
			else
				line.append("-");
			if(WhiteRook0.isMoved==false)
				line.append("Q");
			else
				line.append("-");
		}
		else
			line.append("--");
		if ( BlackKing.isMoved==false)
		{
			if(BlackRook1.isMoved==false)
				line.append("k");
			else
				line.append("-");
			if(BlackRook0.isMoved==false)
				line.append("q");
			else
				line.append("-");
		}
		else
			line.append("--");
		line.push_back(' ');
		if ( Player == Player1 )
		{
			if(BlackEnpassant.first != -1 && BlackEnpassant.second != -1)
			{
				c=BlackEnpassant.first+'0';
				line.push_back(c);
				c=BlackEnpassant.second+'0';
				line.push_back(c);
			}
			else
				line.push_back('-');
		}
		else
		{
			if(WhiteEnpassant.first != -1 && WhiteEnpassant.second != -1)
			{
				c=WhiteEnpassant.first+'0';
				line.push_back(c);
				c=WhiteEnpassant.second+'0';
				line.push_back(c);
			}
			else
				line.push_back('-');
		}
		line.push_back(' ');
		if ( captured==EMPTY )
			line.push_back('-');
		else
		{
			if( captured->pieceColor == WHITE )
				line.append(captured->tostring());
			else
				line.push_back(tolower(captured->tostring()[0]));
		}
		return line;
	}

	//--- sounds loadifng ---//
	void LoadingSounds()
	{

		music.openFromFile("Sounds//music.wav");


		B_Check.loadFromFile("Sounds//check.wav");
		Sound_Check.setBuffer(B_Check);

		B_Move1.loadFromFile("Sounds//move1.wav");
		Sound_Move1.setBuffer(B_Move1);
		B_Move2.loadFromFile("Sounds//move2.wav");
		Sound_Move2.setBuffer(B_Move2);

		B_Error.loadFromFile("Sounds//error.wav");
		Sound_Error.setBuffer(B_Error);



		music.setLoop(true);


	}

	//--- images loading ---//
	void LoadingImages()
	{

		BG.loadFromFile("Images//Chess//"+Theme+"//BG.png");
		Shade_Green.loadFromFile("Images//Chess//Common//green.png");
		Shade_Trans.loadFromFile("Images//Chess//Common//trans.png");
		Shade_Orange.loadFromFile("Images//Chess//Common//orange.png");
		Shade_Blue.loadFromFile("Images//Chess//Common//blue.png");
		Shade_Red.loadFromFile("Images//Chess//Common//red.png");
		T_Clock.loadFromFile("Images//Chess//Common//sandclock.gif");
		T_Easy.loadFromFile("Images//Chess//Common//easy.png");
		T_Moderate.loadFromFile("Images//Chess//Common//moderate.png");
		T_Hard.loadFromFile("Images//Chess//Common//hard.png");
		T_Check.loadFromFile("Images//Chess//Common//check.gif");
		T_Yes.loadFromFile("Images//Chess//Common//yes.jpg");
		T_No.loadFromFile("Images//Chess//Common//no.jpg");
		T_WhiteCheckmate.loadFromFile("Images//Chess//Common//whitecheckmate.png");
		T_BlackCheckmate.loadFromFile("Images//Chess//Common//blackcheckmate.png");
		T_Draw.loadFromFile("Images//Chess//Common//draw.gif");
		T_EmptyBoard.loadFromFile("Images//Chess//"+Theme+"//EmptyBoard.png");
		T_Menu_BG.loadFromFile("Images//Chess//Common//Menu_BG.png");
		T_Out_BG.loadFromFile("Images//Chess//Common//Out_BG.png");

		EmptyBoardS.setTexture(T_EmptyBoard);

		for(int i=0;i<8;i++)
			for(int j=0;j<8;j++)			
				PiecesSprite[i][j].setPosition(index_cord_x(j+1),index_cord_y(i+1));

		EmptyBoardS.setPosition(400,60);

		S_Clock.setTexture(T_Clock);
		S_Clock.setPosition(130,400);
		S_WhiteCheckmate.setTexture(T_WhiteCheckmate);
		S_BlackCheckmate.setTexture(T_BlackCheckmate);
		S_Draw.setTexture(T_Draw);

		S_Yes.setTexture(T_Yes);
		S_No.setTexture(T_No);

		S_BG.setTexture(BG);
		S_Menu_BG.setTexture(T_Menu_BG);
		S_Menu_BG.setPosition(50,50);
		S_Out_BG1.setTexture(T_Menu_BG);
		S_Out_BG2.setTexture(T_Menu_BG);
		S_Out_BG1.setPosition(1015,50);
		S_Out_BG2.setPosition(1015,390);
		S_Shade_Trans.setTexture(Shade_Trans);
		S_BG.setScale((float)VMode.width/(float)BG.getSize().x,(float)VMode.height/(float)BG.getSize().y);


	}

	//---setting the default position of the board ---//
	void defaultPosition()
	{
		B.Board[0][0]=&BlackRook0;
		B.Board[0][1]=&BlackKnight0;
		B.Board[0][2]=&BlackBishop0;
		B.Board[0][3]=&BlackQueen;
		B.Board[0][4]=&BlackKing;
		B.Board[0][5]=&BlackBishop1;
		B.Board[0][6]=&BlackKnight1;
		B.Board[0][7]=&BlackRook1;

		B.Board[1][0]=&BlackPawn0;
		B.Board[1][1]=&BlackPawn1;
		B.Board[1][2]=&BlackPawn2;
		B.Board[1][3]=&BlackPawn3;
		B.Board[1][4]=&BlackPawn4;
		B.Board[1][5]=&BlackPawn5;
		B.Board[1][6]=&BlackPawn6;
		B.Board[1][7]=&BlackPawn7;

		B.Board[6][0]=&WhitePawn0;
		B.Board[6][1]=&WhitePawn1;
		B.Board[6][2]=&WhitePawn2;
		B.Board[6][3]=&WhitePawn3;
		B.Board[6][4]=&WhitePawn4;
		B.Board[6][5]=&WhitePawn5;
		B.Board[6][6]=&WhitePawn6;
		B.Board[6][7]=&WhitePawn7;

		B.Board[7][3]=&WhiteQueen;
		B.Board[7][4]=&WhiteKing;
		B.Board[7][0]=&WhiteRook0;
		B.Board[7][1]=&WhiteKnight0;
		B.Board[7][2]=&WhiteBishop0;
		B.Board[7][5]=&WhiteBishop1;
		B.Board[7][6]=&WhiteKnight1;
		B.Board[7][7]=&WhiteRook1;

		WhiteKing.pieceColor=WHITE;
		WhiteQueen.pieceColor=WHITE;
		WhiteRook0.pieceColor=WHITE;
		WhiteBishop0.pieceColor=WHITE;
		WhiteKnight0.pieceColor=WHITE;
		WhiteRook1.pieceColor=WHITE;
		WhiteBishop1.pieceColor=WHITE;
		WhiteKnight1.pieceColor=WHITE;
		WhitePawn0.pieceColor=WHITE;
		WhitePawn1.pieceColor=WHITE;
		WhitePawn2.pieceColor=WHITE;
		WhitePawn3.pieceColor=WHITE;
		WhitePawn4.pieceColor=WHITE;
		WhitePawn5.pieceColor=WHITE;
		WhitePawn6.pieceColor=WHITE;
		WhitePawn7.pieceColor=WHITE;

		BlackKing.pieceColor=BLACK;
		BlackQueen.pieceColor=BLACK;
		BlackRook0.pieceColor=BLACK;
		BlackBishop0.pieceColor=BLACK;
		BlackKnight0.pieceColor=BLACK;	
		BlackRook1.pieceColor=BLACK;
		BlackBishop1.pieceColor=BLACK;
		BlackKnight1.pieceColor=BLACK;	
		BlackPawn0.pieceColor=BLACK;
		BlackPawn1.pieceColor=BLACK;
		BlackPawn2.pieceColor=BLACK;
		BlackPawn3.pieceColor=BLACK;
		BlackPawn4.pieceColor=BLACK;
		BlackPawn5.pieceColor=BLACK;
		BlackPawn6.pieceColor=BLACK;
		BlackPawn7.pieceColor=BLACK;


		for(int i=2;i<6;i++)
			for(int j=0;j<8;j++)
				B.Board[i][j]=EMPTY;


		//Bonus Square Initialization
		for(int i=0;i<8;i++)
			for(int j=0;j<8;j++)
			{
				if(B.Board[i][j]!=EMPTY)
					B.Board[i][j]->setBonusPosition();
			}

			//Pieces Images Initialization
			for(int i=0;i<8;i++)
				for(int j=0;j<8;j++)
				{
					if(B.Board[i][j]!=EMPTY)
						B.Board[i][j]->setImage();
				}

				//UnMove Pieces
				for(int i=0;i<8;i++)
					for(int j=0;j<8;j++)
					{
						if(B.Board[i][j]!=EMPTY)
							B.Board[i][j]->isMoved=false;
					}
					BlackOut=0;
					WhiteOut=0;
	}

	//--- put the pieces pictures on their correct place on the board ---//
	void drawPieces()
	{
		for(int i=0;i<8;i++)
			for(int j=0;j<8;j++)
			{
				if(B.Board[i][j]!=EMPTY)
					PiecesSprite[i][j]=B.Board[i][j]->pieceSprite;
				else
					PiecesSprite[i][j]=S_Empty;
				PiecesSprite[i][j].setPosition(index_cord_x(j+1),index_cord_y(i+1));
			}
	}

	//---- Pop messages of draw & winning ----//
	void DrawPopMessage()
	{
		sf::VideoMode VDraw(300,300,32);
		sf::RenderWindow Window(VDraw,"Game Draw",sf::Style::Close);
		S_Draw.setScale((float)VDraw.width/(float)T_Draw.getSize().x,(float)VDraw.height/(float)T_Draw.getSize().y);
		while(Window.isOpen())
		{
			Window.draw(S_Draw);
			Window.display();
			sf::Event EDraw;
			while(Window.pollEvent(EDraw))
			{
				//Window.clear(sf::Color(255,255,255));
				Window.draw(S_Draw);
				Window.display();
				if(EDraw.type==EDraw.MouseButtonPressed || EDraw.type== sf::Event::LostFocus || (EDraw.type==sf::Event::Closed))
				{
					Window.close();
					return;
				}
			}

		}
	}
	void WhiteCheckMatePopMessage()
	{
		sf::VideoMode VWhiteCheckMate(300,300,32);
		sf::RenderWindow Window(VWhiteCheckMate,"White CheckMated",sf::Style::Close);
		S_WhiteCheckmate.setScale((float)VWhiteCheckMate.width/(float)T_WhiteCheckmate.getSize().x,(float)VWhiteCheckMate.height/(float)T_WhiteCheckmate.getSize().y);
		while(Window.isOpen())
		{
			Window.draw(S_WhiteCheckmate);
			sf::Event EWhiteCheckMate;
			Window.display();
			while(Window.pollEvent(EWhiteCheckMate))
			{
				/*	Window.clear(sf::Color(255,255,255));*/
				Window.draw(S_WhiteCheckmate);
				Window.display();
				if(EWhiteCheckMate.type==EWhiteCheckMate.MouseButtonPressed || EWhiteCheckMate.type== sf::Event::LostFocus || (EWhiteCheckMate.type==sf::Event::Closed))
				{
					Window.close();
					return;
				}
			}

		}
	}
	void BlackCheckMatePopMessage()
	{
		sf::VideoMode VBlackCheckMate(300,300,32);
		sf::RenderWindow Window(VBlackCheckMate,"Black CheckMated",sf::Style::Close);
		S_BlackCheckmate.setScale((float)VBlackCheckMate.width/(float)T_BlackCheckmate.getSize().x,(float)VBlackCheckMate.height/(float)T_BlackCheckmate.getSize().y);
		while(Window.isOpen())
		{
			sf::Event EBlackCheckMate;
			Window.draw(S_BlackCheckmate);
			Window.display();
			while(Window.pollEvent(EBlackCheckMate))
			{
				//Window.clear(sf::Color(255,255,255));
				Window.draw(S_BlackCheckmate);
				Window.display();
				if(EBlackCheckMate.type==EBlackCheckMate.MouseButtonPressed || EBlackCheckMate.type== sf::Event::LostFocus || (EBlackCheckMate.type==sf::Event::Closed))
				{
					Window.close();
					return;
				}
			}

		}
	}

	//---- asking for a new game ----//
	int NewGameMessage()
	{
		sf::VideoMode VNewGame(400,120,32);
		sf::RenderWindow Window(VNewGame,"Are You Sure ?",sf::Style::Close);
		while(Window.isOpen())
		{
			sf::Event ENewGame;
			sf::Mouse Mouse;

			sf::Text Sure;
			Sure.setString("Do you Want to Start a New Game?");
			Sure.setScale(0.7,0.9);
			Sure.setColor(sf::Color(0,0,0));
			Sure.setPosition(50,0);
			S_Yes.setPosition(60+(float)0.0*400/2.0,30);
			S_No.setPosition(60+(float)1.0*400/2.0,30);

			Window.clear();
			Window.clear(sf::Color(255,255,255));
			Window.draw(S_Yes);
			Window.draw(S_No);
			Window.draw(Sure);

			Window.display();

			while(Window.pollEvent(ENewGame))
			{
				if (ENewGame.type == sf::Event::Closed)
					Window.close();
				int x=Mouse.getPosition().x;
				if (ENewGame.type == sf::Event::MouseButtonPressed)
				{
					if(inRangeXY(x,0,490+(float)0*400/2.0,0,490+(float)1.0*400/2.0,0))
						return 1;
					else if(inRangeXY(x,0,490+(float)1.0*400/2.0,0,490+(float)2.0*400/2.0,0))
						return 2;

				}
				Window.clear();
				Window.clear(sf::Color(255,255,255));
				Window.draw(S_Yes);
				Window.draw(S_No);
				Window.draw(Sure);

				Window.display();

			}

		}
	}
	int SurePopMessage()
	{
		sf::VideoMode VSure(400,120,32);
		sf::RenderWindow Window(VSure,"Are You Sure ?",sf::Style::Close);
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

	//---- to choose between 3 themes for chess ----//
	void setTheme()
	{
		switch(ThemePopWindow())
		{
		case 1:
			Theme="Funny";
			break;
		case 2:
			Theme="Classic";
			break;

		}
		LoadingImages();

		for(int i=0;i<8;i++)
			for(int j=0;j<8;j++)
				if(B.Board[i][j]!=EMPTY)
					B.Board[i][j]->setImage();


	}
	int ThemePopWindow()
	{
		sf::VideoMode VTheme(400,150,32);
		sf::RenderWindow Window(VTheme,"Choose your Theme ?");
		while(Window.isOpen())
		{
			sf::Event ETheme;
			sf::Mouse Mouse;

			sf::Sprite Check;
			Check.setTexture(T_Check);
			if(Theme=="Funny")
				Check.setPosition(140+(float)(0)*400/2.0,120);
			else if(Theme=="Classic")
				Check.setPosition(140+(float)(1)*400/2.0,120);
			

			sf::Texture T_Funny;
			sf::Texture T_Classic;
			T_Funny.loadFromFile("Images//Chess//Common//funny.png");
			T_Classic.loadFromFile("Images//Chess//Common//classic.png");

			sf::Sprite S_Funny;
			S_Funny.setTexture(T_Funny);
			S_Funny.setPosition(20+(float)0.0*400/2.0,5);
			sf::Sprite S_Classic;
			S_Classic.setTexture(T_Classic);
			S_Classic.setPosition(20+(float)1.0*400/2.0,5);


			Window.clear();
			Window.clear(sf::Color(255,255,255));
			Window.draw(S_Funny);
			Window.draw(S_Classic);
			
			Window.draw(Check);
			Window.display();

			while(Window.pollEvent(ETheme))
			{
				if (ETheme.type == sf::Event::Closed)
					Window.close();
				if (ETheme.type == sf::Event::Resized)
					Window.close();
				if (ETheme.type == sf::Event::LostFocus)
					Window.close();




				if (ETheme.type == sf::Event::MouseButtonPressed)
				{
					int x=Mouse.getPosition().x;

					if(inRangeXY(x,0,490+(float)0*400/2.0,0,490+(float)1.0*400/2.0,0))
						return 1;
					else if(inRangeXY(x,0,490+(float)1.0*400/2.0,0,490+(float)2.0*400/2.0,0))
						return 2;
				}



							Window.clear();
			Window.clear(sf::Color(255,255,255));
			Window.draw(S_Funny);
			Window.draw(S_Classic);
			
			Window.draw(Check);
			Window.display();

			}

		}
	}

	//--- make "Turns" vector empty for a new game ---//
	void ClearTurns()
	{
		Turns.clear();
		Turns.push_back( FENnotation());
		Turns.push_back( FENnotation());
	}

	//-- setting up difficulty & its message --//
	int LevelPopMessage()
	{
		sf::VideoMode Ranking(400,120,32);
		sf::RenderWindow Window(Ranking,"Level");
		while(Window.isOpen())
		{
			sf::Event ELevel;
			sf::Mouse Mouse;

			sf::Sprite Check;
			Check.setTexture(T_Check);
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
			SearchDepth=4;
			break;
		case 3:
			SearchDepth=5;
			break;
		}
	}

	//-- pawn ranking functions & pop messages 
	int WhitePawnRankingPopMessage()
	{
		sf::VideoMode Ranking(400,120,32);
		sf::RenderWindow Window(Ranking,"Choose your Pawn Ranking",sf::Style::Titlebar);
		while(Window.isOpen())
		{
			sf::Event EPawn;
			sf::Mouse Mouse;
			sf::Sprite S_Queen=WhiteQueen.pieceSprite;
			S_Queen.setPosition((float)0.0*400/4.0,0);
			sf::Sprite S_Rook=WhiteRook0.pieceSprite;
			S_Rook.setPosition((float)1.0*400/4.0,0);
			sf::Sprite S_Bishop=WhiteBishop0.pieceSprite;
			S_Bishop.setPosition((float)2.0*400/4.0,0);
			sf::Sprite S_Knight=WhiteKnight0.pieceSprite;
			S_Knight.setPosition((float)3.0*400/4.0,0);

			Window.clear();
			Window.draw(S_Queen);
			Window.draw(S_Rook);
			Window.draw(S_Bishop);
			Window.draw(S_Knight);

			Window.display();

			while(Window.pollEvent(EPawn))
			{
				if (EPawn.type == sf::Event::Closed)
					Window.close();
				int x=Mouse.getPosition().x;
				if (EPawn.type == sf::Event::MouseButtonPressed)
				{
					if(inRangeXY(x,0,490+(float)0*400/4,0,490+(float)1.0*400/4.0,0))
						return 1;
					else if(inRangeXY(x,0,490+(float)1.0*400/4.0,0,490+(float)2.0*400/4.0,0))
						return 2;
					else if(inRangeXY(x,0,490+(float)2.0*400/4.0,0,490+(float)3.0*400/4.0,0))
						return 3;
					else if(inRangeXY(x,0,490+(float)3.0*400/4.0,0,490+(float)4.0*400/4.0,0))
						return 4;
				}


				Window.clear();
				Window.draw(S_Queen);
				Window.draw(S_Rook);
				Window.draw(S_Bishop);
				Window.draw(S_Knight);

				Window.display();

			}

		}
	}
	int CheckWhitePawnRanking()
	{
		for(int i=0;i<8;i++){
			if(B.Board[0][i]!=EMPTY && B.Board[0][i]->tostring()=="P")
				return i;
		}
		return -1;
	}
	void doWhitePawnRanking()
	{
		int choosenPiece=WhitePawnRankingPopMessage();
		if(choosenPiece==1)
			B.Board[0][CheckWhitePawnRanking()]=&WhiteQueen;
		else if(choosenPiece==2)
			B.Board[0][CheckWhitePawnRanking()]=&WhiteRook0;
		else if(choosenPiece==3)
			B.Board[0][CheckWhitePawnRanking()]=&WhiteBishop0;
		else if(choosenPiece==4)
			B.Board[0][CheckWhitePawnRanking()]=&WhiteKnight0;
	}

	int BlackPawnRankingPopMessage()
	{
		sf::VideoMode Ranking(400,120,32);
		sf::RenderWindow Window(Ranking,"Choose your Pawn Ranking",sf::Style::Titlebar);
		while(Window.isOpen())
		{
			sf::Event EPawn;
			sf::Mouse Mouse;

			sf::Sprite S_Queen=BlackQueen.pieceSprite;
			S_Queen.setPosition((float)0.0*400/4.0,0);
			sf::Sprite S_Rook=BlackRook0.pieceSprite;
			S_Rook.setPosition((float)1.0*400/4.0,0);
			sf::Sprite S_Bishop=BlackBishop0.pieceSprite;
			S_Bishop.setPosition((float)2.0*400/4.0,0);
			sf::Sprite S_Knight=BlackKnight0.pieceSprite;
			S_Knight.setPosition((float)3.0*400/4.0,0);

			Window.clear();
			Window.draw(S_Queen);
			Window.draw(S_Rook);
			Window.draw(S_Bishop);
			Window.draw(S_Knight);

			Window.display();


			while(Window.pollEvent(EPawn))
			{
				if (EPawn.type == sf::Event::Closed)
					Window.close();
				int x=Mouse.getPosition().x;
				if (EPawn.type == sf::Event::MouseButtonPressed)
				{
					if(inRangeXY(x,0,490+(float)0*400/4,0,490+(float)1.0*400/4.0,0))
						return 1;
					else if(inRangeXY(x,0,490+(float)1.0*400/4.0,0,490+(float)2.0*400/4.0,0))
						return 2;
					else if(inRangeXY(x,0,490+(float)2.0*400/4.0,0,490+(float)3.0*400/4.0,0))
						return 3;
					else if(inRangeXY(x,0,490+(float)3.0*400/4.0,0,490+(float)4.0*400/4.0,0))
						return 4;
				}

				Window.clear();
				Window.draw(S_Queen);
				Window.draw(S_Rook);
				Window.draw(S_Bishop);
				Window.draw(S_Knight);

				Window.display();

			}

		}
	}
	int CheckBlackPawnRanking()
	{
		for(int i=0;i<8;i++){
			if(B.Board[7][i]!=EMPTY && B.Board[7][i]->tostring()=="P")
				return i;
		}
		return -1;
	}
	void doBlackPawnRanking()
	{
		int choosenPiece=BlackPawnRankingPopMessage();
		if(choosenPiece==1)
			B.Board[0][CheckBlackPawnRanking()]=&BlackQueen;
		else if(choosenPiece==2)
			B.Board[0][CheckBlackPawnRanking()]=&BlackRook0;
		else if(choosenPiece==3)
			B.Board[0][CheckBlackPawnRanking()]=&BlackBishop0;
		else if(choosenPiece==4)
			B.Board[0][CheckBlackPawnRanking()]=&BlackKnight0;
	}
	void doBlackPawnRankingComputer()
	{
		if(CheckBlackPawnRanking()!=-1)
			B.Board[7][CheckBlackPawnRanking()]=&BlackQueen;
	}

	//--- draw the pieces checked by other pieces ----//
	void drawPiecesOut()
	{
		for(int i=0;i<WhiteOut;i++)
			WhiteTaken[i].setPosition(W_index_out_x(i%4),W_index_out_y(i/4));
		for(int i=0;i<BlackOut;i++)
			BlackTaken[i].setPosition(B_index_out_x(i%4),B_index_out_y(i/4));
	}

	//----- drawing the color shades on the board 7 removing them -----//
	void setShadesPosition()

	{
		for(int i=0;i<8;i++)
			for(int j=0;j<8;j++)
			{
				Highlight[i][j].setPosition(index_cord_x(j+1)+6,index_cord_y(i+2)-32);
			}
	}
	void resetShades()
	{
		for(int i=0;i<8;i++)
			for(int j=0;j<8;j++)		
				Highlight[i][j].setTexture(Shade_Trans);				
	}
	void organizeShades(int x,int y,ChessBoard _B)
	{
		if(Player==Player1)
		{
		if(y==7 && x==4 && _B.Board[y][x]!=EMPTY )
		{
			if(CheckWhiteKingRookCastling())
				Highlight[7][6].setTexture(Shade_Green);
			if(CheckWhiteQueenRookCastling())
				Highlight[7][2].setTexture(Shade_Green);
		}

		vector< pair<int,int> > V;
		vector< pair<int,int> > ::iterator iter;

		V=_B.Board[y][x]->getPossibleMovesList(y,x,_B);
		ChessPieces* DestinationPiece;
		for(int i=0;i<V.size();i++)
		{

			//Move

			DestinationPiece=_B.Board[V[i].first][V[i].second];
			_B.Board[V[i].first][V[i].second]=_B.Board[y][x];
			_B.Board[y][x]=EMPTY;


			if(WhiteKingCheck(_B))
				Highlight[V[i].first][V[i].second].setTexture(Shade_Red);
			else
				Highlight[V[i].first][V[i].second].setTexture(Shade_Green);

			//Undo Move
			_B.Board[y][x]=_B.Board[V[i].first][V[i].second];
			_B.Board[V[i].first][V[i].second]=DestinationPiece;

		}
		}
		if(Player==Player2)
					{
		if(y==0 && x==4 && _B.Board[y][x]!=EMPTY )
		{
			if(CheckBlackKingRookCastling())
				Highlight[0][6].setTexture(Shade_Green);
			if(CheckBlackQueenRookCastling())
				Highlight[0][2].setTexture(Shade_Green);
		}

		vector< pair<int,int> > V;
		vector< pair<int,int> > ::iterator iter;

		V=_B.Board[y][x]->getPossibleMovesList(y,x,_B);
		ChessPieces* DestinationPiece;
		for(int i=0;i<V.size();i++)
		{

			//Move

			DestinationPiece=_B.Board[V[i].first][V[i].second];
			_B.Board[V[i].first][V[i].second]=_B.Board[y][x];
			_B.Board[y][x]=EMPTY;


			if(BlackKingCheck(_B))
				Highlight[V[i].first][V[i].second].setTexture(Shade_Red);
			else
				Highlight[V[i].first][V[i].second].setTexture(Shade_Green);

			//Undo Move
			_B.Board[y][x]=_B.Board[V[i].first][V[i].second];
			_B.Board[V[i].first][V[i].second]=DestinationPiece;

		}
		}
	}
	void lastMoveShades(int x1, int y1, int x2, int y2)
	{
		Highlight[x1][y1].setTexture(Shade_Orange);
		Highlight[x2][y2].setTexture(Shade_Orange);
	}
	void lastSelectedShades(int x, int y)
	{
		Highlight[y][x].setTexture(Shade_Blue);
	}

	//----- specail case for draw of the game (the game is repeated 3 times) -----//
	bool threefoldRepetition()
	{
		if ( Turns.size()<10 )
			return false;
		if ( Turns[Turns.size()-1] == Turns[Turns.size()-5] && Turns[Turns.size()-1]==Turns[Turns.size()-9] )
			if (Turns[Turns.size()-2] == Turns[Turns.size()-6] && Turns[Turns.size()-2]==Turns[Turns.size()-10])
				return true;
		return false;
	}

	//----- saving game , undo game & loading it using fennotation function ------//
	void savegame()
	{
		string game;
		game = FENnotation();
		fstream fout;
		fout.open("saved_game");
		if (PlayMode==Human)
			fout<<2<<endl<<game;
		else
			fout<<1<<endl<<game;
		fout.close();
	}
	void loadFromFile()
	{
		fstream fin;
		fin.open("saved_game");
		string game;
		int typeOfGame;
		fin>>typeOfGame;
		if ( typeOfGame == 0 )
		{
			PlayMode=None;
			return;
		}
		else if ( typeOfGame == 1 )
			PlayMode=Computer;
		else if ( typeOfGame == 2 )
			PlayMode=Human;
		fin.ignore();
		getline(fin,game);
		loadgame(game);
		fin.close();
		fstream fout;
		fout.open("saved_game",ios::trunc);
		fout<<0<<endl<<endl;
		fout.close();
	}
	void loadgame(string game)
	{
		int i=0;
		bool bRook = false , wRook = false;
		for ( int x=0 ; x<8 ; x++ )
		{
			for ( int y=0 ; y<8 ; y++,i++ )
			{
				if ( game[i] == '\\' )
				{
					y--;
					continue;
				}
				if ( game[i]>='1' && game[i]<='8' )
				{
					int k = game[i]-'0';
					for ( int l=0 ; l<k ; l++,y++ )
						B.Board[x][y]=EMPTY;
					y--;
				}
				else
				{
					if ( game[i] == 'p' )
						B.Board[x][y] = &BlackPawn0;
					else if ( game[i] == 'P' )
						B.Board[x][y] = &WhitePawn0;
					else if ( game[i] == 'K' )
						B.Board[x][y] = &WhiteKing;
					else if ( game[i] == 'k' )
						B.Board[x][y] = &BlackKing;
					else if ( game[i] == 'Q' )
						B.Board[x][y] = &WhiteQueen;
					else if ( game[i] == 'q' )
						B.Board[x][y] = &BlackQueen;
					else if ( game[i] == 'B' )
						B.Board[x][y] = &WhiteBishop0;
					else if ( game[i] == 'b' )
						B.Board[x][y] = &BlackBishop0;
					else if ( game[i] == 'H' )
						B.Board[x][y] = &WhiteKnight0;
					else if ( game[i] == 'h' )
						B.Board[x][y] = &BlackKnight0;
					else if ( game[i] == 'r' )
					{
						if ( bRook==false )
						{
							B.Board[x][y] = &BlackRook0;
							bRook=true;
						}
						else
							B.Board[x][y] = &BlackRook1;
					}
					if ( game[i] == 'R' )
					{
						if (wRook==false )
						{
							B.Board[x][y] = &WhiteRook0;
							wRook=true;
						}
						else
							B.Board[x][y] = &WhiteRook1;
					}
				}
			}
		}
		i++;
		if ( game[i]== 'w')
			Player = Player1;
		else
			Player = Player2;
		i+=2;
		if ( B.Board[7][4] == &WhiteKing )
		{
			if( game[i] == 'K' ){
				B.Board[7][7]->isMoved=false;
				WhiteKing.isMoved=false;
				BlackCastling=false;
			}
			i++;
			if ( game[i] == 'Q' )
			{
				B.Board[7][0]->isMoved=false;
				BlackKing.isMoved=false;
				BlackCastling=false;
			}
			i++;
		}
		else
			i+=2;
		if ( B.Board[0][4] == &BlackKing )
		{
			if( game[i] == 'k' ){
				B.Board[0][7]->isMoved=false;
				BlackKing.isMoved=false;
				BlackCastling=false;
			}
			i++;
			if ( game[i] == 'q' ){
				B.Board[0][0]->isMoved=false;
				BlackKing.isMoved=false;
				BlackCastling=false;
			}
			i++;
		}
		else 
			i+=2;
		i++;
		if ( game[i] != '-' )
		{
			if ( game[i] == '5' )
			{
				int k;
				k = game[i]-'0';
				WhiteEnpassant.first == k;
				i++;
				k = game[i]-'0';
				WhiteEnpassant.second == k;
			}
			else
			{
				int k;
				k = game[i]-'0';
				BlackEnpassant.first == k;
				i++;
				k = game[i]-'0';
				BlackEnpassant.second == k;
			}
		}
		i+=2;
		if ( game[i] != '-' )
		{
			if ( game[i]<='Z' && game[i]>='A' )
				WhiteOut--;
			else
				BlackOut--;
		}
	}
	void UndoMove()
	{
		chosen_x=-1;
		chosen_y=-1;
		resetShades();
		string line;
		if(Turns.size()==1)return;
		line = Turns[Turns.size()-1];
		loadgame(line);
		Turns.pop_back();
		line = Turns[Turns.size()-1];
		loadgame(line);
		if ( line[line.size()-1] != '-' )
		{
			if ( line[line.size()-1]<='Z' && line[line.size()-1]>='A' )
				WhiteOut++;
			else
				BlackOut++;
		}

		drawPieces();

	}

	//---- setting the menu choices -----//
	bool Menu_Range(int x, int y)
	{
		if( y>90 && y<315 && x>95 && x<330 )return true;
		return false;
	}
	void SetMenu()
	{	
		Menu[0].setString("Main Menu");
		Menu[1].setString("New Game");
		Menu[2].setString("Undo Move");
		Menu[3].setString("Difficulty"); 
		Menu[4].setString("Theme");
		Menu[5].setString("Music On");

		for(int i=0;i<6;i++)
		{
			Menu[i].setPosition( 100,Menu_Index_Cord(i-3));
			Menu[i].setColor(sf::Color(255,255,255,50));
		}

	}
	void TextGlow(int y)
	{
		Menu[y].setColor(sf::Color(255,255,255,150));
		for(int i=0;i<6;i++)
			if(i!=y)
				Menu[i].setColor(sf::Color(255,255,255,70));
	}
	void resetGlow()
	{		
		for(int i=0;i<6;i++)
			Menu[i].setColor(sf::Color(255,255,255,70));
	}

	//--- doing enpassant movement ---//
	void doWhiteEnpassant(pair<int,int> from , pair<int,int> Wenpassant)
	{
		B.Board[Wenpassant.first-1][Wenpassant.second]=EMPTY;
		B.Board[Wenpassant.first][Wenpassant.second]= B.Board[from.first][from.second];
		B.Board[from.first][from.second] = EMPTY ;
	}
	void doBlackEnpassant(pair<int,int> from , pair<int,int> Benpassant)
	{
		B.Board[Benpassant.first+1][Benpassant.second]=EMPTY;
		B.Board[Benpassant.first][Benpassant.second]=B.Board[from.first][from.second];
		B.Board[from.first][from.second]=EMPTY;
	}

	//--- check if castling ( of rook & king ) is available ---//
	bool CheckWhiteKingRookCastling()
	{
		if(WhiteRook1.isMoved==true || WhiteKing.isMoved==true )
			return false;
		if(B.Board[7][6]!=EMPTY || B.Board[7][5]!=EMPTY)
			return false;


		if(WhiteKingCheck(B)==true)
			return false;

		doWhiteKingRookCastling();
		if(WhiteKingCheck(B)==true)
		{
			undoWhiteKingRookCastling();
			return false;
		}
		undoWhiteKingRookCastling();

		if(B.Board[7][4]!=EMPTY && B.Board[7][4]->tostring()=="K"  && B.Board[7][4]->pieceColor==WHITE )
			return true;
		else 
			return false;

	}
	bool CheckWhiteQueenRookCastling()
	{
		if(WhiteRook0.isMoved==true || WhiteKing.isMoved==true )
			return false;
		if(B.Board[7][1]!=EMPTY || B.Board[7][2]!=EMPTY || B.Board[7][3]!=EMPTY)
			return false;

		if(WhiteKingCheck(B)==true)
			return false;

		doWhiteQueenRookCastling();
		if(WhiteKingCheck(B)==true)
		{
			undoWhiteQueenRookCastling();
			return false;
		}
		undoWhiteQueenRookCastling();

		if(B.Board[7][4]!=EMPTY && B.Board[7][4]->tostring()=="K"  && B.Board[7][4]->pieceColor==WHITE )
			return true;
		else 
			return false;
	}
	bool CheckBlackKingRookCastling()
	{
		if(BlackRook1.isMoved==true || BlackKing.isMoved==true )
			return false;
		if(B.Board[0][6]!=EMPTY || B.Board[0][5]!=EMPTY)
			return false;

		if(BlackKingCheck(B)==true)
			return false;

		doBlackKingRookCastling();
		if(BlackKingCheck(B)==true)
		{
			undoBlackKingRookCastling();
			return false;
		}
		undoBlackKingRookCastling();

		if(B.Board[0][4]!=EMPTY && B.Board[0][4]->tostring()=="K"  && B.Board[0][4]->pieceColor==WHITE )
			return true;
		return false;
	}
	bool CheckBlackQueenRookCastling()
	{
		if(BlackRook0.isMoved==true || BlackKing.isMoved==true )
			return false;
		if(B.Board[0][1]!=EMPTY || B.Board[0][2]!=EMPTY || B.Board[0][3]!=EMPTY)
			return false;

		if(BlackKingCheck(B)==true)
			return false;

		doBlackQueenRookCastling();
		if(BlackKingCheck(B)==true)
		{
			doBlackQueenRookCastling();
			return false;
		}
		undoBlackQueenRookCastling();
		if(B.Board[0][4]!=EMPTY && B.Board[0][4]->tostring()=="K"  && B.Board[0][4]->pieceColor==WHITE )
			return true;
		else 
			return false;
	}

	//---- carrying out hte castling move ----//
	void doWhiteKingRookCastling()
	{
		B.Board[7][6]=&WhiteKing;
		B.Board[7][5]=&WhiteRook1;
		B.Board[7][4]=EMPTY;
		B.Board[7][7]=EMPTY;
		WhiteKing.isMoved=true;
		WhiteRook1.isMoved=true;
		WhiteCastling=true;
	}
	void doWhiteQueenRookCastling()
	{
		B.Board[7][2]=&WhiteKing;
		B.Board[7][3]=&WhiteRook0;
		B.Board[7][0]=EMPTY;
		B.Board[7][4]=EMPTY;
		WhiteKing.isMoved=true;
		WhiteRook0.isMoved=true;
		WhiteCastling=true;
	}
	void doBlackKingRookCastling()
	{
		B.Board[0][6]=&BlackKing;
		B.Board[0][5]=&BlackRook1;
		B.Board[0][4]=EMPTY;
		B.Board[0][7]=EMPTY;
		BlackKing.isMoved=true;
		BlackRook1.isMoved=true;
		BlackCastling=true;
	}
	void doBlackQueenRookCastling()
	{
		B.Board[0][2]=&BlackKing;
		B.Board[0][3]=&BlackRook0;
		B.Board[0][0]=EMPTY;
		B.Board[0][4]=EMPTY;
		BlackKing.isMoved=true;
		BlackRook0.isMoved=true;
		BlackCastling=true;
	}

	//---- undoing the castling move ----//
	void undoWhiteKingRookCastling()
	{
		B.Board[7][4]=&WhiteKing;
		B.Board[7][7]=&WhiteRook1;
		B.Board[7][5]=EMPTY;
		B.Board[7][6]=EMPTY;
		WhiteKing.isMoved=false;
		WhiteRook1.isMoved=false;
		WhiteCastling=false;
	}
	void undoWhiteQueenRookCastling() 
	{

		B.Board[7][4]=&WhiteKing;
		B.Board[7][0]=&WhiteRook0;
		B.Board[7][2]=EMPTY;
		B.Board[7][3]=EMPTY;
		WhiteKing.isMoved=false;
		WhiteRook0.isMoved=false;
		WhiteCastling=false;
	}
	void undoBlackKingRookCastling()
	{
		B.Board[0][4]=&BlackKing;
		B.Board[0][7]=&BlackRook1;
		B.Board[0][5]=EMPTY;
		B.Board[0][6]=EMPTY;
		BlackKing.isMoved=false;
		BlackRook1.isMoved=false;
		BlackCastling=false;
	}
	void undoBlackQueenRookCastling()
	{
		B.Board[0][4]=&BlackKing;
		B.Board[0][0]=&BlackRook0;
		B.Board[0][2]=EMPTY;
		B.Board[0][3]=EMPTY;
		BlackKing.isMoved=false;
		BlackRook0.isMoved=false;
		BlackCastling=false;
	}

	//--- check if a king is checked but not dead yet---//
	bool WhiteKingCheck(ChessBoard _B)
	{
		int x,y;
		WhiteKing.kingPosition.first;
		bool found=false;
		//Searching for the King
		for(int i=7;i>=0;i--){
			for(int j=7;j>=0;j--)		
				if(_B.Board[i][j]!=EMPTY && _B.Board[i][j]->tostring()=="K" && _B.Board[i][j]->pieceColor==WHITE)
				{
					WhiteKing.kingPosition.first=i;
					x=i;
					WhiteKing.kingPosition.second=j;
					y=j;
					found=true;
					break;
				}
				if(found)break;
		}
		if(!found)return false;
		//Knight Attacks
		for(int i=0;i<8;i++)
		{
			if(x+HORSE_ATTACK_X[i]>7 || x+HORSE_ATTACK_X[i]<0 || y+HORSE_ATTACK_Y[i]>7 || y+HORSE_ATTACK_Y[i]<0)continue;
			else if (_B.Board[x+HORSE_ATTACK_X[i]][y+HORSE_ATTACK_Y[i]]!=EMPTY &&  _B.Board[x+HORSE_ATTACK_X[i]][y+HORSE_ATTACK_Y[i]]->tostring()=="H" && _B.Board[x+HORSE_ATTACK_X[i]][y+HORSE_ATTACK_Y[i]]->pieceColor==BLACK)
				return true;
		}
		// Pawn Attacks
		if(x-1>=0 && y-1>=0 && _B.Board[x-1][y-1]!=EMPTY && _B.Board[x-1][y-1]->tostring()=="P" && _B.Board[x-1][y-1]->pieceColor==BLACK)
			return true;
		else if(x-1>=0 && y+1<8 && _B.Board[x-1][y+1]!=EMPTY && _B.Board[x-1][y+1]->tostring()=="P" && _B.Board[x-1][y+1]->pieceColor==BLACK)
			return true;

		// Bishop & Queen Attacks
		for(int i=x+1, j=y+1 ; i<8 && j<8 ; i++, j++){ //up-right
			if (_B.Board[i][j]!=EMPTY && ( _B.Board[i][j]->tostring()=="B" || _B.Board[i][j]->tostring()=="Q") && _B.Board[i][j]->pieceColor==BLACK)return true;					
			else if (_B.Board[i][j]==EMPTY)continue;
			else break;
		}
		for(int i=x+1, j=y-1 ; i<8 && j>=0 ; i++, j--){ //up-left
			if (_B.Board[i][j]!=EMPTY && ( _B.Board[i][j]->tostring()=="B" || _B.Board[i][j]->tostring()=="Q") && _B.Board[i][j]->pieceColor==BLACK)return true;	
			else if (_B.Board[i][j]==EMPTY)continue;
			else break;
		}
		for(int i=x-1, j=y+1 ; i>=0 && j<8 ; i--, j++){ //down-right
			if (_B.Board[i][j]!=EMPTY && ( _B.Board[i][j]->tostring()=="B" || _B.Board[i][j]->tostring()=="Q") && _B.Board[i][j]->pieceColor==BLACK)return true;					
			else if (_B.Board[i][j]==EMPTY)continue;
			else break;
		}
		for(int i=x-1, j=y-1 ;  i>=0  &&  j>=0  ; i--, j--){ //down-left
			if (_B.Board[i][j]!=EMPTY && ( _B.Board[i][j]->tostring()=="B" || _B.Board[i][j]->tostring()=="Q") && _B.Board[i][j]->pieceColor==BLACK)return true;					
			else if (_B.Board[i][j]==EMPTY)continue;
			else break;
		}
		//Rook & Queen Attacks
		for(int i=x-1;  i>=0; i--){ //Down
			if (_B.Board[i][y]!=EMPTY && ( _B.Board[i][y]->tostring()=="R" || _B.Board[i][y]->tostring()=="Q") && _B.Board[i][y]->pieceColor==BLACK)return true;					
			else if (_B.Board[i][y]==EMPTY)continue;
			else break;
		}
		for(int i=x+1;  i<8; i++){ //Up
			if (_B.Board[i][y]!=EMPTY && ( _B.Board[i][y]->tostring()=="R" || _B.Board[i][y]->tostring()=="Q") && _B.Board[i][y]->pieceColor==BLACK)return true;					
			else if (_B.Board[i][y]==EMPTY)continue;
			else break;
		}

		for(int i=y+1;  i<8; i++){ //Right
			if (_B.Board[x][i]!=EMPTY && ( _B.Board[x][i]->tostring()=="R" || _B.Board[x][i]->tostring()=="Q") && _B.Board[x][i]->pieceColor==BLACK)return true;					
			else if (_B.Board[x][i]==EMPTY)continue;
			else break;
		}

		for(int i=y-1;  i>=0; i--){ //Left
			if (_B.Board[x][i]!=EMPTY && ( _B.Board[x][i]->tostring()=="R" || _B.Board[x][i]->tostring()=="Q") && _B.Board[x][i]->pieceColor==BLACK)return true;					
			else if (_B.Board[x][i]==EMPTY)continue;
			else break;
		}
		//King Attacks
		for(int i=0;  i<8; i++)
			if(x+KING_ATTACK_X[i]>7 || x+KING_ATTACK_X[i]<0 || y+KING_ATTACK_Y[i]>7 || y+KING_ATTACK_Y[i]<0)continue;
			else if (_B.Board[x+KING_ATTACK_X[i]][y+KING_ATTACK_Y[i]]!=EMPTY &&  _B.Board[x+KING_ATTACK_X[i]][y+KING_ATTACK_Y[i]]->tostring()=="K" && _B.Board[x+KING_ATTACK_X[i]][y+KING_ATTACK_Y[i]]->pieceColor==BLACK)
				return true;

		//Otherwise Not Checked
		return false;
	}
	bool BlackKingCheck(ChessBoard _B)
	{
		int x,y;
		bool found=false;
		//Searching for the King
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++)		
				if(_B.Board[i][j]!=EMPTY && _B.Board[i][j]->tostring()=="K" && _B.Board[i][j]->pieceColor==BLACK)
				{
					BlackKing.kingPosition.first=i;
					x=i;
					BlackKing.kingPosition.second=j;
					y=j;
					found=true;
					break;
				}
				if(found)break;
		}
		if(!found)
			return false;
		//Knight Attacks
		for(int i=0;i<8;i++)
		{
			if(x+HORSE_ATTACK_X[i]>7 || x+HORSE_ATTACK_X[i]<0 || y+HORSE_ATTACK_Y[i]>7 || y+HORSE_ATTACK_Y[i]<0)continue;
			else if (_B.Board[x+HORSE_ATTACK_X[i]][y+HORSE_ATTACK_Y[i]]!=EMPTY &&  _B.Board[x+HORSE_ATTACK_X[i]][y+HORSE_ATTACK_Y[i]]->tostring()=="H" && _B.Board[x+HORSE_ATTACK_X[i]][y+HORSE_ATTACK_Y[i]]->pieceColor==WHITE)
				return true;
		}

		// Pawn Attacks
		if(x-1>=0 && y-1>=0 && _B.Board[x+1][y-1]!=EMPTY && _B.Board[x+1][y-1]->tostring()=="P" && _B.Board[x+1][y-1]->pieceColor==WHITE)
			return true;
		else if(x-1>=0 && y+1<8 && _B.Board[x+1][y+1]!=EMPTY && _B.Board[x+1][y+1]->tostring()=="P" && _B.Board[x+1][y+1]->pieceColor==WHITE)
			return true;

		// Bishop & Queen Attacks
		for(int i=x+1, j=y+1 ; i<8 && j<8 ; i++, j++){ //up-right
			if (_B.Board[i][j]!=EMPTY && ( _B.Board[i][j]->tostring()=="B" || _B.Board[i][j]->tostring()=="Q") && _B.Board[i][j]->pieceColor==WHITE)return true;					
			else if (_B.Board[i][j]==EMPTY)continue;
			else break;
		}
		for(int i=x+1, j=y-1 ; i<8 && j>=0 ; i++, j--){ //up-left
			if (_B.Board[i][j]!=EMPTY && ( _B.Board[i][j]->tostring()=="B" || _B.Board[i][j]->tostring()=="Q") && _B.Board[i][j]->pieceColor==WHITE)return true;	
			else if (_B.Board[i][j]==EMPTY)continue;
			else break;
		}
		for(int i=x-1, j=y+1 ; i>=0 && j<8 ; i--, j++){ //down-right
			if (_B.Board[i][j]!=EMPTY && ( _B.Board[i][j]->tostring()=="B" || _B.Board[i][j]->tostring()=="Q") && _B.Board[i][j]->pieceColor==WHITE)return true;					
			else if (_B.Board[i][j]==EMPTY)continue;
			else break;
		}
		for(int i=x-1, j=y-1 ;  i>=0  &&  j>=0  ; i--, j--){ //down-left
			if (_B.Board[i][j]!=EMPTY && ( _B.Board[i][j]->tostring()=="B" || _B.Board[i][j]->tostring()=="Q") && _B.Board[i][j]->pieceColor==WHITE)return true;					
			else if (_B.Board[i][j]==EMPTY)continue;
			else break;
		}
		//Rook & Queen Attacks
		for(int i=x-1;  i>=0; i--){ //Down
			if (_B.Board[i][y]!=EMPTY && ( _B.Board[i][y]->tostring()=="R" || _B.Board[i][y]->tostring()=="Q") && _B.Board[i][y]->pieceColor==WHITE)return true;					
			else if (_B.Board[i][y]==EMPTY)continue;
			else break;
		}
		for(int i=x+1;  i<8; i++){ //Up
			if (_B.Board[i][y]!=EMPTY && ( _B.Board[i][y]->tostring()=="R" || _B.Board[i][y]->tostring()=="Q") && _B.Board[i][y]->pieceColor==WHITE)return true;					
			else if (_B.Board[i][y]==EMPTY)continue;
			else break;
		}

		for(int i=y+1;  i<8; i++){ //Right
			if (_B.Board[x][i]!=EMPTY && ( _B.Board[x][i]->tostring()=="R" || _B.Board[x][i]->tostring()=="Q") && _B.Board[x][i]->pieceColor==WHITE)return true;					
			else if (_B.Board[x][i]==EMPTY)continue;
			else break;
		}

		for(int i=y-1;  i>=0; i--){ //Left
			if (_B.Board[x][i]!=EMPTY && ( _B.Board[x][i]->tostring()=="R" || _B.Board[x][i]->tostring()=="Q") && _B.Board[x][i]->pieceColor==WHITE)return true;					
			else if (_B.Board[x][i]==EMPTY)continue;
			else break;
		}

		//King Attacks
		for(int i=0;  i<8; i++)
			if(x+KING_ATTACK_X[i]>7 || x+KING_ATTACK_X[i]<0 || y+KING_ATTACK_Y[i]>7 || y+KING_ATTACK_Y[i]<0)continue;
			else if (_B.Board[x+KING_ATTACK_X[i]][y+KING_ATTACK_Y[i]]!=EMPTY &&  _B.Board[x+KING_ATTACK_X[i]][y+KING_ATTACK_Y[i]]->tostring()=="K" && _B.Board[x+KING_ATTACK_X[i]][y+KING_ATTACK_Y[i]]->pieceColor==WHITE)
				return true;

		//Otherwise Not Checked
		return false;
	}

	//--- if the king is checked & the game endes ---//
	int WhiteKingCheckmate(ChessBoard _B)
	{
		if(WhiteKingCheck(_B))
		{
			pair<int,int> temp;
			vector< pair<int,int> >::iterator it;
			vector< pair<int,int> >Z;
			ChessPieces* TempPiece;
			for(int i=0;i<8;i++)
				for(int j=0;j<8;j++)
				{
					if(_B.Board[i][j]!=EMPTY && _B.Board[i][j]->pieceColor==WHITE)
					{
						Z=_B.Board[i][j]->getPossibleMovesList(i,j,_B);
						for(it=Z.begin();it!=Z.end();it++)
						{
							temp.first=i;
							temp.second=j;
							TempPiece=_B.Board[(*it).first][(*it).second];
							// Moving
							_B.Board[(*it).first][(*it).second]=_B.Board[i][j];
							_B.Board[i][j]=EMPTY;
							//

							if(!WhiteKingCheck(_B))
							{
								//Undo Move
								_B.Board[i][j]=_B.Board[((*it).first)][(*it).second];
								_B.Board[((*it).first)][(*it).second]=TempPiece;
								//
								return 0;
							}
							//Undo Move
							_B.Board[i][j]=_B.Board[((*it).first)][(*it).second];
							_B.Board[((*it).first)][(*it).second]=TempPiece;
							//
						}
					}
				}
				return -1000000;
		}
		else return 0;
	}
	int BlackKingCheckmate(ChessBoard _B)
	{
		if(BlackKingCheck(_B))
		{
			pair<int,int> temp;
			vector< pair<int,int> >::iterator it;
			vector< pair<int,int> >Z;
			ChessPieces* TempPiece;
			for(int i=0;i<8;i++)
				for(int j=0;j<8;j++)
				{
					if(_B.Board[i][j]!=EMPTY && _B.Board[i][j]->pieceColor==BLACK)
					{
						Z=_B.Board[i][j]->getPossibleMovesList(i,j,_B);
						for(it=Z.begin();it!=Z.end();it++)
						{
							temp.first=i;
							temp.second=j;
							TempPiece=_B.Board[(*it).first][(*it).second];
							// Moving
							_B.Board[(*it).first][(*it).second]=_B.Board[i][j];
							_B.Board[i][j]=EMPTY;
							//

							if(!BlackKingCheck(_B))
							{
								//Undo Move
								_B.Board[i][j]=_B.Board[((*it).first)][(*it).second];
								_B.Board[((*it).first)][(*it).second]=TempPiece;
								//
								return 0;
							}
							//Undo Move
							_B.Board[i][j]=_B.Board[((*it).first)][(*it).second];
							_B.Board[((*it).first)][(*it).second]=TempPiece;
							//
						}
					}
				}
				return 1000000;
		}
		else return 0;
	}

	//--- if stalemate condition takes place (draw) ---//
	bool WhiteKingStalemate(ChessBoard _B)
	{
		if(!WhiteKingCheck(_B))
		{
			pair<int,int> temp;
			vector< pair<int,int> >::iterator it;
			vector< pair<int,int> >Z;
			ChessPieces* TempPiece;
			for(int i=0;i<8;i++)
				for(int j=0;j<8;j++)
				{
					if(_B.Board[i][j]!=EMPTY && _B.Board[i][j]->pieceColor==WHITE)
					{
						Z=_B.Board[i][j]->getPossibleMovesList(i,j,_B);
						for(it=Z.begin();it!=Z.end();it++)
						{
							temp.first=i;
							temp.second=j;
							TempPiece=_B.Board[(*it).first][(*it).second];
							// Moving
							_B.Board[(*it).first][(*it).second]=_B.Board[i][j];
							_B.Board[i][j]=EMPTY;
							//

							if(!WhiteKingCheck(_B))
							{
								//Undo Move
								_B.Board[i][j]=_B.Board[((*it).first)][(*it).second];
								_B.Board[((*it).first)][(*it).second]=TempPiece;
								//
								return false;
							}
							//Undo Move
							_B.Board[i][j]=_B.Board[((*it).first)][(*it).second];
							_B.Board[((*it).first)][(*it).second]=TempPiece;
							//
						}
					}
				}
				return true;
		}
		else return false;
	}
	bool BlackKingStalemate(ChessBoard _B)
	{
		if(!BlackKingCheck(_B))
		{
			pair<int,int> temp;
			vector< pair<int,int> >::iterator it;
			vector< pair<int,int> >Z;
			ChessPieces* TempPiece;
			for(int i=0;i<8;i++)
				for(int j=0;j<8;j++)
				{
					if(_B.Board[i][j]!=EMPTY && _B.Board[i][j]->pieceColor==BLACK)
					{
						Z=_B.Board[i][j]->getPossibleMovesList(i,j,_B);
						for(it=Z.begin();it!=Z.end();it++)
						{
							temp.first=i;
							temp.second=j;
							TempPiece=_B.Board[(*it).first][(*it).second];
							// Moving
							_B.Board[(*it).first][(*it).second]=_B.Board[i][j];
							_B.Board[i][j]=EMPTY;
							//

							if(!BlackKingCheck(_B))
							{
								//Undo Move
								_B.Board[i][j]=_B.Board[((*it).first)][(*it).second];
								_B.Board[((*it).first)][(*it).second]=TempPiece;
								//
								return false;
							}
							//Undo Move
							_B.Board[i][j]=_B.Board[((*it).first)][(*it).second];
							_B.Board[((*it).first)][(*it).second]=TempPiece;
							//
						}
					}
				}
				return true;
		}
		else return false;
	}

	//--- moving the chess pieces from place to place ---//
	void move( pair<short,short>from, pair <short,short>to )
	{
		//Pieces Out
		if(B.Board[to.first][to.second]!=EMPTY){
			if(B.Board[to.first][to.second]->pieceColor==WHITE)
				WhiteTaken[WhiteOut++]=B.Board[to.first][to.second]->pieceSprite;
			else
				BlackTaken[BlackOut++]=B.Board[to.first][to.second]->pieceSprite;
		}

		captured=B.Board[to.first][to.second];
		B.Board[to.first][to.second]=B.Board[from.first][from.second];		
		B.Board[from.first][from.second]=EMPTY;
		if(B.Board[to.first][to.second]!=EMPTY)
			B.Board[to.first][to.second]->isMoved=true;

		if(Player==Player1)
			Sound_Move1.play();
		else
			Sound_Move2.play();


	}

	//---- change from one player to another ----//
	void switchPlayer()
	{
		if(Player==Player1)
		{
			Player=Player2;
			BlackEnpassant.first=-1;
			BlackEnpassant.second=-1;
		}
		else
		{
			Player=Player1;
			WhiteEnpassant.first=-1;
			WhiteEnpassant.second=-1;
		}
		Turns.push_back(FENnotation());
	}

	//===== control the chess players game =====//
	void ComputerPlay();
	void HumanPlay();

	//------------------- search engine of the chess ---------------//
	int Evaluate(ChessBoard _B);
	pair<pair<int,int>,pair<int,int>> minimax( int depth , ChessBoard _B , int alpha , int beta  );
	int minSearch( int depth , ChessBoard _B , int alpha , int beta  );
	int maxSearch( int depth , ChessBoard _B , int alpha , int beta  );
	int QuiescenceMinSearch( ChessBoard _B , int alpha , int beta  );
	int QuiescenceMaxSearch( ChessBoard _B , int alpha , int beta  );

};

//===== control the chess players game =====//

//--- one player versus the computer ---//
void ChessGame::ComputerPlay()
{

	PlayMode=Computer;
	drawPieces();
	LoadingImages();
	LoadingSounds();
	setShadesPosition();
	SetMenu();
	Turns.push_back( FENnotation() );
	Turns.push_back( FENnotation() );
	sf::Mouse Mouse;
	bool firstPressed=false;
	bool firstCheck=true;
	pair<int,int> from;
	pair<int,int> to;
	bool Music=true;
	music.play();
	pair<pair<int,int>,pair<int,int>> bestMove;
	while(Window.isOpen())
	{
		sf::Event Event1;
		while(Window.pollEvent(Event1))
		{
			if (Event1.type==sf::Event::Closed)			
				Window.close();

			if( Event1.key.code == sf::Keyboard::Back &&Event1.type==sf::Event::KeyReleased )		
				UndoMove();

			resetShades();

			drawPiecesOut();

			if(Player==Player1)
			{
				if(firstCheck && threefoldRepetition() || WhiteKingStalemate(B))
				{
					DrawPopMessage();
					defaultPosition();
					ClearTurns();

					firstCheck=false;
					switch (NewGameMessage())
					{
					case 1:
						drawPieces();
						resetShades();
						break;
					case 2:
						music.pause();
						return;
						break;

					}

				}

				if(firstCheck && WhiteKingCheckmate(B)!=0 ){
					WhiteCheckMatePopMessage();
					firstCheck=false;
					defaultPosition(); 
					ClearTurns();

					switch (NewGameMessage())
					{
					case 1:
						drawPieces();
						resetShades();
						break;
					case 2:
						music.pause();
						return;
						break;

					}
				}
				if(firstCheck && WhiteKingCheck(B)){
					Sound_Check.play();
					firstCheck=false;
				}
				if(Event1.type==Event1.MouseButtonPressed && inBoardRange(Mouse.getPosition().x,Mouse.getPosition().y))
				{
					int x=cord_index_x(Mouse.getPosition().x);
					int y=cord_index_y(Mouse.getPosition().y);

					if ( (B.Board[y][x]==EMPTY && firstPressed==false ) || (B.Board[y][x]!=EMPTY && B.Board[y][x]->pieceColor==BLACK && firstPressed==false ) )
					{
						Sound_Error.play();
						chosen_x=-1;
						chosen_y=-1;
						resetShades();
						firstPressed=false;
						continue;
					}
					else if( firstPressed==false )
					{
						chosen_x=x;
						chosen_y=y;
						from.second=x;
						from.first=y;
						firstPressed=true;
					}
					else if (firstPressed==true && B.Board[y][x]!=EMPTY && B.Board[y][x]->pieceColor==WHITE)
					{
						chosen_x=x;
						chosen_y=y;
						from.second=x;
						from.first=y;
					}
					else if(firstPressed==true)
					{
						to.second=x;
						to.first=y;
						firstPressed=false;
						vector< pair<int,int> > MovesList;
						vector< pair<int,int> > ::iterator it;
						pair<int,int> temp;
						firstCheck=true;

						MovesList=B.Board[from.first][from.second]->getPossibleMovesList(from.first,from.second,B);

						if(from.first==7 && from.second==4)
						{
							if(CheckWhiteKingRookCastling())
							{
								temp.first=7;
								temp.second=6;
								MovesList.push_back(temp);
								chosen_x=-1,chosen_y=-1;
							}
							if(CheckWhiteQueenRookCastling())
							{
								temp.first=7;
								temp.second=2;
								MovesList.push_back(temp);
								chosen_x=-1,chosen_y=-1;
							}
						}

						it=find(MovesList.begin(),MovesList.end(),to);
						if(it!=MovesList.end())
						{
							if ( (*it).first == BlackEnpassant.first && (*it).second == BlackEnpassant.second)
							{
								doBlackEnpassant( from,BlackEnpassant);
								switchPlayer();
								chosen_x=-1;
								chosen_y=-1;
								drawPieces();
								continue;
							}
							if(from.first==7 && from.second==4 && to.first==7 && to.second==6){
								doWhiteKingRookCastling();
								switchPlayer();
								chosen_x=-1;
								chosen_y=-1;
								Sound_Move1.play();
								drawPieces();
								continue;
							}
							if(from.first==7 && from.second==4 && to.first==7 && to.second==2){
								doWhiteQueenRookCastling();
								switchPlayer();
								chosen_x=-1;
								chosen_y=-1;
								Sound_Move1.play();
								drawPieces();
								continue;
							}
							if ( B.Board[from.first][from.second]!=EMPTY && B.Board[from.first][from.second]->tostring() == "P" && from.first == 6 && to.first==4) 
							{
								WhiteEnpassant.first = 5;
								WhiteEnpassant.second = from.second;
								chosen_x=-1;
								chosen_y=-1;
								Sound_Move1.play();
							}
							if ( B.Board[to.first][to.second]!=EMPTY && B.Board[to.first][to.second]->tostring() == "R" )
								B.Board[to.first][to.second]->isMoved = true;
							//Do Move
							ChessPieces* DestinationPiece;
							DestinationPiece=B.Board[to.first][to.second];
							B.Board[to.first][to.second]=B.Board[from.first][from.second];
							B.Board[from.first][from.second]=EMPTY;
							//
							if(WhiteKingCheck(B)==true)
							{
								//Undo
								B.Board[from.first][from.second]=B.Board[to.first][to.second];
								B.Board[to.first][to.second]=DestinationPiece;
								Sound_Error.play();
								continue;
							}
							else
							{
								//Undo
								B.Board[from.first][from.second]=B.Board[to.first][to.second];
								B.Board[to.first][to.second]=DestinationPiece;
							}

							move(from,to);
							if(CheckWhitePawnRanking()!=-1)
								doWhitePawnRanking();
							drawPiecesOut();
							chosen_x=-1;
							chosen_y=-1;
							resetShades();
							drawPieces();
							switchPlayer();

						}
						else
						{
							chosen_x=-1;
							chosen_y=-1;
							resetShades();
							Sound_Error.play();
							continue;
						}
					}

				}
			}


			else if(Player==Player2)
			{
				if(threefoldRepetition() || BlackKingStalemate(B))
				{
					ClearTurns();
					DrawPopMessage();

					defaultPosition();
					firstCheck=false;
					switch (NewGameMessage())
					{
					case 1:
						drawPieces();
						resetShades();
						break;
					case 2:
						music.pause();
						return;
						break;

					}

				}


				if(BlackKingCheckmate(B)!=0){
					BlackCheckMatePopMessage();
					firstCheck=false;
					defaultPosition(); 
					ClearTurns();

					switch (NewGameMessage())
					{
					case 1:
						drawPieces();
						resetShades();
						break;
					case 2:
						music.pause();
						return;
						break;

					}

				}
				if(BlackKingCheck(B)){
					Sound_Check.play();
					firstCheck=false;
				}

				bestMove=minimax(SearchDepth,B,INT_MIN,INT_MAX);


				if(bestMove.first.first==0 && bestMove.first.second==4 && bestMove.second.first==0 &&bestMove.second.second==6 )
					doBlackKingRookCastling();
				else if(bestMove.first.first==0 && bestMove.first.second==4 && bestMove.second.first==0 &&bestMove.second.second==2 )
					doBlackQueenRookCastling();
				else 
					move(bestMove.first,bestMove.second);

				drawPiecesOut();
				resetShades();

				lastMoveShades(bestMove.first.first,bestMove.first.second,bestMove.second.first,bestMove.second.second);
				firstCheck=true;
				if(CheckBlackPawnRanking()!=-1)
					doBlackPawnRankingComputer();
				drawPieces();
				switchPlayer();

			}

			if(Menu_Range(Mouse.getPosition().x,Mouse.getPosition().y))
				TextGlow(Menu_Cord_Index(Mouse.getPosition().y));
			else resetGlow();



			if(Menu_Range(Mouse.getPosition().x,Mouse.getPosition().y) && Event1.type==Event1.MouseButtonPressed )
			{
				int choice = Menu_Cord_Index(Mouse.getPosition().y)+1;
				switch (choice)
				{
				case 1:
					savegame();
					music.pause();
					return;
					break;
				case 2:
					switch(SurePopMessage())
					{
					case 1:
						defaultPosition();
						drawPieces();
						resetShades();
						break;
					case 2:
						break;
					}
					break;
				case 3:
					chosen_x=-1;
					chosen_y=-1;
					UndoMove();
					UndoMove();
					drawPieces();
					break;
				case 4:
					setDifficulty();
					break;
				case 5:
					setTheme();
					break;
				case 6:
					if(Music){
						Menu[5].setString("Music Off");
						music.pause();
						Music=false;
					}
					else{
						Menu[5].setString("Music On");
						music.play();
						Music=true;
					}

					break;

				}
			}

			if( chosen_x!=-1 && chosen_y!=-1 )
				organizeShades(chosen_x,chosen_y,B);

			if(chosen_x!=-1 && chosen_y!=-1)
				lastSelectedShades(chosen_x,chosen_y);

			Window.clear(sf::Color(255,255,255));
			Window.draw(S_BG);
			Window.draw(EmptyBoardS);

			Window.draw(S_Menu_BG);
			Window.draw(S_Out_BG1);
			Window.draw(S_Out_BG2);

			for(int i=0;i<WhiteOut;i++)
				Window.draw(WhiteTaken[i]);
			for(int i=0;i<BlackOut;i++)
				Window.draw(BlackTaken[i]);

			for(int i=0;i<8;i++)
				for(int j=0;j<8;j++)
					Window.draw(Highlight[i][j]);

			for(int i=0;i<8;i++)
				for(int j=0;j<8;j++)
					Window.draw(PiecesSprite[i][j]);

			for(int i=0;i<6;i++)
				Window.draw(Menu[i]);

			if(Player==Player2)
				Window.draw(S_Clock);



			Window.display();

		}
	}
}

//--- 2 players versus each others ---//
void ChessGame::HumanPlay()
{
	PlayMode=Human;
	drawPieces();
	LoadingImages();
	LoadingSounds();
	setShadesPosition();
	SetMenu();
	Turns.push_back( FENnotation() );
	Turns.push_back( FENnotation() );
	sf::Mouse Mouse;
	bool firstPressed=false;
	bool firstCheck=true;
	pair<int,int> from;
	pair<int,int> to;
	bool Music=true;
	music.play();
	pair<pair<int,int>,pair<int,int>> bestMove;
	while(Window.isOpen())
	{
		sf::Event Event1;
		while(Window.pollEvent(Event1))
		{
			if (Event1.type==sf::Event::Closed)			
				Window.close();

			if( Event1.key.code == sf::Keyboard::Back &&Event1.type==sf::Event::KeyReleased )		
				UndoMove();

			resetShades();

			drawPiecesOut();

			if(Player==Player1)
			{
				if(firstCheck && threefoldRepetition() || WhiteKingStalemate(B))
				{
					DrawPopMessage();
					defaultPosition();
					ClearTurns();

					firstCheck=false;
					switch (NewGameMessage())
					{
					case 1:
						drawPieces();
						resetShades();
						break;
					case 2:
						return;
						break;

					}

				}

				if(firstCheck && WhiteKingCheckmate(B)!=0 ){
					WhiteCheckMatePopMessage();
					firstCheck=false;
					defaultPosition(); 
					ClearTurns();

					switch (NewGameMessage())
					{
					case 1:
						drawPieces();
						resetShades();
						break;
					case 2:
						return;
						break;

					}
				}
				if(firstCheck && WhiteKingCheck(B)){
					Sound_Check.play();
					firstCheck=false;
				}
				if(Event1.type==Event1.MouseButtonPressed && inBoardRange(Mouse.getPosition().x,Mouse.getPosition().y))
				{
					int x=cord_index_x(Mouse.getPosition().x);
					int y=cord_index_y(Mouse.getPosition().y);

					if ( (B.Board[y][x]==EMPTY && firstPressed==false ) || (B.Board[y][x]!=EMPTY && B.Board[y][x]->pieceColor==BLACK && firstPressed==false ) )
					{
						Sound_Error.play();
						chosen_x=-1;
						chosen_y=-1;
						resetShades();
						firstPressed=false;
						continue;
					}
					else if( firstPressed==false )
					{
						chosen_x=x;
						chosen_y=y;
						from.second=x;
						from.first=y;
						firstPressed=true;
					}
					else if (firstPressed==true && B.Board[y][x]!=EMPTY && B.Board[y][x]->pieceColor==WHITE)
					{
						chosen_x=x;
						chosen_y=y;
						from.second=x;
						from.first=y;
					}
					else if(firstPressed==true)
					{
						to.second=x;
						to.first=y;
						firstPressed=false;
						vector< pair<int,int> > MovesList;
						vector< pair<int,int> > ::iterator it;
						pair<int,int> temp;
						firstCheck=true;

						MovesList=B.Board[from.first][from.second]->getPossibleMovesList(from.first,from.second,B);

						if(from.first==7 && from.second==4)
						{
							if(CheckWhiteKingRookCastling())
							{
								temp.first=7;
								temp.second=6;
								MovesList.push_back(temp);
								chosen_x=-1,chosen_y=-1;
							}
							if(CheckWhiteQueenRookCastling())
							{
								temp.first=7;
								temp.second=2;
								MovesList.push_back(temp);
								chosen_x=-1,chosen_y=-1;
							}
						}

						it=find(MovesList.begin(),MovesList.end(),to);
						if(it!=MovesList.end())
						{
							if ( (*it).first == BlackEnpassant.first && (*it).second == BlackEnpassant.second)
							{
								doBlackEnpassant( from,BlackEnpassant);
								switchPlayer();
								chosen_x=-1;
								chosen_y=-1;
								drawPieces();
								continue;
							}
							if(from.first==7 && from.second==4 && to.first==7 && to.second==6){
								doWhiteKingRookCastling();
								switchPlayer();
								chosen_x=-1;
								chosen_y=-1;
								Sound_Move1.play();
								drawPieces();
								continue;
							}
							if(from.first==7 && from.second==4 && to.first==7 && to.second==2){
								doWhiteQueenRookCastling();
								switchPlayer();
								chosen_x=-1;
								chosen_y=-1;
								Sound_Move1.play();
								drawPieces();
								continue;
							}
							if ( B.Board[from.first][from.second]!=EMPTY && B.Board[from.first][from.second]->tostring() == "P" && from.first == 6 && to.first==4) 
							{
								WhiteEnpassant.first = 5;
								WhiteEnpassant.second = from.second;
								chosen_x=-1;
								chosen_y=-1;
								Sound_Move1.play();
							}
							if ( B.Board[to.first][to.second]!=EMPTY && B.Board[to.first][to.second]->tostring() == "R" )
								B.Board[to.first][to.second]->isMoved = true;
							//Do Move
							ChessPieces* DestinationPiece;
							DestinationPiece=B.Board[to.first][to.second];
							B.Board[to.first][to.second]=B.Board[from.first][from.second];
							B.Board[from.first][from.second]=EMPTY;
							//
							if(WhiteKingCheck(B)==true)
							{
								//Undo
								B.Board[from.first][from.second]=B.Board[to.first][to.second];
								B.Board[to.first][to.second]=DestinationPiece;
								Sound_Error.play();
								continue;
							}
							else
							{
								//Undo
								B.Board[from.first][from.second]=B.Board[to.first][to.second];
								B.Board[to.first][to.second]=DestinationPiece;
							}

							move(from,to);
							if(CheckWhitePawnRanking()!=-1)
								doWhitePawnRanking();
							drawPiecesOut();
							chosen_x=-1;
							chosen_y=-1;
							resetShades();
							drawPieces();
							switchPlayer();

						}
						else
						{
							chosen_x=-1;
							chosen_y=-1;
							resetShades();
							Sound_Error.play();
							continue;
						}
					}

				}
			}


			else if(Player==Player2)
			{
				if(firstCheck && threefoldRepetition() || BlackKingStalemate(B))
				{
					DrawPopMessage();
					defaultPosition();
					ClearTurns();

					firstCheck=false;
					switch (NewGameMessage())
					{
					case 1:
						drawPieces();
						resetShades();
						break;
					case 2:
						return;
						break;

					}

				}

				if(firstCheck && BlackKingCheckmate(B)!=0 ){
					BlackCheckMatePopMessage();
					firstCheck=false;
					defaultPosition(); 
					ClearTurns();

					switch (NewGameMessage())
					{
					case 1:
						drawPieces();
						resetShades();
						break;
					case 2:
						return;
						break;

					}
				}
				if(firstCheck && BlackKingCheck(B)){
					Sound_Check.play();
					firstCheck=false;
				}
				if(Event1.type==Event1.MouseButtonPressed && inBoardRange(Mouse.getPosition().x,Mouse.getPosition().y))
				{
					int x=cord_index_x(Mouse.getPosition().x);
					int y=cord_index_y(Mouse.getPosition().y);

					if ( (B.Board[y][x]==EMPTY && firstPressed==false ) || (B.Board[y][x]!=EMPTY && B.Board[y][x]->pieceColor==WHITE && firstPressed==false ) )
					{
						Sound_Error.play();
						chosen_x=-1;
						chosen_y=-1;
						resetShades();
						firstPressed=false;
						continue;
					}
					else if( firstPressed==false )
					{
						chosen_x=x;
						chosen_y=y;
						from.second=x;
						from.first=y;
						firstPressed=true;
					}
					else if (firstPressed==true && B.Board[y][x]!=EMPTY && B.Board[y][x]->pieceColor==BLACK)
					{
						chosen_x=x;
						chosen_y=y;
						from.second=x;
						from.first=y;
					}
					else if(firstPressed==true)
					{
						to.second=x;
						to.first=y;
						firstPressed=false;
						vector< pair<int,int> > MovesList;
						vector< pair<int,int> > ::iterator it;
						pair<int,int> temp;
						firstCheck=true;

						MovesList=B.Board[from.first][from.second]->getPossibleMovesList(from.first,from.second,B);

						if(from.first==0 && from.second==4)
						{
							if(CheckBlackKingRookCastling())
							{
								temp.first=0;
								temp.second=6;
								MovesList.push_back(temp);
								chosen_x=-1,chosen_y=-1;
							}
							if(CheckBlackQueenRookCastling())
							{
								temp.first=0;
								temp.second=2;
								MovesList.push_back(temp);
								chosen_x=-1,chosen_y=-1;
							}
						}

						it=find(MovesList.begin(),MovesList.end(),to);
						if(it!=MovesList.end())
						{
							if ( (*it).first == WhiteEnpassant.first && (*it).second == WhiteEnpassant.second)
							{
								doWhiteEnpassant( from,WhiteEnpassant);
								switchPlayer();
								chosen_x=-1;
								chosen_y=-1;
								Sound_Move1.play();
								drawPieces();
								continue;
							}
							if(from.first==0 && from.second==4 && to.first==0 && to.second==6){
								doBlackKingRookCastling();
								switchPlayer();
								chosen_x=-1;
								chosen_y=-1;
								Sound_Move1.play();
								drawPieces();
								continue;
							}
							if(from.first==0 && from.second==4 && to.first==0 && to.second==2){
								doBlackQueenRookCastling();
								switchPlayer();
								chosen_x=-1;
								chosen_y=-1;
								Sound_Move1.play();
								drawPieces();
								continue;
							}
							if ( B.Board[from.first][from.second]!=EMPTY && B.Board[from.first][from.second]->tostring() == "P" && from.first == 1 && to.first==3) 
							{
								BlackEnpassant.first = 2;
								BlackEnpassant.second = from.second;
								chosen_x=-1;
								chosen_y=-1;
								Sound_Move1.play();
							}
							if ( B.Board[to.first][to.second]!=EMPTY && B.Board[to.first][to.second]->tostring() == "R" )
								B.Board[to.first][to.second]->isMoved = true;
							//Do Move
							ChessPieces* DestinationPiece;
							DestinationPiece=B.Board[to.first][to.second];
							B.Board[to.first][to.second]=B.Board[from.first][from.second];
							B.Board[from.first][from.second]=EMPTY;
							//
							if(BlackKingCheck(B)==true)
							{
								//Undo
								B.Board[from.first][from.second]=B.Board[to.first][to.second];
								B.Board[to.first][to.second]=DestinationPiece;
								Sound_Error.play();
								continue;
							}
							else
							{
								//Undo
								B.Board[from.first][from.second]=B.Board[to.first][to.second];
								B.Board[to.first][to.second]=DestinationPiece;
							}

							move(from,to);
							if(CheckBlackPawnRanking()!=-1)
								doBlackPawnRankingComputer();

							drawPiecesOut();
							chosen_x=-1;
							chosen_y=-1;
							resetShades();
							drawPieces();
							switchPlayer();

						}
						else
						{
							chosen_x=-1;
							chosen_y=-1;
							resetShades();
							Sound_Error.play();
							continue;
						}
					}

				}
			}
			if(Menu_Range(Mouse.getPosition().x,Mouse.getPosition().y))
				TextGlow(Menu_Cord_Index(Mouse.getPosition().y));
			else resetGlow();



			if(Menu_Range(Mouse.getPosition().x,Mouse.getPosition().y) && Event1.type==Event1.MouseButtonPressed )
			{
				int choice = Menu_Cord_Index(Mouse.getPosition().y)+1;
				switch (choice)
				{
				case 1:
					savegame();
					return;
					break;
				case 2:
					switch(SurePopMessage())
					{
					case 1:
						defaultPosition();
						drawPieces();
						resetShades();
						break;
					case 2:
						break;
					}
					break;
				case 3:
					chosen_x=-1;
					chosen_y=-1;
					UndoMove();
					drawPieces();
					break;
				case 4:
					//setDifficulty();
					break;
				case 5:
					setTheme();
					break;
				case 6:
					if(Music){
						Menu[5].setString("Music Off");
						music.pause();
						Music=false;
					}
					else{
						Menu[5].setString("Music On");
						music.play();
						Music=true;
					}

					break;

				}
			}

			if( chosen_x!=-1 && chosen_y!=-1 )
				organizeShades(chosen_x,chosen_y,B);

			if(chosen_x!=-1 && chosen_y!=-1)
				lastSelectedShades(chosen_x,chosen_y);

			Window.clear(sf::Color(255,255,255));
			Window.draw(S_BG);
			Window.draw(EmptyBoardS);

			Window.draw(S_Menu_BG);
			Window.draw(S_Out_BG1);
			Window.draw(S_Out_BG2);

			for(int i=0;i<WhiteOut;i++)
				Window.draw(WhiteTaken[i]);
			for(int i=0;i<BlackOut;i++)
				Window.draw(BlackTaken[i]);

			for(int i=0;i<8;i++)
				for(int j=0;j<8;j++)
					Window.draw(Highlight[i][j]);

			for(int i=0;i<8;i++)
				for(int j=0;j<8;j++)
					Window.draw(PiecesSprite[i][j]);

			for(int i=0;i<6;i++)
				Window.draw(Menu[i]);

			if(Player==Player2)
				Window.draw(S_Clock);



			Window.display();

		}
	}
}

//-------------- Game AI ------------//

//==== ranking the board using ( weight - bonus - castling availability ) ====//
int ChessGame::Evaluate(ChessBoard _B)
{
	//// Material // Position Bonus // Castling Bonus // Pawn Penalty
	int material=0, bonus=0, castling=0, pawn_penalty=0;
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
		{

			if(_B.Board[i][j]!=EMPTY)
			{
				if(_B.Board[i][j]->pieceColor==WHITE){
					material-=_B.Board[i][j]->Weight;
					bonus-=_B.Board[i][j]->bonusPosition[i][j];
				}
				else {
					material+=_B.Board[i][j]->Weight;
					bonus+=_B.Board[i][j]->bonusPosition[i][j];
				}
			}
			//if(j!=0 && _B.Board[j][i]!=EMPTY && _B.Board[j][i]->tostring()=="P" && _B.Board[j][i]->pieceColor==WHITE &&
			//	_B.Board[j-1][i]!=EMPTY && _B.Board[j-1][i]->tostring()=="P" && _B.Board[j-1][i]->pieceColor==WHITE )
			//	pawn_penalty++;
			//else if(j!=0 && _B.Board[j][i]!=EMPTY && _B.Board[j][i]->tostring()=="P" && _B.Board[j][i]->pieceColor==BLACK &&
			//	   _B.Board[j-1][i]!=EMPTY && _B.Board[j-1][i]->tostring()=="P" && _B.Board[j-1][i]->pieceColor==BLACK)
			//	pawn_penalty--;		
		}
		//Castling Bonus
		if(WhiteCastling)
			castling-=150;
		if(BlackCastling)
			castling+=150;


		return material+bonus+castling/*+pawn_penalty*100*/;
}

//---- search engine using minimax algorithm with alpha beta prauning ----//
pair<pair<int,int>,pair<int,int>> ChessGame::minimax( int depth , ChessBoard _B , int alpha , int beta )
{
	short int i,j;
	pair<pair<int,int>,pair<int,int>> bestMove;
	vector< pair<int,int> > ::iterator it;
	vector< pair<int,int> > MovesList;

	if(CheckBlackQueenRookCastling()){ //Checks if Black Queen Rook Castling Available
		doBlackQueenRookCastling();
		int value = minSearch( depth-1 , _B, alpha, beta ); //Get Min VAlue in in Minimizer
		if( value > alpha ) //Choosing the Best Value
		{
			alpha = value;
			bestMove.first.first = 0;
			bestMove.first.second = 4;
			bestMove.second.first = 0;
			bestMove.second.second = 2;

		}
		undoBlackQueenRookCastling();
	}

	if(CheckBlackKingRookCastling()) //Checks if Black King Rook Castling Available
	{
		doBlackKingRookCastling();
		int value = minSearch( depth-1 , _B, alpha, beta ); //Get Min Value in in Minimizer
		if( value > alpha ) //Choosing the Best Value
		{
			alpha = value;
			bestMove.first.first = 0;
			bestMove.first.second = 4;
			bestMove.second.first = 0;
			bestMove.second.second = 6;

		}
		undoBlackKingRookCastling();
	}

	//Here we Generate All the Possible Moves
	for( i = 0; i < 8; i++ )
		for( j = 0; j < 8; j++ )
		{

			if(_B.Board[i][j]!=EMPTY && _B.Board[i][j]->pieceColor==BLACK )
			{

				MovesList=_B.Board[i][j]->getPossibleMovesList(i,j,_B); //Possible Moves of a Single Square

				for(it=MovesList.begin();it!=MovesList.end();it++)
				{
					pair<int,int> temp;
					temp.first=i,temp.second=j;
					ChessPieces* DestinationPiece;
					DestinationPiece=_B.Board[(*it).first][(*it).second]; //Stores the Destination Piece Temporarily

					//Move
					_B.Board[(*it).first][(*it).second]=_B.Board[i][j];
					_B.Board[i][j]=EMPTY;


					if(BlackKingCheck(_B)) // Check if Move leaves th King Checked
					{
						//Undo Move
						_B.Board[i][j]=_B.Board[((*it).first)][(*it).second];
						_B.Board[(*it).first][(*it).second]=DestinationPiece;
						continue;
					}

					int value = minSearch( depth-1 , _B, alpha, beta );  //Get Min Value in in Minimizer
					if( value > alpha ) //Get the Max Value
					{
						alpha = value;
						bestMove.first.first = i;
						bestMove.first.second = j;
						bestMove.second.first = (*it).first;
						bestMove.second.second = (*it).second;

					}
					//Undo Move
					_B.Board[i][j]=_B.Board[((*it).first)][(*it).second];
					_B.Board[(*it).first][(*it).second]=DestinationPiece;

				}

			}
		}

		return bestMove; // return a pai of pai of the Optimal Move
}
int ChessGame::minSearch( int depth , ChessBoard _B , int alpha , int beta  )
{
	short int i;
	short int j;
	if(depth==0/* || WhiteKingCheckmate(_B)*/)
		return Evaluate(_B)/*+WhiteKingCheckmate(_B)*/;

	//Generate All White Pieces Moves
	for( i = 0; i < 8; i++ )
		for( j = 0; j < 8; j++ )
		{
			vector< pair<int,int> > ::iterator it;
			vector< pair<int,int> > MovesList;

			if(_B.Board[i][j]!=EMPTY && _B.Board[i][j]->pieceColor==WHITE) //White Pieces Only
			{

				MovesList=_B.Board[i][j]->getPossibleMovesList(i,j,_B); // Move List of a Single Square
				for(it=MovesList.begin();it!=MovesList.end();it++) 
				{

					pair<int,int> temp;
					temp.first=i;
					temp.second=j;
					ChessPieces* DestinationPiece;
					DestinationPiece=_B.Board[(*it).first][(*it).second]; //Temp Destination Piece
					// Moving
					_B.Board[(*it).first][(*it).second]=_B.Board[i][j];
					_B.Board[i][j]=EMPTY;
					//
					if(depth==1 && DestinationPiece!=EMPTY) // if Move is Interesting Do Quiscence Search (Capture)
					{
						int value = QuiescenceMaxSearch( _B, alpha, beta );
						if( value < beta ) // Minimize
							beta = value;

					}
					else 
					{
						int value = maxSearch( depth-1 , _B, alpha, beta ); // Do Normal Search in MaxSearch
						if( value < beta ) // Minimize
							beta = value;
					}
					//Undo Move
					_B.Board[i][j]=_B.Board[(*it).first][(*it).second];		
					_B.Board[(*it).first][(*it).second]=DestinationPiece;
					//
					//Alpha Beta Cutting
					if( alpha >= beta )
						return beta;

				}

			}
		}
		return beta; //Return BestValue
}
int ChessGame::maxSearch( int depth , ChessBoard _B , int alpha , int beta  )
{

	short int i;
	short int j;
	if(depth==0/* || BlackKingCheckmate(_B)*/)
		return Evaluate(_B)/*+BlackKingCheckmate(_B)*/;

	vector< pair<int,int> > ::iterator it;
	vector< pair<int,int> > MovesList;
	int bestValue = INT_MIN;
	//Generate All Black Possible Moves
	for( i = 0; i < 8; i++ )
		for( j = 0; j < 8; j++ )
		{

			if(_B.Board[i][j]!=EMPTY && _B.Board[i][j]->pieceColor==BLACK ) // Black Pieces Only
			{
				MovesList=_B.Board[i][j]->getPossibleMovesList(i,j,_B);  // Move List of Single Square
				for(it=MovesList.begin();it!=MovesList.end();it++)
				{
					pair<int,int> temp;

					temp.first=i,temp.second=j;
					ChessPieces* DestinationPiece;
					DestinationPiece=_B.Board[(*it).first][(*it).second];
					//Moving
					_B.Board[(*it).first][(*it).second]=_B.Board[i][j];
					_B.Board[i][j]=EMPTY;
					//
					if(depth==1 && DestinationPiece!=EMPTY)
					{		
						int value = QuiescenceMinSearch( _B, alpha, beta ); // if Move is Interesting Do Quiscence Search (Capture)
						if( value > alpha )
							alpha = value;	

					}
					else
					{
						int value = minSearch( depth-1 , _B, alpha, beta ); // Do Normal Search in MinSearch
						if( value > alpha ) // Maximize
							alpha = value;
					}
					//Undo Move
					_B.Board[i][j]=_B.Board[((*it).first)][(*it).second];	
					_B.Board[(*it).first][(*it).second]=DestinationPiece;
					//

					//Alpha Beta Cutting
					if( alpha >= beta )
						return alpha;
				}

			}
		}
		return alpha; //Return Best Value
}
int ChessGame::QuiescenceMinSearch( ChessBoard _B , int alpha , int beta  )
{
	short int i;
	short int j;

	int bestValue = INT_MAX;
	for( i = 0; i < 8; i++ )
		for( j = 0; j < 8; j++ )
		{
			vector< pair<int,int> > ::iterator it;
			vector< pair<int,int> > Z;
			if(_B.Board[i][j]!=EMPTY && _B.Board[i][j]->pieceColor==WHITE)
			{

				Z=_B.Board[i][j]->getPossibleMovesList(i,j,_B);
				for(it=Z.begin();it!=Z.end();it++)
				{

					pair<int,int> temp;
					temp.first=i;
					temp.second=j;
					ChessPieces* DestinationPiece;
					DestinationPiece=_B.Board[(*it).first][(*it).second];
					
					// Moving
					_B.Board[(*it).first][(*it).second]=_B.Board[i][j];
					_B.Board[i][j]=EMPTY;
					//

					int value = Evaluate(_B);
					if( value < beta )
						beta = value;

					//Undo Move
					_B.Board[i][j]=_B.Board[(*it).first][(*it).second];		
					_B.Board[(*it).first][(*it).second]=DestinationPiece;
					//
					if( alpha >= beta )
						return beta;

				}

			}
		}
		return beta;
}
int ChessGame::QuiescenceMaxSearch( ChessBoard _B , int alpha , int beta  )
{

	short int i;
	short int j;


	vector< pair<int,int> > ::iterator it;
	vector< pair<int,int> > Z;
	int bestValue = INT_MIN;
	for( i = 0; i < 8; i++ )
		for( j = 0; j < 8; j++ )
		{

			if(_B.Board[i][j]!=EMPTY && _B.Board[i][j]->pieceColor==BLACK )
			{
				Z=_B.Board[i][j]->getPossibleMovesList(i,j,_B);
				for(it=Z.begin();it!=Z.end();it++)
				{
					pair<int,int> temp;

					temp.first=i,temp.second=j;
					ChessPieces* DestinationPiece;
					DestinationPiece=_B.Board[(*it).first][(*it).second];
					
					//Moving
					_B.Board[(*it).first][(*it).second]=_B.Board[i][j];
					_B.Board[i][j]=EMPTY;
					//
					int value = Evaluate(_B);
					if( value > alpha )
						alpha = value;	

					//Undo Move
					_B.Board[i][j]=_B.Board[((*it).first)][(*it).second];	
					_B.Board[(*it).first][(*it).second]=DestinationPiece;
					//
					if( alpha >= beta )
						return alpha;
				}

			}
		}
		return alpha;
}

#endif
