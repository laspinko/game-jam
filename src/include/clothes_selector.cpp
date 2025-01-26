#include "object.h"
#include <iostream>
ClothesSelector::ClothesSelector(ClothesTypes type)
{
    this->type = type;
    std::string item_name;
    int num_options;
    switch (type)
    {
    case SHIRT:
        item_name = "Shirt";
        num_options = 4;
        break;
    case SHOES:
        item_name = "Shoes";
        num_options = 3;
        break;
    case PANTS:
        item_name = "Pants";
        num_options = 3;
        break;

    default:
        break;
    }
    for (int i = 0; i < num_options; i++)
    {
        tex_options.push_back(sf::Texture("../../assets/img/Scene2_UI_" + item_name + std::to_string(i + 1) + ".png"));
    }
    option = 0;
}
void ClothesSelector::update()
{
    for (auto &button : buttons)
    {
        button.update();
    }
}
void ClothesSelector::draw(sf::RenderWindow &window)
{
    sf::Sprite sprite(tex_options[option]);
    window.draw(sprite);
}
void ClothesSelector::drawButtons(sf::RenderWindow &window)
{
    for (auto &button : buttons)
    {
        button.draw(window);
    }
}
void ClothesSelector::handleEvent(sf::Event *event)
{

    for (auto &button : buttons)
    {
        button.handleEvent(event);
    }
}
void ClothesSelector::setCallbacks()
{
    std::string item_name;
    switch (type)
    {
    case SHIRT:
        item_name = "Shirt";
        break;
    case SHOES:
        item_name = "Shoes";
        break;
    case PANTS:
        item_name = "Pants";
        break;

    default:
        break;
    }
    buttons.push_back(Button([this]() -> void
                             { this->option = (this->option + 1) % this->tex_options.size(); },
                             sf::Texture("../../assets/img/UI_Wardrobe_" + item_name + "Next.png")));
    buttons.push_back(Button([this]() -> void
                             { this->option = (this->option - 1 + this->tex_options.size()) % this->tex_options.size(); },
                             sf::Texture("../../assets/img/UI_Wardrobe_" + item_name + "Prev.png")));
}
ClothesSelector::~ClothesSelector()
{
}