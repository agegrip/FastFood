#pragma once
#include "Game\Common\DeviceResources.h"

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual void Initialize() = 0;
	virtual void Update(float elapsedTime) = 0;
	virtual void Render() = 0;
	virtual void Finalize() = 0;
};