#include "GameScene.h"
#include "Player.h"
#include <2d\ImGuiManager.h>
#include <base\TextureManager.h>
#include <3d\PrimitiveDrawer.h>

GameScene::GameScene() {}

GameScene::~GameScene() {
	//スプライトの解放
	//delete sprite_;
	// 3Dモデルデータの解放
	delete model_;
	// 自キャラの解放
	delete player_;
}

void GameScene::Initialize() {
	dxCommon_ = KamataEngine::DirectXCommon::GetInstance();
	input_ = KamataEngine::Input::GetInstance();
	audio_ = KamataEngine::Audio::GetInstance();
	// ファイル名を指定してテクスチャハンドルを読み込む
	textureHandle_ = KamataEngine::TextureManager::Load("panda.jpg");
	// スプライトの生成
	//sprite_ = KamataEngine::Sprite::Create(textureHandle_, {100, 50});
	// 3Dモデルデータの生成
	model_ = KamataEngine::Model::Create();
	// ビュープロジェクトションの初期化
	viewProjection_.Initialize();
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	// 自キャラ作成
	player_ = new Player();
	// 自キャラの初期化
	player_->Initialize(model_, textureHandle_,&viewProjection_);


}

void GameScene::Update() {
	// 自キャラの更新
	player_->Update();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	KamataEngine::Sprite::PreDraw(commandList);
	/// ここに背景スプライトの描画処理を追加できる
	// スプライト描画後処理
	KamataEngine::Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	KamataEngine::Model::PreDraw(commandList);
	/// ここに3Dオブジェクトの描画処理を追加できる

	// 自キャラの描画
	player_->Draw();

	// 3Dオブジェクト描画後処理
	KamataEngine::Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	KamataEngine::Sprite::PreDraw(commandList);
	/// ここに前景スプライトの描画処理を追加できる
	// スプライト描画後処理
	KamataEngine::Sprite::PostDraw();

#pragma endregion
}
