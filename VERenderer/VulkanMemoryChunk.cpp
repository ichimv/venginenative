#include "stdafx.h"
#include "VulkanMemoryChunk.h"


VulkanMemoryChunk::VulkanMemoryChunk(VulkanToolkit* ivulkan, uint32_t itype)
    : vulkan(ivulkan), type(itype)
{
    chunkSize = 256 * 1024 * 1024;
    VkMemoryAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = chunkSize;
    allocInfo.memoryTypeIndex = type;

    if (vkAllocateMemory(vulkan->device, &allocInfo, nullptr, &handle) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate image memory!");
    }
}


VulkanMemoryChunk::~VulkanMemoryChunk()
{
    vkFreeMemory(vulkan->device, handle, nullptr);
}

VulkanSingleAllocation VulkanMemoryChunk::bindBufferMemory(VkBuffer buffer, VkDeviceSize size, VkDeviceSize offset)
{
    while (inUse);
    inUse = true;
    vkBindBufferMemory(vulkan->device, buffer, handle, offset);
    auto va = VulkanSingleAllocation(this, size, offset);
    allActiveAllocations.push_back(va);
    allAllocationsSize += size;
    inUse = false;
    return va;
}

VulkanSingleAllocation VulkanMemoryChunk::bindImageMemory(VkImage image, VkDeviceSize size, VkDeviceSize offset)
{
    while (inUse);
    inUse = true;
    vkBindImageMemory(vulkan->device, image, handle, offset);
    auto va = VulkanSingleAllocation(this, size, offset);
    allActiveAllocations.push_back(va);
    allAllocationsSize += size;
    inUse = false;
    return va;
}

void VulkanMemoryChunk::freeBindMemory(VulkanSingleAllocation allocation)
{
    while (inUse);
    inUse = true;
    int allocscount = allActiveAllocations.size();
    for (int i = 0; i < allocscount; i++) {
        auto a = allActiveAllocations[i];
        if (a.offset == allocation.offset && a.size == allocation.size) {
            allActiveAllocations.erase(allActiveAllocations.begin() + i);
            allAllocationsSize -= allocation.size;
            break;
        }
    }
    inUse = false;
}

bool VulkanMemoryChunk::findFreeMemoryOffset(VkDeviceSize size, VkDeviceSize &outOffset)
{
    while (inUse);
    inUse = true;
    if (isFreeSpace(0, size)) {
        outOffset = 0;
        inUse = false;
        return true;
    }
    int allocscount = allActiveAllocations.size();
    for (int i = 0; i < allocscount; i++) {
        auto a = allActiveAllocations[i];
        if (isFreeSpace(a.offset + a.size + 2048, size)) {
            outOffset = a.offset + a.size + 2048;
            inUse = false;
            return true;
        }
    }
    inUse = false;
    return false;
}

bool VulkanMemoryChunk::isFreeSpace(VkDeviceSize offset, VkDeviceSize size)
{
    VkDeviceSize end = offset + size;
    int allocscount = allActiveAllocations.size();
    if (end >= chunkSize) {
        return false;
    }
    for (int i = 0; i < allocscount; i++) {
        auto a = allActiveAllocations[i];
        VkDeviceSize aend = a.offset + a.size;
        if (offset >= a.offset && offset <= aend) { // if start of alloc collides
            return false;
        }
        if (end >= a.offset && end <= aend) { // if end of alloc collides
            return false;
        }
        if (offset <= a.offset && end >= aend) { // if alloc contains element
            return false;
        }
    }
    return true;
}