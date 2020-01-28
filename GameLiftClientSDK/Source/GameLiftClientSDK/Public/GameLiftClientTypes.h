// Created by YetiTech Studios.

#pragma once

#include "GameLiftClientTypes.generated.h"

USTRUCT(BlueprintType)
struct FGameLiftCreateGameSessionConfig
{
	GENERATED_USTRUCT_BODY()

private:

	/* Maximum number of players that can be connected simultaneously to the game session. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int MaxPlayerCount;

	/* 
	 * Unique identifier for an alias associated with the fleet to create a game session in.
	 * You can switch gameplay and players to a new fleet without changing your game client or other game components. 
	 * For example, for games in production, using an alias allows you to seamlessly redirect your player base to a new game server update.
	 * @See http://docs.aws.amazon.com/gamelift/latest/developerguide/aliases-creating.html
	 * @See http://docs.aws.amazon.com/gamelift/latest/apireference/API_CreateAlias.html
	 * */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString AliasId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString FleetId;

	/* Set of developer-defined properties for a game session, formatted as a set of type:value pairs. 
	 * These properties are included in the GameSession object, which is passed to the game server with a request to start a new game session */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<FString, FString> GameProperties;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString IdempotencyToken;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString GameSessionData;

public:

	void SetMaxPlayerCount(int Value)
	{
		this->MaxPlayerCount = Value;
	}

	void SetAliasId(FString Value)
	{
		this->AliasId = Value;
	}

	void SetFleetId(FString Value) {
		this->FleetId = Value;
	}

	void SetGameProperties(TMap<FString, FString> Value)
	{
		this->GameProperties = Value;
	}

	void SetName(FString Value) {
		this->Name = Value;
	}

	void SetIdempotencyToken(FString Value) {
		this->IdempotencyToken = Value;
	}

	void SetGameSessionData(FString Value) {
		this->GameSessionData = Value;
	}

	FORCEINLINE int GetMaxPlayerCount() const { return MaxPlayerCount; }
	FORCEINLINE FString GetAliasId() const { return AliasId; }
	FORCEINLINE FString GetFleetId() const { return FleetId; }
	FORCEINLINE FString GetGameLiftLocalFleetId() const { return "fleet-1a2b3c4d-5e6f-7a8b-9c0d-1e2f3a4b5c6d"; }
	FORCEINLINE TMap<FString, FString> GetGameProperties() const { return GameProperties; }
	FORCEINLINE FString GetName() const { return Name; }
	FORCEINLINE FString GetIdempotencyToken() const { return IdempotencyToken; }
	FORCEINLINE FString GetGameSessionData() const { return GameSessionData; }
};

USTRUCT(BlueprintType)
struct FGameLiftGameSessionDetail
{
	GENERATED_USTRUCT_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString GameSessionId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString GameSessionStatus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int CurrentPlayerCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int MaxPlayerCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString PlayerSessionCreationPolicy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<FString, FString> GameProperties;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString ServerIpAddress;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString ServerPort;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString ServerDnsName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString GameSessionData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString MatchmakerData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString ProtectionPolicy;
public:
	void SetGameSessionId(FString Value) {
		this->GameSessionId = Value;
	}

	void SetGameSessionStatus(FString Value) {
		this->GameSessionStatus = Value;
	}

	void SetCurrentPlayerCount(int Value) {
		this->CurrentPlayerCount = Value;
	}

	void SetMaxPlayerCount(int Value) {
		this->MaxPlayerCount = Value;
	}

	void SetPlayerSessionCreationPolicy(FString Value) {
		this->PlayerSessionCreationPolicy = Value;
	}

	void SetGameProperties(TMap<FString, FString> Value) {
		this->GameProperties = Value;
	}

	void SetServerIpAddress(FString Value) {
		this->ServerIpAddress = Value;
	}

	void SetServerPort(FString Value) {
		this->ServerPort = Value;
	}

	void SetServerDnsName(FString Value) {
		this->ServerDnsName = Value;
	}

