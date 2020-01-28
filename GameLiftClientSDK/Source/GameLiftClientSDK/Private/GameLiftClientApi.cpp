// Created by YetiTech Studios.

#include "GameLiftClientApi.h"
#include "GameLiftClientGlobals.h"

#if WITH_GAMELIFTCLIENTSDK
#include "aws/gamelift/model/DescribeGameSessionDetailsRequest.h"
#include "aws/gamelift/GameLiftClient.h"
#include "aws/core/utils/Outcome.h"
#include "aws/core/auth/AWSCredentialsProvider.h"
#include "aws/gamelift/model/GameProperty.h"
#include "aws/gamelift/model/SearchGameSessionsRequest.h"
#include "aws/gamelift/model/CreatePlayerSessionRequest.h"
#include "aws/gamelift/model/CreateGameSessionRequest.h"
#include "aws/gamelift/model/DescribeGameSessionQueuesRequest.h"
#include "aws/gamelift/model/SearchGameSessionsRequest.h"
#include "aws/gamelift/model/StartGameSessionPlacementRequest.h"
#include "aws/gamelift/model/DescribeGameSessionPlacementRequest.h"
#include "aws/gamelift/model/PlayerSessionStatus.h"
#include "aws/gamelift/model/GameSessionStatus.h"
#include "aws/gamelift/model/GameSessionPlacementState.h"
#include <aws/core/http/HttpRequest.h>
#endif

UGameLiftCreateGameSession* UGameLiftCreateGameSession::CreateGameSession(const FGameLiftCreateGameSessionConfig& CreateGameSessionConfig)
{
#if WITH_GAMELIFTCLIENTSDK
	UGameLiftCreateGameSession* Proxy = NewObject<UGameLiftCreateGameSession>();
	Proxy->CreateGameSessionConfig = &CreateGameSessionConfig;
	return Proxy;
#endif
	return nullptr;
}

EActivateStatus UGameLiftCreateGameSession::Activate()
{
#if WITH_GAMELIFTCLIENTSDK
	if (GameLiftClient)
	{
		LOG_NORMAL("Preparing to create game session...");

		FString FleetId = CreateGameSessionConfig->GetFleetId();
		FString AliasId = CreateGameSessionConfig->GetAliasId();
		int MaxPlayerCount = CreateGameSessionConfig->GetMaxPlayerCount();
		TMap<FString, FString> GameProperties = CreateGameSessionConfig->GetGameProperties();
		FString Name = CreateGameSessionConfig->GetName();
		FString IdempotencyToken = CreateGameSessionConfig->GetIdempotencyToken();
		FString GameSessionData = CreateGameSessionConfig->GetGameSessionData();

		if (OnCreateGameSessionSuccess.IsBound() == false)
		{
			LOG_ERROR("No functions were bound to OnCreateGameSessionSuccess multi-cast delegate! Aborting Activate.");
			return EActivateStatus::ACTIVATE_NoSuccessCallback;
		}

		if (OnCreateGameSessionFailed.IsBound() == false)
		{
			LOG_ERROR("No functions were bound to OnCreateGameSessionFailed multi-cast delegate! Aborting Activate.");
			return EActivateStatus::ACTIVATE_NoFailCallback;
		}

		Aws::GameLift::Model::CreateGameSessionRequest GameSessionRequest;

		GameSessionRequest.SetMaximumPlayerSessionCount(MaxPlayerCount);
		
		if (FleetId.Len() > 0)
		{
			LOG_NORMAL("Setting Fleet Id " + FleetId);
			GameSessionRequest.SetFleetId(TCHAR_TO_UTF8(*FleetId));
		}
		if (AliasId.Len() > 0)
		{
			LOG_NORMAL("Setting Alias Id " + AliasId);
			GameSessionRequest.SetAliasId(TCHAR_TO_UTF8(*AliasId));
		}

		for (auto& Property : GameProperties)
		{
			LOG_NORMAL("********************************************************************");
			Aws::GameLift::Model::GameProperty MapProperty;
			MapProperty.SetKey(TCHAR_TO_UTF8(*Property.Key));
			MapProperty.SetValue(TCHAR_TO_UTF8(*Property.Value));
			GameSessionRequest.AddGameProperties(MapProperty);
			LOG_NORMAL(FString::Printf(TEXT("New GameProperty added. Key: (%s) Value: (%s)"), *Property.Key, *Property.Value));
		}

		if (Name.Len() > 0)
		{
			LOG_NORMAL("Setting Name " + Name);
			GameSessionRequest.SetName(TCHAR_TO_UTF8(*Name));
		}

		if (IdempotencyToken.Len() > 0)
		{
			LOG_NORMAL("Setting Idempotency Token " + IdempotencyToken);
			GameSessionRequest.SetIdempotencyToken(TCHAR_TO_UTF8(*IdempotencyToken));
		}

		if (GameSessionData.Len() > 0)
		{
			LOG_NORMAL("Setting Game Session Data " + GameSessionData);
			GameSessionRequest.SetGameSessionData(TCHAR_TO_UTF8(*GameSessionData));
		}

		// TODO: FIND A BETTER WAY TO PARAMETERIZE GAMELIFT LOCAL

		Aws::GameLift::CreateGameSessionResponseReceivedHandler Handler;
		Handler = std::bind(&UGameLiftCreateGameSession::OnCreateGameSession, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);

		LOG_NORMAL("Starting game session...");
		GameLiftClient->CreateGameSessionAsync(GameSessionRequest, Handler);
		return EActivateStatus::ACTIVATE_Success;
	}
	LOG_ERROR("GameLiftClient is null. Did you call CreateGameLiftObject first?");	
#endif
	return EActivateStatus::ACTIVATE_NoGameLift;
}

