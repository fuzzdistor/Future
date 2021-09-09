
#include "Future/SceneNode.hpp"
#include "Future/Command.hpp"
#include "Future/Utils.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>

#include <cassert>


SceneNode::SceneNode(Category::Type category)
	: mParent(std::nullopt)
	, mChildren()
	, mDefaultCategory(category)
	, mDebugFlag(false)
{
}

/** \brief Method for attaching a node as a child.
 *  \param child unique pointer to insert to the node graph. 
 *      Being a unique_pointer, you have to transfer ownership with 
 *      std::move in order to be passed by value.
 */
void SceneNode::attachChild(SceneNode::Ptr child)
{
	// Assign this instance as parent and push into children vector
	child->mParent = this;
	mChildren.push_back(std::move(child));
}


/** @brief Method for removing a node from the children vector.
 *  @param node reference to a SceneNode to remove from the children 
 *      vector.
 *  @returns a unique_pointer<SceneNode> to the SceneNode that 
 *      was removed.
 *  @exception assertion if node is not found in the children vector.
 */
SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
	// iterator pointing to where node is in children vector
	auto found = std::find_if(mChildren.begin(), mChildren.end(), 
		[&] (Ptr& p) -> bool { return p.get() == &node; });
	
	assert(found != mChildren.end()); // err: the node is not in the vector

	// Receptor for the node leaving mChildren
	Ptr result = std::move(*found);
	mChildren.erase(found);

	// blank the node's parent reference
	result->mParent = nullptr;
	return result;
}

void SceneNode::update(sf::Time dt, CommandQueue& commands)
{
	updateCurrent(dt, commands);
	updateChildren(dt, commands);
}

void SceneNode::updateCurrent(sf::Time, CommandQueue&)
{
}

void SceneNode::updateChildren(sf::Time dt, CommandQueue& commands)
{
	for (auto& child: mChildren)
		child->update(dt, commands);
}

void SceneNode::draw(sf::RenderTarget& target
	, sf::RenderStates states) const
{
	// apply local transform and draw self and children
	states.transform *= getTransform();
	drawCurrent(target, states);
	drawChildren(target, states);

	if (mDebugFlag)
		drawBoundingRect(target, states);
}

// Does nothing by default
void SceneNode::drawCurrent(sf::RenderTarget&, sf::RenderStates) const
{
	// do nothing
}

// Invokes draw() on children nodes recursively
void SceneNode::drawChildren(sf::RenderTarget& target
	, sf::RenderStates states) const
{
	// call draw on every child recursively
	for (const Ptr& child: mChildren)
		child->draw(target, states);    
}

// Draws the bounding rectangle associated with its sprite and gives it an outline determined by getBoundingRectColor()
void SceneNode::drawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::FloatRect rect = getBoundingRect();
	
	// create the bounding shape and give it a green outline
	sf::RectangleShape shape;
	shape.setPosition(rect.left, rect.top);
	shape.setSize(sf::Vector2f(rect.width, rect.height));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(getBoundingRectColor());
	shape.setOutlineThickness(1.f);

	target.draw(shape, states);
}

void SceneNode::toggleDebugFlag()
{
	mDebugFlag = !mDebugFlag;
}

sf::Color SceneNode::getBoundingRectColor() const
{
	return sf::Color::Green;
}

sf::FloatRect SceneNode::getBoundingRect() const
{
	return sf::FloatRect(); // return empty FloatRect by default
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;

	for (auto node = this; node != nullptr; node = node->mParent.value_or(nullptr))
		transform *= node->getTransform();

	return transform;
}

void SceneNode::onCommand(const Command& command, sf::Time dt)
{
	// Command current node, if category matches
	Category::Type thisCategory = getCategory();
	if (static_cast<int>(command.category) & static_cast<int>(thisCategory))
		command.action(*this, dt);

	// Command children
	for(auto& child: mChildren)
		child->onCommand(command, dt);
}

Category::Type SceneNode::getCategory() const
{
	return mDefaultCategory;
}

void SceneNode::checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs)
{
	checkNodeCollision(sceneGraph, collisionPairs);

	for(auto& child: sceneGraph.mChildren)
		checkSceneCollision(*child, collisionPairs);
}

void SceneNode::checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs)
{
	if (this != &node && collision(*this, node) && !isDestroyed() && !node.isDestroyed())
		collisionPairs.insert(std::minmax(this, &node));

	for(auto& child: mChildren)
		child->checkNodeCollision(node, collisionPairs);
}

void SceneNode::removeMarked()
{
	// Remove all children which request so
	auto wreckfieldBegin = std::remove_if(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::isMarkedForRemoval));
	mChildren.erase(wreckfieldBegin, mChildren.end());

	// Call function recursively for all remaining children
	for(auto& child: mChildren)
		 child->removeMarked();
}

bool SceneNode::isMarkedForRemoval() const
{
	// By default, remove node if entity is destroyed
	return isDestroyed();
}

bool SceneNode::isDestroyed() const
{
	// By default, scene node needn't be removed
	return false;
}

bool collision(const SceneNode& lhs, const SceneNode& rhs)
{
	return lhs.getBoundingRect().intersects(rhs.getBoundingRect());
}

float distance(const SceneNode& lhs, const SceneNode& rhs)
{
	return util::length(lhs.getWorldPosition() - rhs.getWorldPosition());
}
