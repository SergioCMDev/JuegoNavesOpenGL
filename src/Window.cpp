#include "Window.h"

glm::vec3 posCamara = glm::vec3(0.0f, 0.0f, 3.0f);
Camera _camera(posCamara);


Window* Window::_window;

Window::~Window(){
	_window = nullptr;
}



Window* Window::GetInstance(const int widht, const int height)
 {
	if (_window == 0) {
		cout << "NULL"<<endl;
		_window = new Window(widht, height);
	}
	return _window;
}


Window::Window(const int widht, const int height) {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	_glfwWindow = glfwCreateWindow(widht, height, "Window 1", NULL, NULL);
	if (!_glfwWindow) {
		cout << "Error creating window" << endl;
		glfwTerminate();
		//return -1;
	}
	_camera = &Camera(posCamara);

	glfwMakeContextCurrent(_glfwWindow);
	//glfwSetCursorPosCallback(_glfwWindow, );
	//glfwSetFramebufferSizeCallback(_glfwWindow, OnChangeFrameBufferSize);
	//glfwSetScrollCallback(_glfwWindow, OnScroll);
	glfwSetInputMode(_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

}



GLFWwindow* Window::GetWindow() {
	return _glfwWindow;
}

void Window::HandlerInput(const double deltaTime) {
	if (glfwGetKey(_glfwWindow, GLFW_KEY_W) == GLFW_PRESS) {
		_camera->HandleKeyboard(Camera::Movement::Forward, deltaTime);
	}
	if (glfwGetKey(_glfwWindow, GLFW_KEY_S) == GLFW_PRESS) {
		_camera->HandleKeyboard(Camera::Movement::Backward, deltaTime);
	}
	if (glfwGetKey(_glfwWindow, GLFW_KEY_A) == GLFW_PRESS) {
		_camera->HandleKeyboard(Camera::Movement::Left, deltaTime);
	}
	if (glfwGetKey(_glfwWindow, GLFW_KEY_D) == GLFW_PRESS) {
		_camera->HandleKeyboard(Camera::Movement::Right, deltaTime);
	}
	Window::HandlerInput();
}

void Window::HandlerInput() {
	//Si pulsamos la tecla ESC cerramos la ventana
	if (glfwGetKey(_glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(_glfwWindow, true);
	}
}

void Window::OnScroll(double xoffset, double yoffset) {
	_camera->handleMouseScroll(yoffset);
}

void Window::OnMouse(GLFWwindow* window, double xpos, double ypos) {
	if (_firstMouse) {
		_firstMouse = false;
		_lastX = xpos;
		_lastY = ypos;
	}

	_xoffset = xpos - _lastX;
	_yoffset = ypos - _lastY;
	_lastX = xpos;
	_lastY = ypos;
	_camera->handleMouseMovement(_xoffset, _yoffset);
}

void OnScroll(GLFWwindow* window, double xoffset, double yoffset) {
	_camera.handleMouseScroll(yoffset);
}

void Window::OnChangeFrameBufferSize(GLFWwindow* window, const int32_t width, const int32_t height) {
	//redimension de pantalla 
	//Cambio de clip scene a view scene
	glViewport(0, 0, width, height);
}