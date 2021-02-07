#include<stdio.h>
#include<stdlib.h>
#include"connect4.h"

struct board_structure{
	char **board_ptr;
	int max_rows;
	int max_cols;
	int num_of_x;
	int num_of_o;
	int *win_info; // {x.x, x.y, x.dir, o.x, o.y, o.dir}
};

board setup_board(){
	board board_to_play = malloc(sizeof(struct board_structure));
	if (board_to_play == NULL) {
		fprintf(stderr, "Error: Unable to allocate memory for board struct\n");
		exit(1);
	}

	board_to_play->max_rows = 1;
	board_to_play->max_cols = 4;

	board_to_play->win_info = (int*)malloc(6*sizeof(int)); 
	if(board_to_play->win_info == NULL){
		fprintf(stderr, "Error: Unable to allocate memory for winning information\n");
		exit(1);
	}

	board_to_play->win_info[0] = -1;
	board_to_play->win_info[1] = -1;
	board_to_play->win_info[2] = -1;
	board_to_play->win_info[3] = -1;
	board_to_play->win_info[4] = -1;
	board_to_play->win_info[5] = -1;

	board_to_play->board_ptr = (char**)malloc((board_to_play->max_rows) * sizeof(char*)); // min 1 row 
	if(board_to_play->board_ptr == NULL){
		fprintf(stderr, "Error: Unable to allocate memory for board pointer\n");
		exit(1);
	}

	(board_to_play->board_ptr)[0] = (char*)malloc((board_to_play->max_cols) * sizeof(char)+1); // min 4 cols
	if((board_to_play->board_ptr)[0] == NULL){
		fprintf(stderr, "Error: Unable to allocate memory for pointer to char\n");
		free(board_to_play->board_ptr);
		exit(1);
	}

	board_to_play->board_ptr[0][0] = ' ';
	board_to_play->board_ptr[0][1] = ' ';
	board_to_play->board_ptr[0][2] = ' ';
	board_to_play->board_ptr[0][3] = ' ';

	board_to_play->num_of_x = 0;
	board_to_play->num_of_o = 0;
	
	return board_to_play;
}

void cleanup_board(board u){
	free(u->win_info);
	for(int i = 0; i <= u->max_rows; i++) free(u->board_ptr[i]);
	free(u->board_ptr);
	free(u);
}

