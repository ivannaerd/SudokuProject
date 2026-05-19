#include "sudoku.h"
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>



using namespace std;

int main()
{
    Sudoku sudoku;

    //nowe wymiary
    float newY = 50.f;


    
    cout << "choose level and type E-easy, M-medium, H-hard" << '\n';
    char l;
    cin >> l;
    if(l == 'E')
    {
        sudoku.load_board("data/easy_solution.txt", sudoku.solution);
        sudoku.load_board("data/easy_board.txt", sudoku.original);
        sudoku.load_board("data/easy_board.txt", sudoku.board);
        sudoku.maxhints = 3;
    }
    else if(l == 'M')
    {
        sudoku.load_board("data/medium_board.txt", sudoku.original);
        sudoku.load_board("data/medium_solution.txt", sudoku.solution);
        sudoku.load_board("data/medium_board.txt", sudoku.board);
        sudoku.maxhints = 2;
    }
    else if(l == 'H')
    {
        sudoku.load_board("data/hard_solution.txt", sudoku.solution);
        sudoku.load_board("data/hard_board.txt", sudoku.original);
        sudoku.load_board("data/hard_board.txt", sudoku.board);
        sudoku.maxhints = 1;
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

    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(600,700)), "Sudoku"); //okno
    float cellSize = 600.0f / 9; 
    //zadna kratka wybrana
    int selectedRow = -1;
    int selectedCol = -1;

    //panel
    float panelY = 650.f;
    float panelHight = 50.f;
    float panelWidth = 600.f / 10.f;

    bool gameOver = false;
    //note
    bool noteMode = false;
    bool panelMode = false;

    int selectedNumber = 0;
    while(window.isOpen()){
        while(auto event = window.pollEvent()) //sprawdza czy co sie wydarzylo i zapisuje
        {
        
            if(event->is<sf::Event::Closed>()) //czy ktos kliknal x
                window.close();
            if(gameOver)
                continue;
            if (event->is<sf::Event::MouseButtonPressed>()){
                if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>())
                {
                    if (mouse->button == sf::Mouse::Button::Left)
                    {
                        //pobieram pozycje
                        int x = mouse->position.x;
                        int y = mouse->position.y;

                        //panel
                        if(y >= panelY){
                            if(selectedRow == -1 || selectedCol == -1){
                                continue;
                            }
                            int index = x/panelWidth;
                            if(index == 0){
                                noteMode = !noteMode;
                            }
                            else{
                                selectedNumber = index;
    
                                if(noteMode){
                                    sudoku.add_note(selectedRow, selectedCol, selectedNumber);
                                }
                                else{
                                    if(sudoku.solution[selectedRow][selectedCol] == selectedNumber){
                                        sudoku.board[selectedRow][selectedCol] = selectedNumber;
                                    }
                                    else{
                                        sudoku.mistakes++;
                                    }
                                    
                                }
                            }
                            panelMode = true;

                        }
                        //kliki sudoku
                        else{
                            //zamieniam na kratki
                            int col = x / cellSize;
                            int row = (y - newY) / cellSize;
                            panelMode = true;
                            //zakaz edytowania pocztakowych
                            if(sudoku.original[row][col] != 0)
                                continue;

                            selectedCol = col;
                            selectedRow = row;
                            panelMode = true;
                            cout << "Row: " << selectedRow 
                                << " Col: " << selectedCol << endl;
                        }



                    }
                       
                    if (mouse->button == sf::Mouse::Button::Right)
                    {
                        //pobieram pozycje
                        int x = mouse->position.x;
                        int y = mouse->position.y;
                        //zamieniam na kratki
                        int col = x / cellSize;
                        int row = (y - newY)/ cellSize;
                        
                        if(sudoku.hints >= sudoku.maxhints){
                            cout << "no more hints" << endl;
                            continue;
                        }

                        if(sudoku.original[row][col] == 0){
                            sudoku.board[row][col] = sudoku.solution[row][col];
                            sudoku.hints++;
                        }
                    }
                }
            }
            //wprowadza wartosci
            if(event->is<sf::Event::TextEntered>()){
                const auto* text = event->getIf<sf::Event::TextEntered>(); //char
                char c = static_cast<char>(text ->unicode); //zamieniam kod znaku na znak
                if(c >= '1' && c <= '9'){
                    cout<< "wpisano " << c << '\n';
                    int val = c - '0';
                    if(sudoku.original[selectedRow][selectedCol] == 0)
                    {
                        if(val == sudoku.solution[selectedRow][selectedCol]){
                            sudoku.board[selectedRow][selectedCol] = val;
                        }
                        else
                            sudoku.mistakes++;  
                    }
                }
            
            }
            if(sudoku.mistakes == 3)
            {
                // cout<<"Game over"<<'\n';
                // window.close();
                gameOver = true;
            }
        }
        window.clear(sf::Color::White);
    
        for(int i = 0; i <= 9; i++)
        {
            float thickness = (i%3 == 0) ? 3.f : 1.f;// pogrubiam co 3
            //poziome
            sf::RectangleShape hline(sf::Vector2f(600,thickness));
            hline.setPosition(sf::Vector2f(0.f, i * cellSize + newY - (thickness/2))); // srodkowanie
            hline.setFillColor(sf::Color::Black);
            window.draw(hline);
        
            //pionowe
            sf::RectangleShape vline(sf::Vector2f(thickness,600));
            vline.setPosition(sf::Vector2f(i * cellSize - (thickness/2), newY));
            vline.setFillColor(sf::Color::Black);
            window.draw(vline);
        }
        //podswietlenie
        if (selectedRow != -1 && selectedCol != -1){
            sf::RectangleShape highlight(sf::Vector2f(cellSize, cellSize));
            highlight.setPosition({
                selectedCol * cellSize,
                selectedRow * cellSize + newY
            });
            
            highlight.setFillColor(sf::Color(225, 192, 203));
            window.draw(highlight);
        }

        

        //qypisanie ramki z numerami
   
        
        //podswietlenie panelu

        if(noteMode == true){
            sf::RectangleShape highlight(sf::Vector2f(panelWidth*10, panelHight));
            highlight.setPosition({0.f, panelY});
            highlight.setFillColor(sf::Color(73, 157, 208));
            window.draw(highlight);
        }

        else if (panelMode == true){
            sf::RectangleShape highlight(sf::Vector2f(panelWidth*10, panelHight));
            highlight.setPosition({0.f, panelY});
            highlight.setFillColor(sf::Color(225, 192, 203));
            window.draw(highlight);
        }
        else{
            sf::RectangleShape highlight(sf::Vector2f(panelWidth*10, panelHight));
            highlight.setPosition({0.f, panelY});
            highlight.setFillColor(sf::Color::White);
            window.draw(highlight);
        }

        for(int i =0; i<10; i++){
            sf::RectangleShape box(sf::Vector2f(panelWidth, panelHight));
            box.setPosition(sf::Vector2f(i*panelWidth, panelY));
            box.setFillColor(sf::Color::Transparent);
            box.setOutlineThickness(1.f);
            box.setOutlineColor(sf::Color::Black);
            window.draw(box);

        }
        
        //wypisanie w box
       
        for(int j = 0; j < 10; j++){
            sf::Text text(font);
            if(j == 0){
                text.setString("N");
            }
            else{
                 text.setString(std::to_string(j));
            }
            
            text.setCharacterSize(40);
            text.setFillColor(sf::Color::Black);

            float x = j * panelWidth + panelWidth / 2.f - 10.f;
            float y = panelY + 5.f;

            text.setPosition(sf::Vector2f(x, y));
            window.draw(text);

        }

        
        

        //wypisanie liczb
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                if(sudoku.board[i][j] != 0 ){
                    sf::Text text(font);
                    text.setString(std::to_string(sudoku.board[i][j])); //konwert w tekst i ustawiam
                    text.setCharacterSize(40);
                    //rozny kolor
                    if(sudoku.original[i][j] != 0)
                        text.setFillColor(sf::Color::Black);
                    else
                        text.setFillColor(sf::Color::Blue);
                    //wyliczam pozycje
                    float x = j * cellSize + cellSize / 2.f - 10.f;
                    float y = newY + i * cellSize + cellSize / 2.f - 20.f;

                    text.setPosition(sf::Vector2f(x, y));
                    window.draw(text);
                }

            }
        }

        //NOTED wpisanie z trybu notes

        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                if(sudoku.board[i][j] == 0 ){
                    for(int k = 0; k < 9; k++){
                        if(sudoku.notes[i][j][k]){
                            sf::Text note(font);
                            note.setString(std::to_string(k+1)); //konwert w tekst i ustawiam
                            note.setCharacterSize(40);
                            note.setFillColor(sf::Color(180,0,255));
                        
                            //wyliczam pozycje
                            float notex = j * cellSize + cellSize / 2.f - 10.f;
                            float notey = newY + i * cellSize + cellSize / 2.f - 20.f;
                            note.setPosition(sf::Vector2f(notex, notey));
                            window.draw(note);
                        }
                    }
                }

            }
        }
  

        sf::Text mistakes(font);
        mistakes.setString("Mistakes: " + std::to_string(sudoku.mistakes) + "/3");
        mistakes.setCharacterSize(25);
        mistakes.setFillColor(sf::Color::Red);
        mistakes.setPosition(sf::Vector2f(10.f, 10.f));
        window.draw(mistakes);

        //game over
        if(gameOver)
        {
            sf::Text gameover(font);
            gameover.setString("GAME OVER");
            gameover.setCharacterSize(60);
            gameover.setFillColor(sf::Color::Red);
            gameover.setPosition(sf::Vector2f(140.f, 250.f));

            window.draw(gameover);
        }
        window.display();
        }       
    
}


