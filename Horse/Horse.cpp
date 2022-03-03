#include "Horse.h"

int main()
{
    setlocale(LC_ALL, "ru");
    time_t timeStart, timeFinish;

    time(&timeStart);
    setKnight(X,Y);

    printBoard();
    time(&timeFinish);

    cout << "\nProcess time is " << timeFinish - timeStart << " sec.";
}

