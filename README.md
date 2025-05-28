# CSE 220: Skyscrapers Puzzle Game

This project is an implementation of the single-player puzzle game "Skyscrapers," completed as part of the CSE 220: Systems Fundamentals I course at Stony Brook University. The implementation is done in C and includes both an interactive version of the game and an automatic solver based on logical heuristics.

## Learning Outcomes

Completing this assignment demonstrates the ability to:
* Implement simple functions in C.
* Implement basic algorithms for processing 2D arrays in C.
* Understand the description of an algorithm and implement it in C, including the architecture of custom functions and data structures.

## Game Rules

Skyscrapers is a puzzle played on an N x N grid.
* Each cell in the grid must be filled with a number from 1 to N, representing a skyscraper of that height.
* No number can be repeated in the same row or column.
* The numbers around the edge of the board are "clues". A clue number indicates how many skyscrapers are visible from that vantage point. Taller buildings block the view of shorter ones behind them.
* A clue value of 0 means no hint is provided for that row or column.

For example, with a clue of "1", the tallest skyscraper (value N) must be in the first position. With a clue of "N", the skyscrapers must be in ascending order (1, 2, ..., N).

## Features

This project is divided into two main parts: an interactive game and an automatic solver.

### Part 1: Interactive Skyscrapers

A playable, interactive version of the Skyscrapers game.

* **Game Initialization**: The game starts by taking command-line arguments to define the board's state.
    * `argv[1]`: The size of the grid (N).
    * `argv[2]`: A string representing the initial board state in row-major order. Empty cells are represented by '-'.
    * `argv[3]`: A string representing the clues (keys) for the top, bottom, left, and right sides, concatenated in that order.
* **Gameplay**: The game prompts the user to choose a piece (skyscraper height), a row, and a column to place the piece.
* **Error Handling**: The program validates user input and game moves, providing specific error messages for:
    * Invalid piece, row, or column choices.
    * Placing a piece in an already occupied cell.
    * Placing a duplicate piece in a row or column.
    * Violating a clue's requirement when completing a row or column.
* **Winning**: Once the board is correctly filled, a congratulatory message is displayed.
* **Board Display**: The game board is printed to the console after each move, showing the current state and the surrounding clues.

### Part 2: Skyscrapers Solver

An automatic solver that uses a series of heuristics to solve the puzzle without backtracking or brute force. The solver operates on an initial board state and a set of clues provided as strings.

#### Solver Heuristics

The solver implements four distinct heuristics to deduce the solution.

1.  **Heuristic #1: Edge Clue Initialization**
    * Places the tallest skyscraper (N) if a clue is '1'.
    * Fills an entire row/column with ascending values (1 to N) if a clue is 'N'.
    * Applies the **Edge Constraint Rule** to eliminate possible skyscraper heights from cells based on their distance from the edge and the clue value. The rule states that for a clue `c` and a distance `d` from the edge, values from `N - c + 2 + d` to `N` can be eliminated.

2.  **Heuristic #2: Constraint Propagation**
    * When a skyscraper is placed in a cell, its value is removed as a possibility from all other cells in the same row and column.
    * This project uses a "constraints list" data structure to track the possible valid values for each empty cell.
    * If this process results in a cell having only one possible value, that value is placed on the board, and propagation continues.

3.  **Heuristic #3: Process of Elimination**
    * The solver scans each row and column's constraint lists. If a specific value appears as a possibility in only one cell within that row or column, it must be the correct value for that cell.

4.  **Heuristic #4: Clue Elimination (Sequence Filtration)**
    * For rows or columns that are nearly complete, this heuristic generates all possible permutations of the remaining empty cells.
    * It filters these permutations by checking which ones satisfy the row/column's clue.
    * If a value is present in the same cell across all valid sequences, that value is confirmed and placed on the board.
    * It can also eliminate possibilities if a value never appears in a certain cell across all valid sequences.
    * To manage complexity, this heuristic prioritizes rows and columns with the fewest empty cells.

## How to Build and Run

The project is configured to be built and run using CMake and VS Code launch targets.

1.  **Configure the build (only once)**:
    ```bash
    cmake -S . -B build
    ```

2.  **Build the code**:
    ```bash
    cmake --build build
    ```

3.  **Run the Interactive Game**:
    * Execute the `Run Game` launch target in VS Code.
    * Command-line arguments can be modified in the `.vscode/launch.json` file. The `args` array holds the board size, initial state string, and keys string.
    * Example `launch.json` configuration:
        ```json
        "args": ["4", "3-2-431-1-4--1-4", "2124242121333321"]
        ```

4.  **Run the Solver**:
    * Execute the `Run Solver` launch target in VS Code.
    * Arguments for the solver can also be set in `.vscode/launch.json`.

5.  **Run Tests**:
    * Execute the `Run Solver Tests` launch target to run a set of unit tests against the implementation.

---

## CSE220 Completion Score: 88%
