#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <SFML/Graphics.hpp>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int KEY_SIZE = 40;
const int KEY_PADDING = 10;
const sf::Color KEY_COLOR = sf::Color::White;
const sf::Color TEXT_COLOR = sf::Color::Black;

std::string generateShuffledKeyboard() {
    std::string standardLayout = "qwertyuiopasdfghjklzxcvbnm";

    // Shuffle the standard layout using a random device as the seed
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(standardLayout.begin(), standardLayout.end(), g);

    return standardLayout;
}

void drawKeyboard(sf::RenderWindow& window, const std::string& keyboard) {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Failed to load font." << std::endl;
        return;
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(TEXT_COLOR);

    int row = 0, col = 0;

    for (char c : keyboard) {
        sf::RectangleShape key(sf::Vector2f(KEY_SIZE, KEY_SIZE));
        key.setFillColor(KEY_COLOR);
        key.setPosition(col * (KEY_SIZE + KEY_PADDING), row * (KEY_SIZE + KEY_PADDING));
        window.draw(key);

        text.setString(std::string(1, c));
        text.setPosition(col * (KEY_SIZE + KEY_PADDING) + KEY_SIZE / 2 - 8, row * (KEY_SIZE + KEY_PADDING) + KEY_SIZE / 2 - 12);
        window.draw(text);

        col++;
        if (col == 10) {
            col = 0;
            row++;
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Randomized Keyboard");
    window.setFramerateLimit(60);

    std::string shuffledKeyboard = generateShuffledKeyboard();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    shuffledKeyboard = generateShuffledKeyboard();
                }
            }
        }

        window.clear(sf::Color::Black);
        drawKeyboard(window, shuffledKeyboard);
        window.display();
    }

    return 0;
}
