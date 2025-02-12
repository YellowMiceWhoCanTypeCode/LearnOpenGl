#pragma once
#include <unordered_map>
#include <string>

class Shader;
class Material;

class MaterialManager
{
public:
    static MaterialManager* Get();


    template <typename MaterialType>
    Material* CreateMaterial(const std::string& name)
    {
        static_assert(std::is_base_of_v<Material, MaterialType>, "MaterialType is not Material`s child");
        /*const auto iter = materials_.find(name);
        if (iter != materials_.end())
        {
            return iter->second;
        }*/

        auto* material = new MaterialType();
        materials_.insert(std::make_pair(name, material));
        return material;
    }

    Material* GetMaterial(const std::string& name);

private:
    MaterialManager() = default;

private:
    std::unordered_map<std::string, Material*> materials_;
};
