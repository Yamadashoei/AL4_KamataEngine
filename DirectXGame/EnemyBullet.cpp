#include "EnemyBullet.h"
#include <cassert>

using namespace KamataEngine;

void EnemyBullet::Initialize(KamataEngine::Model* model, const KamataEngine::Vector3& position, const KamataEngine::Vector3& velocity) {

	// NULLポインタチェック
	assert(model);

	model_ = model;
	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = KamataEngine::TextureManager::Load("white1x1.png");
	// ワールド変換の初期化
	worldTransform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
	// 引数で受け取った初期座標をセット
	velocity_ = velocity;

}

void EnemyBullet::Update() {
	// 座標を移動させる（1フレーム分の移動量を足しこむ）
	worldTransform_.translation_ += velocity_;
	// 時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
	// ワールド変換の更新
	worldTransform_.UpdateMatrix();
}

void EnemyBullet::Draw(const KamataEngine::Camera& viewProjection) { 
	model_->Draw(worldTransform_, viewProjection, textureHandle_); 
}
