#pragma once

#include "Enemy.h"
#include "EnemyBullet.h"
#include "Player.h"
#include "PlayerBullet.h"
#include "skydome.h"


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
	/// コンストラクタ
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

	/// <summary>
	/// 自弾を追加する
	/// </summary>
	/// <param name="playerBullet">自弾</param>
	// void AddPlayerBullet(PlayerBullet* playerBullet);

	/// <summary>
	/// 敵弾を追加する
	/// </summary>
	/// <param name="enemyBullet">敵弾</param>
	// void AddEnemyBullet(EnemyBullet* enemyBullet);

	// 自キャラ3Dモデル
	KamataEngine::Model* model_ = nullptr;
	// 敵キャラ3Dモデル
	KamataEngine::Model* modelEnemy_ = nullptr;
	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;
	// ビュープロジェクション
	KamataEngine::Camera viewProjection_;

	// デスフラグのgetter
	bool IsFinished() const { return finished_; }


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
	// 天球
	skydome* skyDome_ = nullptr;
	KamataEngine::Model* modelSkyDome_ = nullptr;
	uint32_t textureHandleSkyDome_ = 0u;

	// デバッグカメラ有効
	bool isDebugCameraActive_ = false;
	// デバッグカメラ
	KamataEngine::DebugCamera* debugCamera_ = nullptr;

	// 自弾
	std::list<PlayerBullet*> playerBullets_;
	// 敵弾
	std::list<EnemyBullet*> enemyBullets_;

	//シーン終了フラグ
	bool finished_ = false;

	// 経過時間
	float elapsedTime_ = 0.0f; // 0秒からスタート

	// ゲームオーバーシーンへの遷移フラグ
	bool gameOver_ = false;

	// ゲーム終了時間（30秒）
	float gameOverTime_ = 30.0f;



};
