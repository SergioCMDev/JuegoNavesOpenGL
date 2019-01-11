#pragma once
#ifndef WINDOW_H     
#define  WINDOW_H

#include<stdio.h>
#include<iostream>
#include<cstdint>
#define GLFW_INCLUDE_NONE
#include <Camera.h>
#include<GLFW/glfw3.h>
#include<glad/glad.h>

using namespace std;

class Window {
public:
	~Window();
	static Window* Instance();
	static Window* GetInstance(const int widht, const int height);
	//static void HandlerInput(GLFWwindow* window, const double deltaTime);
	static void HandlerInput(const double deltaTime);
	GLFWwindow* GetWindow();
	static Camera _camera;
	static void OnMouse(GLFWwindow* window, double xpos, double ypos);
	Window(const int widht, const int height);
	Window();
	static void OnScroll(GLFWwindow* window, double xoffset, double yoffset);
	static void OnChangeFrameBufferSize(GLFWwindow* window, const int32_t width, const int32_t height);
	void Window::AddCamera(Camera camera);
private:

	static GLFWwindow* _glfwWindow;
	static Window* _window;
	static bool _firstMouse;
	static double _lastX, _lastY;
};
#endif