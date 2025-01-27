#pragma once

#include "../GameObject.h"

class Cloud1 : public GameObject
{

private:

public:
	Cloud1();
	virtual ~Cloud1();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
};



