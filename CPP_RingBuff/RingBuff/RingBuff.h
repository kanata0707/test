#include <mutex>

#pragma region RingBufferBase�F�����O�o�b�t�@�x�[�X�N���X
/// <summary>
/// �����O�o�b�t�@�x�[�X�N���X
/// </summary>
class RingBufferBase
{
protected:
    unsigned int _buffSize = 0;                                         // �����O�o�b�t�@�̃T�C�Y
    unsigned int _dataSize = 0;                                         // �����O�o�b�t�@���ɏ������܂ꂽ�f�[�^��
    unsigned int _writePtr = 0;                                         // �������݈ʒu(�ŐV�f�[�^�̈ʒu)
    unsigned int _readPtr = 0;                                          // �ǂݍ��݈ʒu(�ŌẪf�[�^�ʒu)
    std::mutex _mtx;                                                    // mutex(�ǂݏ����A�o�b�t�@�T�C�Y�ύX��r��)

public:
    RingBufferBase(unsigned int prmBuffSize);                           // �R���X�g���N�^(�����O�o�b�t�@�̃T�C�Y���w��(2�̙p�悪�œK))
    RingBufferBase();                                                   // �R���X�g���N�^(�����Ȃ�)
    virtual ~RingBufferBase();                                          // �f�X�g���N�^
    virtual int SetBufferSize(unsigned int prmBuffSize);                // �����O�o�b�t�@�̃T�C�Y���w��(0����̐����A2�̙p�悪�œK)
    unsigned int GetBufferSize();                                       // �����O�o�b�t�@�̃T�C�Y���擾
};
#pragma endregion
