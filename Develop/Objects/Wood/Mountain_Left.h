#pragma once

#include "../GameObject.h"

class Mountain_Left : public GameObject
{

private:

public:
	Mountain_Left();
	virtual ~Mountain_Left();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;

};


