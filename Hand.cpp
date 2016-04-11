#include "Hand.h"


Hand::Hand()
{

}

Hand::~Hand()
{

}

void Hand::set_hand(Deck & d, Table t)
{
    for (int i = 0; i < N_CARDS_HAND; i++)
    {
        cards.push_back(d.give_card());
    }
    for (int i = 0; i < N_CARDS_TABLE; i++)
    {
        cards.push_back(t.give_card(i));
    }
    sort();
    show();//
    det_comb();
    cout << "comb: " << c[comb].c_str() << endl;
}

void Hand::sort()
{
    for (int i = 0; i < N_CARDS_HAND + N_CARDS_TABLE; i++)
    {
        for (int k = i + 1; k < N_CARDS_HAND + N_CARDS_TABLE; k++)
        {
            if ((cards[i] % 13) < (cards[k] % 13))
            {
                swap(cards[i], cards[k]);
            }
        }
    }
}

void Hand::show()
{
    cout << "Hand: ";
    vector <int>::iterator it;
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
        switch (temp/13)
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
}

void Hand::hclear()
{
    cards.clear();
    current_comb.clear();
}

bool operator > (const Hand& h1, const Hand& h2)
{
    if (h1.comb == h2.comb)
    {
        vector<int>::const_iterator it, it1;
        it = h1.current_comb.begin();
        it1 = h2.current_comb.begin();
        for (it; it != h1.current_comb.end(); it++)
        {
            if (*it != *it1)
            {
                return *it>*it1;
            }
            it1++;
        }
    }
    else
    {
        return (h1.comb > h2.comb);
    }
}

