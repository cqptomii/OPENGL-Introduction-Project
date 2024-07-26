#include "Scene.h"
double LastX, LastY;
double deltaTime = 0, lastFrame = 0;
Scene::Scene(int width, int heigth,std::string name,bool UseDepth): ScreenWidth(width), ScreenHeigth(heigth), UseDepth(UseDepth) {
	CreateScreen(name);
}
void Scene::DrawScene() {
	while (!glfwWindowShouldClose(this->window))
	{
		float currentTime = (float)glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		process_input(this->window);

		glClearColor(0.2f, 0.4f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Rendering


		// Buffer Swap
		glfwSwapBuffers(this->window);
		glfwPollEvents();
	}
	glfwTerminate();
}
void Scene::addObject(OBJ_TYPE type) {

}
void Scene::CreateScreen(std::string windowName) {
	if (!glfwInit()) {
		std::cout << "ERROR :: GLFW FAILED TO INITIALIZE" << std::endl;
		return;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->window = glfwCreateWindow(this->ScreenWidth, this->ScreenHeigth, windowName.c_str(), NULL, NULL);
	if (!window) {
		std::cout << "ERROR :: GFLW WINDOW CREATION FAILED" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(this->window);
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glfwSetWindowSizeCallback(this->window, window_size_callback);
	glfwSetCursorPosCallback(this->window,mouse_callback);
	glfwSetScrollCallback(this->window, scroll_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "ERROR :: GLAD SET UP FAILED " << std::endl;
		glfwTerminate();
		return;
	}
	
	if (this->UseDepth) {
		glEnable(GL_DEPTH_TEST);
	}
}
GLFWwindow* Scene::getWindow() {

}
void window_size_callback(GLFWwindow* window, int width, int heigth) {
	glViewport(0, 0, width, heigth);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (MainCamera.firstMove) {
		LastX = xpos;
		LastY = ypos;
		MainCamera.firstMove = false;
	}
	double xoffset = xpos - LastX;
	double yoffset = LastY - ypos;

	LastX = xpos;
	LastY = ypos;

	float sensivity = MainCamera.getMouseSensivity();
	
	xoffset *= sensivity;
	yoffset *= sensivity;

	MainCamera.setYaw(MainCamera.getYaw() + xoffset);
	MainCamera.setPitch(MainCamera.getPitch() + yoffset);

	MainCamera.reloadCamParameter();
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	MainCamera.setFOV(MainCamera.getFOV() + yoffset);
}
void process_input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	 }
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		MainCamera.handleCamInput(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		MainCamera.handleCamInput(RIGTH, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		MainCamera.handleCamInput(FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		MainCamera.handleCamInput(BACKWARD, deltaTime);
	}

}