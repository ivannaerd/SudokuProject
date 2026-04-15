
#include "sudoku.h"
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>



using namespace std;

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


    sf::Font font;
    //font.openFromFile("font.ttf");
    //sprawdzam czy wczytal sie font, bo byl warning
    if (!font.openFromFile("font.TTF"))
    {
        std::cout << "ERROR";
    }

    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(600,600)), "Sudoku"); //okno
    float cellSize = 600.0f / 9; 
    //zadna kratka wybrana
    int selectedRow = -1;
    int selectedCol = -1;
    while(window.isOpen()){
        while(auto event = window.pollEvent()) //sprawdza czy co sie wydarzylo i zapisuje
        {
            if(event->is<sf::Event::Closed>()) //czy ktos kliknal x
                window.close();
            if (event->is<sf::Event::MouseButtonPressed>()){
                if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>())
                {
                    if (mouse->button == sf::Mouse::Button::Left)
                    {
                        //pobieram pozycje
                        int x = mouse->position.x;
                        int y = mouse->position.y;
                        //zamieniam na kratki
                        selectedCol = x / cellSize;
                        selectedRow = y / cellSize;

                        cout << "Row: " << selectedRow 
                            << " Col: " << selectedCol << endl;
                    }
                }
            }
        }


        window.clear(sf::Color::White);
    
        for(int i = 0; i <= 9; i++)
        {
            float thickness = (i%3 == 0) ? 3.f : 1.f;// pogrubiam co 3
            //poziome
            sf::RectangleShape hline(sf::Vector2f(600,thickness));
            hline.setPosition(sf::Vector2f(0.f, i * cellSize - (thickness/2))); // srodkowanie
            hline.setFillColor(sf::Color::Black);
            window.draw(hline);
        
            //pionowe
            sf::RectangleShape vline(sf::Vector2f(thickness,600));
            vline.setPosition(sf::Vector2f(i * cellSize - (thickness/2), 0.f));
            vline.setFillColor(sf::Color::Black);
            window.draw(vline);
        }
        //podswietlenie
        if (selectedRow != -1 && selectedCol != -1){
            sf::RectangleShape highlight(sf::Vector2f(cellSize, cellSize));
            highlight.setPosition({
                selectedCol * cellSize,
                selectedRow * cellSize
            });
            highlight.setFillColor(sf::Color(225, 192, 203));
            window.draw(highlight);
        }
        //wypisanie liczb
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                if(sudoku.board[i][j] != 0 ){
                    sf::Text text(font);
                    text.setString(std::to_string(sudoku.board[i][j])); //konwert w tekst i ustawiam
                    text.setCharacterSize(40);
                    text.setFillColor(sf::Color::Black);
                    //wyliczam pozycje
                    float x = j * cellSize + cellSize / 2.f - 10.f;
                    float y = i * cellSize + cellSize / 2.f - 25.f;

                    text.setPosition(sf::Vector2f(x, y));
                    window.draw(text);
                }

            }
        }
        window.display();
    }       
    
   
    // cout << "choose level and type E-easy, M-medium, H-hard" << '\n';
    // char l;
    // cin >> l;
    // if(l == 'E')
    // {
    //     sudoku.load_board("data/easy_solution.txt", sudoku.solution);
    //     sudoku.load_board("data/easy_board.txt", sudoku.board);
    // }
    // else if(l == 'M')
    // {
    //     sudoku.load_board("data/medium_solution.txt", sudoku.solution);
    //     sudoku.load_board("data/medium_board.txt", sudoku.board);
    // }
    // else if(l == 'H')
    // {
    //     sudoku.load_board("data/hard_solution.txt", sudoku.solution);
    //     sudoku.load_board("data/hard_board.txt", sudoku.board);
    // }
    // else
    //     cout << "level doesn't exist";

    
    // while(sudoku.mistakes < 3)
    // {
    //     sudoku.display();

    //     int row, col, guess;
    //     cout << "write row and col number and your guess " << '\n';
    //     cin >> row >> col >> guess;
    //     row--;
    //     col--;

    //     sudoku.check_ans(row, col, guess);

    //     if(sudoku.finish())
    //     {
    //         cout<< "you solved, congrats";
    //         break;
    //     }
    // }
    // if(sudoku.mistakes == 3)
    //     cout<<"Game over"<<'\n';


}

//wypisac liczby i sczytac wspl z myszki