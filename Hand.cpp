#include "Hand.h"

const int SUITS = 4;
const int ONE_SUIT = 13;
const int N_CARDS_HAND = 2;
const int N_CARDS = 52;
const int N_CARDS_TABLE = 5;

enum RANK {TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACKET, QUEEN, KING, ACE};
enum COMBINATIONS {HIGH_CARD, PAIR, TWO_PAIRS, THREE_OF_A_KIND, STRAIGHT, FLASH, FULL_HOUSE, FOUR_OF_A_KIND, STRAIGHT_FLASH, ROYAL_FLASH};
enum SUIT { CLUBS, SPADES, DIAMONDS, HEARTS};
string c[10] = { "HIGH_CARD", "PAIR", "TWO_PAIRS", "THREE_OF_A_KIND", "STRAIGHT", "FLASH", "FULL_HOUSE", "FOUR_OF_A_KIND", "STRAIGHT_FLASH", "ROYAL_FLASH"};

Hand::Hand()
{

}

Hand::~Hand()
{

}

void Hand::set_hand(deck & d, Table t)
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
            if ((cards[i] % 13) > (cards[k] % 13))
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
}

bool operator > (const Hand& h1, const Hand& h2)
{
    return (h1.comb > h2.comb);
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
    else if ((combs[3] == 1 && combs[2] >= 1) || combs[3]>1)
    {
        comb = FULL_HOUSE;
    }
    else if (combs[1] >= 5)
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
        }
        else if (combs[3] == 1)
        {
            comb = THREE_OF_A_KIND;
        }
        else if (combs[2] >= 2)
        {
            comb = TWO_PAIRS;
        }
        else if (combs[2] == 1)
        {
            comb = PAIR;
        }
        else
        {
            comb = HIGH_CARD;
        }
    }
    else if (combs[3] == 1)
    {
        comb = THREE_OF_A_KIND;
    }
    else if (combs[2] >= 2)
    {
        comb = TWO_PAIRS;
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
        if (ranks[i] + 4 == ranks[i + 4])
        {
            return true;
        }
    }
    if (ranks[0] == TWO && ranks[1] == THREE && ranks[2] == FOUR && ranks[3] == FIVE && ranks[ranks.size() - 1] == ACE)
    {
        return true;
    }
    return false;
}

/*extern vector <int> unic_cards;

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
}*/