void read_in_file(FILE *infile, board u){
	char *symbol = malloc(sizeof(char));
	int curr_row = 0;
	int curr_col = 0;
	
	while(!feof(infile)){
		if(curr_row == u->max_rows){
			u->board_ptr = (char**)realloc(u->board_ptr, ((u->max_rows)+1)*sizeof(char*));
			if(u->board_ptr == NULL){
				fprintf(stderr, "Error: Unable to reallocate memory for board pointer\n");
				cleanup_board(u);
				free(symbol);
				exit(1);
			}
			u->max_rows++;
			(u->board_ptr)[curr_row] = (char*)malloc((u->max_cols)*sizeof(char)+1);
			if(u->board_ptr[curr_row] == NULL){
				fprintf(stderr, "Error: Unable to allocate memory for pointer to char\n");
				cleanup_board(u);
				free(symbol);
				exit(1);
			}
		}
		fscanf(infile, "%c", &symbol[0]);
		if(symbol[0] == '.' || symbol[0] == 'x' || symbol[0] == 'o'){
			if(curr_col == u->max_cols){
				(u->board_ptr)[curr_row] = (char*)realloc((u->board_ptr)[curr_row], ((u->max_cols))*sizeof(char)+1);
				if((u->board_ptr)[curr_row] == NULL){
					fprintf(stderr, "Error: Unable to reallocate memory for pointer to char\n");
					cleanup_board(u);
					free(symbol);
					exit(1);
				}
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
	}

	(u->max_rows)--;
	free(symbol);
	// if((u->board_ptr)[0][0] != '.' && (u->board_ptr)[0][0] != 'x' && (u->board_ptr)[0][0] != 'o'){
	// 	cleanup_board(u);
	// 	fprintf(stderr, "Error: File empty or does not contain appropriate board format\n");
	// 	exit(1);
	// }
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
	int pos_x, pos_y, count;
	if(u->num_of_x == 0 && u->num_of_o == 0) return '.';
	for(int x = u->max_rows - 1; x >= 0; x--){
		if(u->win_info[2] != -1 && u->win_info[5] != -1) break;
		for(int y = 0; y < u->max_cols; y++){
			if((u->board_ptr)[x][y] != '.'){

				if(((u->win_info)[2] != -1 && (u->board_ptr)[x][y] == 'x') || ((u->win_info)[5] != -1 && (u->board_ptr)[x][y] == 'o')) continue;

				// down
				pos_x = x;
				count = 0;
				for(int i = 0; i < 4; i++){
					if(u->max_rows < 4) break;
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
					continue;
				}else if(((u->board_ptr)[x][y] == 'o' || (u->board_ptr)[x][y] == 'O') && count ==4){
					(u->win_info)[3] = x;
					(u->win_info)[4] = y;
					(u->win_info)[5] = 1;
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
					continue;
				}else if(((u->board_ptr)[x][y] == 'o' || (u->board_ptr)[x][y] == 'O') && count ==4){
					(u->win_info)[3] = x;
					(u->win_info)[4] = y;
					(u->win_info)[5] = 2;
					continue;
				}
			
				// diagonal down right
				pos_x = x;
				pos_y = y;
				count = 0;
				for(int i = 0; i < 4; i++){
					if(u->max_rows < 4) break;
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
					continue;
				}else if(((u->board_ptr)[x][y] == 'o' || (u->board_ptr)[x][y] == 'O') && count ==4){
					(u->win_info)[3] = x;
					(u->win_info)[4] = y;
					(u->win_info)[5] = 4;
					continue;
				}

				// diagonal up right
				pos_x = x;
				pos_y = y;
				count = 0;
				for(int i = 0; i < 4; i++){
					if(u->max_rows < 4) break;
					if(pos_y >= u->max_cols) pos_y = 0;
					if(pos_x >= u->max_rows || pos_x < 0) break;
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
					continue;
				}else if(((u->board_ptr)[x][y] == 'o' || (u->board_ptr)[x][y] == 'O') && count ==4){
					(u->win_info)[3] = x;
					(u->win_info)[4] = y;
					(u->win_info)[5] = 3;
					continue;
				}

			}
		}
	}

	if((u->win_info[2] != -1 && u->win_info[5] != -1) || (u->win_info[2] == -1 && u->win_info[5] == -1 && ((u->num_of_x + u->num_of_o) == (u->max_rows * u->max_cols)))){
		return 'd';
	}else if(u->win_info[2] != -1){
		return 'x';
	}else if(u->win_info[5] != -1){
		return 'o';
	}
	return '.';
}

struct move read_in_move(board u){
	struct move player_move;

	printf("Player %c enter column to place your token: ",next_player(u)); //Do not edit this line
	if(scanf("%d", &(player_move.column)) != 1){
		cleanup_board(u);
		fprintf(stderr, "Error: Invalid user input type - needs to be of type Int\n");
		exit(1);
	}
	printf("Player %c enter row to rotate: ",next_player(u)); // Do not edit this line
	if(scanf("%d", &(player_move.row)) != 1){
		cleanup_board(u);
		fprintf(stderr, "Error: Invalid user input type - needs to be of type Int\n");
		exit(1);
	}

	return player_move;
}

int is_valid_move(struct move m, board u){
	if (m.column < 1 || m.column > u->max_cols || m.row < -(u->max_rows) || m.row > u->max_rows) return 0;
	if ((u->board_ptr)[0][(m.column)-1] == '.') return 1;
	return 0;
}

char is_winning_move(struct move m, board u){

	char **board_copy = (char**)malloc((u->max_rows) * sizeof(char*));
	if(board_copy == NULL){
		fprintf(stderr, "Error: Unable to allocate memory for board copy pointer\n");
		cleanup_board(u);
		exit(1);
	}

	for(int i = 0; i < u->max_rows; i++){
		board_copy[i] = (char*)malloc((u->max_cols) * sizeof(char)+1);
		if(board_copy[i] == NULL){
			cleanup_board(u);
			free(board_copy);
			fprintf(stderr, "Error: Unable to allocate memory for pointer to char\n");
			exit(1);
		}
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
			prev_token = (u->board_ptr)[u->max_rows - abs(m.row)][0];
			for(int y = 1; y < u->max_cols; y++){
				current_token = (u->board_ptr)[u->max_rows - abs(m.row)][y];
				(u->board_ptr)[u->max_rows - abs(m.row)][y] = prev_token;
				prev_token = current_token;
				if(y == (u->max_cols) - 1){
					(u->board_ptr)[u->max_rows - abs(m.row)][0] = prev_token;
				}
			}
		}else if(m.row < 0){ // left rotation
			prev_token = (u->board_ptr)[u->max_rows - abs(m.row)][(u->max_cols) - 1];
			for(int y = (u->max_cols) - 2; y >= 0; y--){
				current_token = (u->board_ptr)[u->max_rows - abs(m.row)][y];
				(u->board_ptr)[u->max_rows - abs(m.row)][y] = prev_token;
				prev_token = current_token;
				if(y == 0){
					(u->board_ptr)[u->max_rows - abs(m.row)][(u->max_cols) - 1] = prev_token;
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