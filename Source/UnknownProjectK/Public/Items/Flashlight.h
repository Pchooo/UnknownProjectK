// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseItem.h"
#include "Flashlight.generated.h"

/**
 * 
 */
UCLASS()
class UNKNOWNPROJECTK_API AFlashlight : public ABaseItem
{
	GENERATED_BODY()
public:
    virtual void DoAction() override;
    virtual void Drop() override;

protected:
  
private:
    bool IsLightOn = false;
};
