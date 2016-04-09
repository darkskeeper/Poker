#pragma once
#include <iostream>
#include <vector>
#include "deck.h"
using namespace std;

class Table
{
private:
    vector <int> cards;
public:
    Table();
    ~Table();
    void set_table(deck & d);
    void show();
    void tclear();
    int give_card(int i);
};

/*class Table
{
private:
    vector <int> cards;
    bool check_unic( const int temp ) const;
public:
    void get_table() const;
    Table();
    ~Table();
};*/