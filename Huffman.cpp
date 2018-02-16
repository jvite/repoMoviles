#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

using namespace std;

string palCifrada;

class Nodo{
	public:
		char caracter;
		string en;
		int frecuen;
		Nodo *izquierda=NULL, *derecha=NULL, *siguiente=NULL, *padre=NULL;
};
Nodo *encrip;

class Arbol{
	public:
		Nodo *inicio,*bu;
	bool buscar(Nodo*, char);
	void buscar2(Nodo*, char);
	void insertar(char , int);
	void mostrar();
	void ordenarInsercion();
	void hu();
	void postOrden(Nodo *);
	void ordenarBurbuja();
	void mostrarArbol(Nodo *,int);
};

bool Arbol::buscar(Nodo *b, char bus){  //Busca un caracter
	if(b==NULL){
		return false;
	}else{
		if(b->caracter==bus){
			bu=b;
			return true;
		}else{
			b=b->siguiente;
			buscar(b,bus);
		}
	}
}

void Arbol::buscar2(Nodo *b, char bus){ //Obtiene la frecuencia de un caracter
	if(b==NULL){ //Si no hay nodos
		return;
	}else{ //Si hay nodos
		if(b->caracter==bus){ //Si el caracter is identico a buscado
			palCifrada+=b->en; //Se aumenta la frecuencia en 1
			return;
		}else{//Se evalua en los demas nodos
			buscar2(b->izquierda,bus);
			buscar2(b->derecha,bus);
		}
	}
}
void Arbol::ordenarInsercion(){ //Ordenamiento por insercion
	if (inicio!=NULL){
		int valor; //Frecuencia
		char l;//cracter
		Nodo* i=inicio;
		Nodo* j=i;
		Nodo* aux;
		
		while(i!=NULL){//Si "i" esta vacia
			aux=i; //aux toma el valor de i
			j=i->siguiente;
			while(j!=NULL){
				if (j->frecuen<aux->frecuen){
					aux=j;
				}
				j = j->siguiente;
			}
			valor=i->frecuen;//Valor toma la frecuencia de i
			l=i->caracter;// toma a frecuencia de i
			i->frecuen=aux->frecuen;//La frecuencia de i toma la frecuencia de aux
			i->caracter=aux->caracter;
			aux->frecuen=valor;
			aux->caracter=l;
			i=i->siguiente;
		}
	}
}

void Arbol::insertar(char v,int f){ //Inserta un elemento en la lista
	Nodo *nuevo=new Nodo(); //Crea un nuevo nodo
	nuevo->caracter=v;
	nuevo->frecuen=f;
	if(inicio==NULL){ //Si no hay elementos
		nuevo->padre=NULL;
		inicio=nuevo;
	}else{//Si hay elementos
		Nodo *aux,*aux2;
		aux=inicio;
		aux2=inicio;
		while(aux->siguiente != NULL){//Mientras aux en su parte siguiente sea distino de NULL
			aux=aux->siguiente;
		}
		nuevo->padre=aux;
		aux->siguiente=nuevo;
	}
}

void Arbol::mostrar(){ //Muestra el caracter con su respectiva frecuencia
	Nodo *aux;
	aux=inicio;
	while(aux !=NULL){
		cout<<aux->caracter<<" "<<aux->frecuen<<endl;
		aux=aux->siguiente;
	}
}

void Arbol::ordenarBurbuja(){ //Ordenamiento por burbuja
	Nodo *aux=NULL, *next=NULL, *aux2=new Nodo(); //Variables auxiliares
	aux=inicio;
	while(aux->siguiente!=NULL){
		next=aux->siguiente;
		while (next != NULL){
			if (aux->frecuen > next->frecuen){
				aux2->caracter = next->caracter;
				aux2->frecuen = next->frecuen;
				aux2->derecha = next->derecha;
				aux2->izquierda = next->izquierda;
				aux2->en = next->en;
				aux2->padre= next->padre;
				
				next->caracter = aux->caracter;
				next->frecuen = aux->frecuen;
				next->derecha = aux->derecha;
				next->izquierda = aux->izquierda;
				next->en = aux->en;
				next->padre=aux->padre;
				
				aux->caracter = aux2->caracter;
				aux->frecuen = aux2->frecuen;
				aux->derecha = aux2->derecha;
				aux->izquierda = aux2->izquierda;
				aux->en = aux2->en;
				aux->padre=aux2->padre;
			}
			next = next->siguiente;
		}
		aux = aux->siguiente;
		next = aux->siguiente;
	}
}

void Arbol::hu(){
	Nodo *n=new Nodo();
	Nodo *aux,*aux2;
	while(inicio->siguiente->siguiente!=NULL){
		Nodo *nuevo = new Nodo();
		Nodo *aux,*aux2;
		if(inicio!=NULL&& inicio->siguiente!=NULL){
			aux=inicio;
			aux->padre=nuevo;
			nuevo->izquierda=aux;
			aux=aux->siguiente;
			aux->padre=nuevo;
			nuevo->derecha=aux;
			nuevo->frecuen=nuevo->derecha->frecuen+nuevo->izquierda->frecuen;
			nuevo->caracter='*';
			inicio=inicio->siguiente->siguiente;
			aux=inicio;
			aux2=inicio;
			while(aux->siguiente != NULL){		
				aux=aux->siguiente;
			}
			aux->siguiente=nuevo;
			ordenarBurbuja();
		}
	}
	n->padre=NULL;
	aux=inicio;
	aux->padre=n;
	n->derecha=aux;
	aux=aux->siguiente;
	aux->padre=n;
	n->izquierda=aux;
	n->frecuen=n->derecha->frecuen+n->izquierda->frecuen;
	n->caracter='*';
	inicio=n;
}

void Arbol::postOrden(Nodo *raiz){ //Recorrido en postOrden
	if (inicio==NULL)
		cout<<"sin datos"<<endl;
	else if(raiz != NULL){ 
		if(raiz->padre==NULL){
			raiz->izquierda->en='0';
			raiz->derecha->en='1';
		}else{
			if(raiz->derecha!=NULL){
				raiz->derecha->en+=raiz->en;
				raiz->derecha->en+='1';
			}
			if(raiz->izquierda!=NULL){
				raiz->izquierda->en+=raiz->en;
				raiz->izquierda->en+='0';
			}
		}
		if(raiz->caracter!='*'){
			cout<<raiz->caracter<<" "<<raiz->en<<endl;
		}
		postOrden(raiz->izquierda);
		postOrden(raiz->derecha);
	}
}

int main(){
	Arbol *arbol =new Arbol();
	char cadena[30]="\0",*p;
	cout<<"----------ARBOL DE HUFFMAN----------"<<endl<<endl;
	cout<<"Ingrese la palabra (no se admiten espacios): ";
	cin>>cadena;
	cout<<endl;
	p=cadena;
	while(*p!='\0'){
		if(arbol->buscar(arbol->inicio,*p)){
			arbol->bu->frecuen +=1;
		}else{
			arbol->insertar(*p,1);
		}
		p++;
	}
	cout<<"-----------FRECUENCIAS-----------"<<endl;
	arbol->mostrar();
	arbol->ordenarInsercion();
	cout<<endl;
	cout<<"------------ORDENADO------------"<<endl;
	arbol->mostrar();
	cout<<endl;
	cout<<"------------CODIGO DE LA PALABRA------------"<<endl;
	arbol->hu();
	arbol->postOrden(arbol->inicio);
	p=cadena;
	while(*p!='\0'){
		arbol->buscar2(arbol->inicio,*p);
		p++;
	}
	cout<<endl;
	cout<<"Palabra normal: "<<cadena<<endl;
	cout<<"Palabra cifrada: "<<palCifrada;
}
