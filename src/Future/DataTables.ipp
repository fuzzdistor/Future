template <typename Type, typename Data>
const Data& getDataTableOf(Type type, const std::map<Type, Data>& table)
{
    auto found = table.find(type);
    assert(found != table.end());
    return found->second;    
}
