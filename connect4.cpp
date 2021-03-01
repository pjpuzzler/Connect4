#include <iostream>

using namespace std;

bool gameOver(int board[7][7], int col)
{
    int row = 5;
    int i = 0;
    int count = 0;
    int player;
    int diagRow;
    int diagCol;

    while (row >= 0 && board[row][col] != 0)
        row--;

    row++;

    player = board[row][col];

    // horizontal check
    for (i; i < 7; i++)
    {
        if (board[row][i] == player)
            count++;
        else
            count = 0;

        if (count == 4)
            return true;
    }

    // vertical check
    count = 0;

    for (i = 0; i < 7; i++)
    {
        if (board[i][col] == player)
            count++;
        else
            count = 0;

        if (count == 4)
            return true;
    }

    // top-left to bottom-right diagonal check
    count = 0;

    if (row < 4)
    {
        diagRow = 0;
    }
    else
        diagRow = row - 3;

    if (col < 4)
        diagCol = 0;
    else
        diagCol = col - 3;

    if (diagRow < 4 && diagCol < 4)
    {
        for (i = 0; i < 7; i++, diagRow++, diagCol++)
        {
            if (board[diagRow][diagCol] == player)
                count++;
            else
                count = 0;

            if (count == 4)
                return true;
        }
    }

    // bottom-left to top-right diagonal check
    count = 0;

    if (row > 2)
    {
        diagRow = 6;
    }
    else
        diagRow = row + 3;

    if (col < 4)
        diagCol = 0;
    else
        diagCol = col - 3;

    if (diagRow > 2 && diagCol < 4)
    {
        for (i = 0; i < 7; i++, diagRow--, diagCol++)
        {
            if (board[diagRow][diagCol] == player)
                count++;
            else
                count = 0;

            if (count == 4)
                return true;
        }
    }

    return false;
}

void displayBoard(int board[7][7])
{
    system("CLS");

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            cout << board[i][j] << "  ";
        }

        cout << "\n";
    }
}

bool validMove(int board[7][7], int col)
{
    return col >= 0 && col < 7 && board[0][col] == 0;
}

void move(int board[7][7], int col, int player)
{
    int row = 6;

    while (row > 0 && board[row][col] != 0)
        row--;

    board[row][col] = player;
}

int main(int argc, char *argv[])
{
    bool humanPlayerOne = true;
    bool humanPlayerTwo = true;
    int board[7][7] = {};
    int player = 1;
    int col;

    do
    {
        if (player == 1 && !humanPlayerOne || player == 2 && !humanPlayerTwo)
        {
            // AI turn
            displayBoard(board);
        }
        else
        {
            // player turn
            while (true)
            {
                // try
                // {
                displayBoard(board);

                if (player == 1)
                    cout << "\n(Player 1) Column: ";
                else
                    cout << "\n(Player 2) Column: ";

                cin >> col;
                col--;

                if (validMove(board, col))
                {
                    move(board, col, player);
                    break;
                }
                // }
                // catch ()
                // {
                //     continue;
                // }
            }
        }

        // change turn
        if (player == 1)
            player = 2;
        else
            player = 1;
    } while (!gameOver(board, col));

    displayBoard(board);

    if (player == 2)
        cout << "\nPlayer 1 Wins!";
    else
        cout << "\nPlayer 2 Wins!";

    return 0;
}