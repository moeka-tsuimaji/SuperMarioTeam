#pragma once

#include "../GameObject.h"

class Mountain_Surface : public GameObject
{

private:

public:
	Mountain_Surface();
	virtual ~Mountain_Surface();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;

};




