#pragma once
#include "3d/Camera.h"
#include "3d/Model.h"
#include "3d/WorldTransform.h"
#include "base/TextureManager.h"

class skydome {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* viewProjection);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw(KamataEngine::Camera& viewProjection);

private:
	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;
	// 3Dモデル
	KamataEngine::Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// カメラモデル
	KamataEngine::Camera* viewProjection_ = nullptr;

};
