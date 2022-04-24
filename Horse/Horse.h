#include <iostream>
#include <ctime>
#include <iomanip> 

// Board dimension
#define RC 76

// Initial coordinates
#define X 4
#define Y 3

using namespace std;

// Global Variables
int predictCount[8] = {};
int board[RC][RC] = {};
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


// Function Prototypes
void PrintBoard();
bool Check(int first, int second);
bool SetKnight(int x, int y);
int Predict(int newX, int newY);

// Function Definitions
bool Check(int first, int second)
{
    // going beyond 
    if ((first < 0) || (second < 0) || (first >= RC) || (second >= RC))
        return false;

    // pointed position
    if (board[first][second] != 0)
        return false;

    return true;
}

void PrintBoard()
{
    for (int i = 0; i < RC; i++)
    {
        for (int j = 0; j < RC; j++)
        {
            cout << setw(5) << left << board[i][j];
            
        }
        cout << endl;
    }
}




bool SetKnight(int x, int y)
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
    
    // Cell Pointing
    board[x][y] = turnNumber;      


    for (int i = 0; i < 8; i++)
    {
        // Switching off Varnsdorf
        if (turnNumber == RC*RC-1)
        {
            for (int i = 0; i < 8; i++)
            {
                if (Check(x + step[i][0], y + step[i][1]))
                {
                   board[x + step[i][0]][y + step[i][1]] = RC * RC;

                }
                   
            }
            break;            
        }
        
        // Common Varnsdorf's Filling
        if (Check(x + step[i][0], y + step[i][1]) )
        {
            predictCount[i] = Predict(x + step[i][0], y + step[i][1]);
        }  
        
    }

    int min = 10;
    int min_id = 0;

    for (int i = 0; i < 8; i++)
    {
        if ((predictCount[i] < min) && predictCount[i] != 0)
        {
            
            min = predictCount[i];
            min_id = i;
        }


        if (i == 7 && min != 0)
        {
            
            if (!SetKnight(x + step[min_id][0], y + step[min_id][1]))
            {
                board[x + step[min_id][0]][y + step[min_id][1]] = 0;
                turnNumber--;
                predictCount[min_id] = 0;
                SetKnight(x,y);
            }
        }
        
    }
    
    return true;
}

// Varnsdorf's Algorithm
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

