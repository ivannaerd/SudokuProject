#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>


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

    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(600,600)), "Sudoku"); //okno
    float cellSize = 600.0f / 9; 

    while(window.isOpen()){
        while(auto event = window.pollEvent()) //sprawdza czy co sie wydarzylo i zapisuje
        {
            if(event->is<sf::Event::Closed>()) //czy ktos kliknal x
                window.close();
        }

        window.clear(sf::Color::White);

        for(int i = 0; i <= 9; i++)
        {
            float thickness = (i%3 == 0) ? 3.f : 1.f;// pogrubiam co 3
            //poziome
            sf::RectangleShape hline(sf::Vector2f(600,thickness));
            hline.setPosition(0.f, i * cellSize - (thickness/2));
            hline.setFillColor(sf::Color::Black);
            window.draw(hline);
        
            //pionowe
            sf::RectangleShape vline(sf::Vector2f(thickness,600));
            vline.setPosition(i * cellSize - (thickness/2), 0.f));
            vline.setFillColor(sf::Color::Black);
            window.draw(vline);
        }
        window.display();
    }        
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
    //oprawka graficzna


}

