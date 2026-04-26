#pragma once
#include <string>

class Sudoku{
    public:
        int board[9][9]; //unsolved
        int solution[9][9];
        int mistakes = 0;
        int original[9][9];//bez zmian

        void load_board(const std::string& filename, int arr[9][9]);
        void check_ans(int row, int col, int guess);
        void display();
        bool finish();
};     

