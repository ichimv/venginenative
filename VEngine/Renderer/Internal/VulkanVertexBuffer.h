#pragma once
#include "VulkanSingleAllocation.h"
namespace VEngine
{
    namespace Renderer
    {
        class VulkanDescriptorSet;
        namespace Internal
        {
            class VulkanDevice;
            class VulkanGraphicsPipeline;
            class VulkanCommandBuffer;
            class VulkanVertexBuffer
            {
            public:
                VulkanVertexBuffer(VulkanDevice* device, std::vector<float>& data);
                ~VulkanVertexBuffer();
                VkBuffer getBuffer();
                void drawInstanced(VulkanGraphicsPipeline* p, std::vector<VulkanDescriptorSet*> sets, VulkanCommandBuffer* cb, uint32_t instances);
            private:
                VulkanDevice * device;
                VkBuffer vertexBuffer;
                VulkanSingleAllocation vertexBufferMemory;
                int vertexCount = 0;
            };
        }
    }
}