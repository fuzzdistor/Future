#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include "Future/Category.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include <vector>
#include <set>
#include <memory>
#include <utility>

struct Command;
class CommandQueue;

class SceneNode : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;
	typedef std::pair<SceneNode*, SceneNode*> Pair;

public:
	explicit SceneNode(Category::Type category = Category::Type::None);

public:
	void                    attachChild(Ptr child);
	Ptr                     detachChild(const SceneNode& node);

	void                    update(sf::Time dt, CommandQueue& commands);

	sf::Vector2f            getWorldPosition() const;
	sf::Transform           getWorldTransform() const;

	void                    onCommand(const Command& command, sf::Time time);
	virtual Category::Type  getCategory() const;

	void                    checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs);
	void                    checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs);
	void                    removeMarked();
	virtual sf::FloatRect   getBoundingRect() const;
	virtual bool            isMarkedForRemoval() const;
	virtual bool            isDestroyed() const;

	void 					toggleDebugFlag();

private:
	virtual void            updateCurrent(sf::Time dt, CommandQueue& commands);
	void                    updateChildren(sf::Time dt, CommandQueue& commands);

	virtual void            draw(sf::RenderTarget& target, sf::RenderStates states) const final override;
	virtual void            drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void                    drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
	void                    drawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual sf::Color		getBoundingRectColor() const;

private:
	std::vector<Ptr>        mChildren;
	SceneNode*              mParent;
	Category::Type          mDefaultCategory;
	bool 					mDebugFlag;
};

bool	collision(const SceneNode& lhs, const SceneNode& rhs);
float	distance(const SceneNode& lhs, const SceneNode& rhs);

#endif // SCENENODE_HPP