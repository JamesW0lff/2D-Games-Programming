/*
* VGP230 2D Games programming
* STUDENT: Jaime Escobar Sanchez
* STUDENT ID: 1940022
*/

#pragma once

#include "Weapon.h"

class Handgun : public Weapon
{

public:
	// Standard Object Functions
	virtual void Load() override; 
	virtual void Unload() override;

	virtual void Render() override;

	// Weapon Specific Functions
	virtual void Fire(const X::Math::Vector2& position, const X::Math::Vector2& direction) override;
	virtual bool CanFire() override;
	virtual void Reload() override;

};

