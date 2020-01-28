// Created by YetiTech Studios.

#include "GameLiftClientObject.h"
#include "GameLiftClientApi.h"
#include "GameLiftClientGlobals.h"
#include "aws/core/client/ClientConfiguration.h"



void UGameLiftClientObject::Internal_InitGameLiftClientSDK(const FString& AccessKey, const FString& Secret, const FString& Region, bool bUsingGameLiftLocal, int32 LocalPort)
{
#if WITH_GAMELIFTCLIENTSDK
	Aws::Client::ClientConfiguration ClientConfig;
	Aws::Auth::AWSCredentials Credentials;

	ClientConfig.connectTimeoutMs = 10000;
	ClientConfig.requestTimeoutMs = 10000;
	ClientConfig.region = TCHAR_TO_UTF8(*Region);
	
	bIsUsingGameLiftLocal = bUsingGameLiftLocal;

	// GameLiftLocal
	if (bUsingGameLiftLocal)
	{
		ClientConfig.scheme = Aws::Http::Scheme::HTTP;
		const FString HostAddress = FString::Printf(TEXT("localhost:%i"), LocalPort);
		ClientConfig.endpointOverride = TCHAR_TO_UTF8(*HostAddress);
		LOG_WARNING("GameLift is currently configured to use GameLift Local.");
	}

	Credentials = Aws::Auth::AWSCredentials(TCHAR_TO_UTF8(*AccessKey), TCHAR_TO_UTF8(*Secret));
	GameLiftClient = new Aws::GameLift::GameLiftClient(Credentials, ClientConfig);
#endif
}

UGameLiftClientObject* UGameLiftClientObject::CreateGameLiftObject(const FString& AccessKey, const FString& Secret, const FString& Region /*= "us-east-1"*/, bool bUsingGameLiftLocal /*= false*/, int32 LocalPort /*= 9080*/)
{
#if WITH_GAMELIFTCLIENTSDK
	UGameLiftClientObject* Proxy = NewObject<UGameLiftClientObject>();
	Proxy->Internal_InitGameLiftClientSDK(AccessKey, Secret, Region, bUsingGameLiftLocal, LocalPort);
	return Proxy;
#endif
	return nullptr;
}

UGameLiftCreateGameSession* UGameLiftClientObject::CreateGameSession(const FGameLiftCreateGameSessionConfig& CreateGameSessionConfig)
{
#if WITH_GAMELIFTCLIENTSDK
	UGameLiftCreateGameSession* Proxy = UGameLiftCreateGameSession::CreateGameSession(CreateGameSessionConfig);
	Proxy->GameLiftClient = GameLiftClient;
	return Proxy;
#endif
	return nullptr;
}

UGameLiftDescribeGameSessionDetails* UGameLiftClientObject::DescribeGameSessionDetails(const FGameLiftDescribeGameSessionDetailsConfig& DescribeGameSessionDetailsConfig)
{
#if WITH_GAMELIFTCLIENTSDK
	UGameLiftDescribeGameSessionDetails* Proxy = UGameLiftDescribeGameSessionDetails::DescribeGameSessionDetails(DescribeGameSessionDetailsConfig);
	Proxy->GameLiftClient = GameLiftClient;
	return Proxy;
#endif
	return nullptr;
}

UGameLiftCreatePlayerSession* UGameLiftClientObject::CreatePlayerSession(const FGameLiftCreatePlayerSessionConfig& CreatePlayerSessionConfig)
{
#if WITH_GAMELIFTCLIENTSDK
	UGameLiftCreatePlayerSession* Proxy = UGameLiftCreatePlayerSession::CreatePlayerSession(CreatePlayerSessionConfig);
	Proxy->GameLiftClient = GameLiftClient;
	return Proxy;
#endif
	return nullptr;
}

UGameLiftDescribeGameSessionQueues* UGameLiftClientObject::DescribeGameSessionQueues(const FGameLiftDescribeGameSessionQueuesConfig& DescribeGameSessionQueuesConfig)
{
#if WITH_GAMELIFTCLIENTSDK
	UGameLiftDescribeGameSessionQueues* Proxy = UGameLiftDescribeGameSessionQueues::DescribeGameSessionQueues(DescribeGameSessionQueuesConfig);
	Proxy->GameLiftClient = GameLiftClient;
	return Proxy;
#endif
	return nullptr;
}

UGameLiftSearchGameSessions* UGameLiftClientObject::SearchGameSessions(const FGameLiftSearchGameSessionsConfig& SearchGameSessionsConfig)
{
#if WITH_GAMELIFTCLIENTSDK
	UGameLiftSearchGameSessions* Proxy = UGameLiftSearchGameSessions::SearchGameSessions(SearchGameSessionsConfig);
	Proxy->GameLiftClient = GameLiftClient;
	return Proxy;
#endif
	return nullptr;
}

UGameLiftStartGameSessionPlacement* UGameLiftClientObject::StartGameSessionPlacement(const FGameLiftStartGameSessionPlacementConfig& StartGameSessionPlacementConfig)
{
#if WITH_GAMELIFTCLIENTSDK
	UGameLiftStartGameSessionPlacement* Proxy = UGameLiftStartGameSessionPlacement::StartGameSessionPlacement(StartGameSessionPlacementConfig);
	Proxy->GameLiftClient = GameLiftClient;
	return Proxy;
#endif
	return nullptr;
}

UGameLiftDescribeGameSessionPlacement* UGameLiftClientObject::DescribeGameSessionPlacement(const FGameLiftDescribeGameSessionPlacementConfig& DescribeGameSessionPlacementConfig)
{
#if WITH_GAMELIFTCLIENTSDK
	UGameLiftDescribeGameSessionPlacement* Proxy = UGameLiftDescribeGameSessionPlacement::DescribeGameSessionPlacement(DescribeGameSessionPlacementConfig);
	Proxy->GameLiftClient = GameLiftClient;
	return Proxy;
#endif
	return nullptr;
}
