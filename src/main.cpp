#include <SFML/Graphics.hpp>
//#include <Rect.hpp>

#include "Board.h"
#include "Board.cpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

// Important: iterate one dimensional array by row * columns + column

int main()
{
    // Read config
    std::ifstream file;
    file.open("boards/config.cfg");
    if (!file.is_open()) {
        std::cerr << "Failed to open the config file!" << std::endl;
        return 1;
    }
    
    std::string line;
    getline(file, line);
    int columns = stoi(line);
    getline(file, line);
    int rows = stoi(line);
    getline(file, line);
    int mines = stoi(line);
    file.close();

    // Load board
    Board board;
    board.setColumns(columns);
    board.setRows(rows);
    board.newGame(mines);
    //board.ReadFile("boards/testboard1.brd");

    // Create the main window
    sf::RenderWindow app(sf::VideoMode(columns * 32, (rows * 32) + 100), "Minesweeper");
    app.setFramerateLimit(60);
    app.setVerticalSyncEnabled(true);

    // Load a sprite to display
    sf::Texture hidden_t;
    if (!hidden_t.loadFromFile("./images/tile_hidden.png")) return EXIT_FAILURE;
    sf::Sprite hidden(hidden_t);

    sf::Texture reveal_t;
    if (!reveal_t.loadFromFile("images/tile_revealed.png")) return EXIT_FAILURE;
    sf::Sprite reveal(reveal_t);

    sf::Texture mine_t;
    if (!mine_t.loadFromFile("images/mine.png")) return EXIT_FAILURE;
    sf::Sprite mine(mine_t);

    sf::Texture flag_t;
    if (!flag_t.loadFromFile("images/flag.png")) return EXIT_FAILURE;
    sf::Sprite flag(flag_t);

    sf::Texture one_t;
    if (!one_t.loadFromFile("images/number_1.png")) return EXIT_FAILURE;
    sf::Sprite one(one_t);

    sf::Texture two_t;
    if (!two_t.loadFromFile("images/number_2.png")) return EXIT_FAILURE;
    sf::Sprite two(two_t);

    sf::Texture three_t;
    if (!three_t.loadFromFile("images/number_3.png")) return EXIT_FAILURE;
    sf::Sprite three(three_t);

    sf::Texture four_t;
    if (!four_t.loadFromFile("images/number_4.png")) return EXIT_FAILURE;
    sf::Sprite four(four_t);

    sf::Texture five_t;
    if (!five_t.loadFromFile("images/number_5.png")) return EXIT_FAILURE;
    sf::Sprite five(five_t);

    sf::Texture six_t;
    if (!six_t.loadFromFile("images/number_6.png")) return EXIT_FAILURE;
    sf::Sprite six(six_t);

    sf::Texture seven_t;
    if (!seven_t.loadFromFile("images/number_7.png")) return EXIT_FAILURE;
    sf::Sprite seven(seven_t);

    sf::Texture eight_t;
    if (!eight_t.loadFromFile("images/number_8.png")) return EXIT_FAILURE;
    sf::Sprite eight(eight_t);

    int face_x = ((columns / 2) - 1) * 32;
    int face_y = rows * 32;

    sf::Texture happy_t;
    if (!happy_t.loadFromFile("images/face_happy.png")) return EXIT_FAILURE;
    sf::Sprite happy(happy_t);
    happy.setPosition(sf::Vector2f(face_x, face_y));

    sf::Texture win_t;
    if (!win_t.loadFromFile("images/face_win.png")) return EXIT_FAILURE;
    sf::Sprite win(win_t);
    win.setPosition(sf::Vector2f(face_x, face_y));

    sf::Texture lose_t;
    if (!lose_t.loadFromFile("images/face_lose.png")) return EXIT_FAILURE;
    sf::Sprite lose(lose_t);
    lose.setPosition(sf::Vector2f(face_x, face_y));

    sf::Texture debug_t;
    if (!debug_t.loadFromFile("images/debug.png")) return EXIT_FAILURE;
    sf::Sprite debug(debug_t);
    debug.setPosition(sf::Vector2f((face_x / 32 + 2 + 2) * 32, face_y));

    sf::Texture test1_t;
    if (!test1_t.loadFromFile("images/test_1.png")) return EXIT_FAILURE;
    sf::Sprite test1(test1_t);
    test1.setPosition(sf::Vector2f((columns - 6) * 32, face_y));

    sf::Texture test2_t;
    if (!test2_t.loadFromFile("images/test_2.png")) return EXIT_FAILURE;
    sf::Sprite test2(test2_t);
    test2.setPosition(sf::Vector2f((columns - 4) * 32, face_y));

    sf::Texture test3_t;
    if (!test3_t.loadFromFile("images/test_3.png")) return EXIT_FAILURE;
    sf::Sprite test3(test3_t);
    test3.setPosition(sf::Vector2f((columns - 2) * 32, face_y));

    sf::Texture digits_t;
    if (!digits_t.loadFromFile("images/digits.png")) return EXIT_FAILURE;
    sf::Sprite digits(digits_t);

    int x;
    int y;
    int counter;

	// Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                x = sf::Mouse::getPosition(app).x / 32;
                y = sf::Mouse::getPosition(app).y / 32;
                if(board.winning() == true && board.won() == false && x < columns && y < rows) board.setReveal(y, x);
                else if(happy.getGlobalBounds().contains(sf::Mouse::getPosition(app).x, sf::Mouse::getPosition(app).y) ||
                        lose.getGlobalBounds().contains(sf::Mouse::getPosition(app).x, sf::Mouse::getPosition(app).y) ||
                        win.getGlobalBounds().contains(sf::Mouse::getPosition(app).x, sf::Mouse::getPosition(app).y))
                        {
                            board.setRows(rows);
                            board.setColumns(columns);
                            board.newGame(mines);
                        }
                else if (debug.getGlobalBounds().contains(sf::Mouse::getPosition(app).x, sf::Mouse::getPosition(app).y) && board.won() == false)
                {
                    board.setDebug(!board.getDebug());
                }
                else if (test1.getGlobalBounds().contains(sf::Mouse::getPosition(app).x, sf::Mouse::getPosition(app).y))
                {
                    board.setColumns(25);
                    board.setRows(16);
                    board.ReadFile("boards/testboard1.brd");
                }
                else if (test2.getGlobalBounds().contains(sf::Mouse::getPosition(app).x, sf::Mouse::getPosition(app).y))
                {
                    board.setColumns(25);
                    board.setRows(16);
                    board.ReadFile("boards/testboard2.brd");
                }
                else if (test3.getGlobalBounds().contains(sf::Mouse::getPosition(app).x, sf::Mouse::getPosition(app).y))
                {
                    board.setColumns(25);
                    board.setRows(16);
                    board.ReadFile("boards/testboard3.brd");
                }
                continue;
            }

            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
            {
                x = sf::Mouse::getPosition(app).x / 32;
                y = sf::Mouse::getPosition(app).y / 32;
                Tile* tile = &board.GetBoard()[y * board.getCols() + x];
                if(board.winning() == true && board.won() == false) board.setFlag(y, x, !tile->flag);
                continue;
            }

            // Close window : exit
            if (event.type == sf::Event::Closed)
            {
                app.close();
            }
        }

        // Clear screen
        app.clear(sf::Color::White);
        // Draw the sprite
        for(int i = 0; i < board.getRows(); i++)
        {
            for(int j = 0; j < board.getCols(); j++)
            {
                Tile* tile = &board.GetBoard()[i * board.getCols() + j];
                // Hidden
                if(tile->reveal == false)
                {
                    hidden.setPosition(sf::Vector2f(j * 32, i * 32));
                    app.draw(hidden);

                    // Debug
                    if(board.getDebug() == true && tile->mine == true)
                    {
                        mine.setPosition(sf::Vector2f(j * 32, i * 32));
                        app.draw(mine);
                    }

                    // Flag
                    if(tile->flag == true)
                    {
                        flag.setPosition(sf::Vector2f(j * 32, i * 32));
                        app.draw(flag);
                    }
                }
                // Revealed
                else
                {
                    reveal.setPosition(sf::Vector2f(j * 32, i * 32));
                    app.draw(reveal);

                    // Mine
                    if(tile->mine == true)
                    {
                        mine.setPosition(sf::Vector2f(j * 32, i * 32));
                        app.draw(mine);
                    }
                    else if(tile->value == 1)
                    {
                        one.setPosition(sf::Vector2f(j * 32, i * 32));
                        app.draw(one);
                    }
                    else if(tile->value == 2)
                    {
                        two.setPosition(sf::Vector2f(j * 32, i * 32));
                        app.draw(two);
                    }
                    else if(tile->value == 3)
                    {
                        three.setPosition(sf::Vector2f(j * 32, i * 32));
                        app.draw(three);
                    }
                    else if(tile->value == 4)
                    {
                        four.setPosition(sf::Vector2f(j * 32, i * 32));
                        app.draw(four);
                    }
                    else if(tile->value == 5)
                    {
                        five.setPosition(sf::Vector2f(j * 32, i * 32));
                        app.draw(five);
                    }
                    else if(tile->value == 6)
                    {
                        six.setPosition(sf::Vector2f(j * 32, i * 32));
                        app.draw(six);
                    }
                    else if(tile->value == 7)
                    {
                        seven.setPosition(sf::Vector2f(j * 32, i * 32));
                        app.draw(seven);
                    }
                    else if(tile->value == 8)
                    {
                        eight.setPosition(sf::Vector2f(j * 32, i * 32));
                        app.draw(eight);
                    }
                }
            }
        }
        // interface
        if(board.won() == true)
        {
            board.flagMines();
            board.setDebug(false);
            app.draw(win);
        }
        else if(board.winning() == true) app.draw(happy);
        else if(board.winning() == false) app.draw(lose);

        app.draw(debug);
        app.draw(test1);
        app.draw(test2);
        app.draw(test3);

        counter = board.getMines() - board.getFlags();

        std::string scounter = std::to_string(counter);

        for(int i = 0; i < scounter.length(); i++)
        {
            if(scounter[i] == '-')
            {
                digits.setTextureRect(sf::IntRect(21 * 10, 0, 21, 32));
            }
            else if(scounter[i] == '0')
            {
                digits.setTextureRect(sf::IntRect(0, 0, 21, 32));
            }
            else if(scounter[i] == '1')
            {
                digits.setTextureRect(sf::IntRect(21, 0, 21, 32));
            }
            else if(scounter[i] == '2')
            {
                digits.setTextureRect(sf::IntRect(21 * 2, 0, 21, 32));
            }
            else if(scounter[i] == '3')
            {
                digits.setTextureRect(sf::IntRect(21 * 3, 0, 21, 32));
            }
            else if(scounter[i] == '4')
            {
                digits.setTextureRect(sf::IntRect(21 * 4, 0, 21, 32));
            }
            else if(scounter[i] == '5')
            {
                digits.setTextureRect(sf::IntRect(21 * 5, 0, 21, 32));
            }
            else if(scounter[i] == '6')
            {
                digits.setTextureRect(sf::IntRect(21 * 6, 0, 21, 32));
            }
            else if(scounter[i] == '7')
            {
                digits.setTextureRect(sf::IntRect(21 * 7, 0, 21, 32));
            }
            else if(scounter[i] == '8')
            {
                digits.setTextureRect(sf::IntRect(21 * 8, 0, 21, 32));
            }
            else if(scounter[i] == '9')
            {
                digits.setTextureRect(sf::IntRect(21 * 9, 0, 21, 32));
            }
            else
            {
                break;
            }
            digits.setPosition(sf::Vector2f(i * 21, face_y));
            app.draw(digits);
        }

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
