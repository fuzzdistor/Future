#ifndef TITLESTATE_HPP
#define TITLESTATE_HPP

#include "states/State.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class TitleState : public State
{
public:
	TitleState(StateStack& stack, Context context);

public:
	virtual void 	draw() override;
	virtual bool 	update(sf::Time dt) override;
	virtual bool 	handleEvent(const sf::Event& event) override;

private:
	sf::Sprite 		mBackgroundSprite;
	sf::Text 		mText;

	bool 			mShowText;
	sf::Time 		mTextEffectTime;
};

#endif // TITLESTATE_HPP
