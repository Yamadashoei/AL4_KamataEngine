#pragma once

#include <audio\Audio.h>
#include <base\DirectXCommon.h>
#include <input\Input.h>
#include <3d\Model.h>
#include <2d\Sprite.h>
#include <3d\Camera.h>
#include <3d\WorldTransform.h>
#include <3d\DebugCamera.h>
#include "Player.h"

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

	// 3Dモデル
	KamataEngine::Model* model_ = nullptr;
	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;
	// ビュープロジェクション
	KamataEngine::Camera viewProjection_;

private: // メンバ変数
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	// 自キャラ
	Player* player_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};