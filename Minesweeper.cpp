//
//  rec03.cpp
//  rec03 - Minesweeper Implementation
//
//  Created by Brittany Ng on 9/20/18.
//  Copyright © 2018 Brittany Ng. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;


struct Tile {
    int row;
    int column;
    int counter = 0;
    bool isVisible = false;
};

class Minesweeper{
private:
    const int gamebrdRow;
    const int gamebrdCol;
    const int BOMB_PROB = 10;
    vector<vector<Tile>> gameboard;
    
    
public:
    
    Minesweeper(int dimension = 10) : gamebrdRow(dimension), gamebrdCol(dimension) {
        srand(time(NULL));
        createBoard(dimension);
        addMines();
        checkNeighbours();
    }
    
    void createBoard(int size) {
        for (int row = 0; row < size; ++row) {
            vector<Tile> tileRow;
            for (int column = 0; column < size; ++column) {
                Tile newTile;
                newTile.row = row;
                newTile.column = column;
                newTile.counter = 0;
                tileRow.push_back(newTile);
            }
            gameboard.push_back(tileRow);
        }
    }
    
    void display(bool display) {
        if (display) {
            for (int row = 0; row < gamebrdRow; ++row) {
                for (int col = 0; col < gamebrdCol; ++col) {
                    if (checkIfMine(row, col)) {
                        // * represents mine
                        cout << "* ";
                    } else {
                        cout << gameboard[row][col].counter << ' ';
                    }
                }
                cout << endl;
            }
        } else {
            for (int row = 0; row < gamebrdRow; ++row) {
                for (int col = 0; col < gamebrdCol; ++col) {
                    if (gameboard[row][col].isVisible) {
                        cout << gameboard[row][col].counter << ' ';
                    } else {
                        // # represents hidden tile
                        cout << "# ";
                    }
                }
                cout << endl;
            }
        }
    }
    
    
    void addMines() {
        for (int row = 0; row < gamebrdRow; ++row) {
            for (int col = 0; col < gamebrdCol; ++col) {
                if (rand() % 100 < BOMB_PROB) {
                    if (gameboard[row][col].counter == 0) {
                        gameboard[row][col].counter = -1;
                    }
                }
            }
        }
    }
    
    bool checkIfMine(int row, int col) const {
        return gameboard[row][col].counter == -1;
    }
    
    bool validRow(int row) const {
        return (row >= 0 && row < gamebrdRow);
    }
    
    bool validCol(int col) const {
        return (col >= 0 && col < gamebrdCol);
    }
    
    bool isVisible(int row, int col) const {
        return gameboard[row][col].isVisible;
    }
    
    
    
    void checkNeighbours() {
        for (int row = 0; row < gamebrdRow; ++ row) {
            for (int column = 0; column < gamebrdCol; ++ column) {
                // checks if the tile is a bomb, if not it will check all of the neighbours and count the number of mines
                if (gameboard[row][column].counter != -1) {
                    if (validRow(row + 1) && validCol(column + 1)) {
                        if (checkIfMine(row + 1, column + 1)) {
                            gameboard[row][column].counter += 1;
                        }
                    }
                    if (validRow(row + 1) && validCol(column)) {
                        if (checkIfMine(row + 1, column)) {
                            gameboard[row][column].counter += 1;
                        }
                    }
                    if (validRow(row) && validCol(column + 1)) {
                        if (checkIfMine(row, column + 1)) {
                            gameboard[row][column].counter += 1;
                        }
                    }
                    if (validRow(row - 1) && validCol(column - 1)) {
                        if (checkIfMine(row - 1, column - 1)) {
                            gameboard[row][column].counter += 1;
                        }
                    }
                    if (validRow(row - 1) && validCol(column)) {
                        if (checkIfMine(row - 1, column)) {
                            gameboard[row][column].counter += 1;
                        }
                    }
                    if (validRow(row) && validCol(column - 1)) {
                        if (checkIfMine(row, column - 1)) {
                            gameboard[row][column].counter += 1;
                        }
                    }
                    if (validRow(row + 1) && validCol(column - 1)) {
                        if (checkIfMine(row + 1, column - 1)) {
                            gameboard[row][column].counter += 1;
                        }
                    }
                    if (validRow(row - 1) && validCol(column - 1)) {
                        if (checkIfMine(row - 1, column - 1)) {
                            gameboard[row][column].counter += 1;
                        }
                    }
                }
            }
        }
    }
    
    
    bool done() const {
        for (int row = 0; row < gamebrdRow; ++row) {
            for (int col = 0; col < gamebrdCol; ++col) {
                if (gameboard[row][col].counter == -1) {
                    if (gameboard[row][col].isVisible) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    
    
    bool play(int row, int col) {
        if (checkIfMine(row, col)) {
            return false;
        }
        // if the tile has several mines around it, it will display the amount of mines around
        else if (gameboard[row][col].counter > 0) {
            gameboard[row][col].isVisible = true;
            return true;
        }
        // if the tile is not a mine, it will become visible and continue to run through the play function until it hits
        // a tile that displays a number > 0 which means that it is next to one or more mines
        else if (gameboard[row][col].counter == 0) {
            gameboard[row][col].isVisible = true;
            if (validRow(row + 1) && validCol(col + 1)) {
                if (!isVisible(row + 1, col + 1)) {
                    play(row + 1, col + 1);
                }
            }
            if (validRow(row + 1) && validCol(col)) {
                if (!isVisible(row + 1, col)) {
                    play(row + 1, col);
                }
            }
            if (validRow(row) && validCol(col + 1)) {
                if (!isVisible(row, col + 1)) {
                    play(row, col + 1);
                }
            }
            if (validRow(row - 1) && validCol(col - 1)) {
                if (!isVisible(row - 1, col - 1)) {
                    play(row - 1, col - 1);
                }
            }
            if (validRow(row - 1) && validCol(col)) {
                if (!isVisible(row - 1, col)) {
                    play(row - 1, col);
                }
            }
            if (validRow(row) && validCol(col - 1)) {
                if (!isVisible(row, col - 1)) {
                    play(row, col - 1);
                }
            }
            if (validRow(row + 1) && validCol(col - 1)) {
                if (!isVisible(row + 1, col - 1)) {
                    play(row + 1, col - 1);
                }
            }
            if (validRow(row - 1) && validCol(col - 1)) {
                if (!isVisible(row - 1, col - 1)) {
                    play(row - 1, col - 1);
                }
            }
        }
        return true;
    }
};



int main() {
    Minesweeper sweeper;
    // Continue until only invisible cells are bombs
    while (!sweeper.done()) {
        sweeper.display(false); // display board without bombs
        
        int row_sel = -1, col_sel = -1;
        while (row_sel == -1) {
            // Get a valid move
            int r, c;
            cout << "row? ";
            cin >> r;
            if (!sweeper.validRow(r)) {
                cout << "Row out of bounds\n";
                continue;
            }
            cout << "col? ";
            cin >> c;
            if (!sweeper.validCol(c)) {
                cout << "Column out of bounds\n";
                continue;
            }
            if (sweeper.isVisible(r,c)) {
                cout << "Square already visible\n";
                continue;
            }
            row_sel = r;
            col_sel = c;
        }
        // Set selected square to be visible. May effect other cells.
        if (!sweeper.play(row_sel,col_sel)) {
            cout << "Sorry, you died..\n";
            sweeper.display(true); // Final board with bombs shown
            exit(0);
        }
    }
    // Ah! All invisible cells are bombs, so you won!
    cout << "You won!!!!\n";
    sweeper.display(true); // Final board with bombs shown
}



