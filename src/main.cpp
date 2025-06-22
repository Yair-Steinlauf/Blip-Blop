#include <iostream>
#include "Controller.h"
#include <GameAnimations.h>
int main()
{
	try {
		GameAnimations::initializeFrames();

		Controller controller;
		controller.run();
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Unknown exception occurred." << std::endl;
	}
}
