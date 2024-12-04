
#pragma once

#include <iostream>
#include <string>
#include "gotoxy.h"
#include <limits> 
#include <windows.h> 
#include "InicioSesion.h"
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

// Estructuras de Datos
struct Evaluacion {
    string comentario;
    int calificacion;
    Evaluacion* siguiente;
};

struct PilaEvaluaciones {
    Evaluacion* cima;
};

struct RegistroAsistencia {
    string fecha;
    string horaEntrada;
    string horaSalida;
    string estado;
    RegistroAsistencia* siguiente; 
};

struct PilaAsistencias {
    RegistroAsistencia* cima;
};

// Estructura de una solicitud
struct Solicitud {
    int IDsolicitud;           
    string Razon;               
    string FechaSolicitud;     
    string Descripcion;         
    string Estado;              
    string FechaResolucion;     
    string ComentarioAdmin;
    int Prioridad;
    int idEmpleado;      
    Solicitud* siguiente;     
};

struct ColaSolicitudes {
    Solicitud* cabeza;  
    Solicitud* cola;   
};

struct Empleado {
    int idEmpleado;
    string nombre;
    string apellido;
    string contrasena;
    string puesto;
    Empleado* anterior;
    Empleado* siguiente;
    PilaEvaluaciones* pilaEvaluaciones; 
    PilaAsistencias* pilaAsistencias;
};

// Declaración de funciones
Empleado* crearEmpleado();
void agregarEmpleado(Empleado*& head, Empleado* nuevoEmpleado);
void mostrarEmpleados(Empleado* head);
void actualizarEmpleado(Empleado* head, int id);
void eliminarEmpleado(Empleado*& head, int id);
int mostrarMenuGestionEmpleados(Empleado*& listaEmpleados);

Empleado* buscarEmpleado(Empleado* head, int id); 


inline int obtenerAnchoConsola() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    return columns;
}

inline int obtenerAltoConsola(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}


inline bool obtenerEntero(int& numero) {
    cin >> numero;
    if (cin.fail()) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        return false;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    return true;
}

// Implementación de funciones

