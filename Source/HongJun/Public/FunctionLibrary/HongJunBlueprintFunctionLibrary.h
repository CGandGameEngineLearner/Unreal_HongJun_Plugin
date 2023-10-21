// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Classes/Kismet/BlueprintFunctionLibrary.h"

#include "SimMode/SimModeBase.h"

#include "HongJunBlueprintFunctionLibrary.generated.h"



/**
 * 
 */
UCLASS()
class HONGJUN_API UHongJunBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	/**
	* 设置AirSim载具的姿态，注意这里设置的是在AirSim的坐标系下的状态 注意使用弧度制设置旋转
	* @param VehicleName  目标载具名，必须是ASCII编码
	* @param NewLocation 坐标
	* @param NewRotator 旋转 注意这里应该用弧度制！
	* @param IgnoreCollision 是否忽略碰撞
	*/	
	UFUNCTION(BlueprintCallable,Category="AirSim | Vehicle API")
	static void SetVehiclePoseByAirSimNedPose(FString VehicleName,FVector NewLocation,FRotator NewRotator,bool IgnoreCollision);
	
	UFUNCTION(BlueprintCallable,Category="AirSim | World API")
	static FTransform GetNedOriginTransform();

	UFUNCTION(BlueprintCallable,Category="AirSim | World API")
	static FTransform UnrealTransformToAirSimNedTransform (FTransform NedOriginTransform,FTransform UnrealTransform);
	
	static void AirPoseToUnrealPose(msr::airlib::Pose AirPose,FVector& UnrealLocation,FRotator& UnrealRotator);

	static msr::airlib::Vector3r FVectorToAirVector3r(FVector FVector);
	
	

	
	
	static msr::airlib::Pose MakePose(FVector Location,FRotator Rotator);
};
