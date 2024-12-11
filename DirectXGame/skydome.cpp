#include "skydome.h"
#include "cassert"
using namespace KamataEngine;

void skydome::Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* viewProjection) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;
	// ワールド変換の初期化
	worldTransform_.Initialize();
	viewProjection_ = viewProjection;
}

void skydome::Update() { worldTransform_.TransferMatrix(); }

void skydome::Draw(Camera& viewProjection) { 
	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
