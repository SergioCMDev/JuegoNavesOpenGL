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
	//void HandlerInput();
	void HandlerInput(const double deltaTime);
	GLFWwindow* GetWindow();
private:
	Window();
	Window(const int widht, const int height);
	static void OnScroll(GLFWwindow* window, double xoffset, double yoffset);
	static void OnMouse(GLFWwindow* window, double xpos, double ypos);
	static void OnChangeFrameBufferSize(GLFWwindow* window, const int32_t width, const int32_t height);

	GLFWwindow* _glfwWindow = nullptr;
	static Window* _window;
	static bool _firstMouse;
	static double _lastX, _lastY, _xoffset, _yoffset;
	static Camera _camera;
};
#endif