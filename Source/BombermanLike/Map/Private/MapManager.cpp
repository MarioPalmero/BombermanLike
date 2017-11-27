// - Mario Palmero [2017], zlib/libpng licensed.

#include "Map/Public/MapManager.h"
#include "ConstructorHelpers.h"


AMapManager::AMapManager() : Super()
{
	static ConstructorHelpers::FObjectFinder<UBlueprint> indestructibleBlockObject(TEXT("Blueprint'/Game/Environment/Blueprints/BP_IndestructibleBlock.BP_IndestructibleBlock'"));
	if (indestructibleBlockObject.Object != nullptr)
		IndestructibleBlock = indestructibleBlockObject.Object->GeneratedClass;

	RootComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
}

void AMapManager::InitializeGrid()
{
	// Check if the number of rows or columns are odds
	if (Rows % 2 != 1)
		++Rows;
	if (Columns % 2 != 1)
		++Columns;

	// Clear the map
	m_map.clear();

	// Fill the map with Empty space
	for (int indexRows = 0; indexRows < Rows; ++indexRows)
	{
		std::vector<EMapCellType> currentColumn;
		for(int indexColumns = 0; indexColumns < Columns; ++indexColumns)
			currentColumn.push_back(EMapCellType::Empty);
		m_map.push_back(currentColumn);
	}
}

void AMapManager::PlaceIndestructibleBlocks()
{
	for (int indexRows = 0; indexRows < Rows; ++indexRows)
	{
		for (int indexColumns = 0; indexColumns < Columns; ++indexColumns)
		{
			
			if (indexColumns % 2 == 1 && indexRows % 2 == 1)
			{
				// First we create the blocks in the abstract layer
				m_map[indexRows][indexColumns] = EMapCellType::IndestructibleBlock;

				AActor* block = GetWorld()->SpawnActor<AActor>(IndestructibleBlock);
				block->SetActorLocation(GetTilePosition(indexColumns, indexRows));
			}
		}
	}
}

FVector AMapManager::GetTilePosition(int column, int row) const
{
	// Positioning the block depending on it's matrix position
	FVector blockLocation((0.5f + float(column) - Columns * 0.5f) * TileSize, (0.5f + float(row) - Rows * 0.5f) * TileSize, 0.0f);
	blockLocation = GetActorQuat() * blockLocation;
	blockLocation += GetActorLocation();
	return blockLocation;
}

void AMapManager::BeginPlay()
{
	InitializeGrid();
	PlaceIndestructibleBlocks();
}