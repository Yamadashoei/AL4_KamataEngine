#pragma once
#include <3d\Camera.h>
#include <3d\Model.h>
#include <3d\WorldTransform.h>
#include <math\Vector3.h>
#include <base\TextureManager.h>
#include <input\Input.h>
#include <cassert>
#include "kMath.h"

using namespace KamataEngine;

class PlayerBullet {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(KamataEngine::Model* model, const KamataEngine::Vector3& position, const KamataEngine::Vector3& velocity);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(const KamataEngine::Camera& viewProjection);

	//デスフラグ getter
	bool IsDead() const { return isDead_; }


private:
	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;
	// 3Dモデル
	KamataEngine::Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//速度
	KamataEngine::Vector3 velocity_;
	//寿命<frm>
	static const int32_t kLifeTime = 60 * 5;
	//デスタイマー
	int32_t deathTimer_ = kLifeTime;
	//デスフラグ
	bool isDead_ = false;


};
