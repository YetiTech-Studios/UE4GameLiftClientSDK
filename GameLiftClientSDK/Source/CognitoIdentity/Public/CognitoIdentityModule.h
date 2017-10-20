#pragma once

#include "ModuleManager.h"

class CognitoIdentityModuleImpl : public IModuleInterface
{
public:
	void StartupModule();
	void ShutdownModule();

private:
};