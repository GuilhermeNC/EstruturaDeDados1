#include <stdio.h>
#include <stdlib.h>

typedef struct sElemento{
  struct sElemento *next;
  int dado;
} Elemento;

typedef struct {
  Elemento *head;
  Elemento *tail;
  int size;
} Lista;

Lista* criaLista(){
  Lista* lista;
  lista = (Lista*) malloc(sizeof(Lista));
  if (lista == NULL){
    return NULL;
  }
  else {
    lista->head = NULL;
    lista->tail = NULL;
    lista->size = 0;
  }
  return lista;
}

Elemento* criaElemento(int dado){
  Elemento* nodo;
  nodo = (Elemento*) malloc(sizeof(Elemento));
  if (nodo == NULL){
    return NULL;
  }
  else {
    nodo->next = NULL;
    nodo->dado = dado;
  }
  return nodo;
}

int inserirElemento(Lista* lista, Elemento* pivo, int dado){
  Elemento* novo = criaElemento(dado);
  if (novo == NULL){
    return -1;
  }
  if (pivo == NULL){
    if (lista->size == 0){
      lista->tail = novo;
    }
    novo->next = lista->head;
    lista->head = novo;
  } 
  else {
    if (pivo->next == NULL){
      lista->tail = novo;
    }
    novo->next = pivo->next;
    pivo->next = novo;
  }
  lista->size++;
  return 0;
}

void percorreLista(Lista* lista){
  Elemento* aux;
  aux = lista->head;
  
  while(aux != NULL){
    printf("%i, ", aux->dado);
    aux = aux->next;
  }
}

int removerElemento(Lista* lista, Elemento* pivo){
  Elemento* antigo;
  int dado;
  
  if (lista->size == 0)
    return -1;
  
  if (pivo == NULL){
    antigo = lista->head;
    lista->head = lista->head->next;

    if (lista->head == NULL){
      lista->tail = NULL;
    }
  } 
  else {
    if (pivo->next == NULL){
      return -2;
    }
    antigo = pivo->next;
    pivo->next = pivo->next->next;

    if (pivo->next == NULL){
      lista->tail = pivo;
    }
    
  }
  
  dado = antigo->dado;
  free(antigo);

  lista->size--;
  
  return dado;
}

Elemento* pesquisa(Lista* lista, int dado){
    Elemento* aux;
    aux = lista->head;
    
    while(aux != NULL){
        if (aux->dado == dado){
          return aux;
        }
        aux = aux->next;
    }
    return NULL;
}

void limpaLista(Lista* lista){
    while(lista->head != NULL){
      removerElemento(lista, NULL);
    }
    free(lista);
}

int main(){
  int dado;
  Elemento* pivo;
  Lista* n = criaLista();
  if (n == NULL){
    printf("Impossivel alocar memoria para a lista n.\n");
    return -1;
  }
  inserirElemento(n, n->tail, 10);
  inserirElemento(n, n->tail, 15);
  inserirElemento(n, n->tail, 25);
  inserirElemento(n, NULL, 35);
  percorreLista(n);
  
  dado = removerElemento(n, NULL);
  printf("\nExcluido o valor %i da lista\n", dado);
  
  pivo = pesquisa(n, 15);
  dado = removerElemento(n, pivo);
  printf("\nExcluido o valor %i da lista\n", dado);
  
  limpaLista(n);
  return 0;
}
