#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

extern sf::Texture numSheet;
extern sf::Sprite dash;
std::vector<sf::Sprite> itoSpr(int x,int size);
void drawCentered(std::vector<sf::Sprite> &sprites,int x,int y);