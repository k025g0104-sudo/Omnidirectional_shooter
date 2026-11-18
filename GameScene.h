#pragma once
#include "KamataEngine.h"

enum class LRDirection
{
public:
	void Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* camera, const KamataEngine::Vector3& position);

	void Update();

	void Drow();
};