	void SetGameSessionData(FString Value) {
		this->GameSessionData = Value;
	}

	void SetMatchmakerData(FString Value) {
		this->MatchmakerData = Value;
	}

	void SetName(FString Value) {
		this->Name = Value;
	}

	void SetProtectionPolicy(FString Value) {
		this->ProtectionPolicy = Value;
	}

	FORCEINLINE FString GetGameSessionId() const { return GameSessionId; }
	FORCEINLINE FString GetGameSessionStatus() const { return GameSessionStatus; }
	FORCEINLINE int GetCurrentPlayerCount() const { return CurrentPlayerCount; }
	FORCEINLINE int GetMaxPlayerCount() const { return MaxPlayerCount; }
	FORCEINLINE FString GetPlayerSessionCreationPolicy() const { return PlayerSessionCreationPolicy; }
	FORCEINLINE TMap<FString, FString> GetGameProperties() const { return GameProperties; }
	FORCEINLINE FString GetServerIpAddress() const { return ServerIpAddress; }
	FORCEINLINE FString GetServerPort() const { return ServerPort; }
	FORCEINLINE FString GetServerDnsName() const { return ServerDnsName; }
	FORCEINLINE FString GetGameSessionData() const { return GameSessionData; }
	FORCEINLINE FString GetMatchmakerData() const { return MatchmakerData; }
	FORCEINLINE FString GetName() const { return Name; }
	FORCEINLINE FString GetProtectionPolicy() const { return ProtectionPolicy; }
};

USTRUCT(BlueprintType)
struct FGameLiftCreateGameSessionResult
{
	GENERATED_USTRUCT_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FGameLiftGameSessionDetail GameSessionDetail;

public:
	void SetGameSessionDetail(FGameLiftGameSessionDetail Value) {
		this->GameSessionDetail = Value;
	}

	FORCEINLINE FGameLiftGameSessionDetail GetGameSessionDetail() const { return GameSessionDetail; }
};

USTRUCT(BlueprintType)
struct FGameLiftDescribeGameSessionDetailsConfig
{
	GENERATED_USTRUCT_BODY()

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString GameSessionId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString FleetId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString AliasId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString StatusFilter;

public:
	void SetGameSessionId(FString Value)
	{
		this->GameSessionId = Value;
	}

	void SetFleetId(FString Value)
	{
		this->FleetId = Value;
	}

	void SetAliasId(FString Value)
	{
		this->AliasId = Value;
	}

	void SetStatusFilter(FString Value)
	{
		this->StatusFilter = Value;
	}

	FORCEINLINE FString GetGameSessionId() const { return GameSessionId; }
	FORCEINLINE FString GetFleetId() const { return FleetId; }
	FORCEINLINE FString GetAliasId() const { return AliasId; }
	FORCEINLINE FString GetStatusFilter() const { return StatusFilter; }
};

USTRUCT(BlueprintType)
struct FGameLiftDescribeGameSessionDetailsResult
{
	GENERATED_USTRUCT_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FGameLiftGameSessionDetail> GameSessionDetails;
public:
	void SetGameSessionDetails(TArray<FGameLiftGameSessionDetail> Value) {
		this->GameSessionDetails = Value;
	}

	FORCEINLINE TArray<FGameLiftGameSessionDetail> GetGameSessionDetails() const { return GameSessionDetails; }
};

USTRUCT(BlueprintType)
struct FGameLiftCreatePlayerSessionConfig
{
	GENERATED_USTRUCT_BODY()

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString GameSessionId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString PlayerId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString PlayerData;

public:
	void SetGameSessionId(FString Value)
	{
		this->GameSessionId = Value;
	}

	void SetPlayerId(FString Value)
	{
		this->PlayerId = Value;
	}
	
	void SetPlayerData(FString Value)
	{
		this->PlayerData = Value;
	}

