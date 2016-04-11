#include "Room.h"
#include <time.h>

int main()
{
    srand(time(NULL));
    Room room_one;
    int T = 10;
    while (T--)//(true)
    {
        room_one.startgame();
        cout << endl;
    }
    room_one.startgame();
    cout << endl;
    room_one.startgame();
    cout << endl;
    room_one.startgame();
    cout << endl;
    system("pause");
    return 0;
}