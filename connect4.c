#include<stdio.h>
#include<stdlib.h>
#include"connect4.h"

struct board_structure{
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

void cleanup_board(board u){
	// for(int x = 0; x < u->max_rows; x++){
	// 	free(u->board_ptr[x]);
	// }
	free(u->board_ptr);
	free(u);
	// need to fix errors showing on Valgrind
}

void read_in_file(FILE *infile, board u){
	char buffer[520]; // need to realloc this somewhere just in case
	int count = 0;
	int curr_row = 0;
	int curr_col = 0;
	u->num_of_x = 0;
	u->num_of_o = 0;
	
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
			if(buffer[count] == 'x'){
				(u->num_of_x)++;
			}else if(buffer[count] == 'o'){
				(u->num_of_o)++;
			}
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
	
	for(int x = 0; x < u->max_rows; x++){
		for(int y = 0; y < u->max_cols; y++){
			fprintf(outfile, "%c", (u->board_ptr)[x][y]);
		}
		fprintf(outfile, "\n");
	}
	fprintf(outfile, "\n\n");
}

char next_player(board u){
	if(u->num_of_x <= u->num_of_o){
		return 'x';
	}else{
		return 'o';
	}
}

char current_winner(board u){
	int x_is_winner = 0;
	int o_is_winner = 0;
	int empty_space = 0;
	int pos_x, pos_y, count;
	if(u->num_of_x == 0 && u->num_of_o == 0) return '.';
	for(int x = u->max_rows - 1; x >= 0; x--){
		if(x_is_winner && o_is_winner) break;
		for(int y = 0; y < u->max_cols; y++){
			if((u->board_ptr)[x][y] != '.'){

				if((x_is_winner && (u->board_ptr)[x][y] == 'x') || (o_is_winner && (u->board_ptr)[x][y] == 'o')) continue;

				// down
				if(((u->board_ptr)[x+1][y] == (u->board_ptr)[x][y]) && ((u->board_ptr)[x+2][y] == (u->board_ptr)[x][y]) && ((u->board_ptr)[x+3][y] == (u->board_ptr)[x][y])){
					if((u->board_ptr)[x][y] == 'x'){
						x_is_winner = 1;
					}else{
						o_is_winner = 1;
					}
					break;
				}

				// // right
				pos_y = y;
				count = 0;
				for(int i = 0; i < 4; i++){
					if(pos_y >= u->max_cols) pos_y = 0;
					if((u->board_ptr)[x][pos_y] == (u->board_ptr)[x][y]){
						count++;
						pos_y++;
					}else{
						break;
					}
				}
				if((u->board_ptr)[x][y] == 'x' && count ==4){
					x_is_winner = 1;
				}else if((u->board_ptr)[x][y] == 'o' && count ==4){
					o_is_winner = 1;
				}
			
				// // diagonal down right
				pos_x = x;
				pos_y = y;
				count = 0;
				for(int i = 0; i < 4; i++){
					if(pos_y >= u->max_cols) pos_y = 0;
					if(pos_x >= u->max_rows) break;
					if((u->board_ptr)[pos_x][pos_y] == (u->board_ptr)[x][y]){
						count++;
						pos_x++;
						pos_y++;
					}else{
						break;
					}
				}
				if((u->board_ptr)[x][y] == 'x' && count ==4){
					x_is_winner = 1;
				}else if((u->board_ptr)[x][y] == 'o' && count ==4){
					o_is_winner = 1;
				}

				// diagonal up right
				pos_x = x;
				pos_y = y;
				count = 0;
				for(int i = 0; i < 4; i++){
					if(pos_y >= u->max_cols) pos_y = 0;
					if(pos_x >= u->max_rows) break;
					if((u->board_ptr)[pos_x][pos_y] == (u->board_ptr)[x][y]){
						count++;
						pos_x--;
						pos_y++;
					}else{
						break;
					}
				}
				if((u->board_ptr)[x][y] == 'x' && count ==4){
					x_is_winner = 1;
				}else if((u->board_ptr)[x][y] == 'o' && count ==4){
					o_is_winner = 1;
				}

			}
			empty_space++;
		}
	}

	if((x_is_winner && o_is_winner) || (!x_is_winner && !o_is_winner && empty_space == 0)){
		return 'd';
	}else if(x_is_winner){
		return 'x';
	}else if(o_is_winner){
		return 'o';
	}
	return '.';
}

struct move read_in_move(board u){
	struct move player_move;
	printf("Player %c enter column to place your token: ",next_player(u)); //Do not edit this line
	scanf("%d", &(player_move.column));
	printf("Player %c enter row to rotate: ",next_player(u)); // Do not edit this line
	scanf("%d", &(player_move.row));
	
	return player_move;
}

int is_valid_move(struct move m, board u){
	if (m.column < 1 || m.column > u->max_cols || m.row < -(u->max_rows) || m.row > u->max_rows) return 0;
	if ((u->board_ptr)[0][(m.column)-1] == '.') return 1;
	exit(1);
}

// char is_winning_move(struct move m, board u){
// 	return '.';
// }

// this works but neeeds some code clean up 
void play_move(struct move m, board u){
	// rows 1,2 ... bottom to top
	// column 1,2 ... left to right
	int row_selected = u->max_rows - abs(m.row);
	int possible_row;
	int count = 1;
	char current_token;
	char prev_token;
	for(int x = 0; x < u->max_rows; x++){
		if((u->board_ptr)[x][(m.column)-1] == '.'){
				possible_row = x;
		}else{
			break;
		}
	}
	(u->board_ptr)[possible_row][(m.column)-1] = next_player(u); // inserts next player's token into the proper column
	if(next_player(u) == 'x'){
		(u->num_of_x)++;
	}else{
		(u->num_of_o)++;
	}

	if(m.row != 0){
		if(m.row > 0){ // right rotation
			prev_token = (u->board_ptr)[row_selected][0];
			for(int y = 1; y < u->max_cols; y++){
				current_token = (u->board_ptr)[row_selected][y];
				(u->board_ptr)[row_selected][y] = prev_token;
				prev_token = current_token;
				if(y == (u->max_cols) - 1){
					(u->board_ptr)[row_selected][0] = prev_token;
				}
			}
		}else if(m.row < 0){ // left rotation
			prev_token = (u->board_ptr)[row_selected][(u->max_cols) - 1];
			for(int y = (u->max_cols) - 2; y >= 0; y--){
				current_token = (u->board_ptr)[row_selected][y];
				(u->board_ptr)[row_selected][y] = prev_token;
				prev_token = current_token;
				if(y == 0){
					(u->board_ptr)[row_selected][(u->max_cols) - 1] = prev_token;
				}
			}
		}

		for(int x = (u->max_rows)-1; x >= 0; x--){	// applying logic of gravity for tokens falling
			for(int y = 0; y < u->max_cols; y++){
				count = 1;
				if((u->board_ptr)[x][y] == 'x' || (u->board_ptr)[x][y] == 'o'){
					current_token = (u->board_ptr)[x][y];
					possible_row = x;
					while(((u->board_ptr)[x+count][y] == '.') && (x+count < u->max_rows)){
						(u->board_ptr)[x][y] = '.';
						possible_row = x+count;
						count++;
					}
					(u->board_ptr)[possible_row][y] = current_token;
				}
			}
		}
	}
}


