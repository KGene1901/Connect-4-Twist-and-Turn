#include<stdio.h>
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
