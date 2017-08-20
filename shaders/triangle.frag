#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 inNormal;
layout(location = 1) in vec2 inTexCoord;

layout(location = 0) out vec4 outColor;

layout(binding = 1) uniform sampler2D texSampler;

void main() {
	float dt = max(0.0, dot(normalize(inNormal), normalize(vec3(1.0, -1.0, 0.0)))) *0.99 + 0.01;
    outColor = vec4(pow(texture(texSampler, inTexCoord).rgb * dt, vec3(1.0 / 2.2)), 1.0);
}