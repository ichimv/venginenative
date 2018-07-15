// Example_SimpleFullScreenPass.cpp: Określa punkt wejścia dla aplikacji konsoli.
//

#include "stdafx.h"

#include "Media.h"

int main()
{
    Media::loadFileMap("../../media");
    Media::loadFileMap("../../shaders");
    auto toolkit = new VulkanToolkit(640, 480, true, "Full screen pass example");

    auto texture = toolkit->getVulkanImageFactory()->build("blaze.png");

    auto buffer = toolkit->getVulkanBufferFactory()->build(VulkanBufferType::BufferTypeUniform, sizeof(float) * 20);

    //////

    auto vertTeapot = toolkit->getVulkanShaderFactory()->build(VulkanShaderModuleType::Vertex, "example-advancedteapot-teapot.vert.spv");
    auto fragTeapot = toolkit->getVulkanShaderFactory()->build(VulkanShaderModuleType::Fragment, "example-advancedteapot-teapot.frag.spv");

    auto layoutTeapot = toolkit->getVulkanDescriptorSetLayoutFactory()->build();
    layoutTeapot->addField(VulkanDescriptorSetFieldType::FieldTypeUniformBuffer, static_cast<VulkanDescriptorSetFieldStage>(VulkanDescriptorSetFieldStage::FieldStageFragment | VulkanDescriptorSetFieldStage::FieldStageVertex));
    layoutTeapot->addField(VulkanDescriptorSetFieldType::FieldTypeSampler, VulkanDescriptorSetFieldStage::FieldStageFragment);
    layoutTeapot->compile();

    auto colorImage = toolkit->getVulkanImageFactory()->build(640, 480, VulkanImageFormat::RGBA16f, static_cast<VulkanImageUsage>(VulkanImageUsage::ColorAttachment | VulkanImageUsage::Sampled));
    auto depthImage = toolkit->getVulkanImageFactory()->build(640, 480, VulkanImageFormat::Depth32f, VulkanImageUsage::Depth, VulkanImageAspect::DepthAspect, VulkanImageLayout::Preinitialized);

    auto stageTeapot = toolkit->getVulkanRenderStageFactory()->build(640, 480, { vertTeapot, fragTeapot }, { layoutTeapot },
        {
            colorImage->getAttachment(VulkanAttachmentBlending::None, true, { { 0.0f, 0.0f, 0.0f, 0.0f } }, false),
            depthImage->getAttachment(VulkanAttachmentBlending::None, true, { { 1.0f, 1.0f, 1.0f, 1.0f } }, false)
        });

    auto setTeapot = layoutTeapot->generateDescriptorSet();
    setTeapot->bindBuffer(0, buffer);
    setTeapot->bindImageViewSampler(1, texture);
    setTeapot->update();

    stageTeapot->setSets({ setTeapot });

    stageTeapot->compile();

    //////

    auto vertOutput = toolkit->getVulkanShaderFactory()->build(VulkanShaderModuleType::Vertex, "example-advancedteapot-output.vert.spv");
    auto fragOutput = toolkit->getVulkanShaderFactory()->build(VulkanShaderModuleType::Fragment, "example-advancedteapot-output.frag.spv");

    auto layoutOutput = toolkit->getVulkanDescriptorSetLayoutFactory()->build();
    layoutOutput->addField(VulkanDescriptorSetFieldType::FieldTypeUniformBuffer, VulkanDescriptorSetFieldStage::FieldStageAll);
    layoutOutput->addField(VulkanDescriptorSetFieldType::FieldTypeSampler, VulkanDescriptorSetFieldStage::FieldStageFragment);
    layoutOutput->compile();

    auto stageOutput = toolkit->getVulkanRenderStageFactory()->build(640, 480, { vertOutput, fragOutput }, { layoutOutput }, { });

    auto setOutput = layoutOutput->generateDescriptorSet();
    setOutput->bindBuffer(0, buffer);
    setOutput->bindImageViewSampler(1, colorImage);
    setOutput->update();

    stageOutput->setSets({ setOutput });

    auto output = toolkit->getVulkanSwapChainOutputFactory()->build(stageOutput);

    auto teapot = toolkit->getObject3dInfoFactory()->build("teapot.raw");
    auto fullScreenQuad = toolkit->getObject3dInfoFactory()->getFullScreenQuad();

    while (!toolkit->shouldCloseWindow()) {

        void* ptr;
        buffer->map(0, sizeof(float) * 1, &ptr);
        ((float*)ptr)[0] = (float)toolkit->getExecutionTime();
        buffer->unmap();

        stageTeapot->beginDrawing();
        stageTeapot->drawMesh(teapot, 1);
        stageTeapot->endDrawing();
        stageTeapot->submit({});

        output->beginDrawing();
        // no meshes drawn, only post process which is handled automatically
        output->drawMesh(fullScreenQuad, 1);
        output->endDrawing();
        output->submit({ stageTeapot->getSignalSemaphore() });

        toolkit->poolEvents();
    }

    return 0;
}