void UGameLiftCreateGameSession::OnCreateGameSession(const Aws::GameLift::GameLiftClient* Client, const Aws::GameLift::Model::CreateGameSessionRequest& Request, const Aws::GameLift::Model::CreateGameSessionOutcome& Outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& Context)
{
#if WITH_GAMELIFTCLIENTSDK
	if (Outcome.IsSuccess())
	{
		LOG_NORMAL("Received OnCreateGameSession with Success outcome.");
		Aws::GameLift::Model::GameSession GameSession = Outcome.GetResult().GetGameSession();

		const FString GameSessionId = GameSession.GetGameSessionId().c_str();
		Aws::GameLift::Model::GameSessionStatus Status = GameSession.GetStatus();
		const FString GameSessionStatus = Aws::GameLift::Model::GameSessionStatusMapper::GetNameForGameSessionStatus(Status).c_str();
		const int CurrentPlayerCount = GameSession.GetCurrentPlayerSessionCount();
		const int MaxPlayerCount = GameSession.GetMaximumPlayerSessionCount();
		Aws::GameLift::Model::PlayerSessionCreationPolicy CreationPolicy = GameSession.GetPlayerSessionCreationPolicy();
		const FString PlayerSessionCreationPolicy = Aws::GameLift::Model::PlayerSessionCreationPolicyMapper::GetNameForPlayerSessionCreationPolicy(CreationPolicy).c_str();
		TMap<FString, FString> GameProperties;
		const Aws::Vector<Aws::GameLift::Model::GameProperty> GameLiftGameProperties = GameSession.GetGameProperties();

		for (Aws::GameLift::Model::GameProperty GameProperty : GameLiftGameProperties) {
			GameProperties.Add(GameProperty.GetKey().c_str(), GameProperty.GetValue().c_str());
		}

		const FString ServerIpAddress = GameSession.GetIpAddress().c_str();
		const FString ServerPort = FString::FromInt(GameSession.GetPort());
		const FString ServerDnsName = GameSession.GetDnsName().c_str();
		const FString GameSessionData = GameSession.GetGameSessionData().c_str();
		const FString MatchmakerData = GameSession.GetMatchmakerData().c_str();
		const FString Name = GameSession.GetName().c_str();

		FGameLiftGameSessionDetail GameSessionDetail;
		GameSessionDetail.SetGameSessionId(GameSessionId);
		GameSessionDetail.SetGameSessionStatus(GameSessionStatus);
		GameSessionDetail.SetCurrentPlayerCount(CurrentPlayerCount);
		GameSessionDetail.SetMaxPlayerCount(MaxPlayerCount);
		GameSessionDetail.SetPlayerSessionCreationPolicy(PlayerSessionCreationPolicy);
		GameSessionDetail.SetGameProperties(GameProperties);
		GameSessionDetail.SetServerIpAddress(ServerIpAddress);
		GameSessionDetail.SetServerPort(ServerPort);
		GameSessionDetail.SetServerDnsName(ServerDnsName);
		GameSessionDetail.SetGameSessionData(GameSessionData);
		GameSessionDetail.SetMatchmakerData(MatchmakerData);
		GameSessionDetail.SetName(Name);

		FGameLiftCreateGameSessionResult CreateGameSessionResult;
		CreateGameSessionResult.SetGameSessionDetail(GameSessionDetail);
		OnCreateGameSessionSuccess.Broadcast(CreateGameSessionResult);
	}
	else
	{
		const FString MyErrorMessage = FString(Outcome.GetError().GetMessage().c_str());
		LOG_ERROR("Received OnCreateGameSession with failed outcome. Error: " + MyErrorMessage);
		OnCreateGameSessionFailed.Broadcast(MyErrorMessage);
	}
#endif
}

UGameLiftDescribeGameSessionDetails* UGameLiftDescribeGameSessionDetails::DescribeGameSessionDetails(const FGameLiftDescribeGameSessionDetailsConfig& DescribeGameSessionDetailsConfig)
{
#if WITH_GAMELIFTCLIENTSDK
	UGameLiftDescribeGameSessionDetails* Proxy = NewObject<UGameLiftDescribeGameSessionDetails>();
	Proxy->DescribeGameSessionDetailsConfig = &DescribeGameSessionDetailsConfig;
	return Proxy;
#endif
	return nullptr;
}

EActivateStatus UGameLiftDescribeGameSessionDetails::Activate()
{
#if WITH_GAMELIFTCLIENTSDK
	if (GameLiftClient)
	{
		LOG_NORMAL("Preparing to describe game session...");

		FString GameSessionId = DescribeGameSessionDetailsConfig->GetGameSessionId();
		FString FleetId = DescribeGameSessionDetailsConfig->GetFleetId();
		FString AliasId = DescribeGameSessionDetailsConfig->GetAliasId();
		FString StatusFilter = DescribeGameSessionDetailsConfig->GetStatusFilter();

		if (OnDescribeGameSessionDetailsSuccess.IsBound() == false)
		{
			LOG_ERROR("No functions were bound to OnDescribeGameSessionDetailsSuccess multi-cast delegate! Aborting Activate.");
			return EActivateStatus::ACTIVATE_NoSuccessCallback;
		}

		if (OnDescribeGameSessionDetailsFailed.IsBound() == false)
		{
			LOG_ERROR("No functions were bound to OnDescribeGameSessionDetailsFailed multi-cast delegate! Aborting Activate.");
			return EActivateStatus::ACTIVATE_NoFailCallback;
		}

		Aws::GameLift::Model::DescribeGameSessionDetailsRequest Request;
		if (GameSessionId.Len() > 0) {
			LOG_NORMAL("Setting game session ID: " + GameSessionId);
			Request.SetGameSessionId(TCHAR_TO_UTF8(*GameSessionId));
		}

		if (FleetId.Len() > 0) {
			LOG_NORMAL("Setting Fleet ID: " + FleetId);
			Request.SetFleetId(TCHAR_TO_UTF8(*FleetId));
		}

		if (AliasId.Len() > 0) {
			LOG_NORMAL("Setting Alias ID: " + AliasId);
			Request.SetAliasId(TCHAR_TO_UTF8(*AliasId));
		}

		if (StatusFilter.Len() > 0) {
			LOG_NORMAL("Setting Status Filter: " + StatusFilter);
			Request.SetStatusFilter(TCHAR_TO_UTF8(*StatusFilter));
		}

		Aws::GameLift::DescribeGameSessionDetailsResponseReceivedHandler Handler;
		Handler = std::bind(&UGameLiftDescribeGameSessionDetails::OnDescribeGameSessionDetails, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);

		LOG_NORMAL("Requesting to describe game session with ID: " + GameSessionId);
		GameLiftClient->DescribeGameSessionDetailsAsync(Request, Handler);
		return EActivateStatus::ACTIVATE_Success;
	}
	LOG_ERROR("GameLiftClient is null. Did you call CreateGameLiftObject first?");
#endif
	return EActivateStatus::ACTIVATE_NoGameLift;
}

