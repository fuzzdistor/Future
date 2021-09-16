#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Future/SceneNode.hpp"

namespace sf 
{
    class Time;
}

class CommandQueue;

class Entity : public SceneNode
{
public:
    Entity();

public:
    void            setVelocity(sf::Vector2f velocity);
    void            setVelocity(float vx, float vy);
    void            accelerate(sf::Vector2f velocity); 
    void            accelerate(float vx, float vy);
    sf::Vector2f    getVelocity() const;

    constexpr void  destroy();
    virtual bool    isDestroyed() const override;

protected:
    virtual void     updateCurrent(sf::Time dt, CommandQueue& commands) override;

private:
    sf::Vector2f    mVelocity;
    bool             mDestroyFlag;
};

#endif // ENTITY_HPP
