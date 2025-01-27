#pragma once

#include "../GameObject.h"

class Mountain_Surface1 : public GameObject
{

private:

public:
	Mountain_Surface1();
	virtual ~Mountain_Surface1();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;

};





