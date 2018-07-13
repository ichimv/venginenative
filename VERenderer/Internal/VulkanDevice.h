#pragma once
#include "VulkanSwapChain.h"
#include "VulkanMemoryManager.h"

class VulkanDevice
{
public:
    VulkanDevice(int width, int height, bool enableValidation, std::string windowName);
    ~VulkanDevice();
    VkDevice getDevice();
    VkQueue getMainQueue();
    VkCommandPool getCommandPool();
    bool shouldCloseWindow();
    void poolEvents();
    double getExecutionTime();
    VulkanMemoryManager* getMemoryManager();
    VulkanSwapChain* getSwapChain();
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
private:

    VkInstance instance;
    VkDevice device;
    VkPhysicalDevice pdevice;
    GLFWwindow *window;
    VkSurfaceKHR surface;
    VkDebugReportCallbackEXT callback;
    int chosenDeviceId = 0;
    int chosenQFId = 0;
    int windowWidth;
    int windowHeight;
    VulkanSwapChain* swapChain;
    VkCommandPool commandPool;
    VkQueue mainQueue;
    VkQueue secondaryQueue;
    VulkanMemoryManager* memoryManager;

    const std::vector<const char*> validationLayers = {
        "VK_LAYER_LUNARG_standard_validation",
        //"VK_LAYER_LUNARG_api_dump"
    };

    std::vector<VkPhysicalDevice> physicalDevices;
    std::vector<VkPhysicalDeviceProperties> physicalDevicesProps;
    std::vector<VkPhysicalDeviceFeatures> physicalDevicesFeats;
    std::vector<VkPhysicalDeviceMemoryProperties> physicalDevicesMemoryProps;
    std::vector<VkQueueFamilyProperties> getQueueFamilyProperties(VkPhysicalDevice pdevice);

    void createInstance(std::string appname, std::string enginename, bool enableValidation);
    void setupDebugCallback();
    void loadPhysicalDevices();
    void createLogicalDevice(VkPhysicalDevice pdevice, VkDeviceCreateInfo cinfo);

};

