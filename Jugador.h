#pragma once
#include<iostream>
#include <string>
#include "ListaCircular.h"

using namespace std;
class Jugador{
public:
	Jugador(int ID_Player, string PlayerName);
	int getID() const;
	int getCurrentBox();
	void setCurrentBox(int newCurrentBox);
	string getName() const;
	~Jugador();
private:
	int id_Player;
	string playerName;
	int currentBox;
};