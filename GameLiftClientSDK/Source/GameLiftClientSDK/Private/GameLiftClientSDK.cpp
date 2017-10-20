// Created by YetiTech Studios.

#include "GameLiftClientSDK.h"
#include "GameLiftClientGlobals.h"
#include "Core.h"
#include "ModuleManager.h"
#include "IPluginManager.h"

#define LOCTEXT_NAMESPACE "FGameLiftClientSDKModule"

void* FGameLiftClientSDKModule::AWSCoreLibraryHandle = nullptr;
void* FGameLiftClientSDKModule::GameLiftClientSDKLibraryHandle = nullptr;
void* FGameLiftClientSDKModule::CognitoIdentiryLibraryHandle = nullptr;

void FGameLiftClientSDKModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
#if PLATFORM_WINDOWS
	LOG_NORMAL("Starting GameLiftClient Module...");
	// Get the base directory of this plugin
	const FString BaseDir = IPluginManager::Get().FindPlugin("GameLiftClientSDK")->GetBaseDir();
	LOG_NORMAL(FString::Printf(TEXT("Base directory is %s"), *BaseDir));

	// Add on the relative location of the third party dll and load it
	const FString ThirdPartyDir = FPaths::Combine(*BaseDir, TEXT("ThirdParty"));
	LOG_NORMAL(FString::Printf(TEXT("ThirdParty directory is %s"), *ThirdPartyDir));

	TryLoadDependency(ThirdPartyDir, TEXT("aws-cpp-sdk-core"), AWSCoreLibraryHandle);
	TryLoadDependency(ThirdPartyDir, TEXT("aws-cpp-sdk-gamelift"), GameLiftClientSDKLibraryHandle);
	TryLoadDependency(ThirdPartyDir, TEXT("aws-cpp-sdk-cognito-identity"), CognitoIdentiryLibraryHandle);
#endif
}

void FGameLiftClientSDKModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	FreeDependency(AWSCoreLibraryHandle);
	FreeDependency(GameLiftClientSDKLibraryHandle);
	FreeDependency(CognitoIdentiryLibraryHandle);
}

bool FGameLiftClientSDKModule::TryLoadDependency(FString ThirdPartyDir, FString Name, void* Handle)
{
	const bool bDependencyLoaded = LoadDependency(ThirdPartyDir, Name, Handle);
	if (!bDependencyLoaded)
	{
		FFormatNamedArguments Arguments;
		Arguments.Add(TEXT("Name"), FText::FromString(Name));
		FMessageDialog::Open(EAppMsgType::Ok, FText::Format(LOCTEXT("LoadDependencyError", "Failed to load {Name}."), Arguments));
		FreeDependency(Handle);
	}
	return bDependencyLoaded;
}

bool FGameLiftClientSDKModule::LoadDependency(const FString& Dir, const FString& Name, void*& Handle)
{
	FString Lib = Name + TEXT(".") + FPlatformProcess::GetModuleExtension();
	FString Path = Dir.IsEmpty() ? *Lib : FPaths::Combine(*Dir, *Lib);

	Handle = FPlatformProcess::GetDllHandle(*Path);

	if (Handle == nullptr)
	{		
		LOG_ERROR(FString::Printf(TEXT("Dependency %s failed to load in directory %s"), *Name, *Dir));
		return false;
	}

	LOG_NORMAL(FString::Printf(TEXT("Dependency %s successfully loaded from directory %s"), *Name, *Dir));
	return true;
}

void FGameLiftClientSDKModule::FreeDependency(void*& Handle)
{
#if !PLATFORM_LINUX
	if (Handle != nullptr)
	{
		FPlatformProcess::FreeDllHandle(Handle);
		Handle = nullptr;
	}
#endif
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGameLiftClientSDKModule, GameLiftClientSDK)
