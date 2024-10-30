#include "Player.h"
#include "kMath.h"
#include <cassert>
#include <input\Input.h>
#include <math\MathUtility.h>

void Player::Initialize(KamataEngine::Model* model, uint32_t textureHandle) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;
	// ワールド変換の初期化
	worldTransform_.Initialize();
	// シングルトンインスタンスを取得する
	input_ = KamataEngine::Input::GetInstance();
}

void Player::Update() {

	// キャラクターの移動ベクトル
	KamataEngine::Vector3 move = {0, 0, 0};
	// キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;

	// 押した方向で移動ベクトルを変更(左右)
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	// 押した方向で移動ベクトルを変更(上下)
	if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	}
	// 座標移動（ベクトルの加算）
	worldTransform_.translation_ += move;
	// アフィン変換の行列の作成
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	// 定数バッファに転送する
	worldTransform_.TransferMatrix();

	// キャラクターの座標を画面表示する処理
	ImGui::Begin("プレイヤーの移動Debug");
	ImGui::DragFloat3("x", &worldTransform_.translation_.x, 0.01f);
	ImGui::End();
}

void Player::Draw(KamataEngine::Camera& viewProjection) {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}