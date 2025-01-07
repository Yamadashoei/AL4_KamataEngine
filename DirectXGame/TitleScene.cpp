#include "TitleScene.h"
#include <base\DirectXCommon.h>
#include <input\Input.h>
#include <cmath>
#include <numbers>

TitleScene::~TitleScene() {
	delete model_;
	delete sprite_;
}

void TitleScene::Initialize() {
	// model_ = Model::CreateFromOBJ("");
	//  ビュープロジェクションの初期化
	viewProjection_.Initialize();
	finished_ = false;
	textureHandle_ = KamataEngine::TextureManager::Load("./Resources/titleFont/Title.png");
	sprite_ = KamataEngine::Sprite::Create(textureHandle_, {0, 0});
}

void TitleScene::Update() {

	if (KamataEngine::Input::GetInstance()->PushKey(DIK_SPACE)) {
		finished_ = true;
	}

}

void TitleScene::Draw() {
	KamataEngine::DirectXCommon* dxCommon_ = KamataEngine::DirectXCommon::GetInstance();
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	KamataEngine::Sprite::PreDraw(commandList);
	sprite_->Draw();

	KamataEngine::Sprite::PostDraw();
	dxCommon_->ClearDepthBuffer();
}