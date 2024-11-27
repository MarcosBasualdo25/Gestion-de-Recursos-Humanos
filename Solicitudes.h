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

inline void enviarSolicitud(ColaSolicitudes*& cola, int idEmpleado) {
    system("cls");
    system("color 70"); // Fondo gris claro
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 40; // Centrar la interfaz

    // Título
    color(113); // Azul para el título
    gotoxy(x, 2);
    cout << "╔════════════════════════════════════════════════════════════════════════════╗";
    gotoxy(x, 3);
    cout << "║                          ENVIAR SOLICITUD                                  ║";
    gotoxy(x, 4);
    cout << "╚════════════════════════════════════════════════════════════════════════════╝";
    color(112); // Texto negro sobre fondo gris claro

    string razon, descripcion;
    int idSolicitud = (cola == nullptr || cola->cabeza == nullptr) ? 1 : cola->cola->IDsolicitud + 1;

    // Lista de razones para seleccionar
    gotoxy(x+10, 6);
    cout << "╔════════════════════════════════════════════════════════╗";
    gotoxy(x+10, 7);
    cout << "║ Seleccione la razón de la solicitud:                   ║";
    gotoxy(x+10, 8);
    cout << "║   1. Seguridad o Salud                                 ║";
    gotoxy(x+10, 9);
    cout << "║   2. Condiciones Laborales                             ║";
    gotoxy(x+10, 10);
    cout << "║   3. Beneficios Adicionales                            ║";
    gotoxy(x+10, 11);
    cout << "╚════════════════════════════════════════════════════════╝";

    int opcionRazon;
    bool entradaValida = false;
    do {
        gotoxy(x, 13);
        cout << "╔════════════════════════════════════════════════════════════════════════════╗";
        gotoxy(x, 14);
        cout << "║ Ingrese la opción (1-3):                                                   ║";
        gotoxy(x, 15);
        cout << "╚════════════════════════════════════════════════════════════════════════════╝";
        gotoxy(x + 28, 14);
        entradaValida = obtenerEntero(opcionRazon);
        if (!entradaValida || opcionRazon < 1 || opcionRazon > 3) {
            gotoxy(x + 4, 16);
            color(124); // Rojo para error
            cout << "Error: Seleccione una opción válida (1-3).";
            gotoxy(x + 28, 14);
            cout << string(10, ' '); // Limpiar entrada
            color(112); // Regresa al color estándar
        }
    } while (!entradaValida || opcionRazon < 1 || opcionRazon > 3);

    int prioridad;
    switch (opcionRazon) {
        case 1:
            razon = "Seguridad o Salud";
            prioridad = 1; // Alta prioridad
            break;
        case 2:
            razon = "Condiciones Laborales";
            prioridad = 2; // Prioridad media
            break;
        case 3:
            razon = "Beneficios Adicionales";
            prioridad = 3; // Baja prioridad
            break;
    }

    // Solicitar descripción
    do {
        gotoxy(x, 17);
        cout << "╔════════════════════════════════════════════════════════════════════════════╗";
        gotoxy(x, 18);
        cout << "║ Breve descripción:                                                         ║";
        gotoxy(x, 19);
        cout << "╚════════════════════════════════════════════════════════════════════════════╝";
        gotoxy(x + 21, 18);
        getline(cin, descripcion);
        if (descripcion.empty()) {
            gotoxy(x + 4, 20);
            color(124); // Rojo para error
            cout << "Error: La descripción no puede estar vacía. Por favor, ingrésela.";
            color(112); // Regresa al color estándar
        }
    } while (descripcion.empty());

    // Crear nueva solicitud
    Solicitud* nuevaSolicitud = new Solicitud();
    nuevaSolicitud->IDsolicitud = idSolicitud;
    nuevaSolicitud->Razon = razon;
    nuevaSolicitud->FechaSolicitud = obtenerFechaActual();
    nuevaSolicitud->Descripcion = descripcion;
    nuevaSolicitud->Estado = "Pendiente";
    nuevaSolicitud->FechaResolucion = "N/A";
    nuevaSolicitud->ComentarioAdmin = "";
    nuevaSolicitud->Prioridad = prioridad;
    nuevaSolicitud->idEmpleado = idEmpleado;
    nuevaSolicitud->siguiente = nullptr;

    // Insertar en la cola
    if (cola == nullptr) {
        cola = new ColaSolicitudes();
        cola->cabeza = cola->cola = nuevaSolicitud;
    } else {
        if (cola->cabeza == nullptr || nuevaSolicitud->Prioridad < cola->cabeza->Prioridad) {
            nuevaSolicitud->siguiente = cola->cabeza;
            cola->cabeza = nuevaSolicitud;
        } else {
            Solicitud* actual = cola->cabeza;
            while (actual->siguiente != nullptr && actual->siguiente->Prioridad <= nuevaSolicitud->Prioridad) {
                actual = actual->siguiente;
            }
            nuevaSolicitud->siguiente = actual->siguiente;
            actual->siguiente = nuevaSolicitud;

            if (nuevaSolicitud->siguiente == nullptr) {
                cola->cola = nuevaSolicitud;
            }
        }
    }

    // Confirmación
    color(114); // Verde para confirmación
    gotoxy(x+16, 22);
    cout << "╔══════════════════════════════════════════════╗";
    gotoxy(x+16, 23);
    cout << "║  Solicitud enviada exitosamente con ID " << setw(4) << idSolicitud << "  ║";
    gotoxy(x+16, 24);
    cout << "╚══════════════════════════════════════════════╝";
    color(112); // Regresa al color estándar

    getch();
}



