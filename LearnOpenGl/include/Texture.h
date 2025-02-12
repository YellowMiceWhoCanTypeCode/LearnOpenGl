#pragma once
#include <string>

class Texture
{
public:
    Texture() = default;
    Texture(const std::string& filePath);

    void Bind(unsigned int slot = 0) const;

public:
    unsigned int texture_ID_ = 0;
    std::string file_path_;
    std::string texture_type_;
};
