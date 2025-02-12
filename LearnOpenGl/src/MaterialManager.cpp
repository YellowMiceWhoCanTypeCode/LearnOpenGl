#include "../include/MaterialManager.h"

#include "../include/Material.h"

MaterialManager* MaterialManager::Get()
{
    static auto* material_manager = new MaterialManager;
    return material_manager;
}

/*Material* MaterialManager::CreateMaterial(const std::string& name, Shader* shader)
{
    /*auto* new_material = new PBR_Material(shader);
    materials_.insert(std::pair{name, new_material});
    return new_material;#1#
}*/

Material* MaterialManager::GetMaterial(const std::string& name)
{
    const auto iter = materials_.find(name);
    if (iter == materials_.end())
    {
        return nullptr;
    }
    return iter->second;
}
