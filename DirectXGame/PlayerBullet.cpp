#include "PlayerBullet.h"
#include <cassert>

void PlayerBullet::Initialize(KamataEngine::Model* model, const KamataEngine::Vector3& position) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = KamataEngine::TextureManager::Load("black.png ");
	// ワールド変換の初期化
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = ;

}

void PlayerBullet::Update() {

}

void PlayerBullet::Draw(const KamataEngine::Camera& veiwProjection) {


}
