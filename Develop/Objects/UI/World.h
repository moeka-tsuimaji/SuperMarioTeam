#pragma once

#include "../GameObject.h"

class World : public GameObject
{

private:

public:
	World();
	virtual ~World();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;

};

