#pragma once
#include <3d\Camera.h>
#include <3d\Model.h>
#include <3d\WorldTransform.h>
#include <base\TextureManager.h>

class Player {
public:
	/// 初期化
	void Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera viewProjection);

	/// 更新
	void Update();

	/// 描画
	void Draw(); //

private:
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;
	// モデル
	KamataEngine::Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// ビュープロジェクション
	KamataEngine::Camera* viewProjection_ = nullptr;
};
