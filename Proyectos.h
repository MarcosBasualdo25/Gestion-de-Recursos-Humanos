#include <iostream>
#include <string>
#include "GestionEmpleados.h"
#include "gotoxy.h"
#include <limits>
#include <ctime>

using namespace std;

struct ArbolEmpleado {
    Empleado* empleado;
    ArbolEmpleado* izq;
    ArbolEmpleado* der;
};

struct NodoLista {
    ArbolEmpleado* raiz;
    string nombreProy;
    NodoLista* siguiente;
};

// Función para buscar un empleado por ID
Empleado* buscarEmpleado(int id, Empleado* headEmpleados) {
    Empleado* actual = headEmpleados;
    while (actual) {
        if (actual->idEmpleado == id)
            return actual;
        actual = actual->siguiente;
    }
    return nullptr;
}

// Función para crear un proyecto
NodoLista* crearProyecto(NodoLista* lista) {
    NodoLista* nuevoNodo = new NodoLista();
    nuevoNodo->raiz = nullptr;
    cout << "Nombre del proyecto: "; cin >> nuevoNodo->nombreProy;
    nuevoNodo->siguiente = lista;
    cout << "Nuevo proyecto creado.\n";
    return nuevoNodo;
}

// Función para agregar un empleado al árbol
void agregarEmpleado(ArbolEmpleado*& raiz, Empleado* empleado) {
    if (raiz == nullptr) {
        if (empleado->puesto == "director de proyecto") {
            raiz = new ArbolEmpleado{empleado, nullptr, nullptr};
            cout << "Director de proyecto agregado como raíz del árbol.\n";
        } else {
            cout << "Primero agregue un director de proyecto.\n";
        }
    } else {
        if (empleado->puesto == "gerente de calidad") {
            if (raiz->izq == nullptr) {
                raiz->izq = new ArbolEmpleado{empleado, nullptr, nullptr};
                cout << "Gerente de calidad agregado.\n";
            } else {
                cout << "Ya existe un gerente de calidad en este proyecto.\n";
            }
        } else if (empleado->puesto == "gerente de desarrollo") {
            if (raiz->der == nullptr) {
                raiz->der = new ArbolEmpleado{empleado, nullptr, nullptr};
                cout << "Gerente de desarrollo agregado.\n";
            } else {
                cout << "Ya existe un gerente de desarrollo en este proyecto.\n";
            }
        } else if (empleado->puesto == "lider de equipo de QA") {
            if (raiz->izq != nullptr && raiz->izq->empleado->puesto == "gerente de calidad") {
                if (raiz->izq->izq == nullptr) {
                    raiz->izq->izq = new ArbolEmpleado{empleado, nullptr, nullptr};
                    cout << "Líder de equipo de QA agregado.\n";
                } else {
                    cout << "Ya existe un líder de equipo de QA.\n";
                }
            } else {
                cout << "Primero agregue un gerente de calidad.\n";
            }
        } else if (empleado->puesto == "lider de equipo de desarrollo") {
            if (raiz->der != nullptr && raiz->der->empleado->puesto == "gerente de desarrollo") {
                if (raiz->der->izq == nullptr) {
                    raiz->der->izq = new ArbolEmpleado{empleado, nullptr, nullptr};
                    cout << "Líder de equipo de desarrollo agregado.\n";
                } else {
                    cout << "Ya existe un líder de equipo de desarrollo.\n";
                }
            } else {
                cout << "Primero agregue un gerente de desarrollo.\n";
            }
        } else {
            cout << "Puesto no reconocido.\n";
        }
    }
    system("pause");
}

// Función para borrar un árbol
void borrarArbol(ArbolEmpleado*& raiz) {
    if (raiz != nullptr) {
        borrarArbol(raiz->izq); // Borrar subárbol izquierdo
        borrarArbol(raiz->der); // Borrar subárbol derecho
        delete raiz; // Borrar nodo actual
        raiz = nullptr; // Establecer el puntero a nullptr
    }
}

// Función para borrar el árbol de un proyecto
void borrarArbolProyecto(NodoLista* listaProyectos) {
    string nameProy;
    system("cls");
    cout << "Nombre de proyecto: ";
    cin.ignore();
    getline(cin, nameProy);
    while (listaProyectos != nullptr && nameProy != listaProyectos->nombreProy) {
        listaProyectos = listaProyectos->siguiente;
    }
    if (listaProyectos == nullptr) {
        cout << "No existe el proyecto ingresado" << endl;
    } else {
        borrarArbol(listaProyectos->raiz);
        cout << "El árbol del proyecto ha sido borrado." << endl;
    }
    system("pause");
}

void mostrarArbol(ArbolEmpleado* arbol, int cont) {
    if (arbol != nullptr) {
        mostrarArbol(arbol->der, cont + 1);
        for (int i = 0; i < cont; i++) {
            cout << "\t";
        }
        cout << arbol->empleado->nombre << " " << arbol->empleado->apellido << endl;
        mostrarArbol(arbol->izq, cont + 1);
    }
    return;
}

void mostrarArbolProyecto(NodoLista* listaProyectos) {
    string nameProy;
    system("cls");
    cout << "Nombre de proyecto: "; cin >> nameProy;
    while (listaProyectos != nullptr && nameProy != listaProyectos->nombreProy) {
        listaProyectos = listaProyectos->siguiente;
    }
    if (listaProyectos == nullptr) {
        cout << "No existe el proyecto ingresado" << endl;
    } else {
        mostrarArbol(listaProyectos->raiz, 0);
    }
    system("pause");
}

