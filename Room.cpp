#include "Room.h"



Room::Room()
{
}


Room::~Room()
{
}

void Room::startgame()
{
    d.shuffle();
    t.set_table(d);
    hand_one.set_hand(d, t);
    hand_two.set_hand(d, t);
    show();
    if (hand_one > hand_two)
    {
        cout << endl << "HAND ONE WIN!" << endl;
    }
    else
    {
        cout << endl << "HAND TWO WIN!" << endl;
    }
    t.tclear();
    hand_one.hclear();
    hand_two.hclear();
    d.dclear();
}

void Room::show()
{
    t.show();
    //hand_one.show();
    //hand_two.show();
    d.show();
}