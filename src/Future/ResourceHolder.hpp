#ifndef RESOURCEHOLDER_HPP
#define RESOURCEHOLDER_HPP

#include "Future/json.hpp"

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
	void                    load(Identifier id, const std::string& filename);

	template <typename Parameter>
	void                    load(Identifier id, const std::string& filename, const Parameter& secondParam);

	Resource&               get(Identifier id);
	const Resource&         get(Identifier id) const;

private:
	void                    insertResource(Identifier id, std::unique_ptr<Resource> resource);

private:
	std::map<Identifier, std::unique_ptr<Resource>>     mResourceMap;
};

template <typename Identifier, typename Holder>
void loadResource(Holder& holder, const nlohmann::json& data);

#include "ResourceHolder.ipp"
#endif // RESOURCEHOLDER_HPP