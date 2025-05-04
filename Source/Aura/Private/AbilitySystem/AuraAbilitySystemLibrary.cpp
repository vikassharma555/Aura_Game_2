// CopyrightVIkasAuraProject


#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "AbilitySystem/Data/AttributeInfo.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* Pc = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(Pc->GetHUD()))
		{
			AAuraPlayerState* Ps = Pc->GetPlayerState<AAuraPlayerState>();
			UAbilitySystemComponent* Asc = Ps->GetAbilitySystemComponent();
			UAttributeSet* As = Ps->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(Pc, Ps, Asc,As);
			return AuraHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}

	return nullptr;
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	if (APlayerController* Pc = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(Pc->GetHUD()))
		{
			AAuraPlayerState* Ps = Pc->GetPlayerState<AAuraPlayerState>();
			UAbilitySystemComponent* Asc = Ps->GetAbilitySystemComponent();
			UAttributeSet* As = Ps->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(Pc, Ps, Asc,As);
			return AuraHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}

	return nullptr;
}
