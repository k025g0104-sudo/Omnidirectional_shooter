#include "MapChipField.h"
#include <map>
#include <fstream>
#include <sstream>
#include <cassert>
namespace
{
	std::map<std::string, MapChipType> mapChipTable =
	{
		{"0", MapChipType::kBlank},
		{"1", MapChipType::kBlock},
	/*	{"2", MapChipType::kCoin},
		{"3", MapChipType::kGoal},
		{"4", MapChipType::kEnemy},*/

	};

}

void MapChipField::ResetMapChipData()
{

	mapChipData_.data.clear();
	mapChipData_.data.resize(kNumBlockVirtical);
	for (std::vector<MapChipType>& mapChipDataLine : mapChipData_.data)
	{
		mapChipDataLine.resize(kNumBlockHorizontal);
	}

}

void MapChipField::LoadMapChipCsv(const std::string& filePath)
{
	ResetMapChipData();

	std::ifstream file;
	file.open(filePath);
	assert(file.is_open());

	std::stringstream mapChipCsv;
	mapChipCsv << file.rdbuf();
	file.close();

	for (uint32_t i = 0; i < kNumBlockVirtical; ++i)
	{
		std::string line;
		getline(mapChipCsv, line);

		std::istringstream lineStream(line);

		for (uint32_t j = 0; j < kNumBlockHorizontal; ++j)
		{
			std::string word;
			std::getline(lineStream, word, ',');

			if (mapChipTable.contains(word))
			{
				mapChipData_.data[i][j] = mapChipTable[word];
			}

		}

	}
}

MapChipType MapChipField::GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex)
{
	if (xIndex >= kNumBlockHorizontal)
	{
		return MapChipType::kBlank;
	}

	if (yIndex >= kNumBlockVirtical)
	{
		return MapChipType::kBlank;
	}

	return mapChipData_.data[yIndex][xIndex];
}

KamataEngine::Vector3 MapChipField::GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex)
{
	return KamataEngine::Vector3(kBlockWidth * xIndex, 0, kBlockHeight * (kNumBlockVirtical - 1 - yIndex));
}


MapChipField::IndexSet MapChipField::GetMapChipIndexSetByPosition(const KamataEngine::Vector3& position) 
{
	IndexSet indexSet;
	indexSet.xIndex = static_cast<uint32_t>(position.x / kBlockWidth);
	indexSet.yIndex = static_cast<uint32_t>((kBlockHeight * kNumBlockVirtical - position.z) / kBlockHeight);
	return indexSet;
}

MapChipField::Rect MapChipField::GetRectByIndex(uint32_t xIndex, uint32_t yIndex)
{
	Rect rect;
	rect.left = kBlockWidth * xIndex;
	rect.right = kBlockWidth * (xIndex + 1);
	rect.bottom = kBlockHeight * (kNumBlockVirtical - 1 - yIndex);
	rect.top = kBlockHeight * (kNumBlockVirtical - yIndex);
	return rect;
}

void MapChipField::SetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex, MapChipType type)
{
	if (xIndex < kNumBlockHorizontal && yIndex < kNumBlockVirtical)
	{
		mapChipData_.data[yIndex][xIndex] = type;
	}
}

uint32_t MapChipField::GetNumBlockVirtical()
{
	return kNumBlockVirtical;
}

uint32_t MapChipField::GetNumBlockHorizontal()
{
	return kNumBlockHorizontal;
}

