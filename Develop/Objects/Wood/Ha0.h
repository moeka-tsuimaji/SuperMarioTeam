#pragma once

#include "../GameObject.h"

class Ha0 : public GameObject
{

private:

public:
	Ha0();
	virtual ~Ha0();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;

};



