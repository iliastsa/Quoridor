#include "data_structs.h"
#include "utility.h"

extern int movecounter;
/*Commands*/
void name(char* name){
    printf("= %s\n\n", name);
}

void known_cmd(char* cmd, char* cmdlist[],int listsize){
    int i,IsInList = 0;
    for(i=0;i<listsize;i++)
        if(!strcmp(cmd,cmdlist[i])){
            IsInList = 1;
            break;
        }
    printf("%s\n\n",((IsInList) ? "= true" : "? false"));
}

void printCmdList(char** cmdlist,int listsize){
    int i;
    printf("=\n");
    for(i = 0; i<listsize;i++)
        printf("%s\n", cmdlist[i]);
	printf("\n\n");
}

void setBoardSize(OPTIONS* option_set,char* bsize,GAMESTATE* gs,Stackptr* gsHistory){
    if(isInt(bsize)){
		if(atoi(bsize)%2 && atoi(bsize) <=25 && atoi(bsize)>=3){
        option_set -> boardsize = atoi(bsize);
        set_empty(option_set->boardsize,option_set->walls,gs,gsHistory);
        printf("= \n\n");
        return;
		}
    }
        printf("? unacceptable size\n\n");

}

void setWalls(OPTIONS* option_set,char* wnumber,GAMESTATE* gs,Stackptr* gsHistory){
    if(isInt(wnumber)){
        option_set -> walls = atoi(wnumber);
		set_empty(option_set->boardsize,option_set->walls,gs,gsHistory);
        printf("= \n\n");
    }
    else
        printf("? unacceptable wall number \n\n");
}

/*String and input manipulation/handling*/
int isInt(char* parameter){
    int i;
    for(i = 0;i<strlen(parameter);i++)
        if(parameter[i]<'0' || parameter[i]>'9')
            return 0;
return 1;
}

void toLowerCase(char* str){
	int i = 0;
	while(str[i] != '\0'){
		if('A'<=str[i] &&  str[i]<='Z')
			str[i] += 'a'-'A';
		i++;
	}
}

int isVertical(char* orientation){
	toLowerCase(orientation);
	return (!strcmp("vertical",orientation) || !strcmp("v",orientation));
}

int isHorizontal(char* orientation){
	toLowerCase(orientation);
	return (!strcmp("horizontal",orientation) || !strcmp("h",orientation));
}

int isWhite(char* color){
	toLowerCase(color);
	return (!strcmp("white",color) || !strcmp("w",color));
}

int isBlack(char* color){
	toLowerCase(color);
	return (!strcmp("black",color) || !strcmp("b",color));
}

void removeHT(char* s){
    while(*s != '\0'){
        if(*s == '\t')
            *s = ' ';
        s++;
    }
}

void removeNL(char* s){
    while(*s != '\0'){
        if(*s == '\n')
            *s = '\0'; //Strings end with \n
        s++;
    }
}

void removeCOMM(char* s){
    char* p;
    while(*s != '#' && *s != '\0')
        s++;
    p = s;
    *p++ = '\n'; // Replace # with \n so that it passes the check below(simpler code).
    while(*p != '\0'){
        *p = '\0';
        p++;
    }
}

void getcmd(char (*parameter_list)[4][200]){
        char cmd[200];
        char* p;
        int i;
        i = 0;
        fgets(cmd,200,stdin);
        removeHT(cmd);
        removeCOMM(cmd);
        if(!(strcmp(cmd,"\n")))
            (*parameter_list)[0][0] = '\n';
        p = strtok(cmd," ");
        while(p != NULL){
                strcpy((*parameter_list)[i],p);
                removeNL((*parameter_list)[i]);
                p = strtok(NULL," ");
                i++;
        }
}

/*Board management*/
void set_board(GAMESTATE *gs){
	gs->board[gs->pos_white.x][gs->pos_white.y] = 'W';
	gs->board[gs->pos_black.x][gs->pos_black.y] = 'B';
}

void remove_pawns(GAMESTATE *prev_gs,GAMESTATE* gs){
	gs->board[prev_gs->pos_white.x][prev_gs->pos_white.y] = ' ';
	gs->board[prev_gs->pos_black.x][prev_gs->pos_black.y] = ' ';
}

