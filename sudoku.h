#pragma once
#include <string>

class Sudoku{
    public:
        int board[9][9]; //unsolved
        int solution[9][9];
        int mistakes = 0;
        int original[9][9];//bez zmian
        int notes[9][9][9] = {}; //row col ans
        //licznik
        int hints = 0;
        int maxhints = 0;

        void load_board(const std::string& filename, int arr[9][9]);
        void check_ans(int row, int col, int guess);
        void add_note(int row, int col, int note);
        void display();
        bool finish();
};     