void UGameLiftDescribeGameSessionDetails::OnDescribeGameSessionDetails(const Aws::GameLift::GameLiftClient* Client, const Aws::GameLift::Model::DescribeGameSessionDetailsRequest& Request, const Aws::GameLift::Model::DescribeGameSessionDetailsOutcome& Outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& Context)
{
#if WITH_GAMELIFTCLIENTSDK
	if (Outcome.IsSuccess())
	{
		LOG_NORMAL("Received OnDescribeGameSessionDetails with Success outcome.");
		TArray<FGameLiftGameSessionDetail> GameSessionDetails;
		for (Aws::GameLift::Model::GameSessionDetail GameLiftGameSessionDetail : Outcome.GetResult().GetGameSessionDetails()) {
			Aws::GameLift::Model::ProtectionPolicy GameLiftProtectionPolicy = GameLiftGameSessionDetail.GetProtectionPolicy();
			const FString ProtectionPolicy = Aws::GameLift::Model::ProtectionPolicyMapper::GetNameForProtectionPolicy(GameLiftProtectionPolicy).c_str();
			const Aws::GameLift::Model::GameSession GameSession = GameLiftGameSessionDetail.GetGameSession();

			const FString GameSessionId = GameSession.GetGameSessionId().c_str();
			Aws::GameLift::Model::GameSessionStatus Status = GameSession.GetStatus();
			const FString GameSessionStatus = Aws::GameLift::Model::GameSessionStatusMapper::GetNameForGameSessionStatus(Status).c_str();
			const int CurrentPlayerCount = GameSession.GetCurrentPlayerSessionCount();
			const int MaxPlayerCount = GameSession.GetMaximumPlayerSessionCount();
			Aws::GameLift::Model::PlayerSessionCreationPolicy CreationPolicy = GameSession.GetPlayerSessionCreationPolicy();
			const FString PlayerSessionCreationPolicy = Aws::GameLift::Model::PlayerSessionCreationPolicyMapper::GetNameForPlayerSessionCreationPolicy(CreationPolicy).c_str();
			TMap<FString, FString> GameProperties;
			const Aws::Vector<Aws::GameLift::Model::GameProperty> GameLiftGameProperties = GameSession.GetGameProperties();

			for (Aws::GameLift::Model::GameProperty GameProperty : GameLiftGameProperties) {
				GameProperties.Add(GameProperty.GetKey().c_str(), GameProperty.GetValue().c_str());
			}

			const FString ServerIpAddress = GameSession.GetIpAddress().c_str();
			const FString ServerPort = FString::FromInt(GameSession.GetPort());
			const FString ServerDnsName = GameSession.GetDnsName().c_str();
			const FString GameSessionData = GameSession.GetGameSessionData().c_str();
			const FString MatchmakerData = GameSession.GetMatchmakerData().c_str();
			const FString Name = GameSession.GetName().c_str();

			FGameLiftGameSessionDetail GameSessionDetail;
			GameSessionDetail.SetGameSessionId(GameSessionId);
			GameSessionDetail.SetGameSessionStatus(GameSessionStatus);
			GameSessionDetail.SetCurrentPlayerCount(CurrentPlayerCount);
			GameSessionDetail.SetMaxPlayerCount(MaxPlayerCount);
			GameSessionDetail.SetPlayerSessionCreationPolicy(PlayerSessionCreationPolicy);
			GameSessionDetail.SetGameProperties(GameProperties);
			GameSessionDetail.SetServerIpAddress(ServerIpAddress);
			GameSessionDetail.SetServerPort(ServerPort);
			GameSessionDetail.SetServerDnsName(ServerDnsName);
			GameSessionDetail.SetGameSessionData(GameSessionData);
			GameSessionDetail.SetMatchmakerData(MatchmakerData);
			GameSessionDetail.SetProtectionPolicy(ProtectionPolicy);
			GameSessionDetail.SetName(Name);

			GameSessionDetails.Add(GameSessionDetail);
		}
		
		FGameLiftDescribeGameSessionDetailsResult DescribeGameSessionDetailsResult;
		DescribeGameSessionDetailsResult.SetGameSessionDetails(GameSessionDetails);
		
		OnDescribeGameSessionDetailsSuccess.Broadcast(DescribeGameSessionDetailsResult);
	}
	else
	{
		const FString MyErrorMessage = FString(Outcome.GetError().GetMessage().c_str());
		LOG_ERROR("Received OnDescribeGameSessionDetails with failed outcome. Error: " + MyErrorMessage);
		OnDescribeGameSessionDetailsFailed.Broadcast(MyErrorMessage);
	}
#endif
}

UGameLiftCreatePlayerSession* UGameLiftCreatePlayerSession::CreatePlayerSession(const FGameLiftCreatePlayerSessionConfig& CreatePlayerSessionConfig)
{
#if WITH_GAMELIFTCLIENTSDK
	UGameLiftCreatePlayerSession* Proxy = NewObject<UGameLiftCreatePlayerSession>();
	Proxy->CreatePlayerSessionConfig = &CreatePlayerSessionConfig;
	return Proxy;
#endif
	return nullptr;
}

EActivateStatus UGameLiftCreatePlayerSession::Activate()
{
#if WITH_GAMELIFTCLIENTSDK
	if (GameLiftClient)
	{		
		LOG_NORMAL("Preparing to create player session...");

		FString GameSessionId = CreatePlayerSessionConfig->GetGameSessionId();
		FString PlayerId = CreatePlayerSessionConfig->GetPlayerId();
		FString PlayerData = CreatePlayerSessionConfig->GetPlayerData();

		if (OnCreatePlayerSessionSuccess.IsBound() == false)
		{
			LOG_ERROR("No functions were bound to OnCreatePlayerSessionSuccess multi-cast delegate! Aborting Activate.");
			return EActivateStatus::ACTIVATE_NoSuccessCallback;
		}

		if (OnCreatePlayerSessionFailed.IsBound() == false)
		{
			LOG_ERROR("No functions were bound to OnCreatePlayerSessionFailed multi-cast delegate! Aborting Activate.");
			return EActivateStatus::ACTIVATE_NoFailCallback;
		}

		Aws::GameLift::Model::CreatePlayerSessionRequest Request;
		LOG_NORMAL("Create player session game session ID: " + GameSessionId);
		if (GameSessionId.Len() > 0) {
			LOG_NORMAL("Setting game session ID: " + GameSessionId);
			Request.SetGameSessionId(TCHAR_TO_UTF8(*GameSessionId));
		}
		if (PlayerId.Len() > 0) {
			LOG_NORMAL("Setting player ID: " + PlayerId);
			Request.SetPlayerId(TCHAR_TO_UTF8(*PlayerId));
		}
		if (PlayerData.Len() > 0) {
			LOG_NORMAL("Setting player data: " + PlayerData);
			Request.SetPlayerData(TCHAR_TO_UTF8(*PlayerData));
		}
		
		Aws::GameLift::CreatePlayerSessionResponseReceivedHandler Handler;
		Handler = std::bind(&UGameLiftCreatePlayerSession::OnCreatePlayerSession, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);

		LOG_NORMAL("Creating new player session...");
		GameLiftClient->CreatePlayerSessionAsync(Request, Handler);
		return EActivateStatus::ACTIVATE_Success;
	}
	LOG_ERROR("GameLiftClient is null. Did you call CreateGameLiftObject first?");
#endif
	return EActivateStatus::ACTIVATE_NoGameLift;
}

