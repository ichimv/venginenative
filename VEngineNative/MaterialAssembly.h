#pragma once

#include "Texture2d.h"

#define MASM_DIRECTIVE_STORE_FLOAT 1
#define MASM_DIRECTIVE_STORE_VEC3 2
#define MASM_DIRECTIVE_STORE_VEC4 3
#define MASM_DIRECTIVE_CONSTMOV_INT 4
#define MASM_DIRECTIVE_CONSTMOV_FLOAT 5
#define MASM_DIRECTIVE_CONSTMOV_VEC2 6
#define MASM_DIRECTIVE_CONSTMOV_VEC3 7
#define MASM_DIRECTIVE_CONSTMOV_VEC4 8
#define MASM_DIRECTIVE_REGMOV_FLOAT 9
#define MASM_DIRECTIVE_REGMOV_VEC2 10
#define MASM_DIRECTIVE_REGMOV_VEC3 11
#define MASM_DIRECTIVE_REGMOV_VEC4 12

#define MASM_DIRECTIVE_TEXTURE_R 13
#define MASM_DIRECTIVE_TEXTURE_G 14
#define MASM_DIRECTIVE_TEXTURE_B 15
#define MASM_DIRECTIVE_TEXTURE_A 16

#define MASM_DIRECTIVE_TEXTURE_RG 17
#define MASM_DIRECTIVE_TEXTURE_GB 18
#define MASM_DIRECTIVE_TEXTURE_BA 19

#define MASM_DIRECTIVE_TEXTURE_RGB 20
#define MASM_DIRECTIVE_TEXTURE_GBA 21

#define MASM_DIRECTIVE_TEXTURE_RGBA 22

#define MASM_DIRECTIVE_MIX_FLOAT_FLOAT 23
#define MASM_DIRECTIVE_MIX_VEC2_FLOAT 24
#define MASM_DIRECTIVE_MIX_VEC3_FLOAT 25
#define MASM_DIRECTIVE_MIX_VEC4_FLOAT 26
#define MASM_DIRECTIVE_POW_FLOAT_FLOAT 27
#define MASM_DIRECTIVE_POW_VEC2_FLOAT 28
#define MASM_DIRECTIVE_POW_VEC3_FLOAT 29
#define MASM_DIRECTIVE_POW_VEC4_FLOAT 30

#define MASM_DIRECTIVE_JUMP_ABSOLUTE 31
#define MASM_DIRECTIVE_JUMP_RELATIVE 32 // cool
#define MASM_DIRECTIVE_JUMP_BACK 33 // and i thought recursiveness wouldnt be possible

#define MASM_DIRECTIVE_JUMP_IF_EQUAL_INT 34
#define MASM_DIRECTIVE_JUMP_IF_EQUAL_FLOAT 35
#define MASM_DIRECTIVE_JUMP_IF_EQUAL_VEC2 36
#define MASM_DIRECTIVE_JUMP_IF_EQUAL_VEC3 37
#define MASM_DIRECTIVE_JUMP_IF_EQUAL_VEC4 38

#define MASM_DIRECTIVE_JUMP_IF_NOT_EQUAL_INT 39
#define MASM_DIRECTIVE_JUMP_IF_NOT_EQUAL_FLOAT 40
#define MASM_DIRECTIVE_JUMP_IF_NOT_EQUAL_VEC2 41
#define MASM_DIRECTIVE_JUMP_IF_NOT_EQUAL_VEC3 42
#define MASM_DIRECTIVE_JUMP_IF_NOT_EQUAL_VEC4 43

#define MASM_DIRECTIVE_JUMP_IF_HIGHER_INT 44
#define MASM_DIRECTIVE_JUMP_IF_HIGHER_FLOAT 45
#define MASM_DIRECTIVE_JUMP_IF_HIGHER_VEC2 46
#define MASM_DIRECTIVE_JUMP_IF_HIGHER_VEC3 47
#define MASM_DIRECTIVE_JUMP_IF_HIGHER_VEC4 48

