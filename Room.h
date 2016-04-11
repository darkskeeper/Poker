#pragma once
//#include "Deck.h"
#include "Table.h"
#include "Hand.h"

class Room
{
private:
    Deck d;
    Table t;
    vector <Hand> hands;
public:
    void startgame();
    void show();
    Room();
    ~Room();
};

