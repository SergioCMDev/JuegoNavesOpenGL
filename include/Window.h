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
	//static Window* Instance(const int widht, const int height);
	static Window* GetInstance(const int widht, const int height);
	GLFWwindow* GetWindow();
	void HandlerInput();
	void HandlerInput(const double deltaTime);
	void OnScroll(double xoffset, double yoffset);
	void OnMouse(GLFWwindow* window, double xpos, double ypos);
private:
	Window();
	Window(const int widht, const int height);
	void OnChangeFrameBufferSize(GLFWwindow* window, const int32_t width, const int32_t height);
	GLFWwindow* _glfwWindow = nullptr;
	static Window* _window;

	bool _firstMouse = false;
	double _lastX, _lastY, _xoffset, _yoffset;
	Camera* _camera = nullptr;
};
#endif