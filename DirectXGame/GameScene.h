#pragma once
#include <2d\Sprite.h>
#include <3d\Model.h>
#include <audio\Audio.h>
#include <cstdint>
#include <input\Input.h>
#include <base\DirectXCommon.h>
#include <3d\Camera.h>
#include "Player.h" 
#include <3d\DebugCamera.h>
#include <3d\WorldTransform.h>


class GameScene {

public: // メンバ関数
	/// コンストクラタ
	GameScene();
	/// デストラクタ
	~GameScene();
	/// 初期化
	void Initialize();
	/// 毎フレーム処理
	void Update();
	/// 描画
	void Draw();

private:
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;

	// 自キャラ
	Player* player_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	// スプライト
	KamataEngine::Sprite* sprite_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	// ビュープロジェクション
	KamataEngine::Camera viewProjection_;
	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;

};