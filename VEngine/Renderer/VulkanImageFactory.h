#pragma once
#include "VulkanEnums.h"

namespace VEngine
{
    namespace Renderer
    {
        namespace Internal
        {
            class VulkanDevice;
        }
        class VulkanImage;

        class VulkanImageFactory
        {
        public:
            VulkanImageFactory(Internal::VulkanDevice* device);
            ~VulkanImageFactory();

            VulkanImage* build(uint32_t width, uint32_t height, uint32_t depth,
                VulkanImageFormat format, VulkanImageUsage usage, VulkanImageAspect aspect, VulkanImageLayout layout);

            VulkanImage* build(uint32_t width, uint32_t height, uint32_t depth,
                VulkanImageFormat format, VulkanImageUsage usage);

            VulkanImage* build(uint32_t width, uint32_t height,
                VulkanImageFormat format, VulkanImageUsage usage, VulkanImageAspect aspect, VulkanImageLayout layout);

            VulkanImage* build(uint32_t width, uint32_t height,
                VulkanImageFormat format, VulkanImageUsage usage);

            VulkanImage* build(uint32_t width, uint32_t height, VulkanImageFormat format, int usage);

            VulkanImage* build(std::string mediakey);

            VulkanImage* build(uint32_t width, uint32_t height, uint32_t channelCount, void * data);


        private:
            Internal::VulkanDevice * device;
        };


    }
}