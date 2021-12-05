#include <mutex>

#pragma region RingBufferBase：リングバッファベースクラス
/// <summary>
/// リングバッファベースクラス
/// </summary>
class RingBufferBase
{
protected:
    unsigned int _buffSize = 0;                                         // リングバッファのサイズ
    unsigned int _dataSize = 0;                                         // リングバッファ内に書き込まれたデータ数
    unsigned int _writePtr = 0;                                         // 書き込み位置(最新データの位置)
    unsigned int _readPtr = 0;                                          // 読み込み位置(最古のデータ位置)
    std::mutex _mtx;                                                    // mutex(読み書き、バッファサイズ変更を排他)

public:
    RingBufferBase(unsigned int prmBuffSize);                           // コンストラクタ(リングバッファのサイズを指定(2の冪乗が最適))
    RingBufferBase();                                                   // コンストラクタ(処理なし)
    virtual ~RingBufferBase();                                          // デストラクタ
    virtual int SetBufferSize(unsigned int prmBuffSize);                // リングバッファのサイズを指定(0より大の整数、2の冪乗が最適)
    unsigned int GetBufferSize();                                       // リングバッファのサイズを取得
};
#pragma endregion
