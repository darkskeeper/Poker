#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Hand
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

