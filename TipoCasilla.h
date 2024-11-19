#pragma once

class TipoCasilla{
public:
	TipoCasilla();
	TipoCasilla(int BoxType, int Head, int Tail);/*Escalera o Serpiente*/
	int getBoxType() const;
	int getHead() const; /*Head = donde empieza*/
	int getTail() const;/*Tail = donde termina*/
	~TipoCasilla();
private:
	int boxType = 0;
	int head=0;
	int tail=0;
};