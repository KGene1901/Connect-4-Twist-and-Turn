#include<stdio.h>
#include<stdlib.h>
#include"connect4.h"

struct board_structure{
	char **board_ptr;
	int max_rows;
	int max_cols;
	int num_of_x;
	int num_of_o;
	int *win_info;
};

board setup_board(){
	board board_to_play = malloc(sizeof(struct board_structure));
	if (board_to_play == NULL) exit(1);

	board_to_play->max_rows = 1;
	board_to_play->max_cols = 4;

	board_to_play->win_info = (int*)malloc(6*sizeof(int)); // {x.x, x.y, x.dir, o.x, o.y, o.dir}
	if(board_to_play->win_info == NULL) exit(1);

	board_to_play->win_info[0] = -1;
	board_to_play->win_info[1] = -1;
	board_to_play->win_info[2] = -1;
	board_to_play->win_info[3] = -1;
	board_to_play->win_info[4] = -1;
	board_to_play->win_info[5] = -1;

	board_to_play->board_ptr = (char**)malloc((board_to_play->max_rows) * sizeof(char*)); // min 1 row 
	if(board_to_play->board_ptr == NULL) exit(1);

	(board_to_play->board_ptr)[0] = (char*)malloc((board_to_play->max_cols) * sizeof(char)+1); // min 4 cols
	if((board_to_play->board_ptr)[0] == NULL) exit(1);
	
	return board_to_play;
}

void cleanup_board(board u){
	free(u->win_info);
	for(int i = 0; i <= u->max_rows; i++) free(u->board_ptr[i]);
	free(u->board_ptr);
	free(u);
}

