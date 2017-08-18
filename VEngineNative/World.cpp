#include "stdafx.h"
#include "Game.h"
#include "World.h"

World::World()
{
    mainDisplayCamera = nullptr;
    scene = new Scene();
    physics = new Physics();
}

World::~World()
{
    delete scene;
    delete mainDisplayCamera;
}

void World::draw(VulkanRenderStage *stage, Camera *camera)
{
    scene->draw(stage->commandBuffer);
}

void World::setUniforms( Camera *camera)
{ 
    glm::mat4 cameraViewMatrix = camera->transformation->getInverseWorldTransform();
    glm::mat4 vpmatrix = camera->projectionMatrix * cameraViewMatrix;
    glm::mat4 cameraRotMatrix = camera->transformation->getRotationMatrix();
    glm::mat4 rpmatrix = camera->projectionMatrix * inverse(cameraRotMatrix);
    camera->cone->update(inverse(rpmatrix));
}

void World::setSceneUniforms()
{
    scene->prepareFrame();
}