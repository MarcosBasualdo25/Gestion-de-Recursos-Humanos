
#pragma once

#include <iostream>
#include <string>
#include "gotoxy.h"
#include <limits> // Para std::numeric_limits
#include <windows.h> // Para SetConsoleOutputCP

using namespace std;

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
    RegistroAsistencia* siguiente; // Puntero al siguiente nodo (para la pila)
};

struct PilaAsistencias {
    RegistroAsistencia* cima;
};

struct Empleado {
    int idEmpleado;
    string nombre;
    string apellido;
    string contrasena;
    string puesto;
    Empleado* siguiente;
    PilaEvaluaciones* pilaEvaluaciones; // Puntero a la pila de evaluaciones del empleado
    PilaAsistencias* pilaAsistencias; // Puntero a la pila de evaluaciones del empleado
};

// Declaración de funciones
Empleado* crearEmpleado();
void agregarEmpleado(Empleado*& head, Empleado* nuevoEmpleado);
void mostrarEmpleados(Empleado* head);
void actualizarEmpleado(Empleado* head, int id);
void eliminarEmpleado(Empleado*& head, int id);
int mostrarMenuGestionEmpleados(Empleado*& listaEmpleados);

Empleado* buscarEmpleado(Empleado* head, int id); // Función para buscar empleado por ID

// Función para obtener el ancho de la consola
int obtenerAnchoConsola() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    return columns;
}

// Función para validar la entrada de un entero
bool obtenerEntero(int& numero) {
    cin >> numero;
    if (cin.fail()) {
        cin.clear(); // Limpia el estado de error
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descarta el resto de la línea
        return false;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descarta el resto de la línea
    return true;
}

// Implementación de funciones

Empleado* crearEmpleado() {
    system("cls");
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 20; // Posición X centrada

    gotoxy(x, 2);
    cout << "--- Agregar Nuevo Empleado ---\n";

    Empleado* nuevoEmpleado = new Empleado();

    int idEmpleado;
    string nombre, apellido, contrasena, puesto;

    bool entradaValida = false;
    do {
        gotoxy(x, 4);
        cout << "Ingrese el ID del empleado: ";
        entradaValida = obtenerEntero(idEmpleado);
        if (!entradaValida) {
            gotoxy(x, 5);
            cout << "Entrada no aceptada. Por favor, ingrese un número entero.";
            gotoxy(x, 4);
            cout << string(50, ' '); // Limpia la línea
        }
    } while (!entradaValida);

    gotoxy(x, 5);
    cout << "Ingrese el nombre del empleado: ";
    getline(cin, nombre);
    gotoxy(x, 6);
    cout << "Ingrese el apellido del empleado: ";
    getline(cin, apellido);
    gotoxy(x, 7);
    cout << "Ingrese la contraseña del empleado: ";
    getline(cin, contrasena);
    gotoxy(x, 8);
    cout << "Ingrese el puesto del empleado: ";
    getline(cin, puesto);

    nuevoEmpleado->idEmpleado = idEmpleado;
    nuevoEmpleado->nombre = nombre;
    nuevoEmpleado->apellido = apellido;
    nuevoEmpleado->contrasena = contrasena;
    nuevoEmpleado->puesto = puesto;
    nuevoEmpleado->siguiente = nullptr;
    nuevoEmpleado->pilaEvaluaciones = nullptr; // Inicializamos la pila de evaluaciones

    gotoxy(x, 10);
    cout << "Empleado agregado exitosamente.\n";
    system("pause");
    return nuevoEmpleado;
}

void agregarEmpleado(Empleado*& head, Empleado* nuevoEmpleado) {
    if (head == nullptr) {
        head = nuevoEmpleado;
    } else {
        Empleado* temp = head;
        while (temp->siguiente != nullptr) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevoEmpleado;
    }
}

void mostrarEmpleados(Empleado* head) {
    system("cls");
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 20; // Posición X centrada

    gotoxy(x, 2);
    cout << "--- Lista de Empleados ---\n";

    if (head == nullptr) {
        gotoxy(x, 4);
        cout << "No hay empleados en la lista.\n";
    } else {
        Empleado* temp = head;
        int y = 4;
        while (temp != nullptr) {
            gotoxy(x, y++);
            cout << "ID: " << temp->idEmpleado << ", Nombre: " << temp->nombre << " " << temp->apellido
                 << ", Puesto: " << temp->puesto;
            temp = temp->siguiente;
        }
    }
    cout << "\n";
    system("pause");
}

void actualizarEmpleado(Empleado* head, int id) {
    system("cls");
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 20; // Posición X centrada

    Empleado* temp = head;
    while (temp != nullptr) {
        if (temp->idEmpleado == id) {
            int opcion;
            gotoxy(x, 2);
            cout << "--- Actualizar Empleado ---\n";
            gotoxy(x, 4);
            cout << "Empleado seleccionado: " << temp->nombre << " " << temp->apellido << "\n";

            gotoxy(x, 6);
            cout << "Seleccione el atributo a modificar:\n";
            gotoxy(x, 7);
            cout << "1. Nombre\n";
            gotoxy(x, 8);
            cout << "2. Apellido\n";
            gotoxy(x, 9);
            cout << "3. Contraseña\n";
            gotoxy(x, 10);
            cout << "4. Puesto\n";

            bool entradaValida = false;
            do {
                gotoxy(x, 12);
                cout << "Ingrese su opción: ";
                entradaValida = obtenerEntero(opcion);
                if (!entradaValida || opcion < 1 || opcion > 4) {
                    gotoxy(x, 13);
                    cout << "Entrada no aceptada. Por favor, ingrese una opción válida.";
                    gotoxy(x, 12);
                    cout << string(50, ' '); // Limpia la línea
                }
            } while (!entradaValida || opcion < 1 || opcion > 4);

            string nuevoValor;

            switch(opcion) {
                case 1:
                    gotoxy(x, 14);
                    cout << "Ingrese el nuevo nombre: ";
                    cin.ignore();
                    getline(cin, nuevoValor);
                    temp->nombre = nuevoValor;
                    gotoxy(x, 16);
                    cout << "Nombre actualizado con éxito.\n";
                    break;
                case 2:
                    gotoxy(x, 14);
                    cout << "Ingrese el nuevo apellido: ";
                    cin.ignore();
                    getline(cin, nuevoValor);
                    temp->apellido = nuevoValor;
                    gotoxy(x, 16);
                    cout << "Apellido actualizado con éxito.\n";
                    break;
                case 3:
                    gotoxy(x, 14);
                    cout << "Ingrese la nueva contraseña: ";
                    cin.ignore();
                    getline(cin, nuevoValor);
                    temp->contrasena = nuevoValor;
                    gotoxy(x, 16);
                    cout << "Contraseña actualizada con éxito.\n";
                    break;
                case 4:
                    gotoxy(x, 14);
                    cout << "Ingrese el nuevo puesto: ";
                    cin.ignore();
                    getline(cin, nuevoValor);
                    temp->puesto = nuevoValor;
                    gotoxy(x, 16);
                    cout << "Puesto actualizado con éxito.\n";
                    break;
                default:
                    gotoxy(x, 14);
                    cout << "Opción no válida. No se ha realizado ninguna modificación.\n";
                    break;
            }
            system("pause");
            return;
        }
        temp = temp->siguiente;
    }
    gotoxy(x, 2);
    cout << "Empleado con ID " << id << " no encontrado.\n";
    system("pause");
}

void eliminarEmpleado(Empleado*& head, int id) {
    system("cls");
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 20; // Posición X centrada

    if (head == nullptr) {
        gotoxy(x, 2);
        cout << "Lista vacía, no se puede eliminar.\n";
        system("pause");
        return;
    }

    if (head->idEmpleado == id) {
        Empleado* temp = head;
        head = head->siguiente;
        delete temp;
        gotoxy(x, 2);
        cout << "Empleado eliminado con éxito.\n";
        system("pause");
        return;
    }

    Empleado* actual = head;
    Empleado* anterior = nullptr;

    while (actual != nullptr && actual->idEmpleado != id) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == nullptr) {
        gotoxy(x, 2);
        cout << "Empleado con ID " << id << " no encontrado.\n";
        system("pause");
        return;
    }

    anterior->siguiente = actual->siguiente;
    delete actual;
    gotoxy(x, 2);
    cout << "Empleado eliminado con éxito.\n";
    system("pause");
}

