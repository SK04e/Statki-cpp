#pragma once
#include <iostream>
#include <stdlib.h>
#include <locale>
#include <vector>
using namespace std;

class player {
private:
    const int boardSize = 10;
    string name;
    int ships;
    char board[10][10] = { {'h','s','e','m','e','e','e','h','e','h'},
                           {'e','s','e','s','e','e','e','e','e','e'} };
    vector<int> fleet = { 4,3,3,2,2,2,1,1,1,1 };


public:
    player(string name) {
        this->name = name;
        this->ships = 10;
        cout << "Utworzono obiekt gracza: " << name << "\n";
    }

    int getShips(player& human) const;
    void subShips();
    //char checkField(player& human, int x, int y);
    char guess(player& human);
    void writeBoard() const;
    void placeShip();
    void checkIfEmpty(int x, int y, int currentShipSize, bool vertical);
    int checkAround(int x, int y);
    void directionChange();
};