Empleado* crearYAgregarEmpleado(Empleado*& head, Empleado*& tail) {
    system("cls");
    system("color 70"); // Fondo gris claro
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 40; // Centrar la interfaz

    // Título en azul
    color(113); // Texto azul sobre fondo gris claro
    gotoxy(x+6, 2);
    cout << "╔════════════════════════════════════════════════════════════════╗";
    gotoxy(x+6, 3);
    cout << "║                  AGREGAR NUEVO EMPLEADO                        ║";
    gotoxy(x+6, 4);
    cout << "╚════════════════════════════════════════════════════════════════╝";
    color(112); // Regresa a texto negro sobre fondo gris claro

    // Creación de un nuevo empleado
    Empleado* nuevoEmpleado = new Empleado();
    string nombre, apellido, contrasena, puesto;

    // Entrada: Nombre
    do {
        gotoxy(x, 6);
        cout << "╔════════════════════════════════════════════════════════════════════════════╗";
        gotoxy(x, 7);
        cout << "║ Ingrese el nombre del empleado:                                            ║";
        gotoxy(x, 8);
        cout << "╚════════════════════════════════════════════════════════════════════════════╝";
        gotoxy(x + 35, 7);
        getline(cin, nombre);
        if (nombre.empty()) {
            gotoxy(x + 4, 9);
            color(124); // Texto rojo para error
            cout << "Error: El nombre no puede estar vacío. Por favor, ingréselo.";
            color(112); // Regresa a texto negro
        }
    } while (nombre.empty());

    // Entrada: Apellido
    do {
        gotoxy(x, 9);
        cout << "╔════════════════════════════════════════════════════════════════════════════╗";
        gotoxy(x, 10);
        cout << "║ Ingrese el apellido del empleado:                                          ║";
        gotoxy(x, 11);
        cout << "╚════════════════════════════════════════════════════════════════════════════╝";
        gotoxy(x + 36, 10);
        getline(cin, apellido);
        if (apellido.empty()) {
            gotoxy(x + 4, 12);
            color(124); // Texto rojo para error
            cout << "Error: El apellido no puede estar vacío. Por favor, ingréselo.";
            color(112); // Regresa a texto negro
        }
    } while (apellido.empty());

    // Entrada: Contraseña
    do {
        gotoxy(x, 12);
        cout << "╔════════════════════════════════════════════════════════════════════════════╗";
        gotoxy(x, 13);
        cout << "║ Ingrese la contraseña del empleado:                                        ║";
        gotoxy(x, 14);
        cout << "╚════════════════════════════════════════════════════════════════════════════╝";
        gotoxy(x + 38, 13);
        getline(cin, contrasena);
        if (contrasena.empty()) {
            gotoxy(x + 4, 15);
            color(124); // Texto rojo para error
            cout << "Error: La contraseña no puede estar vacía. Por favor, ingrésela.";
            color(112); // Regresa a texto negro
        }
    } while (contrasena.empty());

    // Entrada: Puesto
    do {
        gotoxy(x, 15);
        cout << "╔════════════════════════════════════════════════════════════════════════════╗";
        gotoxy(x, 16);
        cout << "║ Ingrese el puesto del empleado:                                            ║";
        gotoxy(x, 17);
        cout << "╚════════════════════════════════════════════════════════════════════════════╝";
        gotoxy(x + 35, 16);
        getline(cin, puesto);
        if (puesto.empty()) {
            gotoxy(x + 4, 18);
            color(124); // Texto rojo para error
            cout << "Error: El puesto no puede estar vacío. Por favor, ingréselo.";
            color(112); // Regresa a texto negro
        }
    } while (puesto.empty());

    // Asignar valores al nuevo empleado
    nuevoEmpleado->nombre = nombre;
    nuevoEmpleado->apellido = apellido;
    nuevoEmpleado->contrasena = contrasena;
    nuevoEmpleado->puesto = puesto;
    nuevoEmpleado->siguiente = nullptr; // Será el último
    nuevoEmpleado->anterior = nullptr;
    nuevoEmpleado->pilaEvaluaciones = nullptr;
    nuevoEmpleado->pilaAsistencias = nullptr;

    // Asignación del ID y enlace a la lista
    if (head == nullptr) {
        // Si la lista está vacía, el nuevo empleado es tanto el head como el tail
        nuevoEmpleado->idEmpleado = 1;
        head = nuevoEmpleado;
        tail = nuevoEmpleado;
    } else {
        // Si ya hay empleados, agregar al final
        nuevoEmpleado->idEmpleado = tail->idEmpleado + 1; // El ID será uno más que el último empleado
        nuevoEmpleado->anterior = tail;                  // El anterior del nuevo empleado es el tail actual
        tail->siguiente = nuevoEmpleado;                 // El siguiente del tail actual es el nuevo empleado
        tail = nuevoEmpleado;                            // Actualizar el tail para que apunte al nuevo empleado
    }

    // Creación de la cuenta del usuario
    string user = nombre + "." + apellido;
    lower(user);
    crearUsuario(ListaUsers, user, nuevoEmpleado->contrasena, "EMPLEADO", nuevoEmpleado->idEmpleado);

    // Mensaje de confirmación en verde
    color(114); // Texto verde para confirmación
    gotoxy(x+11, 19);
    cout << "╔════════════════════════════════════════════════╗";
    gotoxy(x+11, 20);
    cout << "║   Empleado agregado exitosamente con ID " << setw(4) << nuevoEmpleado->idEmpleado << "   ║";
    gotoxy(x+11, 21);
    cout << "╚════════════════════════════════════════════════╝";
    color(112); // Regresa a texto negro

    getch();

    return nuevoEmpleado;
}



void mostrarEmpleados(Empleado* head, Empleado* tail) {
    system("cls");
    system("color 70");
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 40;  // Centrar tabla

    // Cuadro para el título
    gotoxy(x, 2);
    cout << "╔════════════════════════════════════════════════════════════════════════════╗";
    gotoxy(x, 3);
    cout << "║                             LISTA DE EMPLEADOS                             ║";
    gotoxy(x, 4);
    cout << "╚════════════════════════════════════════════════════════════════════════════╝";

    // Espaciado entre el título y la tabla
    gotoxy(x, 6);

    // Cuadro para la tabla
    cout << "╔═══════╦══════════════════════════════╦═══════════════════╦═════════════════╗";
    gotoxy(x, 7);
    cout << "║  ID   ║       Nombre Completo        ║      Puesto       ║   Contraseña    ║";
    gotoxy(x, 8);
    cout << "╠═══════╬══════════════════════════════╬═══════════════════╬═════════════════╣";

    if (head == nullptr) {
        gotoxy(x, 9);
        cout << "║                          No hay empleados registrados                      ║";
        gotoxy(x, 10);
        cout << "╚════════════════════════════════════════════════════════════════════════════╝";
    } else {
        Empleado* temp = head;
        int y = 9;

        // Iterar sobre la lista de empleados
        while (temp != nullptr) {
            gotoxy(x, y++);
            cout << "║ " << setw(5) << left << temp->idEmpleado
                 << " ║ " << setw(28) << centerText(temp->nombre + " " + temp->apellido, 28)
                 << " ║ " << setw(17) << centerText(temp->puesto, 17)
                 << " ║ " << setw(15) << centerText(temp->contrasena, 15) << " ║";

            temp = temp->siguiente;

            // Si hay más empleados, dibujar separador
            if (temp != nullptr) {
                gotoxy(x, y++);
                cout << "╠═══════╬══════════════════════════════╬═══════════════════╬═════════════════╣";
            }
        }

        // Dibujar el pie de la tabla
        gotoxy(x, y);
        cout << "╚════════════════════════════════════════════════════════════════════════════╝";
    }
}


