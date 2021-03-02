#include <vector>
#include <array>

using namespace std;

extern int maxDepth;

vector<int> getMoves(array<array<int, 7>, 6> board);

int negamax(array<array<int, 7>, 6> board, int depth, int alpha, int beta, int coef);

int gameOver(array<array<int, 7>, 6> board);

int evaluate(array<array<int, 7>, 6> board);

void displayBoard(array<array<int, 7>, 6> board);

bool validMove(array<array<int, 7>, 6> board, int col);

array<array<int, 7>, 6> pushMove(array<array<int, 7>, 6> board, int col, int player);
