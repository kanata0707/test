#include "RingBuffCAN.h"

#pragma region RingBufferForCAN�F�R���X�g���N�^
RingBufferForCAN::RingBufferForCAN(unsigned int prmBuffSize) : RingBufferBase() {
	SetBufferSize(prmBuffSize);											// �����O�o�b�t�@�̃T�C�Y���w��A��������Ƀo�b�t�@���m��
}
#pragma endregion

#pragma region RingBufferForCAN�F�f�X�g���N�^
/// <summary>
/// �f�X�g���N�^
/// </summary>
RingBufferForCAN::~RingBufferForCAN() {
	if (_canData != nullptr) {
		delete[] _canData;
	}
}
#pragma endregion

#pragma region SetBufferSize�F�����O�o�b�t�@�֎w��
/// <summary>
/// SetBufferSize
/// </summary>
/// <param name="prmBuffSize">�����O�o�b�t�@�T�C�Y</param>
/// <returns>0�F����A1�F�ُ�</returns>
int RingBufferForCAN::SetBufferSize(unsigned int prmBuffSize) {
	int result = 0;

	result = RingBufferBase::SetBufferSize(prmBuffSize);				// �x�[�X�N���X�̃����o�[�ݒ�
	if (result != 0) {
		// �x�[�X�N���X�̃����o�[�ݒ�Ɏ��s�����ꍇ
		return result;
	}

	if (prmBuffSize > 0) {
		std::lock_guard<std::mutex> lock(_mtx);							// �r��

		if (_canData != nullptr)
		{
			// ���łɃ�������Ƀ����O�o�b�t�@���m�ۂ���Ă���ꍇ�́A��U�폜
			delete[] _canData;
		}
		_canData = new canData[prmBuffSize];							// ��������Ƀ����O�o�b�t�@���m��
	}
	else {
		// �ݒ�T�C�Y��0�ȉ��̏ꍇ�G���[�Ƃ���
		int result = 1;
	}

	return result;
}
#pragma endregion

#pragma region WriteBuffer�F�����O�o�b�t�@�Ƀf�[�^����������
/// <summary>
/// �����O�o�b�t�@�Ƀf�[�^����������
/// </summary>
/// <param name="prmCanData">�������݃f�[�^</param>
/// <returns>0�F����A1�F�ُ�</returns>
int RingBufferForCAN::WriteBuffer(canData prmCanData) {
	int result = 0;
	if (_buffSize > 0) {
		// �����O�o�b�t�@���m�ۂ���Ă���ꍇ�̂ݏ���
		std::lock_guard<std::mutex> lock(_mtx);							// �r��
		if (_buffSize > _writePtr - _readPtr) {
			// �����O�o�b�t�@�֏�������
			unsigned int wPtr = _writePtr % _buffSize;					// �z������Z�o
			_canData[wPtr] = prmCanData;								// �f�[�^�������O�o�b�t�@�֏�������
			_writePtr++;												// �������݃|�C���^��i�߂�
			if (_dataSize < _buffSize) {
				// �������񂾃f�[�^�T�C�Y��ێ�
				_dataSize++;
			}
		}
		else {
			// ��x���ǂݍ���ł��Ȃ��f�[�^���㏑���g�p�Ƃ������߃G���[�Ƃ���
			result = 1;
		}
	}
	else {
		// �o�b�t�@�T�C�Y���m�ۂ���Ă��Ȃ����߃G���[�Ƃ���
		result = 1;
	}

	return result;
}
#pragma endregion

#pragma region ReadBuffer�F�����O�o�b�t�@�̃f�[�^��ǂݍ���
/// <summary>
/// �����O�o�b�t�@�̃f�[�^��ǂݍ���
/// </summary>
/// <param name="prmReadPtr">�z������ԍ�</param>
/// <returns>�ǂݍ��񂾃f�[�^</returns>
/// <memo>�ŌÂ̂Ł[�����擾����</memo>
canData RingBufferForCAN::ReadBuffer() {
	canData retData = { "error", "none" };
	if (_readPtr < _writePtr) {
		// �f�[�^�ǂݍ��ݏ���
		std::lock_guard<std::mutex> lock(_mtx);							// �r��
		unsigned int rPtr = _readPtr % _buffSize;						// �z������Z�o
		retData = _canData[rPtr];
		_readPtr++;
		if ((_writePtr > _buffSize) && (_readPtr > _buffSize)) {
			// �J�E���^�̃I�[�o�[�t���[�΍�
			_writePtr -= _buffSize;
			_readPtr -= _buffSize;
		}

		return retData;
	}
	else {
		// �ǂݍ��݈ʒu���������݈ʒu�𒴂����ꍇ�A�����_���ȃf�[�^��n��
		return retData;
	}
}
#pragma endregion