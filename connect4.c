#include<stdio.h>
#include<stdlib.h>
#include"connect4.h"

struct board_structure {
	char **board_ptr;
	int max_rows;
	int max_cols;
	int num_of_x;
	int num_of_o;
};

board setup_board(){
	board board_to_play = malloc(sizeof(board));
	if (board_to_play == NULL){
		exit(1);
	}
	board_to_play->max_rows = 1;
	board_to_play->max_cols = 4;
	board_to_play->board_ptr = (char**)malloc((board_to_play->max_rows) * sizeof(char*)); // min 1 row 
	if(board_to_play->board_ptr == NULL){
		exit(1);
	}
	(board_to_play->board_ptr)[0] = (char*)malloc((board_to_play->max_cols) * sizeof(char)); // min 4 cols
	if((board_to_play->board_ptr)[0] == NULL){
		exit(1);
	}
	return board_to_play;
}

// void cleanup_board(board u){
// //You may put code here
// }

void print_board(board u){
	for(int x = 0; x < u->max_rows; x++){
		printf("\n");
		for(int y = 0; y < u->max_cols; y++){
			printf("%c", (u->board_ptr)[x][y]);
		}
	}
	printf("\n\n");
}

void read_in_file(FILE *infile, board u){
	char buffer[520]; // need to realloc this somewhere just in case
	int count = 0;
	int curr_row = 0;
	int curr_col = 0;
	
	while(!feof(infile)){
		if(curr_row == u->max_rows){
			u->board_ptr = (char**)realloc(u->board_ptr, ((u->max_rows)+1)*sizeof(*(u->board_ptr)));
			if(u->board_ptr == NULL){
				exit(1);
			}
			u->max_rows++;
			(u->board_ptr)[curr_row] = (char*)malloc((u->max_cols)*sizeof(char));
		}
		fscanf(infile, "%c", &buffer[count]);
		if(buffer[count] == '.' || buffer[count] == 'x' || buffer[count] == 'o'){
			if(curr_col == u->max_cols){
				(u->board_ptr)[curr_row] = (char*)realloc((u->board_ptr)[curr_row], ((u->max_cols)+1)*sizeof(char));
				if((u->board_ptr)[curr_row] == NULL){
					exit(1);
				}
				u->max_cols++;
			}
			(u->board_ptr)[curr_row][curr_col] = buffer[count];
			curr_col++;
		}else{
			curr_row++;
			curr_col = 0;
		}
		count++;
	}

	(u->max_rows)--;
}

void write_out_file(FILE *outfile, board u){
//You may put code here
}

char next_player(board u){
	if(u->num_of_x == 0 && u->num_of_o == 0) return "x";
	if(u->num_of_x > u->num_of_o){
		return "o";
	}else{
		return "x";
	}
}

// char current_winner(board u){
// //You may put code here
// }

struct move read_in_move(board u){
	struct move{
		int chosen_col;
		int chosen_rotation;
	};

	struct player_move = malloc(sizeof(struct move));
	printf("Player %c enter column to place your token: ",next_player(u)); //Do not edit this line
	scanf("%d", &(player_move->chosen_col));
	printf("Player %c enter row to rotate: ",next_player(u)); // Do not edit this line
	scanf("%d", &(player_move->chosen_rotation));

	return player_move;
}

int is_valid_move(struct move m, board u){
	if (m->chosen_col < 1 || m->chosen_col > u->max_cols || m->chosen_rotation < -(u->max_rows) || m->chosen_rotation > u->max_rows) return 0;
	if ((u->board_ptr)[0][(m->chosen_col)-1] == ".") return 0;
}

// char is_winning_move(struct move m, board u){
// //You may put code here
// }

// void play_move(struct move m, board u){
// //You may put code here
// }


