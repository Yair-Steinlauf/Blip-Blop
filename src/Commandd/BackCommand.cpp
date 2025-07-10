#include "BackCommand.h"

void BackCommand::execute() {
    if (m_controller) {
        m_controller->backCommand();
    }
}