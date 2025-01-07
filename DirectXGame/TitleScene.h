#pragma once
#include <3d\Camera.h>
#include <3d\Model.h>
#include <3d\WorldTransform.h>
#include <input\Input.h>
#include <2d\Sprite.h>
#include <base\TextureManager.h>

class TitleScene {
public:
	~TitleScene();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	// デスフラグの getter
	bool IsFinished() const { return finished_; }

private:
	KamataEngine::Camera viewProjection_;
	KamataEngine::WorldTransform worldTransformTitle_;
	KamataEngine::WorldTransform worldTransformPlayer_;

	KamataEngine::Model* model_ = nullptr;

	float counter_ = 0.0f;
	// 終了フラグ
	bool finished_ = false;
	static inline const float kTimeTitleMove = 2.0f;

	uint32_t textureHandle_ = 0;
	KamataEngine::Sprite* sprite_ = nullptr;
};