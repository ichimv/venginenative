#pragma once
#include "EventHandler.h"
class Joystick
{
public:
    Joystick(GLFWwindow* win);
    ~Joystick();
    std::vector<bool> getButtonsStatus(int index);
    bool isPresent(int index);
    std::vector<float> getAxes(int index);
private:
    static Joystick * instance;
    GLFWwindow* window;
};

