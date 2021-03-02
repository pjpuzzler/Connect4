#include <iostream>

#include "connect4.h"

int main(int argc, char *argv[])
{
    bool humanPlayerOne = true;
    bool humanPlayerTwo = true;
    array<array<int, 7>, 6> board = {};
    int player = 1;
    int depth = 5;
    int col;

    do
    {
        if (player == 1 && !humanPlayerOne || player == 2 && !humanPlayerTwo)
        {
            // AI turn
            int coef;

            displayBoard(board);

            if (player == 1)
                coef = 1;
            else
                coef = -1;

            board = pushMove(board, negamax(board, depth, -100, 100, coef), player);
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