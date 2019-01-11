#include "Window.h"


Window* Window::_window;
//const glm::vec3 posCamara = glm::vec3(0.0f, 0.0f, 3.0f);
const glm::vec3 posCamara = glm::vec3(-6.0f, 2.0f, 3.0f);
GLFWwindow* Window::_glfwWindow = 0;
Camera Window::_camera(glm::vec3(0.0f, 0.0f, 0.0f));

//Camera camera(glm::vec3(-1.0f, 2.0f, 3.0f));

bool Window::_firstMouse = true;
double Window::_lastX = 0.0f;
double Window::_lastY = 0.0f;

void Window::AddCamera(Camera camera) {
	_camera = camera;
}

Window::~Window() {
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

	double _xoffset = xpos - _lastX;
	double _yoffset = ypos - _lastY;
	_lastX = xpos;
	_lastY = ypos;
	//while (true) {
	//	cout << "dfff" << endl;
	//}
	cout << "X POS " << _lastX << " Y POS " << _lastY << endl;
	_camera.handleMouseMovement(_xoffset, _yoffset);
}


Window* Window::GetInstance(const int widht, const int height)
{
	if (_window == 0) {
		cout << "Creamos instancia de Window" << endl;
		_window = new Window(widht, height);

	}
	return _window;
}

GLFWwindow* Window::GetWindow() {
	return _glfwWindow;
}

void Window::HandlerInput(const double deltaTime) {

	if (glfwGetKey(_glfwWindow, GLFW_KEY_W) == GLFW_PRESS) {
		_camera.HandleKeyboard(Camera::Movement::Forward, deltaTime);
	}
	if (glfwGetKey(_glfwWindow, GLFW_KEY_S) == GLFW_PRESS) {
		_camera.HandleKeyboard(Camera::Movement::Backward, deltaTime);
	}
	if (glfwGetKey(_glfwWindow, GLFW_KEY_A) == GLFW_PRESS) {
		_camera.HandleKeyboard(Camera::Movement::Left, deltaTime);
	}
	if (glfwGetKey(_glfwWindow, GLFW_KEY_D) == GLFW_PRESS) {
		_camera.HandleKeyboard(Camera::Movement::Right, deltaTime);
	}
	//Si pulsamos la tecla ESC cerramos la ventana
	if (glfwGetKey(_glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
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
	glfwMakeContextCurrent(_glfwWindow);
}

Window::Window()
{
}