inline void mostrarSolicitudesEmpleado(ColaSolicitudes* cola, int idEmpleado) {
    system("cls");
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 30;

    // Título
    color(113); // Azul para el título
    gotoxy(x, 2);
    cout << "╔════════════════════════════════════════════════════════════════════════════╗";
    gotoxy(x, 3);
    cout << "║                            MIS SOLICITUDES                                 ║";
    gotoxy(x, 4);
    cout << "╚════════════════════════════════════════════════════════════════════════════╝";
    color(112); // Texto negro sobre fondo gris claro

    if (cola == nullptr || cola->cabeza == nullptr) {
        gotoxy(x, 6);
        cout << "╔════════════════════════════════════════════════════════════════════════════╗";
        gotoxy(x, 7);
        cout << "║    No tienes ninguna solicitud enviada.                                    ║";
        gotoxy(x, 8);
        cout << "╚════════════════════════════════════════════════════════════════════════════╝";
        system("pause");
        return;
    } else {
        Solicitud* actual = cola->cabeza;
        int numeroSolicitud = 1;
        int y = 6;

        while (actual != nullptr) {
            if (actual->idEmpleado == idEmpleado) {
                gotoxy(x, y++);
                cout << "╔══════════════════════╗";
                gotoxy(x, y++);
                cout << "║ Solicitud #" << numeroSolicitud << " (ID: " << actual->IDsolicitud << ") ║";
                gotoxy(x, y++);
                cout << "╚══════════════════════╝";
                gotoxy(x, y++);
                cout << "╔════════════════════════════════════════════════════╗";
                gotoxy(x, y++);
                cout << "║ Razón: " << actual->Razon;
                gotoxy(x, y++);
                cout << "║ Descripción: " << actual->Descripcion;
                gotoxy(x, y++);
                cout << "║ Estado: " << actual->Estado;
                gotoxy(x, y++);
                cout << "║ Fecha de Solicitud: " << actual->FechaSolicitud;
                gotoxy(x, y++);
                cout << "║ Fecha de Resolución: " << actual->FechaResolucion;
                gotoxy(x, y++);
                cout << "║ Comentario del Administrador: " << (actual->ComentarioAdmin.empty() ? "N/A" : actual->ComentarioAdmin);
                gotoxy(x, y++);
                cout << "╚════════════════════════════════════════════════════╝";
                numeroSolicitud++;
                y += 2;  // Espacio entre solicitudes
            }
            actual = actual->siguiente;
        }
    }
    system("pause");
}



