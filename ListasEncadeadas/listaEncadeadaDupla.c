#include <stdio.h>
#include <stdlib.h>

typedef struct node{
  struct node *next;    
  struct node *back;
  int dado; 
} Node;

typedef struct {
  Node *head;
  Node *tail;						 
  int size;
} Lista;

Lista* criaLista(){
  Lista* lista;
  lista = (Lista*) malloc(sizeof(Lista));
  if (lista == NULL)
    return NULL;
  else {
    lista->head = NULL;						
    lista->tail = NULL;
    lista->size = 0;
  }
  return lista;
}

Node* criaElemento(int dado){
  Node* nodo;
  nodo = (Node*) malloc(sizeof(Node));
  if (nodo == NULL)
    return NULL;								
  else {
    nodo -> next = NULL;
    nodo -> back = NULL;
    nodo -> dado = dado;
  }
  return nodo;
}

int insereElementoNaLista(Lista* lista, Node* pivo, int dado){
  Node* novo = criaElemento(dado);
  if (novo == NULL){
    return -1;
  }

  novo -> dado = dado; 

  if (pivo == NULL){
    if (lista -> size == 0){
      lista -> head = novo;					
    } else {
      novo -> next = lista -> head;
      lista -> head -> back = novo;
      lista -> head = novo;							
    }
  } 
  else {
    if (pivo -> next == NULL){
      novo -> back = lista -> tail;
      lista -> tail = novo;
    } else {
      novo -> next = pivo -> next;
      novo -> back = pivo;
      pivo -> next = novo;
    }
  }
  lista -> size++;
  return 0;
}

void percorreLista(Lista* lista, int decisao){
  Node* aux;

  if(lista -> size == 0){
    printf("Lista vazia!\n\n");
    return;
  }

  if(decisao == 1){
    aux = lista->head;
    
    while(aux != NULL){									
      printf("%i, ", aux->dado);
      aux = aux->next;
    }
  }	else if (decisao == -1){
    aux = lista->tail;
    
    while(aux != NULL){									
      printf("%i, ", aux->dado);
      aux = aux->back;
    }
  }
	printf("\n\n");
}


int removeElementoDaLista(Lista* lista, Node* pivo){
  Node* antigo;
  int dado;
  
  if (lista -> size == 0){
    return -1;							
  }

  if (pivo == NULL){
    antigo = lista -> head;
    lista -> head = lista -> head -> next;

    if (lista -> head == NULL){  
      lista -> tail = NULL;
    } else {
      lista -> head -> back = NULL;
    }
  } 
  else {
    if (pivo -> next == NULL){
      return -2; 								
    }

    antigo = pivo -> next;
    pivo -> next = antigo -> next;

    if (pivo -> next == NULL){
      lista -> tail = pivo; 		
    }
  }
  
  dado = antigo -> dado;
  free(antigo);

  lista -> size--;
  
  return dado;
}

Node* pesquisaNaLista(Lista* lista, int dado){
  Node* aux;
  aux = lista -> head;
  
  while(aux != NULL){
    if (aux -> dado == dado){
        return aux;
    }
    aux = aux -> next;
  }
  return NULL;
}

void limpaLista(Lista* lista){
    while(lista -> head != NULL){
      removeElementoDaLista(lista, NULL);
    }
    free(lista);
}

int main(){
    int dado;
    Node* pivo;
    Lista* list = criaLista();
    if (list == NULL){
        printf("Impossivel alocar memoria para a lista.\n");
        return -1;
    }

	  //Inserindo elementos que foram passados no quadro
    insereElementoNaLista(list, list->tail, 15);
		printf("Numero %i inserido na lista\n", 15);
    insereElementoNaLista(list, list->tail, 25);
		printf("Numero %i inserido na lista\n", 25);
    insereElementoNaLista(list, list->head, 10);
		printf("Numero %i inserido na lista\n", 10);
    insereElementoNaLista(list, NULL, 35);
		printf("Numero %i inserido na lista\n", 35);
		insereElementoNaLista(list, list->head, 35);
		printf("Numero %i inserido na lista\n", 35);
		pivo = pesquisaNaLista(list, 10);
		insereElementoNaLista(list, pivo, 27);
		printf("Numero %i inserido na lista\n", 27);
		insereElementoNaLista(list, list->tail, 29);
		printf("Numero %i inserido na lista\n", 29);
		insereElementoNaLista(list, NULL, 45);
		printf("Numero %i inserido na lista\n", 45);

    //Monstrando a lista do começo(cabeça) -> fim(cauda)
    percorreLista(list,1);
    //Monstrando a lista do fim(cauda) -> começo(cabeça)
		percorreLista(list,-1);

    //Removendo elementos que foram passados no quadro
    dado = removeElementoDaLista(list, list -> tail);
    printf("\nExcluido o valor %i da lista\n", dado);
		dado = removeElementoDaLista(list, list -> head);
    printf("\nExcluido o valor %i da lista\n", dado);
		dado = removeElementoDaLista(list, NULL);
    printf("\nExcluido o valor %i da lista\n", dado);
		pivo = pesquisaNaLista(list, 55);
		dado = removeElementoDaLista(list, pivo);
    printf("\nExcluido o valor %i da lista\n", dado);
		pivo = pesquisaNaLista(list, 27);
		dado = removeElementoDaLista(list, pivo);
    printf("\nExcluido o valor %i da lista\n", dado);
		dado = removeElementoDaLista(list, list -> head);
    printf("\nExcluido o valor %i da lista\n", dado);
		pivo = pesquisaNaLista(list, 10);
		dado = removeElementoDaLista(list, pivo);
    printf("\nExcluido o valor %i da lista\n", dado);

    //Monstrando a lista do fim(cauda) -> começo(cabeça)
		percorreLista(list,-1);
    //Monstrando a lista do começo(cabeça) -> fim(cauda)
		percorreLista(list,1);

    //Limpando a lista e liberando memória
    limpaLista(list);
    return 0;
}
