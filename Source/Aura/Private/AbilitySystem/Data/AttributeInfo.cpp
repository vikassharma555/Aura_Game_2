// CopyrightVIkasAuraProject


#include "AbilitySystem/Data/AttributeInfo.h"

#include "Misc/TrackedActivity.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound)
{
	for (const FAuraAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag.MatchesTag(AttributeTag))
		{
			return Info;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find attribute info for tag [%s] on AttributeInfo [%s]"),
			*AttributeTag.ToString(), *GetNameSafe(this));
	}

	return FAuraAttributeInfo();
}