void UGameLiftCreatePlayerSession::OnCreatePlayerSession(const Aws::GameLift::GameLiftClient* Client, const Aws::GameLift::Model::CreatePlayerSessionRequest& Request, const Aws::GameLift::Model::CreatePlayerSessionOutcome& Outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& Context)
{
#if WITH_GAMELIFTCLIENTSDK
	if (Outcome.IsSuccess())
	{
		LOG_NORMAL("Received OnCreatePlayerSession with Success outcome.");
		Aws::GameLift::Model::PlayerSession PlayerSession = Outcome.GetResult().GetPlayerSession();
		const FString ServerIpAddress = PlayerSession.GetIpAddress().c_str();
		const FString ServerPort = FString::FromInt(PlayerSession.GetPort());
		const FString ServerDnsName = PlayerSession.GetDnsName().c_str();
		const FString PlayerSessionId = PlayerSession.GetPlayerSessionId().c_str();
		Aws::GameLift::Model::PlayerSessionStatus Status = PlayerSession.GetStatus();
		const FString PlayerSessionStatus = Aws::GameLift::Model::PlayerSessionStatusMapper::GetNameForPlayerSessionStatus(Status).c_str();
		const FString PlayerId = PlayerSession.GetPlayerId().c_str();
		const FString PlayerData = PlayerSession.GetPlayerData().c_str();
		const FString GameSessionId = PlayerSession.GetGameSessionId().c_str();

		FGameLiftPlayerSessionDetail PlayerSessionDetail;
		PlayerSessionDetail.SetServerIpAddress(ServerIpAddress);
		PlayerSessionDetail.SetServerPort(ServerPort);
		PlayerSessionDetail.SetServerDnsName(ServerDnsName);
		PlayerSessionDetail.SetPlayerSessionId(PlayerSessionId);
		PlayerSessionDetail.SetPlayerSessionStatus(PlayerSessionStatus);
		PlayerSessionDetail.SetPlayerId(PlayerId);
		PlayerSessionDetail.SetPlayerData(PlayerData);
		PlayerSessionDetail.SetGameSessionId(GameSessionId);

		FGameLiftCreatePlayerSessionResult CreatePlayerSessionResult;
		CreatePlayerSessionResult.SetPlayerSessionDetail(PlayerSessionDetail);
		OnCreatePlayerSessionSuccess.Broadcast(CreatePlayerSessionResult);
	}
	else
	{
		const FString MyErrorMessage = FString(Outcome.GetError().GetMessage().c_str());
		LOG_ERROR("Received OnCreatePlayerSession with failed outcome. Error: " + MyErrorMessage);
		OnCreatePlayerSessionFailed.Broadcast(MyErrorMessage);
	}
#endif
}

UGameLiftDescribeGameSessionQueues* UGameLiftDescribeGameSessionQueues::DescribeGameSessionQueues(const FGameLiftDescribeGameSessionQueuesConfig& DescribeGameSessionQueuesConfig)
{
#if WITH_GAMELIFTCLIENTSDK
	UGameLiftDescribeGameSessionQueues* Proxy = NewObject<UGameLiftDescribeGameSessionQueues>();
	Proxy->DescribeGameSessionQueuesConfig = &DescribeGameSessionQueuesConfig;
	return Proxy;
#endif
	return nullptr;
}

EActivateStatus UGameLiftDescribeGameSessionQueues::Activate()
{
#if WITH_GAMELIFTCLIENTSDK
	if (GameLiftClient)
	{
		LOG_NORMAL("Preparing to search for fleets associated with a queue...");
		TArray<FString> QueueNames = DescribeGameSessionQueuesConfig->GetQueueNames();

		if (OnDescribeGameSessionQueuesSuccess.IsBound() == false)
		{
			LOG_ERROR("No functions were bound to OnDescribeGameSessionQueuesSuccess multi-cast delegate! Aborting Activate.");
			return EActivateStatus::ACTIVATE_NoSuccessCallback;
		}

		if (OnDescribeGameSessionQueuesFailed.IsBound() == false)
		{
			LOG_ERROR("No functions were bound to OnDescribeGameSessionQueuesFailed multi-cast delegate! Aborting Activate.");
			return EActivateStatus::ACTIVATE_NoFailCallback;
		}

		Aws::GameLift::Model::DescribeGameSessionQueuesRequest Request;
		std::vector<Aws::String, Aws::Allocator<Aws::String>> GameLiftQueueNames;

		for (FString QueueName : QueueNames) {
			LOG_NORMAL("Setting queue name: " + QueueName);
			
			Aws::String QueueNameStr(TCHAR_TO_UTF8(*QueueName), QueueName.Len());
			GameLiftQueueNames.push_back(QueueNameStr);
		}

		Request.SetNames(GameLiftQueueNames);
		Aws::GameLift::DescribeGameSessionQueuesResponseReceivedHandler Handler;
		Handler = std::bind(&UGameLiftDescribeGameSessionQueues::OnDescribeGameSessionQueues, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);

		LOG_NORMAL("Searching...");
		GameLiftClient->DescribeGameSessionQueuesAsync(Request, Handler);
		return EActivateStatus::ACTIVATE_Success;
	}
	LOG_ERROR("GameLiftClient is null. Did you call CreateGameLiftObject first?");
#endif
	return EActivateStatus::ACTIVATE_NoGameLift;
}

void UGameLiftDescribeGameSessionQueues::OnDescribeGameSessionQueues(const Aws::GameLift::GameLiftClient* Client, const Aws::GameLift::Model::DescribeGameSessionQueuesRequest& Request, const Aws::GameLift::Model::DescribeGameSessionQueuesOutcome& Outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& Context)
{
#if WITH_GAMELIFTCLIENTSDK
	if (Outcome.IsSuccess())
	{
		LOG_NORMAL("Received OnDescribeGameSessionQueues with Success outcome.");
		LOG_NORMAL("Received OnDescribeGameSessionQueues after getting destinations");

		TArray<FGameLiftGameSessionQueueDetail> GameSessionQueueDetails;
		for (Aws::GameLift::Model::GameSessionQueue GameSessionQueue : Outcome.GetResult().GetGameSessionQueues()) {
			const FString Name= GameSessionQueue.GetName().c_str();
			const FString GameSessionQueueArn = GameSessionQueue.GetGameSessionQueueArn().c_str();
			const int TimeoutInSeconds = GameSessionQueue.GetTimeoutInSeconds();
			TArray<FGameLiftPlayerLatencyPolicyDetail> PlayerLatencyPolicyDetails;

			for (Aws::GameLift::Model::PlayerLatencyPolicy PlayerLatencyPolicy : GameSessionQueue.GetPlayerLatencyPolicies()) {
				const int MaxIndividualPlayerLatencyMilliSeconds = PlayerLatencyPolicy.GetMaximumIndividualPlayerLatencyMilliseconds();
				const int PolicyDurationSeconds = PlayerLatencyPolicy.GetPolicyDurationSeconds();

				FGameLiftPlayerLatencyPolicyDetail PlayerLatencyPolicyDetail;
				PlayerLatencyPolicyDetail.SetMaxIndividualPlayerLatencyMilliSeconds(MaxIndividualPlayerLatencyMilliSeconds);
				PlayerLatencyPolicyDetail.SetPolicyDurationSeconds(PolicyDurationSeconds);

				PlayerLatencyPolicyDetails.Add(PlayerLatencyPolicyDetail);
			}

			TArray<FString> DestinationArns;
			for (Aws::GameLift::Model::GameSessionQueueDestination GameSessionQueueDestination : GameSessionQueue.GetDestinations()) {
				const FString DestinationArn = GameSessionQueueDestination.GetDestinationArn().c_str();
				DestinationArns.Add(DestinationArn);
			}

			FGameLiftGameSessionQueueDetail GameSessionQueueDetail;
			GameSessionQueueDetail.SetName(Name);
			GameSessionQueueDetail.SetGameSessionQueueArn(GameSessionQueueArn);
			GameSessionQueueDetail.SetTimeoutInSeconds(TimeoutInSeconds);
			GameSessionQueueDetail.SetPlayerLatencyPolicyDetails(PlayerLatencyPolicyDetails);
			GameSessionQueueDetail.SetDestinationArns(DestinationArns);
			GameSessionQueueDetails.Add(GameSessionQueueDetail);
		}

		FGameLiftDescribeGameSessionQueuesResult DescribeGameSessionQueuesResult;
		DescribeGameSessionQueuesResult.SetGameSessionQueueDetails(GameSessionQueueDetails);
		OnDescribeGameSessionQueuesSuccess.Broadcast(DescribeGameSessionQueuesResult);
	}
	else
	{
		const FString MyErrorMessage = FString(Outcome.GetError().GetMessage().c_str());
		LOG_ERROR("Received OnDescribeGameSessionQueues with failed outcome. Error: " + MyErrorMessage);
		OnDescribeGameSessionQueuesFailed.Broadcast(MyErrorMessage);
	}
#endif
}

