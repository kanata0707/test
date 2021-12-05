#include <mutex>
#include "RingBuff.h"

#pragma region DataCAN：リングバッファに格納するCANデータ形式
/// <summary>
/// リングバッファに格納するCANデータ形式
/// </summary>
struct canData
{
    char message[64];
    char EDP[64];
};
#pragma endregion

#pragma region RingBuffForCAN：CANデータ用リングバッファクラス
/// <summary>
/// CANデータ用リングバッファクラス
/// </summary>
class RingBufferForCAN : public RingBufferBase {
private:
    canData* _canData = nullptr;                                        // リングバッファのポインタ

public:
    RingBufferForCAN(unsigned int prmBuffSize);                         // コンストラクタ
    ~RingBufferForCAN();                                                // デストラクタ
    int SetBufferSize(unsigned int prmBuffSize);                        // リングバッファのサイズを指定(0より大の整数、2の冪乗が最適)
    int WriteBuffer(canData prmCanData);                                // リングバッファにデータを書き込み
    canData ReadBuffer();                                               // リングバッファの最古データを読み込み
};
#pragma endregion