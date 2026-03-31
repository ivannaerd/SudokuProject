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
        int mistakes = 0;
        void check_ans(int row, int col, int guess)
        {
            if(solution[row][col] == guess)
            {
                board[row][col] = guess;
                cout<< "great guess" << '\n';
            }
            else
            {
                mistakes++;
                cout<< "wrong";
                cout<<" mistakes "<< mistakes<< '\n';
                
            }
        }
        bool finish(){
            for(int i = 0; i < 9; i++)
                for(int j = 0; j < 9; j++)
                    if(board[i][j] == 0)
                        return false;
            return true;
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

    
    while(sudoku.mistakes < 3)
    {
        sudoku.display();

        int row, col, guess;
        cout << "write row and col number and your guess " << '\n';
        cin >> row >> col >> guess;
        row--;
        col--;

        sudoku.check_ans(row, col, guess);

        if(sudoku.finish())
        {
            cout<< "you solved, congrats";
            break;
        }
    }
    if(sudoku.mistakes == 3)
        cout<<"Game over"<<'\n';
        
        
}