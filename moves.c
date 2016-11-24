#include "data_structs.h"
#include "utility.h"
#include <math.h>
#include <stdio.h>

extern int movecounter;

int manhattan(int x1,int y1,int x2,int y2){
	return (abs(x1-x2)+abs(y1-y2));
}

int isValidMove(char* color,char* move,int siz,GAMESTATE* gs,int* x_move,int* y_move){
	int x,y,move_number;

	if(!strcmp(move,"\0") || !strcmp(color,"\0"))	 	//First check if the 2 needed arguments are passed.
		return -1;										//Syntax error if they are not.

	if(isWhite(color)){
		x = gs->pos_white.x;
		y = gs->pos_white.y;
	}
	else if(isBlack(color)){
		x = gs->pos_black.x;
		y = gs->pos_black.y;
	}
	else
		return -1;

	if (move[0]>='a' && move[0]<='a'+siz)
		*y_move=2*(move[0]-'a'); 				//Array coords for the move.
	else if (move[0]>='A' && move[0]<='A'+siz)
		*y_move=2*(move[0]-'A'); 				//Array coords for the move.
	else
		return 0;

	if (!isInt(&move[1]))
		return 0;

	move_number = atoi(&move[1]);

	if (move_number<0 || move_number>siz)
		return 0;

	*x_move=2*(siz-move_number);

	int man_distance = manhattan(x,y,*x_move,*y_move);

	int direction;

	if(man_distance == 2){

		direction = moveDirection(x,y,*x_move,*y_move);


		if(isWhite(color)){
			if(gs->board[*x_move][*y_move] == 'B')
				return 0;

			if(direction == 1 && gs->board[gs->pos_white.x-1][gs->pos_white.y] == '=')
				return 0;
			else if(direction == -1 && gs->board[gs->pos_white.x+1][gs->pos_white.y] == '=')
				return 0;
			else if(direction == 2 && gs->board[gs->pos_white.x][gs->pos_white.y + 1] == 'H')
				return 0;
			else if(direction == -2 && gs->board[gs->pos_white.x][gs->pos_white.y - 1] == 'H')
				return 0;
		}
		else if(isBlack(color)){
			if(gs->board[*x_move][*y_move] == 'W')
				return 0;

			if(direction == 1 && gs->board[gs->pos_black.x-1][gs->pos_black.y] == '=')
				return 0;
			else if(direction == -1 && gs->board[gs->pos_black.x+1][gs->pos_black.y] == '=')
				return 0;
			else if(direction == 2 && gs->board[gs->pos_black.x][gs->pos_black.y + 1] == 'H')
				return 0;
			else if(direction == -2 && gs->board[gs->pos_black.x][gs->pos_black.y - 1] == 'H')
				return 0;
		}
	}
	else if(man_distance == 4){
		int relativePosition;
                direction = moveDirection(x,y,*x_move,*y_move);


                if(isWhite(color)){
                        if(gs->board[*x_move][*y_move] == 'B')
                                return 0;

                        if(direction == 1 && gs->board[gs->pos_white.x-1][gs->pos_white.y] == '=')
                                return 0;
                        else if(direction == -1 && gs->board[gs->pos_white.x+1][gs->pos_white.y] == '=')
                                return 0;
                        else if(direction == 2 && gs->board[gs->pos_white.x][gs->pos_white.y + 1] == 'H')
                                return 0;
                        else if(direction == -2 && gs->board[gs->pos_white.x][gs->pos_white.y - 1] == 'H')
                                return 0;
                }
                else if(isBlack(color)){
                        if(gs->board[*x_move][*y_move] == 'W')
                                return 0;

                        if(direction == 1 && gs->board[gs->pos_black.x-1][gs->pos_black.y] == '=')
                                return 0;
                        else if(direction == -1 && gs->board[gs->pos_black.x+1][gs->pos_black.y] == '=')
                                return 0;
                        else if(direction == 2 && gs->board[gs->pos_black.x][gs->pos_black.y + 1] == 'H')
                                return 0;
                        else if(direction == -2 && gs->board[gs->pos_black.x][gs->pos_black.y - 1] == 'H')
                                return 0;
                }

		if(isWhite(color)){
			if(manhattan(gs->pos_white.x,gs->pos_white.y,gs->pos_black.x,gs->pos_black.y) == 2){
				relativePosition  = moveDirection(gs->pos_white.x,gs->pos_white.y,gs->pos_black.x,gs->pos_black.y);
				if(relativePosition != moveDirection(gs->pos_black.x,gs->pos_black.y,*x_move,*y_move))
	
					switch(relativePosition){
					case 1:
						if(gs->board[gs->pos_white.x - 1][gs->pos_white.y] == '=')
							return 0;
						if(gs->pos_black.x - 1 != -1 && gs->board[gs->pos_black.x - 1][gs->pos_black.y] != '=')
							return 0;
						break;
					case -1:
						if(gs->board[gs->pos_white.x + 1][gs->pos_white.y] == '=')
							return 0;
						if(gs->pos_black.x + 1 != 2*siz-1 && gs->board[gs->pos_black.x + 1][gs->pos_black.y] != '=')
							return 0;
						break;
					case 2:
						if(gs->board[gs->pos_white.x][gs->pos_white.y + 1] == 'H')
							return 0;
						if(gs->pos_black.y + 1 != 2*siz-1 && gs->board[gs->pos_black.x][gs->pos_black.y + 1] != 'H')
							return 0;
						break;
					case -2:
						if(gs->board[gs->pos_white.x][gs->pos_white.y - 1] == 'H')
							return 0;
						if(gs->pos_black.y - 1 != -1 && gs->board[gs->pos_black.x][gs->pos_black.y - 1] != 'H')
							return 0;
						break;
					}
				return isValidMove("black",move,siz,gs,x_move,y_move);
			}
			else
				return 0;
		}
		else if(isBlack(color)){
			if(manhattan(gs->pos_black.x,gs->pos_black.y,gs->pos_white.x,gs->pos_white.y) == 2){
				relativePosition  = moveDirection(gs->pos_black.x,gs->pos_black.y,gs->pos_white.x,gs->pos_white.y);
				if(relativePosition != moveDirection(gs->pos_white.x,gs->pos_white.y,*x_move,*y_move))
				switch(relativePosition){
				case 1:
					if(gs->board[gs->pos_black.x - 1][gs->pos_black.y] == '=')
						return 0;					
					if(gs->pos_white.x - 1 != -1 && gs->board[gs->pos_white.x - 1][gs->pos_white.y] != '=')
						return 0;
					break;
				case -1:
					if(gs->board[gs->pos_black.x + 1][gs->pos_black.y] == '=')
						return 0;
					if(gs->pos_white.x + 1 != 2*siz-1 && gs->board[gs->pos_white.x + 1][gs->pos_white.y] != '=')
						return 0;
					break;
				case 2:
					if(gs->board[gs->pos_black.x][gs->pos_black.y + 1] == 'H')
						return 0;
					if(gs->pos_white.y + 1 != 2*siz-1 && gs->board[gs->pos_white.x][gs->pos_white.y + 1] != 'H')
						return 0;
					break;
				case -2:
					if(gs->board[gs->pos_black.x][gs->pos_black.y - 1] == 'H')
						return 0;
					if(gs->pos_white.y - 1 != -1 && gs->board[gs->pos_white.x][gs->pos_white.y - 1] != 'H')
						return 0;
					break;
				}
				return isValidMove("white",move,siz,gs,x_move,y_move);
			}
			else
				return 0;
		}
	}
	else
		return 0;

	return 1;
}

