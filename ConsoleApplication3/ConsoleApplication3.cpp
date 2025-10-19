#include <iostream>
#include <locale>
#include "player.h"

using namespace std;

//setlocale(LC_ALL, "");

int main()
{
    char board[10][10];
    player gracz("abc");
    gracz.guess(gracz);
    //string playerName = "test";
    //player player1(playerName);
    //cout << "Ilosc statkow gracza: " << player1.getShips();

    //while (true) {
    //    if (player1.getShips() == 0 /* || computer.getships == 0 */) {
    //        break;
    //    }
    //    cout << "Gra trwa.";
    //    player1.guess();
    //}
    
}


/*
Gracz podaje swoją nazwę. Następnie program przechodzi do metody/funkcji rozkładania statków na planszy.
Podczas tego musi być sprawdzane czy statki sie nie stykaja, czy miejsce nie jest już zajęte,
czy jest w indexie tablicy położenie.
Wlacza sie glowna petla gry, ktora wywoluje metody guess gracza i random guess komputera na przemian dopoki
wszystkie statki jednego z graczy nie zostana trafione.
W metodzie guess podac x,y if trafiony, to jeszcze raz.

char tablica:
    h - hit
    m - missed
    s - ship
    e - empty
*/