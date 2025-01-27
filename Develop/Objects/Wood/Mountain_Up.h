#pragma once

#include "../GameObject.h"

class Mountain_Up : public GameObject
{

private:

public:
	Mountain_Up();
	virtual ~Mountain_Up();

	virtual void Initialize() override;
	virtual void Update(float delta_seocnd) override;
	virtual void Draw(const Vector2D& screen_offset) const override;

};








