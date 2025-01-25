#pragma once

#include "Player.h"
#include "Enemy.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"
#include "skydome.h"
#include "RailCamera.h"

#include <2d\Sprite.h>
#include <3d\Camera.h>
#include <3d\DebugCamera.h>
#include <3d\Model.h>
#include <3d\WorldTransform.h>
#include <audio\Audio.h>
#include <base\DirectXCommon.h>
#include <input\Input.h>

#include <sstream>

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

	/// <summary>
	/// 自弾を追加する
	/// </summary>
	/// <param name="playerBullet">自弾</param>
	//void AddPlayerBullet(PlayerBullet* playerBullet);

	/// 敵弾を追加する
	void AddEnemyBullet(EnemyBullet* enemyBullet);
	//敵発生データの読み込み
	void LoadEnemyPopData();
	//敵発生コマンドの更新
	void UpdateEnemyPopCommands();

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
	// 天球
	skydome* skyDome_ = nullptr;
	KamataEngine::Model* modelSkyDome_ = nullptr;
	uint32_t textureHandleSkyDome_ = 0u;

	// レールカメラ
	RailCamera* railCamera_ = nullptr;

	// デバッグカメラ有効
	bool isDebugCameraActive_ = false;
	// デバッグカメラ
	KamataEngine::DebugCamera* debugCamera_ = nullptr;

	// 自弾
	std::list<PlayerBullet*> playerBullets_;
	// 敵弾
	std::list<EnemyBullet*> enemyBullets_;

	std::stringstream enemyPopCommands;

};