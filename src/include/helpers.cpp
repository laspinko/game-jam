#include "helpers.h"
#include <iostream>
template <>
bool isInsideRect<int, float>(sf::Vector2<int> point, sf::Rect<float> rect)
{
    return point.x >= rect.position.x && point.x <= rect.position.x + rect.size.x &&
           point.y >= rect.position.y && point.y <= rect.position.y + rect.size.y;
}

template <>
sf::Vector2<float> operator/ <float>(sf::Vector2<float> a, sf::Vector2<float> b)
{
    return {a.x / b.x, a.y / b.y};
}

TargetedValue::TargetedValue(float initial)
{
    target = value = initial;
    speed = 1;
    this->callback_opt = std::nullopt;
}

void TargetedValue::update()
{
    value += std::clamp(target - value, -speed, speed);
    if (std::abs(target - value) < 1e-6)
    {
        value = target;
        if (auto callback = callback_opt)
        {
            (*callback)();
            this->callback_opt = std::nullopt;
        };
    }
}

void TargetedValue::setTarget(float target)
{
    this->target = target;
    this->callback_opt = std::nullopt;
}

void TargetedValue::setSpeed(float speed)
{
    this->speed = speed;
}

void TargetedValue::setTimer(float time)
{
    speed = std::abs(target - value) / time;
}

float TargetedValue::getValue()
{
    return value;
}

float TargetedValue::getTarget()
{
    return target;
}

void TargetedValue::setCallback(callback_type callback)
{
    this->callback_opt = std::optional<callback_type>(callback);
}

bool isOpaque(sf::Vector2u pos, sf::Image &image)
{
    return (pos.x > 0 && pos.y > 0 && pos.x < image.getSize().x && pos.y < image.getSize().y) && image.getPixel(pos).a > 128;
}