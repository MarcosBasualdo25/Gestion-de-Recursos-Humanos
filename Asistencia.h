#include <iostream>
#include <iomanip>  // Para manejar el ancho de columnas
#include <ctime>
#include <windows.h>
#include "GestionEmpleados.h"

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
    // Crear un nuevo nodo
    RegistroAsistencia* nuevoRegistro = new RegistroAsistencia;
    
    // Inicializar los campos del nuevo registro
    nuevoRegistro->fecha = obtenerFechaActual();

    if (pila == nullptr) {
        pila = new PilaAsistencias();
        pila->cima = nullptr;
    }

    if (pila->cima == NULL || (!pila->cima->horaEntrada.empty() && !pila->cima->horaSalida.empty())) {
        // Si no hay ningún registro en la pila o el registro anterior está completo, agregamos uno nuevo
        nuevoRegistro->horaEntrada = obtenerHoraActual();
        nuevoRegistro->estado = "Presente";
        nuevoRegistro->horaSalida = "";  // Aún no se ha registrado la salida
        nuevoRegistro->siguiente = pila->cima;
        pila->cima = nuevoRegistro;
        cout << "Hora de entrada registrada correctamente.\n";
    } else if (pila->cima->horaSalida.empty()) {
        // Si ya hay un registro con hora de entrada pero sin hora de salida, registramos la salida
        pila->cima->horaSalida = obtenerHoraActual();
        cout << "Hora de salida registrada correctamente.\n";
    }
}

// Función para imprimir todos los registros de la pila en formato de filas y columnas
void imprimirRegistros(PilaAsistencias*& pila) {
    RegistroAsistencia* actual = pila->cima;
    int i = 1;

    if (actual == NULL) {
        cout << "No hay registros de asistencia.\n";
        return;
    }

    // Imprimir el encabezado de la tabla
    cout << left << setw(5) << "No."
        << setw(15) << "Fecha"
        << setw(20) << "Hora Entrada"
        << setw(20) << "Hora Salida"
        << setw(12) << "Estado"<<endl;
    cout << string(85, '-') << endl;  // Separador

    // Recorrer la pila e imprimir cada registro en formato de tabla
    while (actual != NULL) {
        cout << left << setw(5) << i++  // Número de registro
            << setw(15) << actual->fecha
            << setw(20) << actual->horaEntrada
            << setw(20) << actual->horaSalida
            << setw(12) << actual->estado<<endl;

        actual = actual->siguiente;
    }
}