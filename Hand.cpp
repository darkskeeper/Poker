#include "Hand.h"

extern vector <int> unic_cards;

Hand::Hand()
{
    int temp;
    for (int i = 0; i < 2; i++)
    {
        do
        {
            temp = rand() % 52;
        } while (!check_unic(temp));
        cards.push_back(temp);
        unic_cards.push_back(temp);
    }
}

Hand::~Hand()
{
}

void Hand::get_hand() const
{
    for (int i = 0; i < 2; i++)
    {
        int temp = cards[i] % 13;
        if (temp + 2 < 10)
        {
            cout << temp + 2 << "_";
        }
        else
        {
            switch (temp)
            {
            case 8:
                cout << "Ten" << "_";
                break;
            case 9:
                cout << "Jacket" << "_";
                break;
            case 10:
                cout << "Queen" << "_";
                break;
            case 11:
                cout << "King" << "_";
                break;
            case 12:
                cout << "Ace" << "_";
                break;
            }
        }
        switch (cards[i] / 13)
        {
        case 0:
            cout << "Clubs ";
            break;
        case 1:
            cout << "Spades ";
            break;
        case 2:
            cout << "Diamonds ";
            break;
        case 3:
            cout << "Hearts ";
            break;
        }
    }
    cout << endl;
}

bool Hand::check_unic(const int temp) const
{
    vector <int>::iterator it;
    for (it = unic_cards.begin(); it != unic_cards.end(); it++)
    {
        if (temp == *it)
        {
            return false;
        }
    }
    return true;
}

bool compare()
{
    return false;
}