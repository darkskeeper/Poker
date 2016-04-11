#include "Table.h"

Table::Table()
{

}

Table::~Table()
{

}

void Table::set_table(Deck & d)
{
    for (int i = 0; i < 5; i++)
    {
        cards.push_back(d.give_card());
    }
    sort();
}

void Table::show() const
{
    cout << "Table: ";
    vector <int>::const_iterator it;
    for (it = cards.begin(); it != cards.end(); it++)
    {
        int temp = *it;
        if (temp % 13 < 8)
        {
            cout << (temp % 13) + 2;
        }
        else
        {
            switch (temp % 13)
            {
            case TEN:
                cout << "T";
                break;
            case JACKET:
                cout << "J";
                break;
            case QUEEN:
                cout << "Q";
                break;
            case KING:
                cout << "K";
                break;
            case ACE:
                cout << "A";
                break;
            }
        }
        switch (temp / 13)
        {
        case CLUBS:
            cout << char(6);
            break;
        case SPADES:
            cout << char(5);
            break;
        case DIAMONDS:
            cout << char(4);
            break;
        case HEARTS:
            cout << char(3);
            break;
        }
        cout << " ";
    }
    cout << endl;
}

void Table::tclear()
{
    cards.clear();
}

int Table::give_card(const int & i)
{
    return cards[i];
}

void Table::sort()
{
    for (int i = 0; i < N_CARDS_TABLE; i++)
    {
        for (int k = i + 1; k < N_CARDS_TABLE; k++)
        {
            if ((cards[i] % 13) < (cards[k] % 13))
            {
                swap(cards[i], cards[k]);
            }
        }
    }
}