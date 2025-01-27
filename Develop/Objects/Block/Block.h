#pragma once

#include "../GameObject.h"

class Block : public GameObject
{

private:

public:
	Block();
	virtual ~Block();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;

	virtual void OnHitCollision(GameObjectManager* hit_object) override;
};

