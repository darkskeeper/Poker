#include "deck.h"


deck::deck()
{
}

deck::~deck()
{
}

void deck::shuffle()
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

void deck::show()
{
    cout << "Deck: ";
    vector <int>::iterator it;
    for (it = cards.begin(); it != cards.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

int deck::give_card()
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

void deck::dclear()
{
    cards.clear();
}
