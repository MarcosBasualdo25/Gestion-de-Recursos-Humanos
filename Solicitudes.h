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

    // Mostrar lista de razones para seleccionar
    gotoxy(x, 4);
    cout << "Seleccione la razón de la solicitud:";
    gotoxy(x, 5);
    cout << "1. Seguridad o Salud";
    gotoxy(x, 6);
    cout << "2. Condiciones Laborales";
    gotoxy(x, 7);
    cout << "3. Beneficios Adicionales";

    int opcionRazon;
    gotoxy(x, 8);
    cout << "Opción: ";
    cin >> opcionRazon;
    cin.ignore();  // Limpiar el buffer de entrada

    int prioridad;
    switch (opcionRazon) {
        case 1:
            razon = "Seguridad o Salud";
            prioridad = 1;  // Alta prioridad
            break;
        case 2:
            razon = "Condiciones Laborales";
            prioridad = 2;  // Prioridad media
            break;
        case 3:
            razon = "Beneficios Adicionales";
            prioridad = 3;  // Baja prioridad
            break;
        default:
            gotoxy(x, 9);
            cout << "Opción inválida. Seleccione una razón válida.\n";
            system("pause");
            return;
    }

    gotoxy(x, 10);
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
    nuevaSolicitud->Prioridad = prioridad;  // Nueva propiedad para la prioridad
    nuevaSolicitud->siguiente = nullptr;

    // Si la cola no existe, inicializarla
    if (cola == nullptr) {
        cola = new ColaSolicitudes();
        cola->cabeza = cola->cola = nuevaSolicitud;
    } else {
        // Insertar la solicitud según su prioridad
        if (cola->cabeza == nullptr || nuevaSolicitud->Prioridad < cola->cabeza->Prioridad) {
            // Insertar al inicio si es de mayor prioridad que la cabeza actual
            nuevaSolicitud->siguiente = cola->cabeza;
            cola->cabeza = nuevaSolicitud;
        } else {
            // Insertar en su posición correcta
            Solicitud* actual = cola->cabeza;
            while (actual->siguiente != nullptr && actual->siguiente->Prioridad <= nuevaSolicitud->Prioridad) {
                actual = actual->siguiente;
            }
            nuevaSolicitud->siguiente = actual->siguiente;
            actual->siguiente = nuevaSolicitud;

            // Ajustar cola si es el último nodo
            if (nuevaSolicitud->siguiente == nullptr) {
                cola->cola = nuevaSolicitud;
            }
        }
    }

    gotoxy(x, 12);
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

inline void atenderSolicitud(ColaSolicitudes*& cola) {
    system("cls");
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 30;

    gotoxy(x, 2);
    cout << "--- Atender Solicitud ---\n";

    if (cola == nullptr || cola->cabeza == nullptr) {
        gotoxy(x, 4);
        cout << "No hay solicitudes en la cola para atender.\n";
        system("pause");
        return;
    }

    // Buscar la primera solicitud con estado "Pendiente"
    Solicitud* actual = cola->cabeza;
    while (actual != nullptr && actual->Estado != "Pendiente") {
        actual = actual->siguiente;
    }

    if (actual == nullptr) {
        // No se encontró ninguna solicitud pendiente
        gotoxy(x, 4);
        cout << "No hay solicitudes con estado 'Pendiente' para atender.\n";
        system("pause");
        return;
    }

    // Mostrar los datos de la solicitud a atender
    gotoxy(x, 4);
    cout << "Primera solicitud pendiente en la cola:";
    gotoxy(x, 5);
    cout << "ID: " << actual->IDsolicitud;
    gotoxy(x, 6);
    cout << "Razón: " << actual->Razon;
    gotoxy(x, 7);
    cout << "Descripción: " << actual->Descripcion;
    gotoxy(x, 8);
    cout << "Fecha de Solicitud: " << actual->FechaSolicitud;

    // Preguntar el nuevo estado de la solicitud
    gotoxy(x, 10);
    cout << "Seleccione el nuevo estado de la solicitud:";
    gotoxy(x, 11);
    cout << "1. Aceptada";
    gotoxy(x, 12);
    cout << "2. Rechazada";
    gotoxy(x, 13);
    cout << "3. Volver al menú";

    int opcionEstado;
    gotoxy(x, 15);
    cout << "Opción: ";
    cin >> opcionEstado;
    cin.ignore();  // Limpiar el buffer de entrada

    switch (opcionEstado) {
        case 1:
            actual->Estado = "Aceptada";
            break;
        case 2:
            actual->Estado = "Rechazada";
            break;
        case 3: 
            return;
        default:
            gotoxy(x, 17);
            cout << "Opción inválida. No se realizará ningún cambio.\n";
            system("pause");
            return;
    }

    // Actualizar fecha de resolución
    actual->FechaResolucion = obtenerFechaActual();

    // Solicitar comentario opcional
    gotoxy(x, 16);
    cout << "Ingrese un comentario administrativo (opcional, presione Enter para omitir): ";
    string comentarioAdmin;
    getline(cin, comentarioAdmin);
    if (!comentarioAdmin.empty()) {
        actual->ComentarioAdmin = comentarioAdmin;
    }

    gotoxy(x, 18);
    cout << "La solicitud fue atendida exitosamente.\n";
    system("pause");
}


