#pragma once

#include "../GameObject.h"

class Sora : public GameObject
{

private:

public:
	Sora();
	virtual ~Sora();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;

};



