#include "sudoku.h"
#include <fstream>
#include <iostream>

using namespace std;

//to co bez sfml
void Sudoku::load_board(const string& filename, int arr[9][9])
{
    ifstream file(filename);
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            file >> arr[i][j];
}

void Sudoku::check_ans(int row, int col, int guess)
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

void Sudoku::add_note(int row, int col, int note){ //note co kliknelam na pasku
    if(original[row][col] != 0){
        return;
    }
    else{
        int id = note - 1;//na id w tab
        for(int i = 0; i < 9; i++){
            notes[row][col][i] = false; //wumazuje jak cos bylo wpisane
        }

        notes[row][col][id]= true; //ustawiam nowe
    }
//notes trzyma co jest jako notatka
}

bool Sudoku::finish(){
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            if(board[i][j] == 0)
                return false;
    return true;
}

void Sudoku::display()
{
    for(int i = 0; i < 9; i++)
    {
        if(i % 3 == 0 && i != 0)
            cout << "-------+-------+------" << '\n';

        for(int j = 0; j < 9; j++)
        {
            if(j % 3 == 0 && j != 0)
                cout << "| ";

            if(board[i][j] == 0)
                cout << "* ";
            else
                cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}