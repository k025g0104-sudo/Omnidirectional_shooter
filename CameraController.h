#pragma once
#include "KamataEngine.h"
#include "Player.h"

class CameraController
{
public:
	void Initialize();

	void Update();

	void Reset();

	void SetTarget(Player* target) 
	{ 
		target_ = target; 
	}

	// GameScene が描画に使うカメラ
	KamataEngine::Camera& GetCamera() 
	{
		return camera_; 
	}

private:
	KamataEngine::Camera camera_;

	Player* target_ = nullptr;

	// 横スクロール用:プレイヤーの手前(Z のマイナス側)から映す
	KamataEngine::Vector3 targetOffset_{0.0f, 30.0f, 0.0f};
};