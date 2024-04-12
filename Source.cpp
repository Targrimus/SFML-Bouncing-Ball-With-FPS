#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <random>



std::string vector2str(sf::Vector2f vec) {
    std::ostringstream oss;
    oss << std::setprecision(4) << "(" << vec.x << "," << vec.y << ")";
    return oss.str();
};


int main()
{
    
    // create the window
    sf::VideoMode mode = sf::VideoMode::getDesktopMode();

    sf::RenderWindow window(sf::VideoMode(mode.width, mode.height), "My window", sf::Style::Fullscreen);

    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(30);

    float gravity = 9.81f;




    // Ball settings
    float ballRadius = mode.height / 10.0;
    sf::CircleShape ball(ballRadius);
    ball.setFillColor(sf::Color::Green);
    ball.setOrigin(ballRadius, ballRadius);
    ball.setPosition(mode.width/2, mode.height/2);


    //std::cout << ball.getOrigin().x << ", " << ball.getOrigin().y;
    
    //ball.setPosition(sf::Vector2f(mode.width, mode.height));
    std::random_device r;
    std::default_random_engine e(r());
    std::uniform_real_distribution<float> uniform_dist(5.0, 20.0);

    float velocity_x = uniform_dist(e);
    float velocity_y = uniform_dist(e);

   
    //set up font
    sf::Font font;
    font.loadFromFile("C:\\windows\\fonts\\arial.ttf");

    //setup text
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setString("(0000,0000)");
    text.setFillColor(sf::Color::Black);
    text.setOrigin(sf::Vector2f(ballRadius/1.8, ballRadius/4.2));
    text.setPosition(ball.getPosition());
    text.setString(vector2str(ball.getPosition()));
    

    sf::Text fps;
    fps.setFont(font);
    fps.setFillColor(sf::Color::Red);
    fps.setCharacterSize(mode.height / 40);

    sf::Clock clock;


    // run the program as long as the window is open
    while (window.isOpen())
    {
        float currentTime = clock.restart().asSeconds();
        std::cout << "FPS: " << 1.f / currentTime << "\r";
        fps.setString("FPS: " + vector2str(sf::Vector2f(1.f / currentTime,0)));

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyReleased)
                if(event.key.code == sf::Keyboard::Escape)
                    window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        if (ball.getPosition().x < 0+ballRadius || ball.getPosition().x > mode.width- ballRadius)
            velocity_x *= -1;
        else if (ball.getPosition().y < 0 + ballRadius || ball.getPosition().y > mode.height- ballRadius)
            velocity_y *= -1;

        
        ball.setPosition(ball.getPosition() + sf::Vector2f(velocity_x, velocity_y));
        sf::sleep(sf::microseconds(1000));
        
        
        //std::cout << ball.getPosition().x << "," << ball.getPosition().y << std::endl;

        //ball.setPosition(ball.getPosition() + sf::Vector2f(1, 1));

        text.setString(vector2str(ball.getPosition()));
        text.setPosition(text.getPosition() + sf::Vector2f(velocity_x, velocity_y));

        //fps.setString("(" + sf::)
        // end the current frame
        

        
       

        window.draw(ball);
        window.draw(text);
        window.draw(fps);
        window.display();

        //std::cout << 1.f/ clock.getElapsedTime().asSeconds() << std::endl;
        //clock.restart();
    }

    return 0;
}