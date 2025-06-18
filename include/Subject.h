#pragma once
#include <vector>

class Observer;
class Subject
{
public:
    virtual ~Subject() = default;
    
    void addObserver(Observer* observer);
    
    void removeObserver(Observer* observer);
    
protected:
    void notifyObservers();
    std::vector<Observer*> m_observers;
};