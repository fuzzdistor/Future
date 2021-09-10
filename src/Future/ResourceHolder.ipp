template <typename Resource, typename ID>
void ResourceHolder<Resource, ID>::load(ID id, const std::string& filename)
{
	auto resource = std::make_unique<Resource>();

	if (!resource->loadFromFile(filename))
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
	
	insertResource(id, std::move(resource));
}

template <typename Resource, typename ID>
template <typename Param>
void ResourceHolder<Resource, ID>::load(ID id, const std::string& filename, const Param& secondParam)
{
	auto resource = std::make_unique<Resource>();

	if (!resource->loadFromFile(filename, secondParam))
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

	insertResource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
	auto found = mResourceMap.find(id);
	
	assert(found != mResourceMap.end() && "You tried getting a resource with key 'id' that is not currently loaded.");

	return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
	auto found = mResourceMap.find(id);
	
	assert(found != mResourceMap.end() && "You tried getting a resource with key 'id' that is not currently loaded.");

	return *found->second;
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::insertResource(Identifier id
	, std::unique_ptr<Resource> resource)
{
	auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));

	assert(inserted.second && "You tried inserting an already existent key");
}

template <typename Identifier, typename Holder>
void loadResource(Holder& holder, const nlohmann::json& data)
{
	for(auto elem: data)
	{
		const Identifier id = elem["ID"].get<Identifier>();
		
		if (id == Identifier::INVALID)
			throw std::runtime_error("loadResource - Fed Invalid identifier " + elem["ID"].get<std::string>());

		holder.load(id, elem["file"].get<std::string>());
	}
}
