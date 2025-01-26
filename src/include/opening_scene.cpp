#include "scene.h"

OpeningScene::OpeningScene(sf::RenderWindow *window,
                           std::function<void(int)> callback) : Scene(callback),
                                                                texBackground("../../assets/img/Scene1_UI_BGR.png"),
                                                                musBackground("../../assets/music/opening_scene_bg_music.wav"),
                                                                phone(window, true)

{
    musBackground.setLooping(true);

    phone.setCallbacks();
    this->window = window;
}

void OpeningScene::update()
{
    phone.update();
    for (auto &button : buttons)
    {
        button.update();
    }
}
void OpeningScene::draw(sf::RenderWindow &window)
{
    window.clear();
    sf::Sprite sprBackground(texBackground);

    window.draw(sprBackground);

    phone.draw(window);

    for (auto &button : buttons)
    {
        button.draw(window);
    }

    window.display();
}

void OpeningScene::handleEvent(sf::Event *event)
{
    phone.handleEvent(event);
    for (auto &button : buttons)
    {
        button.handleEvent(event);
    }
}

void OpeningScene::releaseFocus()
{
    musBackground.pause();
}

void OpeningScene::gainFocus()
{
    musBackground.play();
}
void OpeningScene::setCallbacks()
{
    buttons.push_back(Button([this]() -> void
                             { this->callback(0); }, sf::Texture("../../assets/img/UI_GetDressed_Button.png")));
}

OpeningScene::~OpeningScene()
{
}

Scene::Scene(std::function<void(int)> callback)
{
    this->callback = callback;
}
Scene::~Scene()
{
}
void OpeningScene::setEnding(bool good_ending)
{
}