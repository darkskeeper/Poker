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
    void setHC(vector <int> ccards);
    void setOP(vector <int> ccards);
    //void setTP(vector <int> ccards);
    void setTOAK(vector <int> ccards);
    void setFl(vector <int> ccards);
    //void setFH(vector <int> ccards);
    //void setFOAK(vector <int> ccards); //ме мюдн
public:
    Hand();
    ~Hand();
    void set_hand(Deck & d, Table t);
    void show();
    void hclear();
    void det_comb();
    void sort();
    bool straight_check();
    bool flash_check();
    friend bool operator == (const Hand& h1, const Hand& h2);
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