void set_empty(int real_size,int walls,GAMESTATE *gs,Stackptr* gsHistory){
    int siz = 2*real_size -1;
    int i,j;
    char moveStr[7];
    for (i=0; i<siz; i++)
        for (j=0; j<siz; j++)
            gs->board[i][j]=' ';
    gs->board[0][siz/2]='B';
    gs->board[siz-1][siz/2]='W';
    gs->pos_black.x=0;
    gs->pos_black.y=siz/2;
    gs->pos_white.x=siz-1;
    gs->pos_white.y=siz/2;
    gs->white_walls = walls;
    gs->black_walls = walls;
    gs->winner = 0;
    sprintf(moveStr,"%d\0",movecounter);
    undoMute(gsHistory,gs,moveStr);
}

void printBoard(char A[100][100],int real_size,int black_walls,int white_walls){
    int siz = 2*real_size -1;
    int i,j;
    printf("  ");
    for (i=0; i<siz/2+1; i++)
        printf("   %c",'A'+i);
    printf("\n   +");
    for (i=0; i<siz/2+1; i++)
        printf("---+",'A'+i);
    printf("\n");

    for (i=0; i<siz; i++){
        if (i%2==0){
            printf("%-3d|",(siz-i)/2+1);
            for (j=0; j<siz; j++){
                if (j%2==0)
                    printf(" %c ",A[i][j]);
                else {
                    if (A[i][j]==' ')
                        A[i][j]='|';
                    printf("%c",A[i][j]);
                     }
            }
            printf("|  %d",(siz-i)/2+1);
            if (i==0) printf("  black walls: %d",black_walls);
            if (i==2) printf("  white walls: %d",white_walls);
        }

        else {
            printf("   +");
            for (j=0; j<siz; j++){
                if (j%2==0){
                    if (A[i][j]==' ')
                        A[i][j]='-';
                    printf("%c%c%c",A[i][j],A[i][j],A[i][j]);
                    }
                else {
			if (A[i][j]=='=' || A[i][j]=='H')
				printf("%c",A[i][j]);
			else
		                printf("+");
		}
            }
	    printf("+");
        }
    printf("\n");
    }
    printf("   +");
    for (i=0; i<siz/2+1; i++)
        printf("---+",'A'+i);
    printf("\n");
    printf("  ");
    for (i=0; i<siz/2+1; i++)
        printf("   %c",'A'+i);
    printf("\n");
}

void winner(GAMESTATE* gs){
	if(gs->winner)
		printf("= true %s\n\n",(gs->winner == 1)? "white":"black");
	else
		printf("= false\n\n");
}

/*Game history management*/
void undo(Stackptr* gsHistory,GAMESTATE* gs,char* moveStr){
	int moves;
	if(*moveStr == '\0')
		moves = 1; 	//Default undo value if not specified
	else{
		if(!isInt(moveStr)){
			printf("? Syntax error\n\n");
			return;
		}
		moves = atoi(moveStr);
	}
	int i;
	Stackptr temp = *gsHistory;
	for(i = 0; i<moves;i++){	//First check if undo-ing that many moves is possible.
		if(temp == NULL){	//If it's not, print error message.
			printf("? can not undo\n\n");
			return;		//and exit the function.
		}
		temp = temp->next;	//Traverse through the  game history stack, for "moves" entries.
	}
	GAMESTATE *tempgs;
	for(i=0;i<moves;i++){		//Start removing entities from the game history stack.
		tempgs = pop(gsHistory);
		movecounter--;
	}

	if (moves) {	//Copy the last element removed to the current state, thus completing the undo process
		*gs = *tempgs;
		free(tempgs);
	}
	printf("= \n\n");
}


void undoMute(Stackptr* gsHistory,GAMESTATE* gs,char* moveStr){
	int moves;
	if(*moveStr == '\0')
		moves = 1;
	else{
		if(!isInt(moveStr)){
			return;
		}
		moves = atoi(moveStr);
	}
	int i;
	Stackptr temp = *gsHistory;
	for(i = 0; i<moves;i++){
		if(temp == NULL){
			return;
		}
		temp = temp->next;
	}
	GAMESTATE *tempgs;
	for(i=0;i<moves;i++){
		tempgs = pop(gsHistory);
		movecounter--;
	}

	if (moves) {
	*gs = *tempgs;
	free(tempgs);
	}
}
