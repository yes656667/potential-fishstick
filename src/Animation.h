#pragma once
#include <SFML/Graphics.hpp>
#include <chrono>
#include <set>
#include <memory>

extern unsigned int windowWidth;
extern unsigned int windowHeight;

namespace Tn{
	enum TextureList{
		skylines,
		skystars,
		overlay,
		cards,
		highlight,
		longHighlight
	};
}

extern const sf::Texture masterSheet;
extern const sf::Vector2i textures[]; //array for the textures
extern int convid; //convenient id, used for layer 0 stuff
extern std::chrono::steady_clock::time_point startTime; //program start time
extern std::chrono::duration<double> diffTime;
extern std::chrono::duration<double> diffdiffTime;
class Animation{
public:
	int thres; //Total number of frames
	std::chrono::duration<double> frameTime; //in seconds
	int sheetID; //ID of the spritesheet
	sf::IntRect textureRect;
	bool isSimple = false; //one frame or not
	//Animation(sf::Sprite sprite,bool sc=false);
	Animation(int s, int t, sf::IntRect tr, double f);
};
class AniObj{
private:
	mutable sf::Vector2f pos;
	int layer; //layer for drawing 
	int id;//id for drawing (draw set sorts by layer, then id)
	mutable Animation animation;
	mutable bool active;
	mutable sf::Vector2f scale;
public:
	mutable bool staticC = true; //Does it move with the player? Menus usually don't, world sprites usually do
	mutable sf::Vector2f velocity = {0, 0}; //velocity ooh scary (pixels/sec)
	mutable sf::Vector2f accel = {0, 0};
	AniObj(Animation a,sf::Vector2f p={0,0},int l=0,int i=convid,sf::Vector2f scale_={1,1},bool ac=true);
	void setPosition(sf::Vector2f newh);
	sf::Sprite getSprite(float xOff=0,float yOff=0) const;
	int getLayer() const;
	int getID() const;
	sf::Vector2f getPosition() const;
	bool isActive() const;
	void setActive(bool ac);
	void move(float xOff, float yOff);
	bool isInFrame(float xOff=0, float yOff=0) const;
};
struct AniSort{
	bool operator()(const std::shared_ptr<AniObj> &a,const std::shared_ptr<AniObj> &b) const;
};
void removeAnimation(std::shared_ptr<AniObj> aniobj);
void addAnimation(std::shared_ptr<AniObj> aniobj);
void moveSprites();
extern std::set<std::shared_ptr<AniObj>, AniSort> activeAnimations;