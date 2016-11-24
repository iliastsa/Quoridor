#include "data_structs.h"
#include "utility.h"
#define SPP 0.867
#define SPO -0.596
#define MDO -0.792
#define NFP 0.227
#define INFINITY 1000000.0

static char maxColor[7];
static int SIZ;


extern int movecounter;

void genmove(char* color,GAMESTATE* gs,int siz,Stackptr* gsHistory){
	char move[10];
	SIZ=siz;
	strcpy(maxColor,color);
	if(isWhite(color) || isBlack(color))
		firstminimax(gs,3,siz,color,move,1,-INFINITY,INFINITY);
	else{
		printf("? Syntax error\n\n");
		return;
	}
	push(gsHistory,*gs);
	if(move[0] == 'm'){
		playmoveMUTE(maxColor,&move[1],siz,gs);
		printf("= %c%d",move[2]/2+'A',siz-move[1]/2);
	}
	else{
		playwallMUTE(maxColor,&move[1],&move[3],siz,gs);
		printf("= %c%d %c",'A'+move[2]/2,siz-move[1]/2,move[3]);
	}
	movecounter++;
	printf("\n\n");
}

void firstminimax(GAMESTATE  *gs, int depth,int siz,char* color,char bestmoveS[10],int maximizing,double a, double b){
	char list[800][4] = {0};
	char nextColor[7];
	int i = 0,k;
	int bestmove = 0;
	double bestvalue,value;

	GAMESTATE* previousgs = malloc(sizeof(struct gState));
	*previousgs = *gs;

	if(checkwin(gs)) return;

	makemovelist(gs,siz,color,&k,list);

	bestvalue=-INFINITY;
	for(i=0; i<k; i++){
                if(isWhite(color))
                        strcpy(nextColor,"black");
                else
                        strcpy(nextColor,"white");

		if(list[i][0] == 'm'){
			playmoveMUTE(color,&list[i][1],siz,gs);
	                value = minimax(gs,depth-1,siz,nextColor,0,a,b);

		}
		else{
			playwallMUTE(color,&list[i][1],&list[i][3],siz,gs);
	                value = minimax(gs,depth-1,siz,nextColor,0,a,b);

		}

		*gs = *previousgs;
		if(value == INFINITY){
			bestmove=i;
			break;
		}
		if(value > bestvalue){
			bestvalue = value;
			bestmove=i;
		}
		if(a < bestvalue)
			a = bestvalue;
		if(b<=a)
			break;
	}
	bestmoveS[0]=list[bestmove][0];
	bestmoveS[1]=list[bestmove][1];
	bestmoveS[2]=list[bestmove][2];
	bestmoveS[3]=list[bestmove][3];
	free(previousgs);
}

double minimax(GAMESTATE  *gs, int depth,int siz,char* color,int maximizing,double a,double b){
	char list[800][4] = {0};
	char nextColor[7];
	int i,k;
	double bestvalue,value;
	GAMESTATE* previousgs = malloc(sizeof(struct gState));
	*previousgs = *gs;


	if(maximizing){
		if ((checkwin(gs)==1 && isBlack(color)) || (checkwin(gs) == -1 && isWhite(color))){
			free(previousgs);
			return -INFINITY;
		}
	}
	else{
		if((checkwin(gs)==1 && isBlack(color)) || (checkwin(gs) == -1 && isWhite(color))){
			free(previousgs);
			return INFINITY;
		}
	}
	if(depth<=0){
		free(previousgs);
		return evaluate(gs,siz,color);
	}

	makemovelist(gs,siz,color,&k,list);

	if (maximizing){
		bestvalue=-INFINITY;
		for(i=0; i<k; i++){
                        if(isWhite(color))
                                strcpy(nextColor,"black");
                        else
                                strcpy(nextColor,"white");

			if(list[i][0] == 'm'){
				playmoveMUTE(color,&list[i][1],siz,gs);
	                        value = minimax(gs,depth-1,siz,nextColor,0,a,b);
			}
			else{
				playwallMUTE(color,&list[i][1],&list[i][3],siz,gs);
	                        value = minimax(gs,depth-1,siz,nextColor,0,a,b);
			}
			*gs = *previousgs;
			if(value > bestvalue)
				bestvalue = value;
			if(a < bestvalue)
				a = bestvalue;
			if(b<=a)
				break;
		}
	}
	else {
		bestvalue=INFINITY;
		for(i=0; i<k; i++){
                        if(isWhite(color))
                                strcpy(nextColor,"black");
                        else
                                strcpy(nextColor,"white");

			if(list[i][0] == 'm'){
				playmoveMUTE(color,&list[i][1],siz,gs);
				value = minimax(gs,depth-1,siz,nextColor,1,a,b);

			}
			else{
				playwallMUTE(color,&list[i][1],&list[i][3],siz,gs);
				value = minimax(gs,depth-1,siz,nextColor,1,a,b);
			}
			*gs = *previousgs;
			if(value < bestvalue)
				bestvalue = value;
			if(b > bestvalue)
				b = bestvalue;
			if(b<=a)
				break;
		}
	}

	free(previousgs);

 return bestvalue;
}

