#include <SFML/Graphics.hpp>
#include <functional>
#include <set>
#include "Button.h"

/*
A button is a rectangle on screen that 
*/


Button::Button(sf::FloatRect h,int l, std::function<void()> e, int i,bool ac):hitbox(h),layer(l),ex(e),id(i),active(ac)
{
}

uiButton::uiButton(sf::FloatRect h,int l,std::function<void()> e,int i, bool ac):
    Button(h,l,e,i)
    {
}
std::set<std::unique_ptr<Button>,buttonSort> activeButtons;
Button* activeButton = nullptr;
Button* activeHoverButton = nullptr;

uiButton::~uiButton()
{
	//if(sprite)removeAnimation(sprite);
}
void uiButton::setSprites(std::shared_ptr<AniObj> &s1, std::shared_ptr<AniObj> &s2, std::shared_ptr<AniObj> &s3)
{
	if(sprite)removeAnimation(sprite);
	sprite = s1;
	addAnimation(sprite);
	defSprite = s1;
	hoverSprite = s2;
	clickSprite = s3;
}

bool buttonSort::operator()(const std::unique_ptr<Button> &a, const std::unique_ptr<Button> &b) const
{
    if(a->layer == b->layer)
    {
		if(a->id != b->id) return a->id < b->id;
        if(a->hitbox.position.x == b->hitbox.position.x) return a->hitbox.position.y < b->hitbox.position.y;
        else return a->hitbox.position.x < b->hitbox.position.x;
    }
    return a->layer < b->layer;
}

void w(int &wx){
    std::cout << ++wx << '\n';
}
void w1(int &wx){
    std::cout << --wx << '\n';
}
void checkButtons(int x, int y){
	std::vector<Button*> buttonsForEx;
    for(auto it = activeButtons.rbegin(); it != activeButtons.rend(); it++){
        if((**it).hitbox.contains({float(x),float(y)}))
        {
            activeButton = it->get();
            activeButton->setClicked(true);
			buttonsForEx.push_back(activeButton);
            if((*it)->hungry) break;
        }
    }
	for(Button* b : buttonsForEx)
	{
		b->ex();
	}
}
void checkHover(int x,int y)
{
    for(auto it = activeButtons.rbegin(); it != activeButtons.rend(); it++){
        if((**it).hitbox.contains({float(x),float(y)}))
        {
            auto tempButton2 = dynamic_cast<uiButton*>((*it).get());
            if(tempButton2)
            {
                if(activeHoverButton) activeHoverButton->setHovered(false);
                activeHoverButton = tempButton2;
                tempButton2->setHovered(true);
                break;
            }
        }
    }
}
void removeButton(Button* b)
{
    std::unique_ptr<Button> stale(b);
	if(activeButtons.erase(stale))
	{
	}
    stale.release();
}
void addButton(std::unique_ptr<Button> b)
{
    activeButtons.insert(std::move(b));
}