UGameLiftSearchGameSessions* UGameLiftSearchGameSessions::SearchGameSessions(const FGameLiftSearchGameSessionsConfig& SearchGameSessionsConfig)
{
#if WITH_GAMELIFTCLIENTSDK
	UGameLiftSearchGameSessions* Proxy = NewObject<UGameLiftSearchGameSessions>();
	Proxy->SearchGameSessionsConfig = &SearchGameSessionsConfig;
	return Proxy;
#endif
	return nullptr;
}

EActivateStatus UGameLiftSearchGameSessions::Activate()
{
#if WITH_GAMELIFTCLIENTSDK
	if (GameLiftClient)
	{
		LOG_NORMAL("Preparing to search for game sessions...");
		FString FleetId = SearchGameSessionsConfig->GetFleetId();
		FString AliasId = SearchGameSessionsConfig->GetAliasId();
		FString FilterExpression = SearchGameSessionsConfig->GetFilterExpression();
		FString SortExpression = SearchGameSessionsConfig->GetSortExpression();

		if (OnSearchGameSessionsSuccess.IsBound() == false)
		{
			LOG_ERROR("No functions were bound to OnSearchGameSessionsSuccess multi-cast delegate! Aborting Activate.");
			return EActivateStatus::ACTIVATE_NoSuccessCallback;
		}

		if (OnSearchGameSessionsFailed.IsBound() == false)
		{
			LOG_ERROR("No functions were bound to OnSearchGameSessionsFailed multi-cast delegate! Aborting Activate.");
			return EActivateStatus::ACTIVATE_NoFailCallback;
		}

		Aws::GameLift::Model::SearchGameSessionsRequest Request;
		
		if (FleetId.Len() > 0) {
			LOG_NORMAL("Setting fleet id: " + FleetId);
			Request.SetFleetId(TCHAR_TO_UTF8(*FleetId));
		}
		if (AliasId.Len() > 0) {
			LOG_NORMAL("Setting alias id: " + AliasId);
			Request.SetAliasId(TCHAR_TO_UTF8(*AliasId));
		}
		if (FilterExpression.Len() > 0) {
			LOG_NORMAL("Setting filter expression: " + FilterExpression);
			Request.SetFilterExpression(TCHAR_TO_UTF8(*FilterExpression));
		}
		if (SortExpression.Len() > 0) {
			LOG_NORMAL("Setting sort expression: " + SortExpression);
			Request.SetSortExpression(TCHAR_TO_UTF8(*SortExpression));
		}

		Aws::GameLift::SearchGameSessionsResponseReceivedHandler Handler;
		Handler = std::bind(&UGameLiftSearchGameSessions::OnSearchGameSessions, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);

		LOG_NORMAL("Searching...");
		GameLiftClient->SearchGameSessionsAsync(Request, Handler);
		return EActivateStatus::ACTIVATE_Success;
	}
	LOG_ERROR("GameLiftClient is null. Did you call CreateGameLiftObject first?");
#endif
	return EActivateStatus::ACTIVATE_NoGameLift;
}

void UGameLiftSearchGameSessions::OnSearchGameSessions(const Aws::GameLift::GameLiftClient* Client, const Aws::GameLift::Model::SearchGameSessionsRequest& Request, const Aws::GameLift::Model::SearchGameSessionsOutcome& Outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& Context)
{
#if WITH_GAMELIFTCLIENTSDK
	if (Outcome.IsSuccess())
	{
		LOG_NORMAL("Received OnSearchGameSessions with Success outcome.");
		TArray<FGameLiftGameSessionDetail> GameSessionDetails;
		for (Aws::GameLift::Model::GameSession GameSession : Outcome.GetResult().GetGameSessions()) {
			const FString GameSessionId = GameSession.GetGameSessionId().c_str();
			Aws::GameLift::Model::GameSessionStatus Status = GameSession.GetStatus();
			const FString GameSessionStatus = Aws::GameLift::Model::GameSessionStatusMapper::GetNameForGameSessionStatus(Status).c_str();
			const int CurrentPlayerCount = GameSession.GetCurrentPlayerSessionCount();
			const int MaxPlayerCount = GameSession.GetMaximumPlayerSessionCount();
			Aws::GameLift::Model::PlayerSessionCreationPolicy CreationPolicy = GameSession.GetPlayerSessionCreationPolicy();
			const FString PlayerSessionCreationPolicy = Aws::GameLift::Model::PlayerSessionCreationPolicyMapper::GetNameForPlayerSessionCreationPolicy(CreationPolicy).c_str();
			TMap<FString, FString> GameProperties;
			const Aws::Vector<Aws::GameLift::Model::GameProperty> GameLiftGameProperties = GameSession.GetGameProperties();

			for (Aws::GameLift::Model::GameProperty GameProperty : GameLiftGameProperties) {
				GameProperties.Add(GameProperty.GetKey().c_str(), GameProperty.GetValue().c_str());
			}

			const FString ServerIpAddress = GameSession.GetIpAddress().c_str();
			const FString ServerPort = FString::FromInt(GameSession.GetPort());
			const FString ServerDnsName = GameSession.GetDnsName().c_str();
			const FString GameSessionData = GameSession.GetGameSessionData().c_str();
			const FString MatchmakerData = GameSession.GetMatchmakerData().c_str();
			const FString Name = GameSession.GetName().c_str();

			FGameLiftGameSessionDetail GameSessionDetail;
			GameSessionDetail.SetGameSessionId(GameSessionId);
			GameSessionDetail.SetGameSessionStatus(GameSessionStatus);
			GameSessionDetail.SetCurrentPlayerCount(CurrentPlayerCount);
			GameSessionDetail.SetMaxPlayerCount(MaxPlayerCount);
			GameSessionDetail.SetPlayerSessionCreationPolicy(PlayerSessionCreationPolicy);
			GameSessionDetail.SetGameProperties(GameProperties);
			GameSessionDetail.SetServerIpAddress(ServerIpAddress);
			GameSessionDetail.SetServerPort(ServerPort);
			GameSessionDetail.SetServerDnsName(ServerDnsName);
			GameSessionDetail.SetGameSessionData(GameSessionData);
			GameSessionDetail.SetMatchmakerData(MatchmakerData);
			GameSessionDetail.SetName(Name);

			GameSessionDetails.Add(GameSessionDetail);
		}

		FGameLiftSearchGameSessionsResult SearchGameSessionsResult;
		SearchGameSessionsResult.SetGameSessionDetails(GameSessionDetails);
		OnSearchGameSessionsSuccess.Broadcast(SearchGameSessionsResult);
	}
	else
	{
		const FString MyErrorMessage = FString(Outcome.GetError().GetMessage().c_str());
		LOG_ERROR("Received SearchGameSessions with failed outcome. Error: " + MyErrorMessage);
		OnSearchGameSessionsFailed.Broadcast(MyErrorMessage);
	}
#endif
}