void read_in_file(FILE *infile, board u){
	char symbol[2];
	int count = 0;
	int curr_row = 0;
	int curr_col = 0;
	u->num_of_x = 0;
	u->num_of_o = 0;
	
	while(!feof(infile)){
		if(curr_row == u->max_rows){
			u->board_ptr = (char**)realloc(u->board_ptr, ((u->max_rows)+1)*sizeof(char*));
			if(u->board_ptr == NULL) exit(1);
			u->max_rows++;
			(u->board_ptr)[curr_row] = (char*)malloc((u->max_cols)*sizeof(char)+1);
		}
		fscanf(infile, "%c", &symbol[0]);
		if(symbol[0] == '.' || symbol[0] == 'x' || symbol[0] == 'o'){
			if(curr_col == u->max_cols){
				(u->board_ptr)[curr_row] = (char*)realloc((u->board_ptr)[curr_row], ((u->max_cols))*sizeof(char)+1);
				if((u->board_ptr)[curr_row] == NULL) exit(1);
				u->max_cols++;
			}
			(u->board_ptr)[curr_row][curr_col] = symbol[0];
			if(symbol[0] == 'x'){
				(u->num_of_x)++;
			}else if(symbol[0] == 'o'){
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

	char cur_winner = current_winner(u);
	if(cur_winner == 'x' || cur_winner == 'd'){
		if((u->win_info)[0] != -1 && (u->win_info)[1] != -1 && (u->win_info)[2] != -1){
			// down
			if((u->win_info)[2] == 1){
				for(int i = (u->win_info)[0]; i<=(u->win_info)[0]+3; i++){
					(u->board_ptr)[i][(u->win_info)[1]] = 'X';
				}
			}

			// right
			if((u->win_info)[2] == 2){
				for(int i = 0; i < 4; i++){
					if((u->win_info)[1] >= u->max_cols) (u->win_info)[1] = 0;
					(u->board_ptr)[(u->win_info)[0]][(u->win_info)[1]] = 'X';
					(u->win_info)[1]++;
				}
			}

			// diagonal up right
			if((u->win_info)[2] == 3){
				for(int i = 0; i < 4; i++){
					if((u->win_info)[1] >= u->max_cols) (u->win_info)[1] = 0;
					if((u->win_info)[0] >= u->max_rows) break;
					(u->board_ptr)[(u->win_info)[0]][(u->win_info)[1]] = 'X';
					(u->win_info)[0]--;
					(u->win_info)[1]++;
				}
			}

			// diagonal down right
			if((u->win_info)[2] == 4){
				for(int i = 0; i < 4; i++){
					if((u->win_info)[1] >= u->max_cols) (u->win_info)[1] = 0;
					if((u->win_info)[0] >= u->max_rows) break;
					(u->board_ptr)[(u->win_info)[0]][(u->win_info)[1]] = 'X';
					(u->win_info)[0]++;
					(u->win_info)[1]++;
				}
			}

		}
	}

	if(cur_winner == 'o' || cur_winner == 'd'){
		if(((u->win_info)[3] != -1 && (u->win_info)[4] != -1) && (u->win_info)[5] != -1){
			// down
			if((u->win_info)[5] == 1){
				for(int i = (u->win_info)[3]; i<=(u->win_info)[3]+3; i++){
					(u->board_ptr)[i][(u->win_info)[4]] = 'O';
				}
			}

			// right
			if((u->win_info)[5] == 2){
				for(int i = 0; i < 4; i++){
					if((u->win_info)[4] >= u->max_cols) (u->win_info)[4] = 0;
					(u->board_ptr)[(u->win_info)[3]][(u->win_info)[4]] = 'O';
					(u->win_info)[4]++;
				}
			}

			// diagonal up right
			if((u->win_info)[5] == 3){
				for(int i = 0; i < 4; i++){
					if((u->win_info)[4] >= u->max_cols) (u->win_info)[4] = 0;
					if((u->win_info)[3] >= u->max_rows) break;
					(u->board_ptr)[(u->win_info)[3]][(u->win_info)[4]] = 'O';
					(u->win_info)[3]--;
					(u->win_info)[4]++;
				}
			}

			// diagonal down right
			if((u->win_info)[5] == 4){
				for(int i = 0; i < 4; i++){
					if((u->win_info)[4] >= u->max_cols) (u->win_info)[4] = 0;
					if((u->win_info)[3] >= u->max_rows) break;
					(u->board_ptr)[(u->win_info)[3]][(u->win_info)[4]] = 'O';
					(u->win_info)[3]++;
					(u->win_info)[4]++;
				}
			}
		}
	}

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
				pos_x = x;
				count = 0;
				for(int i = 0; i < 4; i++){
					if(pos_x >= u->max_rows) break;
					if((u->board_ptr)[pos_x][y] == (u->board_ptr)[x][y]){
						count++;
						pos_x++;
					}else{
						break;
					}
				}
				if(((u->board_ptr)[x][y] == 'x' || (u->board_ptr)[x][y] == 'X') && count ==4){
					(u->win_info)[0] = x;
					(u->win_info)[1] = y;
					(u->win_info)[2] = 1;
					x_is_winner = 1;
					continue;
				}else if(((u->board_ptr)[x][y] == 'o' || (u->board_ptr)[x][y] == 'O') && count ==4){
					(u->win_info)[3] = x;
					(u->win_info)[4] = y;
					(u->win_info)[5] = 1;
					o_is_winner = 1;
					continue;
				}

				// right
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
				if(((u->board_ptr)[x][y] == 'x' || (u->board_ptr)[x][y] == 'X') && count ==4){
					(u->win_info)[0] = x;
					(u->win_info)[1] = y;
					(u->win_info)[2] = 2;
					x_is_winner = 1;
					continue;
				}else if(((u->board_ptr)[x][y] == 'o' || (u->board_ptr)[x][y] == 'O') && count ==4){
					(u->win_info)[3] = x;
					(u->win_info)[4] = y;
					(u->win_info)[5] = 2;
					o_is_winner = 1;
					continue;
				}
			
				// diagonal down right
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
				if(((u->board_ptr)[x][y] == 'x' || (u->board_ptr)[x][y] == 'X') && count ==4){
					(u->win_info)[0] = x;
					(u->win_info)[1] = y;
					(u->win_info)[2] = 4;
					x_is_winner = 1;
					continue;
				}else if(((u->board_ptr)[x][y] == 'o' || (u->board_ptr)[x][y] == 'O') && count ==4){
					(u->win_info)[3] = x;
					(u->win_info)[4] = y;
					(u->win_info)[5] = 4;
					o_is_winner = 1;
					continue;
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
				if(((u->board_ptr)[x][y] == 'x' || (u->board_ptr)[x][y] == 'X') && count ==4){
					(u->win_info)[0] = x;
					(u->win_info)[1] = y;
					(u->win_info)[2] = 3;
					x_is_winner = 1;
					continue;
				}else if(((u->board_ptr)[x][y] == 'o' || (u->board_ptr)[x][y] == 'O') && count ==4){
					(u->win_info)[3] = x;
					(u->win_info)[4] = y;
					(u->win_info)[5] = 3;
					o_is_winner = 1;
					continue;
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
	if(scanf("%d", &(player_move.column)) != 1) exit(1);
	printf("Player %c enter row to rotate: ",next_player(u)); // Do not edit this line
	if(scanf("%d", &(player_move.row)) != 1) exit(1);

	return player_move;
}

int is_valid_move(struct move m, board u){
	if (m.column < 1 || m.column > u->max_cols || m.row < -(u->max_rows) || m.row > u->max_rows) exit(1);
	if ((u->board_ptr)[0][(m.column)-1] == '.') return 1;
	exit(1);
}

char is_winning_move(struct move m, board u){

	char **board_copy = (char**)malloc((u->max_rows) * sizeof(char*));
	if(board_copy == NULL) exit(1);

	for(int i = 0; i < u->max_rows; i++){
		board_copy[i] = (char*)malloc((u->max_cols) * sizeof(char)+1);
		if(board_copy[i] == NULL) exit(1);
	}

	for(int x = 0; x < u->max_rows; x++){
		for(int y = 0; y < u->max_cols; y++){
			board_copy[x][y] = (u->board_ptr)[x][y];
		}
	}

	play_move(m, u);
	char simulated_winner = current_winner(u);

	// resets board sturcture to state before move was played
	for(int x = 0; x < u->max_rows; x++){
		for(int y = 0; y < u->max_cols; y++){
			(u->board_ptr)[x][y] = board_copy[x][y];
		}
	}

	for(int j = 0; j < 6; j++){
		(u->win_info)[j] = -1;
	}

	if(next_player(u) == 'x'){
		u->num_of_o --;
	}else if(next_player(u) == 'o'){
		u->num_of_x --;
	}

	for(int i = 0; i < u->max_rows; i++){
		free(board_copy[i]);
	}

	free(board_copy);

	return simulated_winner;
}

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
					while(((x+count < u->max_rows) && (u->board_ptr)[x+count][y] == '.')){
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