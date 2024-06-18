//Profesor, disculpe la molestia, era para recordarle que le falta una nota por revisar del compañero Daniel Torreglosa, del 1er corte.
//POR FAVOR REVISAR EL MENSAJE DE ARRIBA!
#include <iostream>
#include <malloc.h>
using namespace std;

struct viaje {
    char nombreviaje[50];
    char destino[50];
    int precio = 0, capacidad = 0;
    int altura, nmatricula = 0, IdViaje = 0;

    viaje *izq, *der;
};

viaje *raiz, *aux2, *aux;

struct pasajero {
    char destinopsj[50];
    int valorpsj;
    pasajero* sig;
};

pasajero *aux1, *cab, *alfa, *al1, *al2;

int registrarpsj() {
    al1 = (struct pasajero *)malloc(sizeof(struct pasajero));

    cout << "Registre su destino: " << endl;
    cin >> al1->destinopsj; 

    cout << "Registre el valor del viaje: " << endl;
    cin >> al1->valorpsj;

    al1->sig = NULL;

    if (alfa == NULL) {
        alfa = al1;
    } else {
        al2 = alfa;

        while (al2->sig != NULL) {
            al2 = al2->sig;
        }

        al2->sig = al1;  
    }
    return 0;
}

int listarpsj() {
    al1 = alfa;

    while (al1 != NULL) {
        cout << "Su destino es: " << al1->destinopsj << endl;
        cout << "Su valor es: " << al1->valorpsj << endl << endl;
        al1 = al1->sig;  
    }

    return 0;
}

int obtenerAltura(viaje *n) {
    if (n == NULL) {
        return 0;
    }
    return n->altura;
}

int mayor(int a, int b) {
    return (a > b) ? a : b;
}

int obtenerBalance(viaje *n) {
    if (n == NULL) {
        return 0;
    }
    return obtenerAltura(n->izq) - obtenerAltura(n->der);
}

viaje* rotarDerecha(viaje *y) {
    viaje *x = y->izq;
    viaje *T2 = x->der;

    x->der = y;
    y->izq = T2;

    y->altura = mayor(obtenerAltura(y->izq), obtenerAltura(y->der)) + 1;
    x->altura = mayor(obtenerAltura(x->izq), obtenerAltura(x->der)) + 1;

    return x;
}

viaje* rotarIzquierda(viaje *x) {
    viaje *y = x->der;
    viaje *T2 = y->izq;

    y->izq = x;
    x->der = T2;

    x->altura = mayor(obtenerAltura(x->izq), obtenerAltura(x->der)) + 1;
    y->altura = mayor(obtenerAltura(y->izq), obtenerAltura(y->der)) + 1;

    return y;
}

viaje* insertar(viaje* nodo) {
    if (nodo == NULL) {
        return aux2;
    }

    if (aux2->IdViaje < nodo->IdViaje) {
        nodo->izq = insertar(nodo->izq);
    } else if (aux2->IdViaje > nodo->IdViaje) {
        nodo->der = insertar(nodo->der);
    } else {
        return nodo;
    }

    nodo->altura = 1 + mayor(obtenerAltura(nodo->izq), obtenerAltura(nodo->der));

    int balance = obtenerBalance(nodo);

    if (balance > 1 && aux2->IdViaje < nodo->izq->IdViaje) {
        return rotarDerecha(nodo);
    }

    if (balance < -1 && aux2->IdViaje > nodo->der->IdViaje) {
        return rotarIzquierda(nodo);
    }

    if (balance > 1 && aux2->IdViaje > nodo->izq->IdViaje) {
        nodo->izq = rotarIzquierda(nodo->izq);
        return rotarDerecha(nodo);
    }

    if (balance < -1 && aux2->IdViaje < nodo->der->IdViaje) {
        nodo->der = rotarDerecha(nodo->der);
        return rotarIzquierda(nodo);
    }

    return nodo;
}

