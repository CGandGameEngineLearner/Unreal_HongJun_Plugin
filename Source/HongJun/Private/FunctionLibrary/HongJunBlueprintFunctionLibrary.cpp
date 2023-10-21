﻿// Fill out your copyright notice in the Description page of Project Settings.

// include AirSim


#include "AirBlueprintLib.h"
#include "AirSimGameMode.h"
#include "FunctionLibrary/HongJunBlueprintFunctionLibrary.h"

void UHongJunBlueprintFunctionLibrary::SetVehiclePoseByAirSimNedPose(FString VehicleName,FVector NewLocation,FRotator NewRotator,bool IgnoreCollision)
{
	ASimModeBase* SimModeBase=ASimModeBase::getSimMode();

	std::string S_VehicleName(TCHAR_TO_UTF8(*VehicleName));
	PawnSimApi* VehicleSimApi=SimModeBase->getVehicleSimApi(S_VehicleName);
	
	msr::airlib::Pose NewPose=MakePose(NewLocation,NewRotator);
	SimModeBase->getGlobalNedTransform().fromGlobalNed(NewPose);
	
	VehicleSimApi->setPose(NewPose,IgnoreCollision);
	
}

FTransform UHongJunBlueprintFunctionLibrary::GetNedOriginTransform()
{
	ASimModeBase* SimModeBase=ASimModeBase::getSimMode();
	return std::move(SimModeBase->getGlobalNedTransform().getGlobalTransform());
}

FTransform UHongJunBlueprintFunctionLibrary::UnrealTransformToAirSimNedTransform(FTransform NedOriginTransform,FTransform UnrealTransform)
{
	FTransform RelativeTransform=UnrealTransform.GetRelativeTransform(NedOriginTransform);
	FVector NedOriginLocation(RelativeTransform.GetLocation().X/100,RelativeTransform.GetLocation().Y/100,-RelativeTransform.GetLocation().Z/100);
	RelativeTransform.SetLocation(NedOriginLocation);
	FRotator NedOriginRotator(RelativeTransform.GetRotation().Euler().X,RelativeTransform.GetRotation().Euler().Y,-RelativeTransform.GetRotation().Euler().Z);
	RelativeTransform.SetRotation(NedOriginRotator.Quaternion());
	return RelativeTransform;
}


void UHongJunBlueprintFunctionLibrary::AirPoseToUnrealPose(msr::airlib::Pose AirPose,FVector& UnrealLocation,FRotator& UnrealRotator)
{
	ASimModeBase* SimModeBase=ASimModeBase::getSimMode();
	FTransform UnrealTransform=SimModeBase->getGlobalNedTransform().fromGlobalNed(AirPose);
	UnrealLocation=UnrealTransform.GetLocation();
	UnrealRotator=UnrealTransform.GetRotation().Rotator();
}


msr::airlib::Vector3r UHongJunBlueprintFunctionLibrary::FVectorToAirVector3r(FVector FVector)
{
	msr::airlib::Vector3r AirVector3r;
	AirVector3r<<FVector.X,FVector.Y,FVector.Z;
	return std::move(AirVector3r);
}

msr::airlib::Pose UHongJunBlueprintFunctionLibrary::MakePose(FVector Location, FRotator Rotator)
{
	msr::airlib::Pose NewPose;
	
	NewPose.position=UHongJunBlueprintFunctionLibrary::FVectorToAirVector3r(Location);
	NewPose.orientation= msr::airlib::VectorMath::toQuaternion(Rotator.Pitch,Rotator.Roll,Rotator.Yaw);

	return std::move(NewPose);
}
