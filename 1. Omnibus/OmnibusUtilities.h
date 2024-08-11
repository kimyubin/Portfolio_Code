// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <random>

#include "CoreMinimal.h"
#include "Omnibus.h"
#include "UObject/NoExportTypes.h"
#include "OmnibusUtilities.generated.h"

class ATextRenderActor;


////////////////////////////////////////////////
// 게임플레이 유틸리티 정적 클래스 및 함수 모음
////////////////////////////////////////////////


//~=============================================================================
// 테스트 및 디버그 출력

/**
 * 개체 유효성 테스트 및 로그 출력.
 * 유효하지 않을 경우, 로그 출력 및 false 반환.
 * 
 * @param UObjPtr : 테스트할 개체
 * @return 객체가 사용가능하면 true 반환. null, pending kill, 가비지 수집 대상인 경우 false 반환.
 * @see IsOmniValidLog
 */
#define OB_IS_VALID(UObjPtr) IsOmniValidLog(UObjPtr, GET_VAR_NAME(UObjPtr), OB_LOG_FUNC_LINE_INFO)

/**
 * TWeakObjectPtr 객체 유효성 테스트 및 로그 출력
 * nullptr, bEvenIfPendingKill == true 등 유효하지 않을 경우, 로그 출력 및 false 반환.
 * 
 * @param WeakObjectPtr : 테스트할 TWeakObjectPtr 객체
 * @return 객체가 사용가능하면 true 반환. null, pending kill, 가비지 수집 대상인 경우 false 반환.
 * @see IsOmniValidLog
 */
#define OB_IS_WEAK_PTR_VALID(WeakObjectPtr) IsOmniTWeakObjectValidLog(WeakObjectPtr, GET_VAR_NAME(WeakObjectPtr), OB_LOG_FUNC_LINE_INFO)

/**
 * 개체 유효성 테스트 및 로그 출력
 * 
 * @param    Test           테스트할 개체
 * @param    InVarName      테스트할 개체의 변수명
 * @param    InLogFuncInfo  오류가 난 함수 위치 정보.
 * @return   객체가 사용가능하면 true 반환. null, pending kill, 가비지 수집 대상이 아닌 경우.
 * @see OB_IS_VALID
 */
FORCEINLINE bool IsOmniValidLog(const UObject* Test, const FString& InVarName, const FString& InLogFuncInfo)
{	
	if (IsValid(Test))
		return true;

	UE_LOG(Omnibus, Warning, TEXT("%s %s is not valid."), *InLogFuncInfo, *InVarName)
	
	return false;
}

/**
 * TWeakObjectPtr 객체 유효성 테스트 및 로그 출력
 * @param    Test           테스트할 TWeakObjectPtr 객체
 * @param    InVarName      테스트할 객체의 변수명
 * @param    InLogFuncInfo  오류가 난 함수 위치 정보.
 * @return   객체가 사용가능하면 true 반환. null, pending kill, 가비지 수집 대상이 아닌 경우.
 * @see OB_IS_VALID
 */
FORCEINLINE bool IsOmniTWeakObjectValidLog(const TWeakObjectPtr<UObject> Test, const FString& InVarName, const FString& InLogFuncInfo)
{
	if (Test.IsValid())
		return true;

	UE_LOG(Omnibus, Warning, TEXT("TWeakObjectPtr error %s %s is not valid."), *InLogFuncInfo, *InVarName)
	
	return false;
}

/** 조건문 로그. if문을 대체하고, 조건이 true인 경우 로그를 남깁니다.*/
#define OB_IF(cond) \
if ( IfTureLog( cond, *OB_LOG_FUNC_LINE_INFO ) )

/** 참인 경우 로그를 남깁니다/ */
inline bool IfTureLog(const bool InCheck, const FString& InLineInfo)
{
	if (InCheck == true)
	{
		UE_LOG(Omnibus, Warning, TEXT("%s %s"), *InLineInfo, *FString::Printf(TEXT("conditional statement failure")))
	}
	
	return InCheck;
}


