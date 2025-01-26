#include "object.h"
#include "helpers.h"
#include <math.h>
#include <iostream>

Phone::Phone(sf::RenderWindow *window, bool isOpening) : phone_screen({742, 77}, {508, 906}),
                                                         thumb_angle(sf::degrees(20).asRadians()),
                                                         phone_rotation(45),
                                                         phone_translation_x(0),
                                                         phone_translation_y(0),
                                                         phone_scale(1),
                                                         hand_hinge({600, 1080}),
                                                         scroll_position(0)
{
    // #HARDCODED
    textures["frame"] = sf::Texture("../../assets/img/Scene1_UI_Hand.png");
    textures["frame_cropped"] = sf::Texture("../../assets/img/Scene1_UI_Hand_Cropped.png");
    textures["frame_locked"] = sf::Texture("../../assets/img/Scene1_UI_Hand_Locked.png");
    textures["frame_cropped_locked"] = sf::Texture("../../assets/img/Scene1_UI_Hand_Cropped_Locked.png");
    textures["thumb"] = sf::Texture("../../assets/img/Scene1_UI_Thumb.png");

    for (int i = 1; i <= 3; i++)
    {
        posts.push_back(sf::Texture("../../assets/img/UI_Post" + std::to_string(i) + ".png"));
    }

    scroll_position = 0;
    thumb_angle_max = sf::degrees(45).asRadians();
    thumb_angle_min = sf::degrees(0).asRadians();
    thumb_state = SCROLLING;
    thumb_angle.setSpeed(sf::degrees(1).asRadians());
    phone_state = LOCKED;
    this->window = window;
    this->isOpening = isOpening;
    if (!isOpening)
    {
        flipped = true;

        phone_rotation = TargetedValue(0);
        phone_translation_x = TargetedValue(-1900);
        phone_translation_y = TargetedValue(0);
        phone_scale = TargetedValue(0.65);
    }
    else
    {
        flipped = false;
    }
}
void Phone::update()
{
    thumb_angle.update();
    phone_rotation.update();
    phone_translation_x.update();
    phone_translation_y.update();
    phone_scale.update();
    scroll_position.update();
}

void Phone::draw(sf::RenderWindow &window)
{

    // SCREEN CONTENTS

    sf::View phone_screen_viewport(sf::FloatRect({0, scroll_position.getValue()}, phone_screen.size));
    auto last_view = window.getView();
    phone_screen_viewport.setViewport(sf::FloatRect(phone_screen.position / last_view.getSize(),
                                                    phone_screen.size / last_view.getSize()));
    window.setView(phone_screen_viewport);

    if (phone_state == LOCKED)
    {
    }
    else
    {
        sf::RectangleShape padding({1000, 10000});
        padding.setFillColor(sf::Color::White);
        padding.setPosition({0, -5000});
        window.draw(padding);

        float top = 0;
        for (auto &tex_post : posts)
        {
            sf::Sprite post(tex_post);
            post.setPosition({0, top});
            top += tex_post.getSize().y;
            window.draw(post);
        }
    }
    window.setView(last_view);

    // THUMB INTERACTIONS
    // #HARDCODED

    sf::Transform outer_transform;
    outer_transform.translate(hand_hinge);
    outer_transform.rotate(sf::degrees(phone_rotation.getValue()));
    outer_transform.scale(sf::Vector2f(phone_scale.getValue(), phone_scale.getValue()));
    if (flipped)
        outer_transform.scale({-1, 1});
    outer_transform.translate(-hand_hinge);
    outer_transform.translate({phone_translation_x.getValue(), phone_translation_y.getValue()});

    sf::Vector2f hinge_position(794, 969);

    if (phone_state == LOCKED)
    {
        sf::Sprite frame(thumb_angle.getValue() < sf::degrees(25).asRadians() ? textures["frame_cropped_locked"] : textures["frame_locked"]);
        window.draw(frame, outer_transform);
    }
    else
    {
        sf::Sprite frame(thumb_angle.getValue() < sf::degrees(25).asRadians() ? textures["frame_cropped"] : textures["frame"]);
        window.draw(frame, outer_transform);
    }

    sf::Sprite thumb(textures["thumb"]);
    sf::Transform hinge_transform;
    hinge_transform.translate(hinge_position);
    hinge_transform.rotate(sf::radians(thumb_angle.getValue()));
    hinge_transform.translate(-hinge_position);
    window.draw(thumb, outer_transform * hinge_transform);
}

