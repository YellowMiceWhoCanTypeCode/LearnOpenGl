#pragma once
#include <iostream>
#include <vec3.hpp>
#include <mat4x4.hpp>
#include <fwd.hpp>

//begin--------------------------------------------------------------------------------------------------
#define gl_vec3 glm::vec3
#define gl_mat4 glm::mat4
#define vec3_zero gl_vec3(0.0,0.0,0.0)
#define vec3_one gl_vec3(1.0,1.0,1.0)

namespace LearnOpengl
{
    struct Transform
    {
        Transform(const gl_vec3& position, const gl_vec3& rotate, const gl_vec3& scale)
            : position(position), rotate(rotate), scale(scale)
        {
        }

        gl_vec3 position;
        gl_vec3 rotate;
        gl_vec3 scale;
    };
}

#define normalize_transform LearnOpengl::Transform(vec3_zero, vec3_zero, vec3_one)
//end----------------------------------------------------------------------------------------------------


//begin--------------------------------------------------------------------------------------------------
#define DEBUG_OUTPUT_ON
#ifdef DEBUG_OUTPUT_ON
#define Debug_OutPut(info) std::cout<<__FILE__<<" Lines::"<<__LINE__<<"\n"<<(info)<<std::endl
#else
#define Debug_OutPut(info)
#endif
//end----------------------------------------------------------------------------------------------------


//begin--------------------------------------------------------------------------------------------------
#define STB_IMAGE_IMPLEMENTATION
//end----------------------------------------------------------------------------------------------------
