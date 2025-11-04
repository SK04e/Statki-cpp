#include "player.h"
#include <conio.h>

void player::subShips() {
    ships -= 1;
}

int player::getShips(player &human) const {
    return ships;
}

void player::writePlayerBoard() const {
    vector<char> alphabet = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };
    cout << "  1 2 3 4 5 6 7 8 9 10" << endl;
    for (int i = 0; i < 10; i++) {
        cout << alphabet[i] << " ";
        for (int j = 0; j < 10; j++) {
            if (playerBoard[i][j] == 'h' || playerBoard[i][j] == 'm') {
                cout << playerBoard[i][j]<< " ";
            }
            else if (playerBoard[i][j] == 's') {
                cout << "s ";
            }
            else {
                cout << "e ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void player::writeEnemyBoard() const {
    vector<char> alphabet = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };
    cout << "  1 2 3 4 5 6 7 8 9 10" << endl;
    for (int i = 0; i < 10; i++) {
        cout << alphabet[i] << " ";
        for (int j = 0; j < 10; j++) {
            if (enemyBoard[i][j] == 'h' || enemyBoard[i][j] == 'm') {
                cout << enemyBoard[i][j] << " ";
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
                    if (enemyBoard[x][y] == 'h' || enemyBoard[x][y] == 'm') {
                        throw GameException("Those coordinates were already guessed");
                    }
                    else {
                        if (enemyBoard[x][y] == 'e') {
                            enemyBoard[x][y] = 'm';
                            cout << "Fields was empty!" << endl;
                            return 'm';
                        }
                        else if (enemyBoard[x][y] == 's') {
                            enemyBoard[x][y] = 'h';
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
    char direction;
    bool vertical;
    for (int i = 0; i < fleeteSize; ++i) {
        currentShipSize = fleet[i];

        while (1) {
            try {
                //cout << "You are placing ship " << (vertical? "vertical" : "horizontal") << endl;
                cout << "Current ship size is: " << currentShipSize << endl;
                cout << "Insert two digits to guess coordinates (rows/columns): ";
                cin >> x >> y;
                cout << "Choose ship direction. Insert h for horizontal or v for vertical: ";
                while (1) {
                    direction = getchar();
                    if (direction == 'h' || direction == 'v') {
                        break;
                    }
                }
                
                if (direction == 'h') {
                    vertical = 0;
                }
                else {
                    vertical = 1;
                }

                --x;
                --y;
                if ((x >= 0 && x <= 9) && (y >= 0 && y <= 9)) {
                    if (checkIfEmpty(x, y, currentShipSize, vertical) == 1) {
                        placeTheShip(x, y, currentShipSize, vertical);
                        cout << "Wcisnij dowolny przycisk...";
                        _getch();
                        system("cls");
                        writePlayerBoard();
                        //createShipObject(currentShipSize, vertical);
                        break;
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
    }
}

bool player::checkIfEmpty(int x, int y, int currentShipSize, bool vertical) { //0 - ERROR, NOT EMPTY, 1 - OK
    int canPlace = 1;

        try {
            if (playerBoard[x][y] == 's') {
                throw GameException("There is already ship on that coords");
            }
            //trzeba sprawdzic vertical czy horizontal zamiast ora
            else if ((vertical && x + currentShipSize - 1 >= boardSize) || (!vertical && y + currentShipSize - 1 >= boardSize)) {
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
                        if (checkAround((x + i), y) == 0) {
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
                        if (checkAround(x, (y+i)) == 0) {
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
                if (playerBoard[x - 1 + i][y - 1 + j] == 's') {
                    return 0; //BLAD, JUZ POLOZONY STATEK
                }
            }
        }
    }
    return 1;
}


void player::placeTheShip(int x, int y, int currentShipSize, bool vertical) {
    if (vertical) {
        for (int i = 0; i < currentShipSize; ++i) {
            playerBoard[x+i][y] = 's';
        }
    }
    if (!vertical) {
        for (int i = 0; i < currentShipSize; ++i) {
            playerBoard[x][y+i] = 's';
        }
    }
}

void player::initBoards() {
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            playerBoard[i][j] = 'e';
            enemyBoard[i][j] = '?';
        }
    }
}

void player::directionChange(bool &vertical) {
    vertical = !vertical;
}