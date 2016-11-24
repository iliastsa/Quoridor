typedef struct gOptions{
    int boardsize;
    int walls;
}OPTIONS;

typedef struct pos{
    int x;
    int y;
}POSITION;

typedef struct gState{
    char board[100][100];
    POSITION pos_white;
    POSITION pos_black;
    int white_walls;
    int black_walls;
    int winner;
}GAMESTATE;

typedef struct sNode* Stackptr;

typedef GAMESTATE* gsPtr;

typedef struct sNode{
	gsPtr gs;
	Stackptr next;
}Stacknode;


