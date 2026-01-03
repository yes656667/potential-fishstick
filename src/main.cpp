#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <memory>

#include "itoSpr.h"
#include "Button.h"
#include "Animation.h"
#include "primes.h"

int main(int argc,char *argv[])
{
    //todo: make window resizable and good
    sf::RenderWindow window(sf::VideoMode({1600, 900}),"CMake SFML Project",sf::Style::Default); //1600x900 window
    window.setFramerateLimit(144); //frames
    window.setVerticalSyncEnabled(true); //vsync

    sf::Sprite comma(numSheet);
    comma.setTextureRect(sf::IntRect({0, 320},{16, 16}));
    dash.setTextureRect(sf::IntRect({0, 336},{16, 32}));
    std::vector<sf::Sprite> xNum;
    std::vector<sf::Sprite> yNum;
    //window.setMouseCursorGrabbed(true);

    //sprites for the 2 buttons
    auto b1 = std::make_shared<AniObj>(Animation(1,1,{{0,0},{240,144}},1),sf::Vector2f(400,200), 1, 1);
    auto b2 = std::make_shared<AniObj>(Animation(1,1,{{0,0},{240,144}},1),sf::Vector2f(600,300),2,1);
    auto b3 = std::make_shared<AniObj>(Animation(1,1,{{0,144},{240,144}},1),sf::Vector2f(400,200),1,2);
    auto b4 = std::make_shared<AniObj>(Animation(1,1,{{0,144},{240,144}},1),sf::Vector2f(600,300),2,2);
    auto b5 = std::make_shared<AniObj>(Animation(1,1,{{0,288},{240,144}},1),sf::Vector2f(400,200),1,3);
    auto b6 = std::make_shared<AniObj>(Animation(1,1,{{0,288},{240,144}},1),sf::Vector2f(600,300),2,3);

    int count = 0; // the number that follows

    //dancing darknessspawn
    Animation dancingd(2,8,{{0,0},{39,53}},0.25);
    auto darkness = std::make_shared<AniObj>(dancingd,sf::Vector2f(666,141),0,0,sf::Vector2f(3,3));
    addAnimation(darkness);

    //todo: find better way to do this like a setSprites func in uiButton
    std::unique_ptr<uiButton> pB = std::make_unique<uiButton>(sf::FloatRect({{400,200},{240,144}}),1,[&count](){w(count);},b1, 0);
    std::unique_ptr<uiButton> pB2 = std::make_unique<uiButton>(sf::FloatRect({{600,300},{240,144}}),2,[&count](){w1(count);},b2, 0);
    pB.get()->hoverSprite = b3;
    pB2.get()->hoverSprite = b4;
    pB.get()->clickSprite = b5;
    pB2.get()->clickSprite = b6;

    //makes the buttons active
    addButton(std::move(pB));
    addButton(std::move(pB2));

    //mouse stats
    int mlcx = -1,mlcy = -1;
    int mx = sf::Mouse::getPosition(window).x,my = sf::Mouse::getPosition(window).y;
    bool mouseDown = false;

    std::vector<sf::Sprite> countInt;
    startTime = std::chrono::steady_clock::now();
    while(window.isOpen())
    {

        while(const std::optional event = window.pollEvent())
        {
            if(const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if(mouseButtonPressed->button == sf::Mouse::Button::Left)
                {
                    mlcx = mouseButtonPressed->position.x;
                    mlcy = mouseButtonPressed->position.y;
                    mouseDown = true;
                }
            }
            if(const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>())
            {
                if(mouseButtonReleased->button == sf::Mouse::Button::Left)
                {
                    mouseDown = false;
                }
            }
            if(event->is<sf::Event::Closed>())
            {
                window.close();
            }
            if(const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
            {
                mx = mouseMoved->position.x;
                my = mouseMoved->position.y;
            }
        }
        /*xNum = itoSpr(mx,32);
        yNum = itoSpr(my,32);
        xNum.insert(xNum.end(),comma);
        xNum.insert(xNum.end(),yNum.begin(),yNum.end());
        */
        if(isPrime(count))
        {
            if(!darkness->isActive())
            {
                addAnimation(darkness);
            }
        }
        else if(darkness->isActive())
        {
            removeAnimation(darkness);
        }
        diffTime = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now()-startTime);
        //Important! Checks the time difference between the start of the exe and the present. This makes animations run the same
        //on all refresh rates.

        countInt = itoSpr(count,32);
        drawCentered(countInt,mx,my);
        if(mlcx != -1)
        {
            checkButtons(mlcx,mlcy);
            mlcx = -1;
            mlcy = -1;
        }
        if(!mouseDown)
        {
            if(activeButton)
            {
                activeButton->setClicked(false);
                activeButton = nullptr;
            }
            if(activeHoverButton && !activeHoverButton->hitbox.contains({float(mx),float(my)}))
            {
                activeHoverButton->setHovered(false);
                activeHoverButton = nullptr;
            }
            checkHover(mx,my);
        }
        window.clear();
        /*for(std::set<std::unique_ptr<Button>>::reverse_iterator b = activeButtons.rbegin(); b != activeButtons.rend(); b++)
        {
            auto tempButton = dynamic_cast<uiButton*>((*b).get());
            if(tempButton)
            {
                window.draw(tempButton->sprite.getSprite());
            }
        }
        Old drawer for buttons, if I ever need it again.
        */
        for(std::set<std::shared_ptr<AniObj>>::iterator it = activeAnimations.begin(); it != activeAnimations.end(); it++)
        {
            window.draw(it->get()->getSprite());
        }
        for(sf::Sprite s : countInt)
        {
            window.draw(s);
        }
        window.display();
    }
}