void playmove(char* color,char* move,int siz,GAMESTATE* gs,Stackptr* gsHistory){
	int move_x = 0,move_y = 0;

	int valid = isValidMove(color,move,siz,gs,&move_x,&move_y);

	GAMESTATE prev_gs = *gs;

	if(valid == 1){
		movecounter++;
		if(isWhite(color)){
			push(gsHistory,*gs);
			gs->pos_white.x = move_x;
			gs->pos_white.y = move_y;
			if(gs->pos_white.x == 0)
				gs->winner = 1;
			else if(gs->pos_black.x == 2*(siz-1))
				gs->winner = -1;
			else
				gs->winner = 0;
		}
		else if(isBlack(color)){
			push(gsHistory,*gs);
			gs->pos_black.x = move_x;
			gs->pos_black.y = move_y;
			if(gs->pos_black.x == 2*(siz-1))
				gs->winner = -1;
			else if(gs->pos_white.x == 0)
				gs->winner = 1;
			else
				gs->winner = 0;
		}
		remove_pawns(&prev_gs,gs);	//Remove previous pawn position on the board.
		set_board(gs);				//Put them in the new positions.
		printf("= \n\n",move);
	}
	else if(valid == 0)
		printf("? illegal move\n\n");
	else
		printf("? syntax error\n\n");

	fflush(stdout);
}

int moveDirection(int pos_x,int pos_y,int move_x,int move_y){
	if(move_x  < pos_x)
		return 1;	//Moves up
	if(move_x > pos_x)
		return -1;	//Moves down
	if(move_y  > pos_y)
		return 2;	//Moves right
	if(move_y < pos_y)
		return -2;	//Moves left
return 0;
}

void playmoveMUTE(char* color,char* move,int siz,GAMESTATE* gs){
	int move_x =move[0],move_y=move[1] ;

	GAMESTATE prev_gs = *gs;
		if(isWhite(color)){
			gs->pos_white.x = move_x;
			gs->pos_white.y = move_y;
			if(gs->pos_white.x == 0)
				gs->winner = 1;
			else if(gs->pos_black.x == 2*(siz-1))
				gs->winner = -1;
			else
				gs->winner = 0;
		}
		else if(isBlack(color)){
			gs->pos_black.x = move_x;
			gs->pos_black.y = move_y;
			if(gs->pos_white.x == 0)
				gs->winner = 1;
			else if(gs->pos_black.x == 2*(siz-1))
				gs->winner = -1;
			else
				gs->winner = 0;
		}
		remove_pawns(&prev_gs,gs);	//Remove previous pawn position on the board.
		set_board(gs);				//Put them in the new positions.
}