int mostrarMenuGestionEmpleados(Empleado*& listaEmpleados) {
    system("cls");
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 20; // Posición X centrada
    int opcion;

    gotoxy(x, 2);
    cout << "--- Menú de Gestión de Empleados ---\n";
    gotoxy(x, 4);
    cout << "1. Agregar empleado\n";
    gotoxy(x, 5);
    cout << "2. Mostrar empleados\n";
    gotoxy(x, 6);
    cout << "3. Actualizar empleado\n";
    gotoxy(x, 7);
    cout << "4. Eliminar empleado\n";
    gotoxy(x, 8);
    cout << "5. Volver al menú principal\n";

    bool entradaValida = false;
    do {
        gotoxy(x, 10);
        cout << "Ingrese una opción: ";
        entradaValida = obtenerEntero(opcion);
        if (!entradaValida || opcion < 1 || opcion > 5) {
            gotoxy(x, 11);
            cout << "Entrada no aceptada. Por favor, ingrese una opción válida.";
            gotoxy(x, 10);
            cout << string(50, ' '); // Limpia la línea
        }
    } while (!entradaValida || opcion < 1 || opcion > 5);

    switch (opcion) {
        case 1: {
            Empleado* nuevoEmpleado = crearEmpleado();
            agregarEmpleado(listaEmpleados, nuevoEmpleado);
            break;
        }
        case 2:
            mostrarEmpleados(listaEmpleados);
            break;
        case 3: {
            int id;
            bool entradaValida = false;
            do {
                gotoxy(x, 12);
                cout << "Ingrese el ID del empleado a actualizar: ";
                entradaValida = obtenerEntero(id);
                if (!entradaValida) {
                    gotoxy(x, 13);
                    cout << "Entrada no aceptada. Por favor, ingrese un número entero.";
                    gotoxy(x, 12);
                    cout << string(50, ' '); // Limpia la línea
                }
            } while (!entradaValida);
            actualizarEmpleado(listaEmpleados, id);
            break;
        }
        case 4: {
            int id;
            bool entradaValida = false;
            do {
                gotoxy(x, 12);
                cout << "Ingrese el ID del empleado a eliminar: ";
                entradaValida = obtenerEntero(id);
                if (!entradaValida) {
                    gotoxy(x, 13);
                    cout << "Entrada no aceptada. Por favor, ingrese un número entero.";
                    gotoxy(x, 12);
                    cout << string(50, ' '); // Limpia la línea
                }
            } while (!entradaValida);
            eliminarEmpleado(listaEmpleados, id);
            break;
        }
        case 5:
            return 0; // Volver al menú principal
        default:
            gotoxy(x, 12);
            cout << "Opción inválida. Intente de nuevo.\n";
            system("pause");
            break;
    }
    return 1; // Continuar en el menú de gestión de empleados
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
