#pragma once
#include "Framebuffer.h";
#include "Texture.h";
#include "CubeMapTexture.h";
#include "CubeMapFramebuffer.h";
#include "ShaderProgram.h";
#include "Object3dInfo.h";
class Renderer
{
public:
    Renderer(int iwidth, int iheight);
    ~Renderer();
    void renderToFramebuffer(glm::vec3 position, CubeMapFramebuffer *fbo);
    void renderToFramebuffer(Camera *camera, Framebuffer *fbo);
    void recompileShaders();
    void resize(int iwidth, int iheight);
private:
    int width;
    int height;
    void draw(Camera *camera);
    void initializeFbos();
    void destroyFbos();

    CubeMapTexture *skyboxTexture;
    Object3dInfo *quad3dInfo;

    //MRT Buffers
    Framebuffer *mrtFbo;
    Texture *mrtAlbedoRoughnessTex;
    Texture *mrtNormalMetalnessTex;
    Texture *mrtDistanceTexture;
    Texture *depthTexture;

    // Effects part
    ShaderProgram *deferredShader;
    Framebuffer *deferredFbo;
    Texture *deferredTexture;
    void deferred();

    ShaderProgram *ambientLightShader;
    Framebuffer *ambientLightFbo;
    Texture *ambientLightTexture;
    void ambientLight();

    ShaderProgram *ambientOcclusionShader;
    Framebuffer *ambientOcclusionFbo;
    Texture *ambientOcclusionTexture;
    void ambientOcclusion();

    ShaderProgram *fogShader;
    Framebuffer *fogFbo;
    Texture *fogTexture;
    void fog();

    ShaderProgram *motionBlurShader;
    Framebuffer *motionBlurFbo;
    Texture *motionBlurTexture;
    void motionBlur();

    ShaderProgram *bloomShader;
    Framebuffer *bloomFbo;
    Texture *bloomXTexture;
    Texture *bloomYTexture;
    void bloom();

    ShaderProgram *combineShader;
    Framebuffer *combineFbo;
    Texture *combineTexture;
    void combine();

    // Output to output fbo
    ShaderProgram *outputShader;
    void output();
};
