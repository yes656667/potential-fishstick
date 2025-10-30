#include "itoSpr.h"

sf::Texture numSheet("sprites/numberTest1.png");
sf::Sprite dash(numSheet);
std::vector<sf::Sprite> itoSpr(int x, int size)
{
	std::vector<sf::Sprite> nums;
	if(x < 0)
	{
		nums.push_back(dash);
		x*=-1;
	}
	std::string a = std::to_string(x);
	nums.reserve(a.length());
	for(char &c : a)
	{
		sf::Sprite num(numSheet);
		num.setTextureRect(sf::IntRect({0, size * (int(c)-48)}, {size, size}));
		nums.push_back(num);
	}
	return nums;
}

void drawCentered(std::vector<sf::Sprite> &sprites, int x, int y)
{
	float xSum = 0;
	for(sf::Sprite &spr : sprites)
	{
		xSum += int(spr.getTextureRect().size.x)/1.5;
	}
	float count = 0;
	if(x < 54 && y >= 100 || x < 42 && y >= 10 || x < 30)
	{
		for(sf::Sprite &spr : sprites)
		{
			int sprx = int(spr.getTextureRect().size.x);
			int spry = int(spr.getTextureRect().size.y);
			spr.setPosition({float(x+count), float(y-spry)});
			count += sprx/1.5;
		}
	}
	else if(x > 1500)
	{
		for(sf::Sprite &spr : sprites)
		{
			int sprx = int(spr.getTextureRect().size.x);
			int spry = int(spr.getTextureRect().size.y);
			spr.setPosition({float(x-xSum+count), float(y-spry)});
			count += sprx/1.5;
		}
	}
	else
	{
		for(sf::Sprite &spr : sprites)
		{
			int sprx = int(spr.getTextureRect().size.x);
			int spry = int(spr.getTextureRect().size.y);
			spr.setPosition({float(x-xSum/2+count), float(y-spry)});
			count += sprx/1.5;
		}
	}
	if(y < 36)
	{
		for(sf::Sprite &spr : sprites)
		{
			spr.move({0,45});
		}
	}
}