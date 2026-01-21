#include "Set.h"
#include <ctime>
#include <unordered_map>
#include <algorithm>

Animation blankCard(6, 1, {{0, 37}, {105, 60}}, 1);
std::chrono::duration<double> setStartTime;
std::vector<int> setCardOrder;
setCard* activeCards[3];
AniObj lastSet[3] = {AniObj(blankCard, sf::Vector2f(80, 800), 3, 100), AniObj(blankCard, sf::Vector2f(200, 800), 3, 200), 
	AniObj(blankCard, sf::Vector2f(320, 800), 3, 300)};
std::vector<setCard> openCards(12);
int cardCount = 0;
int score = 0;
int comboCount = 0;
float curCombo = 1;
sf::Font font("arial.ttf");
sf::Text cardsLeftText(font);

namespace setScore{
	int deficit = -100; //wrong set deficit
	int gain = 500; // base gain
	int minTime = 120; //seconds until gain decreases
	float decRate = 0.5; //gain dec rate per second
	int replaceCost = -50; //cost to replace 4 cards
}

void updateCardsLeft()
{
	cardsLeftText.setString("Cards Left: " + std::to_string(setCardOrder.size()));
}
void shuffle()
{
	std::vector<int> left(81);
	score = 0;
	setStartTime = diffTime;
	setCardOrder.resize(81);
	openCards.resize(12);
	for(int i = 0; i < 81; i++)
	{
		left[i] = i;
	}
	for(int i = 0; i < 81; i++)
	{
		int num = rand() % (81-i);
		setCardOrder[i] = left[num];
		left.erase(left.begin()+num);
	}
	setCardOrder.resize(18);
	updateCardsLeft();
	updateCards();
	updateLastSet();
}
void addCard(setCard &s)
{
	if(cardCount >= 3) return;
	for(int i = 0; i < cardCount; i++)
	{
		if(activeCards[i]->id == s.id)
		{
			removeCard(s.id);
			updateHighlights();
			return;
		}
	}
	activeCards[cardCount] = &s;
	cardCount++;
	if(cardCount == 3)
	{
		checkCardsSet();
	}
	else updateHighlights();
}
void removeCard(int l)
{
	bool found = false;
	for(int i = 0; i < cardCount; i++)
	{
		if(found)
		{
			activeCards[i-1] = activeCards[i];
		}
		else if(activeCards[i]->id == l)
		{
			found = true;
		}
	}
	cardCount--;
}
void clearCards()
{
	cardCount = 0;
	
}
void checkCardsSet()
{
	int pr1[4] = {(activeCards[0]->id)%3, (activeCards[0]->id/3)%3, (activeCards[0]->id/9)%3, (activeCards[0]->id/27)%3};
	int pr2[4] = {(activeCards[1]->id)%3, (activeCards[1]->id/3)%3, (activeCards[1]->id/9)%3, (activeCards[1]->id/27)%3};
	int pr3[4] = {(activeCards[2]->id)%3, (activeCards[2]->id/3)%3, (activeCards[2]->id/9)%3, (activeCards[2]->id/27)%3};
	for(int i = 0; i < 4; i++)
	{
		if(pr1[i] == pr2[i])
		{
			if(pr3[i] != pr2[i])
			{
				clearCards();
				updateHighlights();
				score += int(setScore::deficit*curCombo);
				return;
			}
		}
		else if(pr3[i] == pr2[i] || pr3[i] == pr1[i])
		{
			clearCards();
			updateHighlights();
			score += int(setScore::deficit*curCombo);
			return;
		}
	}
	int totalGain = setScore::gain-std::max(int(setScore::decRate*(diffTime.count()-setStartTime.count()-setScore::minTime)), 0);
	if(totalGain > 0) score += int(totalGain*curCombo);
	comboCount++;
	updateLastSet();
	clearCards();
	updateHighlights();
	removeSet();
	updateCards();
	updateCardsLeft();
}
void replace4()
{
	if(setCardOrder.size() < 15) return;
	score += int(setScore::replaceCost*curCombo);
	clearCards();
	updateHighlights();
	for(int i = 0; i < 4; i++)
	{
		removeAnimation(openCards[i].button.sprite);
	}
	for(int i = 0; i < 4; i++)
	{
		int bronya = rand() % (setCardOrder.size()-12) + 12; //hsr reference haha
		int temp = setCardOrder[bronya];
		setCardOrder[bronya] = setCardOrder[i];
		setCardOrder[i] = temp;
	}
	updateCards();
}
void removeSet()
{
	
	int cardsRemoved = 0;
	int idsToRemove[3] = {-1, -1, -1};
	bool moreThan12 = setCardOrder.size()>12;
	for(int i = 0; i < 12 && i < setCardOrder.size() && cardsRemoved < 3; i++)
	{
		if(setCardOrder[i] == activeCards[cardsRemoved]->id)
		{
			if(setCardOrder.size() <= 12)
			{
				idsToRemove[cardsRemoved] = i;
			}
			else{
				setCardOrder[i] = setCardOrder[12];
				setCardOrder.erase(setCardOrder.begin()+12);
			}
			i = -1;
			cardsRemoved++;
		}
	}
	if(moreThan12) return;
	for(int i = 0; i < 3; i++)
	{
		int j = 0;
		for(int i2 = 0; i2 < i; i2++)
		{
			if(idsToRemove[i2] < idsToRemove[i]) j++;
		}
		setCardOrder.erase(setCardOrder.begin() + idsToRemove[i] - j);
	}
}
void updateLastSet()
{
	for(int i = 0; i < 3; i++)
	{
		removeAnimation(std::make_shared<AniObj>(lastSet[i]));
	}
	if(cardCount == 0)
	{
		
		for(int i = 0; i < 3; i++)
		{
			lastSet[i] = AniObj(blankCard, sf::Vector2f(100+i*120, 900), 3, i*100+100);
		}
	}
	else
	{
		for(int i = 0; i < 3; i++)
		{
			lastSet[i] = AniObj(Animation(Tn::cards, 1, {{(activeCards[i]->id/9)*105, (activeCards[i]->id%9)*60}, {105, 60}}, 1), 
				sf::Vector2f(100+i*120, 900), 3, i*100+100);
		}
	}
	for(int i = 0; i < 3; i++)
	{
		addAnimation(std::make_shared<AniObj>(lastSet[i]));
	}
}
void updateCards()
{
	activeButton = nullptr;
	activeHoverButton = nullptr;
	for(int i = 0; i < 12; i++)
	{
		if(openCards[i].id > -1)
		{
			removeButton(&(openCards[i].button));
		}
	}
	for(int i = 0; i < 12 && i < setCardOrder.size(); i++)
	{
		
		openCards[i].id = setCardOrder[i];
		uiButton newButton({{float(540 + i/4*440), float(30+i%4*260)}, {420, 240}}, 2, [](){}, i);
		AniObj cardAniObj(Animation(Tn::cards, 1, {{(openCards[i].id/9)*105, (openCards[i].id%9)*60}, {105, 60}}, 1), {float(540 + i/4*440), float(30+i%4*260)}, 2, openCards[i].id, {4, 4});
		std::shared_ptr<AniObj> cardAniObjptr = std::make_shared<AniObj>(cardAniObj);
		newButton.ex = [=](){addCard(openCards[i]); };
		openCards[i].button = newButton;
		openCards[i].activeCard = false;
		openCards[i].button.simple = true;
		openCards[i].button.setSprites(cardAniObjptr, cardAniObjptr, cardAniObjptr);
		std::unique_ptr<uiButton> newButtonptr = std::make_unique<uiButton>(openCards[i].button);
		addButton(std::move(newButtonptr));	
	}
}

void updateHighlights()
{
	for(int i = 0; i < 12 && i < openCards.size(); i++)
	{
		AniObj garb(Animation(-1, 1, {{0, 0}, {0, 0}},1), {0, 0}, 1, (openCards[i]).id);
		removeAnimation(std::make_shared<AniObj>(garb));
	}
	for(int i = 0; i < cardCount; i++)
	{
		if(!activeCards[i]) continue;
		std::shared_ptr<AniObj> cardHighlight = std::make_shared<AniObj>
			(Animation(Tn::highlight, 1, {{0, 0}, {105, 60}}, 1), (*activeCards[i]).button.hitbox.position, 1, (*activeCards[i]).id, sf::Vector2f(4,4));
		addAnimation(cardHighlight);
	}
}