inline void atenderSolicitud(ColaSolicitudes*& cola) {
    system("cls");
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 30;

    // Título con borde
    color(113); // Azul para el título
    gotoxy(x, 2);
    cout << "╔════════════════════════════════════════════════════════════════════════════╗";
    gotoxy(x, 3);
    cout << "║                            ATENDER SOLICITUD                               ║";
    gotoxy(x, 4);
    cout << "╚════════════════════════════════════════════════════════════════════════════╝";
    color(112); // Texto negro sobre fondo gris claro

    if (cola == nullptr || cola->cabeza == nullptr) {
        color(124);
        gotoxy(x, 6);
        cout << "╔════════════════════════════════════════════════════════════════════════════╗";
        gotoxy(x, 7);
        cout << "║ No hay solicitudes en la cola para atender.                                ║";
        gotoxy(x, 8);
        cout << "╚════════════════════════════════════════════════════════════════════════════╝";
        color(112);
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
        gotoxy(x, 6);
        cout << "╔════════════════════════════════════════════════════════════════════════════╗";
        gotoxy(x, 7);
        cout << "║ No hay solicitudes con estado 'Pendiente' para atender.                    ║";
        gotoxy(x, 8);
        cout << "╚════════════════════════════════════════════════════════════════════════════╝";
        system("pause");
        return;
    }

    // Mostrar los datos de la solicitud a atender
    gotoxy(x, 6);
    cout << "╔══════════════════════════════╗";
    gotoxy(x, 7);
    cout << "║ Solicitud Pendiente (ID: " << actual->IDsolicitud << ")  ║";
    gotoxy(x, 8);
    cout << "╚══════════════════════════════╝";
    gotoxy(x, 9);
    cout << "╔═════════════════════════════════════════════╗";
    gotoxy(x, 10);
    cout << "║ Razón: " << actual->Razon;
    gotoxy(x, 11);
    cout << "║ Descripción: " << actual->Descripcion;
    gotoxy(x, 12);
    cout << "║ Fecha de Solicitud: " << actual->FechaSolicitud;
    gotoxy(x, 13);
    cout << "╚═════════════════════════════════════════════╝";

    // Preguntar el nuevo estado de la solicitud
    gotoxy(x, 15);
    cout << "╔═════════════════════════════════════════════╗";
    gotoxy(x, 16);
    cout << "║ Seleccione el nuevo estado de la solicitud: ║";
    gotoxy(x, 17);
    cout << "║ 1. Aceptada                                 ║";
    gotoxy(x, 18);
    cout << "║ 2. Rechazada                                ║";
    gotoxy(x, 19);
    cout << "║ 3. Volver al menú                           ║";
    gotoxy(x, 20);
    cout << "╚═════════════════════════════════════════════╝";

    int opcionEstado;
    gotoxy(x, 22);
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
            color(124);
            gotoxy(x, 23);
            cout << "╔════════════════════════════════════════════════╗";
            gotoxy(x, 24);
            cout << "║ Opción inválida. No se realizará ningún cambio.║";
            gotoxy(x, 25);
            cout << "╚════════════════════════════════════════════════╝";
            color(112);
            system("pause");
            return;
    }

    // Actualizar fecha de resolución
    actual->FechaResolucion = obtenerFechaActual();

    // Solicitar comentario opcional
    gotoxy(x, 23);
    cout << "Ingrese un comentario administrativo (opcional): ";
    string comentarioAdmin;
    getline(cin, comentarioAdmin);
    if (!comentarioAdmin.empty()) {
        actual->ComentarioAdmin = comentarioAdmin;
    }

    color(114);
    gotoxy(x, 24);
    cout << "╔══════════════════════════════════════════╗";
    gotoxy(x,25);
    cout << "║ La solicitud fue atendida exitosamente.  ║";
    gotoxy(x, 26);
    cout << "╚══════════════════════════════════════════╝";
    color(112);
    system("pause");
}