double evaluate(GAMESTATE* gs,int siz,char* color){
		int j,mo,sp=1000,so=1000;
		double value=0.0;


		int dt[100][100];
		if(isWhite(maxColor)){
			min_distance(gs->pos_white.x,gs->pos_white.y,2*siz-1,gs->board,dt);

			for (j=0; j<2*siz-1; j++)
				    if (dt[0][j]<sp)
				    sp=dt[0][j];

			min_distance(gs->pos_black.x,gs->pos_black.y,2*siz-1,gs->board,dt);

			for (j=0; j<2*siz-1; j++)
			    if (dt[2*siz-2][j]<so)
				    so=dt[2*siz-2][j];

			mo=abs(2*siz-1-gs->pos_black.x);


			value+=SPP*((siz*siz-sp)/(double)(siz*siz));
			value+=SPO*((siz*siz*siz*siz-so*so)/(double)(siz*siz*siz*siz));
			value+=MDO*((2*siz-mo)/(2.0*siz));
			value+=NFP*gs->white_walls/10;

		}
		else{
			min_distance(gs->pos_black.x,gs->pos_black.y,2*siz-1,gs->board,dt);

			for (j=0; j<2*siz-1; j++)
				    if (dt[2*siz-2][j]<sp)
				    	sp=dt[2*siz-2][j];

			min_distance(gs->pos_white.x,gs->pos_white.y,2*siz-1,gs->board,dt);

			for (j=0; j<2*siz-1; j++)
			    if (dt[0][j]<so)
				    so=dt[0][j];

			mo=abs(gs->pos_white.x);

			value+=SPP*((siz*siz-sp)/(double)(siz*siz));
			value+=SPO*((siz*siz*siz*siz-so*so)/(double)(siz*siz));
			value+=MDO*((2*siz-mo)/(2.0*siz));
			value+=NFP*gs->black_walls/10;
		}

return value;
}




void makemovelist(GAMESTATE* gs,int siz,char* color,int* k,char array[][4]){
	GAMESTATE gsTest = *gs;

	int i,j,o;
	char* orientation;
	*k=0;
	int x_move =0,y_move=0;
	char move[4] = "\0";
	if(isWhite(color)){
		for(i = 0;i<2*siz-1;i+=2){
			for(j = 0;j<2*siz-1;j+=2){
				sprintf(move,"%c%d",'a'+ j/2,siz - i/2);
				if(isValidMove(color,move,siz,gs,&x_move,&y_move)){
					array[*k][0] = 'm';
					array[*k][1] = x_move;
					array[(*k)++][2] = y_move;
				}
			}
		}

		for(o = 0; o<2;o++){
			if(o == 0)
				orientation = "horizontal";
			else
				orientation = "vertical";

			for(i = 1;i<2*siz -2;i+=2){
				for(j = 1;j<2*siz-2;j+=2){
					if(o == 0)
						sprintf(move,"%c%d",'a'+ j/2,siz - (i-1)/2);
					else
						sprintf(move,"%c%d",'a'+ (j-1)/2,siz - i/2);
					if(trywall(color,move,orientation,siz,&gsTest,&x_move,&y_move)){
						array[*k][0] = 'w';
						array[*k][1] = x_move;
						array[*k][2] = y_move;
						array[(*k)++][3] = orientation[0];
					gsTest = *gs;
					}
				}
			}
		}
	}
	else{
		for(i = 2*siz-2;i>=0;i-=2){
			for(j = 2*siz-2;j>=0;j-=2){
				sprintf(move,"%c%d",'a'+ j/2,siz - i/2);
				if(isValidMove(color,move,siz,gs,&x_move,&y_move)){
					array[*k][0] = 'm';
					array[*k][1] = x_move;
					array[(*k)++][2] = y_move;
				}
			}
		}

		for(o = 0; o<2;o++){
			if(o == 0)
				orientation = "horizontal";
			else
				orientation = "vertical";

			for(i = 1;i<2*siz -2;i+=2){
				for(j = 1;j<2*siz-2;j+=2){
					if(o == 0)
						sprintf(move,"%c%d",'a'+ j/2,siz - (i-1)/2);
					else
						sprintf(move,"%c%d",'a'+ (j-1)/2,siz - i/2);
					if(trywall(color,move,orientation,siz,&gsTest,&x_move,&y_move)){
						array[*k][0] = 'w';
						array[*k][1] = x_move;
						array[*k][2] = y_move;
						array[(*k)++][3] = orientation[0];
					gsTest = *gs;
					}
				}
			}
		}

	}
}

int checkwin(GAMESTATE* gs){
	if (gs->pos_white.x==0)
		return 1;
	else if (gs->pos_black.x==2*SIZ-2)
		return -1;
	return 0;
}

