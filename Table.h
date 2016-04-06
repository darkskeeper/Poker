#pragma once
#include "Hand.h"

class Table
{
private:
    vector <int> cards;
    bool check_unic( const int temp ) const;
public:
    void get_table() const;
    Table();
    ~Table();
};