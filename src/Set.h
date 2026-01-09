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
extern int totalCount;
void addCard(setCard &s);
void removeCard(int id);