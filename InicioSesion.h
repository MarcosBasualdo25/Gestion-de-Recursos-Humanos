#pragma once

#include <iostream>
#include <string>
#include "gotoxy.h"
#include <limits>
#include <conio.h>

using namespace std;
//Funcion para convertir una frase a minuscula o mayuscula
void lower(string &frase){
	for (char &c : frase) {
        c = tolower(c); 
    }
}

void upper(string &frase){
    for (char &c : frase) {
        c = toupper(c);  
    }
}

extern int obtenerAnchoConsola();

struct Usuario {
    string user;
    string clave;
    string rol;
};

struct Nodo {
    Usuario dato;
    Nodo *siguiente;
};

Nodo *ListaUsers = NULL;

//Lista simplemente enlazada (insercion de elementos al final)
void crearUsuario(Nodo *&ListaUsers, string u, string c, string r) {
    Nodo *nuevo_nodo = new Nodo();
    nuevo_nodo->dato.user = u;
    nuevo_nodo->dato.clave = c;
    nuevo_nodo->dato.rol = r;
    nuevo_nodo->siguiente = NULL;
    if (ListaUsers == NULL) {
        ListaUsers = nuevo_nodo;
    } else {
        Nodo *aux = ListaUsers;
        while (aux->siguiente != NULL) {
            aux = aux->siguiente;
        }
        aux->siguiente = nuevo_nodo;
    }
}

void mostrarUsuarios(Nodo *&ListaUsers) {
    Nodo *aux = ListaUsers;
    while (aux != NULL) {
        cout << aux->dato.user << endl;
        cout << aux->dato.clave << endl;
        cout << aux->dato.rol << endl;
        cout << "-------------" << endl;
        aux = aux->siguiente;
    }
}

void fondoInicioSesion(){
    color(127);
    for(int i=1; i<19; i++){
        gotoxy(55, i);
        cout<<"                                      ";
    }  
    color(7);
}

bool LoginUser = false;

void pantallaInicioSesion(Nodo *&ListaUsers) {
    while (!LoginUser) {
        system("cls");
        int anchoConsola = obtenerAnchoConsola();
        int x = anchoConsola / 2 - 20;
        int mensajeY = 16;
        fondoInicioSesion();
        color(112); //Color del inicio de sesion
        //cambiamos el color del fondo y texto
        //system("color F0");
        string rol;
        string usuario;
        string clave;
        gotoxy(x-5, 1);
        cout<<"######################################";
        gotoxy(x+5, 2);
        cout <<"Inicio de Sesion";
        gotoxy(x-5, 3);
        cout<<"--------------------------------------"; 
        gotoxy(x, 4);
        cout << "[1] Administrador";

        gotoxy(x, 5);
        cout << "[2] Empleado";

        int opcionRol = 0;
        bool entradaValida = false;

        do {
            gotoxy(x, 7);
            cout << "Seleccione su rol (1 o 2): ";
            gotoxy(x + 28, 7);
            cin >> opcionRol;
            if (opcionRol == 1) {
                rol = "ADMINISTRADOR";
                entradaValida = true;
            } else if (opcionRol == 2) {
                rol = "EMPLEADO";
                entradaValida = true;
            } else {
                gotoxy(x, mensajeY);
                cout << "Opción no válida. Intente de nuevo.";
                entradaValida = false;
            }
        } while (!entradaValida);

        gotoxy(x, 9);
        cout << "Ingrese su nombre de usuario: ";
        gotoxy(x, 11);
        cin >> usuario;

        gotoxy(x, 13);
        cout << "Ingrese su clave: ";
        gotoxy(x, 15);
        cin >> clave;

        Nodo *aux = ListaUsers;
        while (aux != NULL) {
            if ((aux->dato.user == usuario) && (aux->dato.clave == clave) && (aux->dato.rol == rol)) {
                LoginUser = true;
            }
            aux = aux->siguiente;
        }

        gotoxy(x, 17);
        if (LoginUser) {
            color(114);
            cout << "Ingreso al sistema con exito!" << endl;
            color(7);
        } else {
            color(116);
            cout << "Ingreso denegado" << endl;
            color(7);
        }
        color(7); //volver a la normalidad el color del inicio de sesion
        getch();
    }
}
