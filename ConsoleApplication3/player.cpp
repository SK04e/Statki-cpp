#include "player.h"
#include "GameExceptions.h"

void player::subShips(player& human) {
    ships -= 1;
}

int player::getShips(player &human) const {
    return ships;
}

char player::guess(player& human) { //gracz zgaduje pole, sprawdzanie inputu, zwracanie h(hit) lub m(miss) i zmiana tablicy
    int x, y;

    while (1) {
        try {
            cout << "Insert two digits to guess coordinates" << endl;
            cin >> y >> x;
            --x;
            --y;
            if ((x >= 0 && x <= 9) && (y >= 0 && y <= 9)) {
                try {
                    if (board[x][y] == 'h' || board[x][y] == 'm') {
                        throw GameException("Those coordinates were already guessed");
                    }
                    else {
                        if (board[x][y] == 'e') {
                            board[x][y] = 'm';
                            return 'm';
                        }
                        else if (board[x][y] == 's') {
                            board[x][y] = 'h';
                            return 'h';
                        }
                    }
                }
                catch (const GameException& e) {
                    cout << e.what() << endl;
                }
            }
            else {
                throw GameException("Pass correct digits (1-10)");
            }
        }
        catch (const GameException& e) {
            cout << "Exception: " << e.what() << endl;
        }
        catch (...) {
            cout << "Default Exception!";
        }
    }
}