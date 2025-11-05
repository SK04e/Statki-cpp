#include <iostream>
#include <locale>
#include "player.h"

using namespace std;

//setlocale(LC_ALL, "");

int main()
{
    player gracz1("dupa");
    player gracz2("dupa2");

    //p1 = &gracz1;

    gracz1.initBoards();
    gracz2.initBoards();
    system("cls");
    gracz1.writePlayerBoard();
    gracz1.placeShips();
    system("cls");
    gracz2.writeEnemyBoard(gracz1);
    gracz2.guess(gracz1);
    gracz2.writeEnemyBoard(gracz1);

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

  
Init pustej tablicy u obu graczy -> rozlozenie statkow 
    
    */