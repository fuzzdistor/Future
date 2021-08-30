#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "states/State.hpp"
#include "Future/Room.hpp"
#include "Future/Player.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

namespace sf
{
    class Event;
    class Time;
}

class GameState : public State
{
public:
	GameState(StateStack& stack, Context context);

public:
	virtual void		draw() override;
	virtual bool		update(sf::Time dt) override;
	virtual bool		handleEvent(const sf::Event& event) override;

private:
	Room        mRoom;
	Player&     mPlayer;
};

#endif // GAMESTATE_HPP