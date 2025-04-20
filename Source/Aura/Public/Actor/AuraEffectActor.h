// CopyrightVIkasAuraProject

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActiveGameplayEffectHandle.h"
#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;
struct FActiveGameplayEffectHandle;
class UGameplayEffect;


UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	RemoveOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	RemoveOnEndOverlap,
	DoNotApply
};

USTRUCT(BlueprintType)
struct FUGameplayEffects
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> GameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EEffectApplicationPolicy ApplicationPolicy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EEffectRemovalPolicy RemovalPolicy;

	FActiveGameplayEffectHandle ActiveGameplayEffectHandle;

	FUGameplayEffects()
	{
		ApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
		RemovalPolicy = EEffectRemovalPolicy::DoNotApply;
	}
	
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();

	
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);
	
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	bool bDestroyAfterEffectApplied = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TArray<FUGameplayEffects> GameplayEffects;
	
};
