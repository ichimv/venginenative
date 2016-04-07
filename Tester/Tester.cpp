// Tester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../VEngineNative/Camera.h";
#include "../VEngineNative/Object3dInfo.h";
#include "../VEngineNative/Object3dManager.h";
#include "../VEngineNative/Media.h";
#include "../VEngineNative/World.h";
#include "../VEngineNative/Scene.h";
#include "../VEngineNative/Material.h";
#include "../VEngineNative/Mesh3d.h";
#include "../VEngineNative/Light.h";

int main()
{
    Media::loadFileMap("../../media");
    Media::loadFileMap("../../shaders");
    Game *game = new Game(1366, 768);
    game->start();
    volatile bool ready = false;
    game->invoke([&ready]() {
        ready = true;
    });
    while (!ready);

    Camera *cam = new Camera();
    cam->createProjectionPerspective(deg2rad(90.0f), 1366.0f / 768.0f, 0.01f, 1000);
    cam->transformation->translate(glm::vec3(0, 0, 4));
    glm::quat rot = glm::quat_cast(glm::lookAt(cam->transformation->position, glm::vec3(0), glm::vec3(0, 1, 0)));
    cam->transformation->setOrientation(rot);
    game->world->mainDisplayCamera = cam;

    Material *mat = new Material();
    mat->diffuseColor = glm::vec3(1.0f);
    //mat->diffuseTexture = new Texture("KAMEN.JPG");
    mat->normalsTexture = new Texture("b1WtX.jpg");
    mat->roughness = 0.5;
    mat->metalness = 0.5;

    unsigned char* teapotBytes;
    int teapotBytesCount = Media::readBinary("sponza.raw", &teapotBytes);
    GLfloat * floats = (GLfloat*)teapotBytes;
    int floatsCount = teapotBytesCount / 4;
    vector<GLfloat> flo(floats, floats + floatsCount);

    Object3dInfo *o3i = new Object3dInfo(flo);

    Mesh3d *teapot = Mesh3d::create(o3i, mat);

    game->invoke([teapot]() {
        teapot->updateBuffers();
    });

    game->world->scene->addMesh(teapot);

    Light* light = new Light();
    light->switchShadowMapping(true);
    light->cutOffDistance = 1000.0;
    light->color = glm::vec3(1);
    light->angle = deg2rad(90.0f);
    light->resizeShadowMap(1024, 1024);
    light->transformation->translate(glm::vec3(0, 2, 0));

    game->world->scene->addLight(light);


    bool cursorFree = false;
    game->onKeyPress->add([&game, &cursorFree](int key) {
        if (key == GLFW_KEY_PAUSE) {
            game->shaders->materialShader->recompile();
            game->shaders->depthOnlyShader->recompile();
            game->renderer->recompileShaders();
        }
        if (key == GLFW_KEY_TAB) {
            if (!cursorFree) {
                cursorFree = true;
                game->setCursorMode(GLFW_CURSOR_NORMAL);
            }
            else {
                cursorFree = false;
                game->setCursorMode(GLFW_CURSOR_DISABLED);
            }
        }
    });

    float yaw = 0.0f, pitch = 0.0f;
    double lastcx = 0.0f, lastcy = 0.0f;
    bool intializedCameraSystem = false;

    game->setCursorMode(GLFW_CURSOR_DISABLED);

    while (!game->shouldClose) {

        if (!cursorFree) {
            // process logic - on another thread
            if (game->getKeyStatus(GLFW_KEY_F1) == GLFW_PRESS) {
                light->transformation->position = cam->transformation->position;
                light->transformation->orientation = cam->transformation->orientation;
            }
            if (game->getKeyStatus(GLFW_KEY_W) == GLFW_PRESS) {
                glm::vec3 dir = cam->transformation->orientation * glm::vec3(0, 0, -1);
                cam->transformation->translate(dir * 0.00001f);
            }
            if (game->getKeyStatus(GLFW_KEY_S) == GLFW_PRESS) {
                glm::vec3 dir = cam->transformation->orientation * glm::vec3(0, 0, 1);
                cam->transformation->translate(dir * 0.00001f);
            }
            if (game->getKeyStatus(GLFW_KEY_A) == GLFW_PRESS) {
                glm::vec3 dir = cam->transformation->orientation * glm::vec3(-1, 0, 0);
                cam->transformation->translate(dir * 0.00001f);
            }
            if (game->getKeyStatus(GLFW_KEY_D) == GLFW_PRESS) {
                glm::vec3 dir = cam->transformation->orientation * glm::vec3(1, 0, 0);
                cam->transformation->translate(dir * 0.00001f);
            }
            if (game->getKeyStatus(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                game->shouldClose = true;
            }
            glm::dvec2 cursor = game->getCursorPosition();
            if (!intializedCameraSystem) {
                lastcx = cursor.x;
                lastcy = cursor.y;
                intializedCameraSystem = true;
            }
            float dx = (float)(lastcx - cursor.x);
            float dy = (float)(lastcy - cursor.y);
            lastcx = cursor.x;
            lastcy = cursor.y;
            yaw += dy * 0.2f;
            pitch += dx * 0.2f;
            if (yaw < -90.0) yaw = -90;
            if (yaw > 90.0) yaw = 90;
            if (pitch < -360.0f) pitch += 360.0f;
            if (pitch > 360.0f) pitch -= 360.0f;
            glm::quat newrot = glm::angleAxis(deg2rad(pitch), glm::vec3(0, 1, 0)) * glm::angleAxis(deg2rad(yaw), glm::vec3(1, 0, 0));
            cam->transformation->setOrientation(newrot);
        }
    }
    return 0;
}
