#pragma once
#include "3d/Camera.h"
#include "3d/WorldTransform.h"
#include "kMath.h"
#include "math/MathUtility.h"

class RailCamera {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const KamataEngine::WorldTransform& worldTransform);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	KamataEngine::Camera& GetCamera() { return viewProjection_; }

	const KamataEngine::WorldTransform& GetWorldTransform() {
		return worldTransform_; }

private:
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;
	// カメラ
	KamataEngine::Camera viewProjection_;

	KamataEngine::Vector3 translation_ = {0.0f, 0.0f, 0.0f};

	KamataEngine::Vector3 rotation_ = {0.0f, 0.0f, 0.0f};
};
