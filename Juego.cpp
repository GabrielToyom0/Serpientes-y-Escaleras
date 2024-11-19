#include "Juego.h"
Juego::Juego() { srand(time(0));};

/*Metodo principal, encargada de todo el proceso de juego*/
void Juego::PlayGame(CircularLinkedList<Jugador> &playerList) { 
	setDashboardSize();
	cin.get();
	bool winner = false;
	int turn = 1;
	do
	{
		cout << "\n\t--------- TURNO NO."<<turn<<" ---------";
		cout << "\n\tEs el turno de: " << playerList.getHeadData().getName() << "\n";
		cout << "\tSu posicion actual es : " << playerList.getHeadData().getCurrentBox() << "\n";
		cout << "\t------------------------------\n";
		cout << "\t\033[5;36mPresione Enter para lanzar el dado...\033[0m\n";
		cin.get();
		int diceResult = dado.throwDice();
		int currentBoxPlayer = playerList.getHeadData().getCurrentBox() + diceResult;
		cout << "\n\t\033[1;35m--------RESULTADO DADO--------\t\n";
		cout << "\tEl dado ha dado:\033[0m " << diceResult << "\033[1;35m\n";
		
		if (currentBoxPlayer > dashBoardSize){
			cout << "\t\033[0;31mTe pasaste de la casilla final, permaneces en la casilla \033[0m"<< playerList.getHeadData().getCurrentBox() <<"\033[0;31m!\033[0m\n";
			cout << "\t\033[1;35m------------------------------\033[0m\n";
			showDashBoard(playerList);
			cout << "\n\t\033[5;36mPresione Enter para continuar...\033[0m\n";
			cin.get();
			playerList.getNextTurn();
		}
		else{

			playerList.getHeadData().setCurrentBox(currentBoxPlayer);
			theresASnakeOrLadder(playerList, playerList.getHeadData().getCurrentBox());
			cout <<"\t" << playerList.getHeadData().getName() << " se dirige a  la casilla\033[0m " << playerList.getHeadData().getCurrentBox() << "!\n";
			cout << "\t\033[1;35m------------------------------\033[0m\n\n";
			showDashBoard(playerList);
			if (WinnerPlayer(playerList)) {
				cout << "\n\t\033[5;37m------- GANADOR -------\033[0m\n";
				cout<< "\t" << playerList.getHeadData().getName() << " \033[5;37m es el ganador!\n";
				cout << "\t-----------------------\033[0m\n";
				winner = true;
			}
			else if (!WinnerPlayer(playerList)) {
				cout << "\n\t\033[5;36mPresione Enter para continuar...\033[0m\n";
				cin.get();
				playerList.getNextTurn();
			}
		}
		++turn;
	} while (!winner);
		dashBoard.clear();
		ocuppiedBoxes.clear();
};

/*Metodo que define el tamaño del tablero*/
void Juego::setDashboardSize() {
	cout << "Ingrese cuantas casillas desea en el tablero: ";
	while (!(cin >> dashBoardSize) || dashBoardSize < 30 || dashBoardSize % 5 != 0) {
		cout << "\033[1;31mEntrada invalida. Debe ingresar un número mayor o igual a 30 y multiplo de 5:\033[0m ";
		cin.clear();  /*Limpiar cualquier error de entrada*/
		cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignorar cualquier entrada no válida 
	}
	cout << "Se ha creado un tablero de " << dashBoardSize << " casillas\n";
	setDashBoard();
}

void Juego::setDashBoard() {
	/*25% del tablero designado a casillas especiales*/
	int maxSnakesAndLadders = round(dashBoardSize * 0.25); 
	int snakeOrLadder = 0; /*Contador para saber casillas usan las serpientes o escaleras a lo largo del tablero*/
	for (int i = 0; i < dashBoardSize; i++) {
		int currentRow = i / 6; /*Fila Actual*/
		int specialInRow = 0;
		/*Contar cuántas escaleras/serpientes ya hay en la fila*/
		for (int j = currentRow * 6; j < (currentRow + 1) * 6; j++) {
			if (dashBoard.count(j) && dashBoard[j].getBoxType() != 0) {
				specialInRow++;
			}
		}

		/*Si pasa la validación, almacenarla el mismo objeto tanto en la posición de la cabeza como la de la cola */
		if (snakeOrLadder < maxSnakesAndLadders && specialInRow < 3) {
			TipoCasilla newSpecialBox = setSnakeAndLadder();
			snakeOrLadder += 2;
			dashBoard[newSpecialBox.getHead()] = newSpecialBox;
			dashBoard[newSpecialBox.getTail()] = newSpecialBox;
		}
	}
}

/*Creacion de casillas especiales, ya sea serpiente o escalera*/
TipoCasilla Juego::setSnakeAndLadder() {
	int type, head, tail;
	do {
		type = rand() % 2 + 1; /*Definir si será escalera o serpiente*/
		/*Las cabezas podrán estar entre la casilla 1 y la mitad del tablero*/
		head = rand() % (dashBoardSize / 2) + 2;
		/*Las colas podrán estar a partir de la mitad del tablero y no pueden ser menores a las cabezas*/
		tail = rand() % (dashBoardSize / 2) + (dashBoardSize / 2) - 1;
	} while (isSpecial(head) || isSpecial(tail) || head == tail);
	/*Una vez validado que la serpiente o escalera puedan ser creados, se añaden al set de posiciones ocupadas y
	retorna la casilla*/
	ocuppiedBoxes.push_back(head);
	ocuppiedBoxes.push_back(tail);
	return TipoCasilla(type, head, tail);
}

/*Funcion que retorna verdadero en caso la casilla ya este ocupada*/
bool Juego::isSpecial(int& box) {
	for (int i = 0; i < ocuppiedBoxes.size(); i++) {
		if (ocuppiedBoxes[i] == box) {
			return true;
		}
	}
	return false;
}

//Metodo que se encarga de mostrar el tablero y como los jugadores van a avanzando
void Juego::showDashBoard(CircularLinkedList<Jugador>& playerList) {
	for (int i = 0; i < dashBoardSize; i++) {
		if (i % 6 == 0 && i != 0) {
			cout << "||\n";
		}

		bool currentPlayerBox = (playerList.getHeadData().getCurrentBox() == i + 1);
		if (currentPlayerBox) {
			cout << "\033[5;34m";  // Mostrar que el jugador se encuentra en esa casilla
		}
		cout << "|| " << setw(4) << (i + 1) << ":";
		if (dashBoard.count(i + 1)) {  /*Verificar si la casilla está en el mapa (serpiente o escalera)*/
			if (dashBoard.at(i + 1).getBoxType() == 1) { /*En caso sea escalera*/
				cout << "\033[0;33m";
				cout << setw(14) << left << ("E(" + to_string(dashBoard.at(i + 1).getHead()) + "->" + to_string(dashBoard.at(i + 1).getTail()) + ")\033[0m");
			}
			else if (dashBoard.at(i + 1).getBoxType() == 2) { /*En caso sea serpiente*/
				cout << "\033[1;32m";
				cout << setw(14) << left << ("S(" + to_string(dashBoard.at(i + 1).getTail()) + "->" + to_string(dashBoard.at(i + 1).getHead()) + ")\033[0m");
			}
		}
		else {
			/*En caso de casilla normal*/
			cout << setw(14) << left << "N\033[0m"; 
		}
		if (currentPlayerBox) {
			cout << "\033[0m";  
		}
	}
	cout << "||\n";
}

/*Funcion que define si el jugador ha ganado o no, mientras ninguno gane el juego continua*/
bool Juego::WinnerPlayer(CircularLinkedList<Jugador> &playerList) {
	if (playerList.getHeadData().getCurrentBox() == dashBoardSize) {
		return true;
	}
	return false;
}

void Juego::theresASnakeOrLadder(CircularLinkedList<Jugador> &playerList,int CurrentBoxPlayer){
	if (dashBoard.count(CurrentBoxPlayer)) { /*Verificar si la casilla está en el mapa(serpiente o escalera)* /
		/*Si es escalera*/
		if (dashBoard.at(CurrentBoxPlayer).getBoxType() == 1 && CurrentBoxPlayer == dashBoard.at(CurrentBoxPlayer).getHead()) {
			cout<<"\t" << to_string(dashBoard.at(CurrentBoxPlayer).getHead()) << " -> Has caido en una escalera! \n";
			CurrentBoxPlayer = dashBoard.at(CurrentBoxPlayer).getTail();
			playerList.getHeadData().setCurrentBox(CurrentBoxPlayer);
		}
		/*Si es serpiente*/
		else if (dashBoard.at(CurrentBoxPlayer).getBoxType() == 2 && CurrentBoxPlayer == dashBoard.at(CurrentBoxPlayer).getTail()) {
			cout<<"\t" << to_string(dashBoard.at(CurrentBoxPlayer).getTail()) << " -> Has caido en una serpiente! \n";
			CurrentBoxPlayer = dashBoard.at(CurrentBoxPlayer).getHead();
			playerList.getHeadData().setCurrentBox(CurrentBoxPlayer);
		}
	}
};

/*Destructor del objeto juego*/
Juego::~Juego(){}