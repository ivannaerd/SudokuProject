#include <iostream>
#include <fstream>

using namespace std;

class Sudoku{
    public:
        int board[9][9]; //unsolved
        int solution[9][9];

        void load_board(const string& filename, int arr[9][9])
        {
            ifstream file(filename);
            for(int i = 0; i < 9; i++)
                for(int j = 0; j < 9; j++)
                    file >> arr[i][j];
        }

};