void empleadoAProyecto(Empleado* headEmpleados, NodoLista* listaProyectos) {
    string nameProy;
    system("cls");
    cout << "Nombre de proyecto: "; cin >> nameProy;
    while (listaProyectos != nullptr && nameProy != listaProyectos->nombreProy) {
        listaProyectos = listaProyectos->siguiente;
    }
    if (listaProyectos == nullptr) {
        cout << "No existe el proyecto ingresado" << endl;
    } else {
        int id;
        cout << "Ingrese el ID del empleado: ";
        cin >> id;
        Empleado* empleado = buscarEmpleado(id, headEmpleados);
        if (empleado) {
            int rol;
            cout << "Seleccione el rol del empleado:\n";
            cout << "1. Director de proyecto\n";
            cout << "2. Gerente\n";
            cout << "3. Líder de equipo\n";
            cout << "Ingrese el número del rol: ";
            cin >> rol;

            switch (rol) {
                case 1:
                    if (listaProyectos->raiz == nullptr) {
                        empleado->puesto = "director de proyecto";
                        agregarEmpleado(listaProyectos->raiz, empleado);
                    } else {
                        cout << "Ya existe un director de proyecto en este proyecto.\n";
                    }
                    break;
                case 2:
                    cout << "Seleccione el tipo de gerente:\n";
                    cout << "1. Gerente de desarrollo\n";
                    cout << "2. Gerente de calidad\n";
                    cout << "Ingrese el número del tipo de gerente: ";
                    cin >> rol;
                    if (rol == 1) {
                        if (listaProyectos->raiz != nullptr && listaProyectos->raiz->der == nullptr) {
                            empleado->puesto = "gerente de desarrollo";
                            agregarEmpleado(listaProyectos->raiz, empleado);
                        } else {
                            cout << "No se pudo agregar ese gerente de desarrollo en este proyecto.\n";
                        }
                    } else if (rol == 2) {
                        if (listaProyectos->raiz != nullptr && listaProyectos->raiz->izq == nullptr) {
                            empleado->puesto = "gerente de calidad";
                            agregarEmpleado(listaProyectos->raiz, empleado);
                        } else {
                            cout << "No se pudo agregar ese gerente de calidad en este proyecto.\n";
                        }
                    } else {
                        cout << "Opción no válida.\n";
                    }
                    break;
                case 3:
                    cout << "Seleccione el tipo de líder de equipo:\n";
                    cout << "1. Líder de equipo de QA\n";
                    cout << "2. Líder de equipo de desarrollo\n";
                    cout << "Ingrese el número del tipo de líder de equipo: ";
                    cin >> rol;
                    if (rol == 1) {
                        if (listaProyectos->raiz != nullptr && listaProyectos->raiz->izq != nullptr && listaProyectos->raiz->izq->izq == nullptr) {
                            empleado->puesto = "lider de equipo de QA";
                            agregarEmpleado(listaProyectos->raiz, empleado);
                        } else {
                            cout << "No se puedo agregar ese lider de equipo de QA en este proyecto.\n";
                        }
                    } else if (rol == 2) {
                        if (listaProyectos->raiz != nullptr && listaProyectos->raiz->der != nullptr && listaProyectos->raiz->der->izq == nullptr) {
                            empleado->puesto = "lider de equipo de desarrollo";
                            agregarEmpleado(listaProyectos->raiz, empleado);
                        } else {
                            cout << "No se puedo agregar ese lider de equipo de desarrollo en este proyecto.\n";
                        }
                    } else {
                        cout << "Opción no válida.\n";
                    }
                    break;
                default:
                    cout << "Opción no válida.\n";
            }
        } else {
            cout << "Empleado no encontrado.\n";
        }
    }
    system("pause");
}

// Función para mostrar todos los proyectos creados
void mostrarProyectos(NodoLista* listaProyectos) {
    system("cls");
    if (listaProyectos == nullptr) {
        cout << "No hay proyectos creados." << endl;
    } else {
        cout << "Proyectos creados:" << endl;
        while (listaProyectos != nullptr) {
            cout << "- " << listaProyectos->nombreProy << endl;
            listaProyectos = listaProyectos->siguiente;
        }
    }
    system("pause");
}

Empleado* crearYAgregarEmpleado(Empleado*& head, Empleado*& tail, string nombre, string apellido, string contrasena, string puesto) {
    Empleado* nuevoEmpleado = new Empleado();
    // Asignar valores al nuevo empleado
    nuevoEmpleado->nombre = nombre;
    nuevoEmpleado->apellido = apellido;
    nuevoEmpleado->contrasena = contrasena;
    nuevoEmpleado->puesto = puesto;
    nuevoEmpleado->siguiente = nullptr; // Será el último
    nuevoEmpleado->anterior = nullptr;
    nuevoEmpleado->pilaEvaluaciones = nullptr;
    nuevoEmpleado->pilaAsistencias = nullptr;

    // Asignación del ID y enlace a la lista
    if (head == nullptr) {
        // Si la lista está vacía, el nuevo empleado es tanto el head como el tail
        nuevoEmpleado->idEmpleado = 1;
        head = nuevoEmpleado;
        tail = nuevoEmpleado;
    } else {
        // Si ya hay empleados, agregar al final
        nuevoEmpleado->idEmpleado = tail->idEmpleado + 1; // El ID será uno más que el último empleado
        nuevoEmpleado->anterior = tail;                  // El anterior del nuevo empleado es el tail actual
        tail->siguiente = nuevoEmpleado;                 // El siguiente del tail actual es el nuevo empleado
        tail = nuevoEmpleado;                            // Actualizar el tail para que apunte al nuevo empleado
    }
    string user = nombre + "." + apellido;
    lower(user);
    crearUsuario(ListaUsers, user, nuevoEmpleado->contrasena, "EMPLEADO", nuevoEmpleado->idEmpleado);
    return nuevoEmpleado;
}