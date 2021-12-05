#include <mutex>
#include "RingBuff.h"

#pragma region DataCAN�F�����O�o�b�t�@�Ɋi�[����CAN�f�[�^�`��
/// <summary>
/// �����O�o�b�t�@�Ɋi�[����CAN�f�[�^�`��
/// </summary>
struct canData
{
    char message[64];
    char EDP[64];
};
#pragma endregion

#pragma region RingBuffForCAN�FCAN�f�[�^�p�����O�o�b�t�@�N���X
/// <summary>
/// CAN�f�[�^�p�����O�o�b�t�@�N���X
/// </summary>
class RingBufferForCAN : public RingBufferBase {
private:
    canData* _canData = nullptr;                                        // �����O�o�b�t�@�̃|�C���^

public:
    RingBufferForCAN(unsigned int prmBuffSize);                         // �R���X�g���N�^
    ~RingBufferForCAN();                                                // �f�X�g���N�^
    int SetBufferSize(unsigned int prmBuffSize);                        // �����O�o�b�t�@�̃T�C�Y���w��(0����̐����A2�̙p�悪�œK)
    int WriteBuffer(canData prmCanData);                                // �����O�o�b�t�@�Ƀf�[�^����������
    canData ReadBuffer();                                               // �����O�o�b�t�@�̍ŌÃf�[�^��ǂݍ���
};
#pragma endregion