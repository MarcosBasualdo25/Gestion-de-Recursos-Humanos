#include <iostream>
#include <iomanip> 
#include <ctime>
#include <windows.h>
#include "GestionEmpleados.h"
#include <fstream>
#include <sstream>

using namespace std;

// Función para obtener la hora y fecha actual
string obtenerHoraActual() {
    time_t ahora = time(0);
    struct tm* timeinfo = localtime(&ahora);
    char buffer[80];
    strftime(buffer, 80, "%H:%M:%S", timeinfo);
    return string(buffer);
}

string obtenerFechaActual() {
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
    gotoxy(x,13);
    if (pila->cima == NULL || (!pila->cima->horaEntrada.empty() && !pila->cima->horaSalida.empty())) {
        nuevoRegistro->horaEntrada = obtenerHoraActual();
        nuevoRegistro->estado = "Presente";
        nuevoRegistro->horaSalida = "";  
        nuevoRegistro->siguiente = pila->cima;
        pila->cima = nuevoRegistro;
        color(2); cout << "Hora de entrada registrada correctamente.\n"; color(7);
    } else if (pila->cima->horaSalida.empty()) {
        pila->cima->horaSalida = obtenerHoraActual();
        color(2); cout << "Hora de salida registrada correctamente.\n"; color(7);
    }
}

void imprimirRegistros(PilaAsistencias* pila) {
    system("cls");
    
    int i = 1;
    int anchoConsola = obtenerAnchoConsola();
    int x = anchoConsola / 4;
    
    gotoxy(x,2);
    if (pila == nullptr) {
        
        cout << "No hay registros de asistencia.\n";
        return;
    }

    RegistroAsistencia* actual = pila->cima;

    // Imprimir el encabezado de la tabla
    cout << left << setw(5) << "No."
        << setw(15) << "Fecha"
        << setw(20) << "Hora Entrada"
        << setw(20) << "Hora Salida"
        << setw(12) << "Estado"<<endl;
    gotoxy(x, 3);
    color(6); cout << string(75, '-') << endl; color(7);  // Separador

    // Recorrer la pila e imprimir cada registro en formato de tabla
    while (actual != NULL) {
        gotoxy(x, 3+i);
        cout << left << setw(5) << i++  
            << setw(15) << actual->fecha
            << setw(20) << actual->horaEntrada
            << setw(20) << actual->horaSalida; 
        color(2); cout<< setw(12) << actual->estado<<endl; color(7);

        actual= actual->siguiente;
    }
}