int inorden(viaje *nodo) {
    if (nodo != NULL) {
        inorden(nodo->izq);
        cout << nodo->IdViaje << " ";
        inorden(nodo->der);
    }
    return 0;
}

int obtenerFecha() {
    int year, mes, dia;
    cout << "por favor registre la fecha actual: " << endl;
    cout << "Ingrese el año (4 dígitos): ";
    cin >> year;
    cout << "Ingrese el mes (1-12): ";
    cin >> mes;
    cout << "Ingrese el día (1-31): ";
    cin >> dia;

    if (mes < 1 || mes > 12 || dia < 1 || dia > 31) {
        cout << "Fecha no válida. Inténtelo nuevamente." << endl;
        return obtenerFecha();
    }

    int fecha = year * 10000 + mes * 100 + dia;
    return fecha;
}

int registrar() {
    aux2 = (struct viaje*) malloc(sizeof(struct viaje));
    cout << "Ingrese el valor de su viaje: "; 
    cin >> aux2->precio;
    cout << "Ingrese el destino de la embarcacion: "; 
    cin >> aux2->destino; 
    cout << "Ingrese el numero de matricula de la embarcacion: "; 
    cin >> aux2->nmatricula;
    cout << "Ingrese el nombre de la embarcacion: "; 
    cin >> aux2->nombreviaje; 
    aux2->IdViaje = obtenerFecha();
    cout << "Ingrese el numero de pasajeros que se embarcaran: "; 
    cin >> aux2->capacidad;
    aux2->izq = NULL; 
    aux2->der = NULL; 
    aux2->altura = 1;
    raiz = insertar(raiz);
    return 0;
}


int listarViaje(viaje* viaje_actual) {
    if(viaje_actual != NULL) {
        cout << "INFORMACION DE REGISTROS: " << endl << endl;
        cout << "Precio: " << aux2->precio << endl;
        cout << "Destino: " << aux2->destino << endl;
        cout << "MATRICULA: " << aux2->nmatricula << endl;
        cout << "Nombre de la embarcacion: " << aux2->nombreviaje << endl;
        cout << "ID del viaje: " << aux2->IdViaje << endl;
        cout << "Capacidad de viajeros: " << aux2->capacidad << endl << endl;
        listarViaje(viaje_actual->izq);
        listarViaje(viaje_actual->der);
    }  
    return 0;
}

viaje* buscarIdViaje(viaje* nodo, int idBusqueda) {
    if (nodo == NULL || nodo->IdViaje == idBusqueda) {
        return nodo;
    }
    
    if (idBusqueda < nodo->IdViaje) {
        return buscarIdViaje(nodo->izq, idBusqueda);
    } else {
        return buscarIdViaje(nodo->der, idBusqueda);
    }
}

int buscarYMostrarIdViaje(viaje* nodo, int idBusqueda) {
    viaje* resultado = buscarIdViaje(nodo, idBusqueda);
    if (resultado != NULL) {
        cout << "Viaje encontrado: " << endl;
        cout << "Precio: " << resultado->precio << endl;
        cout << "Destino: " << resultado->destino << endl;
        cout << "MATRICULA: " << resultado->nmatricula << endl;
        cout << "Nombre de la embarcacion: " << resultado->nombreviaje << endl;
        cout << "ID del viaje: " << resultado->IdViaje << endl;
        cout << "Capacidad de viajeros: " << resultado->capacidad << endl << endl;
        return 1;
    } else {
        cout << "Viaje no encontrado." << endl;
        return 0;
 }
}

int ubicar(viaje *aux3, int aguja) {
    if(aux3->IdViaje == aguja) {
        aux = aux3;
        return 0;
    } else {
        if(aux3->izq != NULL) {
            ubicar(aux3->izq, aguja);
        }
        if(aux3->der != NULL) {
            ubicar(aux3->der, aguja);
        }
    }
    return 0;
}

