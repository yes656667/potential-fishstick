#include <SFML/Graphics.hpp>
#include <functional>
#include <set>
#include "Button.h"


sf::Texture buttonTextures("sprites/buttonSheet1.png");
Button::Button(sf::FloatRect h,int l,std::function<void()> e):hitbox(h),layer(l),ex(e)
{
}

uiButton::uiButton(sf::FloatRect h,int l,std::function<void()> e,sf::Sprite s,bool defaultSpr):
    Button(h,l,e),
    sprite(s),
    defSprite(s),
    hoverSprite(s),
    clickSprite(s){
    if(defaultSpr)
    {
        sprite.setPosition(hitbox.position);
        defSprite.setPosition(hitbox.position);
        hoverSprite.setPosition(hitbox.position);
        clickSprite.setPosition(hitbox.position);
    }
}
std::set<std::unique_ptr<Button>,buttonSort> activeButtons;
Button* activeButton = nullptr;
Button* activeHoverButton = nullptr;

bool buttonSort::operator()(const std::unique_ptr<Button> &a, const std::unique_ptr<Button> &b) const
{
    if(a->layer == b->layer)
    {
        if(a->hitbox.position.x == b->hitbox.position.x) return a->hitbox.position.y < b->hitbox.position.y;
        else return a->hitbox.position.x < b->hitbox.position.x;
    }
    return a->layer > b->layer;
}

void w(int &wx){
    std::cout << ++wx << '\n';
}
void w1(int &wx){
    std::cout << --wx << '\n';
}
void checkButtons(int x, int y){
    for(auto it = activeButtons.begin(); it != activeButtons.end(); it++){
        if((**it).hitbox.contains({float(x),float(y)}))
        {
            activeButton = it->get();
            activeButton->setClicked(true);
            (**it).ex();
            break;
        }
    }
}
void checkHover(int x,int y)
{
    for(auto it = activeButtons.begin(); it != activeButtons.end(); it++){
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


