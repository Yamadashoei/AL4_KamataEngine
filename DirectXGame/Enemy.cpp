#include "Enemy.h"
#include "kMath.h"
#include <cassert>

Enemy::~Enemy() {
	// bullet解放
	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}

}
void Enemy::Initialize(KamataEngine::Model* model, uint32_t textureHandle) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;
	// ワールド変換の初期化
	worldTransform_.Initialize();
}

void Enemy::Update() {

	// デスフラグの立った弾を削除
	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	// キャラクターの移動ベクトル
	KamataEngine::Vector3 move = {0.0f, 0.0f, 0.02f};

	// キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;

	move.x -= kCharacterSpeed;

	// アフィン変換行列の作成
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	const float kMoveLimitX = 34;
	const float kMoveLimitY = 18;

	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();

	// 弾を発射
	// Fire();
	Approach();

	// 弾更新
	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}

	// フェーズ処理
	switch (phase_) {
	case Phase::Approach:
	default:
		// 移動（ベクトルを加算）
		worldTransform_.translation_ += ApproachVelocity;
		// 既定の位置に到達したら離脱
		if (worldTransform_.translation_.z < 0.0f) {
			phase_ = Phase::Leave;
		}
		break;
	case Phase::Leave:
		// 移動（ベクトルを加算）
		worldTransform_.translation_ += LeaveVelocity;
		break;
	}
}

void Enemy::Draw(KamataEngine::Camera& viewProjection) {

	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	// 弾描画
	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

// 発射
void Enemy::Fire() {
	// 自キャラの座標をコピー
	// DirectX::XMFLOAT3 position = worldTransform_.translation_;

	// 弾の速度
	const float kBulletSpeed = 1.0f;
	KamataEngine::Vector3 velocity(0, 0, -kBulletSpeed);

	// 速度ベクトルを自機の向きに合わせて回転させる
	velocity = TransformNormal(velocity, worldTransform_.matWorld_);

	// 弾を生成し、初期化
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);
	// 弾を登録する
	bullets_.push_back(newBullet);
}

void Enemy::Approach() {
	// 発射タイマーカウントダウン
	fireTimer++;
	// 指定時間に達した
	if (fireTimer == kFireInterval) {
		// 弾を発射
		Fire();
		// 発射タイマー
		fireTimer = 0;
	}
}
