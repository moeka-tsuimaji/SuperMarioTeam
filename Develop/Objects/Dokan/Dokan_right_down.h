#pragma once

#include "../GameObject.h"

class Dokan_right_down : public GameObject
{

private:

public:
	Dokan_right_down();
	virtual ~Dokan_right_down();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
};


;


;



