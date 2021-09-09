#include "Future/DataTables.hpp"
#include "Future/Actor.hpp"

#include <map>
#include <vector>


std::map<Actor::Type, ActorData> initActorData()
{
	std::map<Actor::Type, ActorData>  data;

	ActorData nanotech;
	nanotech.speed = 200.f;
	nanotech.texture = Textures::ID::BlueGuy;
	data.insert(std::make_pair(Actor::Type::Nanotech, nanotech));

	ActorData nanobot;
	nanobot.speed = 80.f;
	nanobot.texture = Textures::ID::Enemy;
	nanobot.directions.push_back(Direction(+45.f, 80.f));
	nanobot.directions.push_back(Direction(-45.f, 160.f));
	nanobot.directions.push_back(Direction(+45.f, 80.f));
	data.insert(std::make_pair(Actor::Type::Nanobot, nanobot));


	ActorData nanobot2;
	nanobot2.speed = 50.f;
	nanobot2.directions.push_back(Direction(+45.f,  50.f));
	nanobot2.directions.push_back(Direction(  0.f,  50.f));
	nanobot2.directions.push_back(Direction(-45.f, 100.f));
	nanobot2.directions.push_back(Direction(  0.f,  50.f));
	nanobot2.directions.push_back(Direction(135.f, 100.f));
	nanobot2.directions.push_back(Direction(-180.f,  50.f));
	nanobot2.directions.push_back(Direction(-135.f, 50.f));
	nanobot2.directions.push_back(Direction(-180.f,  50.f));
	nanobot2.texture = Textures::ID::Door;
	data.insert(std::make_pair(Actor::Type::Nanobot2, nanobot2));

	ActorData door;
	door.texture = Textures::ID::Door;
	door.speed = 0.f;
	data.insert(std::make_pair(Actor::Type::Door, door));

	return data;
}
