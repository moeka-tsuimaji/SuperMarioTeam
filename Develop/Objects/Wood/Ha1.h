#pragma once

#include "../GameObject.h"

class Ha1 : public GameObject
{

private:

public:
	Ha1();
	virtual ~Ha1();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;

};




