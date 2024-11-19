#pragma once
#include <iostream>
#include <cstdlib> /*Para rand y srand*/ 
#include <ctime>   /*Libreria ctime*/
#include <iomanip>
#include <vector>
#include <unordered_map>
#include "TipoCasilla.h"
#include "Dado.h"
#include "Jugador.h"
#include "ListaCircular.h"

class Juego {
public:
	Juego();
	void PlayGame(CircularLinkedList<Jugador>& playerList);
	void setDashboardSize();
	void theresASnakeOrLadder(CircularLinkedList<Jugador>& playerList, int CurrentBoxPlayer);
	void setDashBoard();
	void showDashBoard(CircularLinkedList<Jugador>& playerList);
	bool WinnerPlayer(CircularLinkedList<Jugador>& playerList);
	bool isSpecial(int& casilla);
	TipoCasilla setSnakeAndLadder();
	~Juego();
private:
	/*Mapa desordenado para almacenar las casillas, util para obtener una complejidad de busqueda O(1)*/
	unordered_map<int, TipoCasilla> dashBoard;
	/*Vector que almacena las posiciones que ya han sido reservadas por una cabeza o cola de una serpiente o escalera*/
	vector<int> ocuppiedBoxes;
	/*Llamada a la clase dado*/
	Dado dado;
	/*Cantidad de casillas del tablero*/
	int dashBoardSize = 0;
};