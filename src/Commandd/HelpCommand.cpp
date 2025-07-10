#include "HelpCommand.h"


void HelpCommand::execute() {
    if (m_controller) {
        m_controller->switchToHelp();
    }
}