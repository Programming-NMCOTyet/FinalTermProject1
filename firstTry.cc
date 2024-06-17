#include <iostream>
#include <malloc.h>
using namespace std;

struct viaje{

    char nombreviaje[50];
    char destino[50];
    int precio = 0, capacidad = 0, dia = 0, mes = 0, year = 0;
    int altura, nmatricula=0, IdViaje=0;

    viaje *izq, *der; 
}; 

viaje *raiz, *aux2;

struct pasajero {

    char nombrepsj[50];
    int doc = 0;
    pasajero* sig;
   
};

pasajero *aux1, *cab,*cab2, *aux ,*aux4;

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

int registrar() {

    aux2 = (struct viaje*) malloc(sizeof(struct viaje));


    
    cout << "Ingrese el valor de su viaje: "; 
    cin >> aux2->precio;

    cout << "Ingrese el destino de la embarcacion: "; 
    cin >> aux2->destino; 
    cin.ignore(1000, '\n');

    cout << "Ingrese el numero de matricula de la embarcacion: "; 
    cin >> aux2->nmatricula;

    cout << "Ingrese el nombre de la embarcacion: "; 
    cin >> aux2->nombreviaje; 
    cin.ignore(1000, '\n');
 
    cout << "Ingrese el año de registro: "; 
    cin >> aux2->year;

    cout << "Ingrese el mes de registro: "; 
    cin >> aux2->mes;

    cout << "Ingrese el dia de registro: "; 
    cin >> aux2->dia;

    cout << "Ingrese el numero de pasajeros que se embarcaran: "; 
    cin >> aux2->capacidad;

    int Idunico = aux2->nmatricula / 10000;
    aux2->IdViaje = Idunico * 100000000 + aux2->year * 10000 + aux2->mes * 100 + aux2->dia;

    aux2->izq = NULL; 
    aux2->der = NULL; 
    aux2->altura = 1;
    raiz = insertar(raiz);

    return 0;
}

int listarViaje(viaje* viaje_actual){

    if(viaje_actual !=NULL){

        
    cout << "INFORMACION DE REGISTROS: " << endl << endl;


    cout << "Precio: " << aux2->precio << endl;
    cout << "Destino: " << aux2->destino << endl;
    cout << "MATRICULA: " << aux2->nmatricula << endl;
    cout << "Nombre de la embarcacion: " << aux2->nombreviaje << endl;
    cout << "Fcha de registro: AÑO " << aux2->year << ", MES " << aux2->mes << ", DIA " << aux2->dia << endl;
    cout << "ID del viaje: " << aux2->IdViaje << endl ;
    cout << "Capacidad de viajeros: " << aux2->capacidad << endl << endl;

        listarViaje(viaje_actual->izq);
        listarViaje(viaje_actual->der);

    }  
    return 0;
}

int buscarViaje(){ 
    
    int Buscar;
    cout<<"Digite el numero de id que desea buscar: "; cin>>Buscar;
    viaje* aux3= raiz;

    while(aux3 != NULL){

        if(aux3->IdViaje == Buscar){


        cout << "INFORMACION DE REGISTROS ENCONTRADOS: " << endl << endl;

       
    cout << "Precio: " << aux2->precio << endl;
    cout << "Destino: " << aux2->destino << endl;
    cout << "MATRICULA: " << aux2->nmatricula << endl;
    cout << "Nombre de la embarcacion: " << aux2->nombreviaje << endl;
    cout << "Fcha de registro: AÑO " << aux2->year << ", MES " << aux2->mes << ", DIA " << aux2->dia << endl;
    cout << "ID del viaje: " << aux2->IdViaje << endl ;
    cout << "Capacidad de viajeros: " << aux2->capacidad << endl << endl;


         return 1;

        } else if(aux3->IdViaje < Buscar){

            aux3 = aux3->izq;

        } else{

            aux3 = aux3->der;

        }
    }
    
    cout<<"Viaje no encontrado: "<<endl;

    return 0;
}

viaje* valor_minimo(viaje* nodo){

    viaje* actual = nodo;

    while (actual && actual->izq != NULL)
    actual = actual->izq;

    return actual;
}

