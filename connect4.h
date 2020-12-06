typedef struct board_structure *board;

struct move{
int column;
int row;
};

board setup_board();
void cleanup_board(board u);

void read_in_file(FILE *infile, board u);
void write_out_file(FILE *outfile, board u);

struct move read_in_move();
int is_valid_move(struct move m, board u);
char is_winning_move(struct move m, board u);
void play_move(struct move m, board u);

char current_winner(board u); 
char next_player(board u); 



