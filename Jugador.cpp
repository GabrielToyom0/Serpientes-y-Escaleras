#include "Jugador.h"
/*Constructor del objeto*/
Jugador::Jugador(int ID_Player, string PlayerName): id_Player(ID_Player), playerName(PlayerName), currentBox(1) {};
/*Funcion para conseguir el numero de cada jugador*/
int Jugador::getID() const { return id_Player; }
/*Funcion para conseguir el nombre de cada jugador*/
string Jugador::getName() const { return playerName; }
/*Funcion para conseguir la posición actual de cada jugador*/
int Jugador::getCurrentBox() { return currentBox; }
/*Metodo para definir el cambio de casillas a lo largo del juego*/
void Jugador::setCurrentBox(int newCurrentBox) {
	currentBox = newCurrentBox;
}
/*Destructor del objeto*/
Jugador::~Jugador() {};