#pragma once

#include "../GameObject.h"

class Cloud4 : public GameObject
{

private:

public:
	Cloud4();
	virtual ~Cloud4();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;

};





