# CSE 220: Skyscrapers Puzzle Game

This project is an implementation of the single-player puzzle game "Skyscrapers," completed as part of the CSE 220: Systems Fundamentals I course at Stony Brook University[cite: 1, 3]. The implementation is done in C and includes both an interactive version of the game and an automatic solver based on logical heuristics.

## Learning Outcomes

Completing this assignment demonstrates the ability to:
* Implement simple functions in C[cite: 2].
* Implement basic algorithms for processing 2D arrays in C[cite: 2].
* Understand the description of an algorithm and implement it in C, including the architecture of custom functions and data structures[cite: 2].

## Game Rules

Skyscrapers is a puzzle played on an N x N grid[cite: 7].
* Each cell in the grid must be filled with a number from 1 to N, representing a skyscraper of that height[cite: 7].
* No number can be repeated in the same row or column[cite: 47].
* The numbers around the edge of the board are "clues"[cite: 8]. A clue number indicates how many skyscrapers are visible from that vantage point[cite: 9]. Taller buildings block the view of shorter ones behind them[cite: 11].
* A clue value of 0 means no hint is provided for that row or column[cite: 10].

For example, with a clue of "1", the tallest skyscraper (value N) must be in the first position. With a clue of "N", the skyscrapers must be in ascending order (1, 2, ..., N)[cite: 70, 71].

## Features

This project is divided into two main parts: an interactive game and an automatic solver.

### Part 1: Interactive Skyscrapers

A playable, interactive version of the Skyscrapers game.

* **Game Initialization**: The game starts by taking command-line arguments to define the board's state[cite: 19].
    * `argv[1]`: The size of the grid (N)[cite: 20, 21].
    * `argv[2]`: A string representing the initial board state in row-major order. Empty cells are represented by '-'[cite: 22, 29].
    * `argv[3]`: A string representing the clues (keys) for the top, bottom, left, and right sides, concatenated in that order[cite: 22].
* **Gameplay**: The game prompts the user to choose a piece (skyscraper height), a row, and a column to place the piece[cite: 36].
* **Error Handling**: The program validates user input and game moves, providing specific error messages for:
    * Invalid piece, row, or column choices[cite: 39].
    * Placing a piece in an already occupied cell[cite: 44, 45].
    * Placing a duplicate piece in a row or column[cite: 47, 48].
    * Violating a clue's requirement when completing a row or column[cite: 51, 52].
* **Winning**: Once the board is correctly filled, a congratulatory message is displayed[cite: 55, 56].
* **Board Display**: The game board is printed to the console after each move, showing the current state and the surrounding clues[cite: 34].

### Part 2: Skyscrapers Solver

An automatic solver that uses a series of heuristics to solve the puzzle without backtracking or brute force[cite: 66, 68]. The solver operates on an initial board state and a set of clues provided as strings[cite: 64, 65].

#### Solver Heuristics

The solver implements four distinct heuristics to deduce the solution.

1.  **Heuristic #1: Edge Clue Initialization**
    * Places the tallest skyscraper (N) if a clue is '1'[cite: 70].
    * Fills an entire row/column with ascending values (1 to N) if a clue is 'N'[cite: 71].
    * Applies the **Edge Constraint Rule** to eliminate possible skyscraper heights from cells based on their distance from the edge and the clue value[cite: 72, 73]. The rule states that for a clue `c` and a distance `d` from the edge, values from `N - c + 2 + d` to `N` can be eliminated[cite: 73, 92].

2.  **Heuristic #2: Constraint Propagation**
    * When a skyscraper is placed in a cell, its value is removed as a possibility from all other cells in the same row and column[cite: 93, 94].
    * This project uses a "constraints list" data structure to track the possible valid values for each empty cell[cite: 77, 95].
    * If this process results in a cell having only one possible value, that value is placed on the board, and propagation continues[cite: 95].

3.  **Heuristic #3: Process of Elimination**
    * The solver scans each row and column's constraint lists[cite: 97]. If a specific value appears as a possibility in only one cell within that row or column, it must be the correct value for that cell[cite: 97, 98].

4.  **Heuristic #4: Clue Elimination (Sequence Filtration)**
    * For rows or columns that are nearly complete, this heuristic generates all possible permutations of the remaining empty cells[cite: 101, 110].
    * It filters these permutations by checking which ones satisfy the row/column's clue[cite: 104, 105].
    * If a value is present in the same cell across all valid sequences, that value is confirmed and placed on the board[cite: 106].
    * It can also eliminate possibilities if a value never appears in a certain cell across all valid sequences[cite: 109].
    * To manage complexity, this heuristic prioritizes rows and columns with the fewest empty cells[cite: 111].

## How to Build and Run

The project is configured to be built and run using CMake and VS Code launch targets[cite: 112].

1.  **Configure the build (only once)**:
    ```bash
    cmake -S . -B build
    ```
    [cite: 112]

2.  **Build the code**:
    ```bash
    cmake --build build
    ```
    [cite: 112]

3.  **Run the Interactive Game**:
    * Execute the `Run Game` launch target in VS Code[cite: 113].
    * Command-line arguments can be modified in the `.vscode/launch.json` file[cite: 114]. The `args` array holds the board size, initial state string, and keys string[cite: 115].
    * Example `launch.json` configuration:
      ```json
      "args": ["4", "3-2-431-1-4--1-4", "2124242121333321"]
      ```

4.  **Run the Solver**:
    * Execute the `Run Solver` launch target in VS Code[cite: 116].
    * Arguments for the solver can also be set in `.vscode/launch.json`[cite: 117].

5.  **Run Tests**:
    * Execute the `Run Solver Tests` launch target to run a set of unit tests against the implementation[cite: 118].
