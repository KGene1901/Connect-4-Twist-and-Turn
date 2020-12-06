#include<stdio.h>
#include<stdlib.h>
#include"connect4.h"

struct board_structure {
 // need to keep track positions of 'x' and 'o'
};

board setup_board(){
	board board_to_play = malloc(sizeof(board));
	if (board_to_play == NULL){
		exit(1);
	}
	return board_to_play;
}

void cleanup_board(board u){
//You may put code here
}

void read_in_file(FILE *infile, board u){
	char buffer[520];
	int count = 0;
	int max_rows = 1;
	int max_cols = 4;
	char **board_ptr;
	int curr_row = 0;
	int curr_col = 0;
	int first_loop = 1;
	FILE *infile=fopen("initial_board.txt","r");
	
	board_ptr = (char**)malloc(1 * sizeof(char*)); // min 1 row 
	board_ptr[0] = (char*)malloc(4 * sizeof(char)); // min 4 cols

	while(!feof(infile)){
		if(curr_row == max_rows){
			board_ptr = (char**)realloc(board_ptr, (max_rows+1)*sizeof(*board_ptr));
			if(board_ptr == NULL){
				exit(1);
			}
			max_rows++;
			board_ptr[curr_row] = (char*)malloc(max_cols*sizeof(char));
		}
		fscanf(infile, "%c", &buffer[count]);
		if(buffer[count] == '.' || buffer[count] == 'x' || buffer[count] == 'o'){
			if(curr_col == max_cols){
				board_ptr[curr_row] = (char*)realloc(board_ptr[curr_row], (max_cols+1)*sizeof(char));
				if(board_ptr[curr_row] == NULL){
					exit(1);
				}
				max_cols++;
			}
			board_ptr[curr_row][curr_col] = buffer[count];
			curr_col++;
		}else{
			curr_row++;
			curr_col = 0;
		}
		count++;
	}

	max_rows--;


	// for(int i = 0; i < max_rows; i++){
	// 	printf("\n");
	// 	for(int j = 0; j < max_cols; j++){
	// 		printf("%c", board_ptr[i][j]);
	// 	}
	// }
	// printf("\n\n");
	// printf("Total rows: %d  Total columns: %d\n", max_rows, max_cols);

	fclose(infile);
}

void write_out_file(FILE *outfile, board u){
//You may put code here
}

char next_player(board u){
//You may put code here
}

char current_winner(board u){
//You may put code here
}

struct move read_in_move(board u){
//You may put code here
  printf("Player %c enter column to place your token: ",next_player(u)); //Do not edit this line
//You may put code here
  printf("Player %c enter row to rotate: ",next_player(u)); // Do not edit this line
//You may put code here
}

int is_valid_move(struct move m, board u){
//You may put code here
}

char is_winning_move(struct move m, board u){
//You may put code here
}

void play_move(struct move m, board u){
//You may put code here
}

//You may put additional functions here if you wish.
