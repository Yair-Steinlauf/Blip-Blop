#include "Subject.h"
#include "Observer.h"

void Subject::addObserver(Observer* observer)
{
    m_observers.push_back(observer);

}

void Subject::removeObserver(Observer* observer)
{
    m_observers.erase(
        std::remove(m_observers.begin(), m_observers.end(), observer),
        m_observers.end()
    );
}

void Subject::notifyObservers()
{
    for (Observer* observer : m_observers)
    {
        observer->notify(*this);
    }
}
