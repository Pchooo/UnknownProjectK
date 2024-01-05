// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Flashlight.h"

#include "Components/SpotLightComponent.h"

AFlashlight::AFlashlight()
{
   SpotLightComponent = CreateDefaultSubobject<USpotLightComponent>("SpotLightComponent");
   SpotLightComponent->SetupAttachment(GetRootComponent());
}
void AFlashlight::DoAction() {
   //TODO: ON or OFF
   if(IsLightOn)
   {
      
   }else{
      
   }
}
void AFlashlight::Drop() //Flashlight is non non droppable
{
   return;
}