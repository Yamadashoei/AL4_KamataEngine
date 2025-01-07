#pragma once
#include "EnemyBullet.h"
#include <3d\Camera.h>
#include <3d\Model.h>
#include <3d\WorldTransform.h>
#include <base\TextureManager.h>
#include <input\Input.h>

enum class Phase {
	Approach, // 接近する
	Leave,    // 離脱する
};

class EnemyBullet;
class Player;
class GameScene;

class Enemy {
public: // メンバ関数
	~Enemy();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(KamataEngine::Model* model, uint32_t textureHandle);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(KamataEngine::Camera& viewProjection);

	/// <summary>
	/// 弾発射
	/// </summary>
	void Fire();

	// 発射間隔
	static const int kFireInterval = 120;
	// 接近フェーズ初期化
	void Approach();
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }
	void SetPlayer(Player* player) { player_ = player; }
	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	KamataEngine::Vector3 GetWorldPosition();
	// 弾リストを取得
	const std::list<EnemyBullet*>& GetBullets() const { return bullets_; }

	// HP
	float hp_ = 100.0f;
	bool IsDead() const { return isDead_; } // 死亡チェックメソッド
	bool IsDamage() { return isDamage_; }
	bool IsGameOver() const { return isGameOver_; } // ゲーム停止状態チェック

private:
	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;
	// 3Dモデル
	KamataEngine::Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// フェーズ
	Phase phase_ = Phase::Approach;
	KamataEngine::Vector3 ApproachVelocity = {0.0f, 0.0f, -0.02f};
	KamataEngine::Vector3 LeaveVelocity = {-0.1f, 0.05f, 0.02f};
	// 弾
	std::list<EnemyBullet*> bullets_;
	// 移動方向
	int moveDirection_ = 0; // 0: 上, 1: 下, 2: 左, 3: 右
	// 移動タイマー
	int moveTimer_ = 0;

	// 発射タイマー
	int32_t fireTimer = 0;
	// ゲームシーン
	GameScene* gameScene_ = nullptr;
	// 自キャラ
	Player* player_ = nullptr;

	// 生死のフラグ
	bool isDead_ = false;
	// ダメージを受けたかどうか
	bool isDamage_ = false;

	// ゲームオーバーフラグ
	bool isGameOver_ = false; // HPが0になったらtrue
};
