#pragma once
#include "Button.h"
#include "Animation.h"
#include <vector>

void clearCards();
void checkCardsSet();
void shuffle();
void updateCards();
void removeSet();
void replace4();
void updateHighlights();
void updateLastSet();

class setCard
{
public:
	int id = -1;
	uiButton button;
	bool activeCard = false;
	setCard(){};
};

extern std::vector<int> setCardOrder;
extern setCard* activeCards[3];
extern std::vector<setCard> openCards;
extern int score;
extern int totalCount;
void addCard(setCard &s);
void removeCard(int id);
extern AniObj lastSet[3];
extern std::chrono::duration<double> setStartTime;
extern sf::Text cardsLeftText;
extern sf::Font font;