#include "stdafx.h"
#include "VulkanFramebuffer.h"
#include "VulkanDevice.h"
#include "VulkanRenderPass.h"
#include <vulkan.h>

VulkanFramebuffer::VulkanFramebuffer(VulkanDevice * device, uint32_t width, uint32_t height, VulkanRenderPass* renderPass, std::vector<VkImageView> &attachments)
    : device(device)
{
    VkFramebufferCreateInfo framebufferInfo = {};
    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferInfo.renderPass = renderPass->getHandle();
    framebufferInfo.attachmentCount = attachments.size();
    framebufferInfo.pAttachments = attachments.data();
    framebufferInfo.width = width;
    framebufferInfo.height = height;
    framebufferInfo.layers = 1;

    vkCreateFramebuffer(device->getDevice(), &framebufferInfo, nullptr, &handle);
}

VulkanFramebuffer::~VulkanFramebuffer()
{
}

VkFramebuffer VulkanFramebuffer::getHandle()
{
    return handle;
}
