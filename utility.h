#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void name(char* name);
void known_cmd(char* cmd, char* cmdlist[],int listsize);
void printCmdList(char** cmdlist,int listsize);
void removeCOMM(char* s);
void getcmd(char (*parameter_list)[4][200]);
void setBoardSize(OPTIONS* option_set,char* bsize,GAMESTATE* gs,Stackptr* gsHistory);
void setWalls(OPTIONS* option_set,char* wnumber,GAMESTATE* gs,Stackptr* gsHistory);
int isInt(char* parameter);
int isWhite(char* color);
int isBlack(char* color);
void removeHT(char* s);
void removeNL(char* s);
void set_empty(int real_size,int walls,GAMESTATE *gs,Stackptr* StackRef);
void printBoard(char A[100][100],int real_size,int black_walls,int white_walls);
int manhattan(int a1,int b1,int a2,int b2);
int isValidMove(char* color,char* move,int siz,GAMESTATE* gs,int* x_move,int* y_move);
void playmove(char* color,char* move,int siz,GAMESTATE* gs,Stackptr* gsHistory);
void set_board(GAMESTATE *gs);
void remove_pawns(GAMESTATE *prev_gs,GAMESTATE* gs);
int moveDirection(int pos_x,int pos_y,int move_x,int move_y);
int isValidWall(char* color,char* orientation,char* move,int siz,GAMESTATE* gs,int* x_wall,int* y_wall);
void playwall(char* color,char* move,char* orientation,int siz,GAMESTATE* gs,Stackptr* gsHistory);
void toLowerCase(char* str);
int isHorizontal(char* orientation);
int isVertical(char* orientation);
void makemovelist(GAMESTATE* gs,int siz,char* color,int* k,char array[][4]);
int trywall(char* color,char* move,char* orientation,int siz,GAMESTATE* gs,int* x_move,int* y_move);
void min_distance(int x,int y,int siz,char A[100][100],int D[100][100]);
int isStackEmpty(Stackptr stackREF);
GAMESTATE* pop(Stackptr* stackREF);
void push(Stackptr* stackREF,GAMESTATE gs);
GAMESTATE* newHistoryEntry(GAMESTATE gs);
void undo(Stackptr* stackREF,GAMESTATE* gs,char* moveStr);
void winner(GAMESTATE* gs);
void firstminimax(GAMESTATE  *gs, int depth,int siz,char* color,char* bestmoveS,int maximizing,double a,double b);
void playwallMUTE(char* color,char* move,char* orientation,int siz,GAMESTATE* gs);
void isValidWallMUTE(char* color,char* orientation,char* move,int siz,GAMESTATE* gs,int* x_move,int* y_move);
void playmoveMUTE(char* color,char* move,int siz,GAMESTATE* gs);
double minimax(GAMESTATE  *gs, int depth,int siz,char* color,int maximizing,double a ,double b);
int checkwin(GAMESTATE* gs);
void genmove(char* color,GAMESTATE* gs,int siz,Stackptr* stackREF);
double evaluate(GAMESTATE* gs,int siz,char* color);
void undoMute(Stackptr* stackREF,GAMESTATE* gs,char* moveStr);