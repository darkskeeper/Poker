#pragma once
#include <iostream>
#include <vector>
#include "Deck.h"
#include "Table.h"
using namespace std;

class Hand
{
private:
    vector <int> cards;
    vector <int> current_comb;
    int comb;
    void setHC(const vector <int> &ccards);
    void setOP(vector <int> ccards);
    void setTP(vector <int> ccards);
    void setTOAK(vector <int> ccards);
    void setFl(vector <int> ccards);
    void setFH(vector <int> ccards);
    bool straight_check();
    bool flash_check() const;
    bool straight_flash_check() const;
    void sort();
    void det_comb();
public:
    Hand();
    ~Hand();
    void set_hand(Deck & d, Table t);
    void hclear();
    friend bool operator == (const Hand& h1, const Hand& h2);
    friend bool operator > (const Hand& h1, const Hand& h2);
    void show() const;
};