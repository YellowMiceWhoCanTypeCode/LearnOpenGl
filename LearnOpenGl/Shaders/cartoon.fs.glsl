#version 330 core

in vec2 texCoords;
out vec4 FragColor;

uniform sampler2D color_map;
uniform sampler2D shadow_map;
uniform sampler2D outline_map;

void main()
{
    FragColor = texture(color_map, texCoords);
    //FragColor = vec4(0.5,0.5,0.5,1.0);
}