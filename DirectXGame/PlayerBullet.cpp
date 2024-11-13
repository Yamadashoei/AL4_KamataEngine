#include "PlayerBullet.h"
#include <base\TextureManager.h>

void PlayerBullet::Initialize(KamataEngine::Model* model, const KamataEngine::Vector3& position) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = KamataEngine::TextureManager::Load("white1x1.png");
	// ワールド変換の初期化
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;

}

void PlayerBullet::Update() {
	// ワールド変換の更新
	worldTransform_.UpdateMatrix();
}

void PlayerBullet::Draw(const KamataEngine::Camera& viewProjection) { 
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}
