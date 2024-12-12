#pragma once
#include <KamataEngine.h>
#include <math.h>
#include <math\Matrix4x4.h>
#include <math\Vector3.h>

//
// 行列操作関連の関数
//

// 2つの行列を掛け算する関数（行列同士の積）
KamataEngine::Matrix4x4 Multiply(KamataEngine::Matrix4x4 matrix1, KamataEngine::Matrix4x4 matrix2);

// 拡大縮小行列を作成する関数
// scale: 拡大・縮小するための倍率ベクトル
KamataEngine::Matrix4x4 MakeScaleMatrix(const KamataEngine::Vector3& scale);

// 平行移動行列を作成する関数
// translate: 移動量を表すベクトル
KamataEngine::Matrix4x4 MakeTranslateMatrix(const KamataEngine::Vector3& translate);

// X軸周りの回転行列を作成する関数
// radian: 回転角度（ラジアン）
KamataEngine::Matrix4x4 MakeRotateXMatrix(float radian);

// Y軸周りの回転行列を作成する関数
// radian: 回転角度（ラジアン）
KamataEngine::Matrix4x4 MakeRotateYMatrix(float radian);

// Z軸周りの回転行列を作成する関数
// radian: 回転角度（ラジアン）
KamataEngine::Matrix4x4 MakeRotateZMatrix(float radian);

// 3次元アフィン変換行列を作成する関数
// scale: 拡大縮小ベクトル
// rotate: 回転角度ベクトル（X, Y, Z軸）
// translation: 平行移動ベクトル
KamataEngine::Matrix4x4 MakeAffineMatrix(const KamataEngine::Vector3& scale, const KamataEngine::Vector3& rotate, const KamataEngine::Vector3& translation);

// プレイヤー専用のアフィン変換行列を作成する関数
// scale: プレイヤーの拡大縮小ベクトル
// rotate: プレイヤーの回転角度ベクトル
// translate: プレイヤーの平行移動ベクトル
KamataEngine::Matrix4x4 PlayerAffineMatrix(const KamataEngine::Vector3& scale, const KamataEngine::Vector3& rotate, const KamataEngine::Vector3& translate);

// ベクトルに行列を掛けて変換する関数
// vector: 変換するベクトル
// matrix: 変換行列
KamataEngine::Vector3 Transform(const KamataEngine::Vector3& vector, const KamataEngine::Matrix4x4& matrix);

// 法線ベクトルの変換
// v : 法線ベクトル
// m : 4x4の変換行列
KamataEngine::Vector3 TransformNormal(const KamataEngine::Vector3& v, const KamataEngine::Matrix4x4& m);

// 逆行列を計算する関数
// m: 元の行列
KamataEngine::Matrix4x4 Inverse(const KamataEngine::Matrix4x4& m);

//
// ベクトル演算関連の関数
//

// EaseInOut補間関数
// x1: 始点の値
// x2: 終点の値
// t: 補間係数（0.0〜1.0）
float EaseInOut(float x1, float x2, float t);

// 線形補間関数（Lerp）
// x1: 始点の値
// x2: 終点の値
// t: 補間係数（0.0〜1.0）
float Lerp(float x1, float x2, float t);

// ベクトルの線形補間関数
// v1: 始点のベクトル
// v2: 終点のベクトル
// t: 補間係数（0.0〜1.0）
KamataEngine::Vector3 Lerp(const KamataEngine::Vector3& v1, const KamataEngine::Vector3& v2, float t);

// Vector3同士の演算子オーバーロード

// 足し算
KamataEngine::Vector3& operator+=(KamataEngine::Vector3& lhs, const KamataEngine::Vector3& rhv);
const KamataEngine::Vector3 operator+(const KamataEngine::Vector3& v1, const KamataEngine::Vector3& v2);

// 引き算
KamataEngine::Vector3& operator-=(KamataEngine::Vector3& lhs, const KamataEngine::Vector3& rhv);
const KamataEngine::Vector3 operator-(const KamataEngine::Vector3& v1, const KamataEngine::Vector3& v2);

// 掛け算（ベクトル同士）
KamataEngine::Vector3& operator*=(KamataEngine::Vector3& lhs, const KamataEngine::Vector3& rhv);

// スカラー掛け算
KamataEngine::Vector3& operator*=(KamataEngine::Vector3 v, float s);
const KamataEngine::Vector3 operator*(const KamataEngine::Vector3& v, float s);

// スカラー割り算（未実装）

// 行列同士の掛け算
KamataEngine::Matrix4x4& operator*=(KamataEngine::Matrix4x4& lhs, const KamataEngine::Matrix4x4& rhv);
