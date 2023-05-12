#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
using namespace std;

struct nodo {
    int valu;
    char nom[30];
    int tiempo ;
    int ronda;
     int altura;
   float prom;
     int tiempototal;
    nodo *izq;
    nodo *der;
};



nodo *raiz = NULL;
struct promedio {
   // float prom;
   nodo *apunta;
};
promedio *raiz2,*auxp;

int altura(nodo *N) {
    if (N == NULL)
        return 0;
    return N->altura;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

nodo* rotarDerecha(nodo* y) {
    nodo* x = y->izq;
    nodo* T2 = x->der;

    x->der = y;
    y->izq = T2;

    y->altura = max(altura(y->izq), altura(y->der)) + 1;
    x->altura = max(altura(x->izq), altura(x->der)) + 1;

    return x;
}

nodo* rotarIzquierda(nodo* x) {
    nodo* y = x->der;
    nodo* T2 = y->izq;

    y->izq = x;
    x->der = T2;

    x->altura = max(altura(x->izq), altura(x->der)) + 1;
    y->altura = max(altura(y->izq), altura(y->der)) + 1;

    return y;
}

int obtenerBalance(nodo* N) {
    if (N == NULL)
        return 0;
    return altura(N->izq) - altura(N->der);
}



nodo* posicionar(nodo* aux, nodo* aux2) {
    if (aux2 == NULL)
        return aux;

    if (aux->valu < aux2->valu)
        aux2->izq = posicionar(aux, aux2->izq);
    else if (aux->valu > aux2->valu)
        aux2->der = posicionar(aux, aux2->der);
    else // Si el valor ya existe, no se inserta
        return aux2;

    aux2->altura = 1 + max(altura(aux2->izq), altura(aux2->der));

    int balance = obtenerBalance(aux2);

    // Rotaciones
    if (balance > 1 && aux->valu < aux2->izq->valu)
        return rotarDerecha(aux2);

    if (balance < -1 && aux->valu > aux2->der->valu)
        return rotarIzquierda(aux2);

    if (balance > 1 && aux->valu > aux2->izq->valu) {
        aux2->izq = rotarIzquierda(aux2->izq);
        return rotarDerecha(aux2);
    }

    if (balance < -1 && aux->valu < aux2->der->valu) {
        aux2->der = rotarDerecha(aux2->der);
        return rotarIzquierda(aux2);
    }

    return aux2;
}


int preorden(nodo *aux3) {
    if (aux3 != NULL) {
        cout << "Numero de camisa: " << aux3->valu << " "
             << "Nombre del Atleta: " << aux3->nom << " "
             << "Tiempo: " << aux3->tiempo << endl;
        preorden(aux3->izq);
        preorden(aux3->der);
    }
    return 0;
}
/*
void inorden_inverso(nodo* aux3) {
    if (aux3 == NULL) {
        return;
    }
    inorden_inverso(aux3->der);  // primero visitar hijo derecho
    cout << "Promedio: " << aux3->tiempototal << endl;
    inorden_inverso(aux3->izq);  // luego visitar hijo izquierdo
}
*/
void inordenInverso(nodo* raiz) {
    if (raiz == NULL) {
        return;
    }
    inordenInverso(raiz->izq);  // primero visitar hijo izquierdo
    cout << "Número de camisa: " << raiz->valu << endl;
    cout << "Nombre del atleta: " << raiz->nom << endl;
    cout << "Tiempo total: " << raiz->tiempototal << endl;
    cout << "Promedio de tiempos: " << raiz->prom << endl << endl;
    inordenInverso(raiz->der);  // luego visitar hijo derecho
}


/*
int errorp(nodo *aux){
     aux->prom = aux->tiempototal/2;	

	while(aux != NULL) {
	cout << "Es el corredor: " << aux->nom << " :: "<<aux->prom<<endl;
	break;
	
	}
	return  0;
}
*/









/*
int registraTimp() {
    int numcorredor;
    int bandera = 0;
    preorden(raiz);
    cout << "Registre el número del corredor:" << endl;
    cin >> numcorredor;
    nodo *aux = raiz;

    while (aux != NULL && aux->valu != numcorredor) {
        if (numcorredor < aux->valu) {
            aux = aux->izq;
        }
        else {
            aux = aux->der;
        }
    }

    if (aux != NULL) {
        bandera = 1;
        aux->ronda++;
        cout << "Es el corredor: " << aux->nom << " :: "<<" ronda: "<<aux->ronda<<" "<<"Tiempo: "<< aux->tiempo << endl;
        cout << "Registre el tiempo de la última vuelta:" << endl;
        cin >> aux->tiempo;
        
          
           
		    if(aux->ronda>=2){
                //promedio =  aux->tiempototal/aux->ronda;
                //calcularPromedio(aux);
                aux->tiempototal = aux->tiempototal + aux->tiempo/aux->ronda;
               
            }  
            
    }
    else {
        cout << "El corredor no existe" << endl;
    }
    return 0;
}
*/
int registraTimp() {
    int numcorredor;
    int bandera = 0;
    preorden(raiz);
    cout << "Registre el número del corredor:" << endl;
    cin >> numcorredor;
    nodo *aux = raiz;

    while (aux != NULL && aux->valu != numcorredor) {
        if (numcorredor < aux->valu) {
            aux = aux->izq;
        }
        else {
            aux = aux->der;
        }
    }

    if (aux != NULL) {
        bandera = 1;
        aux->ronda++;
        cout << "Es el corredor: " << aux->nom << " :: "<<" ronda: "<<aux->ronda<<" "<<"Tiempo: "<< aux->tiempo << endl;
        cout << "Registre el tiempo de la última vuelta:" << endl;
        cin >> aux->tiempo;
        aux->tiempototal += aux->tiempo;
        aux->prom = aux->tiempototal / aux->ronda;
    }
    else {
        cout << "No se encontró el corredor." << endl;
    }

    if (bandera == 1) {
        return 0;
    }
    else {
        return 1;
    }
    
    inordenInverso(raiz); // llamar a la función para imprimir los resultados en orden descendente
}





int registrar() {
   //nodo *aux = new nodo;
    nodo *aux  = (struct nodo *) malloc (sizeof(struct nodo));
    aux->tiempo=0;
    aux->ronda=0;
    aux->prom=0;
    aux->tiempototal=0;
    aux->altura=1;
	
    cout << "Ingresar el mnumero de Camisa: ";
    cin >> aux->valu;
    cout << "Ingresar el nombre del Atleta: ";
    cin >> aux->nom;

    aux->izq = NULL;
    aux->der = NULL;

    if (raiz == NULL) {
        raiz = aux;
    }
    else {
        posicionar(aux, raiz);
    }
    return 0;
}


  int cargar(){
  	
  	const int total = 200; // Número total de elementos a procesar
  const int delay = 1000000; // Tiempo de espera entre iteraciones en microsegundos

  for (int i = 0; i <= total; ++i) {
    // Limpiar la línea de la barra de progreso
    std::cout << "\r";
    std::cout.flush();

    // Imprimir la barra de progreso
    int progress = i * 100 / total;
    std::cout << "[";

    for (int j = 0; j < 50; ++j) {
      if (j * 2 < progress) {
        std::cout << "=";
      } else if (j * 2 == progress) {
        std::cout << ">";
      } else {
        std::cout << " ";
      }
    }

    std::cout << "] " << progress << "%" << std::flush;

    // Retardo para simular el procesamiento de un elemento
    for (int k = 0; k < delay; ++k) {}

  }

  std::cout << std::endl;
  return 0;
  	
  	
  	
  	
  }
 
 
 
 

int main() {
	
	cargar();
	system("cls");
    int opc = 0;
    do {
        cout<< "\nMenu" << endl;
        cout<<"1. Registar datos" << endl;
        cout<<"2. Mostrar lista" << endl;
        cout<<"3. Registrar tiempo"<<endl;
        cout<<"4. Promedio "<<endl;
        cout<<"5. Salir"<<endl;
        
        cin>>opc;
        	cout<<"\n";
        system("cls");
        switch(opc){
            case 1:
              	cout<<"registar datos del personal "<<endl;
				    	registrar();	

				  // preorden(raiz);
				break;
            case 2:
            		//cout<<"Inorden"<<endl; inorden(raiz);
            	 preorden(raiz);
			 
			break;
            case 3:
            	 	//cout<<"Postorden"<<endl;postorden(raiz);
                  registraTimp();
                break;
                 
            case 4:
            	 	//mostraP();
            	 	 //inorden(raiz);
            	 	 //inorden_inverso(raiz);
            	 	 
				inordenInverso(raiz);
            	 	break;
            	 	
            	 	
            	 	
                case 5:
                	
				 cout<<"Hasta pronto  "; 
                break;
                default:
                    cout<<"Opcion no valida....";
                break;    
            }

        }while(opc!=5);
		} 
        
