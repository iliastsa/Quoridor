#include "data_structs.h"
#include "utility.h"
#define NAME "Volitsa"

int movecounter = 0;

int main(void){
        char* cmdlist[] =   {
                            "name","known_command","list_commands","quit", "boardsize" ,
                            "clear_board", "walls","playmove","playwall","genmove",
                            "undo", "winner", "showboard"
							};
        int listsize = sizeof(cmdlist)/sizeof(cmdlist[0]);

        char parameter_list[4][200] = {"\0","\0","\0","\0"};

        int i;

        Stackptr gsHistory = NULL;

        OPTIONS game_options;

        game_options.walls = 2;

        game_options.boardsize = 3;

        GAMESTATE gs;


        set_empty(game_options.boardsize,game_options.walls,&gs,&gsHistory);

		getcmd(&parameter_list);

		while(strcmp(parameter_list[0],"quit")!=0){

            if(!strcmp(parameter_list[0],"name")){               	//name
                name(NAME);
                fflush(stdout);
            }
            else if(!strcmp(parameter_list[0], "known_command")){   //known_command
                known_cmd(parameter_list[1],cmdlist,listsize);
                fflush(stdout);
            }
            else if(!strcmp(parameter_list[0],"list_commands")){ 	//list_commands
                printCmdList(cmdlist,listsize);
                fflush(stdout);
            }
            else if(!strcmp(parameter_list[0],"boardsize")){		//boardsize
                setBoardSize(&game_options,parameter_list[1],&gs,&gsHistory);
                fflush(stdout);
            }
            else if(!strcmp(parameter_list[0],"walls")){			//walls
                setWalls(&game_options,parameter_list[1],&gs,&gsHistory);
                fflush(stdout);
            }
            else if(!strcmp(parameter_list[0],"showboard")){		//showboard
                printBoard(gs.board,game_options.boardsize,gs.black_walls,gs.white_walls);
                fflush(stdout);
            }
            else if(!strcmp(parameter_list[0],"clear_board")){		//clear_board
				set_empty(game_options.boardsize,game_options.walls,&gs,&gsHistory);
				printf("= \n\n");
				fflush(stdout);
            }
			else if(!strcmp(parameter_list[0],"playmove")){			//playmove
				playmove(parameter_list[1],parameter_list[2],game_options.boardsize,&gs,&gsHistory);
				fflush(stdout);
			}
			else if(!strcmp(parameter_list[0],"playwall")){			//playwall
				playwall(parameter_list[1],parameter_list[2],parameter_list[3],game_options.boardsize,&gs,&gsHistory);
				fflush(stdout);
			}
			else if(!strcmp(parameter_list[0],"genmove")){			//genmove
				genmove(parameter_list[1],&gs,game_options.boardsize,&gsHistory);
				fflush(stdout);
			}
			else if(!strcmp(parameter_list[0],"undo")){
				undo(&gsHistory,&gs,parameter_list[1]);
				fflush(stdout);
			}
			else if(!strcmp(parameter_list[0],"winner")){
				winner(&gs);
				fflush(stdout);
			}
            else if(!strcmp(parameter_list[0],"\0"))            	//Ignore null(and subsequently \n due to the input handling that is done)
                ;
            else{
                printf("? unknown command\n\n");
				fflush(stdout);										//Unknown command
            }
            for(i=0;i<4;i++)
                parameter_list[i][0] = '\0';						//Empty Parameter list;

            getcmd(&parameter_list);								//Read next command
        }
        printf("= \n\n");
		fflush(stdout);
return 0;
}
