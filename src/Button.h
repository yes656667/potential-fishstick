#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <set>
#include <functional>
#include <memory>

class Button{
public:
    Button() = default;
    sf::FloatRect hitbox;
    bool isHovered = false;
    bool isClicked = false;
    int layer;
    std::function<void()> ex;
    Button(sf::FloatRect h,int l,std::function<void()> e);
    void setClicked(bool clicked) { if(clicked == isClicked) return; isClicked = clicked; update(); }
    void setHovered(bool hovered) { if(hovered == isHovered) return; isHovered = hovered; update(); }
    virtual void update(){}
    virtual ~Button() = default;
};
class uiButton: public Button{
public:
    sf::Sprite sprite;
    sf::Sprite defSprite;
    sf::Sprite hoverSprite;
    sf::Sprite clickSprite;
    void update() override{
       
        if(isClicked)
        {
            sprite = clickSprite;
        }
        else if(isHovered)sprite = hoverSprite;
        else sprite = defSprite;
    }
    uiButton(sf::FloatRect h,int l,std::function<void()> e,sf::Sprite s, bool defaultSpr=true);
};
struct buttonSort{
    bool operator()(const std::unique_ptr<Button> &a,const std::unique_ptr<Button> &b) const;
};
void w(int &wx);
void w1(int &wx);
void checkButtons(int x, int y);
void checkHover(int x,int y);
extern sf::Texture buttonTextures;
extern std::set<std::unique_ptr<Button>,buttonSort> activeButtons;
extern Button* activeButton;
extern Button* activeHoverButton;
