#pragma once

#include "../GameObject.h"

class Time : public GameObject
{

private:

public:
	Time();
	virtual ~Time();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;

};