//~=============================================================================
// 메시지
namespace OmniMsg
{
	/** 확인창이 포함된 대화상자형 메시지 */
	void Dialog(const FString& InMsg);
	
	/** 일반 토스트 팝업 메시지. 확인하지 않음. */
	void ToastMsg(const FString& InMsg);
}

/**
 * 디버그용 3D Text Render를 스폰합니다.
 * ATextRenderActor의 스폰 및 설정 절차를 간소화 시킨 함수입니다.
 * 
 * @param InLocation 스폰 위치
 * @param InLifeSpan 렌더 액터의 수명(초)
 * @param InText 표기할 텍스트
 * @param InWorldSize 문자 크기. 50 전후부터 보이며 200 이상부터 잘 보입니다.
 * @param InZOffset 스폰 위치의 Z축 오프셋입니다. 이 값만큼 Z축에 더해져 스폰됩니다.
 * @param InRenderColor 문자 색상
 * 
 * @note 에디터 전용.
 */
ATextRenderActor* SimpleTextRender(const FVector& InLocation, const float InLifeSpan, const FString& InText, const float InWorldSize, const double InZOffset = 10.0f, const FColor& InRenderColor = FColor::Red);


//~=============================================================================
/* 객체 ID 생성용 */
UCLASS()
class OMNIBUS_API UOmniID : public UObject
{
	GENERATED_BODY()

public:
	static uint64 GenerateID_Number(const AActor* InActor);

	/**
	 * 상위 19bit : 날짜 정보. 10bit(연) : 1900 ~ 2924, 4bit(월) : 1~12, 5bit(일) : 1~31
	 * 중위 17bit : 실행 시간 초
	 * 하위 28bit : 일일 생성 순번
	 */
	static uint64 GenerateID_NumberByDate();
	static std::string GetID_DateToString(const uint64 InID);

	/** 액터가 스폰된 위치와 레벨 기반으로 ID 생성. */
	static uint64 GenerateID_NumberByPos(const AActor* InActor);
	static uint64 GenerateID_NumberByHash(const AActor* InActor);
	static std::string GetID_InfoToString(const uint64 InID);

private:
	static std::atomic<uint64> ID_TodayCountAtomic;
};

/** 시간 관련 함수 및 변수를 취급 */
struct FOmniTime
{
	static void   SetLevelStartTime_Sec();
	static uint64 GetLevelStartTime_Sec();
	static uint64 GetNowTime_Sec();

	/** 현재 마이크로초  */
	static int64 GetNowMicroSec();
	
	/**
	 * 간단한 형태의 일회용 타이머입니다.
	 * 취소 및 갱신할 수 없습니다.
	 * 반복할 수 없고, InRate 이후 시작합니다.
	 */
	static void SimpleTimer(const AActor* InWorldActor, float InRate, TFunction<void(void)>&& Callback);
	
private:
	/** 게임 시작 시각. 초로 기록 */
	static uint64 LevelStartTime_Sec;
};


//~=============================================================================
// 유용한 함수 모음

struct FOmniStatics
{
	/**
	 * InTestComp와 동일한 ObjectType(Collision Type)을 추적하는 간소화된 오버랩 함수.
	 * InTestComp에 오버랩된 컴포넌트 배열 반환. BeginPlay 이전에 사용.
	 * 
     * @param InTestComp             테스트할 컴포넌트
     * @param InComponentClassFilter 찾고자하는 컴포넌트 클래스 유형
     * @param OutOverlapComps        오버랩된 컴포넌트 배열 반환값.
     * @return 조건에 부합한 요소를 찾으면 true 반환.
     */
	static bool GetOverlapComps(UPrimitiveComponent* InTestComp, UClass* InComponentClassFilter, TArray<UPrimitiveComponent*>& OutOverlapComps);

	/**
	 * InTestComp와 동일한 ObjectType(Collision Type)을 추적하는 간소화된 오버랩 함수.
	 * InTestComp에 오버랩된 컴포넌트 배열 반환. BeginPlay 이전에 사용.
	 * 
	 * @param InTestComp         테스트할 컴포넌트
	 * @param InActorClassFilter 찾고자하는 액터 클래스 유형
	 * @param OutOverlapActors   오버랩된 액터 배열 반환값.
	 * @return  조건에 부합한 요소를 찾으면 true 반환.
	 */
	static bool GetOverlapActors(UPrimitiveComponent* InTestComp, UClass* InActorClassFilter, TArray<AActor*>& OutOverlapActors);

