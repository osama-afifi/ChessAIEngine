#ifndef GAME_H
#define GAME_H
#pragma once
#include "connect4 2.h"
#include "xo 2.h"
#include "chess2.h"

//======= the class controling the game =======//
class GameControl
{
public :
	// ======= creates object of every game ======//
	ChessGame Chess;
	xoGame Xo;
	c4Game Connect4;

	//=========== Graphics ============//

	sf::Texture T_Menu_Chess;
	sf::Texture T_Menu_Connect;
	sf::Texture T_Menu_XO;
	sf::Sprite S_Menu_Chess;
	sf::Sprite S_Menu_Connect;
	sf::Sprite S_Menu_XO;
	sf::Texture T_Main_Menu_BG;
	sf::Sprite S_Main_Menu_BG;

	sf::Text Text_Exit;

	//----Sound----//
	sf::Music music;
	sf::SoundBuffer B_MouseHover;
	sf::Sound Sound_MouseHover;
	sf::SoundBuffer B_MouseClick;
	sf::Sound Sound_MouseClick;

	//--- load mainmenu images ---//
	void LoadingMenuImages()
	{
		//Main Menu
		T_Main_Menu_BG.loadFromFile("Images//Menu//Main_Menu_BG.png");
		T_Menu_Chess.loadFromFile("Images//Menu//menu_connect.png");
		T_Menu_Connect.loadFromFile("Images//Menu//menu_chess.png");
		T_Menu_XO.loadFromFile("Images//Menu//menu_XO.png");
		//

		S_Main_Menu_BG.setTexture(T_Main_Menu_BG);
		S_Menu_XO.setTexture(T_Menu_XO);
		S_Menu_Chess.setTexture(T_Menu_Chess);
		S_Menu_Connect.setTexture(T_Menu_Connect);

	}

	//--- load mainmenu sounds ---//
	void LoadingMenuSounds()
	{
		B_MouseHover.loadFromFile("Sounds//mousehover.wav");
		Sound_MouseHover.setBuffer(B_MouseHover);

		B_MouseClick.loadFromFile("Sounds//mouseclick.wav");
		Sound_MouseClick.setBuffer(B_MouseClick);
	}

	//==== check if the mouse click is on the right places of windows ====//
	bool inRangeXY(int x,int y , float r1x , float r1y , float r2x , float r2y)
	{
		if(x>=r1x && x<=r2x && y>=r1y && y<=r2y  )
			return true;
		return false;
	}

