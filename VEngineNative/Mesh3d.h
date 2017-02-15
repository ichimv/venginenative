#pragma once
#include "Mesh3dInstance.h";
#include "Mesh3dLodLevel.h";
#include "Object3dInfo.h";
#include "AbsDrawable.h";
#include "Material.h";
class Mesh3d : public AbsDrawable
{
public:
    Mesh3d();
    ~Mesh3d();
    static Mesh3d *create(Object3dInfo *info, Material *material);
    void addInstance(Mesh3dInstance *instance);
    void addLodLevel(Mesh3dLodLevel *level);
    void clearInstances();
    void clearLodLevels();
    vector<Mesh3dInstance*>& getInstances();
    vector<Mesh3dLodLevel*>& getLodLevels();
    Mesh3dInstance *getInstance(int index);
    Mesh3dLodLevel *getLodLevel(int index);
    void removeInstance(Mesh3dInstance* instance);
    void removeLodLevel(Mesh3dLodLevel* level);
    void updateBuffers(TransformStruct transform);
    void draw();
    void setUniforms(TransformStruct transform);
    unsigned int id;
    string name = "";
private:
    vector<Mesh3dInstance*> instances;
    vector<Mesh3dLodLevel*> lodLevels;
};
