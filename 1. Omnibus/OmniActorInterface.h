// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "OmniActorInterface.generated.h"

class UOmniTimeManager;
class AOmnibusRoadManager;
class UOmnibusUIsHandler;
class UOmnibusPlayData;
class UOmnibusGameInstance;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UOmniActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 공용 ID 함수 정의.
 */
class OMNIBUS_API IOmniActorInterface
{
	GENERATED_BODY()

	friend class AOmnibusGameStateBase;

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
protected:
	/**
	 * 레벨에서 로드되는 모든 액터의 BeginPlay()가 호출된 이후에 실행됩니다.
	 * 액터 초기화 순서가 필요한 경우에 사용합니다.
	 * 
	 * @note 플레이 중 스폰되는 경우 발동되지 않습니다.
	 */
	virtual void PostBeginPlay() = 0;

	/** 아이디 생성 및 세팅. */
	virtual void SetOmniID() = 0;

public:
	virtual uint64 GetOmniID() = 0;

protected:
	/** 게임 인스턴스 및 시스템 객체 */
	UFUNCTION()
	virtual UOmnibusGameInstance* GetOmniGameInstance() const = 0;
	UFUNCTION()
	virtual UOmnibusPlayData* GetOmnibusPlayData() const = 0;
	UFUNCTION()
	virtual UOmnibusUIsHandler* GetOmnibusUIsHandler() const = 0;
	UFUNCTION()
	virtual AOmnibusRoadManager* GetOmnibusRoadManager() const = 0;
	UFUNCTION()
	virtual UOmniTimeManager* GetOmniTimeManager() const = 0;
};
