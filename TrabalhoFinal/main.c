#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 53

typedef struct elemento{
	struct elemento *next;     
	struct elemento *prev;
	char name[30]; 
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

Elemento* criaElemento(char* name){
	Elemento* elemento;
	elemento = (Elemento*) malloc(sizeof(Elemento));
	if (elemento == NULL)
		return NULL;								
	else {
		elemento -> next = NULL;
		elemento -> prev = NULL;
    strcpy(elemento->name, name);
	}
	return elemento;
}

char* inserir(Lista* lista, char* name){
	Elemento* novo = criaElemento(name);

	if (novo == NULL){
		return "-1";
	}
	
	if( lista -> size == 0 ){
		lista -> head = novo;
		lista -> tail = novo;
	}
  else {
		novo -> prev = lista -> tail;
    lista -> tail -> next = novo;
    lista -> tail = novo;
	}

	lista -> size++;
	return novo -> name;
}

int percorreLista(Lista* lista, int decisao){
	Elemento* aux;

	printf("\n");
	if(lista -> size == 0){
		return -1;
	}

	if(decisao == 1){
		aux = lista->head;
		
		while(aux != NULL){									
			printf("%s, ", aux->name);
			aux = aux->next;
		}
	}	
  else if (decisao == -1){
  	aux = lista->tail;
		
		while(aux != NULL){									
			printf("%s, ", aux->name);
			aux = aux->prev;
		}
	}
	printf("\n");
	return 0;
}

char* remover(Lista* lista, Elemento* elem){
	if(elem != NULL && lista -> size != 0){
		if(elem == lista ->head){
			lista -> head = elem -> next;
			if(lista -> head == NULL){
				lista -> tail = NULL;
			}
			else {
				elem -> next -> prev = NULL;
			}
		}
		else{
			elem -> prev -> next = elem -> next;
			if(elem -> next == NULL){
				lista -> tail = elem-> prev;
			}
			else{
				elem -> next -> prev = elem -> prev;
			}
		}
	} else {
		return "-1";
	}

  char* prevup = elem->name;
	free (elem);
	lista -> size --;

	return prevup;
}

Elemento* pesquisaNaLista(Lista* lista, char* name){
	Elemento* aux;
	aux = lista -> head;
	
	while(aux != NULL){
		if (strcmp(aux -> name, name) == 0){
			return aux;
		}
		aux = aux -> next;
	}
	return NULL;
}

void limpaLista(Lista* lista){
	while(lista -> head != NULL){
		remover(lista, lista->head);
	}
	free(lista);
}

void resultInserir(char* n, int nr){
  if(strcmp(n, "-1") == 0){
    printf("\nN??o recebemos nomes\n");
  }
  else{
    printf("\nNome inserido na lista %d: %s\n\n", nr+1, n);
  }
}

void resultRemover(char* n, int nr){
  if(strcmp(n, "-1") == 0){
    printf("\nNome n??o encontrado\n");
  }
  else{
    printf("\nNome excluido Da lista %d: %s\n\n", nr+1, n);
  }
}

Lista** criarMatriz(){
  Lista**  lista = (Lista** ) malloc(sizeof(Lista* ) * TAM);
  for(int i=0; i<TAM; i++){
    lista[i]=criaLista();
  }
  return lista;
}

int funcaoHash(char* name){
  int tamName = strlen(name);
   int hash = 0;

  for(int i=0; i<tamName; i++){
    hash += name[i] * (i+1);
  }
  hash %= TAM;
  return hash;
}

void limpaVet(Lista** lista){
  for(int i=0; i<TAM; i++){ 
    limpaLista(lista[i]);
  }
  free(lista);
}

void histograma(Lista** lista){
  printf("\n%s  %s   %s\n\n", "Lista","Tamanho", "Histograma (1:40)");
  for(int pos=0; pos<TAM; pos++){
    printf("%3u %9.2f    ", pos+1, (float)lista[pos]->size/40);
    for(int qtd=0; qtd<= (lista[pos]->size/40); qtd++){
      printf("???");
    }
    puts("");
  }
}

void calculos(Lista** lista){
  int media=0,max=0,min=0;
  min = lista[0]-> size;
  //Percorrendo o Vetor de Listas e somando os tamanhos
  for(int i = 0; i < TAM; i++){
    media += lista[i]-> size;
    if(max<lista[i]->size){
      max=lista[i]->size;
    }
    if(min>lista[i]->size){
      min=lista[i]->size;
    }
  }
  media /= TAM;    //Calulando a m??dia entre as listas

  printf("\nC??lculos ---------- \n\nM??dia: %d \nMaior Lista: %d \nMenor Lista: %d\n\n", media, max, min);
}

void trocar(Lista* lista, Elemento* um, Elemento* dois){ 
  char bkp[30];
  strcpy(bkp, um->name);
  strcpy(um->name, dois->name);
  strcpy(dois->name, bkp);

  //Por algum motivo n??o ta funcionando com esse txt  
//if(um == NULL || dois == NULL || um == dois){
//		return;
//}

// 	if(lista -> head == um){
// 		lista -> head = dois;
// 	}else if(lista -> head == dois){
// 		lista -> head = um;
// 	}

// 	if(lista -> tail == um){
// 		lista -> tail = dois;
// 	}else if(lista -> tail == dois){
// 		lista -> tail = um;
// 	}

//   if(um -> next != NULL){
// 		um -> next -> prev = dois;
// 	}
// 	if(dois -> next != NULL){
// 		dois -> next -> prev = um;
// 	}

	
// 	Elemento* bkpNext = um -> next;
// 	um -> next = dois -> next;
// 	dois -> next = bkpNext;

//   if(um -> prev != NULL){
// 		um -> prev -> next = dois;
// 	}
// 	if(dois -> prev != NULL){
// 		dois -> prev -> next = um;
// 	}

// 	Elemento* bkpPrev = um -> prev;
// 	um -> prev = dois -> prev;
// 	dois -> prev = bkpPrev;
}

Elemento* partition(Lista* lista, Elemento* left, Elemento* last){
  char* pivo = last->name;
  Elemento* i = left->prev;
  for (Elemento* rodar = left; rodar != last; rodar = rodar->next){
    if (strcmp(rodar->name, pivo) <= 0){
      i = (i == NULL) ? left : i->next;
      trocar(lista, i, rodar);
    }
  }
  i = (i == NULL) ? left : i->next;
  trocar(lista, i, last);
  return i;
}

void quicksort(Lista* lista, Elemento* esquerda, Elemento* direita){
  if(esquerda != NULL && direita != NULL && esquerda != direita && esquerda != direita->next){
    Elemento* aux = partition(lista, esquerda, direita);
    quicksort(lista, esquerda, aux->prev);
    quicksort(lista, aux->next, direita);
  }
}

int main(void) {
  //Criando Vetor de Listas e Alocando---------------------------------------
  Lista** VetorListas;
  VetorListas = criarMatriz();

  //Upload e leitura do arquivo txt -----------------------------------------
	FILE *file;                       //declarando o ponteiro com os nomes
	file = fopen("nomes.txt","r");    //recebendo os nomes no ponteiro
	if(file == NULL){                 //verificando se o txt era vazio
		printf("N??o foi poss??vel ler o arquivo\n");
		return 0;
	}
  
  while(1){
    int opcao=0;
    printf("\nMENU DE INTERA????O - O QUE DESEJA FAZER? \n\n1 - Inserir nome \n2 - Pesquisar nome \n3 - Histograma \n4 - Remover nome \n5 - Processar arquivo txt \n6 - Printar lista(s) \n7 - Ordenar lista(s) \n8 - Tamanho da(s) lista(s) \n9 - Sair\n\n");
    scanf("%i", &opcao);
    
    if(opcao==1){ //Op????o 1 ----------------------------------------------------
      char nome[30];
      char* result;
      printf("\nDigite o nome a inserir\n\n");
      scanf("%s", nome);
      int indice = funcaoHash(nome);
      result = inserir(VetorListas[indice], strcpy(nome, nome));
      resultInserir(result, indice);
    }
    else if(opcao==2){//Op????o 2 ----------------------------------------------------
      char nome[30];
      printf("\nDigite o nome para consulta\n\n");
      scanf("%s", nome);
      int indice = funcaoHash(nome);
      Elemento* temp = pesquisaNaLista(VetorListas[indice], nome);
      if(temp != NULL){
        printf("\nNome: %s encontrado na lista: %d\n\n", temp->name, indice+1);
      }
      else{
        printf("Nome n??o encontrado");
      }
    }
    else if(opcao==3){//Op????o 3 ----------------------------------------------------
      histograma(VetorListas);
      calculos(VetorListas);
    }
    else if(opcao==4){//Op????o 4 ----------------------------------------------------
      char nome[30];
      char* result;      
      printf("\nDigite o nome a remover\n\n");
      scanf("%s", nome);
      int indice = funcaoHash(nome);
      Elemento* temp = pesquisaNaLista(VetorListas[indice], nome);
      result = remover(VetorListas[indice], temp);
      resultRemover(result, indice);
    }
    else if(opcao==5){//Op????o 5 ----------------------------------------------------
      //Manipula????o do TXT -------------------------------------------------------
    	 char nome[30];                        //Vari??vel que armazena cada nome                          
      char* result; //Vari??vel que vai armazenar se foi poss??vel inserir ou n??o
      while(fgets(nome,30,file) != NULL){//M??todo para pegar string por linha
        strcpy(nome, strtok(nome, "\n"));
        int indice = funcaoHash(nome);      //Recebendo o ??ndice de armazenamento dada pela fun????o de hashing
        result = inserir(VetorListas[indice], strcpy(nome, nome)); //Armazenando nome na lista
      }
    }
    else if(opcao==6){//Op????o 6 ----------------------------------------------------
      int escolha = 0;
      printf("\n1 - Printar todas as listas \n2 - Printar uma espec??fica?\n\n");
      scanf("%i", &escolha);
      if(escolha==1){
        for(int i=0; i<TAM; i++){
          if(VetorListas[i]->size > 0){
            percorreLista(VetorListas[i], 1);
          }
        }
      }
      else if(escolha==2){
        int indice=0;
        printf("\nDigite qual lista: (1-53)\n");
        scanf("%i", &indice);
        if(indice<=53 && indice >=1){
          percorreLista(VetorListas[indice-1], 1);
        }        
      }
      else{
        printf("Op????o inv??lida");
      }
    }
    else if(opcao==7){//Op????o 7 ----------------------------------------------------
      int escolha = 0;
      printf("\n1 - Ordenar todas as listas \n2 - Ordenar uma espec??fica?\n\n");
      scanf("%i", &escolha);
      if(escolha==1){
        for(int i=0; i<TAM; i++){
          if(VetorListas[i]->size > 0){
            quicksort(VetorListas[i], VetorListas[i]->head, VetorListas[i]->tail);
          }
        }
      }
      else if(escolha==2){
        int indice=0;
        printf("\nDigite qual lista: (1-53)\n");
        scanf("%i", &indice);
        if(indice>=1 && indice<=53){
          quicksort(VetorListas[indice-1], VetorListas[indice-1]->head, VetorListas[indice-1]->tail);
        }
      }
      else{
        printf("Op????o inv??lida");
      }
    }
    else if(opcao==8){//Op????o 8 ----------------------------------------------------
      int escolha = 0;
      printf("\n1 - Tamanho de todas as listas \n2 - Tamanho de uma espec??fica?\n\n");
      scanf("%i", &escolha);
      if(escolha==1){
        printf("\n");
        for(int i=0; i<TAM; i++){
          printf("%i nomes na lista: %i\n", VetorListas[i]->size, i+1);
        }
      }
      else if(escolha==2){
        int indice=0;
        printf("\nDigite qual lista: (1-53)\n");
        scanf("%i", &indice);
        if(indice>=1 && indice<=53){
          printf("%i nomes na lista: %i", VetorListas[indice-1]->size, indice);
        }
      }
      else{
        printf("Op????o inv??lida");
      }
    }
    else if(opcao==9){
      printf("\nValeu!\n");
      limpaVet(VetorListas);
      break;
    }
    else{
      printf("Op????o inv??lida");      
    }
  }
}
