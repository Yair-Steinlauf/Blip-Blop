#pragma once
#include "Subject.h"
class Observer
{
public:
    virtual ~Observer() = default;
    virtual void notify(const Subject& subject) = 0;
};