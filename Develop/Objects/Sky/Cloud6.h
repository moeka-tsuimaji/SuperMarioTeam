#pragma once

#include "../GameObject.h"

class Cloud6 : public GameObject
{

private:

public:
	Cloud6();
	virtual ~Cloud6();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;

};





