#pragma once

#include "CoreMinimal.h"
#include "UMUTypes.generated.h"

UENUM(BlueprintType)
enum class EFaceDirection : uint8
{
	Left				= 0			UMETA(DisplayName = "Left0"),
	Right				= 1			UMETA(DisplayName = "Right1")
};

UENUM(BlueprintType)
enum class EInputDirection : uint8
{
	Temp				= 0			UMETA(DisplayName = "Temp0"),
	Up					= 2			UMETA(DisplayName = "Up2"),
	Down				= 3			UMETA(DisplayName = "Down3"),
	Back				= 4			UMETA(DisplayName = "Back4"),
	Forward				= 5			UMETA(DisplayName = "Forward5"),
	None				= 6			UMETA(DisplayName = "None6")
};			

UENUM(BlueprintType)
enum class EShape : uint8
{		
	Sphere				= 0			UMETA(DisplayName = "Sphere0"),
	Box					= 1			UMETA(DisplayName = "Box1"),
	Pill				= 2			UMETA(DisplayName = "Pill2")
	
};

UENUM(BlueprintType)
enum class ECollisionType : uint8
{
	Normal				= 0			UMETA(DisplayName = "Normal0"),
	Sweet				= 1			UMETA(DisplayName = "Sweet1"),
	Sour				= 2			UMETA(DisplayName = "Sour2"),
	spike				= 3			UMETA(DisplayName = "spike3"),
	metior				= 4			UMETA(DisplayName = "metior4"),
	multi				= 5			UMETA(DisplayName = "multi5")
};

UENUM(BlueprintType)
enum class EPlayerStateType : uint8
{
	Idle				= 0			UMETA(DisplayName = "Idle0"),
	walkrun				= 1			UMETA(DisplayName = "walkrun1"),
	sprint				= 2			UMETA(DisplayName = "sprint2"),
	jump				= 3			UMETA(DisplayName = "jump3"),
	fall				= 4			UMETA(DisplayName = "fall4"),
	hit					= 5			UMETA(DisplayName = "hit5"),
	launch				= 6			UMETA(DisplayName = "launch6"),
	crouch				= 7			UMETA(DisplayName = "crouch7"),
	ledge				= 8			UMETA(DisplayName = "ledge8"),
	dead				= 9			UMETA(DisplayName = "dead9"),
	shiled				= 12		UMETA(DisplayName = "shiled12"),
	tumble				= 13		UMETA(DisplayName = "tumble13"),
	shildtumble			= 14		UMETA(DisplayName = "shildtumble14"),
	prone				= 15		UMETA(DisplayName = "prone15"),
	stun				= 16		UMETA(DisplayName = "stun16"),
	dizzy				= 17		UMETA(DisplayName = "dizzy17"),
	ability				= 18		UMETA(DisplayName = "ability18"),
	Dodge				= 19		UMETA(DisplayName = "Dodge19"),
	FreeFall			= 20		UMETA(DisplayName = "FreeFall20"),
	Held				= 21		UMETA(DisplayName = "Held21"),
	Hold				= 22		UMETA(DisplayName = "Hold22")
}; 			

UENUM(BlueprintType)
enum class EHitStateType : uint8
{
	Normal				= 0			UMETA(DisplayName = "Normal0"),
	Intangible			= 1			UMETA(DisplayName = "Intangible1"),
	Invincible			= 2			UMETA(DisplayName = "Invincible2"),
	Armor				= 3			UMETA(DisplayName = "Armor3"),
	Shield				= 4			UMETA(DisplayName = "Shield4")
};		

UENUM(BlueprintType)
enum class EBufferType : uint8
{		
	Attack				= 0 		UMETA(DisplayName = "Attack0"),
	Special				= 1 		UMETA(DisplayName = "Special1"),
	Jump				= 2 		UMETA(DisplayName = "Jump2"),
	Shield				= 3 		UMETA(DisplayName = "Sheild3"),
	None				= 4 		UMETA(DisplayName = "None4")
};

UENUM(BlueprintType)
enum class EButtonType : uint8
{
	Pressed				= 0			UMETA(DisplayName = "Pressed0"),
	Released			= 1			UMETA(DisplayName = "Released1")
};

UENUM(BlueprintType)
enum class ECharacter : uint8
{
	Fighter				= 0			UMETA(DisplayName = "Fighter0"),
	None				= 1			UMETA(DisplayName = "None1"),
	SwordMan			= 2			UMETA(DisplayName = "SwordMan2"),
	Gunner				= 3			UMETA(DisplayName = "Gunner3"),
	Hats				= 4			UMETA(DisplayName = "Hats4"),
	Mage				= 5			UMETA(DisplayName = "Mage5"),
	Unknown				= 6			UMETA(DisplayName = "Unknown6"),
	Bob					= 7			UMETA(DisplayName = "Bob7"),
	Random				= 8			UMETA(DisplayName = "Random8")
};

UENUM(BlueprintType)
enum class EEnableType : uint8
{
	Enable				= 0			UMETA(DisplayName = "Enabled0"),
	Disable				= 1			UMETA(DisplayName = "Disabled1"),
	Custom				= 2			UMETA(DisplayName = "Custom2")
};

UENUM(BlueprintType)
enum class EGameModes : uint8
{
	VS					= 0			UMETA(DisplayName = "VS0"),
	Online				= 1			UMETA(DisplayName = "Online1"),
	Arcade				= 3			UMETA(DisplayName = "Arcade3")
};

