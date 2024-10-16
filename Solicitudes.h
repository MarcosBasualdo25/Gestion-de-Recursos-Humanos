#include <iostream>
#include <string>
#include "GestionEmpleados.h"  // Asegúrate de que este archivo incluye la definición de la estructura ColaSolicitudes
#include "gotoxy.h"
#include <limits>
#include <ctime>

using namespace std;

// Funciones para manejar solicitudes
void enviarSolicitud(ColaSolicitudes*& cola);
void mostrarSolicitudesEmpleado(ColaSolicitudes* cola);


// Implementación de funciones

inline void enviarSolicitud(ColaSolicitudes*& cola) {
    system("cls");
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 20;

    gotoxy(x, 2);
    cout << "--- Enviar Solicitud ---\n";

    string razon, descripcion;
    int idSolicitud = (cola == nullptr || cola->cabeza == nullptr) ? 1 : cola->cola->IDsolicitud + 1;  // ID incrementa automáticamente

    gotoxy(x, 4);
    cout << "Ingrese la razón de la solicitud: ";
    getline(cin, razon);
    
    gotoxy(x, 5);
    cout << "Ingrese una breve descripción: ";
    getline(cin, descripcion);

    // Crear nueva solicitud
    Solicitud* nuevaSolicitud = new Solicitud();
    nuevaSolicitud->IDsolicitud = idSolicitud;
    nuevaSolicitud->Razon = razon;
    nuevaSolicitud->FechaSolicitud = obtenerFechaActual();  // Función que genera la fecha actual
    nuevaSolicitud->Descripcion = descripcion;
    nuevaSolicitud->Estado = "Pendiente";
    nuevaSolicitud->FechaResolucion = "N/A";
    nuevaSolicitud->ComentarioAdmin = "";
    nuevaSolicitud->siguiente = nullptr;

    // Si la cola no existe, inicializarla
    if (cola == nullptr) {
        cola = new ColaSolicitudes();
        cola->cabeza = cola->cola = nullptr;
    }

    // Agregar la solicitud a la cola
    if (cola->cabeza == nullptr) {
        // Si la cola está vacía, la nueva solicitud es tanto la cabeza como la cola
        cola->cabeza = cola->cola = nuevaSolicitud;
    } else {
        // Si no está vacía, agregar la solicitud al final (en cola)
        cola->cola->siguiente = nuevaSolicitud;
        cola->cola = nuevaSolicitud;
    }

    gotoxy(x, 7);
    cout << "Solicitud enviada exitosamente con ID " << idSolicitud << ".\n";
    system("pause");
}

inline void mostrarSolicitudesEmpleado(ColaSolicitudes* cola) {
    system("cls");
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 30;

    gotoxy(x, 2);
    cout << "--- Solicitudes del Empleado ---\n";

    if (cola == nullptr || cola->cabeza == nullptr) {
        gotoxy(x, 4);
        cout << "No hay solicitudes enviadas por este empleado.\n";
    } else {
        Solicitud* actual = cola->cabeza;
        int numeroSolicitud = 1;
        int y = 4;

        while (actual != nullptr) {
            gotoxy(x, y++);
            cout << "Solicitud #" << numeroSolicitud << " (ID: " << actual->IDsolicitud << "):";
            gotoxy(x, y++);
            cout << "Razón: " << actual->Razon;
            gotoxy(x, y++);
            cout << "Descripción: " << actual->Descripcion;
            gotoxy(x, y++);
            cout << "Estado: " << actual->Estado;
            gotoxy(x, y++);
            cout << "Fecha de Solicitud: " << actual->FechaSolicitud;
            gotoxy(x, y++);
            cout << "Fecha de Resolución: " << actual->FechaResolucion;
            gotoxy(x, y++);
            cout << "Comentario del Administrador: " << (actual->ComentarioAdmin.empty() ? "N/A" : actual->ComentarioAdmin);
            gotoxy(x, y++);
            cout << "-------------------------------------------";

            actual = actual->siguiente;
            numeroSolicitud++;
            y++;  // Espacio entre solicitudes
        }
    }
    system("pause");
}
