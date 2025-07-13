#include "ExitCommand.h"



ExitCommand::ExitCommand(Controller* controller) : m_controller(controller) {}


void ExitCommand::execute() {
	if (m_controller) {
		m_controller->closeGame();
	}
}