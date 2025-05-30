#ifndef __HW1_H
#define __HW1_H

#define INFO(...) do {fprintf(stderr, "[          ] [ INFO ] "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); fflush(stderr);} while(0)
#define ERROR(...) do {fprintf(stderr, "[          ] [ ERR  ] "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); fflush(stderr);} while(0) 


#define MAX_LENGTH 8
#define MAX_SEQUENCE_CAP  40320

//Required:
int initialize_board(const char *initial_state, const char *keys, int size);
int solve(const char *initial_state, const char *keys, int size);

int generateRowCombinations(int rowSize, int possibleValues[MAX_LENGTH][MAX_LENGTH], int results[MAX_LENGTH * MAX_LENGTH * MAX_LENGTH * MAX_LENGTH * MAX_LENGTH][MAX_LENGTH]);
void generateCombinations(int rowSize, int possibleValues[MAX_LENGTH][MAX_LENGTH], int currentRow[MAX_LENGTH], int index, int results[MAX_LENGTH * MAX_LENGTH][MAX_LENGTH], int *resultCount, bool usedHeights[MAX_LENGTH]);
void heuristic_1(int size);
void heuristic_2(int size);
void heuristic_3(int size);
void print3DArray(int size);
int check_col_filled(int size, int col);
int check_row_filled(int size, int row);
int check_2nd_key_req_row(int size, int row);
int check_2nd_key_req_col(int size, int col);
int check_board_row_col(int size, char value,int row,int col);
int check_board(int size);
void print_2D_array(int size);
void print_array_int(int[],int);
void printCharNTimes(char,int);
void heurestic_4(int size);

/* Hints from our solution (feel free to use or ignore):

Part 1

void print_board();
int get_move();
int check_dupes_col(int col);
int check_dupes_row(int row);
int check_row(int row);
int check_col(int col);
int try_move(char choice, int row, int col);

Part 2

void edge_clue_initialization(void);
void apply_edge_constraint_rule(void);
bool apply_constraint_propagation(int row, int column, int piece);
void apply_process_of_elimination(int row, int column, int piece);

Part 3

void generate_valid_sequences(int valid_sequences[MAX_SEQUENCE_CAP][MAX_LENGTH], bool is_horizontal, int index);
void generate_valid_sequences_helper(int valid_sequences[MAX_SEQUENCE_CAP][MAX_LENGTH], bool is_horizontal, int index, int sequence[MAX_LENGTH], int starts_at);
void generate_filtered_sequences(int filtered_sequences[MAX_SEQUENCE_CAP][MAX_LENGTH], bool is_horizontal, int index);
bool sequence_filtration(bool is_horizontal, int index);
bool apply_sequence_filtration(void);

Testing functions

void print_possible_pieces_state(void);
void print_possible_pieces_at_cell(int row, int column);
*/


#endif // HW1_H