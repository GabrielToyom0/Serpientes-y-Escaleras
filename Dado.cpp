#include "Dado.h"

/*Constructor*/
Dado::Dado() { srand(time(0));}

/*Funcion que retorna un numero del 1 al 6, simulando un dado de juego*/
int Dado::throwDice() {
	/*Funcion de la libreria random que retorna un numero entre 1 y 6*/
	return (rand() % 6) + 1;
};

/*Destructor del objeto*/
Dado::~Dado(){}