#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "states/State.hpp"
#include "gui/Container.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

namespace sf
{
    class Event;
    class Time;
}

class MenuState : public State
{
public:
    MenuState(StateStack& states, Context context);

public:
    virtual void    draw() override;
    virtual bool    update(sf::Time dt) override;
    virtual bool    handleEvent(const sf::Event& event) override;

private:
    sf::Sprite      mBackgroundSprite;
    GUI::Container  mGUIContainer;
};

#endif // MENUSTATE_HPP