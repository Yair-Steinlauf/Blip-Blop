#include "HelpCommand.h"


HelpCommand::HelpCommand(Controller* controller) : m_controller(controller) {}


void HelpCommand::execute() {
    if (m_controller) {
        m_controller->switchToHelp();
    }
}