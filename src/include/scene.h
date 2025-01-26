#ifndef SCENE
#define SCENE
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "object.h"

class Scene
{

public:
    std::function<void(int)> callback;
    sf::RenderWindow *window;
    sf::Vector2i pointer;
    Scene(std::function<void(int)> callback);
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
    virtual void handleEvent(sf::Event *event) = 0;
    virtual void releaseFocus() = 0;
    virtual void gainFocus() = 0;
    virtual void setCallbacks() = 0;
    virtual ~Scene() = 0;
    virtual void setEnding(bool good_ending) = 0;
};

class OpeningScene : public Scene
{
    sf::Texture texBackground;
    sf::Music musBackground;
    Phone phone;
    std::vector<Button> buttons;

public:
    OpeningScene(sf::RenderWindow *window, std::function<void(int)> callback);
    void update();
    void draw(sf::RenderWindow &window);
    void handleEvent(sf::Event *event);
    void releaseFocus();
    void gainFocus();
    void setCallbacks();
    void setEnding(bool good_ending);
    ~OpeningScene();
};

class DressingScene : public Scene
{
    std::map<std::string, sf::Texture> textures;
    sf::Music musBackground;
    Phone phone;
    std::vector<ClothesSelector> clothes;
    std::vector<Button> buttons;

public:
    DressingScene(sf::RenderWindow *window, std::function<void(int)> callback);
    void update();
    void draw(sf::RenderWindow &window);
    void handleEvent(sf::Event *event);
    void releaseFocus();
    void gainFocus();
    void setCallbacks();
    void setEnding(bool good_ending);
    ~DressingScene();
};
class EndingScene : public Scene
{

    sf::Texture texBackground;
    sf::Music musBackground;

public:
    EndingScene(sf::RenderWindow *window, std::function<void(int)> callback);
    void update();
    void draw(sf::RenderWindow &window);
    void handleEvent(sf::Event *event);
    void releaseFocus();
    void gainFocus();
    void setCallbacks();
    void setEnding(bool good_ending);
    ~EndingScene();
};

#endif