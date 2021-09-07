#ifndef PAUSESTATE_HPP
#define PAUSESTATE_HPP

#include "states/State.hpp"
#include "gui/Container.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

namespace sf
{
    class Event;
    class Time;
}

class PauseState : public State
{
public:
    PauseState(StateStack& states, Context context);

public:
    virtual void    draw() override;
    virtual bool    update(sf::Time dt) override;
    virtual bool    handleEvent(const sf::Event& event) override;

private:
    sf::Sprite          mBackgroundSprite;
    sf::Text            mPausedText;
    GUI::Container      mGUIContainer;
};

#endif // PAUSESTATE_HPP