//ubicar padre
int ubicarpadre(viaje *padre) {
    if((padre->izq != NULL) && (padre->izq != aux)) {
        ubicarpadre(padre->izq);
    }
    if(padre->izq == aux) {
        aux2 = padre;
    }
    if((padre->der != NULL) && (padre->der != aux)) {
        ubicarpadre(padre->der);
    }
    if(padre->der == aux) {
        aux2 = padre;
    }
    return 0;
}

//casos de eliminacion 
int casouno() {
    if(aux != raiz) {
        ubicarpadre(raiz);
    }
    if(aux2->izq == aux) {
       aux2->izq = NULL;
    } else if(aux2->der == aux) {
        aux2->der = NULL;
    }
    free(aux);
    return 0;
}

int casodos() {
    if(aux != raiz) {
       ubicarpadre(raiz);
    }
    if(aux2->izq == aux) {
        if (aux->izq != NULL)
            aux2->izq = aux->izq;
        else if (aux->der != NULL)
            aux2->izq = aux->der;
    } else if (aux2->der == aux) {
        if (aux->izq != NULL)
            aux2->der = aux->izq;
        else if (aux->der != NULL)
            aux2->der = aux->der;
    }
    free(aux);
    return 0;
}

int casotres() {
    if(aux != raiz) {
       ubicarpadre(raiz);
    }
    if(aux2->der == aux) {
        if (aux->der != NULL)
            aux2->der = aux->der;
        else if (aux->izq != NULL)
            aux2->der = aux->izq;
    } else if (aux2->izq == aux) {
        if (aux->der != NULL)
            aux2->izq = aux->der;
        else if (aux->izq != NULL)
            aux2->izq = aux->izq;
    }
    free(aux);
return 0;
}

int eliminar() {
    int buscar;
    cout << "Ingrese el valor del codigo que desea eliminar..." << endl;
    cin >> buscar;

    ubicar(raiz, buscar);

    if (aux == NULL) {
        cout << "El viaje con ID " << buscar << " no fue encontrado." << endl;
        return 0;
    }

    if (aux->der == NULL && aux->izq == NULL) {
        cout << "Eliminando..." << endl;
        casouno();
    } else if (aux->der == NULL || aux->izq == NULL) {
        cout << "Eliminando..." << endl;
        casodos();
    } else {
        cout << "Eliminando..." << endl;
        casotres();
    }

 return 0;
}

int main() {
    int op = 0;
    do {
        cout << "MENU PRINCIPAL: " << endl;
        cout << "1. REGISTRAR VIAJE" << endl;
        cout << "2. LISTADO DE VIAJES" << endl;
        cout << "3. BUSCAR VIAJE" << endl;
        cout << "4. ELIMINAR VIAJE" << endl;
        cout << "5. REGISTRAR PASAJERO A UN VIAJE" << endl;
        cout << "6. LISTADO DE PASAJEROS DEL VIAJE" << endl;
        cout << "7. SALIR" << endl << endl;
        cin >> op;

        switch (op) {   
            case 1:
                registrar();
                break;
            case 2: 
                listarViaje(raiz); 
                break;
                
            case 3: {
                int idBuscar;
                cout << "Ingrese el ID del viaje que desea buscar: ";
                cin >> idBuscar;
                int encontrado = buscarYMostrarIdViaje(raiz, idBuscar);
                if (encontrado) {
                    cout << "Búsqueda exitosa." << endl;
                } else {
                    cout << "No se encontró ningún viaje con el ID " << idBuscar << "." << endl;
                }
                break;
            }

            case 4: 
                eliminar(); 
                break;

                
                
                
            case 5: 
                registrarpsj();
                break;
            case 6: 
                listarpsj();
            break;
            
            case 7: 
            cout<< "Saliendo......." <<endl; 
            break;
            
            default: cout<<" la opcion esta en desarrollo..."<<endl; 
            break;
        }
    } while (op!=7);
    return 0;
}
