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

// A very long List of Helper Functions
int array_values[MAX_LENGTH][MAX_LENGTH][MAX_LENGTH] = {0}; 

int initialize_board(const char *initial_state, const char *keys, int size) {
	
    //Initialized Board, (cmake -S . -B build; cmake --build build; ./build/hw1...
    // Initialize Entire Board with '-'
    for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
            board[i][j] = '-';
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

    for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
            char choice = (initial_state[i*(size)+j]);
            int sus_input = 0;
            // Checking for Rule 1
            if (choice != '-' && check_board_row_col(size,choice,i,j)==0) sus_input = 1;
            board[i][j] = choice;

            // Checking for Rule 2
            if (check_row_filled(size,i) == 1 && check_2nd_key_req_row(size,i)==0) sus_input = 1;
            if (check_col_filled(size,j) == 1 && check_2nd_key_req_col(size,j)==0) sus_input = 1;

            if (sus_input == 1){
                printf("Invalid initial board state.\n");
                return 0;
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
            printf("Choose a piece (1-%d) or q to quit: ",size);
            scanf(" %c", &choice);
            getchar();
            
            if (choice=='q'){
                doQuit = 0;
                break;
            }

            if (!('1' <= choice && choice <= '0'+size)){
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
            printf("Choose a row (0-%d): ",size-1);
            scanf(" %d", &row);
            getchar();

            if (!(0 <= row && row <= size-1)){
                printf("Invalid choice. ");
                continue;
            } else {
                correct_value_2 = 0;
            }
        }

        while (correct_value_3){
            printf("Choose a column (0-%d): ",size-1);
            scanf(" %d", &col);
            getchar();

            if (!(0 <= col && col <= size-1)){
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
        
        if (check_row_filled(size,row) == 1 && check_2nd_key_req_row(size,row)==0){
            printf("Invalid choice. You violate one of the key requirements.\n");
            board[row][col] = '-';
            continue;
        }

        if (check_col_filled(size,col) == 1 && check_2nd_key_req_col(size,col)==0){
            printf("Invalid choice. You violate one of the key requirements.\n");
            board[row][col] = '-';
            continue;
        }
        
        if (check_board(size)==1){
            printf("Congratulations, you have filled the board!\n");
            print_2D_array(size);
            break;
        }

    }

	return 1;
}

int check_col_filled(int size, int col){
    for (int i = 0; i < size; i++){
        if (board[i][col] == '-'){
            return 0;
        }
    }
    return 1;
}

int check_row_filled(int size, int row){
    for (int i = 0; i < size; i++){
        if (board[row][i] == '-'){
            return 0;
        }
    }
    return 1;
}

int check_2nd_key_req_row(int size, int row){
    int visibility_goal_right = right_key[row];
    int visibility_goal_left = left_key[row];
    int visibilty = 1;
    char tallest_building;

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

int check_2nd_key_req_col(int size, int col){
    int visibility_goal_top = top_key[col];
    int visibility_goal_bottom = bottom_key[col];
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

// Part 2 Starts From Here

#include <stdio.h>
#include <string.h>

int solve(const char *initial_state, const char *keys, int size){
    // Initialize Entire Board with '-'
    for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
            board[i][j] = '-';
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

    for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
            char choice = (initial_state[i*(size)+j]);
            int sus_input = 0;
            // Checking for Rule 1
            if (choice != '-' && check_board_row_col(size,choice,i,j)==0) sus_input = 1;
            board[i][j] = choice;

            // Checking for Rule 2
            if (check_row_filled(size,i) == 1 && check_2nd_key_req_row(size,i)==0) sus_input = 1;
            if (check_col_filled(size,j) == 1 && check_2nd_key_req_col(size,j)==0) sus_input = 1;

            if (sus_input == 1){
                printf("Invalid initial board state.\n");
                return 0;
            }
		}
	}
	
    // Heuristic 1
    // Check each column to see if key = 1, then place 4 right next to it. && Check each column to see if key = size, then simply place values 0 to size sequentially
    for (int i = 0; i < size; i++){
        int key_value_top = top_key[i];
        int key_value_bottom = bottom_key[i];

        if (key_value_top == 0 && key_value_bottom == 0) {
            continue;
        }

        char value_top = board[0][i];
        char value_bottom = board[size-1][i];

        if (key_value_top != 0){
            if (value_top != '-' && key_value_top == 1){
                board[0][i] = (char) (size + '0');
            }
    
            if (key_value_top == size){
                for (int j = 0; j < size; j++){
                    board[j][i] = (char) ((j + 1) + '0');
                }
            }
        }

        if (key_value_bottom != 0){
            if (value_bottom != '-' && key_value_bottom == 1){
                board[size-1][i] = (char) (size + '0');
            }

            if (key_value_bottom == size){
                for (int j = (size-1); j >= 0; j--){
                    board[j][i] = (char) ((size-j) + '0');
                }
            }
        }
    }
    
    // initialize all the '-' with an array to keep track of valid values.
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] != '-'){
                array_values[i][j][(board[i][j] - '0') - 1] = 1;
                continue;
            }
            for (int k = 0; k < size; k++) array_values[i][j][k] = 1;
        }
    }

    // Heurestic 1
    //./build/hw1_solver 4 "3-2-431-1-4--1-4" "2124242121333321"
    //./build/hw1_solver 4 "----------------" "2124242121333321"
    heuristic_1(size);

    // Heurestic 2
    heuristic_2(size);

    // Heurestic 3 + 2
    heuristic_3(size);
    heuristic_2(size);

    // Heurestic 4 Repeated Several several times to ensure all possible values are covered
    for (int pt = 0; pt < 20; pt++){
        // This is for column
        for (int i = 0; i < size; i++) {
            
            int arr_of_possible_values[MAX_LENGTH][MAX_LENGTH];
            
            for (int j = 0; j < size; j++) {
                for (int k = 0; k < size; k++) {
                    arr_of_possible_values[j][k] = array_values[j][i][k];
                }
            }

            int results[MAX_LENGTH * MAX_LENGTH*MAX_LENGTH*MAX_LENGTH * MAX_LENGTH][MAX_LENGTH];
            int resultCount = generateRowCombinations(size, arr_of_possible_values, results);

            for (int t = 0; t < resultCount; t++){
                int visibility_goal_top = top_key[i];
                int visibility_goal_bottom = bottom_key[i];
                
                int visibilty = 1;
                int tallest_building;


                if (visibility_goal_top != 0){
                    tallest_building = results[t][0];
                    for (int m = 0; m < size; m++){
                        if (results[t][m]>tallest_building){
                            tallest_building = results[t][m];
                            visibilty++;
                        }
                    }
                    if (visibility_goal_top != visibilty){
                        results[t][0] = 0;
                    }
                    visibilty = 1;
                }

                if (visibility_goal_bottom != 0){
                    tallest_building = results[t][size-1];
                    for (int m = size-2; m >= 0; m--){
                        if (results[t][m]>tallest_building){
                            tallest_building = results[t][m];
                            visibilty++;
                        }
                    }
                    if (visibility_goal_bottom != visibilty) {
                        results[t][0] = 0;
                    };
                    visibilty = 1;
                }
            }

            for (int j = 0; j < size; j++) {
                for (int p = 0; p < size; p++){
                    array_values[j][i][p] = 0;
                }
            }

            for (int m = 0; m < resultCount; m++){
                if (results[m][0] == 0) continue;
                for (int j = 0; j < size; j++) {
                    int result_val = results[m][j];
                    array_values[j][i][result_val-1] = 1;
                }
            }
        }

        // For Rows
        for (int i = 0; i < size; i++) {
            int arr_of_possible_values[MAX_LENGTH][MAX_LENGTH];
            for (int j = 0; j < size; j++) {
                for (int k = 0; k < size; k++) {
                    arr_of_possible_values[j][k] = array_values[i][j][k];
                }
            }
            int results[MAX_LENGTH * MAX_LENGTH*MAX_LENGTH*MAX_LENGTH * MAX_LENGTH][MAX_LENGTH];
            int resultCount = generateRowCombinations(size, arr_of_possible_values, results);
        
            for (int t = 0; t < resultCount; t++) {
                int visibility_goal_left = left_key[i];
                int visibility_goal_right = right_key[i];
                int visibility = 1;
                int tallest_building;
        
                if (visibility_goal_left != 0) {
                    tallest_building = results[t][0];
                    for (int m = 1; m < size; m++) {
                        if (results[t][m] > tallest_building) {
                            tallest_building = results[t][m];
                            visibility++;
                        }
                    }
                    if (visibility_goal_left != visibility) {
                        results[t][0] = 0;
                    }
                    visibility = 1;
                }
        
                if (visibility_goal_right != 0) {
                    tallest_building = results[t][size - 1];
                    for (int m = size - 2; m >= 0; m--) {
                        if (results[t][m] > tallest_building) {
                            tallest_building = results[t][m];
                            visibility++;
                        }
                    }
                    if (visibility_goal_right != visibility) {
                        results[t][0] = 0;
                    }
                    visibility = 1;
                }
            }

            for (int j = 0; j < size; j++) {
                for (int p = 0; p < size; p++){
                    array_values[i][j][p] = 0;
                }
            }

            for (int m = 0; m < resultCount; m++){
                if (results[m][0] == 0) continue;
                for (int j = 0; j < size; j++) {
                    int result_val = results[m][j];
                    array_values[i][j][result_val-1] = 1;
                }
            }
        }
        heuristic_3(size);
        heuristic_2(size);
        heuristic_3(size);
    }

    // Final Heurestic, pick lowest value and loop Hueristic 2 and 3 until solved.
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == '-'){
                for (int k = 0; k < size; k++){
                    if (array_values[i][j][k] == 1) {
                        board[i][j] = (k+1) + '0';
                        array_values[i][j][k] = 0;
                        break;
                    }
                }
                heuristic_3(size);
                heuristic_2(size);
                heuristic_3(size);
            }
        }
    }
    
    print3DArray(size);
    print_2D_array(size);
	return 1;
}

