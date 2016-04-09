#pragma once
#include "deck.h"
#include "Table.h"
#include "Hand.h"

class Room
{
private:
    deck d;
    Table t;
    Hand hand_one, hand_two;
public:
    void startgame();
    void show();
    Room();
    ~Room();
};

