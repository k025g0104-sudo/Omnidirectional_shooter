#include "GameScene.h"
#include "MyMatrix.h"
using namespace KamataEngine;

void GameScene::Initialize() 
{
	camera_.Initialize();
	// マップ(横40×縦20)が画面に収まる位置へ
	camera_.translation_ = {10.0f, 30.0f, 5.0f};
	camera_.rotation_ = {1.5707963f, 0.0f, 0.0f}; // 真下を向く(追加)
	camera_.UpdateMatrix();

	debugCamera_ = new DebugCamera(1280, 720);

	// マップチップ
	mapChipField_ = new MapChipField();
	mapChipField_->LoadMapChipCsv("Resources/mapchip.csv");

	// ブロック用モデル(標準の立方体)
	modelBlock_ = Model::Create();
	GenerateBlocks();

	// プレイヤー
	modelPlayer_ = Model::CreateFromOBJ("player", true);
	player_ = new Player();
	player_->Initialize(modelPlayer_, textureHandle_, &camera_, {2.0f, 1.0f, 2.0f});
	 
	cameraController = new CameraController();
	cameraController->Initialize();
	cameraController->SetTarget(player_);
	cameraController->Reset();
	
	worldTransform_.Initialize();
}

void GameScene::GenerateBlocks()
{
	uint32_t numV = mapChipField_->GetNumBlockVirtical();
	uint32_t numH = mapChipField_->GetNumBlockHorizontal();

	worldTransformBlocks_.resize(numV);
	for (uint32_t i = 0; i < numV; ++i) 
	{
		worldTransformBlocks_[i].resize(numH, nullptr);
	}

	for (uint32_t i = 0; i < numV; ++i) 
	{
		for (uint32_t j = 0; j < numH; ++j) 
		{
			if (mapChipField_->GetMapChipTypeByIndex(j, i) != MapChipType::kBlock) 
			{
				continue;
			}

			WorldTransform* wt = new WorldTransform();
			wt->Initialize();
			wt->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			wt->scale_ = {0.5f, 0.5f, 0.5f}; // 立方体(1辺2)を 1×1 にする

			// 動かないブロックなので、ここで一度だけ行列を計算して転送する
			wt->matWorld_ = MakeAffineMatrix(wt->scale_, wt->rotation_, wt->translation_);
			wt->TransferMatrix();

			worldTransformBlocks_[i][j] = wt;
		}
	}
}

GameScene::~GameScene() 
{
	for (auto& line : worldTransformBlocks_) 
	{
		for (WorldTransform* wt : line)
		{
			delete wt; // nullptr の delete は安全
		}
	}
	worldTransformBlocks_.clear();

	delete mapChipField_;
	mapChipField_ = nullptr;

	delete modelBlock_;
	modelBlock_ = nullptr;

	delete player_;
	player_ = nullptr;

	delete modelPlayer_;
	modelPlayer_ = nullptr;

	delete debugCamera_;
	debugCamera_ = nullptr;

	delete cameraController;
	cameraController = nullptr;
}

void GameScene::Update()
{
	player_->Update();
	cameraController->Update();

	// 追従カメラの結果を、描画用のカメラへ反映する
	camera_.translation_ = cameraController->GetCamera().translation_;
	camera_.rotation_ = cameraController->GetCamera().rotation_;

#ifdef _DEBUG
	// 注意:A キーはプレイヤーの左移動と重なるので、C キーにしています
	if (Input::GetInstance()->TriggerKey(DIK_C))
	{
		isDebugCameraActive_ = !isDebugCameraActive_;
	}
#endif

	if (isDebugCameraActive_) {
		debugCamera_->Update();
		camera_.matView = debugCamera_->GetCamera().matView;
		camera_.matProjection = debugCamera_->GetCamera().matProjection;
		camera_.TransferMatrix();
	} else {
		camera_.UpdateMatrix();
	}
}

void GameScene::Drow()
{
	Model::PreDraw();

	// ブロック
	for (auto& line : worldTransformBlocks_) 
	{
		for (WorldTransform* wt : line)
		{
			if (wt) 
			{
				modelBlock_->Draw(*wt, camera_);
			}
		}
	}

	player_->Drow();

	Model::PostDraw();
}