UENUM(BlueprintType)
enum class EInGameModes : uint8
{
	Stock				= 0			UMETA(DisplayName = "Stock0"),
	Time				= 1			UMETA(DisplayName = "Time1"),
	MiniGame			= 3			UMETA(DisplayName = "MiniGame3"),
	BossFight			= 4			UMETA(DisplayName = "BossFight4")
};

UENUM(BlueprintType)
enum class EMaps : uint8
{
	ConcludingGround	= 0			UMETA(DisplayName = "ConcludingGround0"),
	ConflictZone		= 1			UMETA(DisplayName = "ConflictZone1"),
	Random				= 8			UMETA(DisplayName = "Random8"),
	AnotherLevel		= 9			UMETA(DisplayName = "AnotherLevel9"),
	TheWalkWay			= 10		UMETA(DisplayName = "TheWalkWay10"),
	IceZone				= 11		UMETA(DisplayName = "IceZone11"),

};

UENUM(BlueprintType)
enum class EMenus : uint8
{
	Main				= 0			UMETA(DisplayName = "Main0"),
	CharacterSelect		= 2			UMETA(DisplayName = "CharacterSelect2"),
	MapSelect			= 3			UMETA(DisplayName = "MapSelect3"),
	Online				= 4			UMETA(DisplayName = "Online4"),
	Host				= 5			UMETA(DisplayName = "Host5"),
	Join				= 6			UMETA(DisplayName = "Join6"),
	Lobby				= 7			UMETA(DisplayName = "Lobby7"),
	Title				= 8			UMETA(DisplayName = "Title8")
};

UENUM(BlueprintType)
enum class EAttackType : uint8
{
	TiltUp             	= 0			UMETA(DisplayName = "TiltUp0"),
	TiltDown           	= 1			UMETA(DisplayName = "TiltDown1"),
	TiltForward        	= 2			UMETA(DisplayName = "TiltForward2"),
	TiltBack           	= 3			UMETA(DisplayName = "TiltBack3"),
	TiltNeutral        	= 4			UMETA(DisplayName = "TiltNeutral4"),
	AirUp              	= 5			UMETA(DisplayName = "AirUp5"),
	AirDown            	= 6			UMETA(DisplayName = "AirDown6"),
	AirForward         	= 7			UMETA(DisplayName = "AirForward7"),
	AirBack            	= 8			UMETA(DisplayName = "AirBack8"),
	AirNeutral         	= 9			UMETA(DisplayName = "AirNeutral9"),
	SmashUp            	= 10		UMETA(DisplayName = "SmashUp10"),
	SmashDown          	= 11		UMETA(DisplayName = "SmashDown11"),
	SmashForward       	= 12		UMETA(DisplayName = "SmashForward12"),
	SmashBack          	= 13		UMETA(DisplayName = "SmashBack13"),
	SpecialDown        	= 14		UMETA(DisplayName = "SpecialDown14"),
	SpecialForward     	= 15		UMETA(DisplayName = "SpecialForward15"),
	SpecialBack        	= 16		UMETA(DisplayName = "SpecialBack16"),
	SpecialNeutral     	= 17		UMETA(DisplayName = "SpecialNeutral17"),
	Grab               	= 18		UMETA(DisplayName = "Grab18"),
	ThrowUp            	= 19		UMETA(DisplayName = "ThrowUp19"),
	ThrowDown          	= 20		UMETA(DisplayName = "ThrowDown20"),
	ThrowForward       	= 21		UMETA(DisplayName = "ThrowForward21"),
	ThrowBack          	= 22 		UMETA(DisplayName = "ThrowBack22"),
	Pummel             	= 23		UMETA(DisplayName = "Pummel23"),
	LedgeAttack        	= 24		UMETA(DisplayName = "LedgeAttack24"),
	ProneAttack        	= 25		UMETA(DisplayName = "ProneAttack25"),
	SpecialUp          	= 26		UMETA(DisplayName = "SpecialUp26"),
	None               	= 27 		UMETA(DisplayName = "None27"),
	DodgeSpot          	= 28		UMETA(DisplayName = "DodgeSpot28"),
	DodgeAir           	= 29		UMETA(DisplayName = "DodgeAir29"),
	DodgeBack          	= 30		UMETA(DisplayName = "DodgeBack30"),
	DodgeForward       	= 31		UMETA(DisplayName = "DodgeForward31"),
	Super              	= 32		UMETA(DisplayName = "Super32"),
};	


UENUM(BlueprintType)
enum class EAbilityType : uint8
{
	none				= 0			UMETA(DisplayName = "none0"),
	Basic				= 1			UMETA(DisplayName = "Basic1"),
	special				= 2			UMETA(DisplayName = "special2"),
	air					= 3 		UMETA(DisplayName = "air3"),
	smash				= 4 		UMETA(DisplayName = "smash4"),
	Super				= 5 		UMETA(DisplayName = "Super5"),
	other				= 6 		UMETA(DisplayName = "other6"),
	Dodge				= 7 		UMETA(DisplayName = "Dodge7"),
	Taunt				= 8 		UMETA(DisplayName = "Taunt8"),
	Ledge				= 9 		UMETA(DisplayName = "Ledge9"),
	Throw				= 10 		UMETA(DisplayName = "Throw10"),
	Prone				= 11 		UMETA(DisplayName = "Prone11"),
	grab				= 12 		UMETA(DisplayName = "grab12")
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
	Attack30
};