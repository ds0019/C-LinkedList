#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "intSetADT.h"
#include "intLinkedListSet.h"

IntSetADT mkSet() {
	IntSetADT insieme = malloc(sizeof(struct intSet));
	if(insieme!=NULL){
		insieme->front = NULL;
		insieme->size = 0;
	}
    return insieme;
}

_Bool dsSet(IntSetADT *sp) {
	if(sp==NULL || (*sp)->size == 0){
		return 0;
	}
	
	ListNodePtr current = (*sp)->front;
	while(current!=NULL){
			(*sp)->front = (*sp)->front->next;
			free(current);
			(*sp)->size -= 1;
			current = (*sp)->front;	
		}
		
	*sp = NULL;
	
	return true; 
}


_Bool set_add(IntSetADT set, const int elem) {
	if(set!=NULL){
		ListNodePtr nuovoNodo = malloc(sizeof(ListNode)); //creiamo il nuovo nodo
		if(nuovoNodo!=NULL){
			nuovoNodo->data = elem;
			nuovoNodo->next = NULL;
			
			if(set->front == NULL){
				set->front = nuovoNodo;
				set->size +=1;
				
				return 1;
			}
			
			ListNodePtr currentNodo = set->front;
			ListNodePtr previousNodo = NULL;
			while(currentNodo!=NULL){
				if(currentNodo->data == elem){
					free(nuovoNodo);
					return 0;
				}
				previousNodo = currentNodo;
				currentNodo = currentNodo->next;
			}
			previousNodo->next = nuovoNodo;
			nuovoNodo->next = NULL;
			set->size += 1;
			return 1;
		}
	}
	return 0;
	

}

_Bool set_remove(IntSetADT set, const int elem) {
	
	if(set==NULL || set->size == 0){
		return 0;
	}
	if(set->size == 1){ //se c'è solamente un nodo all'interno dell'insieme
		if((set->front)->data == elem){ //se il nodo contiene l'elemento cercato
			free(set->front);
			set->size -= 1;//elimina direttamente l'unico nodo presente
		}
		return 1;
	}
	
	ListNodePtr previousNodo = NULL;
	ListNodePtr currentNodo = set->front;
	while(currentNodo!=NULL){
		if(currentNodo->data == elem){
			ListNodePtr tempNodoPtr = currentNodo;
			currentNodo = currentNodo->next;
			if(previousNodo==NULL){
				set->front = currentNodo;
			}
			free(tempNodoPtr);
			set->size -= 1;
			return 1;
		}
		else{
			previousNodo = currentNodo;
			currentNodo = currentNodo->next;
		}
	}
	
    return 0;
}



_Bool set_member(const IntSetADT set, const int elem) {
	if(set!=NULL && set->front !=NULL){
		ListNodePtr currentNodo = set->front;
		while(currentNodo != NULL){
			if(currentNodo->data == elem){
				return 1;
			}
			currentNodo = currentNodo->next;
		}
	}
    return false;
}

_Bool isEmptySet(const IntSetADT set) {
	if(set==NULL || set->size > 0){
		return 0;
	}
	else{
		return 1;
	}
}

int set_size(const IntSetADT set) {
	if(set==NULL){
		return -1;
	}
	
	return set->size;
}

_Bool set_extract(IntSetADT set, int *datap) {
	if(set==NULL || set->front == NULL || set->size == 0){
		return 0;
	}
	ListNodePtr currentNodo = set->front;
	
	//APPROCCIO NON FUNZIONANTE PER VIA DEL SRAND(TIME(NULL)) Non funzionante al di fuori del main	
	/*int indiceRandom = rand() % (set->size);
	int indiceLista = 0;
	while(indiceLista!=indiceRandom){
		indiceLista++;
		currentNodo = currentNodo->next;
		srand(time(NULL));
	}*/

	//APPROCCIO ALTERNATIVO: Rimuoviamo ogni elemento estratto in modo che non sia estratto più volte, modificando l'insieme.

	*datap = currentNodo->data;
	set_remove(set, currentNodo->data);
	
    return 1;
}

_Bool set_equals(const IntSetADT set1, const IntSetADT set2) {
	if(set1 == NULL || set2 == NULL || set1->size != set2->size){
		return 0;
	}
	
	ListNodePtr currentNodo1 = set1->front;
	

	while(currentNodo1 != NULL){
		bool elementoTrovato = false;
		ListNodePtr currentNodo2 = set2->front;
		while(currentNodo2 != NULL && !elementoTrovato){
			if(currentNodo1->data == currentNodo2->data){
				elementoTrovato = true;
			}
			else{
				currentNodo2 = currentNodo2->next;
			}
		}
		if(!elementoTrovato){
			return 0;
		}
		currentNodo1 = currentNodo1->next;
	}
	return 1;
}

