#pragma once
#ifndef LISTA_H
#define LISTA_H

#include <functional>
#include <conio.h>
#include <iostream>
#include <iterator>

using namespace std;
template <class T>
struct Nodo {
    T element;
    Nodo<T>* next;
    Nodo<T>* prev;
    Nodo(T c) { element = c; next = nullptr; prev = nullptr; }
};
template <class T>
class Iterador {
private:
    Nodo<T>* current;

public:
    Iterador(Nodo<T>* nodo) : current(nodo) {}

    // Operadores de acceso y modificación
    T& operator*() const {
        return current->element;
    }

    Iterador<T>& operator++() {
        current = current->next;
        return *this;
    }

    Iterador<T>& operator--() {
        current = current->prev;
        return *this;
    }

    // Operadores de comparación
    bool operator==(const Iterador<T>& otro) const {
        return current == otro.current;
    }

    bool operator!=(const Iterador<T>& otro) const {
        return current != otro.current;
    }
};

template <class T>
class Lista
{
private:
    Nodo<T>* start;
    Nodo<T>* tail;
    size_t size;
public:
    Lista() {
        start = nullptr;
        tail = nullptr;
        size = 0;
    }
    Iterador<T> begin() const {
        return Iterador<T>(start);
    }
    size_t getSize() const { return this->size; }
    Iterador<T> end() const {
        return Iterador<T>(nullptr);
    }
    T& at(size_t posicion) const {                                                                          
        if (posicion < 0 || posicion > size) {                                              //3 + MAX INTERNO-> 3 + 1 = 4
            throw std::out_of_range("Índice fuera de rango");                    //1
        }
        Nodo<T>* current = start;                                                             //1
        size_t currentPosicion = 0;                                                            //1

        while (currentPosicion < posicion) {                                            //1+ MAX INTERNA->1+2=3
            current = current->next;                                                           //2
            currentPosicion++;                                                                   //1
        }                                                                                                   //TOTAL = 3+1+1+4= 9

        return current->element;
    }
    Iterador<T> find(const T& elemento) const {
        Nodo<T>* current = start;

        while (current != nullptr) {//recorre hasta el final 
            if (current->element == elemento) {
                return Iterador<T>(current);//en caso lo encuentr lo devuelve
            }
            current = current->next;//sino sigue con el siguiente
        }
        //sino encuentra retorna nulo
        return end();
    }

    Iterador<T> find(T valorBuscado, bool(*func)(T&, T&)) {                            //COMPLEJIDAD ALGORITMICA
        Nodo<T>* current = start;                                                                           //1
        
        while (current != nullptr) {                                                                        // 1 + MAX interno - > 1 + 4 = 5
            if(func(current->element, valorBuscado))                                            //2 + Max -> 2 + 2 = 4 
                return Iterador<T>(current);                                                            //1
            current = current->next;//sino sigue con el siguiente                           //2
        }                                                                                                           //TOTAL 1 + 5 = 6
        return end();
    }

