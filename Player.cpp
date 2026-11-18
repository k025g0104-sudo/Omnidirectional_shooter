#include "Player.h"
#include "MyMatrix.h"
#include <algorithm>
#include <cassert>

using namespace KamataEngine;

namespace 
{
const float kPi = 3.14159265f;
const float kRightRotY = kPi / 2.0f;       
const float kLeftRotY = kPi * 3.0f / 2.0f; 
} 
void Player::Initialize(Model* model, uint32_t textureHandle, Camera* camera, const Vector3& position)
{
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;
	camera_ = camera;

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = kRightRotY;
}

WorldTransform& Player::GetWorldTransform() { return worldTransform_; }

void Player::Update() 
{
	Move();

	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}

void Player::Move() 
{
	Input* input = Input::GetInstance();

	bool right = input->PushKey(DIK_D) || input->PushKey(DIK_RIGHT);
	bool left = input->PushKey(DIK_A) || input->PushKey(DIK_LEFT);

	if (right && !left) 
	{
		if (velocity_.x < 0.0f)
		{
			velocity_.x *= (1.0f - kAttenuation);
		}
		velocity_.x += kAcceleration;

		if (lrDirection_ != LRDirection::kRight)
		{
			lrDirection_ = LRDirection::kRight;
			turnFirstRotationY_ = worldTransform_.rotation_.y;
			turnTimer_ = kTimeTurn;
		}
	} else if (left && !right) 
	{
		if (velocity_.x > 0.0f) 
		{
			velocity_.x *= (1.0f - kAttenuation);
		}
		velocity_.x -= kAcceleration;

		if (lrDirection_ != LRDirection::kLeft) 
		{
			lrDirection_ = LRDirection::kLeft;
			turnFirstRotationY_ = worldTransform_.rotation_.y;
			turnTimer_ = kTimeTurn;
		}
	} 
	else 
	{
	
		velocity_.x *= (1.0f - kAttenuation);
	}

   bool up = input->PushKey(DIK_W) || input->PushKey(DIK_UP);
	bool down = input->PushKey(DIK_S) || input->PushKey(DIK_DOWN);

	if (up && !down) 
	{
		if (velocity_.z < 0.0f) 
		{
			velocity_.z *= (1.0f - kAttenuation);
		}
		velocity_.z += kAcceleration;
	} else if (down && !up) 
	{
		if (velocity_.z > 0.0f) 
		{
			velocity_.z *= (1.0f - kAttenuation);
		}
		velocity_.z -= kAcceleration;
	} else 
	{
		velocity_.z *= (1.0f - kAttenuation);
	}

	velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);
	velocity_.z = std::clamp(velocity_.z, -kLimitRunSpeed, kLimitRunSpeed);
	worldTransform_.translation_.x += velocity_.x;
	worldTransform_.translation_.z += velocity_.z;
	
	if (turnTimer_ > 0.0f) {
		turnTimer_ -= 1.0f / 60.0f;

		float dest = (lrDirection_ == LRDirection::kRight) ? kRightRotY : kLeftRotY;
		float t = std::clamp(1.0f - turnTimer_ / kTimeTurn, 0.0f, 1.0f);
		worldTransform_.rotation_.y = turnFirstRotationY_ + (dest - turnFirstRotationY_) * t;
	}
}

void Player::Drow() { model_->Draw(worldTransform_, *camera_, textureHandle_); }