#ifndef ACTOR_HPP
#define ACTOR_HPP

#include "Future/Entity.hpp"
#include "Future/Command.hpp"
#include "Future/ResourceIdentifiers.hpp"
#include "Future/SpriteNode.hpp"
#include "Future/TextNode.hpp"
#include "CommandQueue.hpp"

#include <SFML/Graphics/Sprite.hpp>


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
    virtual Category::Type      getCategory() const override;
    virtual sf::FloatRect       getBoundingRect() const override;
    virtual bool                isMarkedForRemoval() const override;
    constexpr bool                 isAllied() const;
    float                       getMaxSpeed() const;

private:
    virtual void                drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void                 updateCurrent(sf::Time dt, CommandQueue& commands) override;
    void                        updateMovementPattern(sf::Time dt);
    virtual sf::Color           getBoundingRectColor() const override;

    void                        updateTexts();

private:
    Type                        mType;
    SpriteNode*                 mSprite;
    bool                         mIsMarkedForRemoval;

    float                        mTravelledDistance;
    std::size_t                    mDirectionsIndex;
    TextNode*                    mTextDisplay;
    TextNode*                    mTextDisplay2;
};

#endif // ACTOR_HPP
