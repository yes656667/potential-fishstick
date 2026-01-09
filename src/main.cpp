#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <memory>

#include "itoSpr.h"
#include "Button.h"
#include "Animation.h"
#include "primes.h"
#include "Set.h"

float cloudSpeed = 8;
int main(int argc, char* argv[])
{
    //todo: make window resizable and good
    sf::RenderWindow window(sf::VideoMode({1921, 1080}), "CMake SFML Project", sf::Style::None, sf::State::Windowed);
    //window.setVerticalSyncEnabled(true); //vsync
	window.setFramerateLimit(144);

	srand(time(0));
    /*sf::Sprite comma(numSheet);
    comma.setTextureRect(sf::IntRect({0, 320}, {16, 16}));
    dash.setTextureRect(sf::IntRect({0, 336}, {16, 32}));*/
    /*std::vector<sf::Sprite> xNum;
    std::vector<sf::Sprite> yNum;*/
    //window.setMouseCursorGrabbed(true);

	/*Animation bDef(1, 1, {{0, 0}, {240, 144}}, 1);
	Animation bHover(1, 1, {{0, 144}, {240, 144}}, 1);
	Animation bClick(1, 1, {{0, 288}, {240, 144}}, 1);*/
    //sprites for the 2 buttons
    /*auto b1 = std::make_shared<AniObj>(bDef, sf::Vector2f(400, 200), 1, 1);
    auto b2 = std::make_shared<AniObj>(bDef, sf::Vector2f(600, 300), 2, 1);
    auto b3 = std::make_shared<AniObj>(bHover, sf::Vector2f(400, 200), 1, 2);
    auto b4 = std::make_shared<AniObj>(bHover, sf::Vector2f(600, 300), 2, 2);
    auto b5 = std::make_shared<AniObj>(bClick, sf::Vector2f(400, 200), 1, 3);
    auto b6 = std::make_shared<AniObj>(bClick, sf::Vector2f(600, 300), 2, 3);*/

    //int count = 0; // the number that follows

    //dancing darknessspawn
    /*Animation dancingd(2, 8, {{0, 0}, {39, 53}}, 0.25);
    auto darkness = std::make_shared<AniObj>(dancingd, sf::Vector2f(666, 141), 0, 0, sf::Vector2f(3, 3));
    addAnimation(darkness);*/

	Animation bg(Tn::skystars, 1, {{0, 0}, {480, 270}}, 1);
	auto bgobj = std::make_shared<AniObj>(bg, sf::Vector2f(0, 0), -1, 0, sf::Vector2f(4, 4));
	addAnimation(bgobj);
	Animation skyline1(Tn::skylines, 1, {{0, 270}, {1440, 270}}, 1);
	Animation skyline2(Tn::skylines, 1, {{0, 540}, {1440, 270}}, 1);
	Animation skyline3(Tn::skylines, 1, {{0, 810}, {1440, 270}}, 1);
	Animation skyline4(Tn::skylines, 1, {{0, 0}, {1440, 270}}, 1);
	auto skylineobj1 = std::make_shared<AniObj>(skyline1, sf::Vector2f(0, 0), -1, 64, sf::Vector2f(4, 4));
	auto skylineobj2 = std::make_shared<AniObj>(skyline2, sf::Vector2f(0, 0), -1, 128, sf::Vector2f(4, 4));
	auto skylineobj3 = std::make_shared<AniObj>(skyline3, sf::Vector2f(0, 0), -1, 192, sf::Vector2f(4, 4));
	auto skylineobj4 = std::make_shared<AniObj>(skyline4, sf::Vector2f(0, 0), -1, 256, sf::Vector2f(4, 4));
	skylineobj1.get()->velocity = {-2*cloudSpeed, 0};
	skylineobj2.get()->velocity = {-4*cloudSpeed, 0};
	skylineobj3.get()->velocity = {-6*cloudSpeed, 0};
	skylineobj4.get()->velocity = {-8*cloudSpeed, 0};
	addAnimation(skylineobj1);
	addAnimation(skylineobj2);
	addAnimation(skylineobj3);
	addAnimation(skylineobj4);
	Animation bgo(Tn::overlay, 1, {{0, 0}, {16, 9}}, 1);
	auto bgoverlay = std::make_shared<AniObj>(bgo, sf::Vector2f(0, 0), -1, 257, sf::Vector2f(120, 120));
	std::unique_ptr<uiButton> bgButton = std::make_unique<uiButton>(sf::FloatRect({{0, 0}, {1920, 1080}}), 1, [](){replace4(); }, 0);
	bgButton.get()->setSprites(bgoverlay, bgoverlay, bgoverlay);
	bgButton.get()->simple = true;
	addButton(std::move(bgButton));
    //std::unique_ptr<uiButton> pB = std::make_unique<uiButton>(sf::FloatRect({{400,200},{240,144}}),1,[&count](){w(count);}, 0);
    //std::unique_ptr<uiButton> pB2 = std::make_unique<uiButton>(sf::FloatRect({{600,300},{240,144}}),2,[&count](){w1(count);}, 0);
	//pB.get()->setSprites(b1, b3, b5);
	//pB2.get()->setSprites(b2, b4, b6);

    //makes the buttons active
    //addButton(std::move(pB));
    //addButton(std::move(pB2));

    //mouse stats
    int mlcx = -1,mlcy = -1;
    int mx = sf::Mouse::getPosition(window).x,my = sf::Mouse::getPosition(window).y;
    bool mouseDown = false;

    /*std::vector<sf::Sprite> countInt;*/

    startTime = std::chrono::steady_clock::now();
	shuffle();
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
        /*if(isPrime(count))
        {
            if(!darkness->isActive())
            {
                addAnimation(darkness);
            }
        }
        else if(darkness->isActive())
        {
            removeAnimation(darkness);
        }*/
		//Important! Checks the time difference between the start of the exe and the present. This makes animations run the same
	    //on all refresh rates.
		diffdiffTime = diffTime;
        diffTime = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now()-startTime);
		diffdiffTime = diffTime-diffdiffTime;
		moveSprites();
		if(skylineobj1.get()->getPosition().x < -960*4) skylineobj1.get()->move(960*4, 0);
		if(skylineobj2.get()->getPosition().x < -960*4) skylineobj2.get()->move(960*4, 0);
		if(skylineobj3.get()->getPosition().x < -960*4) skylineobj3.get()->move(3840, 0);
		if(skylineobj4.get()->getPosition().x < -960*4) skylineobj4.get()->move(3840, 0);
       

        //countInt = itoSpr(count,32);
        //drawCentered(countInt,mx,my);
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
    //    for(std::set<std::unique_ptr<Button>>::reverse_iterator b = activeButtons.rbegin(); b != activeButtons.rend(); b++)
    //    {
    //        auto tempButton = dynamic_cast<uiButton*>((*b).get());
    //        if(tempButton)
    //        {
    //            /*window.draw(tempButton->sprite.getSprite());*/
				//std::cout << b->get()->id;
    //        }
    //    }
        /*Old drawer for buttons, if I ever need it again.*/
        
        for(std::set<std::shared_ptr<AniObj>>::iterator it = activeAnimations.begin(); it != activeAnimations.end(); it++)
        {
            window.draw(it->get()->getSprite());
        }
        /*for(sf::Sprite s : countInt)
        {
            window.draw(s);
        }*/
        window.display();
		sf::sleep(std::chrono::milliseconds(2));
    }
}
