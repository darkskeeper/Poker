#pragma once
#include <iostream>
#include <vector>
#include "Deck.h"
using namespace std;

class Table
{
private:
    vector <int> cards;
    void sort();
public:
    Table();
    ~Table();
    void set_table(Deck & d);//
    void show() const;
    void tclear();
    int give_card(const int & i);
};