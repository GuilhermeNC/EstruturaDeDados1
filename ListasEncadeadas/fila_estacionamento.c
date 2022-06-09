#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define LIM 3
#define NL 99999

typedef struct elemento{
  struct elemento *next;    
  struct elemento *prev;
  int dado; 
} Elemento;

typedef struct {
  Elemento *front;
  Elemento *rear;						 
  int size;
  int l;
} Fila;

Fila* criaFila(int tam){
  Fila* fila;
  fila = (Fila*) malloc(sizeof(Fila));
  if (fila == NULL)
    return NULL;
  else {
    fila->front = NULL;						
    fila->rear = NULL;
    fila->size = 0;
    fila->l=tam;
  }
  return fila;
}

bool empty(Fila* fila){
  if(fila->size==0){
    return true;
  }
  return false;
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

int insert(Fila* fila, Fila* sec, Elemento* pivo, int dado){
  Elemento* novo = criaElemento(dado);

  if(fila->size == fila->l){
    printf("\nLista principal cheia\n");
    return insert(sec, NULL, pivo, dado);
  }
  
   if(novo==NULL){
    return-1;
  }
  
  if(empty(fila)){
    fila -> front = novo;
    fila -> rear = novo;
  }
  else{
    novo -> prev = fila->rear;
    fila->rear-> next = novo;
    fila -> rear = novo;
    fila->rear->next = NULL;
  }
  fila -> size++;
  return dado;
}

void percorreFila(Fila* fila, int decisao){
  Elemento* aux;

  if(fila -> size == 0){
    printf("\nFila vazia!\n");
    return;
  }

  if(decisao == 1){
    aux = fila->front;
    
    while(aux != NULL){									
      printf("%i, ", aux->dado);
      aux = aux->next;
    }
  }	
  else if (decisao == -1){
    aux = fila->rear;
    
    while(aux != NULL){									
      printf("%i, ", aux->dado);
      aux = aux->prev;
    }
  }
	printf("\n");
}

int remover(Fila* fila,Fila* sec, Elemento* pivo){
  int dado=0;
  if(!empty(fila)){
    if(pivo == NULL || pivo == fila->front){
      fila -> front = fila -> front -> next;
      if(fila -> front == NULL){
        fila -> rear = NULL;
      }
      else {
        fila -> front -> prev = NULL;
      } 
      dado = pivo -> dado; 
      free(pivo);
      fila -> size--;
    }
    else{
      for(int i=0; i< (fila->size)+1; i++){
        if(pivo!=fila->front){
          fila->rear->next = fila->front;
          fila->front->prev = fila->rear;
          
          fila->front = fila->front->next;
          fila->rear = fila->rear->next;
          
          fila->rear->next = NULL;
          fila->front->prev = NULL; 
        }
        else{
          dado = remover(fila, NULL, pivo);
        }
      }
    }
    if(!empty(sec) && sec != NULL){
      insert(fila, NULL, pivo, sec -> front -> dado);
      remover(sec, NULL, NULL);
    }
  }
  return dado;
}

Elemento* pesquisaNaFila(Fila* fila, int dado){
  Elemento* aux;
  aux = fila -> front;
  
  while(aux != NULL){
    if (aux -> dado == dado){
        return aux;
    }
    aux = aux -> next;
  }
  return NULL;
}

void limpaFila(Fila* fila, Fila* sec){
    while(fila -> front != NULL){
      remover(fila, sec, fila ->front);
    }
    free(fila);
}

void resultInserir(int n){
  if(n==-1){
    printf("\nNão recebemos dados\n");
  }
  else if(n==-2){    
    printf("\nSó aceita pivo nulo na inserção do primeiro elemento\n");
  }
  else{
    printf("\nNumero %i inserido na fila\n", n);
  }
}

void resultRemover(int n){
  if(n==-1){
    printf("\nSó é possível remover quando a fila não é vazio e o pivo também não for nulo\n");
  }
  else{
    printf("\nExcluido o valor %i da fila\n", n);    
  }
}

int main(){
    int dado;
    Elemento* pivo;
    int teste;
    Fila* fila = criaFila(LIM);
    Fila* sec = criaFila(NL);  
  
    if (fila == NULL){
        printf("\nImpossivel alocar memoria para a fila.\n");
        return -1;
    }

  
    //Inserindo elementos
    teste = insert(fila, sec, fila->rear, 1);
    resultInserir(teste);
    teste = insert(fila, sec, fila->rear, 2);
    resultInserir(teste);
    teste = insert(fila, sec, fila->rear, 3);
    resultInserir(teste);
    teste = insert(fila, sec, fila->rear, 4);
    resultInserir(teste);
    teste = insert(fila, sec, fila->rear, 5);
    resultInserir(teste);
    teste = insert(fila, sec, fila->rear, 6);
    resultInserir(teste);
    teste = insert(fila, sec, fila->rear, 7);
    resultInserir(teste);

    //Monstrando a filaa do começo(cabeça) -> fim(cauda)
    percorreFila(fila,1);
    percorreFila(sec,1);
    //percorreFila(fila,-1);
    //percorreFila(sec,-1);
    //Monstrando a filaa do fim(cauda) -> começo(cabeça)

    //Removendo elementos 
    pivo = pesquisaNaFila(fila, 3);
    dado = remover(fila, sec, pivo);
    resultRemover(dado);
    pivo = pesquisaNaFila(fila, 2);
    dado = remover(fila, sec, pivo);
    resultRemover(dado);
    //Monstrando a filaa do fim(cauda) -> começo(cabeça)
    percorreFila(fila,1);
    percorreFila(sec,1);
    //Monstrando a filaa do começo(cabeça) -> fim(cauda)
    //percorreFila(fila,1);

    //Limpando a fila e liberando memória
    limpaFila(fila, sec);
    return 0;
}
