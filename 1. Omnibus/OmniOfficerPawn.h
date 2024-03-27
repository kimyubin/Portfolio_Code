// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "OmniOfficerPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class OMNIBUS_API AOmniOfficerPawn : public APawn
{
	GENERATED_BODY()

public:
	AOmniOfficerPawn();

protected:
	virtual void BeginPlay() override;

	/** 기준 기본값을 기반으로 값 생성. 생성자 및 블루프린트에서 수정 후 BeginPlay에서도 사용 */
	void InitSettings();

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// 맵 이동 관련
	void MoveCameraInput(const FInputActionValue& InputValue);
	void SetDragActive(const bool bInDragActive, const FVector2D& InMousePosition);
	void DragMap(const FVector2D& InMousePosition);

	// 카메라 줌 관련	
	void ZoomCameraInput(const FInputActionValue& InputValue);
	void UpdateCameraZoom(const float DeltaTime);
	float GetDesiredOrthoWidth() const;

	bool AddZoomStep(const int InZoomStepDelta);
	bool AddZoomStep(const float InZoomStepAxis);

	// 액터 위치 관련	
	void GoToActor(const FVector& TargetPosition);
	void SetDefaultPawnLocation(const FVector& TargetPosition);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CameraComponent, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* PlayerCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CameraComponent, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** 줌 속도  */
	UPROPERTY(EditAnywhere, Category = CameraControlSettings, meta = (AllowPrivateAccess = "true"))
	float ZoomSpeed;

	/** 최대 줌 단계. 줌 조절 단계 수*/
	UPROPERTY(EditAnywhere, Category = CameraControlSettings, meta = (AllowPrivateAccess = "true"))
	uint8 MaxZoomStep;

	UPROPERTY(EditAnywhere, Category = CameraControlSettings, meta = (AllowPrivateAccess = "true"))
	uint8 StartZoomStep;

	UPROPERTY(EditAnywhere, Category = CameraControlSettings, meta = (AllowPrivateAccess = "true"))
	float MaxOrthoWidth;

	UPROPERTY(EditAnywhere, Category = CameraControlSettings, meta = (AllowPrivateAccess = "true"))
	float MinOrthoWidth;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CameraControlSettings, meta = (AllowPrivateAccess = "true"))
	int CurrentZoomStep;

	/** 한 스탭당 단위 orthoWidth*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CameraControlSettings, meta = (AllowPrivateAccess = "true"))
	float UnitOrthoWidth;

	bool      bCameraZooming;
	bool      bUsingMouseWheelCameraZoom;    // 휠로 줌
	FVector2D PrevScrollUnderCursorLocation; // 휠 굴릴 때 커서 아래 위치 임시 저장.

	bool      bDragActive;
	FVector2D DragStartMouseLocation;		 // 드래그 시작 지점 마우스 위치
};
