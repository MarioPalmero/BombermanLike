// - Mario Palmero [2017], zlib/libpng licensed.

#pragma once

#include <vector>
#include "MapManager.generated.h"

/*! \brief Type that represents what a cell in the map can contain
 *
 * This type represents the things that can be places in a cell of the map
 */
UENUM(BlueprintType)
enum class EMapCellType : uint8
{
	Empty,
	IndestructibleBlock,
	DestructibleBlock
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Map)
	float DestructibleApparitionProbability;			//<! 0 to 1 probability of a destructible appearing in an empty cell

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MapCreation)
	UClass* IndestructibleBlock;	//<! Class for the indestructible blocks to spawn

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MapCreation)
	UClass* DestructibleBlock;	//<! Class for the destructible blocks to spawn

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

	/*! \brief Creates destructible blocks around the grid
	*
	* Method that fills the map with destructible blocks avoiding player start
	*/
	UFUNCTION()
	void PlaceDestructibleBlocks();

	/*! \brief Returns the position in world of a tile object
	 *
	 * Function that calculates the position of a tile depending on its coordinates in the map,
	 * the position of this actor and its rotation
	 */
	UFUNCTION(BlueprintCallable, Category = Map)
	FVector GetTilePosition(int column, int row) const;

	/*! \brief Calculates the cell where the input position is located
	 *
	 * Converts a location into a cell coordinate (column, row)
	 * If it's outside boundaries will return -1 in the coordinate
	 */
	UFUNCTION(BlueprintCallable, Category = Map)
	FVector2D GetCoordinatesByLocation(FVector inputLocation) const;

	/*! \brief Returns the type of tile of a cell
	*
	* Looks up for the content of a cell
	*/
	UFUNCTION(BlueprintCallable, Category = Map)
	EMapCellType GetCellTypeByCoordinates(int column, int row) const;

	/*! \brief Returns the locations where an explosion should set fire
	*
	* With the length parameter and the position this function return the cells where
	* a fire actor should be placed
	*/
	UFUNCTION(BlueprintCallable, Category = Map)
	TArray<FVector> GetExplosionLocations(FVector location, int flameLength) const;

	/*! \brief Notifies the map that a destructible block has been destructed
	*
	* The map updates the abstract with the position info, empting the cell if there was a destructible block
	*/
	UFUNCTION(BlueprintCallable, Category = Map)
	void NotifyDestructionOfDestructibleBlock(FVector location);

	AMapManager();		//<! Constructor

	UFUNCTION(BlueprintCallable, Category = Map)
	static AMapManager* GetInstance();		//<! Returns a reference to the map
protected:
	virtual void BeginPlay() override;				//<! Called when the game starts or when spawned

private:
	static AMapManager* m_mapInstance;				//<! Instance of the map
	static UWorld* m_world;							//<! Reference to the world

	std::vector<std::vector<EMapCellType>> m_map;		//<! The abstraction of the physical map
};