#include "RingBuff.h"

#pragma region RingBufferBase�F�R���X�g���N�^
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="prmBuffSize">�o�b�t�@�T�C�Y</param>
RingBufferBase::RingBufferBase(unsigned int prmBuffSize) {
	SetBufferSize(prmBuffSize);											// �����O�o�b�t�@�̃T�C�Y���w��A��������Ƀo�b�t�@���m��
}
#pragma endregion

#pragma region RingBufferBase�F�R���X�g���N�^
/// <summary>
/// �R���X�g���N�^
/// </summary>
RingBufferBase::RingBufferBase() {

}
#pragma endregion

#pragma region ~RingBufferBase�F�f�X�g���N�^
/// <summary>
/// �f�X�g���N�^
/// </summary>
RingBufferBase::~RingBufferBase() {
}
#pragma endregion

#pragma region SetBufferSize�F�����O�o�b�t�@�֎w��
/// <summary>
/// �����O�o�b�t�@�̃T�C�Y���w��
/// </summary>
/// <param name="prmBuffuffSize">�����O�o�b�t�@�T�C�Y</param>
/// <returns>0�F����A1�F�ُ�</returns>
int RingBufferBase::SetBufferSize(unsigned int prmBuffSize) {
	int result = 0;

	if (prmBuffSize > 0) {
		std::lock_guard<std::mutex> lock(_mtx);							// �r��

		_buffSize = prmBuffSize;										// �����O�o�b�t�@�̃T�C�Y��ێ�
		_dataSize = 0;													// �����O�o�b�t�@���ɏ������܂ꂽ�f�[�^��
		_writePtr = 0;													// �������݈ʒu(�ŐV�f�[�^�̈ʒu)
		_readPtr = 0;													// �ǂݍ��݈ʒu(�ŌẪf�[�^�ʒu)
	}
	else {
		// �ݒ�T�C�Y��0�ȉ��̏ꍇ�G���[�Ƃ���
		int result = 1;
	}

	return result;
}
#pragma endregion

#pragma region GetBufferSize�F�����O�o�b�t�@�̃T�C�Y���擾
/// <summary>
/// �����O�o�b�t�@�̃T�C�Y���擾
/// </summary>
/// <returns>�����O�o�b�t�@�T�C�Y</returns>
unsigned int RingBufferBase::GetBufferSize() {
	std::lock_guard<std::mutex> lock(_mtx);								// �r��
	return _buffSize;
}
#pragma endregion