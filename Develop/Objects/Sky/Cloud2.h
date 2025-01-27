#pragma once

#include "../GameObject.h"

class Cloud2 : public GameObject
{

private:

public:
	Cloud2();
	virtual ~Cloud2();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;

};





