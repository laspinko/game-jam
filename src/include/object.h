#ifndef OBJECT
#define OBJECT
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "helpers.h"
#include <map>
#include <functional>

class Object
{
protected:
    std::map<std::string, sf::Texture> textures;

public:
    sf::RenderWindow *window;
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
    virtual void handleEvent(sf::Event *event) = 0;
    virtual ~Object() = 0;
};

class Phone : public Object
{
    TargetedValue scroll_position;
    sf::Rect<float> phone_screen;
    std::optional<sf::Vector2i> mouse_drag;
    TargetedValue thumb_angle;
    float thumb_angle_min, thumb_angle_max;
    std::vector<sf::Texture> posts;
    bool isOpening;

    enum ThumbState
    {
        SCROLLING,
        RESET_DOWN,
        RESET_UP
    } thumb_state;
    enum PhoneState
    {
        LOCKED,
        UNLOCKED
    } phone_state;
    TargetedValue phone_rotation, phone_scale, phone_translation_x, phone_translation_y;
    bool flipped;
    sf::Vector2f hand_hinge;

public:
    Phone(sf::RenderWindow *window, bool isOpening);
    void update();
    void draw(sf::RenderWindow &window);
    void setCallbacks();
    virtual void handleEvent(sf::Event *event);
    ~Phone();
};

class Button : public Object
{
    std::function<void()> callback;
    sf::IntRect rect;
    sf::Texture tex;
    sf::Image img;
    enum State
    {
        NORMAL,
        HOVER,
        PRESSED
    } state;

public:
    Button(std::function<void()> callback, sf::Texture tex, std::optional<sf::IntRect> rect = std::nullopt);
    void update();
    void draw(sf::RenderWindow &window);
    void handleEvent(sf::Event *event);
    ~Button();
};

class ClothesSelector : public Object
{
    std::vector<sf::Texture> tex_options;
    std::vector<Button> buttons;

public:
    int option;

    // Order of drawing
    enum ClothesTypes
    {
        SHOES,
        PANTS,
        SHIRT
    } type;
    ClothesSelector(ClothesTypes type);
    void update();
    void draw(sf::RenderWindow &window);
    void drawButtons(sf::RenderWindow &window);
    void handleEvent(sf::Event *event);
    void setCallbacks();
    ~ClothesSelector();
};

#endif