    void push_frontV1(T e) {//Sin depurar
        if (start == nullptr) {
            Nodo<T>* _new = new Nodo<T>(e);
            start = _new;
            ++size;
        }
        else if (start->next == nullptr) {
            Nodo<T>* _new = new Nodo<T>(e);
            _new->next = start;
            start = _new;
            ++size;
        }
        else {
            Nodo<T>* _new = new Nodo<T>(e);
            _new->next = start;
            start = _new;
        }
        ++size;
    }
    void push_front(T e) {
        Nodo<T>* _new = new Nodo<T>(e);     //2
        if (start != nullptr) {                                 //1 + maxInterna
            _new->next = start;                             //2
        }
        start = _new;                                           //1
        ++size;                                                   //1
    }
    void bubbleSort_V2(function<bool(Nodo<T>*, Nodo<T>*)> operador) {                 //COMPLEJIDAD ALGORITMICA DEL METODO
        //O(N^2) 
        bool intercambiado;                                                                                    //PORQUE HAY 2 FOR ANIDADOS
        do {
            Nodo<T>* ptr1 = start;
            intercambiado = false;
            while (ptr1->next != nullptr) {
                if (operador(ptr1, ptr1->next)) {
                    auto aux = ptr1->element;
                    ptr1->element = ptr1->next->element;
                    ptr1->next->element = aux;
                    intercambiado = true;
                }
                ptr1 = ptr1->next;
            }
        } while (intercambiado);
    }
    void push_inPos(T e, size_t posicion) {
        // Verifica si la posición es válida
        if (posicion < 1 || posicion > size + 1) {
            cout << "Posición inválida" << endl;
            return;
        }

        if (posicion == 1) {
            // Insertar en el inicio de la lista
            push_front(e);
        }
        else if (posicion == size + 1) {
            // Insertar al final de la lista
            push_back(e);
        }
        else {
            // Insertar en una posición intermedia
            Nodo<T>* _new = new Nodo<T>(e);

            Nodo<T>* current = start;
            size_t currentPosition = 1;

            while (currentPosition < posicion - 1) {
                current = current->next;
                currentPosition++;
            }

            // Ajustar los punteros para insertar el nuevo nodo en la posición deseada
            _new->next = current->next;
            _new->prev = current;
            current->next->prev = _new;
            current->next = _new;

            ++size;
        }
    }
    void pop_back() {
        if (start == nullptr) {
            cout << "La lista está vacía. No se puede eliminar ningún elemento." << endl;
            return;
        }

        if (start == tail) {
            // Solo hay un elemento en la lista
            delete start;
            start = nullptr;
            tail = nullptr;
        }
        else {
            Nodo<T>* previousTail = tail->prev;
            previousTail->next = nullptr;
            delete tail;
            tail = previousTail;
        }

        --size;
    }
    void pop_front() {
        if (start == nullptr) {
            cout << "La lista está vacía. No se puede eliminar ningún elemento." << endl;
            return;
        }

        if (start == tail) {
            // Solo hay un elemento en la lista
            delete start;
            start = nullptr;
            tail = nullptr;
        }
        else {
            Nodo<T>* newStart = start->next;
            newStart->prev = nullptr;
            delete start;
            start = newStart;
        }

        --size;
    }
    void remove(const T& elemento) {
        Nodo<T>* tmp = start;
        Nodo<T>* previo = nullptr;

        while (tmp != nullptr) {
            if (tmp->element == elemento) {
                //el nodo a eliminar es el primer nodo
                if (previo == nullptr) {
                    start = tmp->next;
                }
                //cuando no es el primero ni el ultimo
                else {
                    previo->next = tmp->next;
                    if (tmp->next == nullptr) {
                        tail = previo;
                    }
                }
                // el nodo a eliminar es el último nodo
                if (tmp == tail) {
                    tail = previo;
                }

                delete tmp;
                size--;
                return;
            }

            previo = tmp;
            tmp = tmp->next;
        }
    }
    void delete_inPos(size_t posicion) {
        // Verifica si la posición es válida
        if (posicion < 1 || posicion > size) {
            cout << "Posición inválida" << endl;
            return;
        }

        if (posicion == 1) {
            // Eliminar el elemento del inicio de la lista
            pop_front();
        }
        else if (posicion == size) {
            // Eliminar el elemento del final de la lista
            pop_back();
        }
        else {
            // Eliminar en una posición intermedia
            Nodo<T>* current = start;
            size_t currentPosition = 1;

            while (currentPosition < posicion) {
                current = current->next;
                currentPosition++;
            }

            // Ajustar los punteros para eliminar el nodo
            current->prev->next = current->next;
            current->next->prev = current->prev;

            // Liberar la memoria del nodo
            delete current;

            --size;
        }
    }
    void push_middle(T e) {
        Nodo<T>* _new = new Nodo<T>(e);

        if (start == nullptr) {//en caso 0

            start = _new;
            tail = _new;
            ++size;
            return;
        }
        size_t medio = (size + 1) / 2;//se calcula el medio de la lista 

        Nodo<T>* temp = start;
        size_t currentPosition = 1;

        while (currentPosition < medio) {//recorre la lista hasta estar en el medio
            temp = temp->next;
            currentPosition++;
        }

        //insertamos el elemento en el medio 
        _new->next = temp;
        _new->prev = temp->prev;
        temp->prev->next = _new;
        temp->prev = _new;

        ++size;
    }
    T buscador(function<bool(T)>buscador) {
        Nodo<T>* tmp = start;
        while (tmp != nullptr)
        {
            if (buscador(tmp->element)) return tmp->element;
            tmp = tmp->next;
        }
        cout << "Elemento no encontrado" << endl;
        return T{};
    }
    void print() {
        Nodo<T>* tmp = start;
        while (tmp != nullptr) {
            cout << tmp->element << "->";
            tmp = tmp->next;
        }
        cout << "nullptr";
    }

    void push_back(T e) {
        Nodo<T>* _new = new Nodo<T>(e);
        if (tail != nullptr) {
            tail->next = _new;
            _new->prev = tail;
        }
        else start = _new;

        tail = _new;
        ++size;
    }

};

#endif // DEBUG