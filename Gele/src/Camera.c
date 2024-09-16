#include "Camera.h"

void camera_move(GLFWwindow* window, mat4 view) {
	mat4 add;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		mat4_create_translation(add, 0, 0, CAMERA_SPEED);
		mat4_add(view, add);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		mat4_create_translation(add, 0, 0, -CAMERA_SPEED);
		mat4_add(view, add);
	}
}