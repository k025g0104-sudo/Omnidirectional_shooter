#include "CameraController.h"
#include <numbers>
using namespace KamataEngine;

void CameraController::Initialize() 
{
	camera_.Initialize(); 

	camera_.rotation_ = {std::numbers::pi_v<float> / 2.0f, 0.0f, 0.0f};
}


void CameraController::Update()
{
	if (target_)
	{
		const WorldTransform& targetWT = target_->GetWorldTransform();

		camera_.translation_.x = targetWT.translation_.x + targetOffset_.x;
		camera_.translation_.y = targetWT.translation_.y + targetOffset_.y;
		camera_.translation_.z = targetWT.translation_.z + targetOffset_.z;
	}

	camera_.UpdateMatrix();
}

void CameraController::Reset()
{
	if (target_)
	{
		const WorldTransform& targetWT = target_->GetWorldTransform();

		camera_.translation_.x = targetWT.translation_.x + targetOffset_.x;
		camera_.translation_.y = targetWT.translation_.y + targetOffset_.y;
		camera_.translation_.z = targetWT.translation_.z + targetOffset_.z;
	}
}