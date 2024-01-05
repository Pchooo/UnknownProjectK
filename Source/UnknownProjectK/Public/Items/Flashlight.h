// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseItem.h"
#include "Flashlight.generated.h"

/**
 * 
 */
class USpotLightComponent; 
UCLASS()
class UNKNOWNPROJECTK_API AFlashlight : public ABaseItem
{
	GENERATED_BODY()
public:
    AFlashlight();
    virtual void DoAction() override;
    virtual void Drop() override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component")
    USpotLightComponent* SpotLightComponent;
private:
    bool IsLightOn = false;
};
