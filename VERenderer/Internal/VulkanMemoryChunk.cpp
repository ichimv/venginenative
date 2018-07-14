#include "stdafx.h"
#include "VulkanMemoryChunk.h"
#include "VulkanSingleAllocation.h"
#include "VulkanDevice.h"


VulkanMemoryChunk::VulkanMemoryChunk(VulkanDevice* device, uint32_t itype)
    : device(device), type(itype)
{
    chunkSize = 256 * 1024 * 1024;
    VkMemoryAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = chunkSize;
    allocInfo.memoryTypeIndex = type;

    if (vkAllocateMemory(device->getDevice(), &allocInfo, nullptr, &handle) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate requested memory!");
    }
}

VulkanMemoryChunk::~VulkanMemoryChunk()
{
    vkFreeMemory(device->getDevice(), handle, nullptr);
}

VulkanSingleAllocation VulkanMemoryChunk::bindBufferMemory(VkBuffer buffer, uint64_t size, uint64_t offset)
{
    while (inUse); // todo mutex
    inUse = true;
    vkBindBufferMemory(device->getDevice(), buffer, handle, offset);
    auto va = VulkanSingleAllocation(this, size, offset);
    allActiveAllocations.push_back(va);
    allAllocationsSize += size;
    inUse = false;
    return va;
}

VulkanSingleAllocation VulkanMemoryChunk::bindImageMemory(VkImage image, uint64_t size, uint64_t offset)
{
    while (inUse);
    inUse = true;
    vkBindImageMemory(device->getDevice(), image, handle, offset);
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
        if (a.getOffset() == allocation.getOffset() && a.getSize() == allocation.getSize()) {
            allActiveAllocations.erase(allActiveAllocations.begin() + i);
            allAllocationsSize -= allocation.getSize();
            break;
        }
    }
    inUse = false;
}

bool VulkanMemoryChunk::findFreeMemoryOffset(uint64_t size, uint64_t &outOffset)
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
        if (isFreeSpace(a.getOffset() + a.getSize() + 2048, size)) {
            outOffset = a.getOffset() + a.getSize() + 2048;
            inUse = false;
            return true;
        }
    }
    inUse = false;
    return false;
}

VkDeviceMemory VulkanMemoryChunk::getHandle()
{
    return handle;
}

VkDevice VulkanMemoryChunk::getDevice()
{
    return device->getDevice();
}

bool VulkanMemoryChunk::isFreeSpace(uint64_t offset, uint64_t size)
{
    VkDeviceSize end = offset + size;
    int allocscount = allActiveAllocations.size();
    if (end >= chunkSize) {
        return false;
    }
    for (int i = 0; i < allocscount; i++) {
        auto a = allActiveAllocations[i];
        VkDeviceSize aend = a.getOffset() + a.getSize();
        if (offset >= a.getOffset() && offset <= aend) { // if start of alloc collides
            return false;
        }
        if (end >= a.getOffset() && end <= aend) { // if end of alloc collides
            return false;
        }
        if (offset <= a.getOffset() && end >= aend) { // if alloc contains element
            return false;
        }
    }
    return true;
}