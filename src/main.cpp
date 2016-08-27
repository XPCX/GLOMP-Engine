#include "system.hpp"
#include "control.hpp"
#include "math.hpp"
#include "main.hpp"

#include <iostream>

#include "omp.h"
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

int main(int argc, const char **argv) {
	using namespace Util;

	glfwInit();
	std::atomic_bool alive(true);
	Control::control ctl(alive, "share/test.obj",
			"share/fallback.vert", "share/shade.frag");
	task::init(alive, &ctl);
	task::run(alive, &ctl);
	glfwTerminate();

	return 0;
}
