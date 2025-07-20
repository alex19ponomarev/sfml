#include <SFML/Graphics.hpp>
#include <sstream>
using namespace sf;
int main() {
    
    sf::RenderWindow window(sf::VideoMode(800, 600), "Создание и удаление кружков");

    
    std::vector<sf::CircleShape> circles;
    int counter = 0;

    sf::Font font;

    font.loadFromFile("arial.ttf");

    sf::Text counterText;
    counterText.setFont(font);
    counterText.setCharacterSize(24);
    counterText.setFillColor(sf::Color::Black);
    counterText.setPosition(10, 10);
     auto updateText = [&]() {
        std::stringstream ss;
        ss << "Number of clicks: " << counter;
        counterText.setString(ss.str());
    };
    updateText();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            
            if (event.type == sf::Event::Closed)
                window.close();

            
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    
                    sf::CircleShape circle(20); 
                    circle.setFillColor(sf::Color::Blue);
                    circle.setPosition(event.mouseButton.x - 20, event.mouseButton.y - 20); 
                    circles.push_back(circle);
                 
                }
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    
                    sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                    
                    for (auto it = circles.begin(); it != circles.end(); ++it) {
                        sf::Vector2f circlePos = it->getPosition();
                        float dx = circlePos.x + it->getRadius() - mousePos.x;
                        float dy = circlePos.y + it->getRadius() - mousePos.y;
         
                        if (dx * dx + dy * dy <= it->getRadius() * it->getRadius()) {
                            circles.erase(it);
                            break; 
                            
                        }
                    }
                }
            }
        }

        
        window.clear(sf::Color::White);

        
        for (const auto& circle : circles) {
            window.draw(circle);
        }

        window.draw(counterText);
        window.display();
    }

    return 0;
}