void print3DArray(int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("{");
            for (int k = 0; k < size; k++) {
                if (array_values[i][j][k] == 1) printf("%d", k+1);
                if (k < size - 1 && array_values[i][j][k] == 1) printf(",");
            }
            printf("} ");
        }
        printf("\n");
    }
}

void heuristic_1(int size){
    for (int i = 0; i < size; i++) {
        int key_value_top = top_key[i];
        int key_value_bottom = bottom_key[i];
        for (int j = 0; j < size; j++) {
            int part_of_heuristic_form_val_top = size - key_value_top + 2;
            int part_of_heuristic_form_val_bottom = size - key_value_bottom + 2;

            int heuristic_val_top = j + part_of_heuristic_form_val_top;
            int heuristic_val_bottom = ((size - 1) - j) + part_of_heuristic_form_val_bottom;
    
            if (heuristic_val_top > 0 && heuristic_val_top <= size && key_value_top != 0) {
                for (int k = heuristic_val_top; k <= size; k++) {
                    array_values[j][i][k - 1] = 0;
                }
            }
    
            if (heuristic_val_bottom > 0 && heuristic_val_bottom <= size && key_value_bottom != 0) {
                for (int k = heuristic_val_bottom; k <= size; k++) {
                    array_values[j][i][k - 1] = 0;
                }
            }
        }
    }
}

