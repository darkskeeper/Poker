#pragma once
#include <iostream>
#include <vector>
#include "deck.h"
#include "Table.h"
using namespace std;

class Hand
{
private:
    vector <int> cards;
    int comb;
public:
    Hand();
    ~Hand();
    void set_hand(deck & d, Table t);
    void show();
    void hclear();
    void det_comb();
    void sort();
    bool straight_check();
    bool flash_check();
    friend bool operator > (const Hand& h1, const Hand& h2);
};

/*class Hand
{
private:
    vector <int> cards;
public:
    Hand();
    bool check_unic(const int temp) const;
    void get_hand() const;
    friend bool compare();
    ~Hand();
};

*/