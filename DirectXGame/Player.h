#include <3d\Camera.h>
#include <3d\WorldTransform.h>
#include <input\Input.h>
#include <3d\Model.h>

class Player {
public: // メンバ関数
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
	void Draw(KamataEngine::Camera& veiwProjection);

private:
	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;
	// 3Dモデル
	KamataEngine::Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// キーボード入力
	KamataEngine::Input* input_ = nullptr;
};