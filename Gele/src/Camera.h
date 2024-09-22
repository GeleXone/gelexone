#pragma once
#include "Xone/x_math.h"
#include "GLFW/glfw3.h"

#define CAMERA_SPEED 0.0000000001f

void camera_move(GLFWwindow* window, mat4 view);
