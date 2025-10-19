#pragma once
#include <iostream>
#include <stdlib.h>
#include <locale>
#include <vector>
using namespace std;

class player {
private:
    string name;
    int ships;
    void placeShips();
    char board[10][10] = { {'h','h','h','h','h','h','h','h','h','h'},
                           {'e','e','e','e','e','e','e','e','e','e'} };
    vector<int> fleet = { 4,3,3,2,2,2,1,1,1,1 };


public:
    player(string name) {
        this->name = name;
        this->ships = 10;
        cout << "Utworzono obiekt gracza: " << name << "\n";
    }

    int getShips(player& human) const;
    void subShips(player& human);
    char checkField(player& human, int x, int y);
    char guess(player& human);

};