	/**
	 * 지정된 ObjectPath로 에셋 데이터를 가져옴.
	 * 
	 * @param ObjectPath 조회할 객체 경로
	 * @param bIncludeOnlyOnDiskAssets true인 경우 메모리 내 개체가 무시됩니다. 더 빠른 호출 가능
	 * @param bSkipARFilteredAssets true인 경우 IsAsset에 대해 true를 반환하지만 현재 플랫폼의 자산이 아닌 개체를 건너뜁니다.
	 * @return 자산 데이터. 객체를 찾을 수 없으면 유효하지 않음.
	 */
	static FAssetData GetAssetByObjectPath(const FSoftObjectPath& ObjectPath
	                                     , bool bIncludeOnlyOnDiskAssets = false
	                                     , bool bSkipARFilteredAssets    = true);
	/**
	 * 지정된 ObjectPath로 에셋 데이터가 존재하는지 찾습니다.
	 * 
	 * @param ObjectPath 조회할 객체 경로
	 * @return 객체를 찾을 수 있다면 true.
	 */
	static bool IsAssetExists(const FSoftObjectPath& ObjectPath);
	
	/**
	 * ObjectPath + _N 형식으로 중복된 이름을 회피합니다.
	 * 이미 유일한 이름이라면, 숫자를 포함하지 않고, 원본을 반환합니다.
	 * ObjectPath 이름에 숫자가 포함되어 있어도, 이를 무시하고 '_N'을 추가합니다.
	 * AssetToolsModule.CreateUniqueAssetName()의 대안입니다.
	 * 
	 * @param ObjectPath 유일한지 체크할 이름.
	 * @param OutAssetPathName 유일하지 않다면 "_N"을 더해 반환. 이미 유일하다면 그대로 반환.
	 * @return 생성에 성공하면 true;
	 */
	static bool CreateUniqueAssetName(const FString& ObjectPath, FString& OutAssetPathName);

	/**
	 * ThreadSafe 버전 TWeakObjectPtr 동등성 검사.
	 * 개체 유효성을 검사하지 않고, 인덱스와 시리얼의 동일성만 확인합니다.
	 */
	template <typename T>
	FORCEINLINE static bool IsSameWeak(const TWeakObjectPtr<T>& AWeak, const TWeakObjectPtr<T>& BWeak)
	{
		return AWeak.HasSameIndexAndSerialNumber(BWeak);
	};

	/**
	 * ThreadSafe 버전 nullPtr 검사.
	 * 실제 포인터의 유효성 검사가 아니라, TWeakObjectPtr가 비어있는지만 검사합니다.
	 * 
	 * @tparam T 
	 * @param TestWeak 테스트할 약포인터
	 * @param NullWeak 미리 생성된 약포인터가 있다면 사용. 아니라면 nullptr을 사용합니다.
	 * @return 비어있다면(nullptr) true 반환
	 */
	template <typename T>
	FORCEINLINE static bool IsNullWeak(const TWeakObjectPtr<T>& TestWeak, const TWeakObjectPtr<T>& NullWeak = nullptr)
	{
		return IsSameWeak(TestWeak, NullWeak);
	};

	/**
	 * ThreadSafe 버전 유효성 검사.
	 * 실제 포인터의 유효성 검사가 아니라, TWeakObjectPtr가 비어있지 않은지만 검사합니다.
	 * 
	 * @tparam T 
	 * @param TestWeak 테스트할 약포인터
	 * @param NullWeak 미리 생성된 약포인터가 있다면 사용. 아니라면 nullptr을 사용합니다.
	 * @return 비어있지 않다면 true 반환
	 */
	template <typename T>
	FORCEINLINE static bool IsValidSafe(const TWeakObjectPtr<T>& TestWeak, const TWeakObjectPtr<T>& NullWeak = nullptr)
	{
		return IsNullWeak(TestWeak, NullWeak) == false;
	};
	
};

