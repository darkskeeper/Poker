#include "Table.h"

Table::Table()
{

}

Table::~Table()
{

}

void Table::set_table(deck & d)
{
    for (int i = 0; i < 5; i++)
    {
        cards.push_back(d.give_card());
    }
}

void Table::show()
{
    cout << "Table: ";
    vector <int>::iterator it;
    for (it = cards.begin(); it != cards.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

void Table::tclear()
{
    cards.clear();
}

int Table::give_card(int i)
{
    return cards[i];
}

/*extern vector <int> unic_cards;

Table::Table()
{
    int temp;
    for(int i = 0; i < 5; i++)
    {
        do
        {
            temp = rand() % 52;
        } while (!check_unic(temp));
        cards.push_back(temp);
        unic_cards.push_back(temp);
    }
}


Table::~Table()
{
}

void Table::get_table() const
{
    cout << "Table: ";
    for (int i = 0; i < 5; i++)
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

bool Table::check_unic( const int temp ) const
{
    vector <int> ::iterator it;
    for (it = unic_cards.begin(); it != unic_cards.end(); it++)
    {
        if (*it == temp) 
        {
            return false;
        }
    }
    return true;
}*/