#pragma once
#include <iostream>
#include <stdlib.h>
#include <locale>
#include <vector>
#include "GameExceptions.h"

using namespace std;

class player {
private:
    static constexpr int boardSize = 10;
    string name;
    int ships;
    char playerBoard[boardSize][boardSize];
    char enemyBoard[boardSize][boardSize];
    const char hit = 'X';
    const char miss = 'O';
    vector<int> fleet = { 4,3,3,2,2,2,1,1,1,1 };


public:
    player(string name) {
        this->name = name;
        this->ships = 10;
        cout << "Utworzono obiekt gracza: " << name << "\n";

    }

    void initBoards();
    int getShips() const;
    void subShips();
    //char checkField(player& human, int x, int y);
    void guess(player& enemy);
    void writePlayerBoard() const;
    void writeEnemyBoard(player& enemy) const;
    void placeShips();
    bool checkIfEmpty(int x, int y, int currentShipSize, bool vertical);
    int checkAround(int x, int y);
    void placeTheShip(int x, int y, int currentShipSize, bool vertical);
    void directionChange(bool& vertical);
};
