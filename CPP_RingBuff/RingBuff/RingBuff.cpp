#include "RingBuff.h"

#pragma region RingBufferBase：コンストラクタ
/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="prmBuffSize">バッファサイズ</param>
RingBufferBase::RingBufferBase(unsigned int prmBuffSize) {
	SetBufferSize(prmBuffSize);											// リングバッファのサイズを指定、メモリ上にバッファを確保
}
#pragma endregion

#pragma region RingBufferBase：コンストラクタ
/// <summary>
/// コンストラクタ
/// </summary>
RingBufferBase::RingBufferBase() {

}
#pragma endregion

#pragma region ~RingBufferBase：デストラクタ
/// <summary>
/// デストラクタ
/// </summary>
RingBufferBase::~RingBufferBase() {
}
#pragma endregion

#pragma region SetBufferSize：リングバッファへ指定
/// <summary>
/// リングバッファのサイズを指定
/// </summary>
/// <param name="prmBuffuffSize">リングバッファサイズ</param>
/// <returns>0：正常、1：異常</returns>
int RingBufferBase::SetBufferSize(unsigned int prmBuffSize) {
	int result = 0;

	if (prmBuffSize > 0) {
		std::lock_guard<std::mutex> lock(_mtx);							// 排他

		_buffSize = prmBuffSize;										// リングバッファのサイズを保持
		_dataSize = 0;													// リングバッファ内に書き込まれたデータ数
		_writePtr = 0;													// 書き込み位置(最新データの位置)
		_readPtr = 0;													// 読み込み位置(最古のデータ位置)
	}
	else {
		// 設定サイズが0以下の場合エラーとする
		int result = 1;
	}

	return result;
}
#pragma endregion

#pragma region GetBufferSize：リングバッファのサイズを取得
/// <summary>
/// リングバッファのサイズを取得
/// </summary>
/// <returns>リングバッファサイズ</returns>
unsigned int RingBufferBase::GetBufferSize() {
	std::lock_guard<std::mutex> lock(_mtx);								// 排他
	return _buffSize;
}
#pragma endregion