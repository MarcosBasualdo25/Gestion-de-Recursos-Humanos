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
    int i = 1;
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 4;
    gotoxy(x,2);
    if (pila == nullptr || pila->cima == nullptr) {
        
        cout << "No hay registros de asistencia.\n";
        return;
    }

    RegistroAsistencia* actual = pila->cima;

    gotoxy(x, 2);
    cout << "╔═══════════════════════════════════════════════════════════════════╗";
    gotoxy(x, 3);
    cout << "║                           MIS ASISTENCIAS                         ║";
    gotoxy(x, 4);
    cout << "╚═══════════════════════════════════════════════════════════════════╝";
    
    // Imprimir el encabezado de la tabla
    cout<<endl;
        gotoxy(x, 5);
    cout << left << setw(5) << "No."
        << setw(15) << "Fecha"
        << setw(20) << "Hora Entrada"
        << setw(20) << "Hora Salida"
        << setw(12) << "Estado"<<endl;
    gotoxy(x, 6);
    color(118); cout << string(75, '-') << endl; color(7);  // Separador

    // Recorrer la pila e imprimir cada registro en formato de tabla
    while (actual != NULL) {
        gotoxy(x, 6+i);
        color(112);
        cout << left << setw(5) << i++  
            << setw(15) << actual->fecha
            << setw(20) << actual->horaEntrada
            << setw(20) << actual->horaSalida; 
        color(114); cout<< setw(12) << actual->estado<<endl; color(7);

        actual = actual->siguiente;
    }
}