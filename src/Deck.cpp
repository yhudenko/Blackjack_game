#include "Deck.h"
#include <map>
#include <algorithm>
#include <random>
#include <chrono>

std::map<int, SDL_Rect> dictionaryCardBackSideRect{ {0,  {0, 0, 932, 1448}}, {1, {1070, 0, 932, 1448}}, {2, {2140, 0, 932, 1448}} };
const int CARD_HEIGHT = 140;
const int CARD_WIDTH = 100;

Deck::Deck(const int xPos, const int yPos) : BaseObject(new SDL_Rect{ xPos,yPos,CARD_WIDTH,CARD_HEIGHT })
{
    cardBackSideTexture = new Texture(objRect, "data/Card_back.png", new SDL_Rect(dictionaryCardBackSideRect[cardBackSideIndex]));

    int xCardOffset = 0, yCardOffset = 0;
    for (int suit = 0; suit < 4; ++suit)
    {
        for (int cardIndex = 1; cardIndex <= 13; ++cardIndex)
        {
            cardDeck.push_back(new Card(new SDL_Rect{ xPos + xCardOffset, yPos - yCardOffset, CARD_WIDTH, CARD_HEIGHT }, cardIndex, suit, cardBackSideTexture));
            ++xCardOffset;
            ++yCardOffset;
        }
    }
    shuffleDeck();
}

Deck::~Deck()
{
    for (Card* card : cardDeck)
        delete card;
    cardDeck.clear();

    delete cardBackSideTexture;
}

void Deck::update()
{
    for (const auto& card : cardDeck)
        card->update();
}

void Deck::render()
{
    for (const auto& card : cardDeck)
        card->render();
}

Card* Deck::GetCard(bool hidden)
{
    Card* tempCard = cardDeck.back();
    cardDeck.pop_back();

    tempCard->isFaceSide = !hidden;

    return tempCard;
}

void Deck::ChangeCardBackSide()
{
    ++cardBackSideIndex;
    auto search = dictionaryCardBackSideRect.find(cardBackSideIndex);
    if (search == dictionaryCardBackSideRect.end())
    {
        cardBackSideIndex = 0;
        search = dictionaryCardBackSideRect.find(cardBackSideIndex);
    }

    cardBackSideTexture->changeSRect(search->second);
}

void Deck::shuffleDeck()
{
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);
    std::shuffle(cardDeck.begin(), cardDeck.end(), rng);

    int xCardOffset = 0, yCardOffset = 0;
    for (auto card : cardDeck)
    {
        card->changeLocation(objRect->x + xCardOffset, objRect->y + yCardOffset);
        ++xCardOffset;
        ++yCardOffset;
    }
}
