#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <memory>

#include "itoSpr.h"
#include "Button.h"

int main(int argc, char *argv[])
{
    auto window = sf::RenderWindow(sf::VideoMode({1600, 900}), "CMake SFML Project");
    window.setFramerateLimit(144);
    window.setVerticalSyncEnabled(true);
    sf::Sprite comma(numSheet);
    comma.setTextureRect(sf::IntRect({0, 320},{16, 16}));
    dash.setTextureRect(sf::IntRect({0, 336},{16, 32}));
    int mx = sf::Mouse::getPosition(window).x,my = sf::Mouse::getPosition(window).y;
    std::vector<sf::Sprite> xNum;
    std::vector<sf::Sprite> yNum;
    //window.setMouseCursorGrabbed(true);
    sf::Sprite b1(buttonTextures);
    b1.setTextureRect(sf::IntRect({{0,0},{240,144}}));
    int count = 0;
    std::unique_ptr<uiButton> pB = std::make_unique<uiButton>(sf::FloatRect({{400,200},{240,144}}),1,[&count](){w(count);},b1);
    std::unique_ptr<uiButton> pB2 = std::make_unique<uiButton>(sf::FloatRect({{600,300},{240,144}}),2,[&count](){w1(count);},b1);
    b1.setTextureRect(sf::IntRect({0,144},{240,144}));
    b1.setPosition({400,200});
    pB.get()->hoverSprite = b1;
    b1.setPosition({600,300});
    pB2.get()->hoverSprite = b1;
    b1.setTextureRect(sf::IntRect({0,288},{240,144}));
    b1.setPosition({400,200});
    pB.get()->clickSprite = b1;
    b1.setPosition({600,300});
    pB2.get()->clickSprite = b1;
    activeButtons.insert(std::move(pB));
    activeButtons.insert(std::move(pB2));
    int mlcx = -1,mlcy = -1;
    std::vector<sf::Sprite> countInt;
    bool mouseDown = false;
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
        for(const std::unique_ptr<Button> &b : activeButtons)
        {
            auto tempButton = dynamic_cast<uiButton*>(b.get());
            if(tempButton)
            {
                window.draw(tempButton->sprite);
            }
        }
        for(sf::Sprite s : countInt)
        {
            window.draw(s);
        }
        window.display();
    }
}
