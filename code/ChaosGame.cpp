// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

// Make the code easier to type with "using namespace"
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

    // Load the font once, outside the loop
    Font font;
    if (!font.loadFromFile("SpaceMono-Regular.ttf"))
    {
        cout << "Font did not load" << endl;
        return -1;
    }

    Text text;
    text.setFont(font);
    text.setString("Click 3 spots to make a triangle. The 4th click is where your fractal will originate.");
    text.setCharacterSize(36);
    text.setFillColor(Color::Magenta);

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

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    if (vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if (points.size() == 0)
                    {
                        /// fourth click
                        /// push back to points vector
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
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

        if (points.size() > 0)
        {
            /// generate more point(s)
            for (int i = 0; i < 100; i++)
            {
                /// randomly selecting one of the triangle vertices
                int randomVertexIndex = rand() % 3;
                /// vector object
                Vector2f randomVertex = vertices[randomVertexIndex];

                /// calculate midpoint between random vertex and the last point in the vector
                Vector2f lastPoint = points.back(); // Retrieves the last element in the points vector
                Vector2f midpoint(
                        (randomVertex.x + lastPoint.x) / 2.0f,
                        (randomVertex.y + lastPoint.y) / 2.0f
                );

                /// push back the newly generated coord.
                points.push_back(midpoint);
            }
        }

        /*
        ****************************************
        Draw
        ****************************************
        */
        window.clear();

        // User instructions with font and text begins.
        text.setPosition(10, 10);
        window.draw(text);
        // User instructions ends.

        for (int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(10, 10));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::Cyan);
            window.draw(rect);
        }

        // Draw fractal points
        for (size_t i = 0; i < points.size(); i++)
        {
            RectangleShape point(Vector2f(2, 2));
            point.setPosition(points[i]);
            point.setFillColor(Color::Green);
            window.draw(point);
        }

        window.display();
    }
}
