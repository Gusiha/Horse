#include "Horse.h"

int main()
{
    setlocale(LC_ALL, "ru");
    time_t timeStart, timeFinish;

    cout << endl;

    time(&timeStart);
    setKnight(X,Y);

    printBoard();
    time(&timeFinish);

    cout << "\nВыполнено за " << timeFinish - timeStart << " сек.";
}

