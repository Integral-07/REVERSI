#if 0
#include <iostream> //�W�����o��
#include <sys/socket.h> //�A�h���X�h���C��
#include <sys/types.h> //�\�P�b�g�^�C�v
#include <arpa/inet.h> //�o�C�g�I�[�_�̕ϊ��ɗ��p
#include <unistd.h> //close()�ɗ��p
#include <string> //string�^

int main() {

	//�\�P�b�g�̐���
	int sockfd = socket(AF_INET, SOCK_STREAM, 0); //�A�h���X�h���C��, �\�P�b�g�^�C�v, �v���g�R��
	if (sockfd < 0) { //�G���[����

		std::cout << "Error socket:" << std::strerror(errno); //�W���o��
		exit(1); //�ُ�I��
	}

	//�A�h���X�̐���
	struct sockaddr_in addr; //�ڑ���̏��p�̍\����(ipv4)
	memset(&addr, 0, sizeof(struct sockaddr_in)); //memset�ŏ�����
	addr.sin_family = AF_INET; //�A�h���X�t�@�~��(ipv4)
	addr.sin_port = htons(1234); //�|�[�g�ԍ�,htons()�֐���16bit�z�X�g�o�C�g�I�[�_�[���l�b�g���[�N�o�C�g�I�[�_�[�ɕϊ�
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //IP�A�h���X,inet_addr()�֐��̓A�h���X�̖|��

	//�\�P�b�g�o�^
	if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) { //�\�P�b�g, �A�h���X�|�C���^, �A�h���X�T�C�Y //�G���[����

		std::cout << "Error bind:" << std::strerror(errno); //�W���o��
		exit(1); //�ُ�I��
	}

	//��M�҂�
	if (listen(sockfd, SOMAXCONN) < 0) { //�\�P�b�g, �L���[�̍ő咷 //�G���[����

		std::cout << "Error listen:" << std::strerror(errno); //�W���o��
		close(sockfd); //�\�P�b�g�N���[�Y
		exit(1); //�ُ�I��
	}

	//�ڑ��҂�
	struct sockaddr_in get_addr; //�ڑ�����̃\�P�b�g�A�h���X
	socklen_t len = sizeof(struct sockaddr_in); //�ڑ�����̃A�h���X�T�C�Y
	int connect = accept(sockfd, (struct sockaddr*)&get_addr, &len); //�ڑ��҂��\�P�b�g, �ڑ�����̃\�P�b�g�A�h���X�|�C���^, �ڑ�����̃A�h���X�T�C�Y

	if (connect < 0) { //�G���[����

		std::cout << "Error accept:" << std::strerror(errno); //�W���o��
		exit(1); //�ُ�I��
	}

	//��M
	char str[12]; //��M�p�f�[�^�i�[�p
	recv(connect, str, 12, 0); //��M
	std::cout << str << std::endl; //�W���o��

	//���M
	send(connect, str, 12, 0); //���M
	std::cout << str << std::endl; //�W���o��

	//�\�P�b�g�N���[�Y
	close(connect);
	close(sockfd);

	return 0;
}
#endif