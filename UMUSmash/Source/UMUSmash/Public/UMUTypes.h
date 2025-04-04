

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UMUTypes.generated.h"

UENUM(BlueprintType)
enum class EFaceDirection : uint8
{
	Left,
	Right,
};

UENUM(BlueprintType)
enum class EInputDirection : uint8
{
	Up,
	Down,
	Back,
	Forward,
	None
};

UENUM(BlueprintType)
enum class EShape : uint8
{
	Sqhere,
	Box,
	Pill
};

UENUM(BlueprintType)
enum class CollisionType : uint8
{
	Normal,
	Sweet,
	Sour,
	Spike,
	Metlor,
	Multi
};
UENUM(BlueprintType)
enum class EPlayerStateType : uint8
{
	Idle,
	Move,
	Crouch,
	Sprint,
	Jump,
	Fall,
	Hit,
	Launch,
	Ledge,
	Dead,
	Shield,
	Tumble,
	ShieldTumble,
	Prone,
	Stun,
	Dizzy,
	Ability,
	Dodge,
	FreeFall,
	Held,
	Hold
};

UENUM(BlueprintType)
enum class EHitStateType : uint8
{
	Normal,
	Intangible,
	Invincible,
	Armor,
	Shield
};

UENUM(BlueprintType)
enum class BuffeerType : uint8
{
	Attack,
	Special,
	Jump,
	Shield,
	None
};

UENUM(BlueprintType)
enum class ButtonType : uint8
{
	Pressed,
	Released
};

UENUM(BlueprintType)
enum class ECharacter : uint8
{
	None        UMETA(DisplayName = "None"),
	Fighter        UMETA(DisplayName = "Fighter"),
	SwordMan    UMETA(DisplayName = "SwordMan"),
	Gunner        UMETA(DisplayName = "Gunner"),
	Hats        UMETA(DisplayName = "Hats"),
	Mage        UMETA(DisplayName = "Mage"),
	Unknown        UMETA(DisplayName = "Unknown"),
	Bob            UMETA(DisplayName = "Bob"),
	Random        UMETA(DisplayName = "Random")
};

UENUM(BlueprintType)
enum class EEnableType : uint8
{
	Enable        UMETA(DisplayName = "Enable"),
	Disable    UMETA(DisplayName = "Disable"),
	Custom        UMETA(DisplayName = "Custom")
};

UENUM(BlueprintType)
enum class EGameModes : uint8
{
	VS        UMETA(DisplayName = "VS"),
	Online    UMETA(DisplayName = "Online"),
	Arcade    UMETA(DisplayName = "Arcade")
};

UENUM(BlueprintType)
enum class EInGameModes : uint8
{
	Stock        UMETA(DisplayName = "Stock"),
	Time        UMETA(DisplayName = "Time"),
	MiniGame    UMETA(DisplayName = "MiniGame"),
	BossFight    UMETA(DisplayName = "Boss Fight")
};

UENUM(BlueprintType)
enum class EMaps : uint8
{
	ConfilcZone,
	ConcludingGround,
	AnotherLevel,
	TheWalkWay,
	IceZone,
	Random
};

UENUM(BlueprintType)
enum class EMenus : uint8
{
	Main            UMETA(DisplayName = "Main"),
	CharacterSelect    UMETA(DisplayName = "CharacterSelect"),
	MapSelect        UMETA(DisplayName = "MapSelect"),
	Online            UMETA(DisplayName = "Online"),
	Host            UMETA(DisplayName = "Host"),
	Join            UMETA(DisplayName = "Join"),
	Lobby            UMETA(DisplayName = "Lobby"),
	Title            UMETA(DisplayName = "Title")
};

UENUM(BlueprintType)
enum class EAttackType : uint8
{
	None,
	TiltUp,
	TiltDown,
	TiltForward,
	TiltBack,
	TiltNuetral,
	AirUp,
	AirDown,
	AirForward,
	AirBack,
	AirNuetral,
	SmashUp,
	SmashDown,
	SmashForward,
	SmashBack,
	SpecialUp,
	SpecialDown,
	SpecialForward,
	SpecialBack,
	SpecialNuetral,
	Grab,
	ThorwUp,
	ThorwDown,
	ThorwForward,
	ThorwBack,
	Pumble,
	LedgeAttack,
	ProneAttack,
	DodgeSpot,
	DodgeAir,
	DodgeBack,
	DodgeForard,
	Super
};

UENUM(BlueprintType)
enum class EAbilityType : uint8
{
	None,
	Basic,
	Special,
	Air,
	Smash,
	Super,
	Dodge,
	Taunt,
	Ledge,
	Throw,
	Prone,
	Grab,
	Other
};

UENUM(BlueprintType)
enum class EAttackTable : uint8
{
	Attack1,
	Attack2,
	Attack3,
	Attack4,
	Attack5,
	Attack6,
	Attack7,
	Attack8,
	Attack9,
	Attack10,
	Attack11,
	Attack12,
	Attack13,
	Attack14,
	Attack15,
	Attack16,
	Attack17,
	Attack18,
	Attack19,
	Attack20,
	Attack21,
	Attack22,
	Attack23,
	Attack24,
	Attack25,
	Attack26,
	Attack27,
	Attack28,
	Attack29,
	Attack30,
};