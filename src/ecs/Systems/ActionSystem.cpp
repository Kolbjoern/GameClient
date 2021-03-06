#include "ActionSystem.h"

#include "../../data/Actions.h"
#include "../../factories/ObjectFactory.h"
#include "../../math/VectorMath.h"

namespace ActionSystem
{
	void update(float deltaTime, int& counter,
				std::unordered_map<int, Action1Component>& act1, 
				std::unordered_map<int, PositionComponent>& pos,
				std::unordered_map<int, MotionComponent>& mot,
				std::unordered_map<int, AgeComponent>& age,
				std::unordered_map<int, ShapeComponent>& sha,
				std::unordered_map<int, HealthComponent>& hea)
	{
		int objId;
		for (std::pair<int, Action1Component> action : act1) {
			objId = action.first;

			// SHOOT BASIC
			if (action.second.id == 11) {
				if (pos.find(objId) != pos.end()) {
					act1[objId].reloadTimer += deltaTime;
					if (action.second.triggered && (action.second.reloadTimer > shootBasic.fireRate)) {
						act1[objId].reloadTimer = 0.0f;

						sf::Vector2f gunslingerPos = sf::Vector2f(pos[objId].x, pos[objId].y);
						sf::Vector2f fireDirection = action.second.vector - gunslingerPos;
						sf::Vector2f normalized = VectorMath::normalize(fireDirection);

						int projectileId = counter++;

						ObjectFactory::createProjectile(projectileId, pos, mot, age, sha, hea);
						pos[projectileId].x = gunslingerPos.x + normalized.x*25.0f;
						pos[projectileId].y = gunslingerPos.y + normalized.y*25.0f;
						mot[projectileId].direction = normalized;
						mot[projectileId].speed = shootBasic.bulletSpeed;
						age[projectileId].lifeTime = shootBasic.lifeTime;
					}
					act1[objId].triggered = false;
				}
			}
		}
	}
};
