#pragma once
#include <stack>
#include <memory>
#include "UndoableCommand.h"

class CommandManager {
private:
    std::stack<std::unique_ptr<UndoableCommand>> history;

public:
    void save(std::unique_ptr<UndoableCommand> cmd);               // �� ����
    void execute(std::unique_ptr<UndoableCommand> cmd);     // ���� + ����
    void undoLast();
};
