#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

#include "connect4.h"

using namespace std;

int maxDepth = 10;

vector<int> getMoves(array<array<int, 7>, 6> board)
{
    vector<int> moves;

    if (board[0][3] == 0)
        moves.push_back(3);
    if (board[0][2] == 0)
        moves.push_back(2);
    if (board[0][4] == 0)
        moves.push_back(4);
    if (board[0][1] == 0)
        moves.push_back(1);
    if (board[0][5] == 0)
        moves.push_back(5);
    if (board[0][0] == 0)
        moves.push_back(0);
    if (board[0][6] == 0)
        moves.push_back(6);

    return moves;
}

int negamax(array<array<int, 7>, 6> board, int depth, int alpha, int beta, int coef)
{
    if (depth == 0 || gameOver(board) > 0)
        return coef * evaluate(board);

    int maxEval = -1000;
    int bestMove;
    for (int move : getMoves(board))
    {
        int eval;

        if (coef == 1)
            eval = -negamax(pushMove(board, move, 1), depth - 1, -beta, -alpha, -coef);
        else
            eval = -negamax(pushMove(board, move, 2), depth - 1, -beta, -alpha, -coef);

        if (eval > maxEval)
        {
            maxEval = eval;
            bestMove = move;
        }

        alpha = max(alpha, maxEval);
        if (alpha >= beta)
            break;
    }

    if (depth == maxDepth)
        return bestMove;
    else
        return maxEval;
}

int gameOver(array<array<int, 7>, 6> board)
{
    if (board[0][0] != 0 && board[0][1] != 0 && board[0][2] != 0 && board[0][3] != 0 && board[0][4] != 0 && board[0][5] != 0 && board[0][6] != 0)
        return 3;

    int i = 0;
    int j;
    int count;
    int player;

    // horizontal check
    for (i; i < 6; i++)
    {
        count = 0;
        player = 0;

        for (j = 0; j < 7; j++)
        {
            if (board[i][j] == 0)
            {
                count = 0;
                player = 0;
            }
            else if (board[i][j] != player)
            {
                count = 1;
                player = board[i][j];
            }
            else
                count++;

            if (count == 4)
                return player;
        }
    }

    // vertical check
    for (i = 0; i < 7; i++)
    {
        count = 0;
        player = 0;

        for (j = 5; j >= 0; j--)
        {
            if (board[j][i] == 0)
            {
                count = 0;
                player = 0;
            }
            else if (board[j][i] != player)
            {
                count = 1;
                player = board[j][i];
            }
            else
                count++;

            if (count == 4)
                return player;
        }
    }

    // top-left to bottom-right diagonal check
    for (i = 0; i < 3; i++)
    {
        j = 0;
        count = 0;
        player = 0;

        while (i + j < 6)
        {
            if (board[i + j][j] == 0)
            {
                count = 0;
                player = 0;
            }
            else if (board[i + j][j] != player)
            {
                count = 1;
                player = board[i + j][j];
            }
            else
                count++;

            if (count == 4)
                return player;

            j++;
        }
    }

    for (i = 1; i < 4; i++)
    {
        j = 0;
        count = 0;
        player = 0;

        while (i + j < 7)
        {
            if (board[j][i + j] == 0)
            {
                count = 0;
                player = 0;
            }
            else if (board[j][i + j] != player)
            {
                count = 1;
                player = board[j][i + j];
            }
            else
                count++;

            if (count == 4)
                return player;

            j++;
        }
    }

    // bottom-left to top-right diagonal check
    for (i = 3; i < 6; i++)
    {
        j = 0;
        count = 0;
        player = 0;

        while (i - j >= 0)
        {
            if (board[i - j][j] == 0)
            {
                count = 0;
                player = 0;
            }
            else if (board[i - j][j] != player)
            {
                count = 1;
                player = board[i - j][j];
            }
            else
                count++;

            if (count == 4)
                return player;

            j++;
        }
    }

    for (i = 1; i < 4; i++)
    {
        j = 5;
        count = 0;
        player = 0;

        while (i + 5 - j < 7)
        {
            if (board[j][i + 5 - j] == 0)
            {
                count = 0;
                player = 0;
            }
            else if (board[j][i + 5 - j] != player)
            {
                count = 1;
                player = board[j][i + 5 - j];
            }
            else
                count++;

            if (count == 4)
                return player;

            j--;
        }
    }

    return 0;
}

