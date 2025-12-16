#include "Animation.h"
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <iostream>
const int textureCount = 3;
const sf::Texture textures[textureCount] =
{
sf::Texture("sprites/numberTest1.png"),
sf::Texture("sprites/buttonSheet1.png"),
sf::Texture("sprites/dancingdarknessspawn1R.png")
}; //array for the textures
int convid = 0; //convenient id, used for layer 0 stuff
std::chrono::steady_clock::time_point startTime; //program start time
std::chrono::duration<double> diffTime;
std::set<std::shared_ptr<AniObj>, AniSort> activeAnimations;

//Animation::Animation(sf::Sprite sprite, bool sc)
//{
//	sheetID = std::distance(textures, std::find(textures, textures + textureCount, sprite.getTexture()));
//	thres = 1;
//	isSimple = true;
//	textureRect = sprite.getTextureRect();
//	staticC = sc;
//}

Animation::Animation(int s,int t,sf::IntRect tr,double f,bool sc):
	sheetID(s),
	thres(t),
	textureRect(tr),
	staticC(sc){
	frameTime = std::chrono::duration<double>(f);
	if(thres == 1) isSimple = true;
}

AniObj::AniObj(Animation a,sf::Vector2f p,int l,int i,bool ac):
	animation(a),
	active(ac)
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
	sf::Sprite sprite(textures[animation.sheetID]);
	if(animation.isSimple) sprite.setTextureRect(animation.textureRect);
	sprite.setTextureRect(sf::IntRect(sf::Vector2<int>(animation.textureRect.position.x,
		animation.textureRect.position.y + (int(diffTime.count()/animation.frameTime.count())%animation.thres)*animation.textureRect.size.y),
		animation.textureRect.size));
	sprite.setPosition(pos);
	sprite.move({xOff,yOff});
	return sprite;
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