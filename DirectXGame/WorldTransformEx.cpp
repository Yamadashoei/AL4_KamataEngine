#include <3d\WorldTransform.h>
#include "kMath.h"

void KamataEngine::WorldTransform::UpdateMatrix() {
	// スケール、回転、平行移動を合成して行列を計算する
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);
	// 親があれば親のワールド行列を掛ける
	if (parent_) {
		KamataEngine::WorldTransform::matWorld_ = 
			Multiply(KamataEngine::WorldTransform::matWorld_, parent_->matWorld_);
	}
	
	// 定数バッファに転送する
	TransferMatrix();
}

