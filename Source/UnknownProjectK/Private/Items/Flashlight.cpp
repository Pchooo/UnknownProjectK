// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Flashlight.h"

#include "Components/SpotLightComponent.h"
 DEFINE_LOG_CATEGORY_STATIC(FlashlightLog, All, All)
AFlashlight::AFlashlight()
{
    SpotLightComponent = CreateDefaultSubobject<USpotLightComponent>("SpotLightComponent");
    SpotLightComponent->SetupAttachment(GetRootComponent());
    IsLightOn = false;
    SpotLightComponent->SetVisibility(IsLightOn);
}


void AFlashlight::DoAction()
{
   //TODO: ON or OFF
    IsLightOn = !IsLightOn;
    SpotLightComponent->SetVisibility(IsLightOn);
    if(IsLightOn)
    {
       UE_LOG(FlashlightLog, Warning, TEXT("ON"));
    }else{
      
       UE_LOG(FlashlightLog, Warning, TEXT("OFF"));
    }
    
}


// void AFlashlight::Drop() //Flashlight is non droppable
// {
//    return;
// }