	FORCEINLINE FString GetGameSessionId() const { return GameSessionId; }
	FORCEINLINE FString GetPlayerId() const { return PlayerId; }
	FORCEINLINE FString GetPlayerData() const { return PlayerData; }
};

USTRUCT(BlueprintType)
struct FGameLiftPlayerSessionDetail
{
	GENERATED_USTRUCT_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString ServerIpAddress;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString ServerPort;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString ServerDnsName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString PlayerSessionId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString PlayerSessionStatus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString PlayerId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString PlayerData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString GameSessionId;
public:
	void SetServerIpAddress(FString Value) {
		this->ServerIpAddress = Value;
	}

	void SetServerPort(FString Value) {
		this->ServerPort = Value;
	}

	void SetServerDnsName(FString Value) {
		this->ServerDnsName = Value;
	}

	void SetPlayerSessionId(FString Value) {
		this->PlayerSessionId = Value;
	}

	void SetPlayerSessionStatus(FString Value) {
		this->PlayerSessionStatus = Value;
	}

	void SetPlayerId(FString Value) {
		this->PlayerId = Value;
	}

	void SetPlayerData(FString Value) {
		this->PlayerData = Value;
	}

	void SetGameSessionId(FString Value) {
		this->GameSessionId = Value;
	}

	FORCEINLINE FString GetServerIpAddress() const { return ServerIpAddress; }
	FORCEINLINE FString GetServerPort() const { return ServerPort; }
	FORCEINLINE FString GetServerDnsName() const { return ServerDnsName; }
	FORCEINLINE FString GetPlayerSessionId() const { return PlayerSessionId; }
	FORCEINLINE FString GetPlayerSessionStatus() const { return PlayerSessionStatus; }
	FORCEINLINE FString GetPlayerId() const { return PlayerId; }
	FORCEINLINE FString GetPlayerData() const { return PlayerData; }
	FORCEINLINE FString GetGameSessionId() const { return GameSessionId; }
};

USTRUCT(BlueprintType)
struct FGameLiftCreatePlayerSessionResult
{
	GENERATED_USTRUCT_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FGameLiftPlayerSessionDetail PlayerSessionDetail;

public:
	void SetPlayerSessionDetail(FGameLiftPlayerSessionDetail Value) {
		this->PlayerSessionDetail = Value;
	}

	FORCEINLINE FGameLiftPlayerSessionDetail GetPlayerSessionDetail() const { return PlayerSessionDetail; }
};

USTRUCT(BlueprintType)
struct FGameLiftDescribeGameSessionQueuesConfig
{
	GENERATED_USTRUCT_BODY()

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FString> QueueNames;

public:
	void SetQueueNames(TArray<FString> Value)
	{
		this->QueueNames = Value;
	}

	FORCEINLINE TArray<FString> GetQueueNames() const { return QueueNames; }
};

USTRUCT(BlueprintType)
struct FGameLiftPlayerLatencyPolicyDetail
{
	GENERATED_USTRUCT_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int MaxIndividualPlayerLatencyMilliSeconds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int PolicyDurationSeconds;
public:
	void SetMaxIndividualPlayerLatencyMilliSeconds(int Value) {
		this->MaxIndividualPlayerLatencyMilliSeconds = Value;
	}

	void SetPolicyDurationSeconds(int Value) {
		this->PolicyDurationSeconds = Value;
	}

	FORCEINLINE int GetMaxIndividualPlayerLatencyMilliSeconds() const { return MaxIndividualPlayerLatencyMilliSeconds; }
	FORCEINLINE int GetPolicyDurationSeconds() const { return PolicyDurationSeconds; }
};

USTRUCT(BlueprintType)
struct FGameLiftGameSessionQueueDetail
{
	GENERATED_USTRUCT_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString GameSessionQueueArn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int TimeoutInSeconds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FGameLiftPlayerLatencyPolicyDetail> PlayerLatencyPolicyDetails;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FString> DestinationArns;
public:
	void SetName(FString Value) {
		this->Name = Value;
	}

