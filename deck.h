#pragma once
#include <iostream>
#include <vector>
using namespace std;

const int SUITS = 4;
const int ONE_SUIT = 13;
const int N_CARDS_HAND = 2;
const int N_CARDS = 52;
const int N_CARDS_TABLE = 5;

const enum RANK { TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACKET, QUEEN, KING, ACE };
const enum COMBINATIONS { HIGH_CARD, PAIR, TWO_PAIRS, THREE_OF_A_KIND, STRAIGHT, FLASH, FULL_HOUSE, FOUR_OF_A_KIND, STRAIGHT_FLASH, ROYAL_FLASH };
const enum SUIT { CLUBS, SPADES, DIAMONDS, HEARTS };
const string c[10] = { "HIGH_CARD", "PAIR", "TWO_PAIRS", "THREE_OF_A_KIND", "STRAIGHT", "FLASH", "FULL_HOUSE", "FOUR_OF_A_KIND", "STRAIGHT_FLASH", "ROYAL_FLASH" };

class Deck
{
private:
    vector <int> cards;
public:
    Deck();
    ~Deck();
    void shuffle();
    void show() const;
    int give_card();
    void dclear();
};