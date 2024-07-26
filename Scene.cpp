#include "Scene.h"

Scene::Scene(int width, int heigth,std::string name,bool UseDepth): ScreenWidth(width), ScreenHeigth(heigth), UseDepth(UseDepth) {
	CreateScreen(name);
}
void Scene::DrawScene() {
	while (!glfwWindowShouldClose(this->window))
	{
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
float Scene::getMouseSensivity() {

}
void window_size_callback(GLFWwindow* window, int width, int heigth) {
	glViewport(0, 0, width, heigth);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {

}
void process_input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	 }
}