int evaluate(array<array<int, 7>, 6> board)
{
    int res = gameOver(board);

    if (res == 1)
        return 999;
    if (res == 2)
        return -999;
    if (res == 3)
        return 0;

    int eval = 0;
    int i = 0;
    int j;
    int count;
    int player;
    bool slotBefore;

    // horizontal check
    for (i; i < 6; i++)
    {
        count = 0;
        player = 0;
        slotBefore = false;

        for (j = 0; j < 7; j++)
        {
            if (board[i][j] == 0)
            {
                if (slotBefore)
                {
                    if (player == 1)
                        eval += pow(count, 3) * 2;
                    else
                        eval -= pow(count, 3) * 2;
                }
                else
                {
                    if (player == 1)
                        eval += pow(count, 3);
                    else
                        eval -= pow(count, 3);
                }
                count = 0;
                player = 0;
                slotBefore = true;
            }
            else if (board[i][j] != player)
            {
                if (slotBefore)
                {
                    if (player == 1)
                        eval += pow(count, 3);
                    else
                        eval -= pow(count, 3);
                }
                count = 1;
                if (player != 0)
                    slotBefore = false;
                player = board[i][j];
            }
            else
                count++;
        }

        if (slotBefore)
        {
            if (player == 1)
                eval += pow(count, 3);
            else
                eval -= pow(count, 3);
        }
    }

    // vertical check
    for (i = 0; i < 7; i++)
    {
        count = 0;
        player = 0;

        for (j = 5; j >= 0; j--)
        {
            if (board[j][i] == 0)
            {
                if (player == 1)
                    eval += pow(count, 3);
                else
                    eval -= pow(count, 3);
                count = 0;
                player = 0;
            }
            else if (board[j][i] != player)
            {
                count = 1;
                player = board[j][i];
            }
            else
                count++;

            if (count == 4)
                return player;
        }
    }

    // top-left to bottom-right diagonal check
    for (i = 0; i < 3; i++)
    {
        j = 0;
        count = 0;
        player = 0;
        slotBefore = false;

        while (i + j < 6)
        {
            if (board[i + j][j] == 0)
            {
                if (slotBefore)
                {
                    if (player == 1)
                        eval += pow(count, 3) * 2;
                    else
                        eval -= pow(count, 3) * 2;
                }
                else
                {
                    if (player == 1)
                        eval += pow(count, 3);
                    else
                        eval -= pow(count, 3);
                }
                count = 0;
                player = 0;
                slotBefore = true;
            }
            else if (board[i + j][j] != player)
            {
                if (slotBefore)
                {
                    if (player == 1)
                        eval += pow(count, 3);
                    else
                        eval -= pow(count, 3);
                }
                count = 1;
                if (player != 0)
                    slotBefore = false;
                player = board[i + j][j];
            }
            else
                count++;

            if (count == 4)
                return player;

            j++;
        }

        if (slotBefore)
        {
            if (player == 1)
                eval += pow(count, 3);
            else
                eval -= pow(count, 3);
        }
    }

    for (i = 1; i < 4; i++)
    {
        j = 0;
        count = 0;
        player = 0;
        slotBefore = false;

        while (i + j < 7)
        {
            if (board[j][i + j] == 0)
            {
                if (slotBefore)
                {
                    if (player == 1)
                        eval += pow(count, 3) * 2;
                    else
                        eval -= pow(count, 3) * 2;
                }
                else
                {
                    if (player == 1)
                        eval += pow(count, 3);
                    else
                        eval -= pow(count, 3);
                }
                count = 0;
                player = 0;
                slotBefore = true;
            }
            else if (board[j][i + j] != player)
            {
                if (slotBefore)
                {
                    if (player == 1)
                        eval += pow(count, 3);
                    else
                        eval -= pow(count, 3);
                }
                count = 1;
                if (player != 0)
                    slotBefore = false;
                player = board[j][i + j];
            }
            else
                count++;

            if (count == 4)
                return player;

            j++;
        }

        if (slotBefore)
        {
            if (player == 1)
                eval += pow(count, 3);
            else
                eval -= pow(count, 3);
        }
    }

    // bottom-left to top-right diagonal check
    for (i = 3; i < 6; i++)
    {
        j = 0;
        count = 0;
        player = 0;
        slotBefore = false;

        while (i - j >= 0)
        {
            if (board[i - j][j] == 0)
            {
                if (slotBefore)
                {
                    if (player == 1)
                        eval += pow(count, 3) * 2;
                    else
                        eval -= pow(count, 3) * 2;
                }
                else
                {
                    if (player == 1)
                        eval += pow(count, 3);
                    else
                        eval -= pow(count, 3);
                }
                count = 0;
                player = 0;
                slotBefore = true;
            }
            else if (board[i - j][j] != player)
            {
                if (slotBefore)
                {
                    if (player == 1)
                        eval += pow(count, 3);
                    else
                        eval -= pow(count, 3);
                }
                count = 1;
                if (player != 0)
                    slotBefore = false;
                player = board[i - j][j];
            }
            else
                count++;

            if (count == 4)
                return player;

            j++;
        }

        if (slotBefore)
        {
            if (player == 1)
                eval += pow(count, 3);
            else
                eval -= pow(count, 3);
        }
    }

    for (i = 1; i < 4; i++)
    {
        j = 5;
        count = 0;
        player = 0;
        slotBefore = false;

        while (i + 5 - j < 7)
        {
            if (board[j][i + 5 - j] == 0)
            {
                if (slotBefore)
                {
                    if (player == 1)
                        eval += pow(count, 3) * 2;
                    else
                        eval -= pow(count, 3) * 2;
                }
                else
                {
                    if (player == 1)
                        eval += pow(count, 3);
                    else
                        eval -= pow(count, 3);
                }
                count = 0;
                player = 0;
                slotBefore = true;
            }
            else if (board[j][i + 5 - j] != player)
            {
                if (slotBefore)
                {
                    if (player == 1)
                        eval += pow(count, 3);
                    else
                        eval -= pow(count, 3);
                }
                count = 1;
                if (player != 0)
                    slotBefore = false;
                player = board[j][i + 5 - j];
            }
            else
                count++;

            if (count == 4)
                return player;

            j--;
        }

        if (slotBefore)
        {
            if (player == 1)
                eval += pow(count, 3);
            else
                eval -= pow(count, 3);
        }
    }

    return eval;
}

void displayBoard(array<array<int, 7>, 6> board)
{
    system("CLS");

    for (int i = 0; i < 24; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (i % 4 == 0)
                cout << "|-----";
            else if ((i - 2) % 4 == 0)
            {
                if (board[floor(i / 4)][j] == 1)
                    cout << "|  X  ";
                else if (board[floor(i / 4)][j] == 2)
                    cout << "|  O  ";
                else
                    cout << "|     ";
            }
            else
                cout << "|     ";
        }

        cout << "|\n";
    }

    cout << "-------------------------------------------";
}

bool validMove(array<array<int, 7>, 6> board, int col)
{
    return col >= 0 && col < 7 && board[0][col] == 0;
}

array<array<int, 7>, 6> pushMove(array<array<int, 7>, 6> board, int col, int player)
{
    int row = 5;

    while (row > 0 && board[row][col] != 0)
        row--;

    board[row][col] = player;

    return board;
}