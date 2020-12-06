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
	int rows = 6;
	int cols = 8;
	char board_struc[rows][cols];
	int curr_row = 0;
	int curr_col = 0;
	FILE *infile=fopen("initial_board.txt","r");

	while(!feof(infile)){
		fscanf(infile, "%c", &buffer[count]);
		if(buffer[count] == '.' || buffer[count] == 'x' || buffer[count] == 'o'){
			if(curr_col == cols){
				curr_row++;
				curr_col=0;
			}
			board_struc[curr_row][curr_col] = buffer[count];
			curr_col++;
		}
		count++;
	}
	
	for(int i = 0; i < rows; i++){
		printf("\n");
		for(int j = 0; j < cols; j++){
			printf("%c", board_struc[i][j]);
		}
	}
	printf("\n\n");
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
