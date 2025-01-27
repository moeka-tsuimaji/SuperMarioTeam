#pragma once

#include "../GameObject.h"

class Flag : public GameObject
{

private:

public:
	Flag();
	virtual ~Flag();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;

	virtual void OnHitCollision(GameObjectManager* hit_object) override;
};




