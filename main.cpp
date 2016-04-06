#include "Hand.h"
#include "Table.h"
#include <time.h>

vector <int> unic_cards;

int main()
{
    int t = 10;
    srand(time(NULL));
    while (t--)
    {
        Table table;
        //table.get_table();
        Hand hand_one, hand_two;
        /*cout << "Hand_one: ";
        hand_one.get_hand();
        cout << "Hand_two: ";
        hand_two.get_hand();*/
        unic_cards.clear();
        if (compare())
        {
            cout << "WTF?";
        }
        else
        {
            cout << "nice";
        }
    }
    system("pause");
    return 0;
}