#include "Animation.h"
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <iostream>

/*
* Animation: 
* A collection of images that play after one another in succession, located on a spritesheet. Spritesheet iteration is vertical.
* 
* Animation Object:
* A physical object (rectangle) on the screen, using an Animation as the texture.
*/

const int textureCount = 5;
const sf::Texture masterSheet("sprites/masterSheet.png");
const sf::Vector2i textures[textureCount] =
{
{0,540},
	{945,270},
	{945,0},
	{0,0},
{961,0}
}; //array for the textures

int convid = 0; //convenient id, used for layer 0 stuff
std::chrono::steady_clock::time_point startTime; //program start time
std::chrono::duration<double> diffTime;
std::chrono::duration<double> diffdiffTime;
std::set<std::shared_ptr<AniObj>, AniSort> activeAnimations;

//Animation::Animation(sf::Sprite sprite, bool sc)
//{
//	sheetID = std::distance(textures, std::find(textures, textures + textureCount, sprite.getTexture()));
//	thres = 1;
//	isSimple = true;
//	textureRect = sprite.getTextureRect();
//	staticC = sc;
//}

Animation::Animation(int s,int t,sf::IntRect tr,double f):
	sheetID(s),
	thres(t),
	textureRect(tr)
{
	frameTime = std::chrono::duration<double>(f);
	if(thres == 1) isSimple = true;
}

AniObj::AniObj(Animation a,sf::Vector2f p,int l,int i,sf::Vector2f scale_, bool ac):
	animation(a),
	active(ac),
	scale(scale_)
{
	pos = p;
	layer = l;
	if(l == 0) convid++;
	id = i;
}
void AniObj::setPosition(sf::Vector2f newh)
{
	pos = newh;
}
sf::Sprite AniObj::getSprite(float xOff,float yOff) const
{
	sf::Sprite sprite(masterSheet);
	sf::Vector2i newTexturePos = {animation.textureRect.position.x+textures[animation.sheetID].x, animation.textureRect.position.y+textures[animation.sheetID].y};
	if(animation.isSimple) sprite.setTextureRect({newTexturePos, animation.textureRect.size});
	else sprite.setTextureRect(sf::IntRect(sf::Vector2<int>(newTexturePos.x,
		newTexturePos.y + (int(diffTime.count()/animation.frameTime.count())%animation.thres)*animation.textureRect.size.y),
		animation.textureRect.size));
	sprite.setPosition(pos);
	if(!staticC) sprite.move({xOff,yOff});
	sprite.scale(scale);
	return sprite;
}

void AniObj::move(float xOff, float yOff)
{
	pos.x += xOff;
	pos.y += yOff;
}
void moveSprites()
{
	for(const std::shared_ptr<AniObj> &spr : activeAnimations)
	{
		spr.get()->move(diffdiffTime.count()*spr.get()->velocity.x, diffdiffTime.count()*spr.get()->velocity.y);
	}
}
int AniObj::getLayer() const
{
	return layer;
}
int AniObj::getID() const
{
	return id;
}
sf::Vector2f AniObj::getPosition() const
{
	return pos;
}
bool AniObj::isActive() const
{
	return active;
}
void AniObj::setActive(bool ac)
{
	active = ac;
}
void removeAnimation(std::shared_ptr<AniObj> aniobj)
{
	activeAnimations.erase(aniobj);
	aniobj->setActive(false);
}
void addAnimation(std::shared_ptr<AniObj> aniobj)
{
	activeAnimations.insert(aniobj);
	aniobj->setActive(true);
}
bool AniSort::operator()(const std::shared_ptr<AniObj> &a,const std::shared_ptr<AniObj> &b) const
{
	if(a.get()->getLayer() == b.get()->getLayer())
	{
		return a.get()->getID() < b.get()->getID();
	}
	return a.get()->getLayer() < b.get()->getLayer();
}