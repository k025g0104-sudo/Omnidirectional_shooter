#pragma once
#include "KamataEngine.h"

enum class LRDirection
{
	kRight,
	kLeft,
};

class Player
{
public:
	void Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* camera, const KamataEngine::Vector3& position);

	void Update();

	void Drow();

	KamataEngine::WorldTransform& GetWorldTransform();

private:
	void Move();

	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Camera* camera_ = nullptr;
	uint32_t textureHandle_ = 0;

	KamataEngine::Vector3 velocity_ = {};
	LRDirection lrDirection_ = LRDirection::kRight;
	float turnFirstRotationY_ = 0.0f; 
	float turnTimer_ = 0.0f;         

	// 参考プロジェクトと同じ値
	static inline const float kAcceleration = 0.01f;
	static inline const float kAttenuation = 0.2f;
	static inline const float kLimitRunSpeed = 0.15f;
	static inline const float kTimeTurn = 0.3f;

};