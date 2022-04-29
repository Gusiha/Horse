#include <iostream>
#include <ctime>
#include <iomanip> 

// Board dimension
#define RC 8

// Initial coordinates
#define X 4
#define Y 3

using namespace std;

// Global Variables

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
void SetKnight(int x, int y, bool repeat = false, int* predictCount = {});
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

void SetKnight(int x, int y, bool repeat, int* backupArray)
{
    

    if (!Check(x, y))
        return; 


    if (turnNumber == RC * RC)
    {
        return;
    }

    turnNumber++;
    // cell pointing
    board[x][y] = turnNumber;
    
    if(!repeat)
    {

    int predictCount[8] = {};
    
    for (int j = 0; j < 8; j++)
    {
        predictCount[j] = 0;
    }

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
    }

    int min = 10;
    int min_id = -1;

    for (int i = 0; i < 8; i++)
    {
        if ((predictCount[i] < min) && predictCount[i] != 0)
        {
            
            min = predictCount[i];
            min_id = i;
        }
   
        if (i == 7 && min_id != -1)
        {

            // if (SetKnight(x + step[min_id][0], y + step[min_id][1]))
            if (Check(x + step[min_id][0], y + step[min_id][1]))
                SetKnight(x + step[min_id][0], y + step[min_id][1]);
             
            else
            {
                turnNumber--;
                board[x][y] = 0;
                predictCount[min_id] = 0;
                SetKnight(x , y , true, predictCount);
            }
        }

    }
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