inline void eliminarSolicitud(ColaSolicitudes*& cola, int idEmpleado) {
    system("cls");
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 30;

    // Título con borde
    color(113); // Azul para el título
    gotoxy(x, 2);
    cout << "╔════════════════════════════════════════════════════════════════════════════╗";
    gotoxy(x, 3);
    cout << "║                           ELIMINAR SOLICITUD                               ║";
    gotoxy(x, 4);
    cout << "╚════════════════════════════════════════════════════════════════════════════╝";
    color(112); // Texto negro sobre fondo gris claro

    if (cola == nullptr || cola->cabeza == nullptr) {
        gotoxy(x, 6);
        cout << "╔════════════════════════════════════════════════════════════════════════════╗";
        gotoxy(x, 7);
        cout << "║ No hay solicitudes en la cola para eliminar.                               ║";
        gotoxy(x, 8);
        cout << "╚════════════════════════════════════════════════════════════════════════════╝";
        system("pause");
        return;
    }

    int idSolicitud;
    gotoxy(x, 6);
    cout << "╔══════════════════════════════════════════════════════╗";
    gotoxy(x, 7);
    cout << "║ Ingrese el ID de la solicitud que desea eliminar:    ║";
    gotoxy(x, 8);
    cout << "╚══════════════════════════════════════════════════════╝";
    gotoxy(x+52,7);
    cin >> idSolicitud;
    cin.ignore();  // Limpiar el buffer de entrada

    // Buscar la solicitud por ID
    Solicitud* actual = cola->cabeza;
    Solicitud* anterior = nullptr;

    while (actual != nullptr && (actual->IDsolicitud != idSolicitud || actual->idEmpleado != idEmpleado)) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == nullptr) {
        // Si no se encuentra la solicitud
        gotoxy(x, 10);
        cout << "╔═══════════════════════════════════════════════════╗";
        gotoxy(x, 11);
        cout << "║ No se encontró una solicitud con el ID ingresado. ║";
        gotoxy(x, 12);
        cout << "╚═══════════════════════════════════════════════════╝";
        system("pause");
        return;
    }

    // Mostrar los datos de la solicitud antes de confirmar eliminación
    gotoxy(x, 10);
    cout << "╔════════════════════════╗";
    gotoxy(x, 11);
    cout << "║ Solicitud encontrada   ║";
    gotoxy(x, 12);
    cout << "╚════════════════════════╝";
    gotoxy(x, 13);
    cout << "╔════════════════════════════════════════════════════════╗";
    gotoxy(x, 14);
    cout << "║ ID: " << actual->IDsolicitud;
    gotoxy(x, 15);
    cout << "║ Razón: " << actual->Razon;
    gotoxy(x, 16);
    cout << "║ Descripción: " << actual->Descripcion;
    gotoxy(x, 17);
    cout << "║ Estado: " << actual->Estado;
    gotoxy(x, 18);
    cout << "║ Fecha de Solicitud: " << actual->FechaSolicitud;
    gotoxy(x, 19);
    cout << "║ Fecha de Resolución: " << actual->FechaResolucion;
    gotoxy(x, 20);
    cout << "║ Comentario del Administrador: " << (actual->ComentarioAdmin.empty() ? "N/A" : actual->ComentarioAdmin);
    gotoxy(x, 21);
    cout << "╚════════════════════════════════════════════════════════╝";

    gotoxy(x, 23);
    cout << "╔══════════════════════════════════════════════════════════╗";
    gotoxy(x, 24);
    cout << "║ ¿Está seguro que desea eliminar esta solicitud? (S/N):   ║";
    gotoxy(x, 25);
    cout << "╚══════════════════════════════════════════════════════════╝";
    char confirmacion;
    gotoxy(x+56, 24);
    cin >> confirmacion;

    if (tolower(confirmacion) != 's') {
        color(124);
        gotoxy(x, 27);
        cout << "╔═════════════════════════════════════════════════════╗";
        gotoxy(x, 28);
        cout << "║ Operación cancelada. La solicitud no fue eliminada. ║";
        gotoxy(x, 29);
        cout << "╚═════════════════════════════════════════════════════╝";
        color(112);
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

    color(114);
    gotoxy(x, 27);
    cout << "╔════════════════════════════════════════════════════╗";
    gotoxy(x, 28);
    cout << "║ La solicitud con ID " << idSolicitud << " fue eliminada exitosamente.  ║";
    gotoxy(x, 29);
    cout << "╚════════════════════════════════════════════════════╝";
    color(112);
    system("pause");
}

