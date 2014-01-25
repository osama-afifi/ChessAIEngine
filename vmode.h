#ifndef VMODE_H
#define VMODE_H
#pragma once

//--- controling the displayed window for the game ---//
sf::VideoMode VMode=sf::VideoMode::getDesktopMode();
sf::RenderWindow Window(VMode,"Chess Game",sf::Style::Fullscreen);

#endif