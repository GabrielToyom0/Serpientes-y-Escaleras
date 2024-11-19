#pragma once
#include <iostream>
#include <stdexcept>

using namespace std;
template <typename T>
class CircularLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(T data) : data(data), next(nullptr) {}
    };

    Node* head;
    Node* tail;

public: 
    CircularLinkedList();
    void addNode(T data) ;
    void deleteNode(int position);
    bool isEmpty() const;
    T& getHeadData();
    T& getNextTurn();
    ~CircularLinkedList();
};

/*Constructor de la lista circular*/
template <typename T>
CircularLinkedList<T>::CircularLinkedList() : head(nullptr), tail(nullptr) {}

/*Método que añade un jugador a la lista circular*/
template <typename T>
void CircularLinkedList<T>::addNode(T data) {
    Node* newPlayer = new Node(data);
    if (isEmpty()) {
        head = newPlayer;
        tail = newPlayer;
        newPlayer->next = head;
    }
    else {
        tail->next = newPlayer;
        tail = newPlayer;
        tail->next = head;
    }
}

/*Método que elimina un jugador de la lista circular*/
template <typename T>
void CircularLinkedList<T>::deleteNode(int position) {
    if (isEmpty() || position < 0) { throw out_of_range("Lista de Jugadores vacia!.\n"); }

    Node* currentPlayer = head;
    Node* prevPlayer = nullptr;

    if (position == 0) {
        if (head == tail) {
            head = nullptr;
            tail = nullptr;
            return;
        }
        tail->next = head->next;
        currentPlayer = head;
        head = head->next;
        currentPlayer = nullptr;
        return;
    }

    int count = 0;
    do {
        if (count == position) {
            prevPlayer->next = currentPlayer->next;
            if (currentPlayer == tail) {
                tail = prevPlayer;
            }
            currentPlayer = nullptr;
            return;
        }
        prevPlayer = currentPlayer;
        currentPlayer = currentPlayer->next;
        count++;
    } while (currentPlayer != head);
}

/*Método que determina si la lista esta vacia o no*/
template <typename T>
bool CircularLinkedList<T>::isEmpty() const {
    return head == nullptr;
}


/*Funcion que retorna al primer jugador, util para mostrar cada jugador con nodos temporales*/
template <typename T>
T& CircularLinkedList<T>::getHeadData() {
    return head->data;
}

/*Funcion que gestiona los turnos de los jugadores cambiando constantemente el head*/
template <typename T>
T& CircularLinkedList<T>::getNextTurn() {
    if (isEmpty()) {
        throw out_of_range("Lista de Jugadores vacia!.\n");
    }
    T turnPlayer = head->data;
    head = head->next;
    tail = tail->next;
    return turnPlayer;
}

/*Destructor, pendiente*/
template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
    if (!isEmpty()) {
        Node* actual = head;
        do {
            Node* temp = actual;
            actual = actual->next;
            delete temp;
        } while (actual != head);
    }
}