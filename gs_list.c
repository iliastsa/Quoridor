#include "data_structs.h"
#include "utility.h"


GAMESTATE* newHistoryEntry(GAMESTATE gs){
	gsPtr gsp = malloc(sizeof(struct gState));
	*gsp = gs;
	return gsp;
}

void push(Stackptr* stackREF,GAMESTATE gs){
	Stackptr newStackNode = malloc(sizeof(struct sNode));
	if(newStackNode == NULL)
		return;
	Stackptr temp = *stackREF;
	*stackREF = newStackNode;
	(*stackREF)->gs = newHistoryEntry(gs);
	(*stackREF)->next = temp;
}


GAMESTATE* pop(Stackptr* stackREF){
	Stackptr newStackREF = NULL;
	GAMESTATE* gs = NULL;
	if(isStackEmpty(*stackREF)){
		return NULL;
	}
	else{
		newStackREF = *stackREF;
		gs = newStackREF->gs;
		*stackREF = newStackREF->next;
		free(newStackREF);
	}

	return gs;
}

int isStackEmpty(Stackptr stackREF){
	if(stackREF == NULL)
		return 1;
	return 0;
}