	void SetGameSessionQueueArn(FString Value) {
		this->GameSessionQueueArn = Value;
	}

	void SetTimeoutInSeconds(int Value) {
		this->TimeoutInSeconds = Value;
	}

	void SetPlayerLatencyPolicyDetails(TArray<FGameLiftPlayerLatencyPolicyDetail> Value) {
		this->PlayerLatencyPolicyDetails = Value;
	}

	void SetDestinationArns(TArray<FString> Value) {
		this->DestinationArns = Value;
	}

	FORCEINLINE FString GetName() const { return Name; }
	FORCEINLINE FString GetGameSessionQueueArn() const { return GameSessionQueueArn; }
	FORCEINLINE int GetTimeoutInSeconds() const { return TimeoutInSeconds; }
	FORCEINLINE TArray<FGameLiftPlayerLatencyPolicyDetail> GetPlayerLatencyPolicyDetails() const { return PlayerLatencyPolicyDetails; }
	FORCEINLINE TArray<FString> GetDestinationArns() const { return DestinationArns; }
};

USTRUCT(BlueprintType)
struct FGameLiftDescribeGameSessionQueuesResult
{
	GENERATED_USTRUCT_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FGameLiftGameSessionQueueDetail> GameSessionQueueDetails;

public:
	void SetGameSessionQueueDetails(TArray<FGameLiftGameSessionQueueDetail> Value) {
		this->GameSessionQueueDetails = Value;
	}

	FORCEINLINE TArray<FGameLiftGameSessionQueueDetail> GetGameSessionQueueDetails() const { return GameSessionQueueDetails; }
};

USTRUCT(BlueprintType)
struct FGameLiftSearchGameSessionsConfig
{
	GENERATED_USTRUCT_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString FleetId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString AliasId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString FilterExpression;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString SortExpression;

public:
	void SetFleetId(FString Value)
	{
		this->FleetId = Value;
	}

	void SetAliasId(FString Value)
	{
		this->AliasId = Value;
	}

	void SetFilterExpression(FString Value)
	{
		this->FilterExpression = Value;
	}

	void SetSortExpression(FString Value)
	{
		this->SortExpression = Value;
	}

	FORCEINLINE FString GetFleetId() const { return FleetId; }
	FORCEINLINE FString GetAliasId() const { return AliasId; }
	FORCEINLINE FString GetFilterExpression() const { return FilterExpression; }
	FORCEINLINE FString GetSortExpression() const { return SortExpression; }
};

USTRUCT(BlueprintType)
struct FGameLiftSearchGameSessionsResult
{
	GENERATED_USTRUCT_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FGameLiftGameSessionDetail> GameSessionDetails;
public:
	void SetGameSessionDetails(TArray<FGameLiftGameSessionDetail> Value) {
		this->GameSessionDetails = Value;
	}

	FORCEINLINE TArray<FGameLiftGameSessionDetail> GetGameSessionDetails() const { return GameSessionDetails; }
};

USTRUCT(BlueprintType)
struct FGameLiftPlayerLatencyDetail
{
	GENERATED_USTRUCT_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString PlayerId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString RegionIdentifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float LatencyInMilliseconds;
public:
	void SetPlayerId(FString Value)
	{
		this->PlayerId = Value;
	}

	void SetRegionIdentifier(FString Value)
	{
		this->RegionIdentifier = Value;
	}

	void SetLatencyInMilliseconds(float Value)
	{
		this->LatencyInMilliseconds = Value;
	}

	FORCEINLINE FString GetPlayerId() const { return PlayerId; }
	FORCEINLINE FString GetRegionIdentifier() const { return RegionIdentifier; }
	FORCEINLINE float GetLatencyInMilliseconds() const { return LatencyInMilliseconds; }
};

USTRUCT(BlueprintType)
struct FGameLiftDesiredPlayerSessionConfig
{
	GENERATED_USTRUCT_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString PlayerId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString PlayerData;

public:
	void SetPlayerId(FString Value)
	{
		this->PlayerId = Value;
	}

