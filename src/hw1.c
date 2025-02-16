#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "hw1.h"

int top_key[MAX_LENGTH] = {0};
int bottom_key[MAX_LENGTH] = {0};
int left_key[MAX_LENGTH] = {0};
int right_key[MAX_LENGTH] = {0};

char board[MAX_LENGTH][MAX_LENGTH] = {0};

int length = 5;

// List of Helper Functions
int check_2nd_key_req(int size, int col, int row);
int check_board_row_col(int size, char value,int row,int col);
int check_board(int size);
void print_2D_array(int size);
void print_array_int(int[],int);
void printCharNTimes(char,int);


int initialize_board(const char *initial_state, const char *keys, int size) {
	
    //Initialized Board, (cmake -S . -B build; cmake --build build; ./build/hw1...)
    //./build/hw1_game 4 "3-2-431-1-4--1-4" "2124242121333321"
    //./build/hw1_game 4 "3-21-3---2---1--" "2124242121333321"
	
    for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			board[i][j] = (initial_state[i*(size)+j]);
		}
	}

	// Initialized Keys
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < size; j++){
			int to_put = keys[i*(size)+j]-'0';
			if (i==0){
				top_key[j] = to_put;
			} else if (i==1){
				bottom_key[j] = to_put;
			} else if (i==2){
				left_key[j] = to_put;
			} else {
				right_key[j] = to_put;
			}
		}
	}
	
	while (1){
        char choice;
        int row;
        int col;
        int doQuit = 1;
        int correct_value_1 = 1; 
        int correct_value_2 = 1;
        int correct_value_3 = 1;

        print_2D_array(size);
        
        while (doQuit && correct_value_1){
            printf("Choose a piece (1-4) or q to quit: ");
            scanf(" %c", &choice);
            getchar();
            
            if (choice=='q'){
                doQuit = 0;
                break;
            }

            if (!('1' <= choice && choice <= '5')){
                printf("Invalid choice. ");
                continue;
            } else {
                correct_value_1 = 0;
            }
        }

        if (doQuit == 0){
            return 0;
        }

        while (correct_value_2){
            printf("Choose a row (0-3): ");
            scanf(" %d", &row);
            getchar();

            if (!(0 <= row && row <= 4)){
                printf("Invalid choice. ");
                continue;
            } else {
                correct_value_2 = 0;
            }
        }

        while (correct_value_3){
            printf("Choose a column (0-3): ");
            scanf(" %d", &col);
            getchar();

            if (!(0 <= col && col <= 4)){
                printf("Invalid choice. ");
                continue;
            } else {
                correct_value_3 = 0;
            }
        }

        char board_piece = board[row][col];
        
        if (board_piece != '-'){
            printf("Invalid choice. That space is already occupied.\n");
            continue;
        }

		if (check_board_row_col(size,choice,row,col)==0){
			printf("Invalid choice. There is already a building with that height in that row or column.\n");
			continue;
		}

        board[row][col] = choice;
        
        if (check_board(size)==1){
            if (check_2nd_key_req(size,col,row)==0){
                printf("Invalid choice. You violate one of the key requirements.\n");
                board[row][col] = '-';
                continue;
            }
            printf("Congratulations, you have filled the board!\n");
            print_2D_array(size);
            break;
        }

    }

	return 1;
}

int check_2nd_key_req(int size, int col, int row){
    int visibility_goal_top = top_key[col];
    int visibility_goal_bottom = bottom_key[col];
    int visibility_goal_right = right_key[row];
    int visibility_goal_left = left_key[row];
    int visibilty = 1;
    char tallest_building;

    // Check Top
    if (visibility_goal_top != 0){
        tallest_building = board[0][col];
        for (int i = 0; i < size; i++){
            if (board[i][col]>tallest_building){
                tallest_building = board[i][col];
                visibilty++;
            }
        }
        if (visibility_goal_top != visibilty) return 0;
        visibilty = 1;
    }

    // Check Bottom
    if (visibility_goal_bottom != 0){
        tallest_building = board[size-1][col];
        for (int i = size-2; i >= 0; i--){
            if (board[i][col]>tallest_building){
                tallest_building = board[i][col];
                visibilty++;
            }
        }
        if (visibility_goal_bottom != visibilty) return 0;
        visibilty = 1;
    }
    
    // Check Left
    if (visibility_goal_left != 0){
        tallest_building = board[row][0];
        for (int i = 0; i < size; i++){
            if (board[row][i]>tallest_building){
                tallest_building = board[row][i];
                visibilty++;
            }
        }
        if (visibility_goal_left != visibilty) return 0;
        visibilty = 1;
    }
    
    // Check Right
    if (visibility_goal_right != 0){
        tallest_building = board[row][size-1];
        for (int i = size-2; i >= 0; i--){
            if (board[row][i]>tallest_building){
                tallest_building = board[row][i];
                visibilty++;
            }
        }
        if (visibility_goal_right != visibilty) return 0;
        visibilty = 1;
    }

    return 1;
}

int check_board_row_col(int size, char value,int row,int col){
    int is_row_col_fine = 1;

	for (int i = 0; i < size; i++){
		if (board[row][i] == value){
			is_row_col_fine = 0;
			break;
		} 
    }

	for (int i = 0; i < size; i++){
		if (board[i][col] == value){
			is_row_col_fine = 0;
			break;
		} 
    }

    return is_row_col_fine;
}

int check_board(int size){
    int isFull = 1;
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if (board[i][j] == '-'){
                isFull = 0;
            }   
        }
    }

    if (isFull==0){
        return 0;
    }

    return 1;
}

void print_array_int(int x[], int size){
    for (int i = 0; i < size; i++){
        printf("%d ",x[i]);
    }
    printf("\n");
}

void print_2D_array(int size){
    printf("    ");
    print_array_int(top_key,size);
    printf("    ");
    printCharNTimes('v',size);
    for (int i = 0; i < size; i++){
        printf("%d > ",left_key[i]);
        for (int j = 0; j < size; j++){
            printf("%c ",board[i][j]);   
        }
        printf("< %d",right_key[i]);
        printf("\n");
    }
    printf("    ");
    printCharNTimes('^',size);
    printf("    ");
    print_array_int(bottom_key,size);
}

void printCharNTimes(char c, int n) {
    for (int i = 0; i < n; i++) {
        printf("%c", c);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

int solve(const char *initial_state, const char *keys, int size){
	(void) initial_state;
	(void) keys;
	(void) size;
	
	return 1;
	
}