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
	void Initialize(KamataEngine::Model* model, uint32_t textureHandle, const KamataEngine::Vector3& position);

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
	static const int kFireInterval = 60;
	// 接近フェーズ初期化
	void Approach();
	void SetPlayer(Player* player) { player_ = player; }
	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	KamataEngine::Vector3 GetWorldPosition();
	// 弾リストを取得
	const std::list<EnemyBullet*>& GetBullets() const { return bullets_; }



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
	// 発射タイマー
	int32_t fireTimer = 0;
	//ゲームシーン
	GameScene* gameScene_ = nullptr;
	// 自キャラ
	Player* player_ = nullptr;
};
