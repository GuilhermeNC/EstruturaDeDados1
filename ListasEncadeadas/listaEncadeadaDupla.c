#include <stdio.h>
#include <stdlib.h>

typedef struct elemento{
  struct elemento *next;    
  struct elemento *prev;
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
  if (lista == NULL)
    return NULL;
  else {
    lista->head = NULL;						
    lista->tail = NULL;
    lista->size = 0;
  }
  return lista;
}

Elemento* criaElemento(int dado){
  Elemento* elemento;
  elemento = (Elemento*) malloc(sizeof(Elemento));
  if (elemento == NULL)
    return NULL;								
  else {
    elemento -> next = NULL;
    elemento -> prev = NULL;
    elemento -> dado = dado;
  }
  return elemento;
}

int inserir(Lista* lista, Elemento* pivo, int dado){
  Elemento* novo = criaElemento(dado);
  novo -> dado = dado;

  if(novo==NULL){
    return-1;
  }

  if (pivo == NULL && lista -> size !=0){
    return -2;
  }
  
  if(lista-> size ==0){
    lista -> head = novo;
    lista -> tail = novo;
  }
  else{
    novo -> prev = pivo;
    novo -> next = pivo -> next;
    if(pivo -> next == NULL){
      lista -> tail = novo;
    }
    else {
      pivo -> next -> prev = novo;
    }
    pivo -> next = novo;
  }
  lista -> size++;
  return dado;
}

void percorreLista(Lista* lista, int decisao){
  Elemento* aux;

  if(lista -> size == 0){
    printf("\nLista vazia!\n");
    return;
  }

  if(decisao == 1){
    printf("\nLista do começo->fim (cabeça->cauda)\n");
    aux = lista->head;
    
    while(aux != NULL){									
      printf("%i, ", aux->dado);
      aux = aux->next;
    }
  }	
  else if (decisao == -1){
    printf("\nLista do fim->começo (cauda->cabeça)\n");
    aux = lista->tail;
    
    while(aux != NULL){									
      printf("%i, ", aux->dado);
      aux = aux->prev;
    }
  }
	printf("\n");
}


int remover(Lista* lista, Elemento* pivo){
  int dado;
  if(pivo != NULL && lista -> size != 0){
    if(pivo == lista ->head){
      lista -> head = pivo -> next;
      if(lista -> head == NULL){
        lista -> tail = NULL;
      }
      else {
        pivo -> next -> prev = NULL;
      }
    }
    else{
      pivo -> prev -> next = pivo -> next;
      if(pivo -> next == NULL){
        lista -> tail = pivo-> prev;
      }
      else{
        pivo -> next -> prev = pivo -> prev;
      }
    }  
  dado = pivo -> dado; 
  free(pivo);
  lista -> size--;
  }
  else {
    return -1;
  }
  return dado;
}

Elemento* pesquisaNaLista(Lista* lista, int dado){
  Elemento* aux;
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
      remover(lista, lista ->head);
    }
    free(lista);
}

void resultInserir(int n){
  if(n==-1){
    printf("\nNão recebemos dados\n");
  }
  else if(n==-2){    
    printf("\nSó aceita pivo nulo na inserção do primeiro elemento\n");
  }
  else{
		printf("\nNumero %i inserido na lista\n", n);
  }
}

void resultRemover(int n){
  if(n==-1){
    printf("\nSó é possível remover quando a lista não é vazio e o pivo também não for nulo\n");
  }
  else{
    printf("\nExcluido o valor %i da lista\n", n);    
  }
}

int main(){
    int dado;
    int teste;
    Elemento* pivo;
    Lista* list = criaLista();
    if (list == NULL){
        printf("\nImpossivel alocar memoria para a lista.\n");
        return -1;
    }

	  //Inserindo elementos que foram passados no quadro
    teste = inserir(list, list->tail, 15);
    resultInserir(teste);
    teste = inserir(list, list->tail, 25);
    resultInserir(teste);  
    teste = inserir(list, list->head, 10);
    resultInserir(teste);  
    teste = inserir(list, NULL, 35);
    resultInserir(teste);  
		inserir(list, list->head, 35);
    resultInserir(teste);  
		pivo = pesquisaNaLista(list, 10);
		teste = inserir(list, pivo, 27);
    resultInserir(teste);  
		teste = inserir(list, list->tail, 29);
    resultInserir(teste);  
		teste = inserir(list, NULL, 45);

    //Monstrando a lista do começo(cabeça) -> fim(cauda)
    percorreLista(list,1);
    //Monstrando a lista do fim(cauda) -> começo(cabeça)
		percorreLista(list,-1);

    //Removendo elementos que foram passados no quadro
    dado = remover(list, list -> tail);
    resultRemover(dado);
		dado = remover(list, list -> head);
    resultRemover(dado);
		dado = remover(list, NULL);
    resultRemover(dado);
		pivo = pesquisaNaLista(list, 55);
		dado = remover(list, pivo);
    resultRemover(dado);
		pivo = pesquisaNaLista(list, 27);
		dado = remover(list, pivo);
    resultRemover(dado);
		dado = remover(list, list -> head);
    resultRemover(dado);
		pivo = pesquisaNaLista(list, 10);
		dado = remover(list, pivo);
    resultRemover(dado);

    //Monstrando a lista do fim(cauda) -> começo(cabeça)
		percorreLista(list,-1);
    //Monstrando a lista do começo(cabeça) -> fim(cauda)
		percorreLista(list,1);

    //Limpando a lista e liberando memória
    limpaLista(list);
    return 0;
}
