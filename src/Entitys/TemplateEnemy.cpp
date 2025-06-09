#include "TemplateEnemy.h"
#include "EnemyMovmentState.h"


static auto regTemplateEnemy = Factory<BaseEnemy>::instance().registerType(
	ObjectType::Dinosaur,
	[]() -> std::unique_ptr<BaseEnemy>
	{
		// ===================================Dinosaur Movment!====Type = dinosaur=======
		return std::make_unique<TemplateEnemy<EnemyMovementState>>(ObjectType::Dinosaur); //, AttackStrategy>();
	}
);