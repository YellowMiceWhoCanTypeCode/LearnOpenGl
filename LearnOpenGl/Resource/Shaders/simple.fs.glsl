#version 330 core
#extension GL_ARB_shading_language_include : require
#include "/LightingFuncLib.glsl"

in vec2 texCoords;

out vec4 FragColor;

uniform sampler2D texture_diffuse;

void main()
{
    FragColor = texture(texture_diffuse, texCoords);
}