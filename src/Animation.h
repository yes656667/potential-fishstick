#pragma once
#include <SFML/Graphics.hpp>
#include <chrono>
#include <set>
#include <memory>

extern const sf::Texture textures[]; //array for the textures
extern int convid; //convenient id, used for layer 0 stuff
extern std::chrono::steady_clock::time_point startTime; //program start time
extern std::chrono::duration<double> diffTime;
class Animation{
public:
	int thres; //Total number of frames
	std::chrono::duration<double> frameTime; //in seconds
	int sheetID; //ID of the spritesheet
	sf::IntRect textureRect;
	bool staticC; //Does it move with the player? Menus usually don't, world sprites usually do
	bool isSimple = false; //one frame or not
	//Animation(sf::Sprite sprite,bool sc=false);
	Animation(int s, int t, sf::IntRect tr, double f, bool sc=false);
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
	AniObj(Animation a,sf::Vector2f p={0,0},int l=0,int i=convid,sf::Vector2f scale_={1,1},bool ac=true);
	void setPosition(sf::Vector2f newh);
	sf::Sprite getSprite(float xOff=0,float yOff=0) const;
	int getLayer() const;
	int getID() const;
	sf::Vector2f getPosition() const;
	bool isActive() const;
	void setActive(bool ac);
};
struct AniSort{
	bool operator()(const std::shared_ptr<AniObj> &a,const std::shared_ptr<AniObj> &b) const;
};
extern bool operator<(const std::shared_ptr<AniObj>& a,const std::shared_ptr<AniObj>& b);
void removeAnimation(std::shared_ptr<AniObj> aniobj);
void addAnimation(std::shared_ptr<AniObj> aniobj);
extern std::set<std::shared_ptr<AniObj>, AniSort> activeAnimations;