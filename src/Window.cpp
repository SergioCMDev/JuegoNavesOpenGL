#include "Window.h"


Window* Window::_window;
//const glm::vec3 posCamara = glm::vec3(0.0f, 0.0f, 3.0f);
const glm::vec3 posCamara = glm::vec3(-6.0f, 2.0f, 3.0f);

Camera Window::_camera(glm::vec3(-1.0f, 2.0f, 3.0f));

//Camera camera(glm::vec3(-1.0f, 2.0f, 3.0f));

bool Window::_firstMouse = false;
double Window::_lastX = 0.0f, 
	   Window::_lastY = 0.0f, 
	   Window::_xoffset = 0.0f, 
	   Window::_yoffset = 0.0f;

Window::~Window(){
	_window = nullptr;
}
Window* Window::Instance()
{
	return _window;
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

	_camera.handleMouseMovement(_xoffset, _yoffset);
}


Window* Window::GetInstance(const int widht, const int height)
 {
	if (_window == 0) {
		cout << "Creamos instancia de Window"<<endl;
		_window = new Window(widht, height);
	}
	return _window;
}

GLFWwindow* Window::GetWindow() {
	return _glfwWindow;
}

void Window::HandlerInput(GLFWwindow* window, const double deltaTime) {
	//Window* window = Window::Instance();
	//Camera camera = window->_camera;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		_camera.HandleKeyboard(Camera::Movement::Forward, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		_camera.HandleKeyboard(Camera::Movement::Backward, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		_camera.HandleKeyboard(Camera::Movement::Left, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		_camera.HandleKeyboard(Camera::Movement::Right, deltaTime);
	}
	//Window::HandlerInput();
	//Si pulsamos la tecla ESC cerramos la ventana
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(_glfwWindow, true);
	}
}


void Window::OnScroll(GLFWwindow* window, double xoffset, double yoffset) {
	 //Window* windowW = Window::Instance();
	 //Camera camera = windowW->_camera;
	 _camera.handleMouseScroll(yoffset);
}

void Window::OnChangeFrameBufferSize(GLFWwindow* window, const int32_t width, const int32_t height) {
	//redimension de pantalla 
	//Cambio de clip scene a view scene
	glViewport(0, 0, width, height);
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
	//_camera = Camera(posCamara);
	Window* window = Window::Instance();
	glfwMakeContextCurrent(_glfwWindow);
	glfwSetCursorPosCallback(_glfwWindow, window->OnMouse);
	glfwSetFramebufferSizeCallback(_glfwWindow, window->OnChangeFrameBufferSize);
	glfwSetScrollCallback(_glfwWindow, window->OnScroll);
	glfwSetInputMode(_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

}

Window::Window()
{
}
