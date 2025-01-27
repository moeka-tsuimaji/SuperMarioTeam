#pragma once

#include "../GameObject.h"

class Mountain_Right : public GameObject
{

private:

public:
	Mountain_Right();
	virtual ~Mountain_Right();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;

};



