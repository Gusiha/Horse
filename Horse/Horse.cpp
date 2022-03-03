#include <iostream>
#include <ctime>

//размерность доски
#define RC 8  

//начальные координаты
#define X 3   
#define Y 4

using namespace std;

void printBoard();

int Predict(int newX, int newY);

int predictCount[8] = {};

int board[RC][RC] {};
int angelTable[RC][RC]{};
int step[8][2] = {
    {-1,2},
    {-2,1},
    {2,1},
    {1,2},
    {1,-2},
    {2,-1},
    {-2,-1},
    {-1,-2}


};
int turnNumber = 0;

int angelMove(int newX, int newY)
    {
        if (angelTable[newX][newY] != 0)
            return (angelTable[newX][newY]);
        else
            return 0;
    }

bool Check(int first, int second)
{   // go behind the border
    if ((first < 0) || (second < 0) || (first >= RC) || (second >= RC))
        return false;

    // pointed position before
    if (board[first][second] != 0)
        return false;

    return true;
}


bool setKnight(int x, int y)
{
    for (int j = 0; j < 8; j++)
    {
        predictCount[j] = 0;
    }

    if (!Check(x, y))
        return false;


    if (turnNumber == RC * RC)
    {
        return true;
    }

    turnNumber++;
    board[x][y] = turnNumber;

    

    for (int i = 0; i < 8; i++)
    {
        if (Check(x + step[i][0], y + step[i][1]) && turnNumber != 63)
        {
            predictCount[i] = Predict(x + step[i][0], y + step[i][1]);
        }

        if (turnNumber == RC*RC-1)
        {
           
            for (int k = 0; k < 8; k++)
            {
                if (Check(x + step[k][0], y + step[k][1]))
                {
                    board[x + step[k][0]][y + step[k][1]] = RC * RC;

                }
                    
            }

            
            
        }
        

    }

    int min = 10;
    int min_id = 0;

    for (int i = 0; i < 8; i++)
    {
        if ((predictCount[i] <= min) && predictCount[i] != 0)
        {
            min = predictCount[i];
            min_id = i;
        }
        
        
            

        if (i == 7 && min != 0)
        {

            if (setKnight(x + step[min_id][0], y + step[min_id][1]))
                return true;
            else
                return false;
        }
        
    }
    cout << endl;
    printBoard();

    turnNumber--;
    board[x][y] = 0;
    return false;
  
        
  

    /*int angelPoss = angelMove(x, y);*/

    // recursive exit
    



    // changing turn in the angel
    /*if (angelPoss && board[step[angelPoss - 1][0], step[angelPoss - 1][1]] == 0)
    {

        setKnight(x + step[angelPoss-1][0], y + step[angelPoss-1][1]);
        return true;
    }*/

    //else
    //{

        /*for (int i = 0; i < 8; i++)
        {
            if (setKnight(x + step[i][0], y + step[i][1]))
                return true;
        }*/

    //}

   
}

void printBoard()
{
    for (int i = 0; i < RC; i++)
    {
        for (int j = 0; j < RC; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

void printAngeTable()
{
    for (int i = 0; i < RC; i++)
    {
        for (int j = 0; j < RC; j++)
        {
            cout << angelTable[i][j] << " ";
        }
        cout << endl;
    }
}

int iterations(int a, int b)
{
    int count = 0;
    for (int m = 0; m < 8; m++)
    {
        if (iterations(a + step[m][0], b + step[m][1]))
            return true;
    }
}

//Варнсдорф
int Predict(int newX, int newY)
{
    int count = 0;

    for (int k = 0; k < 8; k++)
    {
        if (Check(newX + step[k][0], newY + step[k][1]))
            count++;
    }

    return count;
}


int main()
{
    setlocale(LC_ALL, "ru");
    time_t timeStart, timeFinish;
    
    //filling angelTable
    angelTable [1][RC - 3] = 1;
    angelTable [2][RC - 2] = 2;

    angelTable [RC - 3][RC - 2] = 3;
    angelTable [RC - 2][RC - 3] = 4;

    angelTable [RC - 2][2] = 5;
    angelTable [RC - 3][1] = 6;

    angelTable[2][1] = 7;
    angelTable[1][2] = 8;



    printAngeTable();
    
    cout << endl;

    time(&timeStart);
    setKnight(X,Y);

    printBoard();
    time(&timeFinish);

    cout << "\nВыполнено за " << timeFinish - timeStart << " сек.";
}

