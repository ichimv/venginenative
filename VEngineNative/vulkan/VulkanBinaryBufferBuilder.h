#pragma once
class VulkanBinaryBufferBuilder
{
public:
	std::vector<unsigned char> buffer;
	VulkanBinaryBufferBuilder();
	~VulkanBinaryBufferBuilder();
	void* getPointer();
	void emplaceByte(unsigned char byte);
	void emplaceInt32(int32_t byte);
	void emplaceFloat32(float byte);
	void emplaceMat4(glm::mat4 m);
	void emplaceVec3(glm::vec3 v);
};