enum class ECityBlockType : uint8;

/** 문자열 관련 유틸리티 */
namespace OmniStr
{
	/**
	 * 문자열과 인덱스를 합쳐서 FName으로 반환.
	 * @return "InNameString_InIdx" 
	 */
	FName ConcatStrInt(const FString& InNameString, const int32 InIdx);

	/** 열거형을 문자열로 변환. 필요에 따라 오버로딩해서 추가예정. */
	FString EnumToString(ECityBlockType InBlockType);
}

/** 비트연산 */
namespace OmniBit
{
	/**
	 * 입력 비트값의 하위 BitCount만큼 추출 후, 시작 위치부터 지정된 개수(count)만큼 채워서 반환. 지정된 비트수 외의 공간은 0으로 채움.
	 * @param InBitVal : 비트값
	 * @param InStartBitOffset : 반환값에서 시작할 지점. 좌측부터, 0~63
	 * @param InBitCount : 사용할(채울) 비트 개수, 1~64 
	 */
	uint64 ExtractFillBit(const uint64 InBitVal, const uint64 InStartBitOffset, const uint64 InBitCount);

	/**
	 * 지정된 범위의 비트를 추출함.(Unsigned)
	 * 입력 비트값을 시작 지점부터 지정된 개수만큼 뽑아, 하위 비트에 채워 반환.
	 * 부호 없음. 
	 * @param InBitValue : 비트값
	 * @param InStartBitOffset : 시작 지점. 좌측부터, 0~63
	 * @param InBitCount : 가져올 비트 개수, 1~64
	 */
	uint64 GetSubBit(const uint64 InBitValue, const uint64 InStartBitOffset, const uint64 InBitCount);

	/**
	 * 지정된 범위의 비트를 추출함.(Signed)
	 * 입력 비트값을 시작 지점부터 지정된 개수만큼 뽑아, 하위 비트에 채워 반환. 첫 비트가 1인 경우 음수로 인식해서 상위 비트를 0 대신 1로 채움
	 * @param InBitValue : 비트값
	 * @param InStartBit : 시작 지점. 좌측부터, 0~63
	 * @param InBitCount : 가져올 비트 개수, 1~64
	 */
	int64 GetSignedBitRange(const uint64 InBitValue, const uint64 InStartBit, const uint64 InBitCount);
}

/** 수식 유틸리티 */
namespace OmniMath
{
	/**
	 * 입력된 숫자를 주어진 범위[0, Max] 내에서 순환시켜 반환.
	 * 음수, 양수 양방향 변환
	 * @param InMax 범위 최대값(범위에 포함됨)
	 * @param InNum 입력값.
	 * @return 범위[0, Max] 내 순환한 값
	 */
	uint32 CircularNum(const uint32 InMax, const int64 InNum);
	
	/**
	 * 입력된 숫자를 주어진 범위 (0.0, Max] 내에서 순환시켜 반환.
	 * 음수, 양수 양방향 변환
	 * 0.0 == Max 으로 간주됨. 0.0은 포함하지 않음.
	 * 
	 * @param InMax 범위 최대값(범위에 포함됨)
	 * @param InNum 입력값.
	 * @return 범위[0, Max] 내 순환한 값
	 */
	double CircularNumF(const double InMax, const double InNum);

	/**
	 * offset 만큼 떨어진 곳에 있는 대상의 절대 Transform 계산
	 * @param InPos : 자신의 위치
	 * @param InDirection : 상대 방향
	 * @param InOffset : 상대 위치 거리
	 * @return Offset 적용 후 Transform
	 */
	FTransform GetTransformAddOffset(const FVector& InPos, const FVector& InDirection, const double InOffset);

	//////////////////
	//벡터, 차원 관련

	FVector2D MakeFVector2D(const FVector& InVector);
	FVector   MakeFVector(const FVector2D& InVector, const double InZ = 0.0);
	
