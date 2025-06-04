#include "BaseScreen.h"

BaseScreen::BaseScreen(sf::RenderWindow* window)
	:m_window(window)
{

}

void BaseScreen::draw()
{
	m_window->draw(m_background);
}
