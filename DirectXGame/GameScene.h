#pragma once

#include "Player.h"
#include "Enemy.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"

#include <2d\Sprite.h>
#include <3d\Camera.h>
#include <3d\DebugCamera.h>
#include <3d\Model.h>
#include <3d\WorldTransform.h>
#include <audio\Audio.h>
#include <base\DirectXCommon.h>
#include <input\Input.h>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

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

	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollisions();

	// 自キャラ3Dモデル
	KamataEngine::Model* model_ = nullptr;
	// 敵キャラ3Dモデル
	KamataEngine::Model* modelEnemy_ = nullptr;
	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;
	// ビュープロジェクション
	KamataEngine::Camera viewProjection_;

private: // メンバ変数
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;
	// 自キャラのテクスチャハンドル
	uint32_t textureHandle_ = 0;
	// 敵キャラのテクスチャハンドル
	uint32_t textureHandleEnemy_ = 0;
	// 自キャラ
	Player* player_ = nullptr;
	// 敵キャラ
	Enemy* enemy_ = nullptr;

	// デバッグカメラ有効
	bool isDebugCameraActive_ = false;
	// デバッグカメラ
	KamataEngine::DebugCamera* debugCamera_ = nullptr;

	// 自弾
	std::list<PlayerBullet*> playerBullets_;
	// 敵弾
	std::list<EnemyBullet*> enemyBullets_;

};