void actualizarEmpleado(Empleado* head, Empleado* tail, int id) {
    system("cls");
    system("color 70"); // Fondo gris claro
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 40; // Centrar la interfaz

    Empleado* temp = head;

    // Buscar el empleado por ID
    while (temp != nullptr) {
        if (temp->idEmpleado == id) {
            // Título
            color(113); // Azul para el título
            gotoxy(x, 2);
            cout << "╔════════════════════════════════════════════════════════════════════════════╗";
            gotoxy(x, 3);
            cout << "║                         ACTUALIZAR EMPLEADO                                ║";
            gotoxy(x, 4);
            cout << "╚════════════════════════════════════════════════════════════════════════════╝";
            color(112); // Texto negro sobre fondo gris claro

            // Mostrar información del empleado seleccionado
            gotoxy(x, 6);
            cout << "Empleado seleccionado: " << temp->nombre << " " << temp->apellido;

            // Menú de opciones
            gotoxy(x+12, 8);
            cout << "╔═══════════════════════════════════════════════════╗";
            gotoxy(x+12, 9);
            cout << "║                 1. Nombre                         ║";
            gotoxy(x+12, 10);
            cout << "║                 2. Apellido                       ║";
            gotoxy(x+12, 11);
            cout << "║                 3. Contraseña                     ║";
            gotoxy(x+12, 12);
            cout << "║                 4. Puesto                         ║";
            gotoxy(x+12, 13);
            cout << "╚═══════════════════════════════════════════════════╝";

            // Validar la opción seleccionada
            int opcion;
            bool entradaValida = false;
            do {
                gotoxy(x, 15);
                cout << "╔════════════════════════════════════════════════════════════════════════════╗";
                gotoxy(x, 16);
                cout << "║ Ingrese su opción:                                                         ║";
                gotoxy(x, 17);
                cout << "╚════════════════════════════════════════════════════════════════════════════╝";
                gotoxy(x + 21, 16);
                entradaValida = obtenerEntero(opcion);
                if (!entradaValida || opcion < 1 || opcion > 4) {
                    gotoxy(x + 4, 18);
                    color(124); // Rojo para error
                    cout << "Error: Ingrese una opción válida (1-4).";
                    gotoxy(x + 20, 16);
                    cout << string(30, ' '); // Limpia la entrada
                    color(112); // Regresa al color estándar
                }
            } while (!entradaValida || opcion < 1 || opcion > 4);

            // Validar y actualizar el campo seleccionado
            string nuevoValor;
            do {
                gotoxy(x, 18);
                cout << "╔════════════════════════════════════════════════════════════════════════════╗";
                switch (opcion) {
                    case 1: // Actualizar nombre
                        gotoxy(x, 19);
                        cout << "║ Ingrese el nuevo nombre:                                                   ║";
                        break;
                    case 2: // Actualizar apellido
                        gotoxy(x, 19);
                        cout << "║ Ingrese el nuevo apellido:                                                 ║";
                        break;
                    case 3: // Actualizar contraseña
                        gotoxy(x, 19);
                        cout << "║ Ingrese la nueva contraseña:                                               ║";
                        break;
                    case 4: // Actualizar puesto
                        gotoxy(x, 19);
                        cout << "║ Ingrese el nuevo puesto:                                                   ║";
                        break;
                }
                gotoxy(x, 20);
                cout << "╚════════════════════════════════════════════════════════════════════════════╝";
                gotoxy(x + 30, 19);
                getline(cin, nuevoValor);
                if (nuevoValor.empty()) {
                    gotoxy(x + 4, 21);
                    color(124); // Rojo para error
                    cout << "Error: Este campo no puede estar vacío.";
                    color(112);
                }
            } while (nuevoValor.empty());

            // Actualizar el atributo correspondiente
            switch (opcion) {
                case 1:
                    temp->nombre = nuevoValor;
                    break;
                case 2:
                    temp->apellido = nuevoValor;
                    break;
                case 3:
                    temp->contrasena = nuevoValor;
                    break;
                case 4:
                    temp->puesto = nuevoValor;
                    break;
            }

            // Actualizar usuario (nombre de usuario y clave)
            string new_username = temp->nombre + "." + temp->apellido;
            lower(new_username);
            string new_clave = temp->contrasena;
            actualizarUsuario(ListaUsers, id, new_username, new_clave);

            // Mensaje de confirmación
            color(114); // Verde para confirmación
            gotoxy(x+14, 22);
            cout << "╔════════════════════════════════════════════════╗";
            gotoxy(x+14, 23);
            cout << "║     ¡Empleado actualizado exitosamente!        ║";
            gotoxy(x+14, 24);
            cout << "╚════════════════════════════════════════════════╝";
            color(112); // Regresa al color estándar

            getch();
            return;
        }
        temp = temp->siguiente;
    }

    // Si no se encuentra el empleado
    color(124); // Rojo para mensaje de error
    gotoxy(x, 6);
    cout << "Error: Empleado con ID " << id << " no encontrado.";
    color(112);
    getch();
}




