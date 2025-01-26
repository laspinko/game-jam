#ifndef HELPERS
#define HELPERS
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <functional>

template <typename T, typename U>
bool isInsideRect(sf::Vector2<T> point, sf::Rect<U> rect);

template <typename T>
sf::Vector2<T> operator/(sf::Vector2<T>, sf::Vector2<T>);

typedef std::function<void()> callback_type;
class TargetedValue
{
    float value, target, speed;
    std::optional<callback_type> callback_opt;

public:
    TargetedValue(float initial);
    void update();
    void setValue(float value);

    // Resets callback
    void setTarget(float target);
    void setSpeed(float speed);
    void setTimer(float time);
    float getValue();
    float getTarget();
    void setCallback(callback_type callback);
};

bool isOpaque(sf::Vector2u, sf::Image &);

#endif