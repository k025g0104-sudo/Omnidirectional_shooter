#pragma once
#include "KamataEngine.h"
#include "MapChipField.h"
#include "Player.h"
#include "CameraController.h"
#include <vector>

class GameScene 
{
public:
	void Initialize();

	~GameScene();

	void Update();

	void Drow();

private:
	void GenerateBlocks(); // マップチップからブロックを並べる

	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Model* modelPlayer_ = nullptr;

	KamataEngine::Camera camera_;

	uint32_t textureHandle_ = 0;

	Player* player_ = nullptr;

	KamataEngine::DebugCamera* debugCamera_ = nullptr;

	bool isDebugCameraActive_ = false;

	// マップとブロック
	KamataEngine::Model* modelBlock_ = nullptr;
	MapChipField* mapChipField_ = nullptr;
	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_;

	CameraController* cameraController = nullptr;
};