#include "player.h"

void player::subShips() {
    ships -= 1;
}

int player::getShips(player &human) const {
    return ships;
}

void player::writeBoard() const {
    vector<char> alphabet = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };
    cout << "  1 2 3 4 5 6 7 8 9 10" << endl;
    for (int i = 0; i < 10; i++) {
        cout << alphabet[i] << " ";
        for (int j = 0; j < 10; j++) {
            if (board[i][j] == 'h' || board[i][j] == 'm') {
                cout << board[i][j]<< " ";
            }
            else {
                cout << "? ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

char player::guess(player &human) { //gracz zgaduje pole, sprawdzanie inputu, zwracanie h(hit) lub m(miss) i zmiana tablicy
    int x, y;

    while (1) {
        try {
            cout << "Insert two digits to guess coordinates (rows/columns)" << endl;
            cin >> x >> y;
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
                            cout << "Fields was empty!" << endl;
                            return 'm';
                        }
                        else if (board[x][y] == 's') {
                            board[x][y] = 'h';
                            cout << "You got a hit! Try again" << endl;
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

void player::placeShips() {
    int fleeteSize = fleet.size();
    int currentShipSize;
    int x, y;
    bool vertical = true; // bedzie z statku przekazane?        //do zmiany bo blad wywala jak nie ustalone
    for (int i = 0; i < fleeteSize; ++i) {
        currentShipSize = fleet[i];

        while (1) {
            try {
                cout << "Insert two digits to guess coordinates (rows/columns)" << endl;
                cin >> x >> y;
                --x;
                --y;
                if ((x >= 0 && x <= 9) && (y >= 0 && y <= 9)) {
                    if (checkIfEmpty(x, y, currentShipSize, vertical) == 1) {
                        //placeTheShip(currentShipSize, vertical);
                        //createShipObject(currentShipSize, vertical);
                    }
                    else {
                        throw GameException("There was a ship somewhere too close!");
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

        //sprawdz kordy x,y
        //sprawdz kordy wokol
        //jesli polozony, to pop? albo nie
    }
}

bool player::checkIfEmpty(int x, int y, int currentShipSize, bool vertical) { //0 - ERROR, NOT EMPTY, 1 - OK
    int canPlace = 1;

        try {
            if (board[x][y] == 's') {
                throw GameException("There is already ship on that coords");
            }
            else if ((x+currentShipSize-1>boardSize) || (y+currentShipSize-1>boardSize)) {
                throw GameException("Can't fit this ship here!");
            }
            else {
                //srawdzenie horizontal czy vertical statku
                if (currentShipSize == 1) {
                    if (checkAround(x, y) == 1) {
                        cout << "You can place a ship here!" << endl;
                        return 1;
                    }
                    else {
                        cout << "Can't place a ship here!" << endl;
                        return 0;
                    }
                }
                else if (vertical) {
                    for (int i = 0; i < currentShipSize; ++i) {
                        if (checkAround(x, (y + i)) == 0) {
                            canPlace = 0;
                            cout << "You can't place a ship here!" << endl;
                            return 0;
                        }
                    }
                    if (canPlace) {
                        cout << "You can place a ship here" << endl;
                        return 1;
                    }
                }
                else if (!vertical) {
                    for (int i = 0; i < currentShipSize; ++i) {
                        if (checkAround((x+i), y) == 0) {
                            canPlace = 0;
                            cout << "You can't place a ship here!" << endl;
                            return 0;
                        }
                    }
                    if (canPlace) {
                        cout << "You can place a ship here!" << endl;
                        return 1;
                    }
                }
            }
        }
        catch (const GameException& e) {
            cout << e.what() << endl;
        }
    }

int player::checkAround(int x, int y) { //0 - ERROR, 1 - OK
    int x1, y1;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            x1 = x - 1 + i;
            y1 = y - 1 + j;
            if ((x1 < 0 || x1 > 9) || (y1 < 0 && y1 > 9)) {
                continue;
            }
            else {
                if (board[x - 1 + i][y - 1 + j] == 's') {
                    return 0; //BLAD, JUZ POLOZONY STATEK
                }
            }
        }
    }
    return 1;
}