	//------- controling the mainmenu window -------//
	int MainMenuWindow()
	{

		bool firstSoundPlay=true;

		S_Main_Menu_BG.setScale((float)VMode.width/(float)T_Main_Menu_BG.getSize().x,(float)VMode.height/(float)T_Main_Menu_BG.getSize().y);

		S_Menu_XO.setPosition(20+(float)0.0*Window.getSize().x/3.0,150);
		S_Menu_Connect.setPosition(20+(float)1.0*Window.getSize().x/3.0,150);
		S_Menu_Chess.setPosition(20+(float)2.0*Window.getSize().x/3.0,150);


		while(Window.isOpen())
		{
			sf::Event EMenu;
			sf::Mouse Mouse;
			sf::Text Text_Exit;
			Text_Exit.setString("Exit to Windows");
			Text_Exit.setPosition(560,700);
			Window.display();

			while(Window.pollEvent(EMenu))
			{
				if (EMenu.type == sf::Event::Closed)
					Window.close();
				if (EMenu.type == sf::Event::MouseButtonPressed)
				{
					int x=Mouse.getPosition().x;
					int y=Mouse.getPosition().y;

					if(inRangeXY(x,y,30,150,400,600))
						return 1;
					else if(inRangeXY(x,y,480,150,855,600))
						return 2;
					else if(inRangeXY(x,y,935,150,1310,600))
						return 3;
					else if(inRangeXY(x,y,545,700,780,750))
						return 4;
				}


				resetMainMenuGlow();

				int x=Mouse.getPosition().x;
				int y=Mouse.getPosition().y;

				if(inRangeXY(x,y,30,150,400,600)){
					if(firstSoundPlay)
						Sound_MouseHover.play();
					firstSoundPlay=false;
					MainMenuGlow(1);
				}
				else if(inRangeXY(x,y,480,150,855,600)){
					if(firstSoundPlay)
						Sound_MouseHover.play();
					firstSoundPlay=false;
					MainMenuGlow(2);
				}
				else if(inRangeXY(x,y,935,150,1310,600)){
					if(firstSoundPlay)
						Sound_MouseHover.play();
					firstSoundPlay=false;
					MainMenuGlow(3);
				}
				else if(inRangeXY(x,y,545,700,780,750)){
					if(firstSoundPlay)
						Sound_MouseHover.play();
					firstSoundPlay=false;
					MainMenuGlow(4);
				}
				else firstSoundPlay=true;

				Window.draw(S_Main_Menu_BG);
				Window.draw(S_Menu_Connect);
				Window.draw(S_Menu_Chess);
				Window.draw(Text_Exit);

				Window.draw(S_Menu_XO);

				Window.display();

			}

		}

	}
	void MainMenuChoice()
	{
		music.pause();
		while(true)
		{
			switch (MainMenuWindow())
			{
			case 1:
				Sound_MouseClick.play();
				XoPlayModeScreen();
				break;
			case 2:
				Sound_MouseClick.play();
				Chess.loadFromFile();
				switch ( PlayMode )
				{
				case None:
					ChessPlayModeScreen();
					break;
				default :
					ResumeGameScreen();
					break;
				}
				break;
			case 3:
				Sound_MouseClick.play();
				Connect4PlayModeScreen();
				break;
			case 4:
				Sound_MouseClick.play();
				exit(0);
				break;
			}
		}
	}
	void MainMenuGlow(int n)
	{

		switch(n)
		{
		case 1://-- choose to play xo game
			S_Menu_XO.setColor(sf::Color(255,255,255));
			break;
		case 2://-- choose to play connect4 game
			S_Menu_Connect.setColor(sf::Color(255,255,255));
			break;
		case 3://-- choose to play chess game
			S_Menu_Chess.setColor(sf::Color(255,255,255));
			break;
		case 4://-- choose to exit
			Text_Exit.setColor(sf::Color(255,255,255));
			break;

		}
	}
	void resetMainMenuGlow()
	{
		S_Menu_XO.setColor(sf::Color(255,255,255,150));
		S_Menu_Chess.setColor(sf::Color(255,255,255,150));
		S_Menu_Connect.setColor(sf::Color(255,255,255,150));
		Text_Exit.setColor(sf::Color(255,255,255,70));
	}

