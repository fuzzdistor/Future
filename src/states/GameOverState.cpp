#include "states/GameOverState.hpp"
#include "states/State.hpp"
#include "Future/Utils.hpp"
#include "Future/Player.hpp"
#include "Future/ResourceHolder.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


GameOverState::GameOverState(StateStack& stack, Context context)
: State(stack, context)
, mGameOverText()
, mElapsedTime(sf::Time::Zero)
, mDarkBackground()
{
    sf::Font& font = context.fonts->get(Fonts::ID::Main);
    sf::Vector2f windowSize(context.window->getSize());

    mGameOverText.setFont(font);
    if (context.player->getMissionStatus() == Player::MissionStatus::MissionFailure)
        mGameOverText.setString("Mission failed!");    
    else
        mGameOverText.setString("Mission successful!");

    mGameOverText.setCharacterSize(70);
    util::centerOrigin(mGameOverText);
    mGameOverText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);

    mDarkBackground.setFillColor(sf::Color(0, 0, 0, 150));
}

void GameOverState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    mDarkBackground.setSize(window.getView().getSize());

    window.draw(mDarkBackground);
    window.draw(mGameOverText);
}

bool GameOverState::update(sf::Time dt)
{
    // Show state for 3 seconds, after return to menu
    mElapsedTime += dt;
    if (mElapsedTime > sf::seconds(3))
    {
        requestStateClear();
        requestStackPush(States::ID::Game);
        requestStackPush(States::ID::Menu);
    }
    return false;
}

bool GameOverState::handleEvent(const sf::Event&)
{
    return false;
}
