#pragma once

#include "../GameObject.h"

class Cloud3 : public GameObject
{

private:

public:
	Cloud3();
	virtual ~Cloud3();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;

};





