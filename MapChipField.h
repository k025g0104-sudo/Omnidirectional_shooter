#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include "KamataEngine.h"

enum  class MapChipType
{
	kBlank,
	kBlock,
	//kCoin,
	//kGoal,
	//kEnemy,
};



class MapChipField
{
public:

	//1ブロックのサイズ
	struct IndexSet
	{
		uint32_t xIndex;
		uint32_t yIndex;
	};

	struct Rect
	{
		float left;
		float right;
		float bottom;
		float top;
	};

	IndexSet GetMapChipIndexSetByPosition(const KamataEngine::Vector3& position);

	Rect GetRectByIndex(uint32_t xIndex, uint32_t yIndex);

	void LoadMapChipCsv(const std::string& filePath);
	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);
	KamataEngine::Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);
	uint32_t GetNumBlockVirtical();
	uint32_t GetNumBlockHorizontal();

	void SetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex, MapChipType type);
private:


	static inline const float kBlockWidth = 1.0f;
	static inline const float kBlockHeight = 1.0f;


	static inline const uint32_t kNumBlockVirtical = 20;
	static inline const uint32_t kNumBlockHorizontal = 100;

	struct MapChipData
	{
		std::vector<std::vector<MapChipType>> data;
	};

	void  ResetMapChipData();

	MapChipData mapChipData_;
};