	/**
	 * 경계구역 체크. 좌상, 우하 순서 입력 권장.
	 * @param InVector2D : 체크할 벡터
	 * @param A : 경계가 되는 사각형의 한쪽 모서리. B의 대각 
	 * @param B : 경계가 되는 사각형의 한쪽 모서리. A의 대각
	 */
	FVector2D ClampVector2D(const FVector2D& InVector2D, const FVector2D& A, const FVector2D& B);
	
	/**
	 * 경계구역 체크. 좌상, 우하 순서 입력 권장. z축은 체크하지 않고, 입력된 z축을 그대로 반환.
	 * @param InVector : 체크할 벡터
	 * @param A : 경계가 되는 사각형의 한쪽 모서리. B의 대각 
	 * @param B : 경계가 되는 사각형의 한쪽 모서리. A의 대각
	 * @return : z축 제외 후 경계 체크된 벡터
	 */
	FVector ClampVector(const FVector& InVector, const FVector& A, const FVector& B);

	/**
	 * 입력된 FRotator에서 Yaw값만 취한 후 리턴
	 * @param InRotator Yaw값을 추출할 Rotator
	 * @return Yaw외엔 0.0인 FRotator
	 */
	FORCEINLINE FRotator YawRotator(const FRotator& InRotator)
	{
		return FRotator(0.0, InRotator.Yaw, 0.0);
	}
	
	/**
	 * 입력된 축을 기준으로 FRotator를 회전 후 반환.
	 * @param InRotator 회전할 FRotator
	 * @param InAngle 회전 각도.
	 * @param InAxis 회전 축. 내부에서 정규화해서 처리
	 * @return 회전된 FRotator
	 */
	FRotator RotateAxis(const FRotator& InRotator, const double InAngle, const FVector& InAxis);

	/**
	 * X축을 기준으로 회전
	 * @param InRotator 회전할 FRotator
	 * @param InAngle 회전량. 단위는 도.
	 * @return 회전 후 결과 FRotator
	 */
	FRotator RotateAxisX(const FRotator& InRotator, const double InAngle);

	/**
	 * Y축을 기준으로 회전
	 * @param InRotator 회전할 FRotator
	 * @param InAngle 회전량. 단위는 도.
	 * @return 회전 후 결과 FRotator
	 */
	FRotator RotateAxisY(const FRotator& InRotator, const double InAngle);

	/**
	 * Z축을 기준으로 회전
	 * @param InRotator 회전할 FRotator
	 * @param InAngle 회전량. 단위는 도.
	 * @return 회전 후 결과 FRotator
	 */
	FRotator RotateAxisZ(const FRotator& InRotator, const double InAngle);

	/**
	 * 박스의 폭(y)을 반환
	 * @param InBox 계산할 FBox
	 * @return 박스의 폭
	 */
	double GetBoxWidth(const FBox& InBox);
	
	/////////////////
	// 수치 

	/**
	 * 반올림. 0.5는 가장 가까운 짝수값이 됨.<br>
	 * 양쪽의 정수가 동일한 거리에 있는 경우(==0.5), 가장 가까운 짝수 값 반환.<br>
	 * 1.5-> 2, 0.5->0, -1.5->2, -0.5->0
	 * @param InDouble : 반올림할 부동 소수점 숫자
	 * @param InUnitValue : 반올림에 사용할 단위. 50을 입력하면 50단위로 반올림 처리.
	 */
	double RoundHalfToEvenByUnitValue(const double InDouble, const double InUnitValue = 1.0);

	/**
	 * InUnitValue단위로 스냅되게끔 벡터 위치를 조정 .<br>
	 * 양쪽의 정수가 동일한 거리에 있는 경우(==0.5), 가장 가까운 짝수 값 반환.<br>
	 * 1.5-> 2, 0.5->0, -1.5->2, -0.5->0
	 * @param InVector : 반올림할 FVector
	 * @param InUnitValue : 반올림에 사용할 단위. 50을 입력하면 50단위로 반올림 처리.
	 */
	FVector RoundHalfToEvenVector(const FVector& InVector, const double InUnitValue = 1.0);


	//~=============================================================================
	// 진수 변환

