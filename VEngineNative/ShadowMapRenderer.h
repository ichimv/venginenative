#pragma once  
class VulkanDescriptorSetLayout;
class VulkanGenericBuffer;
class VulkanImage;
class VulkanToolkit;
class Camera;

class ShadowMapRenderer
{
public:
    ShadowMapRenderer(VulkanToolkit * vulkan, int width, int height, std::string fragmentModule);
    ~ShadowMapRenderer();
    VulkanToolkit * vulkan; 

    VulkanDescriptorSet* sharedSet;


    VulkanGenericBuffer* uboHighFrequencyBuffer;
    VulkanGenericBuffer* uboLowFrequencyBuffer;
    VulkanImage* depthImage;
    VulkanImage* distanceImage;

    VulkanRenderer* renderer;

    void render(Camera *camera);
    int width;
    int height;
};

