#include "Room.h"



Room::Room()
{
}


Room::~Room()
{
}

void Room::startgame()
{
    Hand hand;
    hands.push_back(hand);
    hands.push_back(hand);
    d.shuffle();
    t.set_table(d);
    hands[0].set_hand(d, t);
    hands[1].set_hand(d, t);
    show();
    if (hands[0] == hands[1])
    {
        cout << endl << "TIE!" << endl;
    }
    else
    {
        if (hands[0] > hands[1])
        {
            cout << endl << "HAND ONE WIN" << endl;
        }
        else
        {
            cout << endl << "HAND TWO WIN!" << endl;
        }
    }
    t.tclear();
    hands[0].hclear();
    hands[1].hclear();
    d.dclear();
    hands.clear();
}

void Room::show() const
{
    t.show();
    vector <Hand>::const_iterator it;
    for (it = hands.begin(); it != hands.end(); it++)
    {
        (*it).show();
    }
    d.show();
}