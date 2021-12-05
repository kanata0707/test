#include "RingBuffCAN.h"

#pragma region RingBufferForCAN：コンストラクタ
RingBufferForCAN::RingBufferForCAN(unsigned int prmBuffSize) : RingBufferBase() {
	SetBufferSize(prmBuffSize);											// リングバッファのサイズを指定、メモリ上にバッファを確保
}
#pragma endregion

#pragma region RingBufferForCAN：デストラクタ
/// <summary>
/// デストラクタ
/// </summary>
RingBufferForCAN::~RingBufferForCAN() {
	if (_canData != nullptr) {
		delete[] _canData;
	}
}
#pragma endregion

#pragma region SetBufferSize：リングバッファへ指定
/// <summary>
/// SetBufferSize
/// </summary>
/// <param name="prmBuffSize">リングバッファサイズ</param>
/// <returns>0：正常、1：異常</returns>
int RingBufferForCAN::SetBufferSize(unsigned int prmBuffSize) {
	int result = 0;

	result = RingBufferBase::SetBufferSize(prmBuffSize);				// ベースクラスのメンバー設定
	if (result != 0) {
		// ベースクラスのメンバー設定に失敗した場合
		return result;
	}

	if (prmBuffSize > 0) {
		std::lock_guard<std::mutex> lock(_mtx);							// 排他

		if (_canData != nullptr)
		{
			// すでにメモリ上にリングバッファが確保されている場合は、一旦削除
			delete[] _canData;
		}
		_canData = new canData[prmBuffSize];							// メモリ上にリングバッファを確保
	}
	else {
		// 設定サイズが0以下の場合エラーとする
		int result = 1;
	}

	return result;
}
#pragma endregion

#pragma region WriteBuffer：リングバッファにデータを書き込み
/// <summary>
/// リングバッファにデータを書き込み
/// </summary>
/// <param name="prmCanData">書きこみデータ</param>
/// <returns>0：正常、1：異常</returns>
int RingBufferForCAN::WriteBuffer(canData prmCanData) {
	int result = 0;
	if (_buffSize > 0) {
		// リングバッファが確保されている場合のみ処理
		std::lock_guard<std::mutex> lock(_mtx);							// 排他
		if (_buffSize > _writePtr - _readPtr) {
			// リングバッファへ書き込み
			unsigned int wPtr = _writePtr % _buffSize;					// 配列引数算出
			_canData[wPtr] = prmCanData;								// データをリングバッファへ書き込み
			_writePtr++;												// 書き込みポインタを進める
			if (_dataSize < _buffSize) {
				// 書きこんだデータサイズを保持
				_dataSize++;
			}
		}
		else {
			// 一度も読み込んでいないデータを上書き使用としたためエラーとする
			result = 1;
		}
	}
	else {
		// バッファサイズが確保されていないためエラーとする
		result = 1;
	}

	return result;
}
#pragma endregion

#pragma region ReadBuffer：リングバッファのデータを読み込み
/// <summary>
/// リングバッファのデータを読み込み
/// </summary>
/// <param name="prmReadPtr">配列引数番号</param>
/// <returns>読み込んだデータ</returns>
/// <memo>最古のでーたを取得する</memo>
canData RingBufferForCAN::ReadBuffer() {
	canData retData = { "error", "none" };
	if (_readPtr < _writePtr) {
		// データ読み込み処理
		std::lock_guard<std::mutex> lock(_mtx);							// 排他
		unsigned int rPtr = _readPtr % _buffSize;						// 配列引数算出
		retData = _canData[rPtr];
		_readPtr++;
		if ((_writePtr > _buffSize) && (_readPtr > _buffSize)) {
			// カウンタのオーバーフロー対策
			_writePtr -= _buffSize;
			_readPtr -= _buffSize;
		}

		return retData;
	}
	else {
		// 読み込み位置が書き込み位置を超えた場合、ランダムなデータを渡す
		return retData;
	}
}
#pragma endregion