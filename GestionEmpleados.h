
#pragma once

#include <iostream>
#include <string>
#include "gotoxy.h"
#include <limits> 
#include <windows.h> 
#include "InicioSesion.h"
#include <fstream>
#include <sstream>

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
    ColaSolicitudes* colaSolicitudes;
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
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 30; 

    gotoxy(x, 2);
    cout << "--- Agregar Nuevo Empleado ---\n";

    // Creación de un nuevo empleado
    Empleado* nuevoEmpleado = new Empleado();
    string nombre, apellido, contrasena, puesto;

    gotoxy(x, 4);
    cout << "Ingrese el nombre del empleado: ";
    getline(cin, nombre);
    gotoxy(x, 5);
    cout << "Ingrese el apellido del empleado: ";
    getline(cin, apellido);
    gotoxy(x, 6);
    cout << "Ingrese la contraseña del empleado: ";
    getline(cin, contrasena);
    gotoxy(x, 7);
    cout << "Ingrese el puesto del empleado: ";
    getline(cin, puesto);

    // Asignar valores al nuevo empleado
    nuevoEmpleado->nombre = nombre;
    nuevoEmpleado->apellido = apellido;
    nuevoEmpleado->contrasena = contrasena;
    nuevoEmpleado->puesto = puesto;
    nuevoEmpleado->siguiente = nullptr;  // Será el último
    nuevoEmpleado->anterior = nullptr;
    nuevoEmpleado->pilaEvaluaciones = nullptr;
    nuevoEmpleado->pilaAsistencias = nullptr;

    // Creación de la cuenta del usuario
    string user;
    lower(nombre);
    lower(apellido);
    user = nombre + "." + apellido;
    crearUsuario(PilaUsers, user, nuevoEmpleado->contrasena, "EMPLEADO");

    // Asignación del ID y enlace a la lista
    if (head == nullptr) {
        // Si la lista está vacía, el nuevo empleado es tanto el head como el tail
        nuevoEmpleado->idEmpleado = 1;
        head = nuevoEmpleado;
        tail = nuevoEmpleado;
    } else {
        // Si ya hay empleados, agregar al final
        nuevoEmpleado->idEmpleado = tail->idEmpleado + 1;  // El ID será uno más que el último empleado
        nuevoEmpleado->anterior = tail;  // El anterior del nuevo empleado es el tail actual
        tail->siguiente = nuevoEmpleado;  // El siguiente del tail actual es el nuevo empleado
        tail = nuevoEmpleado;  // Actualizar el tail para que apunte al nuevo empleado
    }

    // Mensaje de confirmación
    gotoxy(x, 9);
    color(2);
    cout << "Empleado agregado exitosamente con ID " << nuevoEmpleado->idEmpleado << ".\n";
    color(7);
    getch();

    return nuevoEmpleado;
}


void mostrarEmpleados(Empleado* head, Empleado* tail) {
    system("cls");  // Limpia la consola
    int anchoConsola = obtenerAnchoConsola();  // Obtiene el ancho de la consola
    int x = anchoConsola / 2 - 30;  // Centra el título en la consola

    gotoxy(x, 2);
    cout << "--- Lista de Empleados ---\n";  // Título

    if (head == nullptr) {
        gotoxy(x, 4);
        cout << "No hay empleados en la lista.\n";  // Mensaje si no hay empleados
    } else {
        Empleado* temp = head;
        int y = 4;
        
        // Cabecera
        gotoxy(50, y);
        cout << "ID";
        gotoxy(55, y);
        cout << "Nombre";
        gotoxy(75, y);
        cout << "Puesto";
        gotoxy(50, y + 1);
        cout << "-----------------------------------";

        // Itera sobre la lista desde head hasta tail y muestra cada empleado
        while (temp != nullptr) {
            y += 2;

            // Muestra los detalles de cada empleado
            gotoxy(50, y);
            cout << temp->idEmpleado;
            gotoxy(55, y);
            cout << temp->nombre << " " << temp->apellido;
            gotoxy(75, y);
            cout << temp->puesto;

            // Avanza al siguiente empleado
            temp = temp->siguiente;
        }

        // Muestra un mensaje indicando que se ha mostrado toda la lista en orden
        gotoxy(x, y + 3);
        cout << "Todos los empleados han sido mostrados en orden.\n";
        
        // Mostrar lista en orden inverso (opcional)
        cout << "\nDeseas mostrar la lista en orden inverso? (s/n): ";
        char opcion;
        cin >> opcion;
        if (opcion == 's' || opcion == 'S') {
            system("cls");
            gotoxy(x, 2);
            cout << "--- Lista de Empleados (Orden Inverso) ---\n";

            temp = tail;  // Empezamos desde el tail
            y = 4;

            // Cabecera
            gotoxy(50, y);
            cout << "ID";
            gotoxy(55, y);
            cout << "Nombre";
            gotoxy(75, y);
            cout << "Puesto";
            gotoxy(50, y + 1);
            cout << "-----------------------------------";

            // Itera sobre la lista desde tail hasta head
            while (temp != nullptr) {
                y += 2;

                // Muestra los detalles de cada empleado
                gotoxy(50, y);
                cout << temp->idEmpleado;
                gotoxy(55, y);
                cout << temp->nombre << " " << temp->apellido;
                gotoxy(75, y);
                cout << temp->puesto;

                // Retrocede al empleado anterior
                temp = temp->anterior;
            }

            // Muestra un mensaje indicando que se ha mostrado toda la lista en orden inverso
            gotoxy(x, y + 3);
            cout << "Todos los empleados han sido mostrados en orden inverso.\n";
        }
    }

    system("pause");  // Pausa después de mostrar la lista completa
}


