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
    cout<<"Nombre del proyecto: "; cin>>nuevoNodo->nombreProy;
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
void mostrarArbol(ArbolEmpleado *arbol, int cont){
    if(arbol != NULL){
        mostrarArbol(arbol->der,cont+1);
        for(int i=0;i<cont;i++){
            cout<<"\t";
        }
        cout<<arbol->empleado->nombre<<" "<<arbol->empleado->apellido<<endl;
        mostrarArbol(arbol->izq, cont+1);
    }
    return;
}
void mostrarArbolProyecto(NodoLista* listaProyectos){
    string nameProy;
    system("cls");
    cout<<"Nombre de proyecto: ";cin>>nameProy;
    while(listaProyectos != NULL && nameProy != listaProyectos->nombreProy){
        listaProyectos = listaProyectos->siguiente;
    }
    if(listaProyectos == NULL){
        cout<<"No existe el proyecto ingresado"<<endl;
    }else{
        mostrarArbol(listaProyectos->raiz,0);
    }
    system("pause");
}
void empleadoAProyecto(Empleado* headEmpleados, NodoLista* listaProyectos){
    string nameProy;
    system("cls");
    cout<<"Nombre de proyecto: ";cin>>nameProy;
    while(listaProyectos != NULL && nameProy != listaProyectos->nombreProy){
        listaProyectos = listaProyectos->siguiente;
    }
    if(listaProyectos == NULL){
        cout<<"No existe el proyecto ingresado"<<endl;
    }else{
        int opcion, id;
        if (listaProyectos == nullptr) {
            cout << "Primero cree un proyecto.\n";
        }
        cout << "Ingrese el ID del empleado: ";
        cin >> id;
        Empleado* empleado = buscarEmpleado(id, headEmpleados);
        if (empleado) {
            agregarEmpleado(listaProyectos->raiz, empleado);
        } else {
            cout << "Empleado no encontrado.\n";
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