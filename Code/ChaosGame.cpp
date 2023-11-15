// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);

    vector<Vector2f> vertices;
    vector<Vector2f> points;

    ///load the font and if fail to load display error message & quit program
    Font font;
    if (!font.loadfromFile("ARCHITIC.TTF"));
    {
        cout << "Error loading font!" << endl;
        return -1;
    }

    ///Title text
    Text title_text;
    title_text.setFont(font);
    title_text.setCharacterSize(250);
    title_text.setFillColor(Color::White);
    title_text.setPosition(150,150);
    title_text.setString("Chaos Game");

    //Start text
    Text start_text;
    start_text.setFont(font);
    start_text.setCharacterSize(50);
    start_text.setFillColor(Color::White);
    start_text.setPosition(150, 100);
    start_text.setString("Press any key to start.");

    bool titleScreen = true;





	while (window.isOpen())
	{
        /*
		****************************************
		Handle the players input
		****************************************
		*/

        Event event;
		while (window.pollEvent(event))
		{
            if (event.type == Event::Closed)
            {
				// Quit the game when the window is closed
				window.close();
            }

            if (event.type == Event::KeyPressed && titleScreen)
            {
                titleScreen = false;
            }


            if (!titleScreen && event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    if(vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if(points.size() == 0)
                    {
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                        ///fourth click
                        ///push back to points vector
                    }
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

        /*
		****************************************
		Update
		****************************************
		*/

        if(points.size() > 0)
        {
            for(int i = 0; i < 100; i++)
            {
                double midpoint_x, midpoint_y;

                ///select random vertex
                int random = rand() % vertices.size();

                ///calculate midpoint between random vertex and last point in vector
                midpoint_x = (((vertices.at(random).x) - (points.back().x)) / 2);
                midpoint_y = (((vertices.at(random).y) - (points.back().y)) / 2);

                ///push back the new coord
                points.pusback(Vector2f(midpoint_x, midpoint_y));

            }
        }

        /*
		****************************************
		Draw
		****************************************
		*/
        window.clear();

        if (titleScreen)
        {
            window.draw(title_text);
            window.draw(start_text);
        }
        else
        {
            text.setString("This is your fractal pattern. Press ESC to exit");
            window.draw(text)

            ///use the rect to print our the fractal
            for(int i = 0; i < points.size(); i++)
            {
                RectangleShape rect(Vector2f(10,10));
                rect.setPosition(Vector2f(points[i].x, points[i].y));
                rect.setFillColor(Color::Blue);
                window.draw(rect);
            }
        }


        window.display();
    }
}