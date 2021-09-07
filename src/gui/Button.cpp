#include "gui/Button.hpp"
#include "Future/Utils.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

GUI::Button::Button(const FontHolder& fonts, const TextureHolder& textures)
	: mCallback()
	, mNormalTexture(textures.get(Textures::ID::GUIButtonNormal))
	, mSelectedTexture(textures.get(Textures::ID::GUIButtonSelected))
	, mPressedTexture(textures.get(Textures::ID::GUIButtonPressed))
	, mSprite()
	, mText("", fonts.get(Fonts::ID::Main))
	, mIsToggle(false)
{
	mSprite.setTexture(mNormalTexture);
	//mSprite.setTextureRect(sf::IntRect(0, 0, 50, 50));

	sf::FloatRect bounds = mSprite.getLocalBounds();
	mText.setPosition(bounds.width / 2.f, bounds.height / 2.f);
}

void GUI::Button::setCallback(Callback callback)
{
	mCallback = std::move(callback);
}

void GUI::Button::setText(const std::string& text)
{
	mText.setString(text);
	util::centerOrigin(mText);
}

void GUI::Button::setToggle(bool flag)
{
	mIsToggle = flag;
}

bool GUI::Button::isSelectable() const
{
	return true;
}

void GUI::Button::select()
{
	Component::select();

	mSprite.setTexture(mSelectedTexture);
}

void GUI::Button::deselect()
{
	Component::deselect();

	mSprite.setTexture(mNormalTexture);
}

void GUI::Button::activate()
{
	Component::activate();

	if(mIsToggle)
		mSprite.setTexture(mPressedTexture);

	if(mCallback)
		mCallback();

	if(!mIsToggle)
		deactivate();
}

void GUI::Button::deactivate()
{
	Component::deactivate();

	if (mIsToggle)
	{
		// Reset texture to right one depending on if we are selecting it or not.
		if (isSelected())
			mSprite.setTexture(mSelectedTexture);
		else
			mSprite.setTexture(mNormalTexture);
	}	
}

void GUI::Button::handleEvent(const sf::Event& event)
{
}

void GUI::Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
	target.draw(mText, states);
}
