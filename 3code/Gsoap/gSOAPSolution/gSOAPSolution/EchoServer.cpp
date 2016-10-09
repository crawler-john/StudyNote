#include "EchoServer.h"
#include "EchoService.hpp"
#include <fstream>


EchoServer::EchoServer(void)
{
}


EchoServer::~EchoServer(void)
{
}

void EchoServer::run()
{
	//�½������log��¼�����з���Ĵ�����Ϣ�����¼
	std::ofstream _log("EchoService.log", std::ios::app);
	//����EchoService����
	EchoService echo;
	int _error = SOAP_OK;
	echo.bind_flags = SO_REUSEADDR;
	while(true)
	{
		//��8080�˿ڿ�������
		_error = echo.run(8080);
		//�������������ڱ�׼�������д�ӡ������Ϣ
		echo.soap_stream_fault(std::cerr);
		//��������������log��¼��д�������Ϣ
		echo.soap_stream_fault(_log);
		_log.flush();
		//��������ϣ����¿�ʼ����
	}
}