UGameLiftStartGameSessionPlacement* UGameLiftStartGameSessionPlacement::StartGameSessionPlacement(const FGameLiftStartGameSessionPlacementConfig& StartGameSessionPlacementConfig)
{
#if WITH_GAMELIFTCLIENTSDK
	UGameLiftStartGameSessionPlacement* Proxy = NewObject<UGameLiftStartGameSessionPlacement>();
	Proxy->StartGameSessionPlacementConfig = &StartGameSessionPlacementConfig;
	return Proxy;
#endif
	return nullptr;
}

EActivateStatus UGameLiftStartGameSessionPlacement::Activate()
{
#if WITH_GAMELIFTCLIENTSDK
	if (GameLiftClient)
	{
		LOG_NORMAL("Preparing to make a game session if available...");

		FString PlacementId = StartGameSessionPlacementConfig->GetPlacementId();
		FString QueueName = StartGameSessionPlacementConfig->GetQueueName();
		TMap<FString, FString> GameProperties = StartGameSessionPlacementConfig->GetGameProperties();
		int MaxPlayerCount = StartGameSessionPlacementConfig->GetMaxPlayerCount();
		TArray<FGameLiftPlayerLatencyDetail> PlayerLatencyConfigs = StartGameSessionPlacementConfig->GetPlayerLatencies();
		TArray<FGameLiftDesiredPlayerSessionConfig> DesiredPlayerSessionConfigs = StartGameSessionPlacementConfig->GetDesiredPlayerSessions();
		FString GameSessionData = StartGameSessionPlacementConfig->GetGameSessionData();

		if (OnStartGameSessionPlacementSuccess.IsBound() == false)
		{
			LOG_ERROR("No functions were bound to OnStartGameSessionPlacement multi-cast delegate! Aborting Activate.");
			return EActivateStatus::ACTIVATE_NoSuccessCallback;
		}

		if (OnStartGameSessionPlacementFailed.IsBound() == false)
		{
			LOG_ERROR("No functions were bound to OnStartGameSessionPlacement multi-cast delegate! Aborting Activate.");
			return EActivateStatus::ACTIVATE_NoFailCallback;
		}

		Aws::GameLift::Model::StartGameSessionPlacementRequest Request;
		if (PlacementId.Len() > 0) {
			LOG_NORMAL("Setting placement id: " + PlacementId);
			Request.SetPlacementId(TCHAR_TO_UTF8(*PlacementId));
		}

		if (QueueName.Len() > 0) {
			LOG_NORMAL("Setting queue name: " + QueueName);
			Request.SetGameSessionQueueName(TCHAR_TO_UTF8(*QueueName));
		}

		for (auto& Property : GameProperties)
		{
			LOG_NORMAL("********************************************************************");
			Aws::GameLift::Model::GameProperty MapProperty;
			MapProperty.SetKey(TCHAR_TO_UTF8(*Property.Key));
			MapProperty.SetValue(TCHAR_TO_UTF8(*Property.Value));
			Request.AddGameProperties(MapProperty);
			LOG_NORMAL(FString::Printf(TEXT("New GameProperty added. Key: (%s) Value: (%s)"), *Property.Key, *Property.Value));
		}

		LOG_NORMAL("Setting max player count: " + FString(std::to_string(MaxPlayerCount).c_str()));
		Request.SetMaximumPlayerSessionCount(MaxPlayerCount);

		for (FGameLiftPlayerLatencyDetail PlayerLatencyConfig : PlayerLatencyConfigs) {
			LOG_NORMAL("Setting player latencies");
			Aws::GameLift::Model::PlayerLatency PlayerLatency;

			FString PlayerId = PlayerLatencyConfig.GetPlayerId();
			FString RegionIdentifier = PlayerLatencyConfig.GetRegionIdentifier();
			float LatencyInMilliseconds = PlayerLatencyConfig.GetLatencyInMilliseconds();

			PlayerLatency.SetPlayerId(TCHAR_TO_UTF8(*PlayerId));
			PlayerLatency.SetRegionIdentifier(TCHAR_TO_UTF8(*RegionIdentifier));
			PlayerLatency.SetLatencyInMilliseconds(LatencyInMilliseconds);
			
			Request.AddPlayerLatencies(PlayerLatency);
		}

		for (FGameLiftDesiredPlayerSessionConfig DesiredPlayerSessionConfig : DesiredPlayerSessionConfigs) {
			LOG_NORMAL("Setting desired player sessions");
			Aws::GameLift::Model::DesiredPlayerSession DesiredPlayerSession;

			FString PlayerId = DesiredPlayerSessionConfig.GetPlayerId();
			FString PlayerData = DesiredPlayerSessionConfig.GetPlayerData();

			DesiredPlayerSession.SetPlayerId(TCHAR_TO_UTF8(*PlayerId));
			DesiredPlayerSession.SetPlayerData(TCHAR_TO_UTF8(*PlayerData));

			Request.AddDesiredPlayerSessions(DesiredPlayerSession);
		}

		if (GameSessionData.Len() > 0) {
			LOG_NORMAL("Setting game session data: " + GameSessionData);
			Request.SetGameSessionData(TCHAR_TO_UTF8(*GameSessionData));
		}

		Aws::GameLift::StartGameSessionPlacementResponseReceivedHandler Handler;
		Handler = std::bind(&UGameLiftStartGameSessionPlacement::OnStartGameSessionPlacement, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);

		LOG_NORMAL("Searching...");
		GameLiftClient->StartGameSessionPlacementAsync(Request, Handler);
		return EActivateStatus::ACTIVATE_Success;
	}
	LOG_ERROR("GameLiftClient is null. Did you call CreateGameLiftObject first?");
#endif
	return EActivateStatus::ACTIVATE_NoGameLift;
}

