#include "Future/Entity.hpp"

#include <cassert>


Entity::Entity()
    : mVelocity()
    , mDestroyFlag(false)
{
}

void Entity::setVelocity(sf::Vector2f velocity)
{
    mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
    mVelocity = { vx, vy };
}

sf::Vector2f Entity::getVelocity() const
{
    return mVelocity;
}

constexpr void Entity::destroy()
{
    mDestroyFlag = true;
}

void Entity::accelerate(sf::Vector2f velocity)
{
    mVelocity += velocity;
}

void Entity::accelerate(float vx, float vy)
{
    mVelocity += { vx, vy };
}

bool Entity::isDestroyed() const
{
    return mDestroyFlag;
}

void Entity::updateCurrent(sf::Time dt, CommandQueue&)
{
    move(mVelocity * dt.asSeconds());
}


