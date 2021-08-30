#ifndef ACTOR_HPP
#define ACTOR_HPP

#include "Future/Entity.hpp"
#include "Future/Command.hpp"
#include "Future/ResourceIdentifiers.hpp"
#include "Future/TextNode.hpp"
#include "Future/json.hpp"
#include "CommandQueue.hpp"

#include <SFML/Graphics/Sprite.hpp>

using json = nlohmann::json;


class Actor : public Entity
{
public:
	enum class Type
	{
		Nanobot,
		Nanobot2,
		Nanotech,
		Door,
		Terminal
	};

public: 
	Actor(Type type, const TextureHolder& textures, const FontHolder& fonts);


public:
	virtual Category::Type  	getCategory() const;
	virtual sf::FloatRect   	getBoundingRect() const override;
	virtual bool            	isMarkedForRemoval() const override;
	bool                    	isAllied() const;
	float                   	getMaxSpeed() const;

	void 						from_json(const json& j, Actor& p);

private:
	virtual void				drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void 				updateCurrent(sf::Time dt, CommandQueue& commands) override;
	void						updateMovementPattern(sf::Time dt);
	virtual sf::Color			getBoundingRectColor() const override;

	void						updateTexts();

private:
	Type						mType;
	sf::Sprite					mSprite;
	bool 						mIsMarkedForRemoval;

	float						mTravelledDistance;
	std::size_t					mDirectionsIndex;
	TextNode*					mTextDisplay;
	TextNode*					mTextDisplay2;
};

#endif // ACTOR_HPP