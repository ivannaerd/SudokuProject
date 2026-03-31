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

        void display()
        {
            for(int i = 0; i < 9; i++)
            {
                if(i % 3 == 0 && i != 0)
                    cout<< "-------+-------+------" << '\n';
                for(int j = 0; j < 9; j++)
                {
                    if(j % 3 == 0 && j != 0)
                        cout<<"| ";
                    if(board[i][j]== 0)
                        cout << "* ";
                    else
                        cout<< board[i][j] <<" ";
                }
                //po jednej linjce przeskakujemy w dol
                cout << "\n";
            }
        }

};

int main()
{
    Sudoku sudoku;

    cout << "choose level and type E-easy, M-medium, H-hard" << '\n';
    char l;
    cin >> l;
    if(l == 'E')
    {
        sudoku.load_board("data/easy_solution.txt", sudoku.solution);
        sudoku.load_board("data/easy_board.txt", sudoku.board);
    }
    else if(l == 'M')
    {
        sudoku.load_board("data/medium_solution.txt", sudoku.solution);
        sudoku.load_board("data/medium_board.txt", sudoku.board);
    }
    else if(l == 'H')
    {
        sudoku.load_board("data/hard_solution.txt", sudoku.solution);
        sudoku.load_board("data/hard_board.txt", sudoku.board);
    }
    else
        cout << "level doesn't exist";

    sudoku.display();
}