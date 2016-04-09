#pragma once
#include <iostream>
#include <vector>
using namespace std;

class deck
{
private:
    vector <int> cards;
public:
    deck();
    ~deck();
    void shuffle();
    void show();
    int give_card();
    void dclear();
};

