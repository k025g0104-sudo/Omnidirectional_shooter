#include <Windows.h>
#include "KamataEngine.h"
#include "GameScene.h"
using namespace KamataEngine;
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) 
{
	// KamataEngineの初期化
	Initialize(L"LE2C_23_ハットリ_ユウマ");

	// DirectXCommonのインスタンスを取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	GameScene* gameScene = new GameScene();

	gameScene->Initialize();

	// メインループ
	while (true) 
	{
	    //エンジンの更新
		if (Update()) 
		{
			break;
		}

		// ゲームシーンの更新
		gameScene->Update();

		// 描画開始
		dxCommon->PreDraw();

		// ゲームシーンの描画
		gameScene->Drow();


		//描画終了
		dxCommon->PostDraw();
	}

	Finalize();

	return 0;
}
