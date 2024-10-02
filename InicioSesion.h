#pragma once

#include <iostream>
#include <string>
#include "GestionEmpleados.h"
#include "gotoxy.h"
#include <limits>

using namespace std;

struct Usuario {
    string user;
    string clave;
    string rol;
};

struct Nodo {
    Usuario dato;
    Nodo *siguiente;
};

void Usuarios(Nodo *&listaUsers, string u, string c, string r) {
    Nodo *nuevo_nodo = new Nodo();
    nuevo_nodo->dato.user = u;
    nuevo_nodo->dato.clave = c;
    nuevo_nodo->dato.rol = r;
    nuevo_nodo->siguiente = NULL;
    if (listaUsers == NULL) {
        listaUsers = nuevo_nodo;
    } else {
        Nodo *aux = listaUsers;
        while (aux->siguiente != NULL) {
            aux = aux->siguiente;
        }
        aux->siguiente = nuevo_nodo;
    }
}

void mostrarUsuarios(Nodo *&listaUsers) {
    Nodo *aux = listaUsers;
    while (aux != NULL) {
        cout << aux->dato.user << endl;
        cout << aux->dato.clave << endl;
        cout << aux->dato.rol << endl;
        cout << "-------------" << endl;
        aux = aux->siguiente;
    }
}

bool LoginUser = false;

void pantallaInicioSesion(Nodo *&ListaUsers) {
    while (!LoginUser) {
        int anchoConsola = obtenerAnchoConsola();
        int x = anchoConsola / 2 - 20;
        int mensajeY = 16;

        string rol;
        string usuario;
        string clave;

        gotoxy(x, 2);
        cout << "----- Inicio de Sesion -----";

        gotoxy(x, 4);
        cout << "[1] Administrador.";

        gotoxy(x, 5);
        cout << "[2] Empleado.";

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

        gotoxy(x, 10);
        cout << "Ingrese su nombre de usuario: ";
        gotoxy(x + 28, 10);
        cin >> usuario;

        gotoxy(x, 12);
        cout << "Ingrese su clave: ";
        gotoxy(x + 28, 12);
        cin >> clave;

        Nodo *aux = ListaUsers;
        while (aux != NULL) {
            if ((aux->dato.user == usuario) && (aux->dato.clave == clave) && (aux->dato.rol == rol)) {
                LoginUser = true;
            }
            aux = aux->siguiente;
        }

        gotoxy(x, mensajeY);
        if (LoginUser) {
            cout << "Ingreso al sistema con exito!" << endl;
        } else {
            cout << "Ingreso denegado, datos no validos" << endl;
        }
        gotoxy(x, mensajeY + 2);
        system("Pause");
        system("cls");
    }
}