bool operator == (const Hand& h1, const Hand& h2)
{
    /*if (h1.comb == STRAIGHT_FLASH || h2.comb == STRAIGHT_FLASH)
    {
        cout << " ";
    }*/
    if (h1.comb == h2.comb)
    {
        /*if (h1.comb == STRAIGHT_FLASH || h1.comb == STRAIGHT)
        {
            cout << " ";
        }*/
        vector<int>::const_iterator it, it1;
        it = h1.current_comb.begin();
        it1 = h2.current_comb.begin();
        for (it; it != h1.current_comb.end(); it++)
        {
            if (*it != *it1)
            {
                return false;
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

void Hand::det_comb()
{
    vector <int> def_cards(N_CARDS, 0);
    vector <int> combs(5, 0);
    for (int i = 0; i < N_CARDS_HAND + N_CARDS_TABLE; i++)
    {
        def_cards[cards[i]] = 1;
    }
    for (int i = 0; i < ONE_SUIT; i++)
    {
        combs[def_cards[i + (CLUBS * ONE_SUIT)] + def_cards[i + (SPADES * ONE_SUIT)] + def_cards[i + (DIAMONDS * ONE_SUIT)] + def_cards[i + (HEARTS * ONE_SUIT)]]++;
    }
    if (combs[4] == 1)
    {
        comb = FOUR_OF_A_KIND;
        //setFOAK(cards);
    }
    else if ((combs[3] == 1 && combs[2] >= 1) || combs[3] > 1 )
    {
        comb = FULL_HOUSE;
        //setFH(cards);
    }
    else if (combs[1] + combs[2] + combs[3] >= 5)
    {
        if (straight_check())
        {
            if (flash_check())
            {
                if (
                    (def_cards[ACE + CLUBS * ONE_SUIT] || def_cards[ACE + SPADES * ONE_SUIT] || def_cards[ACE + DIAMONDS * ONE_SUIT] || def_cards[ACE + HEARTS * ONE_SUIT]) &&
                        (
                            (!def_cards[TWO + CLUBS * ONE_SUIT] && !def_cards[TWO + SPADES * ONE_SUIT] && !def_cards[TWO + DIAMONDS * ONE_SUIT] && !def_cards[TWO + HEARTS * ONE_SUIT]) ||
                            (!def_cards[THREE + CLUBS * ONE_SUIT] && !def_cards[THREE + SPADES * ONE_SUIT] && !def_cards[THREE + DIAMONDS * ONE_SUIT] && !def_cards[THREE + HEARTS * ONE_SUIT]) ||
                            (!def_cards[FOUR + CLUBS * ONE_SUIT] && !def_cards[FOUR + SPADES * ONE_SUIT] && !def_cards[FOUR + DIAMONDS * ONE_SUIT] && !def_cards[FOUR + HEARTS * ONE_SUIT])
                        )
                    )
                {
                    comb = ROYAL_FLASH;
                }
                else
                {
                    comb = STRAIGHT_FLASH;
                }
            }
            else
            {
                comb = STRAIGHT;
            }
        }
        else if (flash_check())
        {
            comb = FLASH;
            setFl(cards);
        }
        else if (combs[3] == 1)
        {
            comb = THREE_OF_A_KIND;
            setTOAK(cards);
        }
        else if (combs[2] >= 2)
        {
            comb = TWO_PAIRS;
            //setTP(cards);
        }
        else if (combs[2] == 1)
        {
            comb = PAIR;
            setOP(cards);
        }
        else
        {
            comb = HIGH_CARD;
            setHC(cards);
        }
    }
    else if (combs[3] == 1)
    {
        comb = THREE_OF_A_KIND;
        setTOAK(cards);
    }
    else if (combs[2] >= 2)
    {
        comb = TWO_PAIRS;
        //setTP(cards);
    }
}

bool Hand::flash_check()
{
    vector <int> suits(4, 0);
    for (int i = 0; i < N_CARDS_HAND + N_CARDS_TABLE; i++)
    {
        suits[(cards[i] / 13)]++;
    }
    for (int i = 0; i < SUITS; i++)
    {
        if (suits[i] >= 5)
        {
            return true;
        }
    }
    return false;
}

bool Hand::straight_check()
{
    vector <int> ranks;
    vector <int>::iterator it;
    ranks.push_back(cards[0] % 13);
    for (int i = 1; i < N_CARDS_HAND + N_CARDS_TABLE; i++)
    {
        bool check = true;
        for (it = ranks.begin(); it != ranks.end(); it++)
        {
            if (*it == (cards[i] % 13))
            {
                check = false;
            }
        }
        if (check)
        {
            ranks.push_back(cards[i] % 13);
        }
    }
    for (int i = 0; i + 4 < ranks.size(); i++)
    {
        if (ranks[i] - 4 == ranks[i + 4])
        {
            current_comb.push_back(ranks[i]); //???????????????
            return true;
        }
    }
    int rs = ranks.size() - 1;
    if (ranks[rs] == TWO && ranks[rs - 1] == THREE && ranks[rs - 2] == FOUR && ranks[rs - 3] == FIVE && ranks[0] == ACE)
    {
        current_comb.push_back(-1);
        return true;
    }
    return false;
}

void Hand::setHC(vector <int> ccards)
{
    vector <int> ::iterator it;
    int i = 0;
    for (it = ccards.begin(); i < 5; it++, i++)
    {
        current_comb.push_back(*it);
    }
}

void Hand::setOP(vector <int> ccards)
{
    vector <int>::iterator it, it1;
    it = ccards.begin();
    while (current_comb.empty())
    {
        for (it1 = it + 1; it1 != ccards.end(); it1++)
        {
            if ((*it % 13) == (*it1 % 13))
            {
                current_comb.push_back(*it % 13);
                break;
            }
        }
        if (current_comb.empty())
        {
            it++;
        }
    }
    ccards.erase(it1);
    ccards.erase(it);
    int i = 0;
    for (it = ccards.begin(); i < 3; it++, i++)
    {
        current_comb.push_back(*it);
    }
}

void Hand::setTOAK(vector <int> ccards)
{
    vector <int>::iterator it, it1;
    it = ccards.begin();
    while (current_comb.empty())
    {
        for (it1 = it + 1; it1 < ccards.end(); it1++)
        {
            if (*it % 13 == *it1 % 13)
            {
                if (current_comb.empty())
                {
                    current_comb.push_back(*it % 13);
                }
                ccards.erase(it1);
                it1 = it;
            }
        }
        if (current_comb.empty())
        {
            it++;
        }
    }
    ccards.erase(it);
    int i = 0;
    for (it = ccards.begin(); i < 2; it++, i++)
    {
        current_comb.push_back(*it);
    }
}

void Hand::setFl(vector <int> ccards)
{
    int suit;
    vector <int> suits(4, 0);
    for (int i = 0; i < N_CARDS_HAND + N_CARDS_TABLE; i++)
    {
        suits[(ccards[i] / 13)]++;
    }
    for (int i = 0; i < SUITS; i++)
    {
        if (suits[i] >= 5)
        {
            suit = i;
            break;
        }
    }
    vector <int>::iterator it;
    int i = 0;
    for (it = ccards.begin(); i < 5; it++)
    {
        if ((*it / 13) == suit)
        {
            current_comb.push_back(*it);
            i++;
        }
    }
}