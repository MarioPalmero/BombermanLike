// - Mario Palmero [2017], zlib/libpng licensed.

#pragma once

#include <vector>
#include "MapManager.generated.h"

/*! \brief Type that represents what a cell in the map can contain
 *
 * This type represents the things that can be places in a cell of the map
 */
UENUM(BlueprintType)
enum EMapCellType
{
	Empty,
	IndestructibleBlock,
	DestructibleBlock,
	PowerUp,
	Bomb,
	Fire
};

/*! \brief Class that handles creation, progress and destruction of the map during a match
 *
 * Class that manages the creation of the grid and the placement of the destructibles,
 * along with the progress of the map during the match.
 */
UCLASS()
class AMapManager : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Map)
	float TileSize;		//<! Sets the measure of the side of the tiles that compose the map

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Map)
	int Columns;		//<! Indicates the current number of columns. The map will generate this number of columns when initializing.

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Map)
	int Rows;			//<! Indicates the current number of rows. The map will generate this number of rows when initializing.

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MapCreation)
	UClass* IndestructibleBlock;	//<! Class for the indestructible blocks to spawn

	/*! \brief Initializes the grid
	*
	* Method that fills all the cells with empty floor
	*/
	UFUNCTION()
	void InitializeGrid();

	/*! \brief Creates the non-destructible grid
	 *
	 * Method that fills the map with a grid of indestructible blocks
	 */
	UFUNCTION()
	void PlaceIndestructibleBlocks();

	/*! \brief Returns the position in world of a tile object
	 *
	 * Function that calculates the position of a tile depending on its coordinates in the map,
	 * the position of this actor and its rotation
	 */
	UFUNCTION(BlueprintCallable, Category = Map)
	FVector GetTilePosition(int column, int row) const;

	AMapManager();		//<! Constructor

protected:
	virtual void BeginPlay() override;				//<! Called when the game starts or when spawned
private:
	std::vector<std::vector<EMapCellType>> m_map;		//<! The abstraction of the physical map
};