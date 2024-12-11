#include "GameScene.h"
#include <2d\ImGuiManager.h>
#include <3d\AxisIndicator.h>
#include <3d\PrimitiveDrawer.h>
#include <base\TextureManager.h>
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete enemy_;
	delete debugCamera_;

	delete modelSkyDome_;
	delete skyDome_;
}

void GameScene::Initialize() {

	dxCommon_ = KamataEngine::DirectXCommon::GetInstance();
	input_ = KamataEngine::Input::GetInstance();
	audio_ = KamataEngine::Audio::GetInstance();

	// 自キャラのテクスチャ
	textureHandle_ = KamataEngine::TextureManager::Load("panda.jpg ");
	// 敵キャラのテクスチャ
	textureHandleEnemy_ = KamataEngine::TextureManager::Load("wasi.jpg ");

	// 3Dモデルの生成
	model_ = KamataEngine::Model::Create();
	modelEnemy_ = KamataEngine::Model::Create();

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	// 自キャラの生成
	player_ = new Player();
	// 自キャラの初期化
	player_->Initialize(model_, textureHandle_);

	// 敵キャラの生成
	enemy_ = new Enemy();
	// 敵キャラの初期化
	enemy_->Initialize(modelEnemy_, textureHandleEnemy_);

	// 敵キャラに自キャラのアドレスを渡す
	enemy_->SetPlayer(player_);
	// デバッグカメラの生成
	debugCamera_ = new KamataEngine::DebugCamera(KamataEngine::WinApp::kWindowWidth, KamataEngine::WinApp::kWindowHeight);

	// スカイドーム
	modelSkyDome_ = Model::CreateFromOBJ("SkyDome", true);
	textureHandleSkyDome_ = TextureManager::Load("./Resources/SkyDome/sky_sphere.png");
	skyDome_ = new skydome();
	skyDome_->Initialize(modelSkyDome_, textureHandleSkyDome_, &viewProjection_);

	// 軸方向表示の表示を有効にする
	KamataEngine::AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	KamataEngine::AxisIndicator::GetInstance()->SetTargetCamera(&viewProjection_);
}

void GameScene::Update() {
	// 自キャラの更新
	player_->Update();
	// 敵キャラの更新
	enemy_->Update();
	// デバッグカメラの更新
	debugCamera_->Update();
	CheckAllCollisions();
	// スカイドームの更新
	skyDome_->Update();

	// デバッグカメラの切り替え処理
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_0)) {
		isDebugCameraActive_ = !isDebugCameraActive_;
	}
#endif
	// カメラの処理
	if (isDebugCameraActive_) {
		// デバッグカメラの更新
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetCamera().matView;
		viewProjection_.matProjection = debugCamera_->GetCamera().matProjection;
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
		// ビュープロジェクション行列の更新と転送
		viewProjection_.UpdateMatrix();
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	KamataEngine::Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	KamataEngine::Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	KamataEngine::Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// スカイドームの描画
	skyDome_->Draw(viewProjection_);
	// 自キャラの描画
	player_->Draw(viewProjection_);
	// 敵キャラの描画
	enemy_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	KamataEngine::Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	KamataEngine::Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	KamataEngine::Sprite::PostDraw();

#pragma endregion
}

// 当たり判定　再確認
void GameScene::CheckAllCollisions() {
	// 判定対象AとBの座標
	Vector3 posA, posB;

	// 自弾リストの取得
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	// 敵弾リストの取得
	const std::list<EnemyBullet*> enemyBullets = enemy_->GetBullets();

#pragma region 自キャラと敵弾の当たり判定
	// 自キャラの座標
	posA = player_->GetWorldPosition();
	// 自キャラと敵弾全ての当たり判定
	for (EnemyBullet* bullet : enemyBullets) {
		// 敵弾の座標
		posB = bullet->GetWorldPosition();
		// 座標AとBの距離を求める
		// 自キャラと敵弾の距離の二乗を求める
		float dist = pow((posB.x - posA.x), 2.0f) + pow((posB.y - posA.y), 2.0f) + pow((posB.z - posA.z), 2.0f);
		// 衝突判定距離の二乗
		float len = pow((1.0f + 1.0f), 2.0f);

		// 自キャラと敵弾の衝突判定
		if (dist <= len) {
			// 自キャラの衝突時コールバックを呼び出す
			player_->OnCollision();
			// 敵弾の衝突時コールバックを呼び出す
			bullet->OnCollision();
		}
	}
#pragma endregion

#pragma region 自弾と敵キャラの当たり判定
	// 敵キャラの座標
	posA = enemy_->GetWorldPosition();

	// 敵キャラと自弾全ての当たり判定
	for (PlayerBullet* bullet : playerBullets) {
		// 自弾の座標
		posB = bullet->GetWorldPosition();

		// 座標AとBの距離を求める
		// 自キャラと敵弾の距離の二乗を求める
		float dist = pow((posB.x - posA.x), 2.0f) + pow((posB.y - posA.y), 2.0f) + pow((posB.z - posA.z), 2.0f);
		// 衝突判定距離の二乗
		float len = pow((1.0f + 1.0f), 2.0f);

		// 弾と弾の交差
		if (dist <= len) {
			// 敵キャラの衝突コールバックを呼び出す
			enemy_->OnCollision();
			// 自弾の衝突コールバックを呼び出す
			bullet->OnCollision();
		}
	}
#pragma endregion

#pragma region 自弾と敵弾の当たり判定
	for (PlayerBullet* playerBullet : playerBullets) {
		// 自弾の座標
		posA = playerBullet->GetWorldPosition();
		for (EnemyBullet* enemyBullet : enemyBullets) {
			// 敵弾の座標
			posB = enemyBullet->GetWorldPosition();

			// 座標AとBの距離を求める
			// 自キャラと敵弾の距離の二乗を求める
			float dist = pow((posB.x - posA.x), 2.0f) + pow((posB.y - posA.y), 2.0f) + pow((posB.z - posA.z), 2.0f);
			// 衝突判定距離の二乗
			float len = pow((1.0f + 1.0f), 2.0f);

			// 弾と弾の交差
			if (dist <= len) {
				// 自弾の衝突コールバックを呼び出す
				playerBullet->OnCollision();
				// 敵弾の衝突コールバックを呼び出す
				enemyBullet->OnCollision();
			}
		}
	}
#pragma endregion
}

// void GameScene::AddPlayerBullet(PlayerBullet* playerBullet) {
//	// リストに登録する
//	playerBullets_.push_back(playerBullet);
// }
//
// void GameScene::AddEnemyBullet(EnemyBullet* enemyBullet) {
//	// リストに登録する
//	enemyBullets_.push_back(enemyBullet);
// }
