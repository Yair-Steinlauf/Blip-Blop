#include "Movment/GunState.h"
#include "Movment/MoveComponent.h"
GunState::GunState(MoveComponent& moveComponent)
	: m_moveComponent(moveComponent)
{
}
