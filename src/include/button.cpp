#include "object.h"
#include "helpers.h"
#include <iostream>
Button::Button(std::function<void()> callback, sf::Texture tex, std::optional<sf::IntRect> rect)
{
    this->callback = callback;
    this->tex = tex;
    this->rect = rect.value_or(sf::IntRect({0, 0}, sf::Vector2i(tex.getSize())));
    this->img = tex.copyToImage();
    state = NORMAL;
}
void Button::update()
{
}
void Button::draw(sf::RenderWindow &window)
{
    sf::Sprite sprite(tex, rect);
    switch (state)
    {
    case HOVER:
        sprite.setColor(sf::Color(0xFFFBBDFF));
        break;
    case PRESSED:
        sprite.setColor(sf::Color(0xE2FFBDFF));
        break;
    default:
        break;
    }
    window.draw(sprite);
}
void Button::handleEvent(sf::Event *event)
{
    if (const auto mouse_button_pressed = event->getIf<sf::Event::MouseButtonPressed>())
    {
        if (mouse_button_pressed->button == sf::Mouse::Button::Left &&
            isOpaque(sf::Vector2u(mouse_button_pressed->position - rect.position), img))
        {
            state = PRESSED;
        }
    }
    else if (const auto mouse_button_released = event->getIf<sf::Event::MouseButtonReleased>())
    {
        if (mouse_button_released->button == sf::Mouse::Button::Left &&
            isOpaque(sf::Vector2u(mouse_button_released->position - rect.position), img) &&
            state == PRESSED)
        {
            callback();
        }
        state = NORMAL;
    }
    else if (const auto mouse_moved = event->getIf<sf::Event::MouseMoved>())
    {
        if (isOpaque(sf::Vector2u(mouse_moved->position - rect.position), img))
        {
            if (state == NORMAL)
                state = HOVER;
        }
        else
        {
            if (state == HOVER)
                state = NORMAL;
        }
    }
}
Button::~Button()
{
}