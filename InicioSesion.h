#pragma once

#include <iostream>
#include <string>
#include "gotoxy.h"
#include <limits>
#include <conio.h>
#include <fstream>

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

Nodo *PilaUsers = NULL;

void crearUsuario(Nodo *&PilaUsers, string u, string c, string r) {
    Nodo *nuevo_nodo = new Nodo();
    nuevo_nodo->dato.user = u;
    nuevo_nodo->dato.clave = c;
    nuevo_nodo->dato.rol = r;
    nuevo_nodo->siguiente = NULL;
    if (PilaUsers == NULL) {
        PilaUsers = nuevo_nodo;
    } else {
        Nodo *aux = PilaUsers;
        while (aux->siguiente != NULL) {
            aux = aux->siguiente;
        }
        aux->siguiente = nuevo_nodo;
    }
}

void mostrarUsuarios(Nodo *&PilaUsers) {
    Nodo *aux = PilaUsers;
    while (aux != NULL) {
        cout << aux->dato.user << endl;
        cout << aux->dato.clave << endl;
        cout << aux->dato.rol << endl;
        cout << "-------------" << endl;
        aux = aux->siguiente;
    }
}

void actualizarUserUsuario(Nodo *&PilaUsers, const string& usuarioActual, const string& nuevoUsuario) {
    Nodo *aux = PilaUsers;

    while (aux != NULL) {
        if (aux->dato.user == usuarioActual) {  //Buscamos el usuario a modificar
            aux->dato.user = nuevoUsuario;  //Actualizamos el nombre de usuario
            cout << "Usuario actualizado correctamente." << endl;
            return;
        }
        aux = aux->siguiente;
    }

    cout << "Usuario no encontrado." << endl;
}
void actualizarClaveUsuario(Nodo *&PilaUsers, const string& usuarioActual, const string& nuevaClave) {
    Nodo *aux = PilaUsers;

    while (aux != NULL) {
        if (aux->dato.user == usuarioActual) {  // Buscamos el usuario a modificar
            aux->dato.clave = nuevaClave;  // Actualizamos la clave
            cout << "Usuario actualizado correctamente." << endl;
            return;
        }
        aux = aux->siguiente;
    }

    cout << "Usuario no encontrado." << endl;
}


//---- FUNCIONES PARA EL MANEJO DE ARCHIVOS ----
// Función para guardar los usuarios en el archivo "Usuarios.txt"
void guardarUsuariosEnArchivo(Nodo *PilaUsers, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        Nodo *aux = PilaUsers;
        while (aux != NULL) {
            archivo << aux->dato.user << " "
                    << aux->dato.clave << " "
                    << aux->dato.rol << endl;
            aux = aux->siguiente;
        }
        archivo.close();
        //cout << "Usuarios guardados en " << nombreArchivo << endl;
    } else {
        //cout << "Error al abrir el archivo " << nombreArchivo << endl;
    }
}

// Funcion para cargar los usuarios creados previamente
void cargarUsuariosDesdeArchivo(Nodo *&PilaUsers, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        string user, clave, rol;
        while (archivo >> user >> clave >> rol) {
            crearUsuario(PilaUsers, user, clave, rol);
        }
        archivo.close();
        //cout << "Usuarios cargados desde " << nombreArchivo << endl;
    } else {
        //cout << "Error al abrir el archivo " << nombreArchivo << endl;
    }
}

//Funcion que actualiza cambios en los usuarios (sobrescribe el txt)
void actualizarUsuarios(Nodo *PilaUsers) {
    ofstream archivo("Usuarios.txt", ios::trunc);  // Abrimos el archivo en modo trunc para sobrescribir
    if (archivo.is_open()) {
        Nodo *aux = PilaUsers;

        // Recorremos la pila y escribimos cada usuario en el archivo
        while (aux != NULL) {
            archivo << aux->dato.user << " " << aux->dato.clave << " " << aux->dato.rol << endl;
            aux = aux->siguiente;  // Pasamos al siguiente nodo
        }

        archivo.close();  // Cerramos el archivo
        //cout << "Pila guardada correctamente en el archivo." << endl;
    } else {
        //cout << "Error: No se pudo abrir el archivo." << endl;
    }
}



bool LoginUser = false;

void pantallaInicioSesion(Nodo *&PilaUsers) {

    cargarUsuariosDesdeArchivo(PilaUsers, "Usuarios.txt");

    while (!LoginUser) {
        system("cls");
        int anchoConsola = obtenerAnchoConsola();
        int x = anchoConsola / 2 - 20;
        int mensajeY = 16;

        string rol;
        string usuario;
        string clave;
        gotoxy(x, 1);
        cout<<"--------------------------";
        gotoxy(x+5, 2);
        cout <<"Inicio de Sesion";
        gotoxy(x, 3);
        cout<<"--------------------------"; 
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

        Nodo *aux = PilaUsers;
        while (aux != NULL) {
            if ((aux->dato.user == usuario) && (aux->dato.clave == clave) && (aux->dato.rol == rol)) {
                LoginUser = true;
            }
            aux = aux->siguiente;
        }

        gotoxy(x, 17);
        if (LoginUser) {
            color(2);
            cout << "Ingreso al sistema con exito!" << endl;
            color(7);
        } else {
            color(4);
            cout << "Ingreso denegado, datos no validos" << endl;
            color(7);
        }
        getch();
    }
}