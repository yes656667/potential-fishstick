#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <set>
#include <functional>
#include <memory>
#include "Animation.h"

class Button{
public:
    Button() = default;
    sf::FloatRect hitbox;
    bool isHovered = false;
    bool isClicked = false;
    int layer;
    bool active;
    std::function<void()> ex;
    Button(sf::FloatRect h,int l, std::function<void()> e,int i=convid, bool ac=true);
    void setClicked(bool clicked) { if(clicked == isClicked) return; isClicked = clicked; update(); }
    void setHovered(bool hovered) { if(hovered == isHovered) return; isHovered = hovered; update(); }
    virtual void update(){}
    virtual ~Button() = default;
};
class uiButton: public Button{
public:
    std::shared_ptr<AniObj> sprite;
    std::shared_ptr<AniObj> defSprite;
    std::shared_ptr<AniObj> hoverSprite;
    std::shared_ptr<AniObj> clickSprite;
    void update() override{
       
        if(isClicked)
        {
            sprite = clickSprite;
            removeAnimation(defSprite);
            removeAnimation(hoverSprite);
            addAnimation(clickSprite);
        }
        else if(isHovered)
        {
            sprite = hoverSprite;
            removeAnimation(defSprite);
            addAnimation(hoverSprite);
            removeAnimation(clickSprite);
        }
        else
        {
            sprite = defSprite;
            addAnimation(defSprite);
            removeAnimation(hoverSprite);
            removeAnimation(clickSprite);
        }
    }
    uiButton(sf::FloatRect h,int l, std::function<void()> e,std::shared_ptr<AniObj> s, int i=convid,bool defaultSpr=true, bool ac=true);
};
struct buttonSort{
    bool operator()(const std::unique_ptr<Button> &a,const std::unique_ptr<Button> &b) const;
};
void w(int &wx);
void w1(int &wx);
void checkButtons(int x, int y);
void checkHover(int x,int y);
void removeButton(Button* b);
void addButton(std::unique_ptr<Button> b);
extern sf::Texture buttonTextures;
extern std::set<std::unique_ptr<Button>,buttonSort> activeButtons;
extern Button* activeButton;
extern Button* activeHoverButton;
