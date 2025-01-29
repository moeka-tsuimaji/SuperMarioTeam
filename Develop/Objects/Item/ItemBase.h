
/*

#pragma once

#include "../GameObjectManager.h"

class PickupItem : public GameObjectManager
{
protected:
    float floating_speed;   // Speed of the item's vertical float
    float float_amplitude;  // Amplitude of the item's floating
    float float_offset;     // Offset for each item's floating.
public:
    PickupItem();
    ~PickupItem() override;

    virtual void Initialize() override;
    virtual void Update(float delta_second) override;
    virtual void OnHitCollision(GameObjectManager* hit_object) override;
    virtual void ApplyEffect(class Player* player) = 0;

    void SetFloatingSpeed(float speed);
    void SetFloatAmplitude(float amplitude);
    void SetFloatOffset(float offset);

};


*/