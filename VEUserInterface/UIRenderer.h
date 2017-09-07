#pragma once
class VulkanRenderer;
class VulkanToolkit;
class UIBox;
class UIText;
class UIBitmap;

class UIRenderer
{
public:
    UIRenderer(VulkanToolkit* vulkan, int width, int height);
    ~UIRenderer();
    int width{ 0 };
    int height{ 0 };
    VulkanToolkit* vulkan{ nullptr };
    VulkanRenderer* renderer{ nullptr };
    VulkanRenderStage* stage{ nullptr };
    VulkanDescriptorSetLayout* layout{ nullptr };
    VulkanImage* outputImage;
    std::vector<UIBox*> boxes;
    std::vector<UIText*> texts;
    std::vector<UIBitmap*> bitmaps;
    void draw();
    VulkanImage* dummyTexture;
};

