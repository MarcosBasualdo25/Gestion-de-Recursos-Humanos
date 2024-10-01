#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

struct Empleado {
    int idEmpleado;
    string nombre;
    string apellido;
    string contrasena;
    string puesto;
    Empleado *siguiente;
};

Empleado* crearEmpleado();
void agregarEmpleado(Empleado*& head, Empleado* nuevoEmpleado);
void mostrarEmpleados(Empleado* head);
void actualizarEmpleado(Empleado* head, int id);
void eliminarEmpleado(Empleado*& head, int id);
void mostrarMenu(Empleado* listaEmpleados);

Empleado* crearEmpleado() {
    Empleado* nuevoEmpleado = new Empleado();

    int idEmpleado;
    string nombre, apellido, contrasena, puesto;

    cout << "Ingrese el ID del empleado: ";
    cin >> idEmpleado;
    cout << "Ingrese el nombre del empleado: ";  
    cin.ignore();// Ignorar el salto de línea pendiente en el búfer de entrada
    getline(cin, nombre);
    cout << "Ingrese el apellido del empleado: ";
    getline(cin, apellido);
    cout << "Ingrese la contraseña del empleado: ";
    getline(cin, contrasena);
    cout << "Ingrese el puesto del empleado: ";
    getline(cin, puesto);

    nuevoEmpleado->idEmpleado = idEmpleado;
    nuevoEmpleado->nombre = nombre;
    nuevoEmpleado->apellido = apellido;
    nuevoEmpleado->contrasena = contrasena;
    nuevoEmpleado->puesto = puesto;
    nuevoEmpleado->siguiente = nullptr;
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
    cout << "\n";

    if (head == nullptr) {
        cout << "No hay empleados en la lista." << endl;
        return;
    }

    Empleado* temp = head;
    while (temp != nullptr) {
        cout << "ID: " << temp->idEmpleado << ", Nombre: " << temp->nombre << " " << temp->apellido
             << ", Puesto: " << temp->puesto << endl;
        temp = temp->siguiente;
    }

    cout << "\n";
}

void actualizarEmpleado(Empleado* head, int id) {
    Empleado* temp = head;
    while (temp != nullptr) {
        if (temp->idEmpleado == id) {

            int opcion;

            cout << "Seleccione el atributo a modificar:" << endl;
            cout << "1. Nombre" << endl;
            cout << "2. Apellido" << endl;
            cout << "3. Contraseña" << endl;
            cout << "4. Puesto" << endl;
            
            do {
                cout << "Ingrese su opción: ";
                cin >> opcion;
            } while (opcion < 1 || opcion > 4);

            // Variable para almacenar el nuevo valor
            string nuevoValor;

            switch(opcion) {
                case 1:
                    cout << "Ingrese el nuevo nombre: ";
                    cin.ignore(); // Ignorar el salto de línea pendiente en el búfer de entrada
                    getline(cin, nuevoValor);
                    temp->nombre = nuevoValor;
                    cout << "Nombre actualizado con éxito." << endl;
                    break;
                case 2:
                    cout << "Ingrese el nuevo apellido: ";
                    cin.ignore();
                    getline(cin, nuevoValor);
                    temp->apellido = nuevoValor;
                    cout << "Apellido actualizado con éxito." << endl;
                    break;
                case 3:
                    cout << "Ingrese la nueva contraseña: ";
                    cin.ignore();
                    getline(cin, nuevoValor);
                    temp->contrasena = nuevoValor;
                    cout << "Contraseña actualizada con éxito." << endl;
                    break;
                case 4:
                    cout << "Ingrese el nuevo puesto: ";
                    cin.ignore();
                    getline(cin, nuevoValor);
                    temp->puesto = nuevoValor;
                    cout << "Puesto actualizado con éxito." << endl;
                    break;
                default:
                    cout << "Opción no válida. No se ha realizado ninguna modificación." << endl;
                    break;
            }
            return;  // Salir de la función después de actualizar el empleado
        }
        temp = temp->siguiente;
    }
    cout << "Empleado con ID " << id << " no encontrado." << endl;
}

void eliminarEmpleado(Empleado*& head, int id) {
    if (head == nullptr) {
        cout << "Lista vacía, no se puede eliminar." << endl;
        return;
    }

    if (head->idEmpleado == id) {
        Empleado* temp = head;
        head = head->siguiente;
        delete temp;
        cout << "Empleado eliminado con éxito." << endl;
        return;
    }

    Empleado* actual = head;
    Empleado* anterior = nullptr;

    while (actual != nullptr && actual->idEmpleado != id) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == nullptr) {
        cout << "Empleado con ID " << id << " no encontrado." << endl;
        return;
    }

    anterior->siguiente = actual->siguiente;
    delete actual;
    cout << "Empleado eliminado con éxito." << endl;
}

int mostrarMenu() {
    int opcion;

    cout << "Menu de opciones:\n";
    cout << "1. Agregar empleado\n";
    cout << "2. Mostrar empleados\n";
    cout << "3. Actualizar empleado\n";
    cout << "4. Eliminar empleado\n";
    cout << "5. Salir\n";
    cout << "Ingrese una opcion: ";
    cin >> opcion;

    return opcion;
}

int main() {
    Empleado* listaEmpleados = nullptr; 
    int opcion = 0;

    cout << "Creando el primer empleado..." << endl;
    Empleado* empleado1 = crearEmpleado();
    agregarEmpleado(listaEmpleados, empleado1);

    // Crear y agregar el segundo empleado
    cout << "Creando el segundo empleado..." << endl;
    Empleado* empleado2 = crearEmpleado();
    agregarEmpleado(listaEmpleados, empleado2);

    mostrarEmpleados(listaEmpleados);
    
    do {
        opcion = mostrarMenu(); // Llama a la función de menú

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
                cout << "Ingrese el ID del empleado a actualizar: ";
                cin >> id;
                actualizarEmpleado(listaEmpleados, id);
                break;
            }
            case 4: {
                int id;
                cout << "Ingrese el ID del empleado a eliminar: ";
                cin >> id;
                eliminarEmpleado(listaEmpleados, id);
                break;
            }
            case 5:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo." << endl;
                break;
        }
    } while (opcion != 5);

    system("pause");
    return 0;
}