	void SetPlayerData(FString Value)
	{
		this->PlayerData = Value;
	}

	FORCEINLINE FString GetPlayerId() const { return PlayerId; }
	FORCEINLINE FString GetPlayerData() const { return PlayerData; }
};

USTRUCT(BlueprintType)
struct FGameLiftStartGameSessionPlacementConfig
{
	GENERATED_USTRUCT_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString PlacementId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString QueueName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<FString, FString> GameProperties;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int MaxPlayerCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FGameLiftPlayerLatencyDetail> PlayerLatencies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FGameLiftDesiredPlayerSessionConfig> DesiredPlayerSessions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString GameSessionData;

public:
	void SetPlacementId(FString Value)
	{
		this->PlacementId = Value;
	}

	void SetQueueName(FString Value)
	{
		this->QueueName = Value;
	}

	void SetGameProperties(TMap<FString, FString> Value)
	{
		this->GameProperties = Value;
	}

	void SetMaxPlayerCount(int Value)
	{
		this->MaxPlayerCount = Value;
	}

	void SetPlayerLatencies(TArray<FGameLiftPlayerLatencyDetail> Value)
	{
		this->PlayerLatencies = Value;
	}

	void SetDesiredPlayerSessions(TArray<FGameLiftDesiredPlayerSessionConfig> Value)
	{
		this->DesiredPlayerSessions = Value;
	}

	void SetGameSessionData(FString Value)
	{
		this->GameSessionData = Value;
	}

	FORCEINLINE FString GetPlacementId() const { return PlacementId; }
	FORCEINLINE FString GetQueueName() const { return QueueName; }
	FORCEINLINE TMap<FString, FString> GetGameProperties() const { return GameProperties; }
	FORCEINLINE int GetMaxPlayerCount() const { return MaxPlayerCount; }
	FORCEINLINE TArray<FGameLiftPlayerLatencyDetail> GetPlayerLatencies() const { return PlayerLatencies; }
	FORCEINLINE TArray<FGameLiftDesiredPlayerSessionConfig> GetDesiredPlayerSessions() const { return DesiredPlayerSessions; }
	FORCEINLINE FString GetGameSessionData() const { return GameSessionData; }
};

USTRUCT(BlueprintType)
struct FGameLiftPlacedPlayerSessionDetail
{
	GENERATED_USTRUCT_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString PlayerId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString PlayerSessionId;

public:
	void SetPlayerId(FString Value)
	{
		this->PlayerId = Value;
	}

	void SetPlayerSessionId(FString Value)
	{
		this->PlayerSessionId = Value;
	}

	FORCEINLINE FString GetPlayerId() const { return PlayerId; }
	FORCEINLINE FString GetPlayerSessionId() const { return PlayerSessionId; }
};

USTRUCT(BlueprintType)
struct FGameLiftGameSessionPlacementDetail
{
	GENERATED_USTRUCT_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString PlacementId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString QueueName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString GameSessionPlacementStatus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<FString, FString> GameProperties;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int MaxPlayerCount;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString GameSessionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString GameSessionId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString GameSessionRegion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FGameLiftPlayerLatencyDetail> PlayerLatencies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString ServerIpAddress;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString ServerPort;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString ServerDnsName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FGameLiftPlacedPlayerSessionDetail> PlacedPlayerSessionDetails;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString GameSessionData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString MatchmakerData;

public:
	void SetPlacementId(FString Value)
	{
		this->PlacementId = Value;
	}

	void SetQueueName(FString Value)
	{
		this->QueueName = Value;
	}

	void SetGameSessionPlacementStatus(FString Value)
	{
		this->GameSessionPlacementStatus = Value;
	}

	void SetGameProperties(TMap<FString, FString> Value)
	{
		this->GameProperties = Value;
	}

	void SetMaxPlayerCount(int Value)
	{
		this->MaxPlayerCount = Value;
	}

