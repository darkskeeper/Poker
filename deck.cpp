#include "Deck.h"


Deck::Deck()
{
}

Deck::~Deck()
{
}

void Deck::shuffle()
{
    for (int i = 0; i < 52; i++)
    {
        cards.push_back(i);
    }
    int random, temp;
    for (int i = 0; i < 52; i++)
    {
        random = rand() % 52;
        temp = cards[i];
        cards[i] = cards[random];
        cards[random] = temp;
    }
}

void Deck::show() const
{
    cout << "Deck: ";
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

int Deck::give_card()
{
    int cc = cards.size();
    int i = rand() % cards.size();
    vector <int> ::iterator it;
    it = cards.begin();
    it += i;
    int temp = *it;
    cards.erase(it);
    return temp;
}

void Deck::dclear()
{
    cards.clear();
}
