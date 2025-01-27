#pragma once

#include "../GameObject.h"

class Pole_down : public GameObject
{

private:

public:
	Pole_down();
	virtual ~Pole_down();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;

	virtual void OnHitCollision(GameObjectManager* hit_object) override;

};




