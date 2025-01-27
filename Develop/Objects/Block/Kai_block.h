#pragma once

#include "../GameObject.h"

class Kai_block : public GameObject
{

private:

public:
	Kai_block();
	virtual ~Kai_block();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;

	virtual void OnHitCollision(GameObjectManager* hit_object) override;
};



