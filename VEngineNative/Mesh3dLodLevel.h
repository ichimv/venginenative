#pragma once
class Mesh3d;
#include "Material.h"
#include "Object3dInfo.h"
#include "Mesh3dInstance.h"
class Mesh3dLodLevel
{
public:
    Mesh3dLodLevel(Object3dInfo *info, Material *imaterial, float distancestart, float distanceend);
    Mesh3dLodLevel(Object3dInfo *info, Material *imaterial);
    Mesh3dLodLevel();
    ~Mesh3dLodLevel();
    Material *material;
    Object3dInfo *info3d;
    float distanceStart;
    float distanceEnd;
    unsigned int id; 
    bool visible = true;
    bool ignoreFrustumCulling = false; 
    void draw(VulkanRenderStage* stage, const Mesh3d* mesh);
    void updateBuffer(const Mesh3d* mesh, const vector<Mesh3dInstance*> &instances); 
    void initialize(); 
    VulkanDescriptorSet descriptorSet;
private:
    VulkanGenericBuffer *modelInfosBuffer;

    bool checkIntersection(Mesh3dInstance* instance);

    size_t instancesFiltered;
    vector<unsigned int> lastIdMap = vector<unsigned int>{};
    vector<unsigned int> newids = vector<unsigned int>{};
};
