#include "Future/Room.hpp"
#include "Future/TextNode.hpp"
#include "Future/Utils.hpp"
#include "Future/TriggerNode.hpp"
#include "Future/json.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Time.hpp>

#include <utility>
#include <algorithm>
#include <cmath>
#include <limits>
#include <fstream>

using json = nlohmann::json;


Room::Room(sf::RenderWindow& window, FontHolder& fonts)
	: mWindow(window)
	, mWorldView(window.getDefaultView())
	, mTextures() 
	, mFonts(fonts)
	, mSceneGraph()
	, mSceneLayers()
	, mCommandQueue()
	, mWorldBounds(0.f, 0.f, 2000, 2000.f)
	, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
	, mScrollSpeed(0.f)
	, mFinishLine(nullptr)
	, mPlayerCharacter(nullptr)
	, mArrow(nullptr)
	, mWinFlag(false)
	, mEnemySpawnPoints()
	, mActiveEnemies()
{
	loadTextures();
	buildScene();

	// Prepare the view
	mWorldView.setCenter(mSpawnPosition);
}

void Room::update(sf::Time dt)
{
	// Scroll the world, reset player velocity
	mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());	
	mPlayerCharacter->setVelocity(0.f, 0.f);

	// Forward commands to scene graph, adapt velocity (scrolling, diagonal correction)
	while (!mCommandQueue.isEmpty())
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);
	// daptPlayerVelocity();

	// Collision detection and response (may destroy entities)
	handleCollisions();

	// Remove all destroyed entities, create new ones
	mSceneGraph.removeMarked();
    // spawnEnemies();
    
	sf::Vector2f vec = mFinishLine->getWorldPosition() - mPlayerCharacter->getWorldPosition();
	float angle = util::toDegree(atan2f(vec.y, vec.x));
	mArrow->setRotation(angle);
	mArrow->setRotation(1.f);
	mArrow->setOrigin(0.f,0.f);
	mArrow->setOrigin(sf::Vector2f(-std::min(100.f, util::length(vec)), 0.f));

	// Regular update step, adapt position (correct if outside view)
	mSceneGraph.update(dt, mCommandQueue);
	adaptPlayerPosition();

	mWorldView.setCenter(mPlayerCharacter->getPosition() + mPlayerCharacter->getOrigin());
}

constexpr bool Room::hasFinishedLevel() const
{
	return isWinConditionMet();
}

void Room::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

constexpr CommandQueue& Room::getCommandQueue()
{
	return mCommandQueue;
}

bool Room::hasAlivePlayer() const
{
	return !mPlayerCharacter->isMarkedForRemoval();
}

constexpr bool Room::isWinConditionMet() const
{
	return mWinFlag;
}

void Room::loadTextures()
{
    std::string jsonPath = "../src/Resources.json";
	std::ifstream i(jsonPath);
	if (i.fail())
		throw std::runtime_error("Could not open file: " + jsonPath);
	json data;
	i >> data;

    loadResource<Textures::ID>(mTextures, data["Room1"]["Textures"]);
}

void Room::adaptPlayerPosition()
{
	const float borderDistance = 40.f;

	sf::Vector2f position = mPlayerCharacter->getPosition();
	position.x = std::max(position.x, mWorldBounds.left + borderDistance);
	position.x = std::min(position.x, mWorldBounds.left + mWorldBounds.width - borderDistance);
	position.y = std::max(position.y, mWorldBounds.top + borderDistance);
	position.y = std::min(position.y, mWorldBounds.left + mWorldBounds.height - borderDistance);
	mPlayerCharacter->setPosition(position);
}

void Room::adaptPlayerVelocity()
{
	sf::Vector2f velocity(mPlayerCharacter->getVelocity().x, 0.f);

	// If moving diagonally, reduce velocity (to have always same velocity)
	if (velocity.x != 0.f && velocity.y != 0.f)
		mPlayerCharacter->setVelocity(velocity / std::sqrt(2.f));

	mPlayerCharacter->setVelocity(velocity);
}

bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2)
{
	Category::Type category1 = colliders.first->getCategory();
	Category::Type category2 = colliders.second->getCategory();

	// Make sure first pair entry has category type1 and second has type2
	if (type1 == category1 && type2 == category2)
	{
		return true;
	}
	else if (type1 == category2 && type2 == category1)
	{
		std::swap(colliders.first, colliders.second);
		return true;
	}
	else
	{
		return false;
	}
}

void Room::handleCollisions()
{
	std::set<SceneNode::Pair> collisionPairs;
	mSceneGraph.checkSceneCollision(mSceneGraph, collisionPairs);

	for(SceneNode::Pair pair: collisionPairs)
	{
		// ** Use this as a prototype for when pairs collide
		// if (matchesCategories(pair, Category::Type::<FirstType>, Category::Type::<SecondType>))
		// {
		// 	auto& FirstNode = static_cast<FirstType&>(*pair.first);
		// 	auto& SecondNode = static_cast<SecondType&>(*pair.second);
		//
		// 		Do logic here
		//
		// }

		if (matchesCategories(pair, Category::Type::PlayerActor, Category::Type::Trigger))
		{
			auto& triggerNode = static_cast<TriggerNode&>(*pair.second);

			Command command;
			command.category = Category::Type::PlayerActor;
			command.action = triggerNode.getAction();
			mCommandQueue.push(command);
		}
	}
}

void Room::buildScene()
{

	// Register and add Layers
	SceneNode::Ptr layerBG(new SceneNode());
	mSceneLayers.emplace(std::make_pair(Layer::Background, layerBG.get()));
	mSceneGraph.attachChild(std::move(layerBG));
	SceneNode::Ptr layerC(new SceneNode());
	mSceneLayers.emplace(std::make_pair(Layer::Cables, layerC.get()));
	mSceneGraph.attachChild(std::move(layerC));
	SceneNode::Ptr layerPF(new SceneNode(Category::Type::SceneAirLayer));
	mSceneLayers.emplace(std::make_pair(Layer::Playfield, layerPF.get()));
	mSceneGraph.attachChild(std::move(layerPF));


	// Prepare the tiled background
	sf::Texture& texture = mTextures.get(Textures::ID::Background);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	// Add the background sprite to the scene
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Layer::Background]->attachChild(std::move(backgroundSprite));

    // Add House thing
    auto houseSprite = std::make_unique<SpriteNode>(mTextures.get(Textures::ID::House));
    houseSprite->setPosition(mSpawnPosition - sf::Vector2f(0.f, 200.f));
    mSceneLayers[Layer::Background]->attachChild(std::move(houseSprite));

	// Add player
	std::unique_ptr<Actor> player(new Actor(Actor::Type::Nanotech, mTextures, mFonts));
	mPlayerCharacter = player.get();
	mPlayerCharacter->setPosition(mSpawnPosition);

	// Add arrow pointing
	std::unique_ptr<Actor> arrow(new Actor(Actor::Type::Door, mTextures, mFonts));
	mArrow = arrow.get();
	//mArrow->setOrigin(sf::Vector2f(-100.f, mArrow->getOrigin().y));
	//mArrow->setPosition(0.f,0.f);

	player->attachChild(std::move(arrow));

	mSceneLayers[Layer::Playfield]->attachChild(std::move(player));

	std::unique_ptr<Actor> door(new Actor(Actor::Type::Door, mTextures, mFonts));
	mFinishLine = door.get();
	mFinishLine->setPosition(sf::Vector2f(200.f + static_cast<float>(util::randomInt(1600)), 200.f + static_cast<float>(util::randomInt(1600))));
	mSceneLayers[Layer::Background]->attachChild(std::move(door));

	std::function<void(SceneNode&, sf::Time)> tAction = [this](SceneNode&, sf::Time) { this->mWinFlag = true; };
	auto trigger = std::make_unique<TriggerNode>(derivedAction<SceneNode>(tAction));
	trigger->setPosition(mSpawnPosition + sf::Vector2f(300.f, 0.f));
	mSceneLayers[Layer::Playfield]->attachChild(std::move(trigger));

}

void Room::addEnemies()
{
	// Add enemies to the spawn point container
	addEnemy(Actor::Type::Nanobot,    0.f,  500.f);
	addEnemy(Actor::Type::Nanobot,    0.f, 1000.f);
	addEnemy(Actor::Type::Nanobot, +100.f, 1100.f);
	addEnemy(Actor::Type::Nanobot, -100.f, 1100.f);
	addEnemy(Actor::Type::Nanobot2, -70.f, 1400.f);
	addEnemy(Actor::Type::Nanobot2, -70.f, 1600.f);
	addEnemy(Actor::Type::Nanobot2,  70.f, 1400.f);
	addEnemy(Actor::Type::Nanobot2,  70.f, 1600.f);

	// Sort all enemies according to their y value, such that lower enemies are checked first for spawning
	std::sort(mEnemySpawnPoints.begin(), mEnemySpawnPoints.end(), [] (SpawnPoint lhs, SpawnPoint rhs)
	{
		return lhs.y < rhs.y;
	});
}

void Room::addEnemy(Actor::Type type, float relX, float relY)
{
	SpawnPoint spawn(type, mSpawnPosition.x + relX, mSpawnPosition.y - relY);
	mEnemySpawnPoints.push_back(spawn);
}

void Room::spawnEnemies()
{
	// Spawn all enemies entering the view area (including distance) this frame
	while (!mEnemySpawnPoints.empty())
	{
		SpawnPoint spawn = mEnemySpawnPoints.back();
		
		std::unique_ptr<Actor> enemy(new Actor(spawn.type, mTextures, mFonts));
		enemy->setPosition(spawn.x, spawn.y);
		enemy->setRotation(180.f);

		mSceneLayers[Layer::Playfield]->attachChild(std::move(enemy));

		// Enemy is spawned, remove from the list to spawn
		mEnemySpawnPoints.pop_back();
	}
}

// void Room::guideMissiles()
// {
// 	// Setup command that stores all enemies in mActiveEnemies
// 	Command enemyCollector;
// 	enemyCollector.category = Category::Type::EnemyActor;
// 	enemyCollector.action = derivedAction<Actor>([this] (Actor& enemy, sf::Time)
// 	{
// 		if (!enemy.isDestroyed())
// 			mActiveEnemies.push_back(&enemy);
// 	});

// 	// Setup command that guides all missiles to the enemy which is currently closest to the player
// 	Command missileGuider;
// 	missileGuider.category = Category::Type::AlliedProjectile;
// 	missileGuider.action = derivedAction<Projectile>([this] (Projectile& missile, sf::Time)
// 	{
// 		// Ignore unguided bullets
// 		if (!missile.isGuided())
// 			return;

// 		float minDistance = std::numeric_limits<float>::max();
// 		Actor* closestEnemy = nullptr;

// 		// Find closest enemy
// 		for(auto enemy: mActiveEnemies)
// 		{
// 			float enemyDistance = distance(missile, *enemy);

// 			if (enemyDistance < minDistance)
// 			{
// 				closestEnemy = enemy;
// 				minDistance = enemyDistance;
// 			}
// 		}

// 		if (closestEnemy)
// 			missile.guideTowards(closestEnemy->getWorldPosition());
// 	});

// 	Push commands, reset active enemies
// 	mCommandQueue.push(enemyCollector);
// 	mCommandQueue.push(missileGuider);
// 	mActiveEnemies.clear();
// }

sf::FloatRect Room::getViewBounds() const
{
	return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
}
