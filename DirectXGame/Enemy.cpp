#include "Enemy.h"
#include "Player.h"
#include "kMath.h"
#include <cassert>

using namespace KamataEngine;

Enemy::~Enemy() {
	// bullet解放
	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}
}

KamataEngine::Vector3 Enemy::GetWorldPosition() {
	/// ワールド座標を入れる変数
	KamataEngine::Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
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
	assert(player_);

	// 弾の速度(調整項目)
	const float kBulletSpeed = 1.0f;

	// 自キャラの座標を取得する
	KamataEngine::Vector3 playerWorldPos = player_->GetWorldPosition();
	// 敵キャラの座標を取得する
	KamataEngine::Vector3 enemyWorldPos = GetWorldPosition();
	// 敵キャラから自キャラへの差分ベクトルを求める
	KamataEngine::Vector3 BulletWorldPos = playerWorldPos - enemyWorldPos;
	// ベクトルの正規化
	BulletWorldPos = KamataEngine::MathUtility::Normalize(BulletWorldPos);
	// ベクトルの長さを速さに合わせる
	KamataEngine::Vector3 velocity = BulletWorldPos * kBulletSpeed;

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

//衝突判定
void Enemy::OnCollision() { return; }