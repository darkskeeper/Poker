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
    det_comb();
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

void Hand::show() const
{
    cout << "Hand: ";
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
    cout << "comb: " << c[comb].c_str() << endl;
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
        vector<int>::const_iterator it, it_current;
        it_current = h2.current_comb.begin();
        for (it = h1.current_comb.begin(); it != h1.current_comb.end(); it++)
        {
            if (*it != *it_current)
            {
                return *it>*it_current;
            }
            it_current++;
        }
    }
    else
    {
        return (h1.comb > h2.comb);
    }
}

bool operator == (const Hand& h1, const Hand& h2)
{
    if (h1.comb == h2.comb)
    {
        vector<int>::const_iterator it, it_current;
        it_current = h2.current_comb.begin();
        for (it = h1.current_comb.begin(); it != h1.current_comb.end(); it++)
        {
            if (*it != *it_current)
            {
                return false;
            }
            it_current++;
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
    }
    else if ((combs[3] == 1 && combs[2] >= 1) || combs[3] > 1 )
    {
        comb = FULL_HOUSE;
        setFH(cards);
    }
    else if (combs[1] + combs[2] + combs[3] >= 5)
    {
        if (straight_check())
        {
            if (straight_flash_check())
            {
                if ( current_comb[0] == ACE )
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
            setTP(cards);
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
        setTP(cards);
    }
}

bool Hand::flash_check() const
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
    for (int i = 0; (i + 4) < ranks.size(); i++)
    {
        if (ranks[i] - 4 == ranks[i + 4])
        {
            current_comb.push_back(ranks[i]);
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

bool Hand::straight_flash_check() const
{
    vector <int> suits(4, 0);
    if (current_comb[0] == -1)
    {
        int i = 0;
        while (cards[i] % 13 == ACE)
        {
            suits[cards[i] / 13]++;
            i++;
        }
        while (cards[i] % 13 != FIVE)
        {
            i++;
        }
        for (i; i < N_CARDS_HAND + N_CARDS_TABLE; i++)
        {
            suits[cards[i] / 13]++;
        }
    }
    else
    {
        int i = 0;
        while (current_comb[0] != cards[i] % 13)
        {
            i++;
        }
        while (i != N_CARDS_HAND + N_CARDS_TABLE && cards[i] % 13 >= current_comb[0] - 4)
        {
            suits[cards[i] / 13]++;
            i++;
        }
    }
    for (int i = 0; i < SUITS; i++)
    {
        if (suits[i] == 5)
        {
            return true;
        }
    }
    return false;
}

void Hand::setHC(const vector <int> &ccards)
{
    vector <int> ::const_iterator it;
    int i = 0;
    for (it = ccards.begin(); i < 5; it++, i++)
    {
        current_comb.push_back(*it);
    }
}

void Hand::setOP(vector <int> ccards)
{
    vector <int>::iterator it, it_current;
    it = ccards.begin();
    while (current_comb.empty())
    {
        for (it_current = it + 1; it_current != ccards.end(); it_current++)
        {
            if ((*it % 13) == (*it_current % 13))
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
    ccards.erase(it_current);
    ccards.erase(it);
    int i = 0;
    for (it = ccards.begin(); i < 3; it++, i++)
    {
        current_comb.push_back(*it);
    }
}

void Hand::setTP(vector <int> ccards)
{
    vector <int>::iterator it, it_current;
    it = ccards.begin();
    it_current = it + 1;
    while (current_comb.size() != 2)
    {
        if (it_current == ccards.begin())
        {
            it = ccards.begin();
        }
        for (it_current = it + 1; it_current != ccards.end(); it_current++)
        {
            if ((*it % 13) == (*it_current % 13))
            {
                current_comb.push_back(*it % 13);
                ccards.erase(it_current);
                ccards.erase(it);
                it = it_current = ccards.begin();
                break;
            }
        }
        if (current_comb.size() != 2)
        {
            it++;
        }
    }
    current_comb.push_back(ccards[0] % 13);
}

void Hand::setTOAK(vector <int> ccards)
{
    vector <int>::iterator it, it_current;
    it = ccards.begin();
    while (current_comb.empty())
    {
        for (it_current = it + 1; it_current != ccards.end(); it_current++)
        {
            if (*it % 13 == *it_current % 13)
            {
                if (current_comb.empty())
                {
                    current_comb.push_back(*it % 13);
                }
                ccards.erase(it_current);
                it_current = it;
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

void Hand::setFH(vector <int> ccards)
{
    vector <int>::iterator it, it_current, it_next;
    it = ccards.begin();
    int max = -1;
    while (it != ccards.end())
    {
        for (it_current = it + 1; it_current != ccards.end(); it_current++)
        {
            if (*it % 13 == *it_current % 13)
            {
                for (it_next = it_current + 1; it_next != ccards.end(); it_next++)
                {
                    if (*it_next % 13 == *it_current % 13)
                    {
                        if (*it % 13 > max)
                        {
                            max = *it % 13;
                        }
                        break;
                    }
                }
                break;
            }
        }
        it++;
    }
    current_comb.push_back(max);
    for (it = ccards.begin(); it < ccards.end(); it++)
    {
        if (*it % 13 == max)
        {
            ccards.erase(it);
            it = ccards.begin();
        }
    }
    it = ccards.begin();
    while (current_comb.size() != 2)
    {
        for (it_current = it + 1; it_current != ccards.end(); it_current++)
        {
            if ((*it % 13) == (*it_current % 13))
            {
                current_comb.push_back(*it % 13);
                break;
            }
        }
        it++;
    }
}