	/** 부호 없는 정수를 16진수 FString으로 변환합니다. 자릿수는 자료형의 크기에 비례합니다. */
	FString ToHex(const uint64 InInt);
	FString ToHex(const uint32 InInt);

	/** 부호 없는 정수를 16진수 FString으로 변환합니다. 자릿수는 자료형의 크기에 비례합니다. 일반 상수용. */
	template <std::integral T>
	FString ToHex(T InInt)
	{
		return ToHex(static_cast<uint64>(InInt));
	}

	/** 부호 없는 정수를 2진수 FString으로 변환합니다. 자릿수는 자료형의 크기에 비례합니다. */
	FString ToBin(const uint64 InInt);
	FString ToBin(const uint32 InInt);

	/** 부호 없는 정수를 2진수 FString으로 변환합니다. 자릿수는 자료형의 크기에 비례합니다. 일반 상수용. */
	template <std::integral T>
	FString ToBin(T InInt)
	{
		return ToBin(static_cast<uint64>(InInt));
	}


	//~=============================================================================
	// 난수

	/** random_device seed 기반 mt19937 엔진 반환. */
	inline std::mt19937 GetRandomEngine()
	{
		std::random_device deviceSeed;
		std::mt19937 rdEngine(deviceSeed());
		return rdEngine;
	}
	
	/**
	 * 비결정적 정수 난수 생성. 닫힌 구간[Min, Max] 사용.
	 * 
	 * @param Min 값 범위 포함
	 * @param Max 값 범위 포함
	 * @return 구간 내 임의의 정수 난수 반환.
	 */
	template <std::integral T>
	T GetIntRandom(const T Min = 0, const T Max = RAND_MAX)
	{
		std::mt19937 rdEngine = GetRandomEngine();
		std::uniform_int_distribution<T> rdRange(Min, Max);
		return rdRange(rdEngine);
	}

	/**
	 * 비결정적 실수 난수 생성. 닫힌 구간[Min, Max] 사용.
	 * 
	 * @param Min 값 범위 포함
	 * @param Max 값 범위 포함
	 * @return 구간 내 임의의 실수 난수 반환.
	 */
	template <std::floating_point T>
	T GetRealRandom(const T Min = static_cast<T>(0.0), const T Max = static_cast<T>(1.0))
	{
		std::mt19937 rdEngine = GetRandomEngine();
		std::uniform_real_distribution<T> rdRange(Min, Max);
		return rdRange(rdEngine);
	}


	template <typename RangeType>
	void Shuffle(RangeType& InRange)
	{
		std::mt19937 rdEngine = GetRandomEngine();
		shuffle(InRange.begin(), InRange.end(), rdEngine);
	}
}


//~=============================================================================
/** 언리얼 엔진 컨테이너 레퍼 함수 모음. */
namespace OmniContainer
{
	///////////////////////////////////////
	// TMap 관련

	/**
	 * 키와 값을 TMap에 추가. 키값이 이미 있으면, 해당 키에 대한 값 갱신
	 * TMap 멤버 할당 및 값 갱신 함수.
	 *
	 * @param InMap : 멤버를 추가할 대상 TMap
	 * @param InKey : 키
	 * @param InValue : 값
	 */
	template <typename InKeyType, typename InValueType, typename SetAllocator, typename KeyFuncs>
	FORCEINLINE void TMap_Emplace(TMap<InKeyType, InValueType, SetAllocator, KeyFuncs>& InMap, const InKeyType& InKey, const InValueType& InValue)
	{
		InValueType* ValuePtr = InMap.Find(InKey);
		if (ValuePtr == nullptr)
			InMap.Emplace(InKey, InValue);
		else
			*ValuePtr = InValue;
	}

