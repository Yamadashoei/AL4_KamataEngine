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

	// 移動限界の座標
	const float kMoveLimitX = 10.0f;
	const float kMoveLimitY = 10.0f;
	// 範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	// キャラクターの座標を画面表示する処理
	ImGui::Begin("playerMove_Debug");
	ImGui::DragFloat3("x", &worldTransform_.translation_.x, 0.01f);
	ImGui::End();
}

void Player::Draw(KamataEngine::Camera& viewProjection) {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

//旋回
void Player::Rotate() {
	//回数速さ[ラジアン/frame]
	const float kRotSpeed = 0.02f;
	//押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_A)) {
	
	} else if (input_->PushKey(DIK_D)) {
	
	}




}
