// CopyrightVIkasAuraProject


#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	// When GameplayEffect(GE_Health, GE_Mana...) is applied ( HealthPotion/ ManaPotion)...get notification...using delegates
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
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
