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

FVector2D AMapManager::GetCoordinatesByLocation(FVector inputLocation) const
{
	// Base change to put the input position into the map coordinates
	FVector location = GetActorQuat().Inverse() * (inputLocation - GetActorLocation());

	// Calculate the column
	if (FMath::Abs(location.X) >= Columns * 0.5f * TileSize)
		return FVector2D(-1.0f, -1.0f);
	int column = FMath::FloorToInt(Columns * 0.5f + inputLocation.X / TileSize);

	// Calculate the row
	if (FMath::Abs(location.Y) >= Rows * 0.5f * TileSize)
		return FVector2D(-1.0f, -1.0f);
	int row = FMath::FloorToInt(Rows * 0.5f + inputLocation.Y / TileSize);

	return FVector2D(column, row);
}

EMapCellType AMapManager::GetCellTYpeByCoordinates(int column, int row) const
{
	// Check that we don't access to invalid indices
	ensure(column >= 0 && column < m_map.size());
	ensure(row >= 0 && m_map[column].size() > 0 && row < m_map[column].size());

	return m_map[column][row];
}

void AMapManager::BeginPlay()
{
	InitializeGrid();
	PlaceIndestructibleBlocks();
}