void UGameLiftStartGameSessionPlacement::OnStartGameSessionPlacement(const Aws::GameLift::GameLiftClient* Client, const Aws::GameLift::Model::StartGameSessionPlacementRequest& Request, const Aws::GameLift::Model::StartGameSessionPlacementOutcome& Outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& Context)
{
#if WITH_GAMELIFTCLIENTSDK
	if (Outcome.IsSuccess())
	{
		LOG_NORMAL("Received OnStartGameSessionPlacement with Success outcome.");
		FGameLiftGameSessionPlacementDetail GameSessionPlacementDetail;
		Aws::GameLift::Model::GameSessionPlacement GameSessionPlacement = Outcome.GetResult().GetGameSessionPlacement();
		const FString PlacementId = GameSessionPlacement.GetPlacementId().c_str();
		const FString QueueName = GameSessionPlacement.GetGameSessionQueueName().c_str();
		Aws::GameLift::Model::GameSessionPlacementState Status = GameSessionPlacement.GetStatus();
		const FString GameSessionPlacementStatus = Aws::GameLift::Model::GameSessionPlacementStateMapper::GetNameForGameSessionPlacementState(Status).c_str();
		TMap<FString, FString> GameProperties;
		const Aws::Vector<Aws::GameLift::Model::GameProperty> GameLiftGameProperties = GameSessionPlacement.GetGameProperties();

		for (Aws::GameLift::Model::GameProperty GameProperty : GameLiftGameProperties) {
			GameProperties.Add(GameProperty.GetKey().c_str(), GameProperty.GetValue().c_str());
		}
		const int MaxPlayerCount = GameSessionPlacement.GetMaximumPlayerSessionCount();
		const FString GameSessionName = GameSessionPlacement.GetGameSessionName().c_str();
		const FString GameSessionId = GameSessionPlacement.GetGameSessionId().c_str();
		const FString GameSessionRegion = GameSessionPlacement.GetGameSessionRegion().c_str();
		TArray<FGameLiftPlayerLatencyDetail> PlayerLatencies;
		const Aws::Vector<Aws::GameLift::Model::PlayerLatency> GameLiftPlayerLatencies = GameSessionPlacement.GetPlayerLatencies();

		for (Aws::GameLift::Model::PlayerLatency PlayerLatency : GameLiftPlayerLatencies) {
			const FString PlayerId = PlayerLatency.GetPlayerId().c_str();
			const FString RegionIdentifier = PlayerLatency.GetRegionIdentifier().c_str();
			const float LatencyInMilliseconds = PlayerLatency.GetLatencyInMilliseconds();

			FGameLiftPlayerLatencyDetail PlayerLatencyDetail;
			PlayerLatencyDetail.SetPlayerId(PlayerId);
			PlayerLatencyDetail.SetRegionIdentifier(RegionIdentifier);
			PlayerLatencyDetail.SetLatencyInMilliseconds(LatencyInMilliseconds);
			PlayerLatencies.Add(PlayerLatencyDetail);
		}

		const FString ServerIpAddress = GameSessionPlacement.GetIpAddress().c_str();
		const FString ServerPort = FString::FromInt(GameSessionPlacement.GetPort());
		const FString ServerDnsName = GameSessionPlacement.GetDnsName().c_str();
		TArray<FGameLiftPlacedPlayerSessionDetail> PlacedPlayerSessionDetails;
		const Aws::Vector<Aws::GameLift::Model::PlacedPlayerSession> GameLiftPlacedPlayerSessions = GameSessionPlacement.GetPlacedPlayerSessions();

		for (Aws::GameLift::Model::PlacedPlayerSession PlacedPlayerSession : GameLiftPlacedPlayerSessions) {
			const FString PlayerId = PlacedPlayerSession.GetPlayerId().c_str();
			const FString PlayerSessionId = PlacedPlayerSession.GetPlayerSessionId().c_str();

			FGameLiftPlacedPlayerSessionDetail PlacedPlayerSessionDetail;
			PlacedPlayerSessionDetail.SetPlayerId(PlayerId);
			PlacedPlayerSessionDetail.SetPlayerSessionId(PlayerSessionId);

			PlacedPlayerSessionDetails.Add(PlacedPlayerSessionDetail);
		}

		const FString GameSessionData = GameSessionPlacement.GetGameSessionData().c_str();
		const FString MatchmakerData = GameSessionPlacement.GetMatchmakerData().c_str();

		GameSessionPlacementDetail.SetPlacementId(PlacementId);
		GameSessionPlacementDetail.SetQueueName(QueueName);
		GameSessionPlacementDetail.SetGameSessionPlacementStatus(GameSessionPlacementStatus);
		GameSessionPlacementDetail.SetGameProperties(GameProperties);
		GameSessionPlacementDetail.SetMaxPlayerCount(MaxPlayerCount);
		GameSessionPlacementDetail.SetGameSessionName(GameSessionName);
		GameSessionPlacementDetail.SetGameSessionId(GameSessionId);
		GameSessionPlacementDetail.SetGameSessionRegion(GameSessionRegion);
		GameSessionPlacementDetail.SetPlayerLatencies(PlayerLatencies);
		GameSessionPlacementDetail.SetServerIpAddress(ServerIpAddress);
		GameSessionPlacementDetail.SetServerPort(ServerPort);
		GameSessionPlacementDetail.SetServerDnsName(ServerDnsName);
		GameSessionPlacementDetail.SetPlacedPlayerSessionDetails(PlacedPlayerSessionDetails);
		GameSessionPlacementDetail.SetGameSessionData(GameSessionData);
		GameSessionPlacementDetail.SetMatchmakerData(MatchmakerData);

		FGameLiftStartGameSessionPlacementResult StartGameSessionPlacementResult;
		StartGameSessionPlacementResult.SetGameSessionPlacementDetail(GameSessionPlacementDetail);
		OnStartGameSessionPlacementSuccess.Broadcast(StartGameSessionPlacementResult);
	}
	else
	{
		const FString MyErrorMessage = FString(Outcome.GetError().GetMessage().c_str());
		LOG_ERROR("Received OnStartGameSessionPlacement with failed outcome. Error: " + MyErrorMessage);
		OnStartGameSessionPlacementFailed.Broadcast(MyErrorMessage);
	}
#endif
}

UGameLiftDescribeGameSessionPlacement* UGameLiftDescribeGameSessionPlacement::DescribeGameSessionPlacement(const FGameLiftDescribeGameSessionPlacementConfig& DescribeGameSessionPlacementConfig)
{
#if WITH_GAMELIFTCLIENTSDK
	UGameLiftDescribeGameSessionPlacement* Proxy = NewObject<UGameLiftDescribeGameSessionPlacement>();
	Proxy->DescribeGameSessionPlacementConfig = &DescribeGameSessionPlacementConfig;
	return Proxy;
#endif
	return nullptr;
}

EActivateStatus UGameLiftDescribeGameSessionPlacement::Activate()
{
#if WITH_GAMELIFTCLIENTSDK
	if (GameLiftClient)
	{
		LOG_NORMAL("Preparing to describe a game session placement if available...");
		FString PlacementId = DescribeGameSessionPlacementConfig->GetPlacementId();

		if (OnDescribeGameSessionPlacementSuccess.IsBound() == false)
		{
			LOG_ERROR("No functions were bound to OnDescribeGameSessionPlacement multi-cast delegate! Aborting Activate.");
			return EActivateStatus::ACTIVATE_NoSuccessCallback;
		}

		if (OnDescribeGameSessionPlacementFailed.IsBound() == false)
		{
			LOG_ERROR("No functions were bound to OnDescribeGameSessionPlacement multi-cast delegate! Aborting Activate.");
			return EActivateStatus::ACTIVATE_NoFailCallback;
		}

		Aws::GameLift::Model::DescribeGameSessionPlacementRequest Request;
		if (PlacementId.Len() > 0) {
			LOG_NORMAL("PlacementId " + PlacementId);
			Request.SetPlacementId(TCHAR_TO_UTF8(*PlacementId));
		}
		

		Aws::GameLift::DescribeGameSessionPlacementResponseReceivedHandler Handler;
		Handler = std::bind(&UGameLiftDescribeGameSessionPlacement::OnDescribeGameSessionPlacement, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);

		LOG_NORMAL("Searching...");
		GameLiftClient->DescribeGameSessionPlacementAsync(Request, Handler);
		return EActivateStatus::ACTIVATE_Success;
	}
	LOG_ERROR("GameLiftClient is null. Did you call CreateGameLiftObject first?");
#endif
	return EActivateStatus::ACTIVATE_NoGameLift;
}

