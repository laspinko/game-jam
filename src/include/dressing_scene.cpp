#include "scene.h"
#include <iostream>
DressingScene::DressingScene(sf::RenderWindow *window,
                             std::function<void(int)> callback) : Scene(callback),
                                                                  musBackground("../../assets/music/dressing_scene_bg_music.wav"),
                                                                  phone(window, false)
{
    textures["background"] = sf::Texture("../../assets/img/Scene2_UI_BGR.png");
    textures["glow"] = sf::Texture("../../assets/img/UI_Wardrobe_Glow.png");
    textures["lines"] = sf::Texture("../../assets/img/UI_Wardrobe_Lines.png");

    clothes.push_back(ClothesSelector(ClothesSelector::SHOES));
    clothes.push_back(ClothesSelector(ClothesSelector::PANTS));
    clothes.push_back(ClothesSelector(ClothesSelector::SHIRT));
    for (auto &cloth : clothes)
    {
        cloth.setCallbacks();
    }
    musBackground.setLooping(true);
    musBackground.setVolume(10);
    this->window = window;
    phone.setCallbacks();
}
void DressingScene::update()
{
    for (auto &cs : clothes)
    {
        cs.update();
    }
    for (auto &button : buttons)
    {
        button.update();
    }
    phone.update();
}
void DressingScene::draw(sf::RenderWindow &window)
{
    window.clear();

    window.draw(sf::Sprite(textures["background"]));

    for (auto &cs : clothes)
    {
        cs.draw(window);
    }

    window.draw(sf::Sprite(textures["glow"]));
    window.draw(sf::Sprite(textures["lines"]));

    for (auto &cs : clothes)
    {
        cs.drawButtons(window);
    }

    phone.draw(window);
    /*sf::RectangleShape pnt({100, 100});
    pnt.setPosition(sf::Vector2f(pointer));
    pnt.setFillColor(sf::Color::Black);
    window.draw(pnt);
    */
    for (auto &button : buttons)
    {
        button.draw(window);
    }

    window.display();
}
void DressingScene::handleEvent(sf::Event *event)
{
    if (const auto mouse_moved = event->getIf<sf::Event::MouseMoved>())
    {
        pointer = mouse_moved->position;
    }
    for (auto &cs : clothes)
    {
        cs.handleEvent(event);
    }
    for (auto &button : buttons)
    {
        button.handleEvent(event);
    }
    phone.handleEvent(event);
}
void DressingScene::releaseFocus()
{
    musBackground.pause();
}
void DressingScene::gainFocus()
{
    musBackground.play();
}
void DressingScene::setCallbacks()
{
    buttons.push_back(Button([this]() -> void
                             { 
                                bool passed = this->clothes[0].option == 1 && this->clothes[1].option == 1 && this->clothes[1].option == 1;
                             this->callback(passed); }, sf::Texture("../../assets/img/UI_Ready_Button.png")));
}
DressingScene::~DressingScene()
{
}
void DressingScene::setEnding(bool good_ending)
{
}