	//------ the choices screens of the game -----//
	void ResumeGameScreen()
	{
		bool firstSoundPlay=true;
		sf::Text Resume;
		sf::Text NewGame;
		sf::Text MainMenu;
		Resume.setString("Resume");
		NewGame.setString("New Game");
		MainMenu.setString("Back");
		Resume.setPosition(600,280);
		NewGame.setPosition(580,340);
		MainMenu.setPosition(620,400);
		while(Window.isOpen())
		{
			sf::Event EMenu;
			sf::Mouse Mouse;
			Window.display();

			while(Window.pollEvent(EMenu))
			{
				if (EMenu.type == sf::Event::Closed)
					Window.close();
				if (EMenu.type == sf::Event::MouseButtonPressed)
				{
					int x=Mouse.getPosition().x;
					int y=Mouse.getPosition().y;

					if(inRangeXY(x,y,550,285,750,320))
					{
						Sound_MouseClick.play();
						switch(PlayMode)
						{
						case Computer:
							Chess.ComputerPlay();//--- the chess game saved was for 1 player
							break;
						case Human:
							Chess.HumanPlay();//--- the chess game saved was for 2 players
						}
					}
					else if(inRangeXY(x,y,550,345,750,375)){
						Sound_MouseClick.play();
						ChessPlayModeScreen();
					}
					else if(inRangeXY(x,y,550,395,750,425))
					{
						Sound_MouseClick.play();
						return;
					}
				}

				Resume.setColor(sf::Color(255,255,255,70));
				NewGame.setColor(sf::Color(255,255,255,70));
				MainMenu.setColor(sf::Color(255,255,255,70));

				int x=Mouse.getPosition().x;
				int y=Mouse.getPosition().y;

				if(inRangeXY(x,y,550,285,750,320)){
					Resume.setColor(sf::Color(255,255,255));
					if(firstSoundPlay)
						Sound_MouseHover.play();
					firstSoundPlay=false;
				}
				else if(inRangeXY(x,y,550,345,750,375)){
					NewGame.setColor(sf::Color(255,255,255));
					if(firstSoundPlay)
						Sound_MouseHover.play();
					firstSoundPlay=false;
				}
				else if(inRangeXY(x,y,550,395,750,425)){
					MainMenu.setColor(sf::Color(255,255,255));
					if(firstSoundPlay)
						Sound_MouseHover.play();
					firstSoundPlay=false;
				}
				else
					firstSoundPlay=true;

				Window.clear(sf::Color(255,255,255));
				Window.draw(S_Main_Menu_BG);
				Window.draw(MainMenu);
				Window.draw(Resume);
				Window.draw(NewGame);
				Window.display();

			}

		}

	}
	void ChessPlayModeScreen()
	{
		bool firstSoundPlay=true;
		sf::Text VsComputer;
		sf::Text VsHuman;
		sf::Text MainMenu;
		VsComputer.setString("Vs Computer");
		VsHuman.setString("Vs Human");
		MainMenu.setString("Back");
		VsComputer.setPosition(565,280);
		VsHuman.setPosition(585,340);
		MainMenu.setPosition(620,400);
		while(Window.isOpen())
		{
			sf::Event EMenu;
			sf::Mouse Mouse;
			Window.display();

			while(Window.pollEvent(EMenu))
			{
				if (EMenu.type == sf::Event::Closed)
					Window.close();

				if (EMenu.type == sf::Event::MouseButtonPressed)
				{
					int x=Mouse.getPosition().x;
					int y=Mouse.getPosition().y;

					if(inRangeXY(x,y,550,285,750,320))//--- the player choose to play versus the computer
					{
						Sound_MouseClick.play();
						Chess.defaultPosition();
						PlayMode=Computer;
						Chess.ComputerPlay();

					}
					else if(inRangeXY(x,y,550,345,750,375))//--- 2 players play together 
					{
						Sound_MouseClick.play();
						Chess.defaultPosition();
						PlayMode=Human;
						Chess.HumanPlay();
					}
					else if(inRangeXY(x,y,550,395,750,425))//--- pressing back button
					{
						Sound_MouseClick.play();
						return;
					}
				}

				VsComputer.setColor(sf::Color(255,255,255,70));
				VsHuman.setColor(sf::Color(255,255,255,70));
				MainMenu.setColor(sf::Color(255,255,255,70));

				int x=Mouse.getPosition().x;
				int y=Mouse.getPosition().y;

				if(inRangeXY(x,y,550,285,750,320)){
					VsComputer.setColor(sf::Color(255,255,255));
					if(firstSoundPlay)
						Sound_MouseHover.play();
					firstSoundPlay=false;
				}
				else if(inRangeXY(x,y,550,345,750,375)){
					VsHuman.setColor(sf::Color(255,255,255));
					if(firstSoundPlay)
						Sound_MouseHover.play();
					firstSoundPlay=false;
				}
				else if(inRangeXY(x,y,550,395,750,425)){
					MainMenu.setColor(sf::Color(255,255,255));
					if(firstSoundPlay)
						Sound_MouseHover.play();
					firstSoundPlay=false;
				}
				else 
					firstSoundPlay=true;

				Window.clear(sf::Color(255,255,255));
				Window.draw(S_Main_Menu_BG);
				Window.draw(MainMenu);
				Window.draw(VsComputer);
				Window.draw(VsHuman);
				Window.display();

			}

		}
	}
	void XoPlayModeScreen()
	{
		bool firstSoundPlay=true;
		sf::Text VsComputer;
		sf::Text VsHuman;
		sf::Text MainMenu;
		VsComputer.setString("Vs Computer");
		VsHuman.setString("Vs Human");
		MainMenu.setString("Back");
		VsComputer.setPosition(565,280);
		VsHuman.setPosition(585,340);
		MainMenu.setPosition(620,400);
		while(Window.isOpen())
		{
			sf::Event EMenu;
			sf::Mouse Mouse;
			Window.display();

			while(Window.pollEvent(EMenu))
			{
				if (EMenu.type == sf::Event::Closed)
					Window.close();

				if (EMenu.type == sf::Event::MouseButtonPressed)
				{
					int x=Mouse.getPosition().x;
					int y=Mouse.getPosition().y;

					if(inRangeXY(x,y,550,285,750,320))//--- the player choose to play versus the computer
					{
						Sound_MouseClick.play();
						Xo.Default();
						Xo.ComputerPlay();
					}
					else if(inRangeXY(x,y,550,345,750,375))//--- 2 players play together 
					{
						Sound_MouseClick.play();
						Xo.Default();
						Xo.HumanPlay();
					}
					else if(inRangeXY(x,y,550,395,750,425))//--- pressing back button
					{
						Sound_MouseClick.play();
						return;
					}
				}

				VsComputer.setColor(sf::Color(255,255,255,70));
				VsHuman.setColor(sf::Color(255,255,255,70));
				MainMenu.setColor(sf::Color(255,255,255,70));

				int x=Mouse.getPosition().x;
				int y=Mouse.getPosition().y;

				if(inRangeXY(x,y,550,285,750,320)){
					VsComputer.setColor(sf::Color(255,255,255));
					if(firstSoundPlay)
						Sound_MouseHover.play();
					firstSoundPlay=false;
				}
				else if(inRangeXY(x,y,550,345,750,375)){
					VsHuman.setColor(sf::Color(255,255,255));
					if(firstSoundPlay)
						Sound_MouseHover.play();
					firstSoundPlay=false;
				}
				else if(inRangeXY(x,y,550,395,750,425)){
					MainMenu.setColor(sf::Color(255,255,255));
					if(firstSoundPlay)
						Sound_MouseHover.play();
					firstSoundPlay=false;
				}
				else 
					firstSoundPlay=true;

				Window.clear(sf::Color(255,255,255));
				Window.draw(S_Main_Menu_BG);
				Window.draw(MainMenu);
				Window.draw(VsComputer);
				Window.draw(VsHuman);
				Window.display();

			}

		}
	}
	void Connect4PlayModeScreen()
	{
		bool firstSoundPlay=true;
		sf::Text VsComputer;
		sf::Text VsHuman;
		sf::Text MainMenu;
		VsComputer.setString("Vs Computer");
		VsHuman.setString("Vs Human");
		MainMenu.setString("Back");
		VsComputer.setPosition(565,280);
		VsHuman.setPosition(585,340);
		MainMenu.setPosition(620,400);
		while(Window.isOpen())
		{
			sf::Event EMenu;
			sf::Mouse Mouse;
			Window.display();

			while(Window.pollEvent(EMenu))
			{
				if (EMenu.type == sf::Event::Closed)
					Window.close();
				if (EMenu.type == sf::Event::MouseButtonPressed)
				{
					int x=Mouse.getPosition().x;
					int y=Mouse.getPosition().y;

					if(inRangeXY(x,y,550,285,750,320))//--- the player choose to play versus the computer
					{
						Sound_MouseClick.play();
						Connect4.Default();
						Connect4.ComputerPlay();
					}
					else if(inRangeXY(x,y,550,345,750,375))//--- 2 players play together 
					{
						Sound_MouseClick.play();
						Connect4.Default();
						Connect4.HumanPlay();
					}
					else if(inRangeXY(x,y,550,395,750,425))//--- pressing back button
					{
						Sound_MouseClick.play();
						return;
					}
				}

				VsComputer.setColor(sf::Color(255,255,255,70));
				VsHuman.setColor(sf::Color(255,255,255,70));
				MainMenu.setColor(sf::Color(255,255,255,70));

				int x=Mouse.getPosition().x;
				int y=Mouse.getPosition().y;

				if(inRangeXY(x,y,550,285,750,320)){
					VsComputer.setColor(sf::Color(255,255,255));
					if(firstSoundPlay)
						Sound_MouseHover.play();
					firstSoundPlay=false;
				}
				else if(inRangeXY(x,y,550,345,750,375)){
					VsHuman.setColor(sf::Color(255,255,255));
					if(firstSoundPlay)
						Sound_MouseHover.play();
					firstSoundPlay=false;
				}
				else if(inRangeXY(x,y,550,395,750,425)){
					MainMenu.setColor(sf::Color(255,255,255));
					if(firstSoundPlay)
						Sound_MouseHover.play();
					firstSoundPlay=false;
				}
				else 
					firstSoundPlay=true;

				Window.clear(sf::Color(255,255,255));
				Window.draw(S_Main_Menu_BG);
				Window.draw(MainMenu);
				Window.draw(VsComputer);
				Window.draw(VsHuman);
				Window.display();

			}

		}
	}

};

#endif