_Bool subseteq(const IntSetADT set1, const IntSetADT set2) {
	
	if(set1==NULL || set2==NULL || set1->size > set2->size){
		return false;
	}
	
	ListNodePtr currentNodo1 = set1->front;
	ListNodePtr currentNodo2 = set2->front;
	bool sottoInsieme=true;
	
	while(currentNodo1!=NULL && sottoInsieme){
		sottoInsieme = false;
		while(currentNodo2!=NULL && !sottoInsieme){
			if(currentNodo1->data == currentNodo2->data){
				sottoInsieme = true;
			}
			else{
				currentNodo2 = currentNodo2->next;
			}
		}
		
		currentNodo1 = currentNodo1->next;
	}
	
	return sottoInsieme;
}

_Bool subset(const IntSetADT set1, const IntSetADT set2) {
	
	if(set1==NULL || set2==NULL || set1->size >= set2->size){
		return false;
	}
	
	ListNodePtr currentNodo1 = set1->front;
	ListNodePtr currentNodo2 = set2->front;
	bool sottoInsieme=true;
	
	while(currentNodo1!=NULL && sottoInsieme){
		sottoInsieme = false;
		while(currentNodo2!=NULL && !sottoInsieme){
			if(currentNodo1->data == currentNodo2->data){
				sottoInsieme = true;
			}
			else{
				currentNodo2 = currentNodo2->next;
			}
		}
		
		currentNodo1 = currentNodo1->next;
	}
	
	return sottoInsieme;
     
}

IntSetADT set_union(const IntSetADT set1, const IntSetADT set2) {
    if(set1==NULL || set2==NULL){
		return NULL;
	}
	IntSetADT setUnito = malloc(sizeof(IntSetADT));
	setUnito->front = NULL;
	setUnito->size = 0;
	
	ListNodePtr currentNodo1 = set1->front;
	ListNodePtr currentNodo2 = set2->front;
	
	while(currentNodo1 != NULL){
		set_add(setUnito, currentNodo1->data);
		currentNodo1 = currentNodo1->next;
	}
	
	while(currentNodo2 != NULL){
		set_add(setUnito, currentNodo2->data);
		currentNodo2 = currentNodo2->next;
	}
	
	
	return setUnito;
	
}

IntSetADT set_intersection(const IntSetADT set1, const IntSetADT set2) {
	

	if(set1==NULL || set2==NULL){
		return NULL;
	}

	IntSetADT setIntersezione = malloc(sizeof(IntSetADT));
	setIntersezione->front = NULL;
	setIntersezione->size = 0;

	if((set1->front == NULL || set2->front == NULL) && setIntersezione!= NULL){
		return setIntersezione;
	}
	else if(setIntersezione!=NULL){
		ListNodePtr currentNodo1 = set1->front;
		ListNodePtr currentNodo2 = set2->front;
		
		if(set1->size < set2->size){
			while(currentNodo1!=NULL){
				if(set_member(set2, currentNodo1->data)){
					set_add(setIntersezione, currentNodo1->data);
				}
				currentNodo1 = currentNodo1->next;
			}
		}
		else{
			while(currentNodo2!=NULL){
				if(set_member(set1, currentNodo2->data)){
					set_add(setIntersezione, currentNodo2->data);
				}
				currentNodo2 = currentNodo2->next;
			}
		}
		return setIntersezione;
	}
	else{
		return NULL;
	}

    
}

IntSetADT set_subtraction(const IntSetADT set1, const IntSetADT set2) {
	if(set1==NULL || set2==NULL){
		return NULL;
	}
	IntSetADT setSottratto = malloc(sizeof(IntSetADT));
	setSottratto->front = NULL;
	setSottratto->size = 0;
	if(set2->size == 0){
		return set1;
	}
	else{
		ListNodePtr currentNodo1 = set1->front;
		
		while(currentNodo1!=NULL){
			if(!(set_member(set2, currentNodo1->data))){
				set_add(setSottratto, currentNodo1->data);
			}
			currentNodo1 = currentNodo1->next;
		}
    }
	return setSottratto;
}