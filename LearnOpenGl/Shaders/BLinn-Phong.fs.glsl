#version 330 core

#define LIGHTS_MAX_NUM = 10

//光源结构体
struct DirLight{
    vec3 position;     // 光源位置
    vec3 color;        // 光源颜色
    float ambient;     // 环境光强度
    float diffuse;     // 漫反射光强度
    float specular;    // 镜面反射光强度
    float range;       // 光源有效范围（例如衰减距离）
};

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;//uniform sampler2DArray shadowMap;

uniform vec3 lights_pos;//uniform vec3 lights_pos[LIGHTS_MAX_NUM];
uniform vec3 viewPos;

uniform DirLight lights[LIGHTS_MAX_NUM];


out vec4 FragColor;

float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir)
{
    // 执行透视除法
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // 变换到[0,1]的范围
    projCoords = projCoords * 0.5 + 0.5;
    // 取得最近点的深度(使用[0,1]范围下的fragPosLight当坐标)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // 取得当前片段在光源视角下的深度
    float currentDepth = projCoords.z;
    // 计算bias
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    // 检查当前片段是否在阴影中
    float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    
    //PCF Implementation
    vec2 pixelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x){
        for(int y = -1; y <= 1; ++y){
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * pixelSize).r; 
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }

    return shadow / 9.0f;
}

void main()
{           
    // 采样纹理颜色
    vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;
    
    // 获取法线方向
    vec3 normal = normalize(fs_in.Normal);
    
    // 光源信息从输入获取（假设有多个光源）
    vec3 lightColor = lights[i].color;  // 光源颜色（动态）
    float ambientStrength = lights[i].ambient; // 环境光强度
    float diffuseStrength = lights[i].diffuse; // 漫反射强度
    float specularStrength = lights[i].specular; // 镜面反射强度
    float shininess = material.shininess;  // 光泽度（从材质属性获取）
    
    // ambient（环境光）
    vec3 ambient = ambientStrength * lightColor;

    // diffuse（漫反射）
    vec3 lightDir = normalize(lights_pos - fs_in.FragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diffuseStrength * diff * lightColor;

    // specular（镜面反射）
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightColor;

    // 计算阴影
    float shadow = ShadowCalculation(fs_in.FragPosLightSpace, normal, lightDir);                      
    
    // 最终光照
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;
    
    // 设置最终颜色输出
    FragColor = vec4(lighting, 1.0);
}