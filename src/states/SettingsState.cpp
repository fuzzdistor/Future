#include "states/SettingsState.hpp"
#include "Future/Utils.hpp"
#include "Future/ResourceHolder.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


SettingsState::SettingsState(StateStack& stack, Context context)
: State(stack, context)
, mGUIContainer()
{
	mBackgroundSprite.setTexture(context.textures->get(Textures::ID::TitleScreen));
	
	// Build key binding buttons and labels
	addButtonLabel(Player::ActionID::MoveLeft,		300.f, "Move Left", context);
	addButtonLabel(Player::ActionID::MoveRight,		350.f, "Move Right", context);
	addButtonLabel(Player::ActionID::MoveUp,			400.f, "Move Up", context);
	addButtonLabel(Player::ActionID::MoveDown,		450.f, "Move Down", context);
	addButtonLabel(Player::ActionID::Fire,			500.f, "Fire", context);
	addButtonLabel(Player::ActionID::LaunchMissile,	550.f, "Missile", context);
	addButtonLabel(Player::ActionID::ToggleDebugMode,	600.f, "Toggle Debug", context);
 
	updateLabels();

	auto backButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	backButton->setPosition(80.f, 700.f);
	backButton->setText("Back");
	backButton->setCallback(std::bind(&SettingsState::requestStackPop, this));

	mGUIContainer.pack(backButton);
}

void SettingsState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	sf::RectangleShape rect;
	rect.setSize(window.getView().getSize());
	rect.setFillColor(sf::Color(0U,0U,0U,200U));
	window.draw(rect);

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
}

bool SettingsState::update(sf::Time)
{
	return true;
}

bool SettingsState::handleEvent(const sf::Event& event)
{
	bool isKeyBinding = false;
	
	// Iterate through all key binding buttons to see if they are being pressed, waiting for the user to enter a key
	for (std::size_t action = 0; action < (int)Player::ActionID::ActionCount; ++action)
	{
		if (mBindingButtons[action]->isActive())
		{
			isKeyBinding = true;
			if (event.type == sf::Event::KeyReleased)
			{
				getContext().player->assignKey(static_cast<Player::ActionID>(action), event.key.code);
				mBindingButtons[action]->deactivate();
			}
			break;
		}
	}

	// If pressed button changed key bindings, update labels; otherwise consider other buttons in container
	if (isKeyBinding)
		updateLabels();
	else
		mGUIContainer.handleEvent(event);

	return false;
}

void SettingsState::updateLabels()
{
	Player& player = *getContext().player;

	for (std::size_t i = 0; i < (int)Player::ActionID::ActionCount; ++i)
	{
		sf::Keyboard::Key key = player.getAssignedKey(static_cast<Player::ActionID>(i));
		mBindingLabels[i]->setText(util::toString(key));
	}
}

void SettingsState::addButtonLabel(Player::ActionID action, float y, const std::string& text, Context context)
{
	//TODO v v v v v FIX THIS MESS v v v v v
	int actionIndex = (int)action;
	mBindingButtons[actionIndex] = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	mBindingButtons[actionIndex]->setPosition(80.f, y);
	mBindingButtons[actionIndex]->setText(text);
	mBindingButtons[actionIndex]->setToggle(true);

	mBindingLabels[actionIndex] = std::make_shared<GUI::Label>("", *context.fonts);
	mBindingLabels[actionIndex]->setPosition(300.f, y + 15.f);

	mGUIContainer.pack(mBindingButtons[actionIndex]);
	mGUIContainer.pack(mBindingLabels[actionIndex]);
}