#define MASM_DIRECTIVE_JUMP_IF_LOWER_INT 49
#define MASM_DIRECTIVE_JUMP_IF_LOWER_FLOAT 50
#define MASM_DIRECTIVE_JUMP_IF_LOWER_VEC2 51
#define MASM_DIRECTIVE_JUMP_IF_LOWER_VEC3 52
#define MASM_DIRECTIVE_JUMP_IF_LOWER_VEC4 53

#define MASM_DIRECTIVE_INC_INT 54
#define MASM_DIRECTIVE_DEC_INT 55

#define MASM_DIRECTIVE_ADD_INT 56
#define MASM_DIRECTIVE_ADD_FLOAT 57
#define MASM_DIRECTIVE_ADD_VEC2 58
#define MASM_DIRECTIVE_ADD_VEC2_FLOAT 59
#define MASM_DIRECTIVE_ADD_VEC3 60
#define MASM_DIRECTIVE_ADD_VEC3_FLOAT 61
#define MASM_DIRECTIVE_ADD_VEC4 62
#define MASM_DIRECTIVE_ADD_VEC4_FLOAT 63

#define MASM_DIRECTIVE_SUB_INT 64
#define MASM_DIRECTIVE_SUB_FLOAT 65
#define MASM_DIRECTIVE_SUB_VEC2 66
#define MASM_DIRECTIVE_SUB_VEC2_FLOAT 67
#define MASM_DIRECTIVE_SUB_VEC3 68
#define MASM_DIRECTIVE_SUB_VEC3_FLOAT 69
#define MASM_DIRECTIVE_SUB_VEC4 70
#define MASM_DIRECTIVE_SUB_VEC4_FLOAT 71

#define MASM_DIRECTIVE_MUL_INT 72
#define MASM_DIRECTIVE_MUL_FLOAT 73
#define MASM_DIRECTIVE_MUL_VEC2 74
#define MASM_DIRECTIVE_MUL_VEC2_FLOAT 75
#define MASM_DIRECTIVE_MUL_VEC3 76
#define MASM_DIRECTIVE_MUL_VEC3_FLOAT 77
#define MASM_DIRECTIVE_MUL_VEC4 78
#define MASM_DIRECTIVE_MUL_VEC4_FLOAT 79

#define MASM_DIRECTIVE_DIV_INT 80
#define MASM_DIRECTIVE_DIV_FLOAT 81
#define MASM_DIRECTIVE_DIV_VEC2 82
#define MASM_DIRECTIVE_DIV_VEC2_FLOAT 83
#define MASM_DIRECTIVE_DIV_VEC3 84
#define MASM_DIRECTIVE_DIV_VEC3_FLOAT 85
#define MASM_DIRECTIVE_DIV_VEC4 86
#define MASM_DIRECTIVE_DIV_VEC4_FLOAT 87

#define MASM_TARGET_DIFFUSECOLOR 0
#define MASM_TARGET_NORMAL 1

#define MASM_JUMP_STACK_SIZE 16
#define MASM_OUTPUT_CHUNK_SIZE 4
#define MASM_REGISTER_CHUNK_SIZE 16

#define MAX_PROGRAM_UNIFORMS_FLOAT 32
#define MAX_PROGRAM_UNIFORMS_INT 16
#define MAX_PROGRAM_UNIFORMS_VEC2 16
#define MAX_PROGRAM_UNIFORMS_VEC3 32
#define MAX_PROGRAM_UNIFORMS_VEC4 32
#define MAX_PROGRAM_LENGTH 1024

#define MASM_MAX_TEXTURES 10

class MaterialAssembly
{
public:
    MaterialAssembly();
    ~MaterialAssembly();
    vector<float> uniformsFloat;
    vector<int> uniformsInt;
    vector<glm::vec2> uniformsVec2;
    vector<glm::vec3> uniformsVec3;
    vector<glm::vec4> uniformsVec4;
    vector<int> programAssembly;
    vector<Texture2d*> textures;
    vector<glm::vec2> texturesScales;
    void setUniforms();
};
