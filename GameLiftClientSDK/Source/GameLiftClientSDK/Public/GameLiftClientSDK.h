// Created by YetiTech Studios.

#pragma once

#include "ModuleManager.h"

class FGameLiftClientSDKModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	
	static void* GameLiftClientSDKLibraryHandle;
	static void* AWSCoreLibraryHandle;
	static void* CognitoIdentiryLibraryHandle;
	static bool TryLoadDependency(FString ThirdPartyDir, FString Name, void* Handle);
	static bool LoadDependency(const FString& Dir, const FString& Name, void*& Handle);
	static void FreeDependency(void*& Handle);
};