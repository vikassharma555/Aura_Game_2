// CopyrightVIkasAuraProject


#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AuraGameplayTags.h"
//#include "Internationalization/Text.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	// When GameplayEffect(GE_Health, GE_Mana...) is applied ( HealthPotion/ ManaPotion)...get notification...using delegates
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);

	
	
	// const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
	// GEngine->AddOnScreenDebugMessage(
	// 	-1,
	// 	10.f,
	// 	FColor::Blue,
	// 	FString::Printf(TEXT("Tag : %s"), *GameplayTags.Attribute_Secondary_Armor.ToString())
	// 	);
	
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* Asc, const FGameplayEffectSpec& EffectSpec,
                                                FActiveGameplayEffectHandle ActiveEffectHandle) const
{
	//retrieve GameplayTags associated to GameplayEffect (attached in GE_Health...)
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	// broadcast -> callback function (lambda) -> attached to EffectAssetTag -> In UOverlayWidgetController
	EffectAssetTag.Broadcast(TagContainer);	
}