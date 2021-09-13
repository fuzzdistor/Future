
#include "Future/Actor.hpp"
#include "Future/Utils.hpp"
#include "Future/ResourceHolder.hpp"
#include "Future/DataTables.hpp"
#include "Future/CommandQueue.hpp"
#include "Future/json.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Color.hpp>

#include <map>
#include <cassert>
#include <utility>
#include <memory>


namespace
{
	const std::map<Actor::Type, ActorData> Table = initActorData();

}

Actor::Actor(Type type, const TextureHolder& textures, const FontHolder& fonts)
	: mType(type)
	, mSprite()
	, mIsMarkedForRemoval(false)
	, mTravelledDistance(0.f)
	, mDirectionsIndex(0)
	, mTextDisplay(nullptr)
	, mTextDisplay2(nullptr)
{
    auto sprite = std::make_unique<SpriteNode>(textures.get(getDataTableOf(type, Table).texture));
    util::centerOrigin(*sprite);
    mSprite = sprite.get();
    attachChild(std::move(sprite));

	std::unique_ptr<TextNode> healthDisplay(new TextNode(fonts, ""));
	mTextDisplay = healthDisplay.get();
	mTextDisplay->setOrigin(0.f, -50.f);
	attachChild(std::move(healthDisplay));

	if (getCategory() == Category::Type::PlayerActor)
	{
		std::unique_ptr<TextNode> missileDisplay(new TextNode(fonts, ""));
		missileDisplay->setPosition(0, 70);
		mTextDisplay2 = missileDisplay.get();
		attachChild(std::move(missileDisplay));
	}

	updateTexts();
}

// Sort of converter from Actor::Type to Category::Type according to game logic
Category::Type Actor::getCategory() const
{
	if (isAllied())
		return Category::Type::PlayerActor;

	if (mType == Actor::Type::Door)
		return Category::Type::Door;
		
	return Category::Type::EnemyActor;
}

// 
sf::FloatRect Actor::getBoundingRect() const
{
	return getWorldTransform().transformRect(mSprite->getGlobalBounds());
}

// getter for member isMarkedForRemoval
bool Actor::isMarkedForRemoval() const
{
	return mIsMarkedForRemoval;
}

// \returns true if Actor type is Nanotech 
constexpr bool Actor::isAllied() const
{
	return mType == Type::Nanotech;
}

// \returns speed member as defined in DataTables
float Actor::getMaxSpeed() const
{
	return getDataTableOf(mType, Table).speed;
}

// Draw instance on [target]
void Actor::drawCurrent(sf::RenderTarget&, sf::RenderStates) const
{
    // nothing to draw
}

// Updates the instance. Marks for removal if conditions are met, updates movement pattern, moves the instance and updates texts.
void Actor::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	if (isDestroyed())
	{
		mIsMarkedForRemoval = true;
		return;
	}

	updateMovementPattern(dt);
	Entity::updateCurrent(dt, commands);

	updateTexts();
}

// Calculates the vector for movement acording to it's data table's [directions] and then passes it to setVelocity.
// If [directions] is empty it does nothing.
// \param dt Elapsed time since last frame.
void Actor::updateMovementPattern(sf::Time dt)
{
	const std::vector<Direction>& directions = getDataTableOf(mType, Table).directions;

	if (!directions.empty())
	{
		//TODO maybe change algorithm this one is serviceable but i dont like it.
		if (mTravelledDistance > directions[mDirectionsIndex].distance)
		{
			mDirectionsIndex = (mDirectionsIndex + 1) % directions.size();
			mTravelledDistance = 0.f;
		}

		float radians = util::toRadian(directions[mDirectionsIndex].angle + 90.f);
		float vx = getMaxSpeed() * std::cos(radians);
		float vy = getMaxSpeed() * std::sin(radians);

		setVelocity(vx, vy);
		mTravelledDistance += getMaxSpeed() * dt.asSeconds();
	}
}

void Actor::updateTexts()
{
	mTextDisplay->setString("Test");
	mTextDisplay->setRotation(-getRotation());
	
	if(getCategory() == Category::Type::PlayerActor) 
		mTextDisplay2->setString("Player Character");
}

sf::Color Actor::getBoundingRectColor() const
{
	if (isAllied())
		return sf::Color::Cyan;
	return sf::Color::Red;
}
