#include "CommandManager.h"

void CommandManager::save(std::unique_ptr<UndoableCommand> cmd) {
    if (cmd)
        history.push(std::move(cmd));
}

void CommandManager::execute(std::unique_ptr<UndoableCommand> cmd) {
    if (cmd) {
        cmd->execute();
        history.push(std::move(cmd));
    }
}

void CommandManager::undoLast() {
    if (!history.empty()) {
        history.top()->undo();
        history.pop();
    }
}
