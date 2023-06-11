#include "Deck.h"

Deck::Deck(int xPos, int yPos)
{
    xPos_ = xPos;
    yPos_ = yPos;
    int xCardOffset = 0, yCardOffset = 0;
    for (int suit = 0; suit < 4; ++suit)
    {
        for (int cardIndex = 1; cardIndex <= 13; ++cardIndex)
        {
            cardDeck.push_back(new Card(xPos_ + xCardOffset, yPos_ - yCardOffset, cardIndex, suit));
            ++xCardOffset;
            ++yCardOffset;
        }

    }
}

Deck::~Deck()
{
    while (!cardDeck.empty()) {
        Card* card = cardDeck.front();
        cardDeck.pop_front();
        delete card;
    }
}

void Deck::update()
{

}

void Deck::render()
{
    for (const auto& card : cardDeck)
    {
        card->render();
    }
}