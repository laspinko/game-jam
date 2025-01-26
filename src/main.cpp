#include <SFML/Graphics.hpp>
#include <scene.h>
#include <cpplocate/cpplocate.h>
#include <filesystem>
#include <iostream>

int main()
{

    // Overriding this so that we don't have to drill this value down
    const std::string path = cpplocate::getModulePath();
    std::filesystem::current_path(path);

    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "SFML works!");
    window.setPosition({500, 200});
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    std::vector<Scene *> scenes;
    Scene *currentScene;
    scenes.push_back(new OpeningScene(&window, [&currentScene, &scenes](int _) -> void
                                      {
        currentScene->releaseFocus();
        currentScene = scenes[1];
        currentScene->gainFocus(); }));
    scenes.push_back(new DressingScene(&window, [&currentScene, &scenes](int score) -> void
                                       {
        currentScene->releaseFocus();
        currentScene = scenes[2];
        currentScene->setEnding(score);
        currentScene->gainFocus(); }));
    scenes.push_back(new EndingScene(&window, [&currentScene, &scenes](int score) -> void {}));
    for (auto &scene : scenes)
    {
        scene->setCallbacks();
    }
    currentScene = scenes[0];
    currentScene->gainFocus();

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
                return 0;
            }
            sf::Event ev = event.value();
            currentScene->handleEvent(&ev);
        }

        currentScene->update();
        currentScene->draw(window);
        /*window.clear();
        window.draw(shape);
        window.display();*/
    }
}