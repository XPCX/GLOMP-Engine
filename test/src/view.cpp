#define GLFW_INCLUDE_NONE
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include "view.hpp"
#include <iostream>

#ifndef GLFW_TRUE
#define GLFW_TRUE 1
#endif
#ifndef GLFW_FALSE
#define GLFW_FALSE 0
#endif

int main(int argc, const char **argv) {
	using namespace View;
	if(glfwInit() == GLFW_FALSE) {
		std::cout << "Failed to initialize GLFW "
			<< glfwGetVersionString() << std::endl;
		return 1;
	} else {
		std::atomic_bool alive(true);
		view v(alive);
		if(alive) {
			v.setProg(alive, "share/shade.vert", "share/shade.frag");
		} else {
			std::cout << "Failed to construct view." << std::endl;
		}
		if(alive) v.init(alive);
		else {
			std::cout << "Failed to initialize view." << std::endl;
			return 1;
		}
		if(alive) v.run(alive);
		//glfwTerminate();
	}
}