void actualizarEmpleado(Empleado* head, Empleado* tail, int id) {
    system("cls");
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 30;

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
                    getline(cin, nuevoValor);
                    temp->nombre = nuevoValor;
                    gotoxy(x, 16);
                    cout << "Nombre actualizado con éxito.\n";
                    break;
                case 2:
                    gotoxy(x, 14);
                    cout << "Ingrese el nuevo apellido: ";
                    getline(cin, nuevoValor);
                    temp->apellido = nuevoValor;
                    gotoxy(x, 16);
                    cout << "Apellido actualizado con éxito.\n";
                    break;
                case 3:
                    gotoxy(x, 14);
                    cout << "Ingrese la nueva contraseña: ";
                    getline(cin, nuevoValor);
                    temp->contrasena = nuevoValor;
                    gotoxy(x, 16);
                    cout << "Contraseña actualizada con éxito.\n";
                    break;
                case 4:
                    gotoxy(x, 14);
                    cout << "Ingrese el nuevo puesto: ";
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

        // Liberar la cola de solicitudes asociada al empleado
        if (temp->colaSolicitudes != nullptr) {
            Solicitud* solTemp;
            while (temp->colaSolicitudes->cabeza != nullptr) {
                solTemp = temp->colaSolicitudes->cabeza;
                temp->colaSolicitudes->cabeza = temp->colaSolicitudes->cabeza->siguiente;
                delete solTemp;
            }
            delete temp->colaSolicitudes;
        }

        delete temp;
        gotoxy(x, 2);
        cout << "Empleado eliminado con éxito.\n";
        system("pause");
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

    // Liberar la cola de solicitudes asociada al empleado
    if (actual->colaSolicitudes != nullptr) {
        Solicitud* solTemp;
        while (actual->colaSolicitudes->cabeza != nullptr) {
            solTemp = actual->colaSolicitudes->cabeza;
            actual->colaSolicitudes->cabeza = actual->colaSolicitudes->cabeza->siguiente;
            delete solTemp;
        }
        delete actual->colaSolicitudes;
    }

    delete actual;
    gotoxy(x, 2);
    cout << "Empleado eliminado con éxito.\n";
    system("pause");
}


int mostrarMenuGestionEmpleados(Empleado*& head, Empleado*& tail) {
    system("cls");
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 30; 
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
            cout << string(50, ' '); 
        }
    } while (!entradaValida || opcion < 1 || opcion > 5);

    switch (opcion) {
        case 1: {
            crearYAgregarEmpleado(head,tail);
            break;
        }
        case 2:
            mostrarEmpleados(head, tail);
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
                    cout << string(50, ' '); 
                }
            } while (!entradaValida);
            actualizarEmpleado(head,tail, id);
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
                    cout << string(50, ' '); 
                }
            } while (!entradaValida);
            eliminarEmpleado(head, tail, id);
            break;
        }
        case 5:
            return 0; 
        default:
            gotoxy(x, 12);
            cout << "Opción inválida. Intente de nuevo.\n";
            system("pause");
            break;
    }
    return 1; 
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