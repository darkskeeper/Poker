#include "Room.h"
//#include "Table.h"
#include <time.h>

int main()
{
    srand(time(NULL));
    Room room_one;
    int T = 10;
    while /*(T--)*/(true)
    {
        room_one.startgame();
        cout << endl;
        room_one.show();
        cout << endl;
    }
    room_one.startgame();
    cout << endl;
    room_one.show();
    cout << endl;
    room_one.startgame();
    cout << endl;
    room_one.show();
    cout << endl;
    room_one.startgame();
    cout << endl;
    room_one.show();
    cout << endl;
    system("pause");
    return 0;
}

/*vector <int> unic_cards;

int main()
{
    int t = 10;
    srand(time(NULL));
    while (t--)
    {
        Table table;
        //table.get_table();
        Hand hand_one, hand_two;
        cout << "Hand_one: ";
        hand_one.get_hand();
        cout << "Hand_two: ";
        hand_two.get_hand();
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
}*/