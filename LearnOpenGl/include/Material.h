#pragma once
#include <string>

enum aiTextureType : int;
struct aiMaterial;
class Texture;
class Shader;

class Material
{
public:
    virtual void Apply(Shader* shader) = 0;

    virtual void Generate(aiMaterial* material, const std::string& directory) = 0;

protected:
    Material();
    virtual ~Material();

    bool Bind_Impl(Shader* shader, Texture* texture, const std::string& tex_name, int& slot) const;
    void Gene_Impl(aiMaterial* material, Texture*& texture, aiTextureType texture_type, const std::string& directory) const;
};


class Cartoon_Material : public Material
{
public:
    Cartoon_Material();

    void Generate(aiMaterial* material, const std::string& directory) override;
    void Apply(Shader* shader) override;

public:
    Texture* color_map_ = nullptr;
    Texture* shadow_map_ = nullptr;
    Texture* outline_map_ = nullptr;
};


class PBR_Material : public Material
{
public:
    PBR_Material() = default;

public:
    //纹理
    Texture* color_map_ = nullptr;
    Texture* diffuse_map_ = nullptr;
    Texture* specular_map_ = nullptr;
    Texture* normal_map_ = nullptr;
};
