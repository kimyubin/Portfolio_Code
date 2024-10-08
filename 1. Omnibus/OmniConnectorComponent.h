// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OmnibusTypes.h"
#include "Components/SphereComponent.h"
#include "OmniConnectorComponent.generated.h"

class USplineComponent;
class AOmniRoad;
/**
 * 
 */
UCLASS()
class OMNIBUS_API UOmniConnectorComponent : public USphereComponent
{
	GENERATED_BODY()

public:
	UOmniConnectorComponent();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * 상위 옴니 로드 및 컴포넌트가 따라가야하는 스플라인 포인트 위치 추적.
	 * @param InOwnerOmniRoad : 상위 옴니 로드
	 * @param InOwnerSpline : 상위 스플라인
	 * @param InSplinePointPosition : 스플라인 포인트 위치. 시작인지 끝인지 지정.
	 * @param InAccessPointIdx : 옴니 로드에서 위치 Idx.
	 */
	void SetOwnerOmniRoadAndSpline(AOmniRoad* InOwnerOmniRoad, USplineComponent* InOwnerSpline, const ERoadConnectorPoint InSplinePointPosition, const int32 InAccessPointIdx );

	/**
	 * 상위 옴니 로드 및 컴포넌트가 따라가야하는 스플라인 포인트 위치 추적.
	 * @param InOwnerOmniRoad : 상위 옴니 로드
	 * @param InOwnerSpline : 상위 스플라인
	 * @param InSplinePointIdx : 스플라인 포인트 위치. 시작인지 끝인지 지정. ERoadConnectorPoint로 변환함.
	 * @param InAccessPointIdx : 옴니 로드에서 위치 Idx.
	 */
	void SetOwnerOmniRoadAndSpline(AOmniRoad* InOwnerOmniRoad, USplineComponent* InOwnerSpline, const int32 InSplinePointIdx, const int32 InAccessPointIdx);

	AOmniRoad*          GetOwnerOmniRoad() const;
	int                 GetSplinePointIdx() const;
	ERoadConnectorPoint GetSplinePointPosition() const;

	/** 부모 스플라인 포인트의 위치와 회전으로 조정 */
	void    SetRelativeTransformToSpline();
	
	FVector GetSplinePointInsideTangent() const;
	FVector GetSplinePointInsideTangentNormal() const;
	void    ChangeSplineTangentNormal(const UOmniConnectorComponent* InTarget) const;

	FVector GetSplinePointPos() const;
	
	/**
	 * 현재 포인트가 시작 지점이면, 상대 탄젠트 방향 반전.
	 * @return : 현 컴포넌트가 시작 스플라인 포인트라면 -1.0. 아니라면 1.0
	 */
	double GetStartPointTangentFactor() const;
	
	int32  GetAccessPointIdx() const { return AccessPointIdx; }

private:
	TWeakObjectPtr<AOmniRoad>        OwnerOmniRoad;
	TWeakObjectPtr<USplineComponent> OwnerSpline;
	ERoadConnectorPoint              SplinePointPosition;

	/** 감지한 OmniRoad의 ID */
	uint64 DetectedTargetOmniRoadID;

	/** 본 컴포넌트가 저장된 리스트 idx  */
	int32 AccessPointIdx;
};
