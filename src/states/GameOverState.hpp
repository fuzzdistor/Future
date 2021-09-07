#ifndef GAMEOVERSTATE_HPP
#define GAMEOVERSTATE_HPP

#include "states/State.hpp"
#include "gui/Container.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>

namespace sf
{
    class Event;
    class Time;
}

class GameOverState : public State
{
public:
	GameOverState(StateStack& stack, Context context);

public:
	virtual void    draw() override;
	virtual bool    update(sf::Time dt) override;
    virtual bool    handleEvent(const sf::Event& event) override;

private:
	sf::Text            mGameOverText;
	sf::Time            mElapsedTime;
    sf::RectangleShape  mDarkBackground;
};

#endif // GAMEOVERSTATE_HPP