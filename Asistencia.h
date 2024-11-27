#include <iostream>
#include <iomanip> 
#include <ctime>
#include <windows.h>
#include "GestionEmpleados.h"

using namespace std;

// Función para obtener la hora y fecha actua
inline string obtenerHoraActual() {
    time_t ahora = time(0);
    struct tm* timeinfo = localtime(&ahora);
    char buffer[80];
    strftime(buffer, 80, "%H:%M:%S", timeinfo);
    return string(buffer);
}

inline string obtenerFechaActual() {
    time_t ahora = time(0);
    struct tm* timeinfo = localtime(&ahora);
    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%d", timeinfo);
    return string(buffer);
}

// Función para agregar un registro de asistencia en la pila
void agregarRegistro(PilaAsistencias*& pila) {
    RegistroAsistencia* nuevoRegistro = new RegistroAsistencia;
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 20; 
    nuevoRegistro->fecha = obtenerFechaActual();

    if (pila == nullptr) {
        pila = new PilaAsistencias();
        pila->cima = nullptr;
    }
    gotoxy(x,15);
    if (pila->cima == NULL || (!pila->cima->horaEntrada.empty() && !pila->cima->horaSalida.empty())) {
        nuevoRegistro->horaEntrada = obtenerHoraActual();
        nuevoRegistro->estado = "Presente";
        nuevoRegistro->horaSalida = "";  
        nuevoRegistro->siguiente = pila->cima;
        pila->cima = nuevoRegistro;
        color(114);; cout << "Hora de entrada registrada correctamente.\n"; color(7);
    } else if (pila->cima->horaSalida.empty()) {
        pila->cima->horaSalida = obtenerHoraActual();
        color(114);; cout << "Hora de salida registrada correctamente.\n"; color(7);
    }
}

void imprimirRegistros(PilaAsistencias* pila) {
    system("cls");
    system("color 70");
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 2 - 40;  // Centrar tabla

    // Cuadro para el título
    gotoxy(x, 2);
    cout << "╔════════════════════════════════════════════════════════════════════════════╗";
    gotoxy(x, 3);
    cout << "║                           REGISTRO DE ASISTENCIAS                          ║";
    gotoxy(x, 4);
    cout << "╚════════════════════════════════════════════════════════════════════════════╝";

    // Espaciado entre el título y la tabla
    gotoxy(x, 6);

    // Cuadro para la tabla
    cout << "╔═══════╦══════════════╦═════════════════╦═════════════════╦═════════════════╗";
    gotoxy(x, 7);
    cout << "║  No.  ║     Fecha    ║   Hora Entrada  ║   Hora Salida   ║      Estado     ║";
    gotoxy(x, 8);
    cout << "╠═══════╬══════════════╬═════════════════╬═════════════════╬═════════════════╣";

    if (pila == nullptr || pila->cima == nullptr) {
        gotoxy(x, 9);
        cout << "║                         No hay registros de asistencia.                   ║";
        gotoxy(x, 10);
        cout << "╚════════════════════════════════════════════════════════════════════════════╝";
    } else {
        RegistroAsistencia* actual = pila->cima;
        int i = 1, y = 9;

        // Iterar sobre la pila
        while (actual != nullptr) {
            gotoxy(x, y++);
            cout << "║ " << setw(5) << left << i++
                 << " ║ " << setw(12) << centerText(actual->fecha, 12)
                 << " ║ " << setw(15) << centerText(actual->horaEntrada, 15)
                 << " ║ " << setw(15) << centerText((actual->horaSalida.empty() ? "N/A" : actual->horaSalida), 15)
                 << " ║ " << setw(15) << centerText(actual->estado, 15) << " ║";

            actual = actual->siguiente;

            // Si hay más registros, dibujar separador
            if (actual != nullptr) {
                gotoxy(x, y++);
                cout << "╠═══════╬══════════════╬═════════════════╬═════════════════╬═════════════════╣";
            }
        }

        // Dibujar el pie de la tabla
        gotoxy(x, y);
        cout << "╚════════════════════════════════════════════════════════════════════════════╝";
    }
    getch();
}