void eliminarEmpleado(Empleado*& head, Empleado*& tail, int id) {
    system("cls");
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 30;

    if (head == nullptr) {
        gotoxy(x, 2);
        cout << "Lista vacía, no se puede eliminar.\n";
        system("pause");
        return;
    }

    // Caso especial: Eliminar el primer empleado (head)
    if (head->idEmpleado == id) {
        Empleado* temp = head;

        // Actualizar el head al siguiente nodo
        head = head->siguiente;
        if (head != nullptr) {
            head->anterior = nullptr;  // El nuevo head no debe tener anterior
        } else {
            tail = nullptr;  // Si la lista se vacía, tail también debe ser nullptr
        }

        // Liberar las pilas asociadas al empleado
        if (temp->pilaEvaluaciones != nullptr) {
            Evaluacion* evalTemp;
            while (temp->pilaEvaluaciones->cima != nullptr) {
                evalTemp = temp->pilaEvaluaciones->cima;
                temp->pilaEvaluaciones->cima = temp->pilaEvaluaciones->cima->siguiente;
                delete evalTemp;
            }
            delete temp->pilaEvaluaciones;
        }

        if (temp->pilaAsistencias != nullptr) {
            RegistroAsistencia* asisTemp;
            while (temp->pilaAsistencias->cima != nullptr) {
                asisTemp = temp->pilaAsistencias->cima;
                temp->pilaAsistencias->cima = temp->pilaAsistencias->cima->siguiente;
                delete asisTemp;
            }
            delete temp->pilaAsistencias;
        }

        delete temp;
        gotoxy(x, 2);
        cout << "Empleado eliminado con éxito.\n";
        getch();
        return;
    }

    // Caso general: Eliminar en el medio o al final de la lista
    Empleado* actual = head;

    while (actual != nullptr && actual->idEmpleado != id) {
        actual = actual->siguiente;
    }

    // Si no se encontró el empleado
    if (actual == nullptr) {
        gotoxy(x, 2);
        cout << "Empleado con ID " << id << " no encontrado.\n";
        system("pause");
        return;
    }

    // Si el empleado a eliminar está en el medio o al final
    if (actual->anterior != nullptr) {
        actual->anterior->siguiente = actual->siguiente;  // Saltar al nodo siguiente
    }
    if (actual->siguiente != nullptr) {
        actual->siguiente->anterior = actual->anterior;  // Saltar al nodo anterior
    } else {
        // Si no tiene siguiente, es el último nodo (actualizar tail)
        tail = actual->anterior;
    }

    // Liberar las pilas asociadas al empleado
    if (actual->pilaEvaluaciones != nullptr) {
        Evaluacion* evalTemp;
        while (actual->pilaEvaluaciones->cima != nullptr) {
            evalTemp = actual->pilaEvaluaciones->cima;
            actual->pilaEvaluaciones->cima = actual->pilaEvaluaciones->cima->siguiente;
            delete evalTemp;
        }
        delete actual->pilaEvaluaciones;
    }

    if (actual->pilaAsistencias != nullptr) {
        RegistroAsistencia* asisTemp;
        while (actual->pilaAsistencias->cima != nullptr) {
            asisTemp = actual->pilaAsistencias->cima;
            actual->pilaAsistencias->cima = actual->pilaAsistencias->cima->siguiente;
            delete asisTemp;
        }
        delete actual->pilaAsistencias;
    }

    delete actual;
    gotoxy(x, 2);
    cout << "Empleado eliminado con éxito.\n";
    system("pause");
}


Empleado* buscarEmpleado(Empleado* head, int id) {
    Empleado* temp = head;
    while (temp != nullptr) {
        if (temp->idEmpleado == id) {
            return temp;
        }
        temp = temp->siguiente;
    }
    return nullptr;
}