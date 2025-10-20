#include "player.h"
#include "GameExceptions.h"

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

char player::guess(player& human) { //gracz zgaduje pole, sprawdzanie inputu, zwracanie h(hit) lub m(miss) i zmiana tablicy
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

void player::placeShip() {
    int fleeteSize = fleet.size();
    int currentShipSize;
    int x, y;
    bool vertical;
    for (int i = 0; i < fleeteSize; ++i) {
        currentShipSize = fleet[i];
        cout << "Insert coordinates to place a ship (there can't be any other ships around" << endl;
        cin >> x >> y;
        --x; --y;
        //podaj kordy x,y 
        
        while (1) {
            try {
                cout << "Insert two digits to guess coordinates (rows/columns)" << endl;
                cin >> x >> y;
                --x;
                --y;
                //kontynuacja
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

void player::checkIfEmpty(int x, int y, int currentShipSize, bool vertical) {
    static int canPlace = 1;

    if ((x >= 0 && x <= 9) && (y >= 0 && y <= 9)) {
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
                    if (checkAround(x, y) == 0) {
                        cout << "You can place a ship here!" << endl;
                    }
                    else {
                        cout << "Can't place a ship here!" << endl;
                    }
                }
                else if (vertical) {
                    for (int i = 0; i < currentShipSize; ++i) {
                        if (checkAround(x, (y + i)) == 1) {
                            canPlace = 0;
                            cout << "You can't place a ship here!" << endl;
                        }
                        if (canPlace) {
                            cout << "You can place a ship here!" << endl;
                        }
                    }
                }
                else if (!vertical) {
                    for (int i = 0; i < currentShipSize; ++i) {
                        if (checkAround((x+i), y) == 1) {
                            canPlace = 0;
                            cout << "You can't place a ship here!" << endl;
                        }
                        if (canPlace) {
                            cout << "You can place a ship here!" << endl;
                        }
                    }
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

int player::checkAround(int x, int y) {
    int x1, y1;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            x1 = x - 1 + i;
            y1 = y - 1 + j;
            if ((x1 < 0 || x1 < 9) || (y1 < 0 && y1 < 9)) {
                continue;
            }
            else {
                if (board[x - 1 + i][y - 1 + j] == 's') {
                    return 1; //BLAD, JUZ POLOZONY STATEK
                }
            }
        }
    }
    return 0;
}
