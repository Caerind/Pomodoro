#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main()
{
    sf::RenderWindow app(sf::VideoMode(200, 60), "Pomodoro");
    sf::Image img;
    if (!img.loadFromFile("/usr/local/bin/pomodoro.png"))
        return 0;
    app.setIcon(img.getSize().x,img.getSize().y,img.getPixelsPtr());

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("/usr/local/bin/ring.wav"))
        return 0;
    sf::Sound ring(buffer);

    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"))
        return 0;
    sf::Text text("Click to play !",font,20);
    text.setColor(sf::Color::Black);

    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(200,100));
    shape.setFillColor(sf::Color(255,80,80));

    bool isPlaying = false;
    bool isWorking = false;

    sf::Time timer;
    sf::Clock clock;
    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                if (isPlaying)
                {
                    timer = sf::Time::Zero;
                    isPlaying = false;
                    isWorking = false;
                    shape.setFillColor(sf::Color(255,80,80));
                }
                else
                {
                    timer = sf::Time::Zero;
                    isPlaying = true;
                    isWorking = true;
                    shape.setFillColor(sf::Color(80,255,80));
                }
            }
        }

        if (isPlaying)
        {
            timer += clock.restart();
            if (isWorking && timer.asSeconds() >= 25 * 60)
            {
                timer = sf::Time::Zero;
                ring.play();
                isWorking = false;
                shape.setFillColor(sf::Color(80,80,255));
            }
            else if (!isWorking && timer.asSeconds() >= 5 * 60)
            {
                timer = sf::Time::Zero;
                ring.play();
                isWorking = true;
                shape.setFillColor(sf::Color(80,255,80));
            }
        }

        if (isPlaying)
        {
            int totalSeconds = static_cast<int>(timer.asSeconds());
            int minutes = totalSeconds / 60;
            int seconds = totalSeconds % 60;

            text.setString(std::string(std::to_string(minutes) + " : " + std::to_string(seconds)));
        }
        else
        {
            text.setString("Click to play !");
        }

        text.setPosition(app.getSize().x/2-text.getGlobalBounds().width/2, app.getSize().y/2-text.getGlobalBounds().height/2);

        app.clear();
        app.draw(shape);
        app.draw(text);
        app.display();
    }

    return EXIT_SUCCESS;
}
