#pragma once

#include "../GameObject.h"

class Dokan_right_up : public GameObject
{

private:

public:
	Dokan_right_up();
	virtual ~Dokan_right_up();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
};


;


;




