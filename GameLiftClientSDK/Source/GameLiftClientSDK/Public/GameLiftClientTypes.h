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

	FORCEINLINE int GetMaxPlayerCount() const { return MaxPlayerCount; }
	FORCEINLINE FString GetAliasId() const { return AliasId; }
	FORCEINLINE FString GetFleetId() const { return FleetId; }
	FORCEINLINE FString GetGameLiftLocalFleetId() const { return "fleet-1a2b3c4d-5e6f-7a8b-9c0d-1e2f3a4b5c6d"; }
	FORCEINLINE TMap<FString, FString> GetGameProperties() const { return GameProperties; }
};

USTRUCT(BlueprintType)
struct FGameLiftCreateGameSessionResult
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString GameSessionId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString GameSessionStatus;

	void SetGameSessionId(FString Value) {
		this->GameSessionId = Value;
	}

	void SetGameSessionStatus(FString Value) {
		this->GameSessionStatus = Value;
	}

	FORCEINLINE FString GetGameSessionId() const { return GameSessionId; }
	FORCEINLINE FString GetGameSessionStatus() const { return GameSessionStatus; }
};