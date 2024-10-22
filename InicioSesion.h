#pragma once

#include <iostream>
#include <string>
#include "gotoxy.h"
#include <limits>
#include <conio.h>
#define up 72
#define down 80
#define enter 13
#ifndef INICIOSESION_H
#define INICIOSESION_H
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

//Menu interactivo propio para el INICIO DE SESION
int menuInicioSesion(string titulo, string opciones[], int n){
    int opcion = 1;
    int tecla;
    bool repite = true;
    int longitud = titulo.length();
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 20; 
    do{
        system("cls");
        // CABECERA
        gotoxy(40, 1);
        cout<<" _____ _____    _____ _____ _____ _____ _____ _____ _____ _____ _____"<<endl;
        gotoxy(40, 2);
        cout<<"|   __|     |  |_   _| __  |  _  |   | |   __|  _  |     | __  |_   _|"<<endl;
        gotoxy(40, 3);
        cout<<"|__   | | | |    | | |    -|     | | | |__   |   __|  |  |    -| | |"<<endl;  
        gotoxy(40, 4);
        cout<<"|_____|_|_|_|    |_| |__|__|__|__|_|___|_____|__|  |_____|__|__| |_|"<<endl;

        gotoxy(x-5, 6);
        cout<<"--------------------------------------";
        gotoxy(x-5, 7);
        cout<<"|";
        gotoxy(x+32, 7);
        cout<<"|";
        gotoxy(x+5, 7);
        cout <<"Inicio de Sesion";
        gotoxy(x-5, 8);
        cout<<"--------------------------------------"; 
        
        gotoxy(x-5,8+opcion); cout<<"➤";
        for(int i=0;i<n;i++){
            gotoxy(x,9+i); cout<<opciones[i];
        }
        do{
            tecla = getch();
        }while(tecla != up && tecla!= down && tecla != enter);

        switch(tecla){
            case up:{
                opcion--;
                if(opcion < 1){
                    opcion = n;
                }
                break;
            }
            case down:{
                opcion++;
                if(opcion > n){
                    opcion = 1;
                }
                break;
            }
            case enter:{
                repite=false;
                break;
            }
        }

    }while(repite);
    return opcion;
}

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

bool LoginUser = false;

void pantallaInicioSesion(Nodo *&ListaUsers) {
    ocultarCursor();
    while (!LoginUser) {
        system("cls");
        int anchoConsola = obtenerAnchoConsola();
        int x = anchoConsola / 2 - 20;
        int mensajeY = 16;
        system("color 70"); // con esto cambio tanto el FONDO de la CONSOLA como el color del texto...

        string rol;
        string usuario;
        string clave;

        int opcionRol;
        string opciones[] = {"[1] ADMINISTRADOR", "[2] EMPLEADO"};
        opcionRol = menuInicioSesion(" ", opciones, 2);
        
        if (opcionRol == 1) {
            rol = "ADMINISTRADOR";
        } 
        else{
            rol = "EMPLEADO";
        }

        mostrarCursor();
        gotoxy(x, 12);
        cout << "Ingrese su nombre de usuario: ";
        gotoxy(x, 14);
        cin >> usuario;

        gotoxy(x, 16);
        cout << "Ingrese su clave: ";
        gotoxy(x, 18);
        cin >> clave;

        Nodo *aux = ListaUsers;
        while (aux != NULL) {
            if ((aux->dato.user == usuario) && (aux->dato.clave == clave) && (aux->dato.rol == rol)) {
                LoginUser = true;
            }
            aux = aux->siguiente;
        }

        gotoxy(x, 20);
        if (LoginUser) {
            color(114);
            cout << "Ingreso al sistema con exito!" << endl;
            color(7);
        } else {
            color(116);
            cout << "Ingreso denegado" << endl;
            color(7);
        }
        getch();
    }
}

#endif