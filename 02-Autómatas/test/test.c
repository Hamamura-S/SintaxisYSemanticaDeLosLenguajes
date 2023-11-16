#include "unity.h"
//#include "../src/lists.h"
//#include "../src/automata.h"
#include "../src/library.h"

List* lista;

void reiniciarLista(void){
    freeList(lista);
    lista=createList();
    push(lista, 1);            //indice 3 tiene al entero 1
    push(lista, 2);
    push(lista, 3);
    push(lista, 4);         //indice 6 tiene al entero 4
    enqueue(lista, 'c');
    enqueue(lista, 'b');
    enqueue(lista, 'a');    //indice 0 tiene al caracter 'a'
}

void setUp(void) {
    //lista de prueba
    lista=createList();
    push(lista, 1);            //indice 3 tiene al entero 1
    push(lista, 2);
    push(lista, 3);
    push(lista, 4);         //indice 6 tiene al entero 4
    enqueue(lista, 'c');
    enqueue(lista, 'b');
    enqueue(lista, 'a');    //indice 0 tiene al caracter 'a'
}

void tearDown(void) {
    //limpio la lista
    freeList(lista);
}

void createList_genera_lista_vacia(void){

    List* emptyList=createList();

    TEST_ASSERT_NULL(emptyList->first);
    TEST_ASSERT_NULL(emptyList->head);
    TEST_ASSERT_EQUAL_INT(emptyList->size, 0);

}

void getNode_accede_por_indice(void){

    Node* primerNodo = getNode(lista, 0);
    Node* ultimoNodo = getNode(lista, 6);
    Node* nodoIntermedio = getNode(lista, 3);

    TEST_ASSERT_EQUAL_INT(primerNodo->value, 'a');
    TEST_ASSERT_EQUAL_INT(ultimoNodo->value, 4);
    TEST_ASSERT_EQUAL_INT(nodoIntermedio->value, 1);

}

void dequeue_disminuye_tamanio(void){

    const int initialSize = lista->size;

    dequeue(lista);

    TEST_ASSERT_EQUAL_INT(lista->size, initialSize-1);

}

void pop_disminuye_tamanio(void){

    const int initialSize = lista->size;

    pop(lista);

    TEST_ASSERT_EQUAL_INT(lista->size, initialSize-1);

}

void vaciar_lista_deja_punteros_en_NULL(void){

    const int size = lista->size;

    for(int i=0;i<size;i++){

        pop(lista);

    }

    TEST_ASSERT_NULL(lista->first);
    TEST_ASSERT_NULL(lista->head);

    reiniciarLista();

}

void pop_devuelve_el_ultimo(void){

    int ultimo = pop(lista);

    int nuevoUltimo = pop(lista);

    TEST_ASSERT_EQUAL_INT(ultimo, 4);
    TEST_ASSERT_EQUAL_INT(nuevoUltimo, 3);

}

void dequeue_devuelve_el_primero(void){

    int primero = dequeue(lista);

    int nuevoPrimero = dequeue(lista);

    TEST_ASSERT_EQUAL_INT(primero, 'a');
    TEST_ASSERT_EQUAL_INT(nuevoPrimero, 'b');

}

void isContainedBy_verifica_inclusion(void){

    char saludo[] = "hola";

    TEST_ASSERT_TRUE(isContainedBy(saludo, 4, 'o'));

    TEST_ASSERT_FALSE(isContainedBy(saludo, 4, 'z'));

    TEST_ASSERT_TRUE(isContainedBy(digitos_numericos, 10, '5'));

    TEST_ASSERT_TRUE(isContainedBy(signos, SIGNS_AMOUNT, '+'));

    TEST_ASSERT_TRUE(isContainedBy(digitos_positivos, POSITIVE_DIGITS_AMOUNT, '1'));

}

void transition_desde_0(void){

    TEST_ASSERT_EQUAL_INT(transition(0, '0'), 1);

    TEST_ASSERT_EQUAL_INT(transition(0, '+'), 2);

    TEST_ASSERT_EQUAL_INT(transition(0, '-'), 2);

    TEST_ASSERT_EQUAL_INT(transition(0, '1'), 5);

    TEST_ASSERT_EQUAL_INT(transition(0, '9'), 5);
}

void transition_desde_1(void){

    TEST_ASSERT_EQUAL_INT(transition(1, 'x'), 3);

    TEST_ASSERT_EQUAL_INT(transition(1, 'X'), 3);

    TEST_ASSERT_EQUAL_INT(transition(1, '0'), 4);

    TEST_ASSERT_EQUAL_INT(transition(1, '5'), 4);

    TEST_ASSERT_EQUAL_INT(transition(1, '7'), 4);
}

void transition_desde_2(void){

    TEST_ASSERT_EQUAL_INT(transition(2, '0'), 5);

    TEST_ASSERT_EQUAL_INT(transition(2, '9'), 5);

}

void transition_rechazo(void){

    TEST_ASSERT_EQUAL_INT(transition(0, 'F'), -1);

    TEST_ASSERT_EQUAL_INT(transition(1, '8'), -1);

    TEST_ASSERT_EQUAL_INT(transition(2, 'x'), -1);

}

void reconocerTipo_reconoce(void){

    TEST_ASSERT_EQUAL_INT(reconocerTipo("125", 3), 'd');

    TEST_ASSERT_EQUAL_INT(reconocerTipo("0x", 2), 'h');

    TEST_ASSERT_EQUAL_INT(reconocerTipo("0x0125", 6), 'h');

    TEST_ASSERT_EQUAL_INT(reconocerTipo("084", 3), -1);

    TEST_ASSERT_EQUAL_INT(reconocerTipo("0", 1), 'd');

    TEST_ASSERT_EQUAL_INT(reconocerTipo("00", 2), 'o');
}

int main(){
    UNITY_BEGIN();
    
/*              TESTEANDO FUNCIONES DE LISTA                */

    RUN_TEST(createList_genera_lista_vacia);

    RUN_TEST(getNode_accede_por_indice);

    RUN_TEST(dequeue_disminuye_tamanio);

    RUN_TEST(pop_disminuye_tamanio);

    RUN_TEST(vaciar_lista_deja_punteros_en_NULL);

    RUN_TEST(pop_devuelve_el_ultimo);

    RUN_TEST(dequeue_devuelve_el_primero);


/*              TESTEANDO FUNCIONES DE AUTOMATA                */

    RUN_TEST(isContainedBy_verifica_inclusion);

    RUN_TEST(transition_desde_0);

    RUN_TEST(transition_desde_1);

    RUN_TEST(transition_desde_2);

    RUN_TEST(transition_rechazo);

    RUN_TEST(reconocerTipo_reconoce);

    return UNITY_END();
}