	void SetGameSessionName(FString Value)
	{
		this->GameSessionName = Value;
	}

	void SetGameSessionId(FString Value)
	{
		this->GameSessionId = Value;
	}

	void SetGameSessionRegion(FString Value)
	{
		this->GameSessionRegion = Value;
	}

	void SetPlayerLatencies(TArray<FGameLiftPlayerLatencyDetail> Value)
	{
		this->PlayerLatencies = Value;
	}

	void SetServerIpAddress(FString Value)
	{
		this->ServerIpAddress = Value;
	}

	void SetServerPort(FString Value)
	{
		this->ServerPort = Value;
	}

	void SetServerDnsName(FString Value)
	{
		this->ServerDnsName = Value;
	}

	void SetPlacedPlayerSessionDetails(TArray<FGameLiftPlacedPlayerSessionDetail> Value)
	{
		this->PlacedPlayerSessionDetails = Value;
	}

	void SetGameSessionData(FString Value)
	{
		this->GameSessionData = Value;
	}

	void SetMatchmakerData(FString Value)
	{
		this->MatchmakerData = Value;
	}

	FORCEINLINE FString GetPlacementId() const { return PlacementId; }
	FORCEINLINE FString GetQueueName() const { return QueueName; }
	FORCEINLINE FString GetGameSessionPlacementStatus() const { return GameSessionPlacementStatus; }
	FORCEINLINE TMap<FString, FString> GetGameProperties() const { return GameProperties; }
	FORCEINLINE int GetMaxPlayerCount() const { return MaxPlayerCount; }
	FORCEINLINE FString GetGameSessionName() const { return GameSessionName; }
	FORCEINLINE FString GetGameSessionId() const { return GameSessionId; }
	FORCEINLINE FString GetGameSessionRegion() const { return GameSessionRegion; }
	FORCEINLINE TArray<FGameLiftPlayerLatencyDetail> GetPlayerLatencies() const { return PlayerLatencies; }
	FORCEINLINE FString GetServerIpAddress() const { return ServerIpAddress; }
	FORCEINLINE FString GetServerPort() const { return ServerPort; }
	FORCEINLINE FString GetServerDnsName() const { return ServerDnsName; }
	FORCEINLINE FString GetGameSessionData() const { return GameSessionData; }
	FORCEINLINE FString GetMatchmakerData() const { return MatchmakerData; }
	FORCEINLINE TArray<FGameLiftPlacedPlayerSessionDetail> GetPlacedPlayerSessionDetails() const { return PlacedPlayerSessionDetails; }
};

USTRUCT(BlueprintType)
struct FGameLiftStartGameSessionPlacementResult
{
	GENERATED_USTRUCT_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FGameLiftGameSessionPlacementDetail GameSessionPlacementDetail;

public:
	void SetGameSessionPlacementDetail(FGameLiftGameSessionPlacementDetail Value)
	{
		this->GameSessionPlacementDetail = Value;
	}

	FORCEINLINE FGameLiftGameSessionPlacementDetail GetGameSessionPlacementDetail() const { return GameSessionPlacementDetail; }
};

USTRUCT(BlueprintType)
struct FGameLiftDescribeGameSessionPlacementConfig
{
	GENERATED_USTRUCT_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString PlacementId;

public:
	void SetPlacementId(FString Value)
	{
		this->PlacementId = Value;
	}

	FORCEINLINE FString GetPlacementId() const { return PlacementId; }
};

USTRUCT(BlueprintType)
struct FGameLiftDescribeGameSessionPlacementResult
{
	GENERATED_USTRUCT_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FGameLiftGameSessionPlacementDetail GameSessionPlacementDetail;

public:
	void SetGameSessionPlacementDetail(FGameLiftGameSessionPlacementDetail Value)
	{
		this->GameSessionPlacementDetail = Value;
	}

	FORCEINLINE FGameLiftGameSessionPlacementDetail GetGameSessionPlacementDetail() const { return GameSessionPlacementDetail; }
};