inline void eliminarSolicitud(ColaSolicitudes*& cola) {
    system("cls");
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 30;

    gotoxy(x, 2);
    cout << "--- Eliminar Solicitud ---\n";

    if (cola == nullptr || cola->cabeza == nullptr) {
        gotoxy(x, 4);
        cout << "No hay solicitudes en la cola para eliminar.\n";
        system("pause");
        return;
    }

    int idSolicitud;
    gotoxy(x, 4);
    cout << "Ingrese el ID de la solicitud que desea eliminar: ";
    cin >> idSolicitud;
    cin.ignore();  // Limpiar el buffer de entrada

    // Buscar la solicitud por ID
    Solicitud* actual = cola->cabeza;
    Solicitud* anterior = nullptr;

    while (actual != nullptr && actual->IDsolicitud != idSolicitud) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == nullptr) {
        // Si no se encuentra la solicitud
        gotoxy(x, 6);
        cout << "No se encontró una solicitud con el ID ingresado.\n";
        system("pause");
        return;
    }

    // Mostrar los datos de la solicitud antes de confirmar eliminación
    gotoxy(x, 6);
    cout << "Solicitud encontrada:";
    gotoxy(x, 7);
    cout << "ID: " << actual->IDsolicitud;
    gotoxy(x, 8);
    cout << "Razón: " << actual->Razon;
    gotoxy(x, 9);
    cout << "Descripción: " << actual->Descripcion;
    gotoxy(x, 10);
    cout << "Estado: " << actual->Estado;
    gotoxy(x, 11);
    cout << "Fecha de Solicitud: " << actual->FechaSolicitud;
    gotoxy(x, 12);
    cout << "Fecha de Resolución: " << actual->FechaResolucion;
    gotoxy(x, 13);
    cout << "Comentario del Administrador: " << (actual->ComentarioAdmin.empty() ? "N/A" : actual->ComentarioAdmin);

    gotoxy(x, 15);
    cout << "¿Está seguro que desea eliminar esta solicitud? (S/N): ";
    char confirmacion;
    cin >> confirmacion;

    if (tolower(confirmacion) != 's') {
        gotoxy(x, 17);
        cout << "Operación cancelada. La solicitud no fue eliminada.\n";
        system("pause");
        return;
    }

    // Eliminar la solicitud
    if (actual == cola->cabeza) {
        // Caso: La solicitud a eliminar es la cabeza
        cola->cabeza = actual->siguiente;

        // Si la cabeza era también la cola
        if (cola->cabeza == nullptr) {
            cola->cola = nullptr;
        }
    } else {
        // Caso: La solicitud está en el medio o final
        anterior->siguiente = actual->siguiente;

        // Si la solicitud era la última, actualizar la cola
        if (actual == cola->cola) {
            cola->cola = anterior;
        }
    }

    delete actual;  // Liberar memoria

    gotoxy(x, 17);
    cout << "La solicitud con ID " << idSolicitud << " fue eliminada exitosamente.\n";
    system("pause");
}


