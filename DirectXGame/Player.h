#include <3d\Camera.h>
#include <3d\Model.h>
#include <3d\WorldTransform.h>
#include <base\TextureManager.h>
#include <input\Input.h>
#include "PlayerBullet.h"
#include <list>


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

	// ワールド座標を取得
	Vector3 GetWorldPosition();

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