	/**
	 * TMap의 지정된 키와 연결된 값을 찾아서 반환. 값이 없거나, 유효하지 않을 경우 nullptr 반환
	 * 
	 * @param InMap 찾을 대상 TMap
	 * @param InKey 찾고자 하는 키
	 * @return 찾아낸 값. 유효하지 않거나 값이 없으면 nullptr 반환
	 */
	template <typename InKeyType, typename InValueType, typename SetAllocator, typename KeyFuncs>
	FORCEINLINE InValueType TMap_Find(TMap<InKeyType, InValueType, SetAllocator, KeyFuncs>& InMap, const InKeyType& InKey)
	{
		InValueType* ValuePtr = InMap.Find(InKey);
		if (ValuePtr == nullptr)
			return nullptr;
		else
			return IsValid(*ValuePtr) ? *ValuePtr : nullptr;
	}



	///////////////////////////////////////
	// TArray 관련

	/**
	 * predicate functor와 일치하는 요소의 인덱스를 모두 찾습니다.
	 *
	 * @param InArray 찾을 배열 
	 * @param Pred 각 요소를 평가할 펑터입니다.
	 * @return 일치하는 요소의 인덱스들을 담은 배열 
	 */
	template <typename InElementType, typename InAllocatorType, typename Predicate>
	FORCEINLINE TArray<int32> FindAllIndexByPredicate(const TArray<InElementType, InAllocatorType>& InArray, Predicate Pred)
	{
		TArray<int32> OutFindIdxArray;

		for (int idx = 0; idx < InArray.Num(); ++idx)
		{
			if (::Invoke(Pred, InArray[idx]))
			{
				OutFindIdxArray.Emplace(idx);
			}
		}
		return OutFindIdxArray;
	}

	/**
	 * predicate functor와 최초로 일치하는 요소를 찾아 제거합니다.
	 *
	 * @param InOutArray 찾을 배열
	 * @param Pred 각 요소를 평가할 펑터입니다.
	 * @return 찾아서 제거했다면 true, 찾지 못했다면 false 입니다.
	 */
	template <typename InElementType, typename InAllocatorType, typename Predicate>
	FORCEINLINE bool RemoveByPredicate(TArray<InElementType, InAllocatorType>& InOutArray, Predicate Pred)
	{
		for (int idx = 0; idx < InOutArray.Num(); ++idx)
		{
			if (::Invoke(Pred, InOutArray[idx]))
			{
				InOutArray.RemoveAt(idx);
				return true;
			}
		}
		return false;
	}

	/**
	 * predicate functor와 최초로 일치하는 요소를 찾아 제거합니다.
	 * 제거한 인덱스에는 마지막 원소가 들어가 빈 공간을 채웁니다.
	 * RemoveByPredicate 보다 효율적이지만 배열의 순서를 유지하지 않습니다.
	 * 
	 * @param InOutArray 찾을 배열
	 * @param Pred 각 요소를 평가할 펑터입니다.
	 * @return 찾아서 제거했다면 true, 찾지 못했다면 false 입니다.
	 */
	template <typename InElementType, typename InAllocatorType, typename Predicate>
	FORCEINLINE bool RemoveSwapByPredicate(TArray<InElementType, InAllocatorType>& InOutArray, Predicate Pred)
	{
		for (int idx = 0; idx < InOutArray.Num(); ++idx)
		{
			if (::Invoke(Pred, InOutArray[idx]))
			{
				InOutArray.RemoveAtSwap(idx);
				return true;
			}
		}
		return false;
	}
}


/**
 * TArray 기반 원형 순회 매크로.
 * [_BeginIdx, _EndIdx) 구간을 순회하는 IdxName를 제시합니다.
 * _BeginIdx가 _EndIdx보다 크다면, _BeginIdx ~ ArrayMax / 0 ~ (_EndIdx - 1) 구간의 인덱스를 순차적으로 따라갑니다.
 * 
 * @param IdxName 사용할 인덱스 이름
 * @param _BeginIdx 시작 번호
 * @param _EndIdx 마지막 다음 번호. 범위에 포함되지 않음.
 * @param _ArrayMax 범위의 크기. Array.Num() or vector.size()
 */
#define For_CircularRange(IdxName, _BeginIdx, _EndIdx, _ArrayMax)\
for (int IdxName = OmniMath::CircularNum(_ArrayMax - 1, _BeginIdx); IdxName != _EndIdx; IdxName = OmniMath::CircularNum(_ArrayMax - 1, IdxName + 1))
