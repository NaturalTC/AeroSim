#include "PIDController.h"
#include "Fighter.h"
#include <iostream>
#include <fstream>
#include <deque>
#include <SFML/Graphics.hpp>

int main() {

    // Weights and Parameters
    double targetAltitude = 30000;
    std::unique_ptr<PIDController> controller = std::make_unique<PIDController>(0.05, .05, 0.01, -10, 10);

    // Fighter Object
    std::unique_ptr<Fighter> falcon = std::make_unique<Fighter>("F-35", 700, 0, 5);

    // File I/O
    std::ofstream file("PID_F35_DATA.csv");
    file << "Cycle,Altitude,Error,PID_Output\n";

    // SFML Window
    sf::RenderWindow window(sf::VideoMode({1000u, 700u}), "AeroSim - F-35 PID Altitude Control");
    window.setFramerateLimit(60);

    // Font
    sf::Font font("/System/Library/Fonts/Monaco.ttf");

    // Clouds: {x, y, speed, radius}
    struct Cloud { float x, y, speed, radius; };
    std::vector<Cloud> clouds = {
        {200.f, 100.f, 0.6f, 35.f},
        {450.f, 190.f, 0.9f, 28.f},
        {650.f,  70.f, 1.1f, 40.f},
        {820.f, 280.f, 0.7f, 22.f},
        {120.f, 340.f, 0.8f, 30.f},
        {550.f, 400.f, 1.0f, 25.f},
        {900.f, 130.f, 0.5f, 38.f},
    };

    // Flight trail
    std::deque<sf::Vector2f> trail;

    int i = 0;
    int frameCount = 0;

    // Game Loop
    while (window.isOpen()) {

        // Process events
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
        }

        frameCount++;

        // Update simulation every 3 frames
        if (frameCount % 3 == 0) {
            if (std::abs(targetAltitude - falcon->getAltitude()) >= 10.0) {
                double output = controller->calculate(targetAltitude, falcon->getAltitude(), 0.1);
                falcon->setAltitude(output + falcon->getAltitude());
                file << i << "," << falcon->getAltitude() << "," << controller->getLastError() << "," << output << "\n";
                i++;
                if (i > 10000) {
                    std::cout << "Watchdog: controller failed to converge" << std::endl;
                    window.close();
                }
            } else {
                if (file.is_open()) {
                    std::cout << "Finished at iteration: " << i << std::endl;
                    file.close();
                }
            }
        }

        // Scroll clouds
        for (auto& c : clouds) {
            c.x -= c.speed;
            if (c.x < -80.f) c.x = 1080.f;
        }

        // Map altitude to screen Y
        float groundY       = 650.f;
        float flightArea    = 600.f;
        float screenY       = groundY - (float)(falcon->getAltitude() / 30000.0 * flightArea);
        float targetScreenY = groundY - (float)(targetAltitude        / 30000.0 * flightArea);

        // Update flight trail
        trail.push_back({200.f, screenY});
        if (trail.size() > 120) trail.pop_front();

        bool  climbing  = std::abs(targetAltitude - falcon->getAltitude()) >= 10.0;
        float tiltAngle = climbing ? -12.f : 0.f;

        // Target altitude line
        sf::RectangleShape targetLine(sf::Vector2f(1000.f, 2.f));
        targetLine.setFillColor(sf::Color(255, 80, 80, 180));
        targetLine.setPosition({0.f, targetScreenY});

        // Ground
        sf::RectangleShape ground(sf::Vector2f(1000.f, 55.f));
        ground.setFillColor(sf::Color(34, 100, 34));
        ground.setPosition({0.f, 650.f});

        // Metrics panel
        sf::RectangleShape panel(sf::Vector2f(235.f, 190.f));
        panel.setFillColor(sf::Color(0, 0, 0, 170));
        panel.setPosition({755.f, 10.f});

        double error = targetAltitude - falcon->getAltitude();

        sf::Text altText(font,    "ALT:    " + std::to_string((int)falcon->getAltitude()) + " ft", 15);
        sf::Text tgtText(font,    "TARGET: " + std::to_string((int)targetAltitude)        + " ft", 15);
        sf::Text errText(font,    "ERROR:  " + std::to_string((int)error)                 + " ft", 15);
        sf::Text cycleText(font,  "CYCLE:  " + std::to_string(i),                                  15);
        sf::Text statusText(font, climbing ? "STATUS: CLIMBING" : "STATUS: ON TARGET",             15);

        altText.setFillColor(sf::Color::White);
        tgtText.setFillColor(sf::Color(255, 100, 100));
        errText.setFillColor(sf::Color(255, 210, 0));
        cycleText.setFillColor(sf::Color::Cyan);
        statusText.setFillColor(climbing ? sf::Color(100, 255, 100) : sf::Color(0, 255, 180));

        altText.setPosition({765.f,  20.f});
        tgtText.setPosition({765.f,  50.f});
        errText.setPosition({765.f,  80.f});
        cycleText.setPosition({765.f, 110.f});
        statusText.setPosition({765.f, 148.f});

        // --- Draw ---
        window.clear(sf::Color(25, 80, 150));

        // Clouds
        for (const auto& c : clouds) {
            sf::CircleShape cloud(c.radius);
            cloud.setFillColor(sf::Color(255, 255, 255, 160));
            cloud.setPosition({c.x, c.y});
            window.draw(cloud);
            sf::CircleShape cloud2(c.radius * 0.7f);
            cloud2.setFillColor(sf::Color(255, 255, 255, 140));
            cloud2.setPosition({c.x + c.radius * 0.8f, c.y + c.radius * 0.3f});
            window.draw(cloud2);
        }

        // Flight trail
        for (size_t t = 0; t < trail.size(); t++) {
            sf::CircleShape dot(2.f);
            uint8_t alpha = (uint8_t)(255 * t / trail.size());
            dot.setFillColor(sf::Color(255, 140, 0, alpha));
            dot.setPosition(trail[t]);
            window.draw(dot);
        }

        window.draw(targetLine);
        window.draw(ground);

        // Draw aircraft via polymorphic call
        falcon->draw(window, screenY, tiltAngle);

        window.draw(panel);
        window.draw(altText);
        window.draw(tgtText);
        window.draw(errText);
        window.draw(cycleText);
        window.draw(statusText);

        window.display();
    }

    return 0;
}