void heuristic_2(int size){
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            char val = board[i][j];
            if (val != '-'){
                int val_to_remove = val - '0';
                for (int k = 0; k < size; k++){
                    if (j != k) array_values[i][k][val_to_remove-1] = 0;
                    if (i != k) array_values[k][j][val_to_remove-1] = 0;
                }
            }
        }
    }
}

void heuristic_3(int size){
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == '-'){
                int found = 0;
                int val_found = 0;
                for (int k = 0; k < size; k++){
                    if (array_values[i][j][k] == 1){
                        found++;
                        val_found = k+1;
                    }
                }
                if (found != 1) continue;
                board[i][j] = '0' + val_found;
            }
        }
    }
}

int generateRowCombinations(int rowSize, int possibleValues[MAX_LENGTH][MAX_LENGTH], int results[MAX_LENGTH * MAX_LENGTH*MAX_LENGTH*MAX_LENGTH * MAX_LENGTH][MAX_LENGTH]) {
    int resultCount = 0;
    int stack[MAX_LENGTH];
    bool usedHeights[MAX_LENGTH] = {false};
    int currentRow[MAX_LENGTH];

    memset(stack, 0, sizeof(stack));
    int index = 0;

    while (index >= 0) {
        bool foundNextValue = false;
        for (; stack[index] < MAX_LENGTH; stack[index]++) {
            int k = stack[index];
            if (possibleValues[index][k] == 1 && !usedHeights[k]) {
                currentRow[index] = k + 1;
                usedHeights[k] = true;

                stack[index]++;
                index++;
                if (index < rowSize) {
                    stack[index] = 0;
                }
                foundNextValue = true;
                break;
            }
        }

        if (!foundNextValue) {
            if (index > 0) {
                index--;
                int prevValue = currentRow[index] - 1;
                usedHeights[prevValue] = false;
            } else {
                break;
            }
        } else if (index == rowSize) {
            for (int i = 0; i < rowSize; i++) {
                results[resultCount][i] = currentRow[i];
            }
            resultCount++;
            index--;
            int prevValue = currentRow[index] - 1;
            usedHeights[prevValue] = false;
        }
    }

    return resultCount;
}



