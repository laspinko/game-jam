#include "scene.h"

EndingScene::EndingScene(sf::RenderWindow *window,
                         std::function<void(int)> callback) : Scene(callback)
{
}
void EndingScene::setEnding(bool good_ending)
{
    texBackground = sf::Texture(good_ending ? "../../assets/img/Good_End.png" : "../../assets/img/Bad_End.png");
    musBackground = sf::Music(good_ending ? "../../assets/music/good_ending.wav" : "../../assets/music/bad_ending.wav");

    musBackground.setLooping(good_ending);
}
void EndingScene::update() {}
void EndingScene::draw(sf::RenderWindow &window)
{
    window.clear();

    window.draw(sf::Sprite(texBackground));

    window.display();
}
void EndingScene::handleEvent(sf::Event *event) {}
void EndingScene::releaseFocus()
{
    musBackground.pause();
}
void EndingScene::gainFocus()
{
    musBackground.play();
}
void EndingScene::setCallbacks() {}
EndingScene::~EndingScene() {}