void UGameLiftDescribeGameSessionPlacement::OnDescribeGameSessionPlacement(const Aws::GameLift::GameLiftClient* Client, const Aws::GameLift::Model::DescribeGameSessionPlacementRequest& Request, const Aws::GameLift::Model::DescribeGameSessionPlacementOutcome& Outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& Context)
{
#if WITH_GAMELIFTCLIENTSDK
	if (Outcome.IsSuccess())
	{
		LOG_NORMAL("Received OnDescribeGameSessionPlacement with Success outcome.");
		FGameLiftGameSessionPlacementDetail GameSessionPlacementDetail;
		Aws::GameLift::Model::GameSessionPlacement GameSessionPlacement = Outcome.GetResult().GetGameSessionPlacement();
		const FString PlacementId = GameSessionPlacement.GetPlacementId().c_str();
		const FString QueueName = GameSessionPlacement.GetGameSessionQueueName().c_str();
		Aws::GameLift::Model::GameSessionPlacementState Status = GameSessionPlacement.GetStatus();
		const FString GameSessionPlacementStatus = Aws::GameLift::Model::GameSessionPlacementStateMapper::GetNameForGameSessionPlacementState(Status).c_str();
		TMap<FString, FString> GameProperties;
		const Aws::Vector<Aws::GameLift::Model::GameProperty> GameLiftGameProperties = GameSessionPlacement.GetGameProperties();

		for (Aws::GameLift::Model::GameProperty GameProperty : GameLiftGameProperties) {
			GameProperties.Add(GameProperty.GetKey().c_str(), GameProperty.GetValue().c_str());
		}
		const int MaxPlayerCount = GameSessionPlacement.GetMaximumPlayerSessionCount();
		const FString GameSessionName = GameSessionPlacement.GetGameSessionName().c_str();
		const FString GameSessionId = GameSessionPlacement.GetGameSessionId().c_str();
		const FString GameSessionRegion = GameSessionPlacement.GetGameSessionRegion().c_str();
		TArray<FGameLiftPlayerLatencyDetail> PlayerLatencies;
		const Aws::Vector<Aws::GameLift::Model::PlayerLatency> GameLiftPlayerLatencies = GameSessionPlacement.GetPlayerLatencies();

		for (Aws::GameLift::Model::PlayerLatency PlayerLatency : GameLiftPlayerLatencies) {
			const FString PlayerId = PlayerLatency.GetPlayerId().c_str();
			const FString RegionIdentifier = PlayerLatency.GetRegionIdentifier().c_str();
			const float LatencyInMilliseconds = PlayerLatency.GetLatencyInMilliseconds();

			FGameLiftPlayerLatencyDetail PlayerLatencyDetail;
			PlayerLatencyDetail.SetPlayerId(PlayerId);
			PlayerLatencyDetail.SetRegionIdentifier(RegionIdentifier);
			PlayerLatencyDetail.SetLatencyInMilliseconds(LatencyInMilliseconds);
			PlayerLatencies.Add(PlayerLatencyDetail);
		}

		const FString ServerIpAddress = GameSessionPlacement.GetIpAddress().c_str();
		const FString ServerPort = FString::FromInt(GameSessionPlacement.GetPort());
		const FString ServerDnsName = GameSessionPlacement.GetDnsName().c_str();
		TArray<FGameLiftPlacedPlayerSessionDetail> PlacedPlayerSessionDetails;
		const Aws::Vector<Aws::GameLift::Model::PlacedPlayerSession> GameLiftPlacedPlayerSessions = GameSessionPlacement.GetPlacedPlayerSessions();

		for (Aws::GameLift::Model::PlacedPlayerSession PlacedPlayerSession : GameLiftPlacedPlayerSessions) {
			const FString PlayerId = PlacedPlayerSession.GetPlayerId().c_str();
			const FString PlayerSessionId = PlacedPlayerSession.GetPlayerSessionId().c_str();

			FGameLiftPlacedPlayerSessionDetail PlacedPlayerSessionDetail;
			PlacedPlayerSessionDetail.SetPlayerId(PlayerId);
			PlacedPlayerSessionDetail.SetPlayerSessionId(PlayerSessionId);

			PlacedPlayerSessionDetails.Add(PlacedPlayerSessionDetail);
		}

		const FString GameSessionData = GameSessionPlacement.GetGameSessionData().c_str();
		const FString MatchmakerData = GameSessionPlacement.GetMatchmakerData().c_str();

		GameSessionPlacementDetail.SetPlacementId(PlacementId);
		GameSessionPlacementDetail.SetQueueName(QueueName);
		GameSessionPlacementDetail.SetGameSessionPlacementStatus(GameSessionPlacementStatus);
		GameSessionPlacementDetail.SetGameProperties(GameProperties);
		GameSessionPlacementDetail.SetMaxPlayerCount(MaxPlayerCount);
		GameSessionPlacementDetail.SetGameSessionName(GameSessionName);
		GameSessionPlacementDetail.SetGameSessionId(GameSessionId);
		GameSessionPlacementDetail.SetGameSessionRegion(GameSessionRegion);
		GameSessionPlacementDetail.SetPlayerLatencies(PlayerLatencies);
		GameSessionPlacementDetail.SetServerIpAddress(ServerIpAddress);
		GameSessionPlacementDetail.SetServerPort(ServerPort);
		GameSessionPlacementDetail.SetServerDnsName(ServerDnsName);
		GameSessionPlacementDetail.SetPlacedPlayerSessionDetails(PlacedPlayerSessionDetails);
		GameSessionPlacementDetail.SetGameSessionData(GameSessionData);
		GameSessionPlacementDetail.SetMatchmakerData(MatchmakerData);

		FGameLiftDescribeGameSessionPlacementResult DescribeGameSessionPlacementResult;
		DescribeGameSessionPlacementResult.SetGameSessionPlacementDetail(GameSessionPlacementDetail);
		OnDescribeGameSessionPlacementSuccess.Broadcast(DescribeGameSessionPlacementResult);
	}
	else
	{
		const FString MyErrorMessage = FString(Outcome.GetError().GetMessage().c_str());
		LOG_ERROR("Received OnDescribeGameSessionPlacement with failed outcome. Error: " + MyErrorMessage);
		OnDescribeGameSessionPlacementFailed.Broadcast(MyErrorMessage);
	}
#endif
}