viaje* eliminar_viaje(viaje* nodo, int Eliminar) {

    if (nodo == NULL)

        return nodo;

    if (Eliminar < nodo->IdViaje)

        nodo->izq = eliminar_viaje(nodo->izq, Eliminar);

    else if (Eliminar > nodo->IdViaje)

        nodo->der = eliminar_viaje(nodo->der, Eliminar);

    else {

        if (nodo->izq == NULL || nodo->der == NULL) {

            viaje* temp = nodo->izq ? nodo->izq : nodo->der;

            if (temp == NULL) {
                temp = nodo;
                nodo = NULL;
            } else
                *nodo = *temp;
            free(temp);

        } else {
            viaje* temp = valor_minimo(nodo->der);
            nodo->IdViaje = temp->IdViaje;
            nodo->der = eliminar_viaje(nodo->der, temp->IdViaje);
        }
    }

    if (nodo == NULL)
        return nodo;

    nodo->altura = 1 + mayor(obtenerAltura(nodo->izq), obtenerAltura(nodo->der));

    int balance = obtenerBalance(nodo);

    if (balance > 1 && obtenerBalance(nodo->izq) >= 0)
        return rotarDerecha(nodo);

    if (balance > 1 && obtenerBalance(nodo->izq) < 0) {
        nodo->izq = rotarIzquierda(nodo->izq);
        return rotarDerecha(nodo);
    }

    if (balance < -1 && obtenerBalance(nodo->der) <= 0)
        return rotarIzquierda(nodo);

    if (balance < -1 && obtenerBalance(nodo->der) > 0) {
        nodo->der = rotarDerecha(nodo->der);
        return rotarIzquierda(nodo);
    }

    return nodo;
}

int eliminar_registro(){
    int borrar;
    cout<<"INGRESE EL ID DEL VIAJE QUE QUIERE ELIMINAR: "<<endl;
    cin>>borrar;

    viaje* nodoActual = raiz;
    viaje* padre = NULL;

    while (nodoActual != NULL) {
        if (borrar == nodoActual->IdViaje) {
            if (nodoActual->izq == NULL || nodoActual->der == NULL) {
                viaje* temp = nodoActual->izq ? nodoActual->izq : nodoActual->der;

                if (padre == NULL) {
                    raiz = temp;
                    
                } else if (padre->izq == nodoActual) {
                    padre->izq = temp;
                } else {
                    padre->der = temp;
                }

                free(nodoActual);

            } else {

                viaje* temp = valor_minimo(nodoActual->der);
                nodoActual->IdViaje = temp->IdViaje;
                nodoActual->der = eliminar_viaje(nodoActual->der, temp->IdViaje);
            }

            cout << " Viaje eliminado: ";
            return 0;

        } else if (borrar < nodoActual->IdViaje) {
            padre = nodoActual;
            nodoActual = nodoActual->izq;
        } else {
            padre = nodoActual;
            nodoActual = nodoActual->der;
        }
    }    return 0;
}


 int registrarPasajero(){

        if(cab2==NULL){
      
        cab2 = (struct  pasajero* )malloc(sizeof(struct  pasajero));

        cout << "Ingrese el nombre del pasajero: ";
        cin >> cab2->nombrepsj;

        cout << "Ingrese el documento del pasajero: ";
        cin >> cab2->doc;
        
        cab2->sig = NULL;
        return 0;


        
        }else{

       
        aux = (struct  pasajero* )malloc(sizeof(struct  pasajero));

        
        cout << "Ingrese el nombre del pasajero: ";
        cin >> aux->nombrepsj;

        cout << "Ingrese el documento del pasajero: ";
        cin >> aux->doc;
          
        
        aux->sig = NULL;
        aux4 = cab;

     while(aux4->sig !=NULL)
            aux4 = aux4->sig;
        
        aux4->sig = aux;

        aux4 = aux = NULL;

        free (aux);
        free(aux4);
          
     }
     
     return 0;
    }


int listarPasajeros() {
   

        for(aux = cab2; aux; aux = aux->sig){ 

        cout << "INFORMACION DE REGISTROS: " << endl << endl;

        cout << "El nombre del pasajero es: ";
        cin >> aux->nombrepsj;

        cout << "El documento del pasajero es: ";
        cin >> aux->doc;


        }
        return 0;


   
}





int main() {

    int op = 0;
    
    do{
        cout<<"MENU PRINCIPAL: "<<endl;
        
        cout<<"1. REGISTRAR VIAJE"<<endl;
        cout<<"2. LISTADO DE VIAJES"<<endl;
        cout<<"3. BUSCAR VIAJE"<<endl;
        cout<<"4. ELIMINAR VIAJE"<<endl;
        cout<<"5. REGISTRAR PASAJERO A UN VIAJE"<<endl;
        cout<<"6. LISTADO DE PASAJEROS DEL VIAJE"<<endl;
        cout<<"7. SALIR"<<endl << endl;
        cin >> op;

        switch (op){   
            
            case 1:
            registrar();
            break;

            case 2: 
            listarViaje(raiz); 
            break;

            case 3: 
            buscarViaje(); 
            break;

            case 4: 
            eliminar_registro(); 
            break;

            case 5: 
           
            break;

            case 6: 
           
            break;

            case 7: 
            cout<< "Saliendo......." <<endl; 
            break;
            
            default: cout<<" la opcion esta en desarrollo..."<<endl; 
            break;
        }
    } while (op!=7);
  return 0;
}
