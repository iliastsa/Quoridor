#include "data_structs.h"
#include <stdio.h>
#include "utility.h"

extern int movecounter;

int isValidWall(char* color,char* orientation,char* move,int siz,GAMESTATE* gs,int* x_move,int* y_move){
    int move_number;

    if(!strcmp(move,"") || !strcmp(color,"") || !strcmp(orientation,""))       	//First check if the 2 needed arguments are passed.
        return -1;                                      						//Syntax error if they are not.

	if(isWhite(color)){						//Check for amount of walls,
		if(gs->white_walls == 0)
			return 0;
	}
	else if(isBlack(color)){
		if(gs->black_walls == 0)
			return 0;
	}
	else																		//If color is not correct, syntax error
		return -1;

	if(isHorizontal(orientation))
		if(move[0]>='a' && move[0]<'a'+siz-1)
			*y_move = 2*(move[0] - 'a');							//C-like coords(translating input into array [x][y])
		else if (move[0]>='A' && move[0]<'Z'+siz-1)
			*y_move = 2*(move[0] - 'A');							//Array coords for the move.
		else
			return 0;
    else if(isVertical(orientation))
		if(move[0]>='a' && move[0]<'a'+siz-1)
			*y_move = 2*(move[0] - 'a') + 1;
		else if(move[0]>='A' && move[0]<'Z'+siz-1)
			*y_move = 2*(move[0]-'A') + 1;                			//Array coords for the move.
		else
			return 0;
	else
		return 0;

    if (!isInt(&move[1]))
        return 0;

    move_number = atoi(&move[1]);

    if (move_number<2 || move_number>siz)
        return 0;

	if(isHorizontal(orientation))
		*x_move = 2*(siz - move_number)+1;
	else if(isVertical(orientation))
		*x_move = 2*(siz - move_number);

	if(isHorizontal(orientation)){
		if(gs->board[*x_move][*y_move]=='=' || gs->board[*x_move][*y_move+2]=='=')
			return 0;
		if(gs->board[*x_move - 1][*y_move + 1]=='H' && gs->board[*x_move + 1][*y_move + 1]=='H' && gs->board[*x_move][*y_move + 1]=='H')
			return 0;
	}
	if(isVertical(orientation)){
		if(gs->board[*x_move][*y_move]=='H' || gs->board[*x_move+2][*y_move]=='H')
			return 0;
		if(gs->board[*x_move + 1][*y_move -1]=='=' && gs->board[*x_move + 1][*y_move + 1]=='=' && gs->board[*x_move + 1][*y_move]=='='){
			return 0;
		}
	}

    return 1;
}

int isblocked(GAMESTATE* gs,int siz){
	int j,d[100][100],f0=1,f1=1,f2=1,f3=1;

	min_distance(gs->pos_white.x,gs->pos_white.y,2*siz-1,gs->board,d);
	for (j=0; j<2*siz-1; j++){
		if (d[2*siz-2][j]<1000)
			f0=0;
		if (d[0][j]<1000)
			f1=0;
		}

	min_distance(gs->pos_black.x,gs->pos_black.y,2*siz-1,gs->board,d);
	for (j=0; j<2*siz-1; j++){
		if (d[2*siz-2][j]<1000)
			f2=0;
		if (d[0][j]<1000)
			f3=0;
		}

	if (f0 || f1 || f2 || f3)
		return 1;
	return 0;
}

void playwall(char* color,char* move,char* orientation,int siz,GAMESTATE* gs,Stackptr* gsHistory){
	int x_move = 0;
	int y_move = 0;
	int valid = isValidWall(color,orientation,move,siz,gs,&x_move,&y_move);
	if (!valid){
		printf("? illegal move\n\n");
		return;
	}
	else if(valid == -1){
		printf("? syntax error\n\n");
		return;
	}

	if(isHorizontal(orientation)){
		push(gsHistory,*gs);
		gs->board[x_move][y_move] = '=';
		gs->board[x_move][y_move+1] = '=';
		gs->board[x_move][y_move+2] = '=';
		if (isblocked(gs,siz)){
			pop(gsHistory);
			gs->board[x_move][y_move] = '-';
			gs->board[x_move][y_move+1] = '-';
			gs->board[x_move][y_move+2] = '-';
			printf("? illegal move\n\n");
			return;
		}
		movecounter++;
		if(isWhite(color))
		   		gs->white_walls--;
		else if(isBlack(color))
				gs->black_walls--;

	}
	else{
		push(gsHistory,*gs);
		gs->board[x_move][y_move] = 'H';
		gs->board[x_move+1][y_move] = 'H';
		gs->board[x_move+2][y_move] = 'H';
		if (isblocked(gs,siz)){
			pop(gsHistory);
			gs->board[x_move][y_move] = '|';
			gs->board[x_move+1][y_move] = '|';
			gs->board[x_move+2][y_move] = '|';
			printf("? illegal move\n\n");
			return;
		}
		movecounter++;
		if(isWhite(color))
		   		gs->white_walls--;
		else if(isBlack(color))
				gs->black_walls--;
	}

	printf("= \n\n");
}

int trywall(char* color,char* move,char* orientation,int siz,GAMESTATE* gs,int *x_move,int *y_move){
	*x_move = 0;
	*y_move = 0;

	int valid = isValidWall(color,orientation,move,siz,gs,x_move,y_move);

	if(valid != 1)
		return 0;

	if(isHorizontal(orientation)){
			gs->board[*x_move][*y_move] = '=';
			gs->board[*x_move][*y_move+1] = '=';
			gs->board[*x_move][*y_move+2] = '=';
		if (isblocked(gs,siz)){
			gs->board[*x_move][*y_move] = '-';
			gs->board[*x_move][*y_move+1] = '-';
			gs->board[*x_move][*y_move+2] = '-';
			return 0;
		}
		if(isWhite(color))
		   		gs->white_walls--;
		else if(isBlack(color))
				gs->black_walls--;

	}
	else{
		gs->board[*x_move][*y_move] = 'H';
		gs->board[*x_move+1][*y_move] = 'H';
		gs->board[*x_move+2][*y_move] = 'H';
		if (isblocked(gs,siz)){
			gs->board[*x_move][*y_move] = '|';
			gs->board[*x_move+1][*y_move] = '|';
			gs->board[*x_move+2][*y_move] = '|';
			return 0;
		}
		if(isWhite(color))
		   		gs->white_walls--;
		else if(isBlack(color))
				gs->black_walls--;
	}
return 1;
}

// ---------------------------------------------------
void isValidWallMUTE(char* color,char* orientation,char* move,int siz,GAMESTATE* gs,int* x_move,int* y_move){
    *x_move=move[0];
    *y_move=move[1];
}

void playwallMUTE(char* color,char* move,char* orientation,int siz,GAMESTATE* gs){
	int x_move = 0;
	int y_move = 0;
	isValidWallMUTE(color,orientation,move,siz,gs,&x_move,&y_move);

	if(isHorizontal(orientation)){
		gs->board[x_move][y_move] = '=';
		gs->board[x_move][y_move+1] = '=';
		gs->board[x_move][y_move+2] = '=';
		if(isWhite(color))
		   		gs->white_walls--;
		else if(isBlack(color))
				gs->black_walls--;

	}
	else{
		gs->board[x_move][y_move] = 'H';
		gs->board[x_move+1][y_move] = 'H';
		gs->board[x_move+2][y_move] = 'H';
		if(isWhite(color))
		   		gs->white_walls--;
		else if(isBlack(color))
				gs->black_walls--;
	}
}