void Phone::setCallbacks()
{
    if (isOpening)
    {
        phone_rotation.setTarget(0);
        phone_rotation.setCallback([this]() -> void
                                   { this->phone_state = UNLOCKED; });
        float duration = 50;
        phone_rotation.setTimer(duration);
    }
}
void Phone::handleEvent(sf::Event *event)
{

    if (phone_state == UNLOCKED)
    {

        if (const auto mouse_button_pressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mouse_button_pressed->button == sf::Mouse::Button::Left)
            {
                if (phone_screen.contains(window->mapPixelToCoords(mouse_button_pressed->position)))
                {
                    mouse_drag = std::optional<sf::Vector2i>(mouse_button_pressed->position);
                }
            }
        }
        else if (const auto mouse_button_released = event->getIf<sf::Event::MouseButtonReleased>())
        {
            if (mouse_button_released->button == sf::Mouse::Button::Left)
            {
                mouse_drag = std::nullopt;
                if (scroll_position.getValue() < 0)
                {
                    scroll_position.setTarget(0);
                    scroll_position.setSpeed(50);
                }
                float max_height = posts[0].getSize().y * posts.size() - phone_screen.size.y;
                if (scroll_position.getValue() > max_height)
                {
                    scroll_position.setTarget(max_height);
                    scroll_position.setSpeed(50);
                }
            }
        }
        else if (const auto *mouse_moved = event->getIf<sf::Event::MouseMoved>())
        {
            if (auto last_position = mouse_drag)
            {
                float difference = mouse_moved->position.y - last_position->y;
                scroll_position.setTarget(scroll_position.getTarget() - difference);
                scroll_position.setSpeed(1000);

                if (thumb_state == SCROLLING)
                {
                    const float thumb_length = 320.f;
                    float curr_thumb_y = -cos(thumb_angle.getValue()) * thumb_length;
                    float target_thumb_y = curr_thumb_y + difference;
                    float new_target = std::abs(target_thumb_y) >= thumb_length ? thumb_angle_min - 1 : std::abs(acos(-target_thumb_y / thumb_length));
                    if (new_target > thumb_angle_max)
                    {
                        thumb_state = RESET_UP;
                        thumb_angle.setTarget(thumb_angle_min);
                        thumb_angle.setSpeed(sf::degrees(3).asRadians());
                        thumb_angle.setCallback([this]() -> void
                                                { this->thumb_state = SCROLLING; });
                    }
                    else if (new_target < thumb_angle_min)
                    {
                        thumb_state = RESET_DOWN;
                        thumb_angle.setTarget(thumb_angle_max);
                        thumb_angle.setSpeed(sf::degrees(3).asRadians());
                        thumb_angle.setCallback([this]() -> void
                                                { this->thumb_state = SCROLLING; });
                    }
                    else
                    {
                        thumb_angle.setTarget(new_target);
                        thumb_angle.setSpeed(sf::degrees(1).asRadians());
                    }
                }

                mouse_drag = std::optional<sf::Vector2i>(mouse_moved->position);
            }
        }
    }
    if (!isOpening)
    {
        if (const auto mouse_button_pressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mouse_button_pressed->button == sf::Mouse::Button::Left)
            {
                sf::FloatRect open_hitbox({1400, 420}, {360, 610});
                if (phone_state == LOCKED &&
                    phone_scale.getValue() == phone_scale.getTarget() &&
                    open_hitbox.contains(window->mapPixelToCoords(mouse_button_pressed->position)))
                {
                    phone_translation_x.setTarget(-790.);
                    phone_scale.setTarget(1.);
                    float duration = 40;
                    phone_translation_x.setTimer(duration);
                    phone_scale.setTimer(duration);
                    phone_translation_x.setCallback([this]() -> void
                                                    { this->phone_state = UNLOCKED; });
                }
                else if (phone_state == UNLOCKED &&
                         !phone_screen.contains(window->mapPixelToCoords(mouse_button_pressed->position)))
                {
                    phone_translation_x.setTarget(-1900.);
                    phone_scale.setTarget(.65);
                    float duration = 40;
                    phone_translation_x.setTimer(duration);
                    phone_scale.setTimer(duration);
                    phone_state = LOCKED;
                }
            }
        }
    }
}

Phone::~Phone()
{
}

Object::~Object()
{
}
