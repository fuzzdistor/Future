#ifndef SETTINGSSTATE_HPP
#define SETTINGSSTATE_HPP

#include "states/State.hpp"
#include "Future/Player.hpp"
#include "gui/Container.hpp"
#include "gui/Button.hpp"
#include "gui/Label.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <array>

namespace sf
{
    class Event;
}

class SettingsState : public State
{
public:
    SettingsState(StateStack& stack, Context context);

public:
    virtual void     draw() override;
    virtual bool     update(sf::Time dt) override;
    virtual bool     handleEvent(const sf::Event& event) override;

private:
    void             updateLabels();
    void             addButtonLabel(Player::ActionID action, float y, const std::string& text, Context context);

private:
    sf::Sprite         mBackgroundSprite;
    GUI::Container     mGUIContainer;
    std::map<Player::ActionID, GUI::Button::Ptr>    mBindingButtons;
    std::map<sf::Keyboard::Key, GUI::Label::Ptr>    mBindingLabels;
};

#endif // SETTINGSSTATE_HPP
