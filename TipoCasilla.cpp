#include "TipoCasilla.h"
/*Constructor vacio*/
TipoCasilla::TipoCasilla(){}
/*Constructor de escalera o serpiente*/
TipoCasilla::TipoCasilla(int BoxType, int Head, int Tail):boxType(BoxType), head(Head), tail(Tail) {}
/*Funcion que obtiene el tipo de casilla especial, ya sea 1 para escaleras, 2 para serpientes*/
int TipoCasilla::getBoxType() const { return boxType; }
/*Retorna la cabeza, osea la parte de arriba de la escalera o serpiente*/
int TipoCasilla::getHead() const { return head; }
/*Retorna la cola, osea la parte de abajo de la escalera o serpiente*/
int TipoCasilla::getTail() const { return tail; }
/*Destructor*/
TipoCasilla::~TipoCasilla(){}