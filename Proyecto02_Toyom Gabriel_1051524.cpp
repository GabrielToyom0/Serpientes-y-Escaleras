/*Proyecto 02 - Realizado por Gabriel Emilio Toyom Jimenez */
/*Carne - 1051524 */
#include <iostream>
#include <regex>/*Libreria para validacion de caracteres especiales*/
#include "ListaCircular.h"
#include "Jugador.h"
#include "Juego.h"

using namespace std;
int numberPlayer = 0;
CircularLinkedList<Jugador> PlayerList;
Juego play;

bool stringValidation(const string& string) {
	/*regex delimita y permite unicamente letras mayusculas, minuscilas y espacios*/
	regex pattern("^[a-zA-Z\\s]+$");
	/*Retornar false o verdadero para saber si la entrada es valida*/
	return regex_match(string, pattern);
}

void AddPlayer() {
	string playerName;
	bool isValid = true;
	cout << "Ingrese el nombre del jugador: "; cin >> playerName;
	if (stringValidation(playerName)) {
		Jugador newPlayer = Jugador(numberPlayer + 1, playerName);
		PlayerList.addNode(newPlayer);
		cout << "\n\t\033[1;34m-------- JUGADOR AGREGADO --------\033[0m";
		cout << "\n\tEl jugador No." << numberPlayer + 1 << " es: " << playerName << "!\n";
		cout << "\t\033[1;34m----------------------------------\033[0m\n\n";
		numberPlayer++;
	}
	else{
		cout << "\n\t\033[1;31m-------- ERROR DE SISTEMA --------";
		cout << "\n\tEl nombre del jugador es invalido!\n";
		cout << "\t----------------------------------\033[0m\n\n";
		cout << "Ingrese nuevamente la opcion que desea realizar: \n";
	}
}

void RemovePlayer() {
	cout << "Ingrese el numero del jugador que desea eliminar: ";
	int deletePlayer;
	if (!(cin >> deletePlayer)|| deletePlayer > numberPlayer) {
		cout << "\n\033[1;31mEntrada invalida o la posicion del jugador no existe!\033[0m\n\n";
		cin.clear();  /*Limpiar cualquier error de entrada*/
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); /*Ignorar cualquier entrada no valida*/
	}
	else{
		PlayerList.deleteNode(deletePlayer -1);
		cout << "Jugador en la posicion No." << deletePlayer << " ha sido eliminado!\n";
		numberPlayer--;
	}
};

void ShowPlayers() {
	if (PlayerList.isEmpty()) {
		cout << "\n\t\033[1;31mLISTA DE JUGADORES VACIA!\033[0m\n\n";
	}
	else {
		CircularLinkedList<Jugador> ListToShow = PlayerList;
		cout << "\t\033[1;34m--------- JUGADORES ---------\033[0m\n";
		while (!ListToShow.isEmpty()) {
			Jugador jugadorTemp = ListToShow.getHeadData();
			cout << "\tJugador No." << jugadorTemp.getID() << " es: " << jugadorTemp.getName() << "\n";
			ListToShow.deleteNode(0);
		};
		cout << "\t\033[1;34m-----------------------------\033[0m\n\n";
	}
};

void ResetGame() {
	while (!PlayerList.isEmpty()) {
		PlayerList.deleteNode(0);
		numberPlayer--;
	};
	cout << "El juego ha terminado, se han reseteado los jugadores!\n";
}

bool ContinueOrNot(){
	int opContinue;
	bool exit = true;
	do {
		cout << "Desea volver a jugar?\n1.Si\n2.No\n";
		while (!(cin >> opContinue)) {
			cout << "\033[1;31mEntrada invalida!\033[0m\n";
			cin.clear();  /*Limpiar cualquier error de entrada*/
			cin.ignore(numeric_limits<streamsize>::max(), '\n');  /*Ignorar cualquier entrada no válida*/
			cout << "Ingrese nuevamente la opcion que desea realizar: ";
		}
		switch (opContinue) {
		case 1:
			ResetGame();
			return true;
			break;
		case 2:
			exit = false;
			break;
		default:
			cout << "Debe ingresar un numero de la lista de opciones.\n";
			break;
		}
	}while (exit);
	return false;
}

void PlayMenu() {
	int opPlayer;
	bool exit = true;
	cout << "Ingrese el numero para seleccionar una opcion.\n\n";
	do {
		cout << "\t\033[1;34m--------- MENU JUGADORES ---------\033[0m\n";
		cout << "\t1. Agregar Jugadores\n";
		cout << "\t2. Remover Jugadores\n";
		cout << "\t3. Mostrar Jugadores\n";
		cout << "\t4. Volver al Menu Principal\n" ;
		cout << "\t\033[1;34m----------------------------------\033[0m\n\n"; 
		while (!(cin >> opPlayer)) {
			cout << "\033[1;31mEntrada invalida!\033[0m\n";
			cin.clear();  /*Limpiar cualquier error de entrada*/
			cin.ignore(numeric_limits<streamsize>::max(), '\n');  /*Ignorar cualquier entrada no válida*/
			cout << "Ingrese nuevamente la opcion que desea realizar: ";
		}
		switch (opPlayer) {
		case 1:
			AddPlayer();
			break;
		case 2:
			RemovePlayer();
			break;
		case 3:
				ShowPlayers();
			break;
		case 4:
			if (numberPlayer < 2){
				cout << "Debe existir al menos dos jugadores para continuar!\n";
			}
			else{
				cout << "Volviendo al menu principal...\n";
				exit = false;
			}
			break;
		default:
			cout << "Debe ingresar un numero de la lista de opciones.\n";
			break;
		}
	} while (exit);
};

void PrincipalMenu() {
		int opPrincipal;
		bool exit = true;
		cout << "\tBienvenido al juego Serpientes y Escaleras.\n\tIngrese el numero para seleccionar una opcion.\n\n";
		do {
			cout << "\n\t\033[1;34m----- SERPIENTES Y ESCALERAS -----\033[0m\n";
			cout << "\t1. Ingresar Jugadores\n";
			cout << "\t2. Jugar\n";
			cout << "\t3. Salir\n";
			cout << "\t\033[1;34m----------------------------------\033[0m\n";
			while (!(cin >> opPrincipal)) {
				cout << "\033[1;31mEntrada invalida!\033[0m";
				cin.clear(); 
				cin.ignore(numeric_limits<streamsize>::max(), '\n');  
				cout << "Ingrese nuevamente la opcion que desea realizar: ";
			}
			switch (opPrincipal) {
			case 1:
				PlayMenu();
				break;
			case 2:
				if (PlayerList.isEmpty()) {
					cout << "Lista de jugadores vacia!\n";
				}
				else {
					play.PlayGame(PlayerList);
					exit = ContinueOrNot();
				}
				break;
			case 3:
				cout << "Gracias por jugar!\033[0m\n";
				exit = false;
				break;
			default:
				cout << "Debe ingresar un numero de la lista de opciones.\n";
				break;
			}
		} while (exit);
};

int main(){
	cout << "\t\033[5;32mSERPIENTES\033[0m Y \033[5;33mESCALERAS\n\n\033[0m";
	PrincipalMenu();
}