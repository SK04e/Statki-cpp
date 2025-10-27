#pragma once
#include <vector>
#include "player.h"

using namespace std;

class ship {
private:
    bool sank;
    int size;
    bool vertical;
public:
    //konstruktor
    ship(int size, bool vertical) {
        this->size = size;
        this->vertical = vertical;
        this->sank = false;
        cout << "Ship of size " << size << " has been created";
    }
    int observer(vector<int>& coords, player& human);
};