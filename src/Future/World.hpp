#ifndef WORLD_HPP
#define WORLD_HPP

#include "Future/ResourceHolder.hpp"
#include "Future/ResourceIdentifiers.hpp"
#include "Future/SceneNode.hpp"
#include "Future/Actor.hpp"
#include "Future/CommandQueue.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <vector>
#include <map>

namespace sf
{
	class RenderWindow;
	class Time;
}

class World : private sf::NonCopyable
{
public:
	World(sf::RenderWindow& window, FontHolder& fonts);

public:
	virtual void update(sf::Time dt);
	void draw();

	CommandQueue& getCommandQueue();

	bool hasAlivePlayer() const;
	bool hasFinishedLevel() const;
	virtual bool isWinConditionMet() const;

private:
	virtual void loadTextures();
	void adaptPlayerPosition();
	void adaptPlayerVelocity();
	void handleCollisions();

	void buildScene();
	void addEnemies();
	void addEnemy(Actor::Type type, float relX, float relY);
	void spawnEnemies();
	sf::FloatRect getViewBounds() const;

private:
	enum class Layer : char
	{
		Background,
		Playfield,
		Cables,
	};

	struct SpawnPoint
	{
		SpawnPoint(Actor::Type type, float x, float y)
			: type(type)
			, x(x)
			, y(y)
		{
		}

		Actor::Type type;
		float x;
		float y;
	};

private:
	sf::RenderWindow& mWindow;
	sf::View mWorldView;
	TextureHolder mTextures;
	FontHolder& mFonts;

	SceneNode mSceneGraph;
	CommandQueue mCommandQueue;

	sf::FloatRect mWorldBounds;
	sf::Vector2f mSpawnPosition;
	float mScrollSpeed;
	Actor* mFinishLine;
	Actor* mPlayerCharacter;
	Actor* mArrow;

	std::map<Layer, SceneNode*> mSceneLayers;
	std::vector<SpawnPoint> mEnemySpawnPoints;
	std::vector<Actor*> mActiveEnemies;
};

#endif // WORLD_HPP
