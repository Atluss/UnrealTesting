// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

namespace UnrealTesting
{

class UNREALTESTING_API Battery
{
public:
	Battery();
    Battery(float PercentIn);

    void Charge();
    void UnCharge();
    
    float GetPercent() const;
    FColor GetColor() const;
    FString ToString() const;

    bool operator>=(const Battery& rhs) const{return GetPercent() >= rhs.GetPercent();};
    bool operator==(const Battery& rhs) const{return FMath::IsNearlyEqual(GetPercent(), rhs.GetPercent());};
    
private:
    float Percent{1.0f};
    void SetPercent(float PercentIn);
};
} // namespace UnrealTesting