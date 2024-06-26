// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OmniRoad.h"
#include "GameFramework/Actor.h"
#include "OmniRoadDefaultTwoLane.generated.h"

using namespace std;

/**
 * 기본 왕복 2차선 도로. 
 */
UCLASS()
class OMNIBUS_API AOmniRoadDefaultTwoLane : public AOmniRoad
{
	GENERATED_BODY()

public:
	AOmniRoadDefaultTwoLane();
#if WITH_EDITOR
	virtual void PostEditMove(bool bFinished) override;
#endif // WITH_EDITOR

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	virtual void Tick(float DeltaTime) override;

	/**
	 * 이웃하는 도로 감지 및 추가.
	 */
	virtual void DetectAllConnectedOmniRoad() override;
	
	/** RoadSpline의 시작과 끝 위치를 특정 간격으로 스냅하기. z축 0.0으로 고정. 말단위치*/
	UFUNCTION(BlueprintCallable, Category = PostEditMove)
	void SnapRoadSplineTerminalLocation();

	/////////////////////////////////////////////////////////////////////
	// Construction Script 전용 함수 시작.

	UFUNCTION(BlueprintCallable, Category = CustomConstructionScript)
	void MakeSplineMeshComponentAlongSpline();

	UFUNCTION(BlueprintCallable, Category = CustomConstructionScript)
	void UpdateLaneSplinesAlongRoadCenter();

	// Construction Script 전용 함수 끝.
	/////////////////////////////////////////////////////////////////////

	virtual USplineComponent* GetSplineToNextRoad(AOmniRoad* InPrevRoad, AOmniRoad* InNextTargetRoad) override;

	UFUNCTION()
	USplineComponent* GetMainRoadSpline() const;

};
