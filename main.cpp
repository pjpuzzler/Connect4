#include <iostream>

#include "connect4.h"

int main(int argc, char *argv[])
{
    bool humanPlayerOne = true;
    bool humanPlayerTwo = false;
    array<array<int, 7>, 6> board = {};
    int player = 1;
    int col;

    do
    {
        if (player == 1 && !humanPlayerOne || player == 2 && !humanPlayerTwo)
        {
            // AI turn
            displayBoard(board);

            if (player == 1)
                board = pushMove(board, negamax(board, maxDepth, -100, 100, 1), player);
            else
                board = pushMove(board, negamax(board, maxDepth, -100, 100, -1), player);
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
                    board = pushMove(board, col, player);
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
    } while (gameOver(board) == 0);

    int res = gameOver(board);

    displayBoard(board);

    if (res == 3)
        cout << "\nDraw!";
    else if (res == 2)
        cout << "\nPlayer 2 Wins!";
    else
        cout << "\nPlayer 1 Wins!";

    return 0;
}