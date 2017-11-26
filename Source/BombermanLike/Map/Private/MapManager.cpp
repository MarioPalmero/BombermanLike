// - Mario Palmero [2017], zlib/libpng licensed.

#include "Map/Public/MapManager.h"


void UMapManager::InitializeGrid()
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

void UMapManager::PlaceIndestructibleBlocks()
{
	for (int indexRows = 0; indexRows < Rows; ++indexRows)
	{
		for (int indexColumns = 0; indexColumns < Columns; ++indexColumns)
		{
			if (indexColumns % 2 == 1 && indexRows % 2 == 1)
				m_map[indexRows][indexColumns] = EMapCellType::IndestructibleBlock;
		}
	}
}
