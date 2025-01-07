#pragma once
#include <base\DirectXCommon.h>
#include <3d\Model.h>
#include "Player.h"

#include <base\TextureManager.h>
#include <3d\Camera.h>
#include <3d\WorldTransform.h>
#include <input\Input.h>
#include <2d\Sprite.h>

class ClearScene {
public:
	~ClearScene();
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
	// デスフラグのgetter
	bool IsFinished() const { return finished_; }

	void SetScore(uint32_t score100, uint32_t score10, uint32_t score1);

	int GetScore100() const { return score_100; }
	int GetScore10() const { return score_10; }
	int GetScore1() const { return score_1; }

private:
	Camera viewProjection_;
	WorldTransform worldTransformTitle_;
	WorldTransform worldTransformPlayer_;
	DirectXCommon* dxCommon_ = nullptr;

	Model* model_ = nullptr;

	float counter_ = 0.0f;
	// 終了フラグ
	bool finished_ = false;
	static inline const float kTimeTitleMove = 2.0f;

	int time = 420;

	int score_100;
	int score_10;
	int score_1;
	int score_;

	//
	uint32_t texture;
	Sprite* sprite = nullptr;
	Sprite* scoreSprite100_ = nullptr;

	Sprite* scoreSprite10_ = nullptr;

	Sprite* scoreSprite1_ = nullptr;
};