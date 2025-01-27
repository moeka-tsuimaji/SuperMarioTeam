#pragma once

#include "../GameObject.h"

class Mountain_Surface2 : public GameObject
{

private:

public:
	Mountain_Surface2();
	virtual ~Mountain_Surface2();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;

};






