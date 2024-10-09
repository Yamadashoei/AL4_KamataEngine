#include "GameScene.h"
#include <base\TextureManager.h>
#include <3d\AxisIndicator.h>
#include <2d\ImGuiManager.h>
#include <3d\PrimitiveDrawer.h>
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
}

void GameScene::Initialize() {

	dxCommon_ = KamataEngine::DirectXCommon::GetInstance();
	input_ = KamataEngine::Input::GetInstance();
	audio_ = KamataEngine::Audio::GetInstance();
	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = KamataEngine::TextureManager::Load("panda.jpg ");
	// 3Dモデルの生成
	model_ = KamataEngine::Model::Create();
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	// 自キャラの生成
	player_ = new Player();
	// 自キャラの初期化
	player_->Initialize(model_, textureHandle_);
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

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	KamataEngine::Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	KamataEngine::Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 自キャラの描画
	player_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	KamataEngine::Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	KamataEngine::Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	KamataEngine::Sprite::PostDraw();

#pragma endregion
}