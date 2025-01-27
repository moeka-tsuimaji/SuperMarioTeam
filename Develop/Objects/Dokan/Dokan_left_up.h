#pragma once

#include "../GameObject.h"

class Dokan_left_up : public GameObject
{

private:

public:
	Dokan_left_up();
	virtual ~Dokan_left_up();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
};


;


;

