#pragma once
#include <3d\Camera.h>
#include <3d\Model.h>
#include <3d\WorldTransform.h>
#include <base\TextureManager.h>
#include <input\Input.h>
#include "PlayerBullet.h"
#include <list>


class PlayerBullet;
class GameScene;

class Player {
public: // メンバ関数
	
	//デストラクタ
	~Player();

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
	//旋回 いらないかも
	void Rotate();
	//発射
	void Attack();
	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	// ワールド座標を取得
	KamataEngine::Vector3 GetWorldPosition();
	// 弾リストを取得
	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }


private:
	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;
	// 3Dモデル
	KamataEngine::Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// キーボード入力
	KamataEngine::Input* input_ = nullptr;
	// 弾
	std::list<PlayerBullet*>bullets_;


};