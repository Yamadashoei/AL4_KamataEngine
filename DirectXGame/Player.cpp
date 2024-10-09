#include "Player.h"
#include <cassert>
#include <2d\ImGuiManager.h>

void Player::Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* viewProjection) {
	// NULLポインタチェック
	assert(model);
	// 引数として受け取ったデータをメンバ変数に記録する
	// モデルをメンバ変数に記録
	model_ = model;
	// テクスチャハンドルをメンバ変数に記録
	textureHandle_ = textureHandle;
	//ビュープロジェクションを引数の内容をメンバ変数に記録
	viewProjection_ = viewProjection;
	//ワールド変換の初期化
	worldTransform_.Initialize();
}

void Player::Update() {
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Player::Draw() {
	// 3Dモデル
	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);
}//KamataEngine::Camera& viewProjection
