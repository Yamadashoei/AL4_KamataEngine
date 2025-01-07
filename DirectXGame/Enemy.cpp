#include "Enemy.h"
#include "Player.h"
#include "kMath.h"
#include <cassert>
#include <random>

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
	worldTransform_.translation_ = {0.0f, 0.0f, 20.0f}; // Z軸を奥に設定

	// ワールド変換の初期化
	worldTransform_.Initialize();
}

#include <random>

void Enemy::Update() {
	// デスフラグの立った弾を削除
	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	// ランダム移動のための乱数生成
	static std::random_device rd;                     // ランダムデバイス
	static std::mt19937 gen(rd());                    // メルセンヌ・ツイスタ生成器
	static std::uniform_int_distribution<> dis(0, 3); // 0, 1, 2, 3 の間でランダムに選択

	// 3秒ごとに方向を決定
	moveTimer_++;
	if (moveTimer_ >= 180) {       // 180フレーム = 3秒 (フレームレート60fps想定)
		moveDirection_ = dis(gen); // ランダムで移動方向を決定
		moveTimer_ = 0;            // タイマーリセット
	}

	// キャラクターの移動ベクトル（Z軸の移動を無効化）
	KamataEngine::Vector3 move = {0.0f, 0.0f, 0.0f}; // Z軸の移動を0にする

	// キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;

	// 上下左右の移動処理
	if (moveDirection_ == 0) { // 上方向
		move.y += kCharacterSpeed;
	} else if (moveDirection_ == 1) { // 下方向
		move.y -= kCharacterSpeed;
	} else if (moveDirection_ == 2) { // 左方向
		move.x -= kCharacterSpeed;
	} else if (moveDirection_ == 3) { // 右方向
		move.x += kCharacterSpeed;
	}

	// 画面外に出ないように制限
	const float minX = 0.0f, maxX = 30.0f;
	const float minY = 0.0f, maxY = 20.0f;

	// 移動後の位置が範囲内に収まるように計算
	KamataEngine::Vector3 newPos = worldTransform_.translation_ + move;

	// X座標の制限
	if (newPos.x < minX) {
		newPos.x = minX;
	} else if (newPos.x > maxX) {
		newPos.x = maxX;
	}

	// Y座標の制限
	if (newPos.y < minY) {
		newPos.y = minY;
	} else if (newPos.y > maxY) {
		newPos.y = maxY;
	}

	// Z軸の位置を固定（進行しない）
	newPos.z = worldTransform_.translation_.z;

	// 移動後の位置を反映
	worldTransform_.translation_ = newPos;

	// アフィン変換行列の作成
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();

	// 弾を発射
	// Fire();
	Approach();

	// 弾更新
	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}
}


	void Enemy::Draw(KamataEngine::Camera & viewProjection) {

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

	// 衝突判定
	void Enemy::OnCollision() {
	    return;
		/*hp_ -= 35.0f;
		isDamage_ = true;*/
	}