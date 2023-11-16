#include <stdlib.h>


/*  ------------------   README   ------------------

FUNCIONES DE INTERÉS PARA EL TRABAJO PRÁCTICO "AUTOMATAS"

List createList();

    EJEMPLO: List operadores = createList(); 
        operadores es LISTA VACIA (puntero a NULL)


int listSize(List lista);

    EJEMPLO: int len = listSize(operadores);
        len sera la CANTIDAD DE OPERADORES almacenados


void push(List *lista, int data);

    EJEMPLO: push(operadores, 5);
        se agrega el 5 al final de la lista operadores


int pop(List *lista);

    EJEMPLO: int n = pop(operadores);
        n tiene el valor del ultimo operador almacenado


void enqueue(List *lista, int data);

    EJEMPLO: enqueue(operadores, 5);
        se agrega el 5 al comienzo de la lista operadores


int dequeue(List* lista);

    EJEMPLO: int n = dequeue(operadores);
        n tiene el valor del primer operador almacenado


NO SE REQUIRIERON FUNCIONES DE ACCESO POR INDICE

*/


typedef struct tNode{
    int value;
    struct tNode *next;
    struct tNode *previous;
}Node;

typedef struct {
    Node* head;
    Node* first;
    int size;
}List;

//Devuelve un nuevo nodo en heap
Node* createNode(int data){

    Node * newNode = (Node*)malloc(sizeof(Node));

    newNode->next=NULL;
    newNode->previous=NULL;
    newNode->value=data;

    return newNode;

}

//Reserva heap para una lista vacia y la devuelve
List* createList(){
    List *newList=(List*)malloc(sizeof(List));
    newList->first=NULL;
    newList->head=NULL;
    newList->size=0;
    return newList;
}

//devuelve el tamanio de la lista
int listSize(List* lista){

    return lista->size;

}

Node* getNode(List* lista, int index){

    //chequeo que el index sea valido
    if( index>=listSize(lista) || index<0 ){
        return NULL;
    }

    Node* askedNode=lista->first;

    //recorro desde el primer nodo hasta el pedido
    for(int i=0;i<index;i++){
        askedNode=askedNode->next;
    }

    return askedNode;
}

//devuelve el ultimo nodo de la lista
Node* lastNode(List *lista){

    Node* askedNode = lista->head;

    return askedNode;
}

//asigna memoria dinamica, creando un nodo y agregandolo al final
void push(List *lista, int data){

    Node* newNode = createNode(data);

    if(listSize(lista)==0){
        //si la lista esta vacia, el primer nodo es el nuevo
        lista->first=newNode;
    }else{
        //sino, el nuevo nodo tiene un nodo anterior. Se lo asigna
        newNode->previous=lista->head;
        //y el ultimo de la cola tiene como nuevo siguiente al nuevo nodo
        (lista->head)->next=newNode;
    }
    //en ambos casos, el ultimo nodo pasa a ser el nuevo
    lista->head=newNode;
    lista->size++;
}

//quita el ultimo nodo de la lista y devuelve el valor almacenado
    //devuelve -1 si la lista estaba vacia
int pop(List *lista){
   
    int count=listSize(lista);    

    //me aseguro de que la lista no este vacia
    if(count==0){
        return -1;
    }

    int value;

    //si solo hay un elemento en la lista se elimina
    if(count==1){

        value=(lista->head)->value;
        free(lista->head);
        lista->first=NULL;
        lista->head=NULL;

    }else{

        //sino, buscamos el ultimo
        Node* popped = lastNode(lista);
            //el nuevo ultimo es el previo al extraido
        lista->head=popped->previous;
        (lista->head)->next=NULL;
            //se devuelve el valor del extraido
        value=popped->value;
        free(popped);
    }

    lista->size--;
    return value;

}

void enqueue(List *lista, int data){
    
    Node* newNode = createNode(data);

    //hago que el siguiente al nuevo nodo sea el primero de la lista
    newNode->next=lista->first;

    if(lista->first==NULL){
        //la lista esta vacia
        lista->head=newNode;
    }else{
        //la lista tiene al menos un elemento
            //el previo al primero ahora es el nuevo
        (lista->first)->previous=newNode;
    }

    //y ajusto lista para que apunte al nuevo primer nodo
    lista->first=newNode;

    lista->size++;
}

//devuelve el primer elemento
    //-1 si esta vacia
int dequeue(List* lista){

    if(listSize(lista)==0){
        //la lista esta vacia
        return -1;
    }

    Node* firstNode = lista->first;

    //hago que lista apunte al segundo nodo
    lista->first=(lista->first)->next;

    if(lista->first==NULL){
        //si el primero llega a NULL, la lista ahora esta vacia
        lista->head=NULL;
    }

    //libero el primer nodo
    int value = firstNode->value;
    free(firstNode);

    lista->size--;

    return value;

}

void freeList(List *lista){
    while(listSize(lista)>0){